#include <dlfcn.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#ifndef LOADSYM_H
#define LOADSYM_H

void init_lib_wrapper(const char *caller);

//wrap for sendto
typedef ssize_t (*sendto_t)(int sockfd, const void *buf, size_t len, int flags,
                            const struct sockaddr *dest_addr,
                            socklen_t addrlen);
sendto_t pointer_sendto;
ssize_t true_sendto(int sockfd, const void *buf, size_t len, int flags,
                            const struct sockaddr *dest_addr,
                            socklen_t addrlen);
//wrap for socket
typedef int (*socket_t)(int domain, int type, int protocol);
socket_t pointer_socket;
int      true_socket(int domain, int type, int protocol);
//wrap for write
typedef ssize_t (*write_t)(int fd, const void *buf, size_t count);
write_t pointer_write;
ssize_t true_write(int fd, const void *buf, size_t count);
//wrap for send
typedef ssize_t (*send_t)(int sockfd, const void *buf, size_t len, int flags);
send_t pointer_send; 
ssize_t true_send(int sockfd, const void *buf, size_t len, int flags);
//wrap for read
typedef ssize_t (*read_t)(int fd, void *buf, size_t count);
ssize_t true_read(int fd, void *buf, size_t count);
read_t pointer_read;



#endif

