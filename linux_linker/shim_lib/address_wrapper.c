#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define LIBC_PATH ("/lib/x86_64-linux-gnu/libc-2.19.so")
#define LOG_PATH ("/tmp/addr_shim.log")

typedef int (*addrinfo_f)(const char*, const char*, const struct addrinfo*, struct addrinfo**);

addrinfo_f initialize_lib()
{
  static addrinfo_f lib_addrinfo = NULL;
  static void* stdlib_handle = NULL;
  if(NULL != lib_addrinfo || NULL != stdlib_handle) {
    return lib_addrinfo;
  }

  stdlib_handle = dlopen(LIBC_PATH, RTLD_LAZY);
  if(NULL == stdlib_handle) {
    fprintf(stderr,"Error opening the stdlib at %s: %s\n", LIBC_PATH, strerror(errno));
  }
  lib_addrinfo = (addrinfo_f)dlsym(stdlib_handle, "getaddrinfo");
  return lib_addrinfo;
}

FILE* get_logfile()
{
  static FILE* logfile = NULL;
  if(NULL != logfile) {
    return logfile;
  }
  logfile = fopen(LOG_PATH, "w");
  if(NULL == logfile) {
    logfile = stderr;
  }
  return logfile;
}

int getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo **res)
{
  addrinfo_f lib_addrinfo = initialize_lib();
  FILE* logfile = get_logfile();
  fprintf(logfile, "Performing a lookup for: %s (service: %s)\n", node ? node : "<NULL>", service ? service : "<NULL>");
  return lib_addrinfo(node, service, hints, res);
}
