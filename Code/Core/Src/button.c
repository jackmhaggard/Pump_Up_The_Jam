/*
 * button.c
 *
 *  Created on: Apr 22, 2026
 *      Author: jackd
 */


#include "button.h"


void Polling(void){
	  if (GPIOF->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->C = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->C = 0;
	  }
	  if (GPIOF->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->Cs = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->Cs = 0;
	  }
	  if (GPIOF->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->D = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->D = 0;
	  }
	  if (GPIOE->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->Ds = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->Ds = 0;
	  }
	  if (GPIOB->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->E = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->E = 0;
	  }
	  if (GPIOG->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->F = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->F = 0;
	  }
	  if (GPIOG->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->Fs = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->Fs = 0;
	  }
	  if (GPIOD->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->G = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->G = 0;
	  }
	  if (GPIOD->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->Gs = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->Gs = 0;
	  }
	  if (GPIOD->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->A = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->A = 0;
	  }
	  if (GPIOD->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->As = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->As = 0;
	  }
	  if (GPIOC->IDR & (1 << 0)) {
	      // Logic HIGH (1)
		  Notes->B = 1;
	  } else {
	      // Logic LOW (0)
		  Notes->B = 0;
	  }
}
