#ifndef __select_h__
#define __select_h__

int __c_select(int x, ...);

#define select(...) __c_select(__VA_ARGS__,0)

#define select_over_array(a, n) -1,a,n

int get_selected_array_index();

#endif
