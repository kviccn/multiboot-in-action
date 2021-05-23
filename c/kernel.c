#include "defs.h"
#include "types.h"
#include "multiboot.h"

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

void kernel_main(multiboot_info_t *mbi, uint32_t magic)
{
  cls();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    cprintf("Invalid magic number!\n");
    return;
  }
  cprintf("Hello kernel!@%d\n", 2021);
  cprintf("mem_lower = %dKB, mem_upper = %dKB\n", mbi->mem_lower, mbi->mem_upper);

  multiboot_memory_map_t *mmap;
  cprintf("mmap_addr = 0x%x, mmap_length = 0x%x\n", mbi->mmap_addr, mbi->mmap_length);
  for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
       (unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
       mmap = (multiboot_memory_map_t *)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
  {
    cprintf(" base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
            (unsigned)(mmap->addr >> 32), (unsigned)(mmap->addr & 0xffffffff),
            (unsigned)(mmap->len >> 32), (unsigned)(mmap->len & 0xffffffff),
            (unsigned)mmap->type);
  }
}
