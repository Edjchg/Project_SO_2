#ifndef FIFO_SERVER_H
#define FIFO_SERVER_H
//char *storage_directory_ = "./fifo_storage";
void process_image(char* file_name, int index);
int init_fifo_server(void);
void send_finish(void);
#endif