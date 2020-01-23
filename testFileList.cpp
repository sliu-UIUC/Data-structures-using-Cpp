#include<cstdio>
#include<iostream>

struct Node {
	char data;
	int prev;
	int next;
}

int getPrev(int node, FILE *file) {
	//equiv of node -> prev
	int res;
	fseek(file, node+sizeof(char), SEEK_SET);
	fread(&res, sizeof(int), 1 file);
	return res;
}

int getNext(int node, FILE *file) {
	int res;
	fseek(file, node+sizeof(char)+sizeof(int), SEEK_SET);
	fread(&rev,sizeof(int), 1, file);
	return res;
}

int writePrev(int node, int value, FILE *file) {
	fseek(file, node+sizeof(char), SEEK_SET);
	fwrite(&value, sizeof(int),1, file);
}

int writeNext(int node, int value, FILE *file) {
        fseek(file, node+sizeof(char)+sizeof(int), SEEK_SET);
        fwrite(&value, sizeof(int),1, file);
}

//int getSize();
//void writeSize();

int main() {
	FILE *file = fopen("testlist.bin", "+w")
	Node sentinel {'h', 0, 0};
	fwrite( &sentinel, sizeof(Node),1 ,file);
	int freelist = -1;
	fwrite(&freelist, sizeof(int), 1, file);
	int sz = 0;
	fwrite(&sz, sizeof(int), 1, file);
	
	//insery
	Node newnode('e', 0 , 0);
	fwrite(&newnode,sizeof(Node), 1, file);
	writePrev(0, sizeof(Node)+sizeof(int)+sizeof(int), file);
        writeNext(0, sizeof(Node)+sizeof(int)+sizeof(int), file);
}
