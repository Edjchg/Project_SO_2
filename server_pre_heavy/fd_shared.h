#ifndef FD_SHARED_H
#define FD_SHARED_H


int sv[2];

int configure_socket_pair();
void send_fd();
int receive_fd(); 
void user_send();
int user_receive(); 

#endif