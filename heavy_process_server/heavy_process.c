#include "../sobel/sobel.h"
#include "heavy_process.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <zlib.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#define MAXCHAR 1000
#define PORT 8021
char storage_directory_[] = "../heavy_process_storage/";

int init_heavy_process_server(void){
    int sockd = 0, confd = 0,b,tot;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client;
    char str[100];
    int len = sizeof(client);
    char buff[1000000];
    int num;
    char filename[100];
    sockd = socket(AF_INET, SOCK_STREAM, 0);
    printf("=> Socket creado\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    bind(sockd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockd, 1000000);
    int counter = 0;
    char time[100];
    pid_t child_pid;
    while(1){
        if((confd = accept(sockd, (struct sockaddr *) &serv_addr, (socklen_t *) &len)) < 0){
            printf("Error en la conexion\n");
        }
        read(confd, filename, 256);
        printf("%s\n", filename);
        if (strcmp(filename, "finalrga.png") == 0){
            clock_t b_time;
            b_time = clock();
            sprintf(time, "%ld", b_time);
            write(confd, time, 100);
            break;
        }
        char str[100];
        if(counter < 100){
            sprintf(str, "%d", counter);
            strcat(str, filename);
            strcat(storage_directory_, str);
        }else
        {
            sprintf(str, "%d", 99);
            strcat(str, filename);
            strcat(storage_directory_, str);
        }
        child_pid = fork();
        if(child_pid < 0){
            printf("Fork error\n");
        }
        else if(child_pid == 0){
            FILE* fp;
            fp = fopen(storage_directory_, "wb");
            if (fp != NULL){
                while((b = recv(confd, buff, 999999,0))> 0 ) {
                        tot+=b;
                        fwrite(buff, 1, b, fp);
                }
                if (b<0)
                    perror("Receiving");
                
                fclose(fp);
                fp = NULL;
            }else{
                printf("Fp es Null\n");
            }
            python_image_process(storage_directory_);
            memset(filename, 0, sizeof(filename));
            memset(str, 0, sizeof(str));
            memset(buff, 0, sizeof(buff));
            b = 0;
            tot = 0;
            printf("%i\n", counter);
            close(confd);
            confd = 0;
            exit(0);
        }
        memset(storage_directory_, 0, sizeof(storage_directory_));
        strcpy(storage_directory_, "../heavy_process_storage/");
        counter++;
    }
}

void python_image_process(char *filename){
    char cmd[200];
    strcpy(cmd, "python3 ../python_sobel/python_sobel.py ");
    int x = system(strcat(cmd, filename));
}
 
