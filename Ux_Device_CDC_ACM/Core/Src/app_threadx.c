/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "ux_device_cdc_acm.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	GPIO_TypeDef *ports[4];
	uint16_t pins[4];
	int8_t seqCounter;
} stepper;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define THREAD_STACK_SIZE 512
#define QUEUE_STACK_SIZE 512

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart2;


// Step sequence for motor control (half-drive)
const uint8_t step_sequence[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};


//Threads:
//Sensor Sampling 				100Hz
//	Communicate with CDC over I2C
//Processing
//	Filter Signal (maybe just moving average)
//	Calculate X and Y pos from Cap
//	Calculate steps to get within target
//Motor Control					1kHz
//	Step motors
//USB Communication with PC		INTERUPT?
//	Update Target pos from UART when data comes in

//Shared variables of target posX and posY might need MUTEX


uint8_t motor_thread_stack[THREAD_STACK_SIZE];
TX_THREAD motor_thread_ptr;

uint8_t sensor_thread_stack[THREAD_STACK_SIZE];
TX_THREAD sensor_thread_ptr;

stepper motorX = {
		{X_IN1_GPIO_Port, X_IN2_GPIO_Port, X_IN3_GPIO_Port, X_IN4_GPIO_Port},
		{X_IN1_Pin, X_IN2_Pin, X_IN3_Pin, X_IN4_Pin},0};

stepper motorY = {
		{Y_IN1_GPIO_Port, Y_IN2_GPIO_Port, Y_IN3_GPIO_Port, Y_IN4_GPIO_Port},
		{Y_IN1_Pin, Y_IN2_Pin, Y_IN3_Pin, Y_IN4_Pin},0};

int target = 4096*14;
int targetY = 0;

extern uint32_t targetBufferX[50];
extern uint32_t targetBufferY[50];
extern uint8_t targetBufferEnd;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

// Set up Tasks
VOID Motor_Control_thread_entry(ULONG initial_input);
VOID Sensor_Polling_thread_entry(ULONG initial_input);


void stepMotor(stepper *motor, int8_t direction) {
	HAL_GPIO_WritePin((*motor).ports[0], (*motor).pins[0], step_sequence[(*motor).seqCounter][0]);
	HAL_GPIO_WritePin((*motor).ports[1], (*motor).pins[1], step_sequence[(*motor).seqCounter][2]);
	HAL_GPIO_WritePin((*motor).ports[2], (*motor).pins[2], step_sequence[(*motor).seqCounter][1]);
	HAL_GPIO_WritePin((*motor).ports[3], (*motor).pins[3], step_sequence[(*motor).seqCounter][3]);

	(*motor).seqCounter += direction;

	if ((*motor).seqCounter < 0) {
		(*motor).seqCounter = 7;
	}
	else if ((*motor).seqCounter > 7){
		(*motor).seqCounter = 0;
	}
}

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */
  /* USER CODE BEGIN App_ThreadX_Init */
  tx_thread_create(&motor_thread_ptr,"Motor_Control_Thread",Motor_Control_thread_entry,0,motor_thread_stack,THREAD_STACK_SIZE,20,20,1,TX_AUTO_START);
  tx_thread_create(&sensor_thread_ptr,"Sensor_Polling_Thread",Sensor_Polling_thread_entry,0,sensor_thread_stack,THREAD_STACK_SIZE,10,10,1,TX_AUTO_START);

  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN Before_Kernel_Start */

  /* USER CODE END Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN Kernel_Start_Error */

  /* USER CODE END Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */
VOID Motor_Control_thread_entry (ULONG initial_input){
	uint32_t xPos = 0;
	uint32_t yPos = 0;

	uint32_t xTarget = 0;
	uint32_t yTarget = 0;

	uint8_t targetBufferPos = 0;

	while(1) {
		if (xPos > xTarget) {
			stepMotor(&motorX,1);
			xPos--;
		}
		else if (xPos < xTarget){
			stepMotor(&motorX,-1);
			xPos++;
		}

		if (yPos > yTarget) {
			stepMotor(&motorY,1);
			yPos--;
		}
		else if (yPos < yTarget){
			stepMotor(&motorY,-1);
			yPos++;
		}

		if (yPos == yTarget && xPos == xTarget && targetBufferX[targetBufferPos] != 0) {
			xTarget = targetBufferX[targetBufferPos];
			yTarget = targetBufferY[targetBufferPos];

			targetBufferPos++;
			if (targetBufferPos >= 50) {
				targetBufferPos = 0;
			}
			tx_thread_sleep(100);
		}
		tx_thread_sleep(1);
	}

}


//I2C address
#define CDC_ADR 80

//Configuration bits
#define CIN1 		0b0000000000000000
#define CIN2 		0b0010000000000000
#define CAPDAC 		0b0001000000000000

#define OFFSET1     7
#define OFFSET2 	8

#define RATE100S 	0b0000010000000000
#define REPEAT	 	0b0000000100000000
#define MEAS1 		0b10000000
#define MEAS2	 	0b01000000

#define MEAS1_DONE	0b00001000
#define MEAS2_DONE 	0b00000100

#define RESETCONF	0x1C00

//Registers
#define MEAS1_CONF 	0x08
#define MEAS2_CONF 	0x09
#define FDC_CONF 	0x0C

#define MEAS1_MSB 	0x00
#define MEAS1_LSB 	0x01
#define MEAS2_MSB 	0x02
#define MEAS2_LSB 	0x03

VOID Sensor_Polling_thread_entry (ULONG initial_input){

  	  uint8_t buffer[2];

		  //tx_thread_sleep(50);
		  //HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,FDC_CONF,1,&buffer,2,HAL_MAX_DELAY);
	  if (HAL_I2C_IsDeviceReady(&hi2c2, CDC_ADR << 1, 3, HAL_MAX_DELAY) == HAL_OK) {

		  //Configure measurements
		  uint16_t measConf = CIN1 | CAPDAC | (OFFSET1 << 5);
		  buffer[1] = measConf & 0xFF;
		  buffer[0] = measConf >> 8;
		  HAL_I2C_Mem_Write(&hi2c2, CDC_ADR << 1,MEAS1_CONF,1,buffer,2,HAL_MAX_DELAY);

		  measConf = CIN2 | CAPDAC | (OFFSET2 << 5);
		  buffer[1] = measConf & 0xFF;
		  buffer[0] = measConf >> 8;
		  HAL_I2C_Mem_Write(&hi2c2, CDC_ADR << 1,MEAS2_CONF,1,buffer,2,HAL_MAX_DELAY);
/*
		  measConf = RATE100S | REPEAT | MEAS1 | MEAS2;
		  buffer[1] = measConf & 0xFF;
		  buffer[0] = measConf >> 8;
		  HAL_I2C_Mem_Write(&hi2c2, CDC_ADR << 1,FDC_CONF,1,buffer,2,HAL_MAX_DELAY);
*/
	  }

	  //HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS1_CONF,1,&buffer,2,HAL_MAX_DELAY);
	  //HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS2_CONF,1,&buffer,2,HAL_MAX_DELAY);
	  //HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,FDC_CONF,1,&buffer,2,HAL_MAX_DELAY);


	    uint32_t cap1 = 0;
	    uint32_t cap2 = 0;

	    uint8_t meas1[2] = {(RATE100S >> 8), MEAS1};
	    uint8_t meas2[2] = {(RATE100S >> 8), MEAS2};
	    char message[16];
	    while (1)
	    {
	      /* USER CODE END WHILE */
	  	  if (HAL_I2C_IsDeviceReady(&hi2c2, CDC_ADR << 1, 3, HAL_MAX_DELAY) == HAL_OK) {
	  		  HAL_I2C_Mem_Write(&hi2c2, CDC_ADR << 1,FDC_CONF,1,meas1,2,HAL_MAX_DELAY);

	  		  tx_thread_sleep(50);
	  		  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,FDC_CONF,1,&buffer,2,HAL_MAX_DELAY);

	  		  if (buffer[1] & MEAS1_DONE) {

	  			  //LSB
	  			  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS1_LSB,1,&buffer,2,HAL_MAX_DELAY);
	  			  cap1 = buffer[0];

	  			  //MSB
	  			  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS1_MSB,1,&buffer,2,HAL_MAX_DELAY);
	  			  cap1 += (buffer[1] << 8) + (buffer[0] << 16);

	  			  //HAL_UART_Transmit(&huart2,&message,24,HAL_MAX_DELAY);
				  //HAL_UART_Transmit(&huart2,"\n",1,HAL_MAX_DELAY);


	  		  }

	  		  HAL_I2C_Mem_Write(&hi2c2, CDC_ADR << 1,FDC_CONF,1,meas2,2,HAL_MAX_DELAY);

	  		  tx_thread_sleep(50);
	  		  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,FDC_CONF,1,&buffer,2,HAL_MAX_DELAY);

	  		  if (buffer[1] & MEAS2_DONE) {

				  //LSB
				  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS2_LSB,1,&buffer,2,HAL_MAX_DELAY);
				  cap2 = buffer[0];

				  //MSB
				  HAL_I2C_Mem_Read(&hi2c2, CDC_ADR << 1,MEAS2_MSB,1,&buffer,2,HAL_MAX_DELAY);
				  cap2 += (buffer[1] << 8) + (buffer[0] << 16);

			  }

	  		itoa(cap1,&message,10);
	  		HAL_UART_Transmit(&huart2,&message,10,HAL_MAX_DELAY);
	  		HAL_UART_Transmit(&huart2," ",1,HAL_MAX_DELAY);
	  		itoa(cap2,&message,10);
	  		HAL_UART_Transmit(&huart2,&message,10,HAL_MAX_DELAY);
	  		HAL_UART_Transmit(&huart2,"\n",1,HAL_MAX_DELAY);
	  		  tx_thread_sleep(100);
	  	  }

	    }
}
/* USER CODE END 1 */
