#include<stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

#define DATA_NUM 64

int main()
{
	ofstream oFile;
	oFile.open("firData", ios::app);
	if (!oFile.is_open()) {
		cout << "firData is not opened." << endl;
	}
	else {
		bitset<32> temp;
		for (int i = 0; i < DATA_NUM; i++) {
			temp = i;
			//oFile << "0x" << temp << endl;
			oFile << i + 1 << endl;
		}
	}
	oFile.close();
}
