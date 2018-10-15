#include "IQueue.h"
/*
 A very simple integer queue implemented as a circular array
*/

int Contents[MaxQSize];
int Start = 0;
int Length = 0;

void IQueueStore(int Item)
{
  int StoreAt;
  if (Length == MaxQSize) return;
  StoreAt = (Start + Length ) % MaxQSize;
  Contents[StoreAt] = Item;
  Length++ ;
}

int IQueueRetrieve()
{
  int Value;
  if (Length == 0) return -1;
  Value = Contents[Start];
  Start = ( Start + 1) % MaxQSize;
  Length-- ;
  return Value;
}

int IQueueSize()
{
  return Length;
}

