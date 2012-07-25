#include <print.h>
#include <stdlib.h>
#include "xfifo.h"

#define FIFO_SIZE 10

void producer(xfifo_t fifo) 
{
  for (int i=0;i<5;i++) {
    int success;
    success = xfifo_push(fifo, i);
    if (!success) {
      printstr("Error: fifo full!!");
      exit(1);
    }
  }
}

void consumer(xfifo_t fifo) 
{
  for (int i=0;i<5;i++) {
    int x;
    x = xfifo_blocking_pull(fifo);
    printintln(x);
  }
}

int main() 
{
  unsigned int buf[FIFO_OVERHEAD + FIFO_SIZE];
  xfifo_t fifo;
  fifo = xfifo_init(buf, FIFO_SIZE);
  par {
    producer(fifo);
    consumer(fifo);
  }
  return 0;
}
