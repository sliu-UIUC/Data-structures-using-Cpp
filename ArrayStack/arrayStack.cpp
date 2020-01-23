#include <iostream>
#include <string>
#include <cstdio>
#include "ARRAYSTACK.h"

using namespace std;


int main() {
	ArrayStack<int> s1;
	ArrayStack<char> s2;
	ArrayStack<string> s3;
	cout<<"Is s1 empty:  "<<boolalpha<<s1.isEmpty()<<endl;
	cout<< "Test integer type. \n"<<endl; 
	for(int i =0;i <= 1000; ++i){
		s1.push(i);
		cout<<"current top of the stack: "<<s1.peek()<<endl;
	}
	for(int a = 0; a<=1001; a++){
			cout<<"Poped element: " <<s1.pop()<<"; Next Element: "<<s1.peek()
			<<"; Is stack empty?  "<<boolalpha<<s1.isEmpty()<<endl; 
	}
	cout<<"Is s2 empty:  "<<boolalpha<<s2.isEmpty()<<endl;
	cout<<"Testing char type. \n"<<endl;
	char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p'
			,'q','r','s','t','u','v','w','x','y','z'};
	for(int b= 0;b<=25; b++){ 
                s2.push(chars[b]);
                cout<<"current top of the stack: "<<s2.peek()<<endl;
        }
	for(int c = 0; c<=26; c++){ 
                        cout<<"Poped element: " <<s2.pop()<<"; Next Element: "<<s2.peek() 
                        <<"; Is stack empty?  "<<boolalpha<<s2.isEmpty()<<endl;  
        } 
	cout<<"Is s3 empty:  "<<boolalpha<<s3.isEmpty()<<endl;
	cout<<"Testing string type \n"<<endl;
	string str1 = "Hello";
	string str2 = "c ++";
	string str3 = " is ";
	string str4 = "good";
	s3.push(str1); cout<<"current top of the stack: "<<s3.peek()<<endl;
	s3.push(str2); cout<<"current top of the stack: "<<s3.peek()<<endl;
	s3.push(str3); cout<<"current top of the stack: "<<s3.peek()<<endl; 
	s3.push(str4); cout<<"current top of the stack: "<<s3.peek()<<endl;
	for (int d=0; d<=3; d++) {
		cout<<"Poped element: " <<s3.pop()<<"; Next Element: "<<s3.peek()
                        <<"; Is stack empty?  "<<boolalpha<<s3.isEmpty()<<endl;
	} 	
	return 0;
}
