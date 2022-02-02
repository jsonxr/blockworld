#ifdef APP_UTILS_TRACER_H_DEBUG // Only include if we want to try and learn some cpp memory things
#ifndef APP_UTILS_TRACER_H
#define APP_UTILS_TRACER_H

#include <algorithm>
#include <cstdio>

static int tracer_count{};

struct Tracer {
  Tracer() : name_("default"), count_(++tracer_count) {
    printf("%d - Constructor: Tracer() - %s\n", count_, name_);
  }
  Tracer(const char *name) : name_{name}, count_(++tracer_count) {
    printf("%d - Constructor: Tracer(const char* name_) - %p->%s\n", count_, name_, name_);
  }

  ~Tracer() { printf("%d - Destructor: ~Tracer() - %p->%s\n", count_, name_, name_); }

  Tracer(const Tracer &other)
      : name_(other.name_), count_(++tracer_count) {  // copy constructor
    printf("%d - Copy Constructor: Tracer(const Tracer &other) - %p->%s to %s\n",
           count_, name_, name_, other.name_);
    name_ = other.name_;
  }

  auto operator=(const Tracer &other) -> Tracer & {  // copy assignment
    if(this == &other) {
      printf(
          "%d - Copy Assignment: auto operator=(const Tracer &other) - %p->%s skip!!!\n",
          count_, name_, name_);
      return *this;
    }
    printf(
        "%d - Copy Assignment: auto operator=(const Tracer &other) - %p->%s to %s\n",
        count_, name_, name_, other.name_);
    this->name_ = other.name_;
    return *this;
  }

  Tracer(Tracer &&other) noexcept : count_(++tracer_count) {  // move...
    printf("%d - Move Constructor: Tracer(Tracer &&other) - %p->%s to %s\n", count_,
           name_, name_, other.name_);
    std::swap(name_, other.name_);
  }
  auto operator=(Tracer &&other) noexcept -> Tracer & {
    printf("%d - Move Assignment: Tracer(Tracer &&other) - %p->%s to %s\n", count_,
           name_, name_, other.name_);
    std::swap(name_, other.name_);
    return *this;
  }
  auto count() const -> int { return count_; }
  auto name() const -> const char* { return name_; }

 private:
  const char *name_{nullptr};
  int const count_{0};
};

auto stack_return(const char *name) -> Tracer {
  Tracer t{name};
  return t;
}

//------------------------------------------------------------------------------
// Learn functions
//------------------------------------------------------------------------------

auto unique_return(const char *name) -> std::unique_ptr<Tracer> {
  auto t = std::make_unique<Tracer>(name);
  return t;
}

void print_tracer(const Tracer &t) {
  auto name = t.name();
  auto count = t.count();
  printf("%d - print_tracer %s\n", count, name);
}

auto test_memory() -> int {
  Tracer t1{};
  Tracer t3 = stack_return("t3");
  auto t4 = unique_return("t4");
  print_tracer(*t4);
  Tracer t5 = std::move(t3);
  t1 = t1;
  t1 = t5;
  t3 = t5;
  t1 = t3;
  return 0;
}


#endif  // APP_UTILS_TRACER_H
#endif // APP_UTILS_TRACER_H_DEBUG
