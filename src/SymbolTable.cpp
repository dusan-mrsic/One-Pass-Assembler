#include <string>
#include <iostream>
#include <list>
#include <regex>
#include "SymbolTable.h"
#include "FlinkStruct.h"
#include "RegexSearch.h"
#include "DigitConvert.h"
#include "SectionTable.h"
#include "outputData.h"

using namespace std;

list <symbolNode> symbol_Table;
vector<string> opCode;
bool equ = false;

int locationCounter = 0;

int section = 0;

bool equSearched = false;

void setSymbol(string arg, int& lc, char c, int section){
    //cout << "ARG U INS II" << arg << "!" << endl;
    regex exp("^(\\*?\\%r\\d+[l|h]?)$"); //regdir
    if(regex_search(arg,exp)) return;
    exp=("^(\\*?\\(\\%r.*\\))$"); //regind
    if(regex_search(arg,exp)) return;
    exp=("^(\\*?\\-?\\d+\\(\\%r.*\\))$"); //regindpom
    if(regex_search(arg,exp)) return;
    regex exp1("^(\\*?\\$*\\-?\\d+)$"); //immed
    if(regex_search(arg,exp1)) return;
    exp="^(\\*?\\$*0x\\w+)$"; //immed
    if(regex_search(arg,exp)) return;
    exp=("^(\\d+)$"); //immed
    if(regex_search(arg,exp)) return;
    exp=("^(\\*?[A-z]+\\(%r\\d+\\))$"); //regindpomsym
    if(regex_search(arg,exp)){
        if(arg[0] == '*')  arg.erase(0,1);
        arg.erase(arg.find('('),arg.size()-arg.find('('));
        //cout << arg << "ARG \n";
    }
    exp="^(\\*?\\w+)$";
    if(regex_search(arg,exp)){
        if(arg[0] == '*') arg.erase(0,1);
    }
    if(arg[0] == '$') arg.erase(0,1);
    //cout << "U TABELI SIMBOLA" << endl;
    //cout << arg << endl;
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == arg){
            if(it->defined == false){
                Flink_Node flinknode;
                flinknode.adress=lc;
                it->Flink.push_back(flinknode);
                return;
            }else return;
        }
    }
    
    symbolNode node(arg, 0);
    node.LG = 'L';
    node.defined = false;
    node.section = section;
    if(c != 'b') node.size = 2;
    else node.size = 1;
    
    Flink_Node flinknode;
    flinknode.adress=lc;
    node.Flink.push_back(flinknode);
    symbol_Table.push_back(node);
    
    
}

void setSymbolLabel(string arg, int& lc, int section, bool equ, int equs){

    cout << "USO" << endl;
    symbolNode node(arg, lc);
    if(equ) node.isEqu = true;
    else node.isEqu = false;
    node.LG='L';
    node.section=section;
    node.equSection = equs;
    node.size = 2; // SIZE 2 BYTES
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == node.name){
            //if(it->defined) writeExternError();
            if(equ == false) it->value = lc - findLC(section);
            else it->value = lc;
            it->isEqu = equ;
            it->equSection = equs;
            it->section=section;
            it->defined=true;
            return;
        }
    }
    if(equ == false) node.value = lc - findLC(section);
    else node.value = lc;
    node.defined=true;
    symbol_Table.push_back(node);

}

void setSymbolExtern(string arg, char c){

    regex exp("^(.*r\\d+.*)$");
    if(regex_search(arg,exp)) return;
    exp=("^($.*)$");
    if(regex_search(arg,exp)) return;
    exp=("^(0x\\d+)$");
    if(regex_search(arg,exp)) return;
    exp=("^(\\d+)$");
    if(regex_search(arg,exp)) return;

    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == arg){
            if(it->defined == false){
                it->defined==true;
                it->LG='G';
                return;
            }else{
                writeExternError(); 
                return;
            } // GRESKA, VEC JE UVEZEN
        }
    }

    symbolNode node(arg,0);
    node.size = 2;
    node.section = 0;
    node.LG ='G';
    node.defined=true;
    symbol_Table.push_back(node);

}

void setSymbolGlobal(string arg, char c, int section){

    regex exp("^(.*r\\d+.*)$");
    if(regex_search(arg,exp)) return;
    exp=("^($.*)$");
    if(regex_search(arg,exp)) return;
    exp=("^($0x\\d+)$");
    if(regex_search(arg,exp)) return;
    exp=("^(\\d+)$");
    if(regex_search(arg,exp)) return;
   
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == arg){
            it->LG='G';
            return;
        }
    }

    symbolNode node(arg,0);
    node.section=section;
    node.size = 2;
    node.defined=false;
    node.LG ='G';
    symbol_Table.push_back(node);

}

void writeList(list<Flink_Node> lista){
    cout<< "LISTA:\n";
    list<Flink_Node> :: iterator it;
    for(it = lista.begin(); it != lista.end(); ++it){
        cout<< it->adress << " " << it->adress << "\n";
    }
}

bool findSymbol(string name,int& symbol){
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                symbol = it->value;
                return true;
            }else{ 
                return false;
            }
        }
    }

    return false;
}

bool findSymbolSEC(string name,int& symbol, int& sec){
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                symbol = it->value;
                sec = it->section;
                return true;
            }else{ 
                return false;
            }
        }
    }

    return false;
}

bool findSymbolBP(string name,int& symbol, int& size){
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                symbol = it->value;
                size = it->size;
                return true;
            }else return false;
        }
    }

    return false;
}

void findSymbolPC(string name, int& value, int& section, char& c){

    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                value = it->value;
                section = it->section;
                c=it->LG;
            }
        }
    }

}

void findSymbolREL(string name, int& section, char& LG){
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                section = it->section;
                LG=it->LG;
            }
        }
    }
}

void findSymbolRELOCATION(string name, int& section, char& LG, bool& isEqu, int& equSection){

    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        if(it->name == name){
            if(it->defined == true){
                section = it->section;
                LG = it->LG;
                isEqu = it->isEqu;
                equSection = it->equSection;
            }else{ 
                cout  <<" NIJE DEFINISAN";
                //exit(1);
            }
        }
    }

}

void backpatching(){
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        list<Flink_Node> :: iterator it1;
        for(it1 = it->Flink.begin(); it1 != it->Flink.end(); ++it1){
            int val = 0;
            int size = 0;
            if(findSymbolBP(it->name, val, size)){
                if(it->LG == 'G') val = 0;
                if(size == 1){
                    string pom = intToHex(val);
                    pom = makeTwoBytes(pom);
                    opCode[it1->adress] = pom;
                }else{
                    string pom = intToHex(val);
                    if(pom.size() > 2){
                        string pom1 = pom;
                        if(pom.size() >4) pom.erase(0,4);
                        opCode[it1->adress+1] = pom.erase(pom.size()-2,pom.size());
                        opCode[it1->adress] = pom1.erase(0,pom1.size()-2);
                    }else{
                        opCode[it1->adress+1] = "00";
                        opCode[it1->adress] = makeTwoBytes(pom);
                    }
                }
            }else{
                cout << it->name << endl;
                writeErrorNotDefined();
            }
        }
        
    }

    //changeLC();
};

void changeLC(){

    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        it->value = it->value - findLC(it->section);
    }

}


