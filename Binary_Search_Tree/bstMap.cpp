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
#include "BSTMap.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::make_pair;
using std::boolalpha;

int main() { 
	BSTMap<int,int> numBst;
	BSTMap<int,char> chrBst;
	BSTMap<int,string> strBst;
	
	cout<<"Test number values: \n"<<endl;
	cout<<"Emptyness before insert: "<<boolalpha<<numBst.empty()<<endl;
	cout<<"Size of number BST before insert: "<<numBst.size()<<endl;
	for(int i = 0; i < 1000;i++) {
		numBst.insert(make_pair(i,i));
	}
	cout<<"Emptyness after insert: "<<boolalpha<<numBst.empty()<<endl;
	cout<<"size after 1000 inserts: "<<numBst.size()<<endl;
	cout<<"Find element with the key 1: "<<numBst[1]<<endl;
	cout<<"Number of elements with the key 1: "<<numBst.count(1)<<endl;
	numBst.erase(numBst.find(1));
	cout<<"Size after erase node with the key 1: "<<numBst.size()<<endl;
	cout<<"Number of elements with the key 1: "<<boolalpha<<numBst[1]<<endl;
	numBst.clear();
	cout<<"Emptyness after clear: "<<boolalpha<<numBst.empty()<<endl;
	cout<<"Number of elements after clear: "<<numBst.size()<<endl;

	cout<<"\nTest char values: \n"<<endl;	
	char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	cout<<"Emptyness before insert: "<<chrBst.empty()<<endl;
	cout<<"Size before insert: "<<chrBst.size()<<endl;
	for(int a =0;a<=25;a++) {
		chrBst.insert(make_pair(a,chars[a]));
	}
	cout<<"Size after insert: "<<chrBst.size()<<endl;
        cout<<"Emptyness After insert: "<<chrBst.empty()<<endl;
	cout<<"The 26th element: "<<chrBst[25]<<endl;
        for(int b =0;b<=25;b++) {
                chrBst.erase(b);
        }
	cout<<"Size after erase all: "<<chrBst.size()<<endl;
	
	cout<<"\nTest String type: \n"<<endl;
        string str1 = "Hello,";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
        string str5 = "bad";
	
	strBst.insert(make_pair(1,str1));
        strBst.insert(make_pair(2,str2));
        strBst.insert(make_pair(3,str3));
        strBst.insert(make_pair(4,str4));
	auto sentence1 = strBst;
	cout<<"The sentence: "<<strBst[1]<<strBst[2]
            <<strBst[3]<<strBst[4]<<endl;

	strBst.erase(4);
	strBst.insert(make_pair(4,str5));
	auto sentence2 = strBst;
	cout<<"The sentence after erase and insert: "
            <<strBst[1]<<strBst[2]
            <<strBst[3]<<strBst[4]<<endl;
	cout<<"Are the two sentences same? "
            <<boolalpha<<(sentence1==sentence2)<<endl;
	cout<<"So they are not the same: "
            <<boolalpha<<(sentence1!=sentence2)<<endl;
}
