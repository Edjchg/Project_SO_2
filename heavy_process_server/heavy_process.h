#ifndef HEAVY_PROCESS_H
#define HEAVY_PROCESS_H
//char *storage_directory_ = "./fifo_storage";
void process_image(char* file_name, int index);
int init_heavy_process_server(void);
void send_finish(void);
void python_image_process(char *filename);
#endif