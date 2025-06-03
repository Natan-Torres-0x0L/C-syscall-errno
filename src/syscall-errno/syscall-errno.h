#ifndef _ERRORS_ERRORS_H
#define _ERRORS_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#if defined _WIN16 || defined _WIN32 || defined _WIN64 || defined __WIN32__ || defined __TOS_WIN__ || defined __WINDOWS__
typedef /* DWORD */ uint32_t syscall_errno_t;

#else // elif defined __unix__ || defined __unix
typedef int syscall_errno_t;

#endif


extern const char *syscall_getstrerrno(syscall_errno_t);
extern syscall_errno_t syscall_geterrno(void);
extern void syscall_seterrno(syscall_errno_t);

#ifdef __cplusplus
}
#endif

#endif
