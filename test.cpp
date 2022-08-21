#include "STR/Ac_auto.h"
#include "STR/Manacher.h"
#include "DATA_STRUCT/SparseTable.h"
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>
using namespace ::std;
using namespace QE;
using namespace QE::STR;


int main()
{

    vector<int> vec{1,2,3,4,5,6};
    DS::ST<vector<int>, Min<int>> st(vec.begin(),vec.end());
    cout<<st.get(3,5)<<endl;
}