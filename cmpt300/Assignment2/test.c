#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
   
    printf("\n Job %d started\n", counter);
       pthread_mutex_lock(&lock);

      counter += 1;
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d finished\n", counter);
    pthread_mutex_unlock(&lock);

    return NULL;

}

int main(void)
{
    int i = 0;
    int err;

    pthread_mutex_init(&lock, NULL);

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    pthread_mutex_destroy(&lock);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}