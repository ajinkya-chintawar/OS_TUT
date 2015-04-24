#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int buffer[10],tid1,tid2,cnt = 0;
void *producer();
void *consumer();
void *ret;
sem_t s1,s2;
pthread_t pro,con;

void main()
{
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	tid1 = pthread_create(&pro,NULL,&producer,NULL);	
	if(tid1 == 0)
		printf("\nproducer created successfully");
	tid2 = pthread_create(&con,NULL,&consumer,NULL);	
	if(tid2 == 0)
		printf("\nconsumer created successfully");	

	pthread_join(pro,NULL);	
	pthread_join(con,NULL);	
	sem_destroy(&s1);
	sem_destroy(&s2);
}

void *producer()
{
	int item_produced = 0;
	printf("\nproducing..");
	while(cnt < 10)
	{
		sem_wait(&s2);
		item_produced++;
		buffer[cnt] = item_produced;
		printf("\nitem produced : %d",item_produced);	
		cnt++;
		sem_post(&s1);
		sleep(1);
	}	
	return(&ret);
}


void *consumer()
{
	int item_consumed;
	printf("\nconsuming..");
	while(cnt >= 0)
	{
		sem_wait(&s1);
		cnt--;
		item_consumed = buffer[cnt];
		printf("\nitem consumed : %d",item_consumed);	
		sem_post(&s2);
		sleep(1);
	}
	return(&ret);
}

