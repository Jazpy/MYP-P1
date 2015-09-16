#include <stdlib.h>
#include "linked_list.h"

void free_list(struct node *head)
{
	struct node *conductor;

	while((conductor = head) != 0)
	{
		head = head -> next;
		free(conductor);
	}
}
