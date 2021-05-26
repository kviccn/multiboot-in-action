#ifndef __MMU_H_
#define __MMU_H_

#include "types.h"

// 段选择子
#define SEG_KCODE 1 // 内核代码段
#define SEG_KDATA 2 // 内核数据和堆栈段
#define SEG_UCODE 3 // 用户代码段
#define SEG_UDATA 4 // 用户数据和堆栈段
#define SEG_TSS 5   // 任务状态段

// 段数量
#define NSEGS 6

struct segdesc
{
  uint32_t lim_15_0 : 16;  // 段界限 0~15 位
  uint32_t base_15_0 : 16; // 段基址 0~15 位
  uint32_t base_23_16 : 8; // 段基址 16~23 位
  uint32_t type : 4;       // 段类型
  uint32_t s : 1;          // 0 = 系统段，1 = 应用段
  uint32_t dpl : 2;        // 描述符特权级
  uint32_t p : 1;          // 存在位
  uint32_t lim_19_16 : 4;  // 段界限 16~19 位
  uint32_t avl : 1;        // 可供操作系统使用
  uint32_t rsv1 : 1;       // 保留
  uint32_t db : 1;         // 0 = 16位段，1 = 32位段
  uint32_t g : 1;          // 粒度，置位时 limit 单位为 4K
  uint32_t base_31_24 : 8; // 段基址 24~32 位
};

// 简化段设置的宏
#define SEG(type, base, lim, dpl)                                 \
  (struct segdesc)                                                \
  {                                                               \
    ((lim) >> 12) & 0xffff, (uint32_t)(base)&0xffff,              \
        ((uint32_t)(base) >> 16) & 0xff, type, 1, dpl, 1,         \
        (uint32_t)(lim) >> 28, 0, 0, 1, 1, (uint32_t)(base) >> 24 \
  }

#define DPL_USER 0x3 // user 描述符特权级

// 应用段类型位
#define STA_X 0x8 // 可执行
#define STA_W 0x2 // 可写，不可执行
#define STA_R 0x2 // 可读段，可执行

#endif
