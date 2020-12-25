#include "stdio.h"
#include "libgohooks.h"
#include "loadsym.h"
#include <dlfcn.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#define INIT() init_lib_wrapper(__FUNCTION__)

#define SETUP_SYM(X)                                                           \
  do {                                                                         \
    if (!pointer_##X)                                                             \
      pointer_##X = load_sym(#X);                                              \
  } while (0)


pthread_once_t init_once = PTHREAD_ONCE_INIT;
static void setup_hooks(void);

static void do_init(void) {

  srand(time(NULL));
  setup_hooks();
}


void init_lib_wrapper(const char *caller) {
#ifndef DEBUG
  (void)caller;
#endif
  // if(!init_l) PDEBUG("%s called from %s\n", __FUNCTION__,  caller);
  pthread_once(&init_once, do_init);
}

void *load_sym(char *symname) {
    void *funcptr = dlsym(RTLD_NEXT, symname);

  if (!funcptr) {
    fprintf(stderr, "Cannot load symbol '%s' %s\n", symname, dlerror());
    exit(1);
  } else {
    fprintf(stderr,
            "loaded symbol '%s'"
            " real addr %p \n ",
            symname, funcptr);
  }
  return funcptr;
}





static void setup_hooks(void) {
  SETUP_SYM(sendto);
  SETUP_SYM(write);
  SETUP_SYM(send);
  SETUP_SYM(write);
  SETUP_SYM(read);
  SETUP_SYM(socket);
}

//wrap for sendto
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen) {
  INIT();
  fprintf(stdout, "hello world\n");
  return 0;
}
ssize_t true_sendto(int sockfd, const void *buf, size_t len, int flags,
                            const struct sockaddr *dest_addr,
                            socklen_t addrlen){
    return pointer_sendto(sockfd,buf,len,flags,dest_addr,addrlen);
}


int true_socket(int domain, int type, int protocol){
    return pointer_socket(domain,type,protocol);
}



//wrap for write
ssize_t write(int fd, const void *buf, size_t count) {
  return go_write(fd,(void *)buf,count);
}
ssize_t true_write(int fd, const void *buf, size_t count){
    return pointer_write(fd,buf,count);
}

//wrap for send
ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
  INIT();
  fprintf(stdout, "len:%ld content:%s\n", len, (char *)buf);
  return true_send(sockfd, buf, len, flags);
}
ssize_t true_send(int sockfd, const void *buf, size_t len, int flags){
    return pointer_send(sockfd,buf,len,flags);
}

ssize_t true_read(int fd, void *buf, size_t count){
    return pointer_read(fd,buf,count);
}


