#if defined __linux__ || defined __linux
  #define _GNU_SOURCE // Using GNU source implementation for strerror_r
#endif

#include "syscall-errno.h"

#if defined _WIN16 || defined _WIN32 || defined _WIN64 || defined __WIN32__ || defined __TOS_WIN__ || defined __WINDOWS__
  #include <windows.h>

#else // elif defined __unix__ || defined __unix
  #include <string.h>
  #include <errno.h>

#endif

#include <strings/strings.h>

#if defined __cplusplus && __cplusplus < 201103L
  #define thread_local __thread
#endif

#if !defined __cplusplus
  #define thread_local _Thread_local
#endif


thread_local char syscall_errno_string[2048 /* _POSIX2_LINE_MAX */];


#if defined _WIN16 || defined _WIN32 || defined _WIN64 || defined __WIN32__ || defined __TOS_WIN__ || defined __WINDOWS__
const char *
syscall_getstrerrno(syscall_errno_t error) {
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), syscall_errno_string, sizeof(syscall_errno_string), NULL);
  return string_tolower(syscall_errno_string);
}

syscall_errno_t
syscall_geterrno(void) {
  return GetLastError();
}

void
syscall_seterrno(syscall_errno_t error) {
  SetLastError(error);
}

#else // elif defined __unix__ || defined __unix
const char *
syscall_getstrerrno(syscall_errno_t error) {
#if defined _POSIX_C_SOURCE // Using POSIX source implementation for strerror_r
  char *string = strerror_r(error, syscall_errno_string, sizeof(syscall_errno_string));
  string_write(syscall_errno_string, string, string_length(string));
#elif defined _GNU_SOURCE // Using GNU source implementation for strerror_r
  strerror_r(error, syscall_errno_string, sizeof(syscall_errno_string));
#endif
  return string_tolower(syscall_errno_string);
}

syscall_errno_t
syscall_geterrno(void) {
  return errno;
}

void
syscall_seterrno(syscall_errno_t error) {
  errno = error;
}

#endif
