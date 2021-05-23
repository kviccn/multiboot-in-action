typedef unsigned short uint16_t;

void cprintf(char *str)
{
  static uint16_t *video_buffer = (uint16_t *)0xb8000;

  for (int i = 0; str[i] != '\0'; i++)
  {
    video_buffer[i] = str[i] | 0x0f00; // 黑底白字
  }
}

void kernel_main()
{
  cprintf("Hello kernel!");
}
