#include "gtest/gtest.h"
#include "quicksort.hpp"
#include <iostream>

#define TEST_ARRAY_SIZE 100
#define TEST_ARRAY_SLICES 50
#define NS_PER_SECOND 1000000000

class SortsFixture : public ::testing::Test {
protected:
  int array[TEST_ARRAY_SIZE];

  virtual void SetUp() {
    for (int i = 0; i < TEST_ARRAY_SIZE; i++) {
      array[i] = i;
    }

    std::random_shuffle(std::begin(array), std::end(array));
  }
};

TEST_F(SortsFixture, InsertSort) {
  insert_sort(std::begin(array), std::end(array), [](int a, int b) { return a < b; });

  for (int i = 0; i < TEST_ARRAY_SIZE; ++i) {
    EXPECT_EQ(array[i], i);
  }
}

TEST_F(SortsFixture, QuickSort) {
  quick_sort(std::begin(array), std::end(array), [](int a, int b) { return a < b; });

  for (int i = 0; i < TEST_ARRAY_SIZE; ++i) {
    EXPECT_EQ(array[i], i);
  }
}

TEST_F(SortsFixture, Sort) {
  sort(std::begin(array), std::end(array), [](int a, int b) { return a < b; });

  for (int i = 0; i < TEST_ARRAY_SIZE; ++i) {
    EXPECT_EQ(array[i], i);
  }
}

class ChronoFixture : public SortsFixture {
protected:
  int intersec;
  bool table[TEST_ARRAY_SLICES];
  void arrayFill(int capacity = TEST_ARRAY_SIZE) {
    capacity = capacity > TEST_ARRAY_SIZE ? TEST_ARRAY_SIZE : capacity;
    for (int i = 0; i < capacity; ++i) {
      array[i] = i;
    }
  }

  virtual void SetUp() {
    arrayFill();
    intersec = -1;
  }

  template<typename F>
  long chrono_sort(F sort_func, int offset) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::nanoseconds;

    struct timespec t1, t2, dt;
    clock_gettime(CLOCK_REALTIME, &t1);
    sort_func(array, array + offset);
    clock_gettime(CLOCK_REALTIME, &t2);

    dt.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    dt.tv_sec = t2.tv_sec - t1.tv_sec;

    if (dt.tv_sec > 0 && dt.tv_nsec < 0)
    {
      dt.tv_nsec += NS_PER_SECOND;
      dt.tv_sec--;
    }
    else if (dt.tv_sec < 0 && dt.tv_nsec > 0)
    {
      dt.tv_nsec -= NS_PER_SECOND;
      dt.tv_sec++;
    }

    long ret = dt.tv_sec * NS_PER_SECOND + dt.tv_nsec;
    return ret;
  }
};

TEST_F(ChronoFixture, AlreadySorted) {
  arrayFill(TEST_ARRAY_SIZE);
  int j = 0;

  for (int i = 10; i < TEST_ARRAY_SIZE; ++i) {
    int quick_t = chrono_sort([](int* first, int* last) {
      quick_sort(first, last, [](int a, int b) { return a < b; });
    }, i);
    int insert_t = chrono_sort([](int* first, int* last) {
      insert_sort(first, last, [](int a, int b) { return a < b; });
    }, i);

    if (quick_t < insert_t && intersec == -1) {
      intersec = i;
    }

    if (i % ((TEST_ARRAY_SIZE - 10) / TEST_ARRAY_SLICES) == 0) {
      table[j++] = quick_t < insert_t;
    }

    std::cout << i << ';' << quick_t << ';' << insert_t << ';' << std::endl;
  }

  if (intersec > -1) {
    std::cout << "Found intersection: " << intersec << std::endl;
  }
  for (bool i : table) {
    std::cout << (i ? 'Q' : 'I'); // TODO: График, всё же
  }
  std::cout << std::endl;
}

TEST_F(ChronoFixture, BackwardSorted) {
  int j = 0;
  for (int i = 10; i < TEST_ARRAY_SIZE; ++i) {
    for (int j = 0; j < i; ++j) {
      array[i - j - 1] = j;
    }

    int quick_t = chrono_sort([](int* first, int* last) {
      quick_sort(first, last, [](int a, int b) { return a < b; });
    }, i);

    for (int j = 0; j < i; ++j) {
      array[i - j - 1] = j;
    }

    int insert_t = chrono_sort([](int* first, int* last) {
      insert_sort(first, last, [](int a, int b) { return a < b; });
    }, i);

    if (quick_t < insert_t && intersec == -1) {
      intersec = i;
    }

    if (i % ((TEST_ARRAY_SIZE - 10) / TEST_ARRAY_SLICES) == 0) {
      table[j++] = quick_t < insert_t;
    }

    std::cout << i << ';' << quick_t << ';' << insert_t << ';' << std::endl;
  }

  if (intersec > -1) {
    std::cout << "Found intersection: " << intersec << std::endl;
  }
  for (bool i : table) {
    std::cout << (i ? 'Q' : 'I');
  }
  std::cout << std::endl;
}
