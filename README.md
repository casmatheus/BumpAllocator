# A Minimal Bump Allocator

## Project Overview

A Bump allocator that is based on a pool. The First Time `bump_alloc.h` is Included and only then, `BA_IMPL` must be defined.
The Library does not rely on libc by default, it will only do so if the user defines `BA_USE_LIBC`.

### Time Complexities:

- **Allocation is O(1)**
- **Reset is O(1)**

### Functions

- `baInit(BaPool* pool, uint64_t total_size)`: Initializes the Bump Allocator Pool with a Specified Total Size, Call this Before Any Other Library Functions.

- `baAlloc(BaPool* pool, uint64_t size)`: Allocates Memory of the Specified Ammount of Memory From The Pool.

- `baReset(BaPool* pool)`: Resets the Pool, Does not Set Memory to 0.

- `baDestroy(BaPool* pool)`: Frees the Pool.

## Testing

Testing BumpAllocator is as Simple as Running `test.bat`

Currently, The Library Has Only Been Tested on Windows.

## Copyright and License

```plaintext
Copyright (c) 2023 Matheus Cardoso (casmatheus44@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
