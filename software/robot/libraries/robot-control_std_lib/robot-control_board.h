/*
 * robot-control_board.h
 *
 *  Created on: 29 Jul 2022
 *      Author: Dustin Lehmann
 */

#ifndef ROBOT_CONTROL_BOARD_H_
#define ROBOT_CONTROL_BOARD_H_

#ifdef RCSTD_CONFIG_BOARD_REV_3

#define _RAM_D2 __attribute__(( section(".ramd2block") ))

// LED
#define BOARD_LED_ACT_PORT GPIOD
#define BOARD_LED_ACT_PIN GPIO_PIN_11

#define BOARD_LED_1_PORT GPIOE
#define BOARD_LED_1_PIN GPIO_PIN_10

#define BOARD_LED_2_PORT GPIOE
#define BOARD_LED_2_PIN GPIO_PIN_15

// MEMORY
#define BOARD_EEPROM_CONFIG_ADDRESS 0xA0
#define BOARD_EEPROM_USER_ADDRESS 0xA2

// INTERFACES
#if CORE_CONFIG_USE_I2C
extern I2C_HandleTypeDef hi2c3;
#define BOARD_I2C_INTERN &hi2c3
#endif

#if CORE_CONFIG_USE_SPI
extern SPI_HandleTypeDef hspi2;
#define BOARD_SPI_INTERN &hspi2

#define BOARD_CS_IMU_PORT GPIOB
#define BOARD_CS_IMU_PIN GPIO_PIN_12
#endif


#if CORE_CONFIG_USE_UART
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

#define BOARD_CM4_UART &huart2
#define BOARD_CM4_UART_DMA_RX &hdma_usart2_rx
#define BOARD_CM4_UART_DMA_TX &hdma_usart2_tx

extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;


#define BOARD_RS485_UART &huart8
#define BOARD_RS485_UART_EN_GPIOx GPIOD
#define BOARD_RS485_UART_EN_GPIO_PIN GPIO_PIN_15

#define BOARD_DEBUG_UART &huart1
#define BOARD_DEBUG_UART_DMA_RX &hdma_usart1_rx
#define BOARD_DEBUG_UART_DMA_TX &hdma_usart1_tx
#endif


#endif



#endif /* ROBOT_CONTROL_BOARD_H_ */
