#include <stdio.h>
#include "channel.h"
#include "select.h"

void f(chanend c, chanend d[2], chanend e)
{
  int x, i;
  for (int count=0;count<4;count++) {
    int choice = select(c, // 0
                        select_over_array(d,2), // 1
                        e // 2
                        );
    switch (choice)
      {
      case 0:
        x = chan_input_word(c);
        printf("Received %d on channel c\n",x);
        break;
      case 1:
        i = get_selected_array_index();
        x = chan_input_word(d[i]);
        printf("Received %d on channel d[%d]\n",x,i);
        break;
      case 2:
        x = chan_input_word(e);
        printf("Received %d on channel e\n",x);
        break;
      }
  }
}
