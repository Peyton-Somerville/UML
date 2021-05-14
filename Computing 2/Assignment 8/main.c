#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(void)
{
	PRIORITY_QUEUE hQueue = NULL;
	int i;

	hQueue = priority_queue_init_default();
	if (hQueue = NULL)
	{
		printf("Did not create an object\n");
		exit(1);
	}

	priority_queue_insert(hQueue, 3, 1);
	priority_queue_insert(hQueue, 2, 2);
	priority_queue_insert(hQueue, 1, 3);


	for (i = 0; i < 3; i++)
		printf("%d\n", priority_queue_front(hQueue, NULL));

	priority_queue_destroy(&hQueue);

	return 0;
}
