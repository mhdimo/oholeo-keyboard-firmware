/*
 * keyboard_conf.h
 *
 *  Created on: Oct 29, 2023
 *      Author: xq123
 */

#ifndef KEYBOARD_CONF_H_
#define KEYBOARD_CONF_H_

//#define EXTENDED_SAMPLING

//#define PAUSE_TIM_WHEN_CALCULATING

#define TIM2_COUNTER_PERIOD 2400*2-1

#define ADC12_BEGIN_TIME 800*2

#define ADC34_BEGIN_TIME 1600*2

#define DEFAULT_ADVANCED_KEY_MODE LEFL_KEY_ANALOG_RAPID_MODE
//#define DEFAULT_ADVANCED_KEY_MODE LEFL_KEY_ANALOG_NORMAL_MODE

#define DEFAULT_TRIGGER_DISTANCE 0.04

#define DEFAULT_RELEASE_DISTANCE 0.04

#define DEFAULT_UPPER_DEADZONE 0.02

#define DEFAULT_LOWER_DEADZONE 0.35

#define DEFAULT_SCHMITT_PARAMETER 0.01

#endif /* KEYBOARD_CONF_H_ */
