/*************************************************************************
 *
 * XMOS XC Fifo Library
 *
 *   XC File: xfifo_internal.h
 *   Author: David Lacey
 *
 *************************************************************************/
/*
 * Copyright (c) 2006-2008 XMOS Ltd.
 *
 * Copyright Notice
 *
 *************************************************************************/

#ifndef _xfifo_internal_h_
#define _xfifo_internal_h_

// Here a fifo is defined as an array of unsigned ints
// The typestrings will be patched after compilation
#define fifo_t unsigned int

// A fifo is represented as an array where the first five elements
// of the array contain the information/pointers into the queue.

// a[0] = Index of next element to be added to queue (ipos)
// a[1] = Index before next element to be taken from queue (opos)
// a[2] = Length of the array
// a[3] = Index of the beginning of the current packet (spos)
// a[4] = Flag - 0 if current packet has overflowed, 1 otherwise

// The rest of the array is the queue itself, taking up n+1 words of space
// where n is the size of the queue.
// The extra space lets us have distinct checks for a full/empty queue.

// Conditions (for a normal queue) :

// ipos = opos ==> queue full
// ipos = opos-1 ==> queue empty

// Conditions (for a packetized queue) :

// ipos = opos ==> queue full
// ipos = spos-1 ==> queue empty (not including current packet)

#define IPOS_INDEX 0
#define OPOS_INDEX 1
#define LEN_INDEX 2
#define SPOS_INDEX 3
#define OVERFLOW_INDEX 4
#define FIFO_START 5

#endif
