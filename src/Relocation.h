#ifndef RELOCATION_H
#define RELOCATION_H
#include <string>
#include <list>
#include <vector>

using namespace std;

struct pomNode{

    pomNode(int lc, int next, string symbol, int section){
        locationCounter_=lc;
        nextLC=next;
        symbol_=symbol;
        section_=section;

    }
    int locationCounter_;
    int nextLC;
    string symbol_;
    int section_;
    
};

struct relNode{
    string offset;
    string type;
    string symbol;
    int section;
    int adressing;
};

extern vector< list<relNode> > relTables;
extern list<pomNode> pomPCList;
extern int nextLC;

void addToRelTable(string arg, int adressing);

void addList();

void addToPomPcList(int lc, int next, string symbol, int section);

void fillPomBytes();

void fillRelTable();

#endif