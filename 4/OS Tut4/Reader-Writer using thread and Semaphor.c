#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int hr,min,sec,tid1,tid2;
void *read();
void *write();
void *ret;
sem_t s1,s2;
pthread_t rth,wth;

void main()
{
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	tid1 = pthread_create(&rth,NULL,&read,NULL);	
	if(tid1 == 0)
		printf("\nrth created successfully");
	tid2 = pthread_create(&wth,NULL,&write,NULL);	
	if(tid2 == 0)
		printf("\nwth created successfully");	

	pthread_join(rth,NULL);	
	pthread_join(wth,NULL);	
	sem_destroy(&s1);
	sem_destroy(&s2);

}

void *read()
{
	printf("\nin read");
	while(hr <= 1)
	{
		sem_wait(&s2);
		printf("\n%d:%d:%d",hr,min,sec);	
		sem_post(&s1);
		sleep(1);
	}	
	return(&ret);
}


void *write()
{
	printf("\nin write");
	while(hr <= 1)
	{
		sem_wait(&s1);
		sec++;
		if(sec == 60)
		{
			sec = 0;
			min++;
		}
		if(min == 60)
		{
			min = 0;
			hr++;
		}
		sem_post(&s2);
		sleep(1);
	}
	return(&ret);
}

