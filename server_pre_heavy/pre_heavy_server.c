#include "../sobel/sobel.h"
#include "pre_heavy_server.h"
#include "fd_shared.h"
#include <sys/socket.h>
#include <sys/wait.h>
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
#include <sys/mman.h> 
#define MAXCHAR 1000
#define PORT 8116

/**
 * Funcion principal. Inicio de procesos hijos, el servidor y ciclo del 
 *  procesos padre para atender y assignar las peticiones del cliente.
 * 
 * int num_p: Numero de procesos hijos que se deben crear.
 * */
int init_pre_heavy_server(int num_p)
{
    int pid_father = getpid();
    printf("%d \n", pid_father);
    int fd =0, confd = 0;
    struct sockaddr_in serv_addr;    
    struct sockaddr_in client;
    memset(&client, '0', sizeof(client));
    char str[100];
    int len = sizeof(client);
    int num;
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0){
        perror("Socket creation fail");
        return  0;
    }
    printf("=> Socket creado\n");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    if(bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Binding fail");
        close(fd);
        return 0;
    };
    listen(fd, 1000000);

    int counter = 0;
    printf("Listening..\n");
    
    pross_head = NULL;
    int num_s = 0;
    configure_socket_pair();
    init_pross(num_p);  
    while (1)
    {
        if (getpid() == pid_father)
        {  
            confd = accept(fd, (struct sockaddr*)&client, &len);
            //printf("\n=> El IP del cliente es: %s\n", inet_ntop(AF_INET, &client.sin_addr, str, sizeof(str)));
            //printf("=> EL id del cliente es: %i\n", confd);
            char filename[256];
            memset(filename, 0, sizeof(filename));
            read(confd, filename, 256);
            if (strcmp(filename, "final") == 0)
            {
                char time[100];
                clock_t b_time;
                b_time = clock();
                sprintf(time, "%ld", b_time);
                write(confd, time, 100);
                while (check_pross() == -1){}
                close(fd);
                kill_pross();
                break;
            }
            else
            {
                printf("Solicitud # %d \n", num_s);
                if (counter == 100)
                {
                    counter = 0;
                }
                user_send(confd); 
                while (assing_job_pross(filename, counter) == -1){}
                counter++;
                num_s++;
            }
        }
        else
        {
            return 0;
        }
    }    
}

/**
 * Verifica si algun proceso se esta ejecutando.
 * Si se estan ejecutan devuelve -1 de lo contrario un 0.
 * */
int check_pross()
{
    struct pross *temp;
    temp = pross_head;
    while (temp != NULL)       
    {
        if (temp->flag == 1)
        {
            return -1;
        }            
        temp = temp->next;
    }
    return 0;
} 

/**
 * Se encarga de ejecutar el script de python que 
 * aplica el filtro.
 * 
 * char *filename: ruta y nombre de la imagen 
*/
void python_image_process(char *filename)
{
    char cmd[200];
    strcpy(cmd, "python3 ../python_sobel/python_sobel.py ");
    int x = system(strcat(cmd, filename));
}

/**
 * Funcion utilizada por los hijos para recibir la imagen 
 * y ejecutar la aplicacion del filtro.
 * */
void handling_con(int confd, int counter, char *filename)
{
    char storage_directory_[256] = "../pre_heavy_storage/";
    int flag = 1, tot, b;
    if (flag == 1)
    {
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
        char buff[1025];
        memset(buff, 0, sizeof(buff));
        FILE* fp = fopen(storage_directory_, "wb");
        if (fp != NULL)
        {
            while((b = recv(confd, buff, 1024,0))> 0 ) {
                    tot+=b;
                    fwrite(buff, 1, b, fp);
            }
            if (b<0){
                perror("Receiving");
            }            
            fclose(fp);
            python_image_process(storage_directory_);
            fp = NULL;
            strcpy(storage_directory_, "../pre_heavy_storage/");
        }
        strcpy(storage_directory_, "../pre_heavy_storage/");
    }
    memset(filename, 0, sizeof(filename));
}


/**
 * Inicia los procesos hijos y los agrega a la lista 
 * para el control del proceso padre.
 * */
void init_pross(int num_pross)
{
    for (size_t i = 0; i < num_pross; i++)
    {   
        struct pross *p1 = (struct pross *) create_shared_memory(sizeof(pross));
        p1->num_pross = (int) i+1;
        p1->flag = 0; 
        p1->f = 0; 
        p1->next = pross_head;
        pross_head = p1;
        int pid_t = fork();
        if ((pid_t == 0))
        {
            p1->pid_pross = getpid();
            printf("Proceso creado! ID: %d\n", (*p1).pid_pross);
            exec_pross(p1);
            return;
        }   
    }
    return;
}

/**
 * Ciclo de los procesos para esperar la assignacion de 
 * tareas.
 * 
 * struct pross *p1: procesos hijo a ejecutar el ciclo. 
 * */
void exec_pross(struct pross *p1)
{
    while (1)
    {
        p1->flag = 0;
        kill(p1->pid_pross, SIGSTOP);
        if (p1->f == 1)
        {
            p1->flag = 0;
            printf("Dying ID: %d \n", p1->pid_pross);
            return;
        }
        p1->fd_client = user_receive();
        handling_con(p1->fd_client, p1->counter, p1->filename);  
    }
}
/**
 * Manda la senal para que los procesos hijos se terminen.
 * */
void kill_pross()
{
    struct pross *temp;
    temp = pross_head;
    while (temp != NULL)       
    {
        temp->f = 1;
        printf("Parando el proceso! ID: %d \n", temp->pid_pross);
        kill(temp->pid_pross, SIGCONT);
        temp = temp->next;
    }
}
/**
 * Funcion utilizada por el padre para assignar trabajos a los 
 * hijos cuando esten disponibles.
 * 
 * char *filename: Nombre de la imagen.
 * int counter: Numero de imgenes que se han recibido.
 * */
int assing_job_pross(char *filename, int counter)
{
    struct pross *temp;
    temp = pross_head;
    while (temp != NULL)       
    {
        if (temp->flag == 0)
        {
            int status;
            waitpid(temp->pid_pross, &status, WUNTRACED);
            strcpy(temp->filename, filename);
            temp->counter = counter;
            temp->flag = 1;
            kill(temp->pid_pross, SIGCONT);
            return 0;
        }            
        else
        {
            temp = temp->next;
        }
    }
    return -1;
}

/**
 * https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
 * */
void* create_shared_memory(size_t size) {
  // Our memory buffer will be readable and writable:
  int protection = PROT_READ | PROT_WRITE;

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_SHARED | MAP_ANONYMOUS;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, -1, 0);
}
