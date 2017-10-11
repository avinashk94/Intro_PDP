#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

#include <cilk/cilk.h>


const int MERGE_LIMIT = 65536 >> 2;


// can you improve this code?
template <typename InIter, typename OutIter>
void merge(InIter f1, InIter l1, InIter f2, InIter l2,
           OutIter res) {
  while ((f1 != l1) && (f2 != l2)) {
    *(res++) = (*f2 < *f1) ? *(f2++) : *(f1++);
  }

  std::copy(f1, l1, res);
  std::copy(f2, l2, res);
} // merge

template <typename InIter, typename OutIter>
void merge_dc(InIter f1, InIter l1, InIter f2, InIter l2,
              OutIter res) {
  if ((l1 - f1) + (l2 - f2) < MERGE_LIMIT) {
    return merge(f1, l1, f2, l2, res);
  }

  InIter mid1, mid2;

  if ((l2 - f2) < (l1 - f1)) {
    mid1 = f1 + ((l1 - f1) >> 1);
    mid2 = std::lower_bound(f2, l2, *mid1);
  }
  else {
    mid2 = f2 + ((l2 - f2) >> 1);
    mid1 = std::lower_bound(f1, l1, *mid2);
  }

  cilk_spawn merge_dc(f1, mid1, f2, mid2, res);
  merge_dc(mid1, l1, mid2, l2, res + (mid1 - f1) + (mid2 - f2));
} // merge_dc

template <typename InIter, typename OutIter>
void merge_sr(InIter f1, InIter l1, InIter f2, InIter l2,
              OutIter res) {
  while ((l1 - f1) + (l2 - f2) >= MERGE_LIMIT) {
    InIter mid1, mid2;
    if ((l2 - f2) < (l1 - f1)) {
      mid1 = f1 + ((l1 - f1) >> 1);
      mid2 = std::lower_bound(f2, l2, *mid1);
    }
    else {
      mid2 = f2 + ((l2 - f2) >> 1);
      mid1 = std::lower_bound(f1, l1, *mid2);
    }
    cilk_spawn merge_sr(f1, mid1, f2, mid2, res);
    res += (mid1 - f1) + (mid2 - f2);
    f1 = mid1;
    f2 = mid2;
  }

  merge(f1, l1, f2, l2, res);
} // merge_sr

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " size" << std::endl;
        return -1;
    }

    long int n = std::atoi(argv[1]);

    std::vector<int> x(n);
    std::vector<int> y(n);

    std::iota(x.begin(), x.end(), 0);
    std::iota(y.begin(), y.end(), 0);

    std::vector<int> res(2 * n);
    std::cout << "res.size() = " << res.size() << std::endl;

    std::cout << "go!" << std::endl;

    auto t0 = std::chrono::system_clock::now();

    merge(x.begin(), x.end(), y.begin(), y.end(), res.begin());
    //merge_dc(x.begin(), x.end(), y.begin(), y.end(), res.begin());
    //merge_sr(x.begin(), x.end(), y.begin(), y.end(), res.begin());

    auto t1 = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration<double>(t1 - t0);
    std::cout << "time: " << elapsed.count() << "s" << std::endl;

    std::cout << "is sorted: " << std::is_sorted(res.begin(), res.end()) << std::endl;
    std::cout << res[0] << " " << res[n] << " " << res[2 * n - 1] << std::endl;

    return 0;
} // main
