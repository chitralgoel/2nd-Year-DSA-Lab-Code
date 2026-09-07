#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "clist.h"

/* Performs one Josephus elimination and returns the removed node. */
Node *josephusRemove(CircularList *list, int k);

#endif
