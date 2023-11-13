# philo
Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

## Intro to Threads
> Source: The-Linux-programming-interface, CH 29

In modern UNIX implementations, each process can have multiple threads of execution. One way of envisaging threads is as a set of processes that share the same virtual memory, as well as a range of other attributes. Each thread is executing the same program code and shares the same data area and heap, However, each thread has its own stack containing local variables and function call linkage information.
Threads can communicate with each other via the global variables that they
share. The threading API provides condition variables and mutexes, which are primitives that enable the threads of a process to communicate and synchronize their actions, in particular, their use of shared variables. Threads can also communicate with one another using the IPC and synchronization mechanisms.
The primary advantages of using threads are that they make it easy to share
data between cooperating threads and that some algorithms transpose more naturally to a multithreaded implementation than to a multi-process implementation. Furthermore, a multithreaded application can transparently take advantage of the possibilities for parallel processing on multiprocessor hardware.

<img width="982" alt="1" src="https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/a06f9e2f-25b8-4f7f-a4c7-00741d65c35b">

Besides global memory, threads also share a number of other attributes (i.e., these
attributes are global to a process, rather than specific to a thread). These attributes
include the following:

- process ID and parent process ID.
- process group ID and session ID.
- controlling terminal.
- process credentials (user and group IDs).
- open file descriptors.
- record locks created using **fcntl()**.
- signal dispositions.
- file system-related information: umask, current working directory, and root directory.
- interval timers (**setitimer()**) and POSIX timers (timer_create()).
- System V semaphore undo (semadj) values.
- resource limits.
- CPU time consumed (as returned by times()).
- resources consumed (as returned by **getrusage()**).
- nice value (set by **setpriority()** and nice()).

Among the attributes that are distinct for each thread are the following:

- thread ID (Section 29.5).
- signal mask.
- thread-specific data (Section 31.3).
- alternate signal stack (**sigaltstack()**).
- the errno variable.
- floating-point environment (see **fenv(3)**).
- realtime scheduling policy and priority (Sections 35.2 and 35.3).
- CPU affinity (Linux-specific, described in Section 35.4).
- capabilities (Linux-specific, described in Chapter 39).
- stack (local variables and function call linkage information).

### Threads and errno:

In the traditional UNIX API, errno is a global integer variable. However, this
doesn’t suffice for threaded programs. If a thread made a function call that
returned an error in a global errno variable, then this would confuse other threads
that might also be making function calls and checking errno. In other words, race
conditions would result. Therefore, in threaded programs, each thread has its own
errno value. On Linux, a thread-specific errno is achieved in a similar manner to
most other UNIX implementations: errno is defined as a macro that expands into a
function call returning a modifiable lvalue that is distinct for each thread. (Since
the lvalue is modifiable, it is still possible to write assignment statements of the
form errno = value in threaded programs.).

### Return value from Pthreads functions:

The traditional method of returning status from system calls and some library functions is to return 0 on success and –1 on error, with errno being set to indicate the
error. The functions in the Pthreads API do things differently. All Pthreads functions return 0 on success or a positive value on failure. The failure value is one of
the same values that can be placed in errno by traditional UNIX system calls.
Because each reference to errno in a threaded program carries the overhead of
a function call, our example programs don’t directly assign the return value of a
Pthreads function to errno. Instead, we use an intermediate variable and employ
our errExitEN() diagnostic function (Section 3.5.2), like so:

```c
pthread_t *thread;
int s;
s = pthread_create(&thread, NULL, func, &arg);
if (s != 0)
		errExitEN(s, "pthread_create");
```

### Compiling Pthreads programs

On Linux, programs that use the Pthreads API must be compiled with the cc –pthread
option. The effects of this option include the following:

- The _REENTRANT preprocessor macro is defined. This causes the declarations of a few reentrant functions to be exposed.
- The program is linked with the libpthread library (the equivalent of –lpthread).

### Thread Creation

When a program is started, the resulting process consists of a single thread, called
the initial or main thread. In this section, we look at how to create additional
threads.

The pthread_create() function creates a new thread.

<img width="1216" alt="2" src="https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/284758bf-7978-47c6-baf8-7f3bc2b84d66">

The new thread commences execution by calling the function identified by start
with the argument arg (i.e., start(arg)). The thread that calls pthread_create() continues
execution with the next statement that follows the call. (This behavior is the same as
the glibc wrapper function for the clone() system call described in Section 28.2.)
The arg argument is declared as void *, meaning that we can pass a pointer to
any type of object to the start function. Typically, arg points to a global or heap variable, but it can also be specified as NULL. If we need to pass multiple arguments to
start, then arg can be specified as a pointer to a structure containing the arguments
as separate fields.

### Thread Termination

The execution of a thread terminates in one of the following ways:

- The thread’s start function performs a return specifying a return value for the
thread.
- The thread calls pthread_exit() (described below).
- The thread is canceled using pthread_cancel() (described in Section 32.1).
- Any of the threads calls exit(), or the main thread performs a return (in the
main() function), which causes all threads in the process to terminate immediately.

The pthread_exit() function terminates the calling thread and specifies a return
value that can be obtained in another thread by calling pthread_join().

### Joining with a Terminated Thread

The pthread_join() function waits for the thread identified by thread to terminate. (If
that thread has already terminated, pthread_join() returns immediately.) This operation is termed joining.

<img width="975" alt="3" src="https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/82361800-55f1-4e0a-94d0-c68f43098341">

If retval is a non-NULL pointer, then it receives a copy of the terminated thread’s
return value—that is, the value that was specified when the thread performed a
return or called pthread_exit().
Calling pthread_join() for a thread ID that has been previously joined can lead
to unpredictable behavior; for example, it might instead join with a thread created
later that happened to reuse the same thread ID.

### Thread IDs

Each thread within a process is uniquely identified by a thread ID. This ID is
returned to the caller of pthread_create(), and a thread can obtain its own ID using
pthread_self().

<img width="970" alt="4" src="https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/12705152-f406-4d70-a805-1c6ebf6fd61d">

### Thread detaching

By default, a thread is joinable, meaning that when it terminates, another thread can obtain its return status using pthread_join(). Sometimes, we don’t care about the thread’s return status; we simply want the system to automatically clean up and remove the thread when it terminates. In this case, we can mark the thread as detached, by making a call to pthread_detach() specifying the thread’s identifier in a thread.

![5](https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/7f6a656c-7ec4-4934-b11b-cfd57316c42d)

Once a thread has been detached, it is no longer possible to use pthread_join() to obtain its return status, and the thread can’t be made joinable again.
Detaching a thread doesn’t make it immune to a call to exit() in another thread or a return in the main thread. In such an event, all threads in the process are immediately terminated, regardless of whether they are joinable or detached. To put things another way, pthread_detach() simply controls what happens after a thread terminates, not how or when it terminates.

If a thread is not detached then we must join with it using pthread_join(). If we fail to do this, then, when the thread terminates, it produces the thread equivalent of a zombie process. Aside from wasting system resources, if enough thread zombies accumulate, we won’t be able to create additional threads.



## Thread Synchronization
> Source: The-Linux-programming-interface, CH 30

There are two tools that threads can use to synchronize their actions: **mutexes** and **condition variables**. Mutexes allow threads to synchronize their use of a shared resource, so that, for example, one thread doesn’t try to access a shared variable simultaneously while another thread is modifying it. Condition variables perform a complementary task: they allow threads to info each other that a shared variable (or other shared resources) has changed state.

### Mutexes

One of the principal advantages of threads is that they can share information via global variables. However, this easy sharing comes at a cost: we must take care that multiple threads do not attempt to modify the same variable at the same time, or that one thread doesn’t try to read the value of a variable while another thread is modifying it. The term critical section is used to refer to a section of code that accesses a shared resource and whose execution should be atomic; that is, its execution should not be interrupted by another thread that simultaneously accesses the same shared resource.

To avoid the problems that can occur when threads try to update a shared variable, we must use a mutex (short for mutual exclusion) to ensure that only one thread at a time can access the variable. More generally, mutexes can be used to ensure atomic access to any shared resource, but protecting shared variables is the most common use.

A mutex has two states: locked and unlocked. At any moment, at most one thread may hold the lock on a mutex. Attempting to lock a mutex that is already locked either block or fails with an error, depending on the method used to place the lock.
When a thread locks a mutex, it becomes the owner of that mutex. Only the mutex owner can unlock the mutex. This property improves the structure of code that uses mutexes and also allows for some optimizations in the implementation of mutexes. Because of this ownership property, the terms acquire and release are sometimes used synonymously for lock and unlock.

In general, we employ a different mutex for each shared resource (which may consist of multiple related variables), and each thread employs the following protocol for accessing a resource:

- lock the mutex for the shared resource;
- access the shared resource; and
- unlock the mutex.

If multiple threads try to execute this block of code (a critical section), the fact that only one thread can hold the mutex (the others remain blocked) means that only one thread at a time can enter the block:

![1](https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/ccc39b5e-0014-46ff-be03-5c24c111327f)

### Locking and Unlocking a Mutex

After initialization, a mutex is unlocked. To lock and unlock a mutex, we use the
pthread_mutex_lock() and pthread_mutex_unlock() functions.

![2](https://github.com/Abdeljalil-Bouchfar/philo/assets/55533328/e6cb897a-5ccb-4682-a71a-ee256b710274)

To lock a mutex, we specify the mutex in a call to pthread_mutex_lock(). If the mutex is currently unlocked, this call locks the mutex and returns immediately. If the mutex is currently locked by another thread, then pthread_mutex_lock() blocks until the mutex is unlocked, at which point it locks the mutex and returns.
If the calling thread itself has already locked the mutex given to pthread_mutex_lock(), then, for the default type of mutex, one of two implementation-defined possibilities may result: the thread deadlocks, blocked trying to lock a mutex that it already owns, or the call fails, returning the error EDEADLK. On Linux, the thread deadlocks by default.
The pthread_mutex_unlock() function unlocks a mutex previously locked by the calling thread. It is an error to unlock a mutex that is not currently locked or to unlock a mutex that is locked by another thread.
If more than one other thread is waiting to acquire the mutex unlocked by a call to pthread_mutex_unlock(), it is indeterminate which thread will succeed in acquiring it.
