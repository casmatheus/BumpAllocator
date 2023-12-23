#define TEST_H_IMPL
#include "test.h"
#define BA_IMPL
#include "../bump_alloc.h"

int main(void) {
  BaPool pool = {0};
  uint64_t total_size = 1024;

  TestBegin("Pool Initialization");
  baInit(&pool, total_size);
  Assert(pool.start);

  TestBegin("Allocation");
  char* ptr1 = baAlloc(&pool, 100);
  char* ptr2 = baAlloc(&pool, 200);
  Assert(ptr1);
  Assert(ptr2);

  TestBegin("Reseting");
  baReset(&pool);
  Assert(pool.start);
  char* ptr3 = baAlloc(&pool, 300);
  Assert(ptr1 == ptr3);
  
  TestBegin("Destruction");
  baDestroy(&pool);
  Assert(!pool.start);


  return 0;
}
