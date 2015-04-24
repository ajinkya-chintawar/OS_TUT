#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void* reader();
void* writer();

int a=0;
sem_t r,w;
void* status;

int main()
{
	pthread_t rth,wth;
	sem_init(&r,0,1);
	sem_init(&w,0,0);
	
	pthread_create(&rth,NULL,(void*)&reader,NULL);
	pthread_create(&wth,NULL,(void*)&writer,NULL);
	
	sem_destroy(&r);
	sem_destroy(&w);
	
	pthread_join(rth,NULL);
	printf("\n");
	return 0;
}


void* reader()
{
	while(1)
	{
		printf("\nIn reader");
		sem_wait(&r);
		printf("%d",++a);
		sem_post(&w);
		sleep(1);
	}
	pthread_exit(&status);
}

void* writer()
{	
	while(1)
	{
		printf("\n In Writer");
		sem_wait(&w);
		sem_post(&r);
		sleep(1);
	}
	pthread_exit(&status);	
}

OUTPUT :.
shreyash@ssn:~$ gcc Reader_Writer_Semaphore.c -lpthread
shreyash@ssn:~$ ./a.out
