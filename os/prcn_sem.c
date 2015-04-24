#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
int t1,t2;
pthread_t pth,cth;
sem_t s1,s2;
char a[20],b[20],c[20];
void *s;
void *producer();
void *consumer();

void main()
{
    sem_init(&s1,0,0);
    sem_init(&s2,0,1);
    t1=pthread_create(&pth,NULL,&producer,NULL);
    t2=pthread_create(&cth,NULL,&consumer,NULL);
    if(t1==0)
         printf("\nYes created producer");
    else
         printf("\nDint create producer");
    if(t2==0)
         printf("\nYes created consumer");
    else
         printf("\nDint create consumer");      
    pthread_join(pth,&s);
    pthread_join(cth,&s);  
}
void *producer()
{
    while(1)
    {
        printf("\nEnter a string for producer");
        scanf("%s",a);
        sem_wait(&s2);
        strcpy(b,a);
        sem_post(&s1);
        sleep(1);
    }
    pthread_exit(&s);
}
void *consumer()
{
    while(1)
    {
       
        sem_wait(&s1);
        strcpy(c,b);
        sem_post(&s2);
        printf("\nThe string consumed by the consumer is: %s",c);
        sleep(1);

    }
    pthread_exit(&s);
}        
   
  
    

