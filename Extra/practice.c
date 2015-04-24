/*
#include<stdio.h>
#include<pthread.h>

int hr,min,sec,tid1,tid2;
void *read();
void *write();
void *ret;

pthread_t rth,wth;
pthread_mutex_t mu;

void main()
{
	tid1 = pthread_create(&rth,NULL,&read,NULL);
	if(tid1 == 0)
		printf("\nrth created successfully\n");
	tid2 = pthread_create(&wth,NULL,&write,NULL);
	if(tid2 == 0)
		printf("\nwth created successfully\n");
	
	pthread_mutex_init(&mu,0);
	pthread_join(rth,NULL);
	pthread_join(wth,NULL);
}

void *read()
{
	printf("\nin read");
	while(hr <= 1)
	{
		pthread_mutex_lock(&mu);
		printf("\n%d:%d:%d",hr,min,sec);
		pthread_mutex_unlock(&mu);
		sleep(1);		
	}
	return(&ret);
}

void *write()
{
	printf("\nin write");
	while(hr <= 1)
	{
		pthread_mutex_lock(&mu);
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
		pthread_mutex_unlock(&mu);
		sleep(1);
	}
	return(&ret);
}
*/

///*
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int hr,min,sec,tid1,tid2;
void *read();
void *write();
void *ret;

pthread_t rth,wth;
sem_t s1,s2;

void main()
{
	sem_init(&s1,0,1);
	sem_init(&s2,0,1);
	
	tid1 = pthread_create(&rth,NULL,&read,NULL);
	if(tid1 == 0)
		printf("\nrth created succesfully\n");

	tid2 = pthread_create(&wth,NULL,&write,NULL);
	if(tid2 == 0)
		printf("\nwth created succesfully\n");
	
	pthread_join(rth,NULL);	
	pthread_join(wth,NULL);	
	
	sem_destroy(&s1);
	sem_destroy(&s2);

}

void *read()
{
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
//*/

/*
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int tid1,tid2,produced = 0,consumed = 0,arr[5],flag = 0,i=0;

void *producer();
void *consumer();
void *ret;

pthread_t prod,cons;
sem_t s1,s2;

void main()
{
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);

	tid1 = pthread_create(&prod,NULL,&producer,NULL);
	if(tid1 == 0)
		printf("\nprod created successfully\n");	
	
	tid2 = pthread_create(&cons,NULL,&consumer,NULL);
	if(tid2 == 0)
		printf("\ncons created successfully\n");	
		
	pthread_join(prod,NULL);	
	pthread_join(cons,NULL);
	
	sem_destroy(&s1);	
	sem_destroy(&s2);	
}

void *producer()
{
	printf("\nin producer");
	while(1)
	{
		sem_wait(&s2);
		while(i<5)
		{
			produced++;
			arr[i] = produced;		
			printf("\nitem produced is : %d",produced);
			i++;
		}
		sem_post(&s1);
		sleep(1);
	}
	return(&ret);
}

void *consumer()
{
	printf("\nin consumer");
	while(i>0)
	{
		sem_wait(&s1);
		i--;
		consumed = arr[i];
		printf("\nitem consumed is : %d",consumed);	
		sem_post(&s2);
		sleep(1);
	}
	return(&ret);
}
*/

/*
#include<stdio.h>
#include<pthread.h>

int tid1,tid2,produced = 0,consumed = 0,i = 0,buffer[5];
void *producer();
void *consumer();
void *ret;

pthread_t prod,cons;
pthread_mutex_t mu;

void main()
{
	tid1 = pthread_create(&prod,NULL,&producer,NULL);
	if(tid1 == 0)
		printf("\nprod created successfully\n");

	tid2 = pthread_create(&cons,NULL,&consumer,NULL);
	if(tid2 == 0)
		printf("\ncons created successfully\n");
	
	pthread_mutex_init(&mu,0);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
}

void *producer()
{
	printf("\nin producer : ");
	while(1)
	{
		pthread_mutex_lock(&mu);
		while(i < 5)
		{
			produced++;
			buffer[i] = produced;
			printf("\nitem produced is : %d",produced);
			i++;
		}
		pthread_mutex_unlock(&mu);
		sleep(1);
	}
	return(&ret);
}

void *consumer()
{
	printf("\nin consumer : ");
	while(1)
	{
		pthread_mutex_lock(&mu);
		i--;		
		consumed = buffer[i];
		printf("\nitem consumed is : %d",consumed);
		pthread_mutex_unlock(&mu);
		sleep(1);
	}
	return(&ret);
}
*/
