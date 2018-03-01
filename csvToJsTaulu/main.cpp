// ConsoleApplication9.cpp : Defines the entry point for the console application.
//


//#include "stdafx.h"    uncomment on windows
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()
#include <cstddef>        // std::size_t
#include <vector>

//lisää myös nollat jos on tyhjä
std::vector < std::string > split(std::string s)
{
	int sarakkeita = 1;
	for (int i = 0; i < s.size(); i++) {
		if (s.at(i) == ';') {
			sarakkeita++;
		}
	}
	std::vector < std::string > returned(sarakkeita);
	std::string ss = s;

	for (int i = 0; i < sarakkeita -1 ; i++) {
		int begin = 0;
		int delimPos = ss.find_first_of(';');
		returned.at(i) = ss.substr(begin, delimPos - begin);
		ss = ss.substr(delimPos + 1, ss.size() - (delimPos + 1));
	}
	returned.at(sarakkeita - 1) = ss;

	for (int i = 0; i < returned.size(); i++) {
		if (returned.at(i).length() == 0) {
			returned.at(i) = "0";
		}
	}
	returned.at(0) += " ";
	return returned;
}

int main()
{
	using namespace std;

    //luettava tiedosto
	ifstream inf("csvTaulu.csv");

	if (!inf)
	{
		cerr << "problem reading file" << endl;
		exit(1);
	}

	std::vector < std::vector < std::string > > outputTaulu;

	std::string luettuRivi1;
	getline(inf, luettuRivi1);
	std::vector < std::string > luettuTaulu1 = split(luettuRivi1);
	std::vector < std::string > emptyVector = {};


	for (int i = 0; i < luettuTaulu1.size(); i++) {
		outputTaulu.push_back(emptyVector);
	}

	if (luettuTaulu1.at(1).length() != 0) {
		for (int i = 0; i < luettuTaulu1.size(); i++) {
			outputTaulu.at(i).push_back(luettuTaulu1.at(i));
		}
	}

	bool dataAlkoi = true;


	while (inf)
	{

		std::string luettuRivi;
		getline(inf, luettuRivi);
		if (luettuRivi.size() < 2) {
			continue;
		}
		std::vector < std::string > luettuTaulu = split(luettuRivi);

		if (!dataAlkoi)
		{
			if (luettuTaulu.at(1).length() == 0) {
				continue;
			}
			dataAlkoi = true;
		}


		for (int i = 0; i < luettuTaulu.size(); i++) {
			outputTaulu.at(i).push_back(luettuTaulu.at(i));
		}

		for (int i = 0; i < luettuTaulu.size(); i++) {
			cout << luettuTaulu.at(i) << endl;
		}
		std::cout << '#' << '\n';

		/*
		// read stuff from the file into a string and print it
		std::string strInput;
		getline(inf, strInput);
		cout << strInput << endl;
		*/
	}

	std::string outputString = "var t_taulukko = [";
	for (int i = 0; i < outputTaulu.size(); i++) {
		outputString += "[";
		outputString += "\"" + outputTaulu.at(i).at(0) + "\"";
		for (int j = 1; j < outputTaulu.at(i).size(); j++) {
			outputString += ",\"" + outputTaulu.at(i).at(j) + "\"";
		}
		outputString += "],";
	}
	outputString += "];";

	ofstream outf("T_data.js");

	if (!outf)
	{
		cerr << "problem opening write stream" << endl;
		exit(1);
	}

	//outf << "toimii" << endl;
	outf << outputString << endl;



	/*
	for (int i = 0; i < outputTaulu.size(); i++) {
		cout << outputTaulu.at(i).at(2) << endl;
	}
	*/

	std::cin.clear(); // reset any error flags
	std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get(); // get one more char from the user


	return 0;
}
