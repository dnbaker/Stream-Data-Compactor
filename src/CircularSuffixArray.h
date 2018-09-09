#ifndef _CIRCULARSUFFIXARRAY_H_
#define _CIRCULARSUFFIXARRAY_H_

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <numeric>
#include "Quick3stringEx.h"

namespace bw {
    class CircularSuffixArray {
            std::size_t len;
            std::vector<int> idx;
            std::string b;

        public:
            CircularSuffixArray(const std::string &s)  // circular suffix array of s
                :len(s.size())
                ,idx(len)
            {
                b.reserve(len << 1);
                b += s; b += s;
                std::iota(idx.begin(), idx.end(), 0);

                Quick3stringEx quick3Str;

                quick3Str.sort(idx, b);
            }
            std::size_t length() const           // length of s
            {
                return len;
            }
            int index(int i) const          // returns index of ith sorted suffix
            {
#if !NDEBUG
                return idx.at(i);
#else
                return idx[i];
#endif
            }
            std::string strIndex(int i) const     // return string on index by copying
            {
                return b.substr(index(i), len + index(i));
            }
            void clear() {
                {
                    std::vector<int> tmp;
                    std::swap(tmp, idx);
                }
                {
                    std::string tmp;
                    std::swap(b, tmp);
                }
            }
    };
}
#endif
