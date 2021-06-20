#ifndef FIBER_H
#define FIBER_H

#define FIBER_NOERROR 0
#define FIBER_MAXFIBERS 1
#define FIBER_MALLOC_ERROR 2
#define FIBER_CLONE_ERROR 3
#define FIBER_INFIBER 4

void fiber_init();
/* Yields control to another execution context */
void fiber_yield();
/* Creates a new fiber, running the func that is passed as an argument. */
int fiber_spawn(void (*func)(void));
/* Executes the fibers until they all quit. */
int fiber_wait_all();

#endif
