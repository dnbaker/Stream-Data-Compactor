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
        private:
            std::size_t len;
            std::shared_ptr<std::vector<int>> idx;
            std::shared_ptr<std::string> b;

        public:
            CircularSuffixArray(const std::string &s)  // circular suffix array of s
                :len(s.size())
                ,idx(std::make_shared<std::vector<int>>(len))
                ,b(std::make_shared<std::string>(s+s))
            {
                b->reserve(len << 1);
                *b += s; *b += s;
                std::iota(idx->begin(), idx->end(), 0);

                Quick3stringEx quick3Str;

                quick3Str.sort((*idx), (*b));
            }
            std::size_t length() const           // length of s
            {
                return len;
            }
            int index(unsigned i)               // returns index of ith sorted suffix
            {   if (i < 0 || i >= len)
                throw std::invalid_argument("Out of range");
                return idx->operator[](i);
            }
            std::string strIndex(int i)        // return string on index
            {
                return b->substr(idx->at(i), len + idx->at(i));
            }
    };
}
#endif
