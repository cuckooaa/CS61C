#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t bit0,bit2,bit3,bit5,temp;
    bit0=*reg & 1;
    bit2=*reg>>2 & 1;
    bit3=*reg>>3 & 1;
    bit5=*reg>>5 & 1;
    temp=(bit5^(bit3^(bit2^bit0)));
    *reg=*reg>>1;
    if(temp==0) *reg &= ~(1<<15);
    else *reg |= 1<<15;
}

