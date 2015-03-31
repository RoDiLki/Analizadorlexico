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

typedef struct{
	string lexema;
	string categoria; // P = palavra reservada  O = operador  S = simbolos 
	string ID;
}TPreservadas; //dicionario de palavras reservadas

typedef struct{
	int ID;
	string categoria;
	string tipo;
	string lexema;
	int linha;
}TPtokens; //tokens de saidaaaa


vector<vector <string>> codentrada;

vector<TPreservadas> TPalavras;

vector<TPtokens> TabelaTokens;

vector<TPtokens> TabelaSimbolos;

vector<char> delimitadores{ '(', ')', '[', ']', ';', '{', '}', '+', '-', '*', '/', '<', '>', '=', '!', '\\', ':', '&', '.', '%', '|', ',', '\'','"'};


void inicializaTPalavras(){
	TPreservadas ax;

	ifstream infile("tabelareservados.txt");
	string line;
	
	while (getline(infile, line)){
		istringstream iss(line);
		string s;

		vector<string> v;
		while (iss >> s){
			v.push_back(s);
		}
		ax.ID = v[0];
		ax.categoria = v[1];
		ax.lexema = v[2];
		//cout << " " << ax.ID << " " << ax.categoria << " " << ax.lexema << endl;
		TPalavras.push_back(ax);
	}
	
	
	infile.close();
}

void leituraArquivo(){

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
}

void imprimeArquivo(){
	for (int i = 0; i < codentrada.size(); i++)
	{
		for (int j = 0; j < codentrada[i].size(); j++)
		{
			cout << codentrada[i][j];

		}
		cout << endl;

	}
}

string reservada(string p){
	for (int i = 0; i < TPalavras.size(); i++)
	{
		//cout << TPalavras[i].lexema << endl;
		if (p == TPalavras[i].lexema)return TPalavras[i].categoria;
		
	}
	return "x";
}

int verificaDelimitador(char ca){
	for (int k = 0; k < delimitadores.size(); k++){
		if (delimitadores[k] == ca){
			return 1;
		}
	}
	return 0;
}

int verificaTabelaSimbolo(string pal){

	for (int i = 0; i < TabelaSimbolos.size(); i++)
	{
		if (pal == TabelaSimbolos[i].lexema){
			return 1;
		}
	}
	return 0;
}

void imprimeTS(){

	ofstream arquivo("Tabela de Símbolos.csv");
	ofstream arquivot("Tabela de Símbolos.txt");
	arquivo << "ID;Categoria;Tipo;Lexema;Linha" << endl;
	arquivot << "ID Categoria Linha  Tipo      Lexema " << endl;

	cout << "Tabela de Simbolos:\n";
	cout << "ID  Categoria          Tipo        Lexema         Linha\n";
	
	for (int i = 0; i < TabelaSimbolos.size(); i++)
	{
		arquivo << TabelaSimbolos[i].ID << " ; " << TabelaSimbolos[i].categoria << " ; " << TabelaSimbolos[i].linha << " ; " << TabelaSimbolos[i].tipo << " ; " << TabelaSimbolos[i].lexema << endl;
		arquivot << TabelaSimbolos[i].ID << "\t\t" << TabelaSimbolos[i].categoria << "\t\t" << TabelaSimbolos[i].linha << "\t" << TabelaSimbolos[i].tipo << "\t\t" << TabelaSimbolos[i].lexema << endl;
		cout << TabelaSimbolos[i].ID << "      " << TabelaSimbolos[i].categoria << "              " << TabelaSimbolos[i].tipo << "              " << TabelaSimbolos[i].lexema << "         " << TabelaSimbolos[i].linha << endl;
	}
	arquivo.close();
	arquivot.close();
}

void imprimeTT(){
	ofstream arquivo1("Tabela de Tokens.csv");
	ofstream arquivo1t("Tabela de Tokens.txt");
	arquivo1 << "ID;Categoria;Lexema;Linha" << endl;
	arquivo1t << "ID Linha Categoria  Lexema " << endl;

	cout << "\nTabela de Tokens:\n";
	cout << "ID    Categoria      Lexema       Linha\n";
	for (int i = 0; i < TabelaTokens.size(); i++)
	{
		arquivo1 << TabelaTokens[i].ID << ";" << TabelaTokens[i].linha << ";" << TabelaTokens[i].categoria << ";" << TabelaTokens[i].lexema << endl;
		arquivo1t << TabelaTokens[i].ID << "\t" << TabelaTokens[i].linha << "\t\t" << TabelaTokens[i].categoria << "\t\t" << TabelaTokens[i].lexema << endl;
		cout << TabelaTokens[i].ID << "            " << TabelaTokens[i].categoria << "               " << TabelaTokens[i].lexema << "          " << TabelaTokens[i].linha << endl;
	}

	arquivo1.close();
	arquivo1t.close();
}


int main()
{
	inicializaTPalavras();
	leituraArquivo();
	imprimeArquivo();



	for (int entL = 0; entL < codentrada.size(); entL++){
		for (int entC = 0; entC < codentrada[entL].size(); entC++){

			if ((codentrada[entL][entC][0] == '/' && codentrada[entL][entC][1] == '/') || codentrada[entL][entC][0] == '#') break;
			

			//cout << codentrada[entL][entC] << endl;
			string var = reservada(codentrada[entL][entC]);
			//cout << var<<"\n\n";

			if (var!= "x"){//quando é uma palavra facil de fazer
				TPtokens aux;
				aux.ID = TabelaTokens.size();
				aux.lexema = codentrada[entL][entC];
				aux.linha = entL;
				aux.categoria = var;
				aux.tipo = "";

				TabelaTokens.push_back(aux);

			}
			else{//dificio
				string  pl = "";
				string plAnt;
				for (int i = 0; i < codentrada[entL][entC].size(); i++)	{

					int ret = verificaDelimitador(codentrada[entL][entC][i]);
					plAnt = pl;
					pl += codentrada[entL][entC][i];

					if (ret == 1){//achou um delimitador

						if (pl.size() == 1){
							string var = reservada(codentrada[entL][entC]);

							TPtokens aux;
							aux.ID = TabelaTokens.size();
							aux.lexema = pl;
							aux.linha = entL;
							aux.categoria = var;
							aux.tipo = "";

							TabelaTokens.push_back(aux);
							pl = "";
						}
						/*else if (pl.size() == 2 && reservada(pl) != "x"){

								string var = reservada(pl);
								cout << "HUEHUEHUEHUEHUE";
								TPtokens aux;
								aux.ID = TabelaTokens.size();
								aux.lexema = pl;
								aux.linha = entL;
								aux.categoria = var;
								aux.tipo = "";

								TabelaTokens.push_back(aux);
								pl = "";
						}*/
						
						string var = reservada(plAnt);
						if (var != "x"){//palavra reservada guarda só na tabela de tokens
							TPtokens aux;
							aux.ID = TabelaTokens.size();
							aux.lexema = plAnt;
							aux.linha = entL;
							aux.categoria = var;
							aux.tipo = "";

							TabelaTokens.push_back(aux);

							pl = codentrada[entL][entC][i];
						}
						else{//não esta na tabela de palavras reservadas, tem que gravar na de Tokens e na de Simbolos

							TPtokens aux;
							aux.ID = TabelaTokens.size();
							aux.lexema = plAnt;
							aux.linha = entL;
							if (plAnt[0] <= '9'){//é literal LOL
								aux.categoria = "L";
							}
							else{
								aux.categoria = "I";//é identificador
							}
							
							aux.tipo = "";

							TabelaTokens.push_back(aux);

							int ver = verificaTabelaSimbolo(plAnt);
							if (ver == 0){
								if (entC > 0){
									if (plAnt[0] <= '9'){//é literal LOL
										aux.tipo = "Literal";
									}
									else{
										aux.tipo = codentrada[entL][0];
									}
									
									//cout << "simbolo: " << aux.tipo << endl;
								}
									
								else{
									aux.tipo = "D1";
								}
								TabelaSimbolos.push_back(aux);
							}

							pl = codentrada[entL][entC][i];
							cout << "PL: " << pl << endl;
						}

					}
					else{
						if (pl.size() == 2){
							if (verificaDelimitador(pl[0]) == 1 && verificaDelimitador(pl[1]) == 0){
								TPtokens aux;
								aux.ID = TabelaTokens.size();
								aux.lexema = plAnt;
								aux.linha = entL;
								aux.categoria = "S";//ou ident ou literal MUDAR AQUI TBM
								aux.tipo = "";

								TabelaTokens.push_back(aux);
								pl = pl[1];
							}
						}
					}
					
				}

				TPtokens aux;
				aux.ID = TabelaTokens.size();
				aux.lexema = pl;
				aux.linha = entL;
				aux.categoria = "S";//ou ident ou literal
				aux.tipo = "";

				TabelaTokens.push_back(aux);

			}


		}
	}
	imprimeTS();
	imprimeTT();
	int para;
	cin >> para;

	return 0;
}


