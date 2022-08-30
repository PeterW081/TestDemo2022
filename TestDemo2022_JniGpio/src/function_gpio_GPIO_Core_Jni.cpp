#include "function_gpio_GPIO_Core_Jni.h"

#include <iostream>
#include <pigpio.h>

/*
 * Class:     function_gpio_GPIO_Core_Jni
 * Method:    env_init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_function_gpio_GPIO_1Core_00024Jni_env_1init(JNIEnv*, jclass)
{
	// Thanks: https://github.com/mattjlewis/pigpioj/blob/214aa8827febf17464f99cda7d19906dd5dda352/pigpioj-native/src/main/native/uk_pigpioj_PigpioGpio.c
	static bool isNeedInit = true;
	if (isNeedInit)
	{
		try
		{
			int status;
			status = gpioCfgSetInternals(gpioCfgGetInternals() | PI_CFG_NOSIGHANDLER);
			if (status < 0)
			{
				throw status;
			}
			status = gpioCfgInterfaces(PI_DISABLE_FIFO_IF | PI_DISABLE_SOCK_IF);
			if (status < 0)
			{
				throw status;
			}
			status = gpioInitialise();
			if (status < 0)
			{
				throw status;
			}
		}
		catch (int status)
		{
			std::cerr << "pigpio initialisation failed." << std::endl;
			std::cerr << "pigpio initialisation status is " << status << "." << std::endl;
			return;
		}
		isNeedInit = false;
	}
}

/*
 * Class:     function_gpio_GPIO_Core_Jni
 * Method:    pin_init
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_function_gpio_GPIO_1Core_00024Jni_pin_1init(JNIEnv*, jclass, jint pin_number, jint pin_mode)
{
	gpioSetMode(pin_number, pin_mode);
}

/*
 * Class:     function_gpio_GPIO_Core_Jni
 * Method:    pin_read
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_function_gpio_GPIO_1Core_00024Jni_pin_1read(JNIEnv*, jclass, jint pin_number)
{
	return gpioRead(pin_number);
}

/*
 * Class:     function_gpio_GPIO_Core_Jni
 * Method:    pin_write
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_function_gpio_GPIO_1Core_00024Jni_pin_1write(JNIEnv*, jclass, jint pin_number, jint value)
{
	gpioWrite(pin_number, value);
}
