#include <unistd.h>

#include "core.h"

auto getTotalSystemMemory() -> uint64 {
  int64 pages = sysconf(_SC_PHYS_PAGES);
  int64 page_size = sysconf(_SC_PAGE_SIZE);
  return pages * page_size;
}
