#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "FileLinkedList.h"
using namespace std;

int main() {
        FileLinkedList<int> intLst ("lst1.bin");
        FileLinkedList<char> charLst ("lst2.bin");
        FileLinkedList<string> strLst ("lst3.bin");

        cout<<"Testing integer type: \n\n"<<endl;
        for(int i =0; i < 1000;i++) {
                intLst.push_back(i);
                cout<<"current end of the list: "<<intLst[i]<<endl;
        }
        cout<<"Current size of the list: "<<intLst.size()<<endl;

        cout<<"Current end of list: "<<intLst[intLst.size()-1]<<endl;

         for (int i = 0; i<900;i++) {
                intLst.pop_back();
                cout<<"current size: "<<intLst.size()<<endl;
                cout<<"current end of the list: "<<intLst[intLst.size()-1]<<endl;
        }
intLst.clear();
        cout<<"size after clear: " << intLst.size()<<endl;
        cout<<"Test char type: \n\n"<<endl;

	char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        for(int a = 0; a <= 26;a++) {
                charLst.push_back(chars[a]);
                cout<<"current end of the list: "<<charLst[charLst.size()-1]<<endl;
                cout<<"current size : "<<charLst.size()<<endl;
        }

        for(int b = 0; b<=16;b++) {
                charLst.pop_back();
                cout<<"end after pop: "<<charLst[charLst.size()-1]<<endl;
                cout<<"current size: "<<charLst.size()<<endl;
        }

        charLst.clear();
        cout<<"end after clear:"<<charLst[charLst.size()-1]<<endl;
        cout<<"size after clear: \n"<<charLst.size()<<endl;
        charLst.insert(charLst.begin(), '!');
        cout<<"current elem: "<<charLst[0]<<endl;
        charLst.insert(charLst.begin(), '?');
        cout<<"current elem: "<<charLst[1]<<endl;
        cout<<"size after 2 inserts: "<< charLst.size() <<endl;
        charLst.erase(++charLst.begin());
        cout<<"current elem: "<<charLst[0]<<endl;
        cout<<"size after 1 erase: "<< charLst.size() <<endl;
        charLst.clear();

	cout<<"Testing string type \n\n"<<endl;
        strLst.clear();
        strLst.push_back("Hello,");
        strLst.push_back("C++");
        strLst.push_back(" is ");
        strLst.push_back("Good.");
        cout<<"Current Size: "<<strLst.size()<<endl;
        strLst.erase(++++++strLst.begin());
        cout<<"Current Size after erase: "<<strLst.size()<<endl;
        strLst.insert(++++++strLst.begin(),"Bad");
        cout<<"\nNew list size after insert: "<<strLst.size()<<endl;

}

