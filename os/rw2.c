//Reader Writer using thread and semaphore
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

void *read(), *write();
int a;
int hr=0, min=0, sec=0;
void *ret;
pthread_t rth, wth;
sem_t s1,s2;
void main()
{
	int r1=1, r2=1;
	a=10;

	//create thread	
	r1=pthread_create(&rth,NULL,&read,NULL);
	r2=pthread_create(&wth,NULL,&write,NULL);	
	
	//check for success/failure
	if(r1==0)
		printf("rth created successfully.\n");
	else
		printf("rth thread creation failed.\n");
	if(r2==0)
		printf("wth created successfully.\n");
	else
		printf("wth thread creation failed.\n");

	//initializing semaphore
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);

	//Join threads
	pthread_join(rth,ret);
	pthread_join(wth,ret);
}

void *read()
{
	printf("\n");
	while(1)
	{
		sem_wait(&s2);
		printf("%d:%d:%d\n", hr, min, sec);
		sem_post(&s1);
		sleep(1);
	}
	pthread_exit(&ret);
}

void *write()
{
	printf("\n");
	while(1)
	{
		sem_wait(&s1);
		sec++;
		if(sec==60)
		{
			sec=0; 
			min++;	
		}
		if(min==60)
		{
			min=0;
			hr++;
		}
		if(hr==24)
		{
			hr=0;
		}
		sem_post(&s2);
		sleep(1);
	}
	pthread_exit(&ret);
}

/*
OUTPUT:
guest-LKmaZP@isl-61:~$ gcc rw.c -l pthread
guest-LKmaZP@isl-61:~$ ./a.out
rth created successfully.
wth created successfully.
0:0:0
0:0:1
0:0:3
0:0:4
0:0:5
0:0:5
0:0:6
0:0:7
0:0:9
0:0:10
0:0:10
0:0:12
0:0:13
0:0:14
0:0:15
0:0:16
0:0:17
0:0:18
0:0:19
0:0:20
0:0:21
*/
