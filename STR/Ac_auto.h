#ifndef QE_STR_ACAUTO_H
#define QE_STR_ACAUTO_H
//-------------------------
#include <cassert>
#include <queue>
#include <string>
#include <vector>
namespace QE {
namespace STR {

    struct Tag1 {
        static constexpr char ST = 'a';
        static constexpr int SINGMA_SIZE = 26;
    };

    struct Tag2 {
        static const char ST = 'A';
        static constexpr int SINGMA_SIZE = 26;
    };

    struct Tag3 {
        static const char ST = ' ';
        static constexpr int SINGMA_SIZE = 96;
    };

    template <typename Tag>
    class AcAuto {

    public:
        AcAuto<Tag>()
        {
            tr_.emplace_back(std::vector<int>(SINGMA_SIZE));
            id_.emplace_back(std::vector<int>());
        }

        void insert(const std::string& str, int id);
        void build();
        void match(const std::string& str);
        const std::vector<std::vector<int>>& getEndPos() const
        {
            assert(matched == true);
            return endpos_;
        }

        const std::vector<int>& getCnt() const
        {
            assert(matched == true);
            return cnt_;
        }

    private:
        int tot_ = 0;
        int strnum = 0;
        bool matched = false;
        bool builded = false;
        std::vector<int> fail_; //失配边
        std::vector<int> last_; //上一个匹配结点
        std::vector<int> cnt_; //每个字符串出现的次数
        std::vector<std::vector<int>> id_; // 每个节点对应的字符串
        std::vector<std::vector<int>> endpos_; // 每个字符串出现的位置
        std::vector<std::vector<int>> tr_; // 树

    private:
        char ST = Tag::ST;
        int SINGMA_SIZE = Tag::SINGMA_SIZE;
    };

    template <typename Tag>
    void AcAuto<Tag>::insert(const std::string& str, int id)
    {
        ++strnum;
        assert(matched == false && builded == false);
        int v = 0;
        for (char x : str) {
            if (tr_[v][x - ST] == 0) {
                tr_[v][x - ST] = ++tot_;
                tr_.emplace_back(std::vector<int>(SINGMA_SIZE));
                id_.emplace_back(std::vector<int>());
            }
            v = tr_[v][x - ST];
        }
        id_[v].emplace_back(id);
    }

    template <typename Tag>
    void AcAuto<Tag>::build()
    {
        assert(matched == false && builded == false);
        builded = true;
        fail_.clear();
        fail_.resize(tot_ + 1);
        last_.clear();
        last_.resize(tot_ + 1);
        std::queue<int> que;
        for (int i = 0; i < SINGMA_SIZE; ++i) {
            if (tr_[0][i]) {
                que.push(tr_[0][i]);
            }
        }
        while (!que.empty()) {
            int r = que.front();
            que.pop();
            for (int c = 0; c < SINGMA_SIZE; ++c) {
                int u = tr_[r][c];
                if (!u) {
                    tr_[r][c] = tr_[fail_[r]][c];
                    continue;
                }
                que.push(u);
                int v = fail_[r];
                while (v && !tr_[v][c])
                    v = fail_[v];
                fail_[u] = tr_[v][c];
                last_[u] = id_[fail_[u]].empty() ? last_[fail_[u]] : fail_[u];
            }
        }
    }

    template <typename Tag>
    void AcAuto<Tag>::match(const std::string& str)
    {
        assert(builded == true && matched == false);
        matched = true;
        endpos_.resize(strnum);
        cnt_.resize(strnum);
        int v = 0;
        for (int i = 0, n = str.size(); i < n; ++i) {
            v = tr_[v][str[i] - ST];
            for (int k = (id_[v].empty() ? last_[v] : v); k; k = last_[k]) {
                for (int str_id : id_[k]) {
                    endpos_[str_id].push_back(i);
                    cnt_[str_id]++;
                }
            }
        }
    }
} // namespace STR
} // namespace QE

//-------------------------
#endif
