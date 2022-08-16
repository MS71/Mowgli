#include "stm32f1xx_hal.h"

#include "board.h"
#include "stm32_gpiotest.h"

struct {
    GPIO_TypeDef *port;
    uint32_t pin;
} gpio_table[] = {    
    /* A */
    // 1
    {GPIOA,GPIO_PIN_0}, 
    {GPIOA,GPIO_PIN_1}, // P1.1 (not used)
    {GPIOA,GPIO_PIN_2}, // P1.2 (not used,USART2_TX?)
    {GPIOA,GPIO_PIN_3}, // P1.3 (not used,USART2_RX?)
    {GPIOA,GPIO_PIN_4}, // P1.4 (not used)
    {GPIOA,GPIO_PIN_5}, // P1.5 (not used)
    {GPIOA,GPIO_PIN_6}, // P1.6 (not used)
    {GPIOA,GPIO_PIN_7}, 
    {GPIOA,GPIO_PIN_8}, // J6.3 (not used)
    {GPIOA,GPIO_PIN_9}, // J6.1 (not used)
    {GPIOA,GPIO_PIN_10}, // J14.DM (USB)
    {GPIOA,GPIO_PIN_11}, // J14.DP (USB)
    {GPIOA,GPIO_PIN_12},
    {GPIOA,GPIO_PIN_13},
    {GPIOA,GPIO_PIN_14},
    {GPIOA,GPIO_PIN_15},
    /* B */
    // 16
    {GPIOB,GPIO_PIN_0}, // P2.3
    {GPIOB,0}, // (BEEPER)
    {GPIOB,GPIO_PIN_2}, // (LED)
    {GPIOB,GPIO_PIN_3},
    {GPIOB,GPIO_PIN_4},
    {GPIOB,GPIO_PIN_5}, // J18.4 (not used)
    {GPIOB,GPIO_PIN_6}, // USART1_TX,I2C1_SCL => UART to MOTOR BOARD ?
    {GPIOB,GPIO_PIN_7}, // USART1_RX,I2C1_SDA => UART to MOTOR BOARD ?
    {GPIOB,GPIO_PIN_8}, // J5.3 (Wire Sensor)
    {GPIOB,GPIO_PIN_9}, // J5.4 (Wire Sensor)
    {GPIOB,GPIO_PIN_10}, // U1.11 (Wifi,I2C2_SCL?,USART3_TX?)
    {GPIOB,GPIO_PIN_11}, // U1.12 (Wifi,I2C2_SDA?,USART3_RX?)
    {GPIOB,GPIO_PIN_12}, // J5.6 (not used)
    {GPIOB,GPIO_PIN_13}, // J6.5 (not used)
    {GPIOB,GPIO_PIN_14},
    {GPIOB,GPIO_PIN_15},
    /* C */
    // 32
    {GPIOC,GPIO_PIN_0}, // P2.4 J4.STOP J6.14
    {GPIOC,GPIO_PIN_1}, // TP4
    {GPIOC,GPIO_PIN_2}, // TP5
    {GPIOC,GPIO_PIN_3},
    {GPIOC,GPIO_PIN_4},
    {GPIOC,GPIO_PIN_5},
    {GPIOC,GPIO_PIN_6},
    {GPIOC,GPIO_PIN_7}, // J6.4 (not used)
    {GPIOC,GPIO_PIN_8}, // J4.PC8_STOP J5.8 (not used)
    {GPIOC,GPIO_PIN_9},
    {GPIOC,GPIO_PIN_10}, // J18.7 (not used,USART3_TX?)
    {GPIOC,GPIO_PIN_11}, // J18.8 (not used,USART3_RX?)
    {GPIOC,GPIO_PIN_12}, // J4.TX (UART5_TX)
    {GPIOC,GPIO_PIN_13}, 
    {GPIOC,GPIO_PIN_14},
    {GPIOC,GPIO_PIN_15},
    /* D */
    // 48
    {GPIOD,GPIO_PIN_0}, // J6.10 P5.HALL (Wheel Sensor)
    {GPIOD,GPIO_PIN_1}, // J6.16 P4.HALL (Wheel Sensor)
    {GPIOD,GPIO_PIN_2}, // J4.RX (UART5_RX)
    {GPIOD,GPIO_PIN_3}, // J6.15 (not used)
    {GPIOD,GPIO_PIN_4}, // J6.12 (not used)
    {GPIOD,GPIO_PIN_5}, // USART2_TX
    {GPIOD,GPIO_PIN_6}, // USART2_RX
    {GPIOD,GPIO_PIN_7},
    {GPIOD,GPIO_PIN_8}, // TP1
    {GPIOD,GPIO_PIN_9},
    {GPIOD,GPIO_PIN_10}, // TP2
    {GPIOD,GPIO_PIN_11},
    {GPIOD,GPIO_PIN_12},
    {GPIOD,GPIO_PIN_13}, // J18.1 (not used)
    {GPIOD,GPIO_PIN_14},
    {GPIOD,GPIO_PIN_15}, // TP3
    /* E */
    // 64
    {GPIOE,GPIO_PIN_0},
    {GPIOE,GPIO_PIN_1},
    {GPIOE,GPIO_PIN_2},
    {GPIOE,GPIO_PIN_3},
    {GPIOE,GPIO_PIN_4},
    {GPIOE,GPIO_PIN_5}, // J3.2 (not used)
    {GPIOE,GPIO_PIN_6}, // J3.3 (not used)
    {GPIOE,GPIO_PIN_7},
    {GPIOE,GPIO_PIN_8},
    {GPIOE,GPIO_PIN_9}, // U1.2 (Wifi)
    {GPIOE,GPIO_PIN_10}, // U1.17 (Wifi)
    {GPIOE,GPIO_PIN_11}, // U1.16 (Wifi)
    {GPIOE,GPIO_PIN_12}, // U1.15 (Wifi)
    {GPIOE,GPIO_PIN_13}, // U1.6 (Wifi)
    {GPIOE,GPIO_PIN_14}, // U1.7 (Wifi)
    {GPIOE,GPIO_PIN_15}, // U1.8 (Wifi)
    {NULL,0},
};

void stm32_gpiotest_out(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    int i;
    i=0;
    while(gpio_table[i].port != NULL)
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = gpio_table[i].pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(gpio_table[i].port, &GPIO_InitStruct);
        i++;
    }

#if 0
    while(1)
    {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // => HIGH
            HAL_Delay(10);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // => HIGH
            HAL_Delay(10);
    }
#endif

#if 0
    while(1)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET); // => HIGH
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET); // => HIGH
        HAL_Delay(1);
    }
#endif

    while(1)
    {
        // clear all pins ...
        int k;
#if 1 
        // START
        i=0;
        while (gpio_table[i].port != NULL)
        {
            HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_SET); // => L
            i++;
        }
        HAL_Delay(1);
        #if 1
        for (k = 0; k < 8; k++)
        {
            i = 0;
            while (gpio_table[i].port != NULL)
            {
                if ((i & (1 << k)) != 0)
                {
                    HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_RESET); // => H
                }
                else
                {
                    HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_SET); // => H
                }
                i++;
            }
            HAL_Delay(1);
        }
        #endif
        // STOP
        i = 0;
        while (gpio_table[i].port != NULL)
        {
            HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_RESET); // => H
            i++;
        }
        HAL_Delay(1);
        HAL_Delay(100);
#else
        while (gpio_table[j].port != NULL)
        {
            i = 0;
            while (gpio_table[i].port != NULL)
            {
                if (i >= j)
                {
                    HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_RESET); // => H
                }
                i++;
            }
            for (k = 0; k < 1000; k++)
            {
                __NOP();
            }

            i = 0;
            while (gpio_table[i].port != NULL)
            {
                HAL_GPIO_WritePin(gpio_table[i].port, gpio_table[i].pin, GPIO_PIN_RESET); // => L
                i++;
            }
            for (k = 0; k < 1000; k++)
            {
                __NOP();
            }
            j++;
        }
        HAL_Delay(50);
#endif
    }
}
