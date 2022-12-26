#ifndef ALGOLABS_QUICKSORT_HPP
#define ALGOLABS_QUICKSORT_HPP

#define ALGOLABS_QUICKSORT_SWITCH_VALUE 16

template<typename T, typename Compare>
void insert_sort(T* first, T* last, Compare comp) {
  for (T* i = first + 1; i <= last; ++i) {
    T iVal = *i;
    T* j = i - 1;
    while (j >= first && comp(iVal, *j)) {
      *(j + 1) = std::move(*j);
      --j;
    }
    *(j + 1) = iVal;
  }
}

template<typename T, typename Compare>
void quick_sort(T* first, T* last, Compare comp, bool withInsert = false) {
  while (first < last) {
    if (withInsert && (last - first) <= ALGOLABS_QUICKSORT_SWITCH_VALUE) {
      insert_sort(first, last, comp);
      return;
    }

    T* middle = first + (last - first) / 2;
    if (comp(*middle, *first)) {
      std::swap(*middle, *first);
    }
    if (comp(*last, *first)) {
      std::swap(*last, *first);
    }
    if (comp(*last, *middle)) {
      std::swap(*last, *middle);
    }

    T pivot = *middle;
    T* lhs = first;
    T* rhs = last;

    for (;;) {
      while (comp(*lhs, pivot)) {
        ++lhs;
      }
      while (comp(pivot, *rhs)) {
        --rhs;
      }
      if (lhs >= rhs) {
        break;
      }
      std::swap(*lhs++, *rhs--);
    }

    if (last - rhs > rhs - first) {
      quick_sort(first, rhs, comp);
      first = rhs + 1;
    } else {
      quick_sort(rhs + 1, last, comp);
      last = rhs;
    }
  }
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
  quick_sort(first, last, comp, true);
}

#endif //ALGOLABS_QUICKSORT_HPP
