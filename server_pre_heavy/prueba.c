

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>   

struct pross{
    struct pross *next;
    int pid_pross;
    int fd_client;
    int flag;
    int exec;
    int f;
}pross;



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

struct pross *pross_head;

void exec_pross(struct pross *p1){
    while (1)
    {
        if (p1->f == 1)
        {
            return;
        }
        if(p1->flag == 1){
            printf("Ejecucion %d\n", p1->pid_pross);
            sleep(1);
            p1->flag = 0;
            p1->exec = 0;
        }
        else
        {
           // printf("Child :%d\n",p1->pid_pross);
        }
        sleep(1);
    }
}

void init_pross(int num_pross){
    for (size_t i = 0; i < num_pross; i++)
    {   
        struct pross *p1 = (struct pross *) create_shared_memory(sizeof(pross));
        p1->flag = 0;
        p1->f = 0;  
        p1->exec = 0; 
        p1->next = pross_head;
        pross_head = p1;
        int pid_t = fork();
        if ((pid_t == 0))
        {
            p1->pid_pross = getpid();
            printf("Creation process %d\n", (*p1).pid_pross);
            exec_pross(p1);
            return;
        }   
    }
    return;
}
int main(int agrc, char **argv){
    int parent_id = getpid();
    int num_p = atoi(argv[1]);
    pross_head = NULL;
    printf("Num process = %d \n", num_p);
    init_pross(num_p);
    if (getpid() == parent_id)
    {
        sleep(5);
        struct pross *temp;
        temp = pross_head;
        while (temp != NULL)       
        {
            if (temp->exec == 0)
            {
                printf("Process child id: %d start \n", temp->pid_pross);
                temp->flag = 1;
                temp->exec = 1;
                temp = temp->next;
            }            
            else
            {
                printf("Process child id: %d busy \n", temp->pid_pross);
            }
        }
        temp = pross_head;
        while (temp != NULL)       
        {
            if (temp->exec == 0)
            {
                printf("Process child id: %d start \n", temp->pid_pross);
                temp->flag = 1;
                temp = temp->next;
            }
            else
            {
                printf("Process child id: %d busy \n", temp->pid_pross);
                temp = temp->next;
            }
            
        }
        sleep(2);
        temp = pross_head;
        while (temp != NULL)       
        {
            temp->f =1;
            printf("Process child id: %d  stop\n", temp->pid_pross);
            temp = temp->next;
        }
    }
    
}