#ifndef __ducky_uart_h__
#define __ducky_uart_h__

#include <stdint.h>
#include <bits/mallard.h>

#ifndef __ASSEMBLER__

static inline uint8_t __uart_read_lsr(void)
{
  volatile uint8_t *__uart_lsr = (uint8_t *)(DUCKY_UART_BASE + DUCKY_UART_LSR);

  return *__uart_lsr;
}

static inline void __uart_write_thr(char c)
{
  volatile char *__uart_thr = (char *)(DUCKY_UART_BASE + DUCKY_UART_THR);

  *__uart_thr = c;
}

static inline char __uart_read_rbr()
{
  uint8_t lsr = __uart_read_lsr();

  if (!(lsr & DUCKY_UART_LSR_DATA_AVAIL))
    return 0;

  volatile char *__uart_rbr = (char *)(DUCKY_UART_BASE + DUCKY_UART_RBR);

  return *__uart_rbr;
}

static inline void __uart_write_lcr(int data_length, int stop, int parity, int break_enabled)
{
  static volatile char *__uart_lcr = (char *)(DUCKY_UART_BASE + DUCKY_UART_LCR);

  char b = 0x00;

  switch(data_length) {
    case 5:
      break;
    case 6:
      b |= 0x01;
      break;
    case 7:
      b |= 0x02;
      break;
    case 8:
      b |= 0x03;
      break;
  }

  if (stop)
    b |= 0x04;

  b |= 0x00;

  *__uart_lcr = b;
}

static inline void __uart_write_mcr(int dtr, int rts)
{
  static volatile char *__uart_mcr = (char *)(DUCKY_UART_BASE + DUCKY_UART_MCR);

  char b = 0x00;

  if (dtr)
    b |= 0x01;

  if (rts)
    b |= 0x02;

  *__uart_mcr = b;
}

static inline void __uart_write_fcr(int fifo_enabled, int trigger_level)
{
  static volatile char *__uart_fcr = (char *)(DUCKY_UART_BASE + DUCKY_UART_FCR);

  char b = 0x00;

  if (fifo_enabled)
    b |= 0x01;

  switch(trigger_level) {
    case 1:
      break;
    case 4:
      b |= 0x40;
      break;
    case 8:
      b |= 0x80;
      break;
    case 14:
      b |= 0xC0;
      break;
  }

  *__uart_fcr = b;
}

#endif  // ifndef __ASSEMBLER__

#endif  // ifndef __ducky_uart_h__
