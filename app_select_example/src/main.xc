void f(chanend c, chanend d[2], chanend e);

int main() {
  chan c,d[2],e;
  par {
    f(c, d, e);
    d[0] <: 333;
    c <: 555;
    d[1] <: 777;
    e <: 999;
  }
  return 0;
}
