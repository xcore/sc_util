
// These functions are implemented in use_locks.c
void init_locks(void);
void free_locks(void);
void use_hwlock(int mult);
void use_swlock(int mult);

int main()
{
  init_locks();
  par {
    use_hwlock(1);
    use_hwlock(2);
    use_hwlock(3);
  }
  par {
    use_swlock(4);
    use_swlock(5);
    use_swlock(6);
  }
  free_locks();
}
