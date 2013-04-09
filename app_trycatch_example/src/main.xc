#include "trycatch.h"
#include <print.h>

int x = 100;
int y = 5;

int main() {
  int a[10];
  exception_t exception;
  TRY {
    a[x] = 0; // Out of bounds array access!
  } CATCH(exception) {
    printstr("Got exception:\n");
    printstr("ET: "); printintln(exception.type);
    printstr("ED: "); printintln(exception.data);
  }
  TRY {
    a[y] = 0; // This access should be in bounds.
  } CATCH(exception) {
    // Shouldn't get here.
    printstr("Unexpected exception!\n");
  }
  return 0;
}
