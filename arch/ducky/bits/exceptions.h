#ifndef __ducky_exceptions_h__
#define __ducky_exceptions_h__

#include <stdint.h>

#define EXCEPTION_INVALID_OPCODE    0x10
#define EXCEPTION_INVALID_INST_SET  0x11
#define EXCEPTION_DIVIDE_BY_ZERO    0x12
#define EXCEPTION_UNALIGNED_ACCESS  0x13
#define EXCEPTION_PRIVILEGED_INST   0x14
#define EXCEPTION_DOUBLE_FAULT      0x15
#define EXCEPTION_MEMORY_ACCESS     0x16
#define EXCEPTION_REGISTER_ACCESS   0x17
#define EXCEPTION_INVALID_EXCEPTION 0x18
#define EXCEPTION_COPROCESSOR_ERROR 0x19

#define EXCEPTION_COUNT             0x20

#ifndef __ASSEMBLER__

typedef struct {
  uint32_t e_ip;
  uint32_t e_sp;
} evt_entry_t;

#define EVT_ENTRY(_ip, _sp) { .e_ip = (uint32_t)_ip, .e_sp = (uint32_t)_sp }

#endif // !__ASSEMBLER__

#endif // !__ducky_exceptions_h__
