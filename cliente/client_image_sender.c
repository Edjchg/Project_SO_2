#include "client_image_sender.h"
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>
#define NANO2SEC 1000000000
// ./client <ip> <puerto> <imagen> <hilos> <ciclos> <server>


void take_send_image(char* ip,  char*port, char* fname, char*threads, char*cycles, char* server){
	//char fname[100];
	//Converting the arguments to integers:
	int valido = 0;
	int final = 0;
	int port_ = atoi(port);
	int threads_ = atoi(threads);
	int cycles_ = atoi(cycles);
	int server_ = atoi(server);
	int index = 0;
	//Building the struct of the message:
	struct message new_message;
	new_message.cycles = cycles_;
	new_message.image_name = fname;
	new_message.ip = ip;
	new_message.port = port_;
	new_message.server = server_;
	//while(1){
	//Creating the threads:
	pthread_t threads_list[threads_];
	void * retvals[threads_];
	int valid_extension = detect_extension_pgm(fname);
	clock_t b_time;
	b_time = clock();
	if (valid_extension)
		
		{
		//send_file(&new_message);
		pthread_t cpu_used;
		flag_cpuc = 1;
		pthread_create(&cpu_used, NULL, &get_cpu_counter, NULL);
		for (int i = 0; i < threads_; ++i){
			if (pthread_create(&threads_list[i], NULL, send_file, &new_message) != 0){
				printf("\033[1;31mERROR: Can not create %i thread \033[0m;\n", i);
				break;
			}
			//sleep(1);
			
		}
		for (int n = 0; n < threads_; n++){
			if (pthread_join(threads_list[n], &retvals[n]) != 0)
			{
				printf("\033[1;31mERROR: Can not join %i thread \033[0m;\n", n);
				break;
			}
		}
	}else
	{
		printf("\033[1;31mThis is not a valid extension file \033[0m;\n");
	}
	init_reading(&new_message, (double)b_time, threads_);
}
//######################################################################################################################################
/*######################################################################################################################################
La funcion detect_extension_pgm recibe como parámetro el nombre de un archivo, esta función determina si el archivo es una imagen de tipo .png, si es así retorna TRUE, de lo contrario retorna un FALSE.
*/
int detect_extension_pgm(char *file){
	int size_string = strlen(file) - 1;
	char buffer[] = "   ";
	int index = 0;
	int index_buffer = 0;
	while (index <= size_string){
		
		if(file[index] == 46 | index_buffer > 0){
			//printf("Se detecto un punto\n");
			buffer[index_buffer] = file[index];
			index++;
			index_buffer++;
		}else{
			++index;
		}
	}
	printf("La extension del archivo es: %s\n", buffer);
	if(strcmp(buffer,".png") == 0){
		return 1;
	}else{
		return 0;
	}
}
/*######################################################################################################################################
La función enviar_archivo recibe como parámetro: ip -> Que es el ip del servidor, el nombre del archivo a enviar.
Lee el archivo de la carpeta donde se encuentra, divide al archivo en chunks de información que envia por medio de socket al servidor.
*/
//int send_file(char* ip, char* file_name, int cycles){
void*  send_file (void* argument){
	//Casting the argument to the struct
	struct message *new_message = (struct message *)argument;
	printf("Nuevo mensaje de un archivo %s con el ip %s y un numero de ciclos de %i\n", new_message->image_name, new_message->ip, new_message->cycles);
	int sfd =0, n=0, b;
	char rbuff[1024];
	char sendbuffer[100];
	struct sockaddr_in serv_addr;
	memset(rbuff, '0', sizeof(rbuff));
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(new_message->port);
	serv_addr.sin_addr.s_addr = inet_addr(new_message->ip);
	FILE *fp;

	int index = 0;
	while(index < new_message->cycles){
		sfd = socket(AF_INET, SOCK_STREAM, 0);
		b=connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if (b==-1) {
			perror("Connect");
			exit(1);
		}
		fp = fopen(new_message->image_name, "rb");
		
		write(sfd, new_message->image_name, 256);
		
		if(fp == NULL){
	    	perror("File");
	    	exit(2);
		}
		while( (b = fread(sendbuffer, 1, sizeof(sendbuffer), fp))>0 ){
			send(sfd, sendbuffer, b, 0);
		}
		//strcpy(sendbuffer, " ");
		memset(sendbuffer, 0, sizeof(sendbuffer));
		index++;
		fclose(fp);
		fp = NULL;
		close(sfd);
		sfd = 0;
		b = 0;

	}
	
}
void init_reading(void* msg, double init_time, int threads){
	struct message *new_message = (struct message *)msg;
	int sfd =0, n=0, b;
	char rbuff[1024];
	char sendbuffer[100];
	struct sockaddr_in serv_addr;

	memset(rbuff, '0', sizeof(rbuff));
	sfd = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_port = htons(5000);
	serv_addr.sin_port = htons(new_message->port);
	//serv_addr.sin_addr.s_addr = inet_addr("192.168.1.8");
	serv_addr.sin_addr.s_addr = inet_addr(new_message->ip);

	b=connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (b==-1) {
		perror("Connect");
		exit(1);
	}
	send(sfd, "final\n", 5, 0);
	long time_;
	if(read(sfd, sendbuffer, 256) != -1){
		//printf("%s\n", sendbuffer);
		time_ = atol(sendbuffer);
	}
	flag_cpuc = 0;	
	result_cpuc =  result_cpuc/counter_cpu;
	printf("Result cpu: %Lf \n",result_cpuc);

	printf("%ld\n", clock());
	printf("\033[1;31m El programa duró %ld, con %i elementos y un %Lf de CPU.\033[0m; \n", time_, new_message->cycles*threads, result_cpuc);
	// Writing the statistics for the servers
	if (new_message->server == 1){
		write_to_fifo_statistics(time_, new_message->cycles*threads, result_cpuc);
	}
	else if(new_message->server == 2){
		write_to_hp_statistics(time_, new_message->cycles*threads, result_cpuc);
	}
	else if(new_message->server == 3){
		write_to_php_statistics(time_, new_message->cycles*threads, result_cpuc);
	}
}

void write_file(long time, int items, double cpu_usage, char fn_total_time[], char fn_average_time[], char fn_cpu_usage[]){
	char time_[50];
	sprintf(time_, "%ld", time);
	char items_[50];
	sprintf(items_, "%d", items);

	// Opening file for reading and writing:
	FILE* fp_total_time = fopen(fn_total_time, "r+");
	char buffer1[1000000];
	memset(buffer1, 0, sizeof(buffer1));
	fscanf(fp_total_time, "%s", buffer1);
	char pair[50];
	memset(pair, 0, sizeof(pair));
	strcat(pair, "[");
	strcat(pair, time_);
	strcat(pair, ",");
	strcat(pair, items_);
	strcat(pair, "]");
	strcat(buffer1, pair);
	fprintf(fp_total_time, "%s", pair);
	fclose(fp_total_time);


	double average = (double)time/items;
	char average_time[50];
	sprintf(average_time, "%f", average);
	FILE* fp_average_time = fopen(fn_average_time, "r+");
	char buffer2[1000000];
	memset(buffer2, 0, sizeof(buffer2));
	fscanf(fp_average_time, "%s", buffer2);
	char pair2[50];
	memset(pair2, 0, sizeof(pair2));
	strcat(pair2, "[");
	strcat(pair2, average_time);
	strcat(pair2, ",");
	strcat(pair2, items_);
	strcat(pair2, "]");
	strcat(buffer2, pair2);
	fprintf(fp_average_time, "%s", pair2);
	fclose(fp_average_time);

	char cpu_usage_[50];
	sprintf(cpu_usage_, "%f", cpu_usage);
	FILE * fp_cpu_usage = fopen(fn_cpu_usage, "r+");
	char buffer3[1000000];
	memset(buffer3, 0, sizeof(buffer3));
	fscanf(fp_cpu_usage, "%s", buffer3);
	char pair3[50];
	memset(pair3, 0, sizeof(pair3));
	strcat(pair3, "[");
	strcat(pair3, items_);
	strcat(pair3, ",");
	strcat(pair3, cpu_usage_);
	strcat(pair3, "]");
	fprintf(fp_cpu_usage, "%s", pair3);
	fclose(fp_cpu_usage);
}

void write_to_fifo_statistics(long time, int items, double cpu_usage){
	char *fn_total_time = "fifo_statistics/fifo_total_time.txt";
	char *fn_average_time = "fifo_statistics/fifo_average_time.txt";
	char *fn_cpu_usage = "fifo_statistics/fifo_cpu_usage.txt";
	write_file(time, items, cpu_usage, fn_total_time, fn_average_time, fn_cpu_usage);
}

void write_to_hp_statistics(long time, int items, double cpu_usage){
	char *fn_total_time = "hp_statistics/hp_total_time.txt";
	char *fn_average_time = "hp_statistics/hp_average_time.txt";
	char *fn_cpu_usage = "hp_statistics/hp_cpu_usage.txt";
	write_file(time, items, cpu_usage, fn_total_time, fn_average_time, fn_cpu_usage);
}

void write_to_php_statistics(long time, int items, double cpu_usage){
	char *fn_total_time = "php_statistics/php_total_time.txt";
	char *fn_average_time = "php_statistics/php_average_time.txt";
	char *fn_cpu_usage = "php_statistics/php_cpu_usage.txt";
	write_file(time, items, cpu_usage, fn_total_time, fn_average_time, fn_cpu_usage);
}

void *get_cpu_counter(void *arg)
{
    long double a[4], b[4], loadavg;
    FILE *fp;
    char dump[50];

    while (flag_cpuc == 1)	
    {
        fp = fopen("/proc/loadavg","r");
		fscanf(fp, "%*s %Lf", &a[0]);
        fclose(fp);
        sleep(1);
		double y = a[0]*100;
		double proc_n = sysconf(_SC_NPROCESSORS_ONLN);
		y = y / proc_n;
		counter_cpu++;
		result_cpuc += y;
    }
}
