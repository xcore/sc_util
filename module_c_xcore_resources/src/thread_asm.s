.file "thread_asm.S"

.text
.globl joinable_thread_exit
.type joinable_thread_exit, @function
.typestring joinable_thread_exit, "f{0}(p(0))"
.align 2
.cc_top joinable_thread_exit.function
joinable_thread_exit:
  ssync
  tsetmr r0, r0
.xtathreadstop
  ssync
  ldc r0, 0
  ecallf r0
.size joinable_thread_exit, .-joinable_thread_exit
.cc_bottom joinable_thread_exit.function
.globl joinable_thread_exit.nstackwords
.globl joinable_thread_exit.maxchanends
.globl joinable_thread_exit.maxtimers
.globl joinable_thread_exit.maxthreads
.set joinable_thread_exit.nstackwords, 0
.set joinable_thread_exit.maxchanends, 0
.set joinable_thread_exit.maxtimers, 0
.set joinable_thread_exit.maxthreads, 0

.globl detached_thread_exit
.type detached_thread_exit, @function
.typestring detached_thread_exit, "f{0}(0)"
.align 2
.cc_top detached_thread_exit.function
detached_thread_exit:
.xtathreadstop
  freet
.size detached_thread_exit, .-detached_thread_exit
.cc_bottom detached_thread_exit.function
.globl detached_thread_exit.nstackwords
.globl detached_thread_exit.maxchanends
.globl detached_thread_exit.maxtimers
.globl detached_thread_exit.maxthreads
.set detached_thread_exit.nstackwords, 0
.set detached_thread_exit.maxchanends, 0
.set detached_thread_exit.maxtimers, 0
.set detached_thread_exit.maxthreads, 0

.globl thread_join
.type thread_join, @function
.typestring thread_join, "f{p(0)}(ui)"
.align 2
.cc_top thread_join.function
thread_join:
  mov r1, r0
  msync res[r1]
  mjoin res[r1]
  freer res[r1]
  retsp 0
.size thread_join, .-thread_join
.cc_bottom thread_join.function
.globl thread_join.nstackwords
.globl thread_join.maxchanends
.globl thread_join.maxtimers
.globl thread_join.maxthreads
.set thread_join.nstackwords, 0
.set thread_join.maxchanends, 0
.set thread_join.maxtimers, 0
.set thread_join.maxthreads, 0

.globl thread_group_join
.type thread_group_join, @function
.typestring thread_group_join, "f{0}(ui)"
.align 2
.cc_top thread_group_join.function
thread_group_join:
  bu thread_join
  retsp 0
.size thread_group_join, .-thread_group_join
.cc_bottom thread_group_join.function
.globl thread_group_join.nstackwords
.globl thread_group_join.maxchanends
.globl thread_group_join.maxtimers
.globl thread_group_join.maxthreads
.set thread_group_join.nstackwords, 0
.set thread_group_join.maxchanends, 0
.set thread_group_join.maxtimers, 0
.set thread_group_join.maxthreads, 0
