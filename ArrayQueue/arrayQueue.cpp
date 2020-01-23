#include <iostream>
#include <string>
#include <cstdio>
#include "ArrayQueue.h"

using namespace std;


int main() {
        ArrayQueue<int> q1;
        ArrayQueue<char> q2;
        ArrayQueue<string> q3;
        cout<<"Is q1 empty:  "<<boolalpha<<q1.isEmpty()<<endl;
        cout<< "Test integer type. \n"<<endl;
        for(int i =0;i <= 1000; ++i){
                q1.enqueue(i);
                cout<<"current top of the queue: "<<q1.peek()<<endl;
        }
        for(int a = 0; a<=1001; a++){
                        cout<<"dequeued element: " <<q1.dequeue()<<"; Next Element: "<<q1.peek()
                        <<"; Is queue empty?  "<<boolalpha<<q1.isEmpty()<<endl;
        }
        cout<<"Is q2 empty:  "<<boolalpha<<q2.isEmpty()<<endl;
        cout<<"Testing char type. \n"<<endl;
        char chars[26]= {'a', 'b', 'c','d','e','f', 'g','h','i','j','k','l','m','n','o','p'
                        ,'q','r','s','t','u','v','w','x','y','z'};
        for(int b= 0;b<=25; b++){
                q2.enqueue(chars[b]);
                cout<<"current top of the queue: "<<q2.peek()<<endl;
        }
        for(int c = 0; c<=26; c++){
                        cout<<"dequeued element: " <<q2.dequeue()<<"; Next Element: "<<q2.peek()
                        <<"; Is queue empty?  "<<boolalpha<<q2.isEmpty()<<endl;
        }
        cout<<"Is q3 empty:  "<<boolalpha<<q3.isEmpty()<<endl;
        cout<<"Testing string type \n"<<endl;
        string str1 = "Hello";
        string str2 = "c ++";
        string str3 = " is ";
        string str4 = "good";
        q3.enqueue(str1); cout<<"current top of the queue: "<<q3.peek()<<endl;
        q3.enqueue(str2); cout<<"current top of the queue: "<<q3.peek()<<endl;
        q3.enqueue(str3); cout<<"current top of the queue: "<<q3.peek()<<endl;
        q3.enqueue(str4); cout<<"current top of the queue: "<<q3.peek()<<endl;
        for (int d=0; d<=3; d++) {
                cout<<"dequeued element: " <<q3.dequeue()<<"; Next Element: "<<q3.peek()
                        <<"; Is queue empty?  "<<boolalpha<<q3.isEmpty()<<endl;
        }
        return 0;
}
