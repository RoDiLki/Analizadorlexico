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

vector<vector <string>> codentrada;

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
			//v.push_back(" ");
		}
		codentrada.push_back(v);
	}
	infile.close();
	
	int sizeee = codentrada.size();

	for (int i = 0; i < codentrada.size(); i++)
	{
		for (int j = 0; j < codentrada[i].size(); j++)
		{
			cout << codentrada[i][j];
			
		}
		cout << endl;
		
	}
	int para;
	cin >> para;

	return 0;
}

