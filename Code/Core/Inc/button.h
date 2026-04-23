/*
 * button.h
 *
 *  Created on: Apr 22, 2026
 *      Author: jackd
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

//Button Inputs
#define C_BUTTON GPIO_PIN_4
#define C_BUTTON_PORT (0b01 << 10)
#define Cs_BUTTON GPIO_PIN_2
#define Cs_BUTTON_PORT (0b01 << 6)
#define D_BUTTON GPIO_PIN_0
#define D_BUTTON_PORT (0b01)

#define Ds_BUTTON GPIO_PIN_6
#define Ds_BUTTON_PORT (0b01 << 14)

#define E_BUTTON GPIO_PIN_8
#define E_BUTTON_PORT (0b01 << 18)

#define F_BUTTON GPIO_PIN_11
#define F_BUTTON_PORT (0b01 << 24)
#define Fs_BUTTON GPIO_PIN_9
#define Fs_BUTTON_PORT (0b01 << 20)

#define G_BUTTON GPIO_PIN_7
#define G_BUTTON_PORT (0b01 << 16)
#define Gs_BUTTON GPIO_PIN_5
#define Gs_BUTTON_PORT (0b01 << 12)
#define A_BUTTON GPIO_PIN_3
#define A_BUTTON_PORT (0b01 << 8)
#define As_BUTTON GPIO_PIN_1
#define As_BUTTON_PORT (0b01 << 2)

#define B_BUTTON GPIO_PIN_10
#define B_BUTTON_PORT (0b01 << 22)


//Mosfet Outputs
#define C_OUT GPIO_PIN_5
#define C_OUT_PORT GPIOF
#define Cs_OUT GPIO_PIN_3
#define Cs_OUT_PORT GPIOF
#define D_OUT GPIO_PIN_1
#define D_OUT_PORT GPIOF
#define Ds_OUT GPIO_PIN_15
#define Ds_OUT_PORT GPIOC
#define E_OUT GPIO_PIN_13
#define E_OUT_PORT GPIOC
#define F_OUT GPIO_PIN_5
#define F_OUT_PORT GPIOE

#define Fs_OUT GPIO_PIN_3
#define Fs_OUT_PORT GPIOE
#define G_OUT GPIO_PIN_1
#define G_OUT_PORT GPIOE
#define Gs_OUT GPIO_PIN_9
#define Gs_OUT_PORT GPIOB
#define A_OUT GPIO_PIN_7
#define A_OUT_PORT GPIOB
#define As_OUT GPIO_PIN_5
#define As_OUT_PORT GPIOB
#define B_OUT GPIO_PIN_3
#define B_OUT_PORT GPIOB


#define ONE_LOWER 0.375
#define ONE_UPPER 0.875
#define TWO_LOWER 1.625
#define TWO_UPPER 2.125
#define THREE_LOWER 2.875
#define THREE_UPPER 3.375
#define FOUR_LOWER 4.125
#define FOUR_UPPER 4.625


#endif /* INC_BUTTON_H_ */
