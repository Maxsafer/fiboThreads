#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
	int count, i;

	if (argc != 2) {
		fprintf(stderr,"usage: pthreads <integer value>\n");
		exit(1);
	}

	pthread_attr_t attr; 
	count = atoi(argv[1]);
  int fibos[count-1];

	if (count < 1) {
		fprintf(stderr,"%d must be>= 1\n", count);
		exit(1);
	}

	pthread_attr_init(&attr);

  printf("Fib list es: \n");
	for(i=1;i<=count;i++)
  {
		pthread_t thread;
		pthread_create(&thread,&attr,runner,(void*)i);
		pthread_join(thread,NULL);	
    fibos[i-1] = sum;
	}	

  for(i=0; i<count; i++)
  {      
    printf("%d ",fibos[i]);    
  }
}

void *runner(void *param)
{
	sum = fibonacci((int)param);
	pthread_exit(0);
}

int fibonacci (int x)
{
    if (x <= 1) {
        return 1;
    }
    return fibonacci(x-1) + fibonacci(x-2);
}