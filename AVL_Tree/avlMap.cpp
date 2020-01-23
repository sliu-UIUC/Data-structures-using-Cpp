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
#include "AVLMap.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::make_pair;
using std::boolalpha;

int main() {
        AVLMap<int,int> numAVL;
        AVLMap<int,char> chrAVL;
        AVLMap<int,string> strAVL;

        cout<<"Test number values: \n"<<endl;
        cout<<"Emptyness before insert: "<<boolalpha<<numAVL.empty()<<endl;
        cout<<"Size of number AVL before insert: "<<numAVL.size()<<endl;
        for(int i = 0; i < 1000;i++) {
                numAVL.insert(make_pair(i,i));
        }
        cout<<"Emptyness after insert: "<<boolalpha<<numAVL.empty()<<endl;
        cout<<"size after 1000 inserts: "<<numAVL.size()<<endl;
        cout<<"Find element with the key 1: "<<numAVL[1]<<endl;
        cout<<"Number of elements with the key 1: "<<numAVL.count(1)<<endl;
        numAVL.erase(numAVL.find(1));
        cout<<"Size after erase node with the key 1: "<<numAVL.size()<<endl;
        cout<<"Number of elements with the key 1: "<<boolalpha<<numAVL[1]<<endl;
        numAVL.clear();
        cout<<"Emptyness after clear: "<<boolalpha<<numAVL.empty()<<endl;
        cout<<"Number of elements after clear: "<<numAVL.size()<<endl;

        cout<<"\nTest char values: \n"<<endl;
        char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        cout<<"Emptyness before insert: "<<chrAVL.empty()<<endl;
        cout<<"Size before insert: "<<chrAVL.size()<<endl;
        for(int a =0;a<=25;a++) {
                chrAVL.insert(make_pair(a,chars[a]));
        }
        cout<<"Size after erase all: "<<chrAVL.size()<<endl;

        cout<<"\nTest String type: \n"<<endl;
        string str1 = "Hello,";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
        string str5 = "bad";

        strAVL.insert(make_pair(1,str1));
        strAVL.insert(make_pair(2,str2));
        strAVL.insert(make_pair(3,str3));
        strAVL.insert(make_pair(4,str4));
        auto sentence1 = strAVL;
        cout<<"The sentence: "<<strAVL[1]<<strAVL[2]
            <<strAVL[3]<<strAVL[4]<<endl;

        strAVL.erase(4);
        strAVL.insert(make_pair(4,str5));
        auto sentence2 = strAVL;
        cout<<"The sentence after erase and insert: "
            <<strAVL[1]<<strAVL[2]
            <<strAVL[3]<<strAVL[4]<<endl;
        cout<<"Are the two sentences same? "
            <<boolalpha<<(sentence1==sentence2)<<endl;
        cout<<"So they are not the same: "
            <<boolalpha<<(sentence1!=sentence2)<<endl;
}

