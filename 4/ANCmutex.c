#include<stdio.h>
#include<pthread.h>
int h,m,s,tid1,tid2;
void *read();
void *write();
void *ret;
pthread_t rth,wth;
pthread_mutex_t mu;

void *read()
{
	while(1)
	{
		pthread_mutex_lock(&mu);
		printf("%d : %d : %d",h,m,s);
		pthread_mutex_unlock(&mu);
		sleep(1);
	}
	//pthread_exit(&ret);
	return (&ret);
}
void *write()
{
	while(1)
	{
		pthread_mutex_lock(&mu);
		s = (s + 1) % 61;
		if(s == 60)
			m = ( m + 1 ) % 61;
		if(m == 60)
			h++;

		pthread_mutex_unlock(&mu);
		sleep(1);
	}
	//pthread_exit(&ret);
	return (&ret);
}

void main()
{

	printf("runninggggggg");
	tid1 = pthread_create(&rth,NULL,&read,NULL);
	if(!tid1)
		printf("Rth created Successfully");
	
	tid2 = pthread_create(&wth,NULL,&write,NULL);
	if(!tid2)
		printf("Wth created Successfully");
	pthread_mutex_init(&mu,0);
	pthread_join(rth,ret);
	pthread_join(wth, ret);
	//return 0;
}
