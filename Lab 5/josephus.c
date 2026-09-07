#include "josephus.h"

Node *josephusRemove(CircularList *list, int k)
{
    return locateAndRemove(list, k);
}
