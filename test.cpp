#include "STR/Ac_auto.h"
#include "STR/Manacher.h"
#include <iostream>
#include <vector>
using namespace ::std;
using namespace QE;
using namespace QE::STR;

int main()
{
    int n = 0;
    while (cin >> n) {
        if(n==0) return 0;
        AcAuto<Tag1> Ac;
        vector<string> strvec(n);
        for(int i=0;i<n;++i){
            cin>>strvec[i];
            Ac.insert(strvec[i], i);
        }
        string str;
        cin>>str;
        Ac.build();
        Ac.match(str);
        const auto cnt=Ac.getCnt();
        int ans;
        vector<int> rs;
        for(int i=0;i<n;++i){
           cout<<cnt[i]<<endl;
        }
        
    }
    return 0;
}