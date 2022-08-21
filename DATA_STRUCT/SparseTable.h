#ifndef QE_DATA_STRUCT_SPARSETABLE_H
#define QE_DATA_STRUCT_SPARSETABLE_H
//------------------------------------------
#include <iostream>
#include <iterator>
#include <vector>

namespace QE {
template <typename type>
struct Min {
    bool operator()(type a, type b)
    {
        return std::min(a, b);
    }
};

template <typename type>
struct Max {
    bool operator()(type a, type b)
    {
        return std::max(a, b);
    }
};

}

//只可以求连续区间
namespace QE {
namespace DS {

    template <typename Vec, typename Compare>
    class ST {
    public:
        typedef typename Vec::value_type value_type;
        typedef typename Vec::iterator iterator;
        ST<Vec, Compare>(Vec vec);
        ST<Vec, Compare>(iterator first, iterator last);
        // value_type get(iterator first, iterator lalst);
        value_type get(int first, int lalst);

    private:
        int len_ = 0;
        std::vector<std::vector<value_type>> stable_;
    };

    template <typename Vec, typename Compare>
    ST<Vec, Compare>::ST(Vec vec)
        : ST<Vec, Compare>(vec.begin(), vec.end())
    {
    }

    template <typename Vec, typename Compare>
    ST<Vec, Compare>::ST(iterator first, iterator last)
    {
        while (first != last) {
            stable_.emplace_back(std::vector<value_type>(32));
            stable_[len_++][0] = *first;
            ++first;
        }

        for (int k = 1; (1 << k) <= len_; ++k) {
            for (int s = 0; s + (1 << k) - 1 < len_; ++s) {
                stable_[s][k] = Compare()(stable_[s][k - 1], stable_[s + (1 << (k - 1))][k - 1]);
            }
        }
    }

    template <typename Vec, typename Compare>
    typename ST<Vec, Compare>::value_type ST<Vec, Compare>::get(int first, int last)
    {

        value_type res = stable_[first][0];
        for (int k = 32; k >= 0; --k) {
            if (first + (1LL << k) - 1LL < last) {
                res = Compare()(res, stable_[first][k]);
                first += (1 << k);
            }
        }
        return res;
    }

}
}

//------------------------------------------
#endif