/* Grigore Lucian-Florin - 336CA - SO Tema 4*/

/* libraries used */
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "_test/so_scheduler.h"
#include <errno.h>

/* defining thread states */
#define STATE_NEW 0
#define STATE_READY 1
#define STATE_RUNNING 2
#define STATE_WAITING 3
#define STATE_TERMINATED 4

/* maximum number of threads */
#define MAX_NO_THREADS 1024

/* error check macro */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

/* thread structure */
struct thread {
	tid_t id;
	unsigned int state;
	unsigned int prio;
	unsigned int event;
	so_handler *handler;
	sem_t in_exec;
	int time_left;
};

/* scheduler structure */
struct thread_scheduler {
	int is_init;
	unsigned int t_quant;
	unsigned int no_events;
	unsigned int no_threads;
	unsigned int q_size;
	sem_t done;
	struct thread *curr_thread;
	struct thread *threads[MAX_NO_THREADS];
	struct thread *q[MAX_NO_THREADS];
};

/* scheduler */
static struct thread_scheduler scheduler;

/* additional functions used */
static void free_thread(struct thread *);
static void *f_thread(void *);
static void update_scheduler(void);
static void add_thread_to_sched(struct thread *);
static struct thread *create_thread(so_handler *, unsigned int);
static void run_thread(struct thread *);

int so_init(unsigned int time_quantum, unsigned int io)
{
	int ret;

	/* checking params */
	if (scheduler.is_init == 1 || time_quantum <= 0 ||
		io > SO_MAX_NUM_EVENTS)
		return -1;

	/* scheduler internal data */
	scheduler.t_quant = time_quantum;
	scheduler.no_events = io;
	scheduler.is_init = 1;
	scheduler.curr_thread = NULL;
	scheduler.q_size = 0;
	scheduler.no_threads = 0;

	/* this sem signals when scheduler is done */
	ret = sem_init(&scheduler.done, 0, 1);
	DIE(ret != 0, "sem init err");

	return 0;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	int ret = 0;

	struct thread *new_thread = NULL;

	/* checking params */
	if (func == NULL || priority > SO_MAX_PRIO)
		return INVALID_TID;

	/* if it is the first thread */
	if (scheduler.no_threads == 0) {
		ret = sem_wait(&scheduler.done);
		DIE(ret != 0, "fork sem wait err");
	}

	/* creating new thread */
	new_thread = create_thread(func, priority);

	/* adding new thread to the scheduler */
	scheduler.threads[scheduler.no_threads] = new_thread;
	scheduler.no_threads = scheduler.no_threads + 1;
	add_thread_to_sched(new_thread);

	if (scheduler.curr_thread != NULL)
		so_exec();
	else
		update_scheduler();

	return new_thread->id;
}

int so_wait(unsigned int io)
{
	if (io < 0 || io >= scheduler.no_events)
		return -1;

	/* block current thread until io is signaled */
	scheduler.curr_thread->event = io;
	scheduler.curr_thread->state = STATE_WAITING;

	so_exec();

	return 0;
}

int so_signal(unsigned int io)
{
	int i = 0, no = 0;

	if (io < 0 || io >= scheduler.no_events)
		return -1;

	/* wake up all the threads that are waiting for a specific io */
	for (; i < scheduler.no_threads; ++i) {
		struct thread *t = scheduler.threads[i];

		if (t->event == io && t->state == STATE_WAITING) {
			++no;
			t->state = STATE_READY;
			t->event = SO_MAX_NUM_EVENTS;
			add_thread_to_sched(t);
		}
	}

	so_exec();

	return no;
}

void so_exec(void)
{
	int ret = 0;

	struct thread *t = scheduler.curr_thread;

	/* consume time from current thread and update prio q */
	t->time_left = t->time_left - 1;

	update_scheduler();

	ret = sem_wait(&t->in_exec);
	DIE(ret != 0, "so exec sem wait err");
}

void so_end(void)
{
	int i = 0, ret;

	if (scheduler.is_init == 0)
		return;

	/* wait for scheduler to be done */
	ret = sem_wait(&scheduler.done);
	DIE(ret != 0, "scheduler sem wait err");

	/* wait for all threads and free memory */
	for (; i < scheduler.no_threads; ++i) {
		ret = pthread_join(scheduler.threads[i]->id, NULL);
		DIE(ret != 0, "pthread join err");
	}

	for (i = 0; i < scheduler.no_threads; ++i)
		free_thread(scheduler.threads[i]);

	scheduler.is_init = 0;
	ret = sem_destroy(&scheduler.done);
	DIE(ret != 0, "scheduler sem destroy err");
}

static void free_thread(struct thread *t)
{
	int ret = sem_destroy(&t->in_exec);

	DIE(ret != 0, "thread sem destroy err");

	free(t);
}

/* thread routine executed by all fork'ed threads */
static void *f_thread(void *args)
{
	struct thread *t = (struct thread *) args;

	int ret = sem_wait(&t->in_exec);

	DIE(ret != 0, "thread sem wait err");

	t->handler(t->prio);
	t->state = STATE_TERMINATED;

	update_scheduler();

	return NULL;
}

/* updates scheduler's prio q */
static void update_scheduler(void)
{
	int ret = 0;

	struct thread *curr = scheduler.curr_thread, *next = NULL;

	/* if we can stop the scheduler, if the q is empty */
	if (scheduler.q_size == 0) {
		if (curr->state == STATE_TERMINATED) {
			ret = sem_post(&scheduler.done);
			DIE(ret != 0, "last thread sem post err");
		}

		ret = sem_post(&curr->in_exec);
		DIE(ret != 0, "curr last thread sem post err");

		return;
	}

	next = scheduler.q[scheduler.q_size - 1];

	/* if current thread is blocked/done or not yet initalised */
	if (curr == NULL ||
		curr->state == STATE_WAITING ||
		curr->state == STATE_TERMINATED) {
		scheduler.curr_thread = next;
		run_thread(next);
		return;
	}

	/* if 1st thread in q has a bigger prio */
	if (next->prio > curr->prio) {
		add_thread_to_sched(curr);
		scheduler.curr_thread = next;
		run_thread(next);
		return;
	}

	/* if current thread's quantum expired */
	if (curr->time_left <= 0) {
		/* round robin */
		if (curr->prio == next->prio) {
			add_thread_to_sched(curr);
			scheduler.curr_thread = next;
			run_thread(next);
			return;
		}

		curr->time_left = scheduler.t_quant;
	}

	ret = sem_post(&curr->in_exec);
	DIE(ret != 0, "last sem post err");
}

/* adds a thread to the prio q based on its own priority */
static void add_thread_to_sched(struct thread *t)
{
	int i = 0, j = scheduler.q_size;

	for (; i < scheduler.q_size; ++i)
		if (scheduler.q[i]->prio >= t->prio)
			break;

	for (; j > i; --j)
		scheduler.q[j] = scheduler.q[j - 1];

	scheduler.q[i] = t;
	scheduler.q[i]->state = STATE_READY;
	scheduler.q_size = scheduler.q_size + 1;
}

/* creates a new thread and initialises its internal values */
static struct thread *create_thread(so_handler *func, unsigned int priority)
{
	int ret;

	struct thread *t = (struct thread *) malloc(sizeof(*t));

	DIE(t == NULL, "thread malloc err");

	/* initialising thread atributes */
	t->id = INVALID_TID;
	t->handler = func;
	t->event = SO_MAX_NUM_EVENTS;
	t->prio = priority;
	t->state = STATE_NEW;
	t->time_left = scheduler.t_quant;

	ret = sem_init(&t->in_exec, 0, 0);
	DIE(ret != 0, "thread sem init err");

	/* starting thread */
	ret = pthread_create(&t->id, NULL, &f_thread, (void *)t);
	DIE(ret != 0, "pthread create err");

	return t;
}

/* starts a specific thread and removes it from the prio q */
static void run_thread(struct thread *t)
{
	int ret = 0;

	t->state = STATE_RUNNING;
	t->time_left = scheduler.t_quant;

	scheduler.q_size = scheduler.q_size - 1;
	scheduler.q[scheduler.q_size] = NULL;

	ret = sem_post(&t->in_exec);
	DIE(ret != 0, "thread sem post err");
}
