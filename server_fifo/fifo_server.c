#include "../sobel/sobel.h"
#include "fifo_server.h"
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
#define MAXCHAR 1000
#define PORT 8108
char storage_directory_[] = "../fifo_storage/";
int init_fifo_server(void){
    int fd =0, confd = 0,b,tot;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client;
    char str[100];
    int len = sizeof(client);
    char buff[1000000];
    int num;
    char filename[100];
    fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("=> Socket creado\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    FILE* fp;
    if (bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))){
        perror("Binding fail");
        close(fd);
        return 0;
    };
    listen(fd, 1000000);
    time_t begin, end;
    time(&begin);
    int counter = 0;
    char time_[100];
    while (1)
    {
        confd = accept(fd, (struct sockaddr*)&client, &len);
        //printf("\n=> El IP del cliente es: %s\n", inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)));
        //printf("=> EL id del cliente es: %i\n", confd);

        read(confd, filename, 256);
        if (strcmp(filename, "final") == 0)
        {
            /*clock_t b_time;
            b_time = clock();
            sprintf(time, "%ld", b_time);
            write(confd, time, 100);*/
            time(&end);
    		time_t elapsed = end - begin;
    		printf("Time measured: %ld seconds.\n", elapsed);
    		printf("Total server timetime: %ld\n", elapsed);
    		sprintf(time_, "%ld", elapsed);
    		write(confd, time_, 100);
    		close(confd);
            close(fd);
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
        fp = fopen(storage_directory_, "wb");
        if (fp != NULL)
        {
            //while((b = recv(confd, buff, 1024,0))> 0 ) {
            while((b = recv(confd, buff, 999999,0))> 0 ) {
		            tot+=b;
                    fwrite(buff, 1, b, fp);
		    }
            //printf("=> Su peso es de: %d bytes.\n",tot);
		    if (b<0)
		        perror("Receiving");
		    
            fclose(fp);
            fp = NULL;
        }

        python_image_process(storage_directory_);
        strcpy(storage_directory_, "../fifo_storage/");
        memset(filename, 0, sizeof(filename));
        memset(str, 0, sizeof(str));
        memset(buff, 0, sizeof(buff));
        b = 0;
        tot = 0;
        printf("%i\n", counter);
        close(confd);
        confd = 0;
        counter++;
    }
    
}
void process_image(char file_name[], int index){
    //Use sobel function...
    apply_sobel(file_name, index);
}

void python_image_process(char *filename){
    char cmd[200];
    strcpy(cmd, "python3 ../python_sobel/python_sobel.py ");
    int x = system(strcat(cmd, filename));
}
 
