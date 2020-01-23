#include <iostream>
#include <string>
#include <cstdio>
#include "ArrayList.h"

using namespace std;
int main() {
	ArrayList<int> l;
	ArrayList<char> l2;
	ArrayList<string> l3;
	
	cout<<"Testing int type : \n\n"<<endl;
	cout<<"Current length of the list: "<<l.size()<<endl;	
	for (int i = 0; i<500;i++) {
		l.push_back(i);
		cout<<"current end of the list: "<<l[i]<<endl;
	}
	cout<<"Current size the list: "<<l.size()<<endl;
	
	for(int j = -500;j<0;j++){
		l.insert(j,0);
		cout<<"First elem of the list :"<<l[0]<<endl;
		cout<<"Current size: "<<l.size()<<endl;
	}
	
	cout<<"Current size: "<<l.size()<<endl;
	cout<<"Current end of list: "<<l[l.size()-1]<<endl;
	
	for (int i = 0; i<900;i++) {
                l.pop_back();
		cout<<"current size: "<<l.size()<<endl;
                cout<<"current end of the list: "<<l[l.size()-1]<<endl;
        }
	
	for(int m = 0; m<99; m++) {
		l.remove(100-m);
		cout<<"Current end: "<<l[l.size()-1]<<endl;
	}
	l.clear();
	cout<<"size after clear: " << l.size()<<endl;
	cout<<"Test char type: \n\n"<<endl;
	 char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p'
                        ,'q','r','s','t','u','v','w','x','y','z'};
	for(int a = 0; a <= 26;a++) {
		l2.push_back(chars[a]);
		cout<<"current end of the list: "<<l2[l2.size()-1]<<endl;
		cout<<"current size : "<<l2.size()<<endl;
	}
	for(int b = 0; b<=16;b++) {
		l2.pop_back();
		cout<<"end after pop: "<<l2[l2.size()-1]<<endl;
		cout<<"current size: "<<l2.size()<<endl;
	}
	for(int c =0; c<5;c++) {
		int end = l2.size()-1;
		l2.remove(end);
		end = end-1;
		cout<<"end after remove the previous end: "<<l2[end]<<endl;
		cout<<"current size: "<<l2.size()<<endl;
	}
	l2.clear();
	cout<<"end after clear:"<<l2[l2.size()-1]<<endl;
	cout<<"size after clear: "<<l2.size()<<endl;
	
	cout<<"Testing string type \n\n"<<endl;
	string str1 = "Hello,";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
	string str5 = "bad";
		
	l3.push_back(str1);
	l3.push_back(str2);
	l3.push_back(str3);
	l3.push_back(str4);
	for (int d = 0; d<=3;d++) {
		cout<<l3[d];
	}
	cout<<"\nList size: "<<l3.size()<<endl;
	cout<<"\n"<<endl;
	l3.remove(3);
	l3.insert(str5, 3);
	for(int e = 0; e<=3;e++) {
                cout<<l3[e];
        }
	cout<<"\nNew list size: "<<l3.size()<<endl;

 
}


