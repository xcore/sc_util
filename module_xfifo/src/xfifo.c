#include "xfifo.h"
#include "xfifo_internal.h"

xfifo_t xfifo_init(unsigned int fifo[], unsigned int n)
{
  fifo[LEN_INDEX] = n+FIFO_START+1;
  fifo[IPOS_INDEX] = FIFO_START+1;
  fifo[OPOS_INDEX] = FIFO_START;
  fifo[SPOS_INDEX] = FIFO_START+1;
  fifo[OVERFLOW_INDEX] = 1;
  return ((xfifo_t) &fifo[0]);
}


unsigned int xfifo_push(xfifo_t fifo0, unsigned int x)
{

  unsigned int ipos;
  unsigned int opos;
  unsigned int len;
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;

  ipos = fifo[IPOS_INDEX];
  opos = fifo[OPOS_INDEX];
  len  = fifo[LEN_INDEX];

  if (ipos!=opos)  {
    fifo[ipos] = x;
    ipos++;
    if (ipos == len)
      ipos = FIFO_START;
    fifo[IPOS_INDEX] = ipos;
  }
  else
    return 0;

  return 1;  ;
}

unsigned int xfifo_pull(xfifo_t fifo0, unsigned int *success)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  unsigned int ipos = fifo[IPOS_INDEX];
  unsigned int opos = fifo[OPOS_INDEX];
  unsigned int len = fifo[LEN_INDEX];

  opos++;
  if (opos == len)
    opos = FIFO_START;

  if (ipos!=opos)  {
    unsigned int x = fifo[opos];
    fifo[OPOS_INDEX]=opos;
    *success = 1;
    return x;
  }
  else
    *success = 0;

  return 0;
}

unsigned int xfifo_num_elements(xfifo_t fifo0)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  int n;
  int ipos = fifo[IPOS_INDEX];
  int opos = fifo[OPOS_INDEX];

  n = ipos - opos;

  if (ipos <= opos ) {
    n += fifo[LEN_INDEX] - (FIFO_START + 1);
  }
  else {
    n -= 1;
  }

  return n;
}


unsigned int xfifo_is_empty(xfifo_t fifo0)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  unsigned int ipos = fifo[IPOS_INDEX];
  unsigned int opos = fifo[OPOS_INDEX];
  unsigned int len = fifo[LEN_INDEX];

  opos++;
  if (opos == len)
    opos = FIFO_START;

  return (ipos==opos);
}

unsigned int xfifo_is_full(xfifo_t fifo0)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  unsigned int ipos;
  unsigned int opos;
  ipos = fifo[IPOS_INDEX];
  opos = fifo[OPOS_INDEX];

  return (ipos==opos);
}


void xfifo_blocking_push(xfifo_t fifo0, unsigned int x)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  unsigned int ipos;
  unsigned int opos;
  unsigned int len;

  ipos = fifo[IPOS_INDEX];

  // This loop is dangerous, it relies on the optimizers not
  // lifting the array access out of the loop.
  do {
    opos = fifo[OPOS_INDEX];
  }
  while (ipos==opos);

  len  = fifo[LEN_INDEX];
  fifo[ipos] = x;
  ipos++;
  if (ipos == len)
    ipos = FIFO_START;

  fifo[IPOS_INDEX] = ipos;

  return;
}


unsigned int xfifo_blocking_pull(xfifo_t fifo0)
{
  volatile unsigned int *fifo = (volatile unsigned int *) fifo0;
  unsigned int ipos;
  unsigned int opos;
  unsigned int len;
  unsigned int x;

  len = fifo[LEN_INDEX];
  opos = fifo[OPOS_INDEX];
  opos++;
  if (opos == len)
    opos = FIFO_START;

  // This loop is dangerous, it relies on the optimizers not
  // lifting the array access out of the loop.
  do {
    ipos = fifo[IPOS_INDEX];
  }
  while (ipos == opos);

  x = fifo[opos];
  fifo[OPOS_INDEX]=opos;

  return x;
}
