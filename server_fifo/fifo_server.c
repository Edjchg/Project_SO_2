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
#define PORT 8111
char storage_directory_[] = "../fifo_storage/";
int init_fifo_server(void){
    int fd =0, confd = 0,b,tot;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client;
    memset(&client, '0', sizeof(client));
    char str[100];
    int len = sizeof(client);
    char buff[1025];
    int num;
    char filename[100];
    int valor_predominante = 0;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("=> Socket creado\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));
    memset(filename, '0', sizeof(filename));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(fd, 1000000);
    int counter = 0;
    //confd = accept(fd, (struct sockaddr*)&client, &len);
    printf("hola");
    while (1)
    {
        confd = accept(fd, (struct sockaddr*)&client, &len);
        printf("\n=> El IP del cliente es: %s\n", inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)));
        printf("=> EL id del cliente es: %i\n", confd);
        //strcat();
        //memset(buff, '0', sizeof(buff));

        read(confd, filename, 256);
        if (strcmp(filename, "final") == 0)
        {
            char time[100];
            clock_t b_time;
	        b_time = clock();
            sprintf(time, "%ld", b_time);
            write(confd, time, 100);
            //write(confd, "Hola", 4);
            break;
        }
        printf("Fname: %s\n", filename);
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
        tot = 0;
        memset(buff, '0', sizeof(buff));
        FILE* fp = fopen(storage_directory_, "wb");
        if (fp != NULL)
        {
            while((b = recv(confd, buff, 1024,0))> 0 ) {
		            tot+=b;
                    fwrite(buff, 1, b, fp);
		    }
            printf("=> Su peso es de: %d bytes.\n",tot);
		    if (b<0)
		        perror("Receiving");
		    
            //tot = 0;
            //strcat(storage_directory_, filename);
            process_image(storage_directory_, counter);
            //strcpy(filename, " ");
            //memset(buff, '0', sizeof(buff));
            fclose(fp);
            fp = NULL;
            strcpy(storage_directory_, "../fifo_storage/");
        }
        strcpy(storage_directory_, "../fifo_storage/");
        memset(filename, 0, sizeof(filename));
        //fclose(fp);
        printf("Uno más\n");
        counter++;
    }
    
}
void process_image(char file_name[], int index){
    //Use sobel function...
    apply_sobel(file_name, index);
    printf("Processing the image %s with sobel algorithm\n", file_name);
}
void send_finish(void){

}
