#include<iostream>
#include "arrayStack.h"

using namespace std;

int main(){
Array_stack<int> s1(500);    // was Astack
Array_stack <char> s3;        // was Cstack

 int i;  // remainder the same
 
 for( i = 0; i < 20; i++ ) {
 	s1.push(i);
 }

 for( i = 0; i < 20; i++ ) {
 	cout << s1.pop() << ' ';
 }
 
 for( i = 0; i < 20; i++ ) {
 	s3.push('a' + i);
 }

 for( i = 0; i < 20; i++ ) {
 	cout << s3.pop() << ' ';
 }
 return 0;
}
