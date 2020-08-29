/*
 * Error_Handler.cpp
 *
 *  Created on: 07.10.2019
 *      Author: harald
 */

#include <System/Error_Handler.h>
#include <stdint.h>
#include <stdio.h>
#include <main.h>
#include <System/swo_printf.h>


void error_handler(const char* file, uint32_t line)
{
	printf("Exception in %s, line: %ld\n", file, line);

	while (1) { }; // infinite loop
}

