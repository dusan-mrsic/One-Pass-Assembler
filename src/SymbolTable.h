#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <list>
#include <vector>
#include "FlinkStruct.h"

using namespace std;

struct symbolNode{
    symbolNode(string name_, int value_){
        name = name_; value= value_;
    }
    string name;
    int value;
    int size;
    bool defined;
    char LG;
    int section;

    bool isEqu;
    int equSection;

    list <Flink_Node> Flink;
};

extern list <symbolNode> symbol_Table;
extern vector<string> opCode;
extern int locationCounter;
extern bool equSearched;
extern int section;
extern bool equ;


void setSymbol(string arg, int& lc, char c, int section);

void setSymbolLabel(string arg, int& lc, int section, bool equ, int equsection);

void setSymbolExtern(string arg, char c);

void changeLC();

void setSymbolGlobal(string arg, char c, int section);

void writeList(list<Flink_Node> lista);

bool findSymbol(string name,int& symbol);

bool findSymbolSEC(string name,int& symbol, int& sec);

bool findSymbolBP(string name, int&symbol, int& size);

void findSymbolPC(string name, int& value, int& section, char& c);

void findSymbolREL(string name, int& section, char& LG);

void findSymbolRELOCATION(string name, int& section, char& LG, bool& isEqu, int& equSection);

void backpatching();



#endif
