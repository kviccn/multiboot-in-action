#define MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define MULTIBOOT_HEADER_FLAGS      0
#define MULTIBOOT_HEADER_CHECKSUM   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

#define STACK_SIZE                  0x4000  // 16KB

.section .text
.globl entry
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECKSUM

entry:
// 初始化栈指针
movl $(stack + STACK_SIZE), %esp

call kernel_main

hlt

.section .bss
.comm stack, STACK_SIZE
