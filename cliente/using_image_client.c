#include "client_image_sender.h"
#include <stdio.h>
//compile with: gcc -o using_image_client using_image_client.c client_image_sender.c -pthread
// ./client <ip> <puerto> <imagen> <hilos> <ciclos> <server>
// ./using_image_client 192.168.0.9 8081 brain_492.pgm 1 3
int main(int argc, char *argv[]){
    if (argc < 6)
    {
        printf("Por favor, ingrese los parámetros <ip> <puerto> <imagen> <hilos> <ciclos> <server>\n");
    }else
    {
        take_send_image(argv[1],  argv[2], argv[3], argv[4], argv[5], argv[6]);
    }
    
    
    
    return 0;
}
