#define MaxQSize 80
/*
  A very simple integer queue
*/

/*
  Put an integer into the queue.
  If the queue is full, the integer will not be added.
*/
void IQueueStore(int Item);

/*
  Retrieve an integer from the queue, it is also deleted from the queue
  If the queue is empty, a -1 is returned. Check the queue size before
  doing a retrieve.
*/
int IQueueRetrieve();

/*
 How many integers are in the queue.
*/
int IQueueSize();
