#ifndef __foo_h__
#define __foo_h__

/** This module provides a dummy server that periodically provides some
    data and responsed to commands from the client */

/** Send a command to get a stored value from the foo server */
int foo_cmdA(chanend c);

/** Send a command to set a stored value in the foo server */
void foo_cmdB(chanend c, int x);


/* This select handler fires when the foo server periodically
   provides some data
*/
#pragma select handler
void data_from_foo_server(chanend c, int &data);

/* The foo server task */
void foo_server(chanend c);

#endif // __foo_h__
