#ifndef CLIENT_IMAGE_SENDER_H
#define CLIENT_IMAGE_SENDER_H
#define PORT 8081
struct message{
	char* ip;
	char* image_name;
	int cycles;
	int port;
};
void* send_file(void* argument);
void take_send_image(char* ip, char*port, char* fname, char*threads, char*cycles);
int detect_extension_pgm(char* file);
int detectar_final(char* comando);
#endif
