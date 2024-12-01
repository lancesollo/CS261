//Coded by Lance S.

#include <stdio.h>
#include "queue.h"
/* This method is used to initialize a variable to be tail pointer to a 
process queue. Return a pointer to the tail of an empty process queue; 
i.e. NULL. */
struct queueNode * makeEmptyQueue()
{
    return NULL;
}

/* Return TRUE if the queue whose tail is pointed to by q is empty.
Return FALSE otherwise. */
int emptyQ(struct queueNode *q)
{
    return (q == NULL);
}

/* Insert the queueNode pointed to by p into the queue whose 
tail-pointer is pointed to by q. */
void insertQ(struct queueNode **q, struct queueNode *p)
{
    if (emptyQ(*q))
    {
        /* make p the one and only node in this queue */
        
        // points p's next pointer to itself
        p->next = p;

        // the tail pointer points to the new node
        *q = p;
    }
    else
    {
        /*
            insert p at the tail, and it becomes the new tail
            This is a circular queue, so the tail must point to head, i.e.
            (*q)->next must always be the front of the queue 
        */
       
       // point the new node's next pointer to the tail pointer's node's next pointer
       // (so the new node's next pointer points at the "head" of the circular queue)
       p->next = (*q)->next;

       // point the tail's node's next pointer to the new node
       (*q)->next = p;

       // the tail pointer points to the new node
        *q = p;
    }
}

/* Remove the first (i.e. head) element from the queue whose 
tail-pointer is pointed to by q. Return NULL if the queue is empty; 
otherwise return the pointer to the removed queueNode. Update the 
queue’s tail pointer if necessary. (Note: since *q is a pointer to the tail,
(*q)->next is the head, if it exists)*/
struct queueNode *removeQ(struct queueNode **q)
{
    if (emptyQ(*q))
    {
        return NULL;
    }
    else
    {
        /* disconnect the head node from the queue, update the tail,
        return the head */

        // checks for if the queue only has one element
        // if it does, then it returns q, since q points to the only node
        if((*q)->next == (*q)){
            struct queueNode *x = headQ(*q);
            *q = NULL;
            return (x);
        }

        // get a pointer to the head of the queue, called x
        struct queueNode *x = headQ(*q);

        // change the tail node's next pointer to point to the same node that
        // the head node point's to
        (*q)->next = x->next;

        // now, point the head node's next pointer to nothing
        x->next = NULL;

        // at this point, x and the head are isolated
        // x is the only node that points to head we are looking to remove,
        // and nothing points to x.

        // so, we return x, since it points the head we removed
        return x;


        
    }
    return NULL;
}

/* Return a pointer to the first queueNode from the queue whose tail is 
pointed to by q. Do not remove this queueNode from the queue. Return NULL 
if the queue is empty. */
struct queueNode *headQ(struct queueNode *q)
{
    if (emptyQ(q)) return NULL;
    else return q->next;
}

