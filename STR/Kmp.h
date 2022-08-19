#ifndef QE_STR_KMP_H
#define QE_STR_KMP_H
//-------------------------------------------
#include <string>
#include <vector>

namespace QE {
namespace STR {

    class Kmp {
    public:
        static std::vector<int> kmp_next(const std::string& pat);
        static std::vector<int> kmp_match(const std::string& str,
            const std::string& pat,
            std::vector<int>& next_);
        static std::vector<int> match(const std::string& str, const std::string& pat);
    };

    inline std::vector<int> Kmp::kmp_next(const std::string& pat)
    {
        std::vector<int> next_(pat.size());
        next_[0] = 0;
        for (int i = 1, n = pat.size(); i < n; ++i) {
            int pre = next_[i - 1];
            while (pre && pat[pre] != pat[i])
                pre = next_[pre - 1];
            if (pat[pre] == pat[i])
                next_[i] = pre + 1;
            else
                next_[i] = 0;
        }
        return next_;
    }

    inline std::vector<int> Kmp::kmp_match(const std::string& str, const std::string& pat, std::vector<int>& next_)
    {
        std::vector<int> match_pos;
        int pos_ = 0, end_ = pat.size();
        for (int i = 0, n = str.size(); i < n; ++i) {
            while (pos_ && str[i] != pat[pos_])
                pos_ = next_[pos_ - 1];
            if (str[i] == pat[pos_]) {
                if (++pos_ == end_) {
                    match_pos.push_back(i - end_ + 1);
                    pos_ = next_[pos_ - 1];
                }
            } else {
                pos_ = 0;
            }
        }
        return match_pos;
    }

    inline std::vector<int> Kmp::match(const std::string& str, const std::string& pat)
    {
        auto vec = Kmp::kmp_next(pat);
        return Kmp::kmp_match(str, pat, vec);
    }

}
}

//-------------------------------------------
#endif