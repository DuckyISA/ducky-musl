#include <unistd.h>
#include <sys/uio.h>
#include <bits/errno.h>
#include <bits/uart.h>

#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) __SYSCALL_LL_E((x))

#define SYSCALL_MMAP2_UNIT 8192ULL

#ifdef __GNUC__
__attribute__((noinline,noreturn))
#endif
static void do_exit_group(int ec)
{
  __asm__(
      "hlt %0"
      :
      : "r"(ec)
      :
  );

  // the loop should be unreachable, `hlt rN` halts the CPU
  for(;;);
}

#ifdef __GNUC__
__attribute__((noinline))
#endif
static size_t do_writev(int fd, struct iovec *iov, int iovcnt)
{
  int i;
  size_t buff_len, total = 0;
  char *buff;

  if (fd != STDOUT_FILENO)
    return -ENOSYS;

  for (i = 0; i < iovcnt; i++) {
    buff = (char *)iov[i].iov_base;
    buff_len = iov[i].iov_len;

    total += buff_len;

    while(buff_len--)
      __uart_write_thr(*buff++);
  }

  return total;
}

static long __do_syscall(long n, long a, long b, long c, long d, long e, long f, long g)
{
  switch(n) {
    case __NR_exit_group:
      // should not return...
      do_exit_group((int)a);
      break;

    case __NR_ioctl:
      return 0;

    case __NR_writev:
      return do_writev((int)a, (struct iovec *)b, (int)c);
  }

  n |= 0x10000000;

  __asm__(
      "hlt %0"
      :
      : "r"(n)
      :
  );

  // unreachable but clang doesn't know...
  return -ENOSYS;
}

static long __syscall0(long n)
{
  return __do_syscall(n, -1, -1, -1, -1, -1, -1, -1);
}

static long __syscall1(long n, long a)
{
  return __do_syscall(n, a, -1, -1, -1, -1, -1, -1);
}

static long __syscall2(long n, long a, long b)
{
  return __do_syscall(n, a, b, -1, -1, -1, -1, -1);
}

static long __syscall3(long n, long a, long b, long c)
{
  return __do_syscall(n, a, b, c, -1, -1, -1, -1);
}

static long __syscall4(long n, long a, long b, long c, long d)
{
  return __do_syscall(n, a, b, c, d, -1, -1, -1);
}

static long __syscall5(long n, long a, long b, long c, long d, long e)
{
  return __do_syscall(n, a, b, c, d, e, -1, -1);
}

static long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
  return __do_syscall(n, a, b, c, d, e, f, -1);
}

static long __syscall7(long n, long a, long b, long c, long d, long e, long f, long g)
{
  return __do_syscall(n, a, b, c, d, e, f, g);
}
