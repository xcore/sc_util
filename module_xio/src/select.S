.text

.globl __c_event_handler
.globl __c_event_handler.nstackwords
.globl __c_event_handler.maxthreads
.globl __c_event_handler.maxtimers
.globl __c_event_handler.maxchanends
.globl __c_event_handler.maxsync
.type  __c_event_handler, @function
.linkset __c_event_handler.locnoside, 1
.linkset __c_event_handler.locnochandec, 1
.set __c_event_handler.nstackwords, 0
.set __c_event_handler.maxthreads, 0
.set __c_event_handler.maxtimers, 0
.set __c_event_handler.maxchanends, 0
.set __c_event_handler.maxsync, 0

__c_event_handler:
   get r11, ed
   mkmsk r0, 8
   and r0, r11, r0
   retsp 0

.globl __c_wait
.globl __c_wait.nstackwords
.globl __c_wait.maxthreads
.globl __c_wait.maxtimers
.globl __c_wait.maxchanends
.globl __c_wait.maxsync
.type  __c_wait, @function
.linkset __c_wait.locnoside, 1
.linkset __c_wait.locnochandec, 1
.set __c_wait.nstackwords, 0
.set __c_wait.maxthreads, 0
.set __c_wait.maxtimers, 0
.set __c_wait.maxchanends, 0
.set __c_wait.maxsync, 0

__c_wait:
   waiteu
