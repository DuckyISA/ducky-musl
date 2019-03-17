#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
  __asm__ __volatile__ (
      "cas %1, %0, %2"
      : "=r"(t)
      : "r"(p), "r"(s)
      : "memory", "cc");
  return t;
}
