/* Grigore Lucian-Florin - 336CA - SO Tema 4 Windows */

/* libraries used */
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
#define MAX_NO_THREADS 5000

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
	HANDLE in_exec;
	HANDLE hThread;
	int time_left;
};

/* scheduler structure */
struct thread_scheduler {
	int is_init;
	unsigned int t_quant;
	unsigned int no_events;
	int no_threads;
	int q_size;
	HANDLE done;
	struct thread *threads[MAX_NO_THREADS];
	struct thread *curr_thread;
	struct thread *q[MAX_NO_THREADS];
};

/* scheduler */
static struct thread_scheduler scheduler;

/* additional functions used */
static void free_thread(struct thread *);
static DWORD *f_thread(void *);
static void update_scheduler(void);
static void add_thread_to_sched(struct thread *);
static struct thread *create_thread(so_handler *, unsigned int);
static void run_thread_and_extract_from_prioq(struct thread *);

int so_init(unsigned int time_quantum, unsigned int io)
{
	/* checking params and if scheduler is already init'd */
	if (scheduler.is_init == 1 ||
		time_quantum <= 0 ||
		io > SO_MAX_NUM_EVENTS)
		return -1;

	/* scheduler internal params */
	scheduler.t_quant = time_quantum;
	scheduler.no_events = io;
	scheduler.is_init = 1;
	scheduler.curr_thread = NULL;
	scheduler.q_size = 0;
	scheduler.no_threads = 0;

	/* creating internal semaphore */
	scheduler.done = CreateSemaphore(NULL, 1, 1, NULL);
	DIE(scheduler.done == NULL, "scheduler done create semaphore err");

	return 0;
}

tid_t so_fork(so_handler *func, unsigned int priority)
{
	int ret = 0;

	struct thread *new_thread = NULL;

	/* checking params */
	if (func == NULL || priority > SO_MAX_PRIO)
		return INVALID_TID;

	/* first thread wait for scheduler to be done init'd */
	if (scheduler.no_threads == 0) {
		ret = WaitForSingleObject(scheduler.done, INFINITE);
		DIE(ret == WAIT_FAILED, "fork sem wait err");
	}

	/* create new thread, add it to q and to list */
	new_thread = create_thread(func, priority);

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

	/* block thread until specified io is signaled */
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

	/* wake up all threads waiting for specified io */
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

	/* consuming time left by current thread and updating scheduler */
	t->time_left = t->time_left - 1;

	update_scheduler();

	ret = WaitForSingleObject(t->in_exec, INFINITE);
	DIE(ret == WAIT_FAILED, "so exec sem wait err");
}

void so_end(void)
{
	int i = 0, ret;

	if (scheduler.is_init == 0)
		return;

	/* waiting for scheduler to end */
	ret = WaitForSingleObject(scheduler.done, INFINITE);
	DIE(ret == WAIT_FAILED, "scheduler sem wait err");

	/* waiting for all threads to finish and free their memory */
	for (; i < scheduler.no_threads; ++i) {
		ret = WaitForSingleObject(
			scheduler.threads[i]->hThread, INFINITE);
		DIE(ret == WAIT_FAILED, "pthread join err");
	}

	for (i = 0; i < scheduler.no_threads; ++i)
		free_thread(scheduler.threads[i]);

	/* resetting internal scheduler data */
	scheduler.is_init = 0;
	ret = CloseHandle(scheduler.done);
	DIE(ret == 0, "close handle scheduler done err");
}

/* closes thread handles and frees memory */
static void free_thread(struct thread *t)
{
	int ret = CloseHandle(t->in_exec);

	DIE(ret == 0, "close handle thread err");

	ret = CloseHandle(t->hThread);

	DIE (ret == 0, "close handle hthread err");

	free(t);
}

/* thread routine executed by each forked thread*/
static DWORD *f_thread(void *args)
{
	struct thread *t = (struct thread *) args;

	/* wait for thread to be scheduled */
	int ret = WaitForSingleObject(t->in_exec, INFINITE);

	DIE(ret == WAIT_FAILED, "thread sem wait err");

	/* run specified function */
	t->handler(t->prio);
	t->state = STATE_TERMINATED;

	update_scheduler();

	ExitThread(0);
}

/* updates scheduler prio_q and signals current thread to run */
static void update_scheduler(void)
{
	int ret = 0;

	struct thread *curr = scheduler.curr_thread, *next = NULL;

	/* if prio_q is empty, maybe scheduler is done
	 * if current thread is done
	 */
	if (scheduler.q_size == 0) {
		if (curr->state == STATE_TERMINATED) {
			ret = ReleaseSemaphore(scheduler.done, 1, 0);
			DIE(ret == 0, "last thread sem post err");
		}

		ret = ReleaseSemaphore(curr->in_exec, 1, 0);
		DIE(ret == 0, "curr last thread sem post err");

		return;
	}

	next = scheduler.q[scheduler.q_size - 1];

	/* if current thread is not yet init'd or is blocked/done */
	if (curr == NULL ||
		curr->state == STATE_WAITING ||
		curr->state == STATE_TERMINATED) {
		scheduler.curr_thread = next;
		run_thread_and_extract_from_prioq(next);
		return;
	}

	/* if thread with biggest prio has a bigger one than current thread */
	if (next->prio > curr->prio) {
		add_thread_to_sched(curr);
		scheduler.curr_thread = next;
		run_thread_and_extract_from_prioq(next);
		return;
	}

	/* if current thread finished his quantum time */
	if (curr->time_left <= 0) {
		if (curr->prio == next->prio) {
			add_thread_to_sched(curr);
			scheduler.curr_thread = next;
			run_thread_and_extract_from_prioq(next);
			return;
		}

		curr->time_left = scheduler.t_quant;
	}

	/* signaling new current thread to start */
	ret = ReleaseSemaphore(curr->in_exec, 1, 0);
	DIE(ret == 0, "last sem post err");
}

/* adds a new thread to the prio_q, based on its own prio */
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

/* initialises new thread structure and its data */
static struct thread *create_thread(so_handler *func, unsigned int priority)
{
	struct thread *t = (struct thread *) malloc(sizeof(*t));

	DIE(t == NULL, "thread malloc err");

	t->id = (DWORD) INVALID_TID;
	t->handler = func;
	t->event = SO_MAX_NUM_EVENTS;
	t->prio = priority;
	t->state = STATE_NEW;
	t->time_left = scheduler.t_quant;

	t->in_exec = CreateSemaphore(NULL, 0, 1, NULL);
	DIE(t->in_exec == NULL, "thread sem init err");

	t->hThread = CreateThread(
		NULL, 0, (LPTHREAD_START_ROUTINE) f_thread, t, 0, NULL);
	DIE(t->hThread == NULL, "create thread err");
	t->id = GetThreadId(t->hThread);

	return t;
}

/* starts a thread and eliminates the thread with biggest prio from q */
static void run_thread_and_extract_from_prioq(struct thread *t)
{
	int ret = 0;

	t->state = STATE_RUNNING;
	t->time_left = scheduler.t_quant;

	scheduler.q_size = scheduler.q_size - 1;
	scheduler.q[scheduler.q_size] = NULL;

	ret = ReleaseSemaphore(t->in_exec, 1, 0);
	DIE(ret == 0, "thread sem post err");
}
