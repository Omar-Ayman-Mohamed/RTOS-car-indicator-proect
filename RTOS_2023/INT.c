/*
 * INT.c
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */


#include "INT.h"

void GIE()
{
    SET_BIT(SREG,I_BIT);
}
void GID()
{
	CLR_BIT(SREG,I_BIT);
}
