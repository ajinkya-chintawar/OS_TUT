#include<stdio.h>
#include<pthread.h>
#define buffer 5
int buf[buffer], f, index1 = 0;
pthread_mutex_t mutex;
pthread_cond_t full, empty;
int cntr = 0, i = 0, cntr1 = 0;

void *producer (void *arg)
{
  for (cntr = 0; cntr < 10; cntr++)
    {
      printf ("\n\tProducer: Checking if buffer has some space");
      pthread_mutex_lock (&mutex);
      while (index1 == buffer)
	{
	  printf
	    ("\n\n\tProducer: buffer already full, will block until signalled");
	  pthread_cond_wait (&empty, &mutex);
	}
      buf[index1] = i;
      index1++;
      printf ("\nProducer: Produced item is %d\n", i);
      i++;
      pthread_cond_signal (&full);
      pthread_mutex_unlock (&mutex);
    }

  pthread_exit (0);
}

void *consumer (void *arg)
{
  int item;

  for (cntr1 = 0; cntr1 < 10; cntr1++)
    {
      printf ("\n\tConsumer: Checking if buffer has some item");
      pthread_mutex_lock (&mutex);
      while (index1 == 0)
	{
	  printf ("\n\n\tConsumer: buffer empty, will block until signalled");
	  pthread_cond_wait (&full, &mutex);
	}
      item = buf[index1 - 1];
      index1--;
      printf ("\n\t\t\tConsumer: Consumed item is %d\n", item);
      //buffer=0;
      pthread_cond_signal (&empty);
      pthread_mutex_unlock (&mutex);
      sleep (1);
    }
  pthread_exit (0);

}

void
main ()
{
  int i;
  pthread_t tid1, tid2;

  pthread_mutex_init (&mutex, NULL);
  pthread_cond_init (&full, NULL);
  pthread_cond_init (&empty, NULL);

  pthread_create (&tid1, NULL, producer, NULL);

  pthread_create (&tid2, NULL, consumer, NULL);

  pthread_join (tid1, NULL);
  pthread_join (tid2, NULL);

  pthread_mutex_destroy (&mutex);
  pthread_cond_destroy (&full);
  pthread_cond_destroy (&empty);

}

//OUTPUT
/*
nupur@nupur-VirtualBox:~/Desktop$ gcc ProdConsm.c -lpthread -lrt -o ProdConsm
nupur@nupur-VirtualBox:~/Desktop$ ./ProdConsm

	Consumer: Checking if buffer has some item

	Consumer: buffer empty, will block until signalled
	Producer: Checking if buffer has some space
Producer: Produced item is 0

	Producer: Checking if buffer has some space
			Consumer: Consumed item is 0

Producer: Produced item is 1

	Producer: Checking if buffer has some space
Producer: Produced item is 2

	Producer: Checking if buffer has some space
Producer: Produced item is 3

	Producer: Checking if buffer has some space
Producer: Produced item is 4

	Producer: Checking if buffer has some space
Producer: Produced item is 5

	Producer: Checking if buffer has some space

	Producer: buffer already full, will block until signalled
	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 5

Producer: Produced item is 6

	Producer: Checking if buffer has some space

	Producer: buffer already full, will block until signalled
	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 6

Producer: Produced item is 7

	Producer: Checking if buffer has some space

	Producer: buffer already full, will block until signalled
	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 7

Producer: Produced item is 8

	Producer: Checking if buffer has some space

	Producer: buffer already full, will block until signalled
	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 8

Producer: Produced item is 9

	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 9

	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 4

	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 3

	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 2

	Consumer: Checking if buffer has some item
			Consumer: Consumed item is 1
nupur@nupur-VirtualBox:~/Desktop$ 
*/
