#include  <stdarg.h>
#include "select.h"
#include "print.h"
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
  va_start(ap, arg1);
  for (res = arg1,choice=0; res != 0; res = va_arg(ap, int),choice++) {
    if (res == -1) {
      int *arr = va_arg(ap, int *);
      int n = va_arg(ap, int);
      for (int i=0;i<n;i++)
        setup_resource(arr[i],choice,i);
    } else {
      setup_resource(res,choice,0);
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
