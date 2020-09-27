#ifndef ADRESSING_H
#define ADRESSING_H
#include <iostream>
#include <string>

using namespace std;

int regdir(string arg1);

int regind(string arg1);

int regindpom(string arg1, int &pom);

int memdir(string arg1);

int immed(string arg);

int determinateAdressing(string arg, int& pom, int &adressing);

extern bool sym;

#endif