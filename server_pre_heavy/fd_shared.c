
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "fd_shared.h"

void send_fd(int socket, int fd)  // send fd by socket
{
    struct msghdr msg = { 0 };
    char buf[CMSG_SPACE(sizeof(fd))];
    memset(buf, '\0', sizeof(buf));
    struct iovec io = { .iov_base = "ABC", .iov_len = 3 };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    *((int *) CMSG_DATA(cmsg)) = fd;

    msg.msg_controllen = CMSG_SPACE(sizeof(fd));

    if (sendmsg(socket, &msg, 0) < 0)
      printf("Failed to send message\n");
}

int receive_fd(int socket)  // receive fd from socket
{
    struct msghdr msg = {0};

    char m_buffer[256];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    char c_buffer[256];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);

    if (recvmsg(socket, &msg, 0) < 0)
      printf("Failed to receive message\n");

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    unsigned char * data = CMSG_DATA(cmsg);
    int fd = *((int*) data);
    return fd;
}

int configure_socket_pair(){
    if(socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) != 0)
    {
        printf("Failed to create Unix-domain socket pair\n");
        return -1;
    }
    return 0;
}

void user_send(int fd){
    int sock = sv[0];
    send_fd(sock, fd);
    close(fd);
    nanosleep(&(struct timespec) {.tv_sec = 0, .tv_nsec = 5000000}, 0);
}

int user_receive() {
    int sock = sv[1];
    nanosleep(&(struct timespec) {.tv_sec = 0, .tv_nsec = 5000000}, 0);
    return receive_fd(sock);
}