// Analizadorlexico.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	ifstream infile("teste.txt");
	string line;
	//Leitura do arquivo
	while (getline(infile, line)){
		istringstream iss(line);
		string n;
		vector<string> v;

		while (iss >> n){
			v.push_back(n);
		}

	}
	infile.close();
	int para;
	cin >> para;
	return 0;
}

