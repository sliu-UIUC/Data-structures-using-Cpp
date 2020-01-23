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
#include "HashMap.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::make_pair;
using std::boolalpha;

int main() {
        HashMap<int,int,std::function<int(int)>> numMap ([] (int i) {return i;});
        HashMap<int,char,std::function<int(int)>> chrMap([] (int i) {return i;});
        HashMap<int,string,std::function<int(int)>> strMap ([] (int i) {return i;});

        cout<<"Test number values: \n"<<endl;
        cout<<"Emptyness before insert: "<<boolalpha<<numMap.empty()<<endl;
        cout<<"Size of number BST before insert: "<<numMap.size()<<endl;
        for(int i = 0; i < 1000;i++) {
                numMap.insert(make_pair(i,i));
        }
        cout<<"Emptyness after insert: "<<boolalpha<<numMap.empty()<<endl;
        cout<<"size after 1000 inserts: "<<numMap.size()<<endl;
        cout<<"Number of elements with the key 1: "<<numMap.count(1)<<endl;
        numMap.erase(numMap.find(1));
        cout<<"Size after erase node with the key 1: "<<numMap.size()<<endl;
        numMap.clear();
	cout<<"Emptyness after clear: "<<boolalpha<<numMap.empty()<<endl;
        cout<<"Number of elements after clear: "<<numMap.size()<<endl;

        cout<<"\nTest char values: \n"<<endl;
        char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        cout<<"Emptyness before insert: "<<chrMap.empty()<<endl;
        cout<<"Size before insert: "<<chrMap.size()<<endl;
        for(int a =0;a<=25;a++) {
                chrMap.insert(make_pair(a,chars[a]));
        }
        cout<<"Size after insert: "<<chrMap.size()<<endl;
        cout<<"Emptyness After insert: "<<chrMap.empty()<<endl;
        for(int b =0;b<=25;b++) {
                chrMap.erase(b);
        }
	 cout<<"Size after erase all: "<<chrMap.size()<<endl;

        cout<<"\nTest String type: \n"<<endl;
        string str1 = "Hello,";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
        string str5 = "bad";

        strMap.insert(make_pair(1,str1));
        strMap.insert(make_pair(2,str2));
        strMap.insert(make_pair(3,str3));
        strMap.insert(make_pair(4,str4));

        cout<<"The sentence: "<<strMap[1]<<strMap[2]
            <<strMap[3]<<strMap[4]<<endl;

        strMap.erase(4);
        strMap.insert(make_pair(4,str5));
        cout<<"The sentence after erase and insert: "
            <<strMap[1]<<strMap[2]
            <<strMap[3]<<strMap[4]<<endl;
}

