#include "client_image_sender.h"
#include <stdio.h>
//compile with: gcc -o using_image_client using_image_client.c client_image_sender.c -pthread
// ./client <ip> <puerto> <imagen> <hilos> <ciclos>
// ./using_image_client 192.168.0.9 8081 brain_492.pgm 1 3
int main(int argc, char *argv[]){
    take_send_image(argv[1],  argv[2], argv[3], argv[4], argv[5]);
    return 0;
}
