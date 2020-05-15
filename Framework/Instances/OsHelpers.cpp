/*
 * OsHelpers.cpp
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#include <Instances/OsHelpers.h>

void * operator new( size_t size )
{
    return pvPortMalloc(size);
}

void * operator new[]( size_t size )
{
    return pvPortMalloc( size );
}

void operator delete(void * ptr, unsigned int i)
{
	UNUSED(i);
  vPortFree( ptr );
}

void operator delete( void * ptr )
{
    vPortFree( ptr );
}

void operator delete [](void * ptr, unsigned int i)
{
	UNUSED(i);
  vPortFree( ptr );
}


void operator delete[]( void * ptr )
{
    vPortFree( ptr );
}
