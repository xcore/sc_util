#include  <stdarg.h>
#include <xs1.h>
#include "select.h"
#include "print.h"
#include "port.h"

int __c_wait();

static void setup_resource(int res, int choice, int i)
{
  asm("ldap r11, __c_event_handler;setv res[%0], r11"::"r"(res):"r11");
  asm("mov r11,%1;setev res[%0], r11"::"r"(res),"r"(i<<8|choice):"r11");
  asm("eeu res[%0]"::"r"(res));
}

int __c_select(int arg1, ...)
{
  asm("clre");
  va_list ap;
  int res,choice;
  int use_default = 0;
  va_start(ap, arg1);
  for (res = arg1,choice=0; res != SELECT_END; res = va_arg(ap, int),choice++) {
    switch (res)
      {
      case SELECT_DEFAULT:
        use_default = 1;
        break;
      case SELECT_OVER_ARRAY: {
        int *arr = va_arg(ap, int *);
        int n = va_arg(ap, int);
        for (int i=0;i<n;i++)
          setup_resource(arr[i],choice,i);
        break;
      }
#if 0
      case SELECT_WHEN_PINSEQ:
        res = va_arg(ap, int);
        port_set_condition(res, XS1_PORT_PINSEQ);
        setup_resource(res,choice,0);
        break;
      case SELECT_WHEN_PINSEQ:
        res = va_arg(ap, int);
        port_set_condition(res, XS1_PORT_PINSEQ);
        setup_resource(res,choice,0);
        break;
#endif
      default:
        setup_resource(res,choice,0);
        break;
      }
  }
  va_end(ap);

  return __c_wait();
}

int get_selected_array_index()
{
  int ed;
  asm("get r11,ed;mov %0,r11":"=r"(ed)::"r11");
  return (((short) ed) >> 8);
}
