#include <iostream>
#include <string>
#include <list>
#include "Relocation.h"
#include "SymbolTable.h"
#include "DigitConvert.h"
#include "SymbolTable.h"
#include "RegexSearch.h"
#include "SectionTable.h"


using namespace std;

list<pomNode> pomPCList;
vector < list<relNode> > relTables;
int nextLC = 0;

void addToPomPcList(int lc, int next, string symbol, int section){
    
    pomNode node(lc,next,symbol,section);
    pomPCList.push_back(node);

}

void fillPomBytes(){

    list <pomNode> :: iterator it2;
    for(it2 = pomPCList.begin(); it2 != pomPCList.end(); ++it2){
        int value, section;
        char LG;
        findSymbolPC(it2->symbol_,value, section,LG);
        if(it2->section_ == section){
            int val = value - it2->nextLC + findLC(section);
            string val1 = makeTwoBytes(intToHex(val));
            string val2 = "00";
            if(val1.size()>2){
                string pom = val1;
                if(val1.size() > 4) val1.erase(0,val1.size()-4);
                val2 = val1.erase(val1.size()-2,val1.size());
                val1 = pom.erase(0,pom.size()-2);
            }
            opCode[it2->locationCounter_] = val1;
            opCode[it2->locationCounter_ + 1] = val2;
        }else if(it2->section_ != section && LG == 'G'){
            int val = it2->locationCounter_ - it2->nextLC;
            string val1 = makeTwoBytes(intToHex(val));
            string val2 = "00";
            if(val1.size()>2){
                string pom = val1;
                if(val1.size() > 4) val1.erase(0,val1.size()-4);
                val2 = val1.erase(val1.size()-2,val1.size());
                val1 = pom.erase(0,pom.size()-2);
            }
            opCode[it2->locationCounter_] = val1;
            opCode[it2->locationCounter_ + 1] = val2;
        }else if(it2->section_ != section && LG == 'L'){
            int val = value - it2->nextLC + it2->locationCounter_;
            string val1 = makeTwoBytes(intToHex(val));
            string val2 = "00";
            if(val1.size()>2){
                string pom = val1;
                if(val1.size() > 4) val1.erase(0,val1.size()-4);
                val2 = val1.erase(val1.size()-2,val1.size());
                val1 = pom.erase(0,pom.size()-2);
            }
            opCode[it2->locationCounter_] = val1;
            opCode[it2->locationCounter_ + 1] = val2;
        }

    }


}

void addToRelTable(string arg, int adressing){
    // 1 immed
    // 2 regindpom
    // 3 pcrel
    // 4 memdir
    int section_;
    char lg;
    bool isEquSymbol;
    findSymbolREL(arg,section_,lg);

    if(adressing == 1 || adressing == 2 || adressing == 4){
        relNode node;
        if(oneArg){
            node.offset = intToHex(locationCounter + 2 - findLC(section));
        }else{
            if(firstArg){
                node.offset = intToHex(locationCounter + 2- findLC(section));
            }else{
                node.offset = intToHex(locationCounter + 1- findLC(section));
            }
        }
        node.section = section;
        node.symbol = arg;
        relTables[section-1].push_back(node);
        return;
    }else if(adressing == 3){
        if(section == section_) return;
        relNode node;
        node.adressing = 3;
        if(oneArg){
            node.offset = intToHex(locationCounter + 2- findLC(section));
        }else{
            if(firstArg){
                node.offset = intToHex(locationCounter + 2- findLC(section));
            }else{
                node.offset = intToHex(locationCounter + 1- findLC(section));
            }
        }
        node.section = section;
        node.symbol = arg;
        relTables[section-1].push_back(node);
        return;
    }else if(adressing == 5 || adressing == 6){
        relNode node;
        node.offset = intToHex(locationCounter - findLC(section));
        node.section = section;
        node.symbol = arg;
        relTables[section-1].push_back(node);
        return;
    }
}

void fillRelTable(){
    
    list <relNode> :: iterator it3;
    vector<list <relNode> > :: iterator vec;
    int i = 0;
    for(vec = relTables.begin(); vec != relTables.end(); ++vec){
        
        for(it3 = relTables[i].begin(); it3 != relTables[i].end(); ++it3){
            
            int sec;
            int equSec;
            bool equ = false;
            char lg;
            findSymbolRELOCATION(it3->symbol,sec,lg,equ,equSec);
            list <relNode> :: iterator it;
            if(it3->adressing == 3 && lg == 'L' && it3->section == sec){
                it = it3;
                it3->section = -5;
            }else if(lg == 'G'){
                //cout << "uso" << endl;
                it3->section = -1;
                if(it3->adressing == 3) it3->type = "R_386_PC16";
                else it3->type = "R_386_16";
            }else if(lg == 'L'){
                it3->symbol = '-';
                if(equ == true){
                    if(equSec == 0) 
                        it3->section = sec;
                    else it3->section = equSec;
                
                }
                else it3->section = sec;
                if(it3->adressing == 3) it3->type = "R_386_PC16";
                else it3->type = "R_386_16";
            }
        }
        i++;
    
    }

}

void addList(){
    
    list<relNode> relList;
    relTables.push_back(relList);
    
}

