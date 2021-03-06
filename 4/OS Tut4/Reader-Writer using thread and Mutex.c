#include<stdio.h>
#include<pthread.h>

int hr,min,sec,tid1,tid2;
void *read();
void *write();
void *ret;

pthread_t rth,wth; 		//threads
pthread_mutex_t mu;		//mutex

void main()
{

	tid1 = pthread_create(&rth,NULL,&read,NULL);	
	if(tid1 == 0)
		printf("\nrth created successfully");
	tid2 = pthread_create(&wth,NULL,&write,NULL);	
	if(tid2 == 0)
		printf("\nwth created successfully");	
	
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
