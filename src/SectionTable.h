#ifndef SECTIONTABLE_H
#define SECTIONTABLE_H
#include <iostream>
#include <list>
#include <string>

using namespace std;

struct sectionNode{
   
    string name;
    string offset;
    string rwa;
    char GL;
    int realLC;

};

void setSection(string name, int locationCounter);

int findLC(int section);


extern list<sectionNode> sectionTable;



#endif