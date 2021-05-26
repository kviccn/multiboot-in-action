#include "defs.h"
#include "types.h"
#include "multiboot.h"
#include "mmu.h"

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

extern struct segdesc gdt[NSEGS];

void kernel_main(multiboot_info_t *mbi, uint32_t magic)
{
  cls();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    cprintf("Invalid magic number!\n");
    return;
  }
  cprintf("Hello kernel!@%d\n\n", 2021);

  seginit();

  asm volatile("movw $0x10, %ax\n\t"
               "movw %ax, %es\n\t"
               "movw $0x20, %ax\n\t"
               "movw %ax, %fs\n\t");

  cprintf("GDT base: 0x%x, limit: 0x%x\n\n", (uint32_t)gdt, sizeof(gdt) - 1);

  for (struct segdesc *seg = gdt; (uint32_t)seg < (uint32_t)gdt + sizeof(gdt) - 1; seg++)
  {
    cprintf("Seg: 0x%x 0x%x", *((uint32_t *)seg + 1), *(uint32_t *)seg);
    cprintf("\noffset: %d, base=0x%x, limit=0x%x, g=%s, type=0x%x, dpl=%d, s=%s, db=%s\n\n",
            (uint32_t)seg - (uint32_t)gdt,
            seg->base_31_24 << 24 | seg->base_23_16 << 16 | seg->base_15_0,
            seg->lim_19_16 << 16 | seg->lim_15_0,
            seg->g ? "4K" : "1B",
            seg->type, seg->dpl, seg->s ? "app" : "sys",
            seg->db ? "32" : "16");
  }

  asm volatile("ljmp $0x8, $1f\n\t"
               "1: nop\n\t");
}
