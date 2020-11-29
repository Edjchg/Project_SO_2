#ifndef PRE_HEAVY_SERVER_H
#define PRE_HEAVY_SERVER_H
//char *storage_directory_ = "./fifo_storage";
#include <sys/types.h>
struct pross{ 
    struct pross *next;
    char filename[256];
    pid_t pid_pross;
    int fd_client;
    int counter;
    int num_pross;
    int flag;
    int f;
}pross;

struct pross *pross_head; // Global process list

void process_image();
int init_pre_heavy_server();
void send_finish();
void handling_con();
void exec_pross();
void init_pross();
void kill_pross();
int assing_job_pross();
void* create_shared_memory();
void python_image_process(char *filename);
int check_pross();

#endif