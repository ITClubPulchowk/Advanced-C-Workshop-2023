#pragma once

#include <assert.h>
#include <stdint.h>

#if defined(_MSC_VER)

#define NOMINMAX
#include <Windows.h>
#include <process.h>

#define thread_local __declspec(thread)

#define SOFTWARE_BARRIER _ReadWriteBarrier();
#define HARDWARE_BARRIER MemoryBarrier();

typedef HANDLE thrd_t;
typedef int32_t(*thrd_start_t)(void *);

enum {
	thrd_success,
	thrd_nomem,
	thrd_timedout,
	thrd_busy,
	thrd_error,
};


static inline int thrd_create(thrd_t *thr, thrd_start_t func, void *arg) {
	*thr = (thrd_t*)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)func, arg, 0, NULL);
	if (*thr != INVALID_HANDLE_VALUE)
		return thrd_success;
	return thrd_error;
}

static inline int thrd_join(thrd_t thr, int *res) {
	DWORD result = WaitForSingleObject(thr, INFINITE);

	if (res) {
		DWORD code = 0;
		GetExitCodeThread(thr, &code);
		*res = (int)code;
	}

	if (result != WAIT_FAILED)
		return thrd_success;
	return thrd_error;
}

static inline int thrd_detach(thrd_t *thr) {
	if(CloseHandle(thr)) return thrd_success;
	return thrd_error;
}

static inline void thrd_sleep_millisecs(uint32_t millisecs) {
	Sleep(millisecs);
}


//
//
//

typedef HANDLE mtx_t;

enum {
	mtx_plain,
	mtx_recursive,
	mtx_timed
};

static inline int mtx_init(mtx_t *mutex, int type) {
	// We don't support *mtx_recursive*, you probably don't need *mtx_recursive* anyway
	assert(type != mtx_recursive);

	*mutex = CreateMutexA(NULL, FALSE, NULL);
	if (*mutex != INVALID_HANDLE_VALUE)
		return thrd_success;

	return thrd_error;
}

static inline void mtx_destroy(mtx_t *mutex) {
	CloseHandle(*mutex);
}

static inline int mtx_lock(mtx_t *mutex) {
	DWORD result = WaitForSingleObject(*mutex, INFINITE);
	if (result != WAIT_FAILED)
		return thrd_success;
	return thrd_error;
}

static inline int mtx_unlock(mtx_t *mutex) {
	if (ReleaseMutex(*mutex))
		return thrd_success;
	return thrd_error;
}

#else
#include <threads.h>

#define SOFTWARE_BARRIER asm volatile("": : :"memory");
#define HARDWARE_BARRIER __sync_synchronize();

static inline void thrd_sleep_millisecs(uint32_t millisecs) {
	uint32_t secs = millisecs / 1000;
	millisecs -= 1000 * secs;
	uint32_t nano_secs = 1000000 * millisecs;
	thrd_sleep(&(struct timespec) { .tv_sec = secs, .tv_nsec = nano_secs }, NULL);
}

#endif

#if defined(_MSC_VER)
static inline uint32_t interlocked_inc(uint32_t volatile *addend) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedIncrement((void *)addend);
#else
	return _InterlockedIncrement(addend);
#endif
}

static inline uint32_t interlocked_dec(uint32_t volatile *addend) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedDecrement((void *)addend);
#else
	return _InterlockedDecrement(addend);
#endif
}

static inline uint32_t interlocked_add(uint32_t volatile *added, uint32_t value) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedExchangeAdd((void *)added, value);
#else
	return _InterlockedExchangeAdd(added, value);
#endif
}

static inline uint32_t interlocked_cmpxchg(uint32_t volatile *dst, uint32_t exchange, uint32_t comperand) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedCompareExchange((void *)dst, exchange, comperand);
#else
	return _InterlockedCompareExchange(dst, exchange, comperand);
#endif
}

// 64-bit versions
static inline uint64_t interlocked_inc64(uint64_t volatile *addend) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedIncrement64((void *)addend);
#else
	return _InterlockedIncrement64(addend);
#endif
}

static inline uint64_t interlocked_dec64(uint64_t volatile *addend) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedDecrement64((void *)addend);
#else
	return _InterlockedDecrement64(addend);
#endif
}

static inline uint64_t interlocked_add64(uint64_t volatile *added, uint64_t value) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedExchangeAdd64((void *)added, value);
#else
	return _InterlockedExchangeAdd64(added, value);
#endif
}

static inline uint64_t interlocked_cmpxchg64(uint64_t volatile *dst, uint64_t exchange, uint64_t comperand) {
#if defined(__clang__) || defined(__ibmxl__)
	return _InterlockedCompareExchange64((void *)dst, exchange, comperand);
#else
	return _InterlockedCompareExchange64(dst, exchange, comperand);
#endif
}

#else

static inline uint32_t interlocked_inc(uint32_t volatile *addend) {
	return __sync_fetch_and_add(addend, 1) + 1;
}

static inline uint32_t interlocked_dec(uint32_t volatile *addend) {
	return __sync_fetch_and_sub(addend, 1) - 1;
}

static inline uint32_t interlocked_add(uint32_t volatile *addend, uint32_t value) {
	return __sync_fetch_and_add(addend, value);
}

static inline uint32_t interlocked_cmpxchg(uint32_t volatile *dst, uint32_t exchange, uint32_t comperand) {
	return __sync_val_compare_and_swap(dst, comperand, exchange);
}

// 64-bit versions
static inline uint64_t interlocked_inc64(uint64_t volatile *addend) {
	return __sync_fetch_and_add(addend, 1) + 1;
}

static inline uint64_t interlocked_dec64(uint64_t volatile *addend) {
	return __sync_fetch_and_sub(addend, 1) - 1;
}

static inline uint64_t interlocked_add64(uint64_t volatile *addend, uint64_t value) {
	return __sync_fetch_and_add(addend, value);
}

static inline uint64_t interlocked_cmpxchg64(uint64_t volatile *dst, uint64_t exchange, uint64_t comperand) {
	return __sync_val_compare_and_swap(dst, comperand, exchange);
}
#endif


//
//
//

#if defined(__gnu_linux__) || defined(__linux__) || defined(linux) || defined(__linux)

#include <time.h>

static inline uint64_t clock_counts_now() {
	return (uint64_t)clock();
}

static inline uint64_t clock_frequency() {
	return CLOCKS_PER_SEC;
}

static inline float clock_time(uint64_t counts) {
	return 1000.0f * ((float)(counts)) / CLOCKS_PER_SEC;
}

#elif defined(_WIN64) || defined(_WIN32)

static inline uint64_t clock_counts_now() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return count.QuadPart;
}

static inline uint64_t clock_frequency() {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return freq.QuadPart;
}

static inline float clock_time(uint64_t counts) {
	uint64_t freq = clock_frequency();
	return (1000000.0f * (float)(counts) / (float)freq) / 10000.0f;
}


#else
#	error Unsupported Operating System
#endif



#if defined(__gnu_linux__) || defined(__linux__) || defined(linux) || defined(__linux)

#include <semaphore.h>

#elif defined(_WIN64) || (_WIN32)

#include <Windows.h>
#include <time.h>

typedef HANDLE sem_t;
#define SEM_VALUE_MAX INT_MAX


static inline int sem_init(sem_t *sem, int pShared, unsigned value) {
	*sem = CreateSemaphore(0, (LONG)value, SEM_VALUE_MAX, 0);
	if(!(*sem))
		return 0;
	return -1;
}

static inline int sem_post(sem_t *sem) {
	if(ReleaseSemaphore(*sem, 1, 0))
		return 0;
	return -1;
}

static inline int sem_wait(sem_t *sem) {
	DWORD res = WaitForSingleObject(*sem, INFINITE);
	if(res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
		return 0;
	else
		return -1;
}

static inline int sem_trywait(sem_t *sem) {
	DWORD res = WaitForSingleObject(*sem, 0);
	if(res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
		return 0;
	else
		return -1;
}

static inline int sem_timedwait(sem_t *sem, const struct timespec *abstime) {
	DWORD ms = abstime->tv_sec * 1000 + (abstime->tv_nsec / 1000000L);
	DWORD res = WaitForSingleObject(*sem, ms);
	if(res == WAIT_OBJECT_0 || res == WAIT_ABANDONED)
		return 0;
	else
		return -1;
}

static inline int sem_destroy(sem_t *sem) {
	if(CloseHandle(*sem))
		return 0;
	return -1;
}

#endif