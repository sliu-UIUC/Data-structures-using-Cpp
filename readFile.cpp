#include<cstdio>
#include<iostream>

int main {
	FILE *f = fopen("text.bin", "r+"); 

	if(f!=nullptr) {
		cout<<"File open successful." <<endl;
	} else {
		f = fopen("text.bin", "w+"); //file doesnt exist
		
		return -1;
	
	}
	
	int i = 42;
	
	//fwrite(&i,sizeof(int),1, f);// (object,size in byte,numOfElem, pointer)

	fseek(f, 0 ,SEEK_SET);
	int j;
	fread(&j, sizeof(int), 1, f);
	fclose(f);
}
