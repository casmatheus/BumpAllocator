#include <stdio.h>
#include <assert.h>

#define BA_IMPL
#include "bump_alloc.h"

int main(void) {
  BaPool pool = {0};

  uint64_t total_size = 1024;
  baInit(&pool, total_size);
  if (!pool.start) {
    printf("Failed to Allocate Pool");
    return 1;
  }

  char* ptr1 = baAlloc(&pool, 100);

  char* ptr2 = baAlloc(&pool, 200);

  if (ptr1 && ptr2) {
    for (int i = 0; i < 100; i++) ptr1[i] = 1;
    for (int i = 0; i < 200; i++) ptr2[i] = 2;
    printf("Allocated memory at 0x%p and 0x%p\n", ptr1, ptr2);

    baReset(&pool);
    printf("Pool reset\n");

    char* ptr3 = baAlloc(&pool, 1024);
    if (ptr3) {
      for (int i = 0; i < 1024; i++) ptr3[i] = 3;
      printf("Allocated memory at 0x%p after reset\n", ptr3);
    } else {
      printf("Allocation after reset failed\n");
      baDestroy(&pool);
      return 1;
    }
  } else {
    printf("Failed to Allocate From Pool\n");
    baDestroy(&pool);
    return 1;
  }

  baDestroy(&pool);
  printf("Test Successfull\n");

  return 0;
}
