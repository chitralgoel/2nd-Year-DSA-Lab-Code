#include <stdio.h>
#include <stdlib.h>
#include "list.h"
void init_list(mylist_t* ptr_list)
{
	ptr_list->head_ = NULL;
}

// 1. empty list
// 2. insert in the middle
// 3. insert in the beginning
// 4. insert at the end

void insert_list(mylist_t* ptr_list, int key)
{
	// create the node
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->key_ = key; temp->next_ = NULL;

	// 1.empty list
	if(ptr_list->head_ == NULL)
	{
		ptr_list->head_ = temp;
		temp->next_ = NULL;
	}
	else
	{
		// traverse
		node_t* prev = NULL;
		node_t* pres = ptr_list->head_;
		while(pres != NULL && pres->key_ < temp->key_ )
		{
			prev = pres;
			pres = pres->next_;
		}
		if(prev == NULL) // insert in the beginning
		{
			temp->next_ = pres;
			ptr_list->head_ = temp;
		}
		else // middle or end
		{
			temp->next_ = pres;
			prev->next_ = temp;
		}
		
	}
}


/* Display the list */
void disp_list(mylist_t *ptr_list)
{
    node_t *q = ptr_list->head_;

    while (q != NULL)
    {
        printf("%d ", q->key_);
        q = q->next_;
    }

    printf("\n");
}


/* Free the list */
void free_list(mylist_t *ptr_list)
{
    node_t *q = ptr_list->head_;
    node_t *r;

    while (q != NULL)
    {
        r = q->next_;
        free(q);
        q = r;
    }

    ptr_list->head_ = NULL;
}