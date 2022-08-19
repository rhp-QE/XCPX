#ifndef QE_STR_MANACHER_H
#define QE_STR_MANACHER_H
//------------------------------------------
#include <cstddef>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

namespace QE {

namespace STR {

    class Manacher {
    public:
        static std::vector<int> manacher(const std::string& str);
    };

    inline std::vector<int> Manacher::manacher(const std::string& str)
    {
        char* strr = (char*)malloc(static_cast<size_t>((str.size() + 1) * 2));
        strr[0] = '$', strr[1] = '#';
        int pos = 2;
        for (char x : str) {
            strr[pos++] = x;
            strr[pos++] = '#';
        }

        std::vector<int> R(pos);
        std::vector<int> res(str.size() + 1);
        // R[i]: 以该位置为中心的回文串半径（带中心位置）
        R[0] = 1;
        int mid = 0, r = 1;
        for (int i = 1; i < pos; ++i) {
            if (i < mid + r) {
                R[i] = std::min(R[mid * 2 - i], mid + r - i);
            }
            while (i + R[i] < pos && strr[i + R[i]] == strr[i - R[i]]) {
                ++R[i];
            }

            if (i + R[i] > mid + r) {
                mid = i;
                r = R[i];
            }

            //回文串: k  原字符串的起始位置。 ln： 该位置回文串的长度
            int k = (i - R[i] + 1) / 2, ln = R[i] - 1;
            res[k] = std::max(res[k], ln);
        }
        free(strr);
        return res;
    }

    //------------------------------------------

}
}

#endif