#include <string.h>
#include <stdint.h>

void __init_data(void)
{
  extern char _rodata_end, _data_start, _data_end;

  uint32_t *src = (uint32_t *)&_rodata_end;
  uint32_t *dst = (uint32_t *)&_data_start;

  memcpy(dst, src, &_data_end - &_data_start);
}

__asm__(
    "  .section .rodata\n"
    "  .align 4\n"
    "  .type __stack_start, @object\n"
    "  .size __stack_start, 4\n"
    "\n"
    "__stack_start:\n"
    "  .int _stack_start\n"
    "\n"
    "  .section .text.entry, \"x\", @progbits\n"
    "\n"
    "  .section .text.entry\n"
    "  .globl " START "\n"
    "  .type " START ", @function\n"
    "  .align 4\n"
       START ":\n"
    "      la sp, __stack_start\n"
    "      lw sp, sp\n"
    "      li fp, 0x00\n"
    "\n"
    "      call __init_data\n"
    "      call " START "_c\n"
    "      call _exit\n"
    "      hlt 0x79\n"
);
