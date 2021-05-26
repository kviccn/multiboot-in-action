#ifndef __X86_H_
#define __X86_H_

#include "types.h"

static inline void lgdt(struct segdesc *p, int size)
{
  volatile uint16_t pd[3];

  pd[0] = size - 1,
  pd[1] = (uint32_t)p;
  pd[2] = (uint32_t)p >> 16;

  asm volatile("lgdt (%0)" ::"r"(pd));
}

#endif
