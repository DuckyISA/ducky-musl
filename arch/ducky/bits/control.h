#ifndef __ducky_control_h__
#define __ducky_control_h__

/*
 * Control Coprocessors defines
 */

#define CONTROL_REG_CPUID       r0
#define CONTROL_REG_EVT         r1
#define CONTROL_REG_PT          r2
#define CONTROL_REG_FLAGS       r3

#define CONTROL_FLAG_PT_ENABLED 0x00000001
#define CONTROL_FLAG_JIT        0x00000002
#define CONTROL_FLAG_VMDEBUG    0x00000004

#endif // !__ducky_control_h__
