# multiboot in action

> 原文链接 [https://www.gnu.org/software/grub/manual/multiboot/multiboot.html](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)

## 机器状态

当机器载入32位操作系统系统后，机器必须有如下状态：

- `EAX` 必须包含魔数 `0x2BADB002`，这个值表明操作系统已经被兼容 `Multiboot` 规范的 `bootloader` 加载成功

- `EBX` 必须包含由 `bootloader` 提供的 `Multiboot information` 结构的32位物理地址

- `CS` 必须是一个 `offset` 为 `0`，`limit` 为 `0xFFFFFFFF` 的32位`可读/可执行`代码段。精确值未定义

- `DS` `ES` `FS` `GS` `SS` 必须是一个 `offset` 为 `0`，`limit` 为 `0xFFFFFFFF` 的32位`可读/可写`数据段。精确值未定义

- `A20 gate` 必须开启

- `CR0` 位31 (PG) 必须清除。位0 (PE) 必须置位。其他位未定义

- `EFLAGS` 位17 (VM) 必须清除。位9 (IF) 必须清除。其他位未定义

其他寄存器和标志位均为未定义状态。包括：

- `ESP` 操作系统必须尽快创建自己的栈

- `GDTR` 即使段寄存器已经被设置为如上所述的状态，`GDTR` 依然可能是非法的，所以操作系统不能加载任何段寄存器（即使加载同样的值也不行！）除非操作系统设置了自己的 `GDT`

- `IDTR` 操作系统在设置好 `IDT` 之前必须禁用中断
