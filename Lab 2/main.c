#include <stdio.h>
#include "list.h"

int main()
{
    mylist_t list;

    /* Initialize */
    init_list(&list);

    /* Insert elements */
    insert_list(&list, 30);
    insert_list(&list, 10);
    insert_list(&list, 60);
    insert_list(&list, 20);
    insert_list(&list, 50);
    /* Display */
    printf("Ordered List: ");
    disp_list(&list);

    /* Free memory */
    free_list(&list);

    return 0;
}