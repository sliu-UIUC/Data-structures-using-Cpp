#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<functional>
#include<utility>
#include<map>
#include "OrderStat.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::make_pair;
using std::boolalpha;

int main() {
        OrderStat<int,int> num;
        OrderStat<int,char> chr;
        OrderStat<int,string> str;

        cout<<"Test number values: \n"<<endl;
        cout<<"Emptyness before insert: "<<boolalpha<<num.empty()<<endl;
        cout<<"Size of number AVL before insert: "<<num.size()<<endl;
        for(int i = 0; i < 1000;i++) {
                numAVL.insert(make_pair(i,i));
        }
        cout<<"Emptyness after insert: "<<boolalpha<<num.empty()<<endl;
        cout<<"size after 1000 inserts: "<<num.size()<<endl;
        cout<<"Find element with the key 1: "<<num[1]<<endl;
        cout<<"Size after erase node with the key 1: "<<num.size()<<endl;
        cout<<"Number of elements with the key 1: "<<boolalpha<<num[1]<<endl;
        num.clear();
        cout<<"Emptyness after clear: "<<boolalpha<<num.empty()<<endl;
        cout<<"Number of elements after clear: "<<num.size()<<endl;

       cout<<"\nTest char values: \n"<<endl;
        char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        cout<<"Emptyness before insert: "<<chr.empty()<<endl;
        cout<<"Size before insert: "<<chr.size()<<endl;
        for(int a =0;a<=25;a++) {
                chr.insert(make_pair(a,chars[a]));
        }
        cout<<"Size after erase all: "<<chr.size()<<endl;

        cout<<"\nTest String type: \n"<<endl;
        string str1 = "Hello,";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
        string str5 = "bad";

        str.insert(make_pair(1,str1));
        str.insert(make_pair(2,str2));
        str.insert(make_pair(3,str3));
        str.insert(make_pair(4,str4));
        auto sentence1 = strAVL;
        cout<<"The sentence: "<<str[1]<<str[2]
            <<str[3]<<str[4]<<endl;

        strAVL.erase(4);
        strAVL.insert(make_pair(4,str5));
        auto sentence2 = str;
        cout<<"The sentence after erase and insert: "
            <<str[1]<<str[2]
            <<str[3]<<str[4]<<endl;
        cout<<"Are the two sentences same? "
            <<boolalpha<<(sentence1==sentence2)<<endl;
        cout<<"So they are not the same: "
            <<boolalpha<<(sentence1!=sentence2)<<endl;
}
