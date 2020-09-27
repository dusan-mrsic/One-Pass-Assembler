#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "RegexSearch.h"
#include "SymbolTable.h"
#include "SectionTable.h"
#include "Relocation.h"
#include "outputData.h"


using namespace std;


int main(int argc, char* argv[]){

    string ulaz(argv[3]);
    string izlaz(argv[2]);

    ifstream myFile("../" + ulaz);
    myFile.open(ulaz);

    string line = "-1", arg = "-1", arg1 = "-1", arg2 = "-1";

    while(getline(myFile,line)){
        //cout <<"LINE: "<< line << "\n";
        int code = -1;

    
        if(searchLabel(line, arg, code)){

        }else if(searchInsNoArg(line, code)){
            //locationCounter++;
        }else if(searchIns(line,arg, code)){

        }else if(searchIns2(line,arg1,arg2, code)){
            
        }else if(searchEqu(line)){

        }else if(searchSWB(line)){

        }else if(searchEG(line)){
        
        }else if(searchSection(line)){

        }

    }
    
    countAllEques();
    backpatching();
    fillPomBytes();
    fillRelTable();
    
    
    writeData(izlaz);

    myFile.close();


}

