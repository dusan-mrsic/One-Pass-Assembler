#include <iostream>
#include "Adressing.h"
#include <string>
#include <regex>
#include "DigitConvert.h"
#include "SymbolTable.h"
#include "RegexSearch.h"
#include "Relocation.h"

using namespace std;

bool sym = false;

int regdir(string arg1){
    
    int regNum = -1;
    regex exp("^(\\*?\\%r\\d+[l|h]?)$");
    if(regex_match(arg1, exp)){
        //cout << "USO2" << endl;
        if(arg1[0] == '*') arg1.erase(0,3);
        else arg1.erase(0,2);
        if(arg1[arg1.size()-1] == 'l' || arg1[arg1.size()-1] == 'h'){
            if(arg1[arg1.size()-1] == 'h') lowHigh = true;
            arg1.erase(arg1.size()-1,1);
            
        }
        if(stoi(arg1) >= 0 || stoi(arg1) < 16){
            regNum = stoi(arg1);
        } 
    }
    return regNum;

};

int regind(string arg1){
    
    int regNum = -1;
    regex exp("^(\\*?\\(\\%r\\d+\\))$");
    if(regex_search(arg1, exp)){
        if(arg1[0] == '*') arg1.erase(0,4);
        else arg1.erase(0,3);
        arg1.erase(arg1.size()-1,arg1.size());
        if(stoi(arg1) >= 0 || stoi(arg1) < 16){
            regNum = stoi(arg1);
        } 
    }
    return regNum;

};

int regindpom(string arg1, int &pom){
    int regNum = -1;
    regex exp("^(\\*?\\-?\\w+\\(\\%r\\d+\\))$");
    if(regex_search(arg1, exp)){
        
        string pomarg = arg1;
        if(arg1[0] == '*') arg1.erase(0,1);
        arg1.erase(arg1.find('('),arg1.size()-arg1.find('('));
        exp="\\-?\\d+";
        if(regex_search(arg1,exp)){
            pom = stoi(arg1);
        }else{
            sym = true;
            if(findSymbol(arg1,pom)){

            }else pom = 0;
        }
        exp="[A-z]\\w*";
        pomarg.erase(0,pomarg.find("(")+3);
        pomarg.erase(pomarg.size()-1,1);
        regNum=stoi(pomarg);
        if(regNum == 7 && regex_search(arg1, exp)) addToRelTable(arg1,3);
        else if(regex_search(arg1, exp)) addToRelTable(arg1,2);
        
    }
    return regNum;
};

int memdir(string arg){
    return 1;
};

int immed(string arg1){
    regex exp("^(\\$\\-?\\d+)$");
    if(regex_search(arg1, exp)){
        if(arg1[0] == '$') arg1.erase(0,1);
        int ret = stoi(arg1);
        return ret;
    }
    exp=("^(\\$0x\\w+)$");
    if(regex_search(arg1, exp)){
        if(arg1[0] == '$') arg1.erase(0,1);
        int ret = stoi(arg1,0,16);
        return ret;
    }
    exp=("^(\\$\\w+)$");
    if(regex_search(arg1, exp)){
        if(arg1[0] == '$') arg1.erase(0,1);
        int value;
        if(inImmed) addToRelTable(arg1,1);
        if(findSymbol(arg1,value)){
            list <symbolNode> :: iterator it;
            for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
                if(it->name == arg1 && it->defined){
                    if(it->LG == 'G') value = 0;
                }
            }
            return value;
        }else{
            return 0;
        }
    }
    exp="^(\\d+)$";
    if(regex_search(arg1, exp) && jump){
        int ret = stoi(arg1);
        return ret;
    }
    exp=("^(0x\\w+)$");
    if(regex_search(arg1, exp) && jump){
        int ret = stoi(arg1,0,16);
        return ret;
    }
    exp=("^(\\w+)$");
    if(regex_search(arg1, exp) && jump){
        int value;
        if(inImmed)addToRelTable(arg1,1);
        if(findSymbol(arg1,value)){
            return value;
        }else{
            return 0;
        }
    }
    
    return -1;

}

int determinateAdressing(string arg, int& pom, int& adressing){
   // cout << "USO" << endl;
    int ret = regindpom(arg,pom);
    if(ret != -1){
        adressing = 3;
        return ret;
    }
    ret = regdir(arg);
    if(ret != -1){
        adressing = 1;
        return ret;
    }
    ret = regind(arg);
    if(ret != -1){
        adressing = 2;
        return ret;
    }
    ret = immed(arg);
    if(ret != -1){
        adressing = 0;
        return ret;
    }
    adressing = 4;
    return 0;
    
}
