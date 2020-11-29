
#include <stdio.h>
#include <stdlib.h>
#include "pre_heavy_server.h"
//Copile with: gcc -o using_fifo_server fifo_server.c using_fifo_server.c

/**
 * Funcion principal para utilizar el pre-heavy server.
 * 
 * Recibe el numero de procesos hijos a crear.
 * */
int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("./<name_file> <num_process> \n");
        return 0;
    }
    int num_p = atoi(argv[1]);
    init_pre_heavy_server(num_p);
    return 0;
}
