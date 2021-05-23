#include "types.h"

#define COLUMNS 80
#define ROWS 25
#define VIDEO 0xB8000

static uint16_t *video_buffer = (uint16_t *)VIDEO;
static uint32_t pos = 0;

static void consputc(int c);

static void printint(int xx, int base, int sign)
{
  static char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  unsigned int x;

  if (sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do
  {
    buf[i++] = digits[x % base];
  } while ((x /= base) != 0);

  if (sign)
    buf[i++] = '-';

  while (--i >= 0)
    consputc(buf[i]);
}

void cls()
{
  for (int i = 0; i < COLUMNS * ROWS; i++)
  {
    video_buffer[i] = ' ' | video_buffer[i] & 0xff00;
  }
}

void cprintf(const char *fmt, ...)
{
  uint32_t *argp;
  char *s;
  int c;

  argp = (uint32_t *)(&fmt + 1);

  for (int i = 0; (c = fmt[i] & 0xff) != 0; i++)
  {
    if (c != '%')
    {
      consputc(c);
      continue;
    }

    c = fmt[++i] & 0xff;

    if (c == 0)
      break;

    switch (c)
    {
    case 'd':
      printint(*argp++, 10, 1);
      break;
    case 'x':
    case 'p':
      printint(*argp++, 16, 0);
      break;
    case 's':
      if ((s = (char *)*argp++) == 0)
        s = "(null)";
      for (; *s; s++)
        consputc(*s);
      break;
    case '%':
      consputc('%');
      break;
    default:
      consputc('%');
      consputc(c);
      break;
    }
  }
}

void consputc(int c)
{
  if (c == '\n')
    pos += COLUMNS - pos % COLUMNS;
  else if (c == '\b')
  {
    if (pos > 0)
      --pos;
  }
  else
    video_buffer[pos++] = (c & 0xff) | 0x0f00;

  if (pos >= COLUMNS * ROWS)
  {
    for (int i = 0; i < COLUMNS * (ROWS - 1); i++)
      video_buffer[i] = video_buffer[i + COLUMNS];
    for (int i = COLUMNS * (ROWS - 1); i < COLUMNS * ROWS; i++)
      video_buffer[i] = ' ' | 0x0f00;
    pos -= COLUMNS;
  }
}
