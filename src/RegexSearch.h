#ifndef REGEXSEARCH_H
#define REGEXSEARCH_H
#include <string>
#include <list>
#include <iostream>


using namespace std;

struct equNode{
    string symbol;
    string equation;
    int section;
    int s;
};


bool searchInsNoArg(string& line, int& code);

bool searchLabel(string &line, string& arg, int& code);

bool searchIns(string& line, string& arg, int& code);

bool searchIns2(string& line, string& arg1, string& arg2, int& code);

bool searchEqu(string &line);

bool searchSWB(string &line);

bool searchEG(string& line);

bool searchSection(string& line);

void adressing(string line, char& c, string ins);

int makeFirstByte(int code, char c);

string makeSecondByte(string arg, char c, string& thirdByte, string& fourthByte);

bool countEqu(string& arg1, int& equSection);

void countAllEques();

void putInEquList(string arg1, string agr2);

string changeArg(string arg1);

extern bool jump;
extern bool firstArg;
extern bool oneArg;
extern bool inImmed;
extern bool lowHigh;


extern list <equNode> equList;



#endif