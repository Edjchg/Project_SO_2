#ifndef CLIENT_IMAGE_SENDER_H
#define CLIENT_IMAGE_SENDER_H
#define PORT 8081
struct message{
	char* ip;
	char* image_name;
	int cycles;
	int port;
	int server; //1 -> fifo, 2 -> Heavy Process, 3 -> Pre Heavy Process
};
void* send_file(void* argument);
void take_send_image(char* ip, char*port, char* fname, char*threads, char*cycles, char* server);
int detect_extension_pgm(char* file);
int detectar_final(char* comando);
void init_reading(void* msg, double init_time, int threads);
void write_file(double time, int items, double cpu_usage, char fn_total_time[], char fn_average_time[], char fn_cpu_usage[]);
void write_to_fifo_statistics(double time, int items, double cpu_usage);
void write_to_hp_statistics(double time, int items, double cpu_usage);
#endif
