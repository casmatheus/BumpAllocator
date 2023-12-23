/*
 * Copyright (c) 2023 Matheus Cardoso (casmatheus44@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * A Bump Allocator That is Based on A Pool.
 *
 * The First time this file is included and ONLY Then, BA_IMPL should be Defined.
 *
 * BumpAlloc does Not Rely on libc by Default;
 * It Will Only do so if the User Defines BA_USE_LIBC.
 *
 *
 * Reset is Always O(1).
 * Reset Does Not Imply the Memory is Zeroed!
 * The Pool Can be Reset Whenever The User May Wish.
 * Memory Reutilization is Implied After a Reset.
 *
 * Allocation is Always O(1) if it fits in the Pool, Returns NULL Otherwise.
 * Allocating Does NOT Imply the Memory is Zeroed!
 * You Must First Initiate the Pool before Allocating, Otherwise You Will Always Get NULL.
 *
 * Destroying the Pool is Always O(1).
 * Destroying does NOT Imply the Memory is Zeroed.
 *
 */

#ifndef BUMP_ALLOC_H_
#define BUMP_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct BaPool {
  uint64_t remaining_size;
  void* start;
  void* current;
} BaPool;

/* Initializes The Pool, Call this Before Any Other Functions */
void baInit(BaPool* pool, uint64_t total_size);

/* Allocates From The Pool, Make Sure to Call baInit() First */
void* baAlloc(BaPool* pool, uint64_t size);

/* Resets The Pool, Does not Touch Any of The Memory, Does not Set it to 0 */
void baReset(BaPool* pool);

/* Frees The Memory Pool, Making it Unusable */
void baDestroy(BaPool* pool);

#ifdef BA_IMPL

/* Libc */
#ifdef BA_USE_LIBC
extern void* malloc(uint64_t size);
extern void free(void* ptr);

/* Windows */
#elif defined (_WIN32)
extern void* VirtualAlloc(void* lpAddress, uint64_t dwSize, uint32_t flAllocationType, uint32_t flProtect);
extern int VirtualFree(void* lpAddress, uint64_t dwSize, int dwFreeType);

/* Unix or Mac */
#elif defined (__unix__ || defined (__APPLE__))
extern void* mmap(void* addr, size_t length, int prot, int flags, int fd, int64_t offset);
extern int munmap(void* addr, size_t length);

#else
#error Platform not supported, Define BA_USE_LIBC.

#endif

static void* baInternalOsAlloc(uint64_t size) {
#ifdef BA_USE_LIBC
  return malloc(size);

#elif defined (_WIN32)
  return VirtualAlloc(0, size, 0x3000, 4);

#elif defined (__unix__) || defined (__APPLE__))
  /* Values and Definition Taken from musl libc */
  void* ret = mmap(0, size, 1 | 2, 0x2 | 0x20, -1, 0);
  if (ret == ((void*)-1)) {
    return NULL;
  }
  return ret;

#else
#error Platform not supported, Define BA_USE_LIBC.

#endif
}

static void baInternalOsFree(void* ptr) {
#ifdef BA_USE_LIBC
  free(ptr);

#elif defined (_WIN32)
  VirtualFree(ptr, 0, 0x8000);

#elif defined (__unix__) || defined (__APPLE__)
  munmap(ptr, 0);
#else

#error Platform Not Supported, Define BA_USE_LIBC.
#endif
}

void baInit(BaPool* pool, uint64_t total_size) {
  pool->start = baInternalOsAlloc(total_size);
  pool->current = pool->start;
  pool->remaining_size = total_size;
}

void* baAlloc(BaPool* pool, uint64_t size) {
  if (!pool->start) {
    return NULL;
  }

  if (pool->remaining_size < size) {
    return (void*)-1;
  }

  pool->remaining_size -= size;
  void* current = pool->current;
  pool->current = (char*)pool->current + size;
  return current;
}

void baReset(BaPool* pool) {
  pool->remaining_size = ((char*)(pool->current) - (char*)pool->start) + pool->remaining_size;
  pool->current = pool->start;
}

void baDestroy(BaPool* pool) {
  if (pool->start) {
    baInternalOsFree(pool->start);
    pool->start = NULL;
  }
}

#undef BA_IMPL
#endif /* BA_IMPL */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUMP_ALLOC_H_ */

