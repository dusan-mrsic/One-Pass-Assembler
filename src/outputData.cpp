#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include "outputData.h"
#include "SymbolTable.h"
#include "RegexSearch.h"
#include "SectionTable.h"
#include "Relocation.h"

using namespace std;

void writeData(string izlaz){


    ofstream myFile(izlaz);

    for(int i = 0; i < 80; i++){
        myFile << "=";
    }
    myFile << "\n" << setw(43);
    myFile << "SYMBOL TABLE" << endl;
    for(int i = 0; i < 80; i++){
        myFile << "-";
    }

    myFile <<"\n" << setw(13) << "Symbol" << setw(15) << "Value"<< setw(15) << "Defined" << setw(15)<< "L/G"<< setw(15) << "Size" << endl;   
    
    for(int i = 0; i < 80; i++){
        myFile << "-";
    }

    myFile << "\n";
    list <symbolNode> :: iterator it;
    for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
        myFile<< setw(11) << it->name << setw(16) << it->value << setw(13) << it->defined << setw(17) << it->LG << setw(15) << it->size <<  endl;
    }

    for(int i = 0; i < 80; i++){
        myFile << "=";
    }
    
    myFile << "\n" << "\n" << "\n";

    for(int i = 0; i < 80; i++){
        myFile << "=";
    }
    myFile << "\n" << setw(43);
    myFile << "SECTION TABLE" << endl;
    for(int i = 0; i < 80; i++){
        myFile << "-";
    }

    myFile <<"\n" << setw(15) << "Section"<< setw(18) << "Number" << setw(18) << "Offset"<< setw(18) << "L/G" << endl;   
    
    for(int i = 0; i < 80; i++){
        myFile << "-";
    }
    myFile << endl;
    list <sectionNode> :: iterator it1;
    int i = 1;
    for(it1 = sectionTable.begin(); it1 != sectionTable.end(); ++it1){
        myFile<< setw(14) << it1->name << setw(18) << i++<< setw(18) << it1->offset <<  setw(18) << it1->GL << endl;
    }

    for(int i = 0; i < 80; i++){
        myFile << "=";
    }

    myFile << "\n" << "\n" << "\n";
    list <sectionNode> :: iterator it2, it3;
    int j = 0;
    list <relNode> :: iterator it4;
    vector<list <relNode> > :: iterator vec;
    for(it1 = sectionTable.begin(); it1 != sectionTable.end(); ++it1){
        
        it2 = it1;
        it3 = ++it2;
        it2 = it1;
        for(int i = 0; i < 80-it1->name.size()-2; i++){
            if(i == 35) myFile << " " << it1->name << " ";
            myFile << "=";
        }
        myFile << endl;
        int k = 1;
        for(int i = it2->realLC; i < opCode.size() && i < it3->realLC; i++){
            myFile << opCode[i] << " ";
            if(k % 27 == 0) myFile << endl;
            k++;
        }  
        myFile << endl; 
        for(int i = 0; i < 80-it1->name.size()-7; i++){
            if(i == 32) myFile << " .rel " << it1->name << " ";
        myFile << "-";
        }
        myFile << endl;
        myFile  << setw(15) << "Offset"<< setw(18) << "Type" << setw(18) << "Symbol"<< setw(18) << "Section" << endl;   
        for(it4 = relTables[j].begin(); it4 != relTables[j].end(); ++it4){
            if(it4->section == -5) continue;
            myFile<< setw(15) << it4->offset << setw(18) << it4->type << setw(18) << it4->symbol << setw(18);
            if(it4->section != -1)myFile << it4->section << "\n";
            else myFile << "-" << "\n";
        }
        j++;
        myFile << endl << endl;   

    }



    myFile.close();

}

void writeErrorDest(){
    
    ofstream myFile("izlaz.txt");
    myFile << "****************************************\n";
    myFile << "GRESKA U DESTINACIONOM OPERANDU" << endl;
    myFile << "****************************************\n";
    myFile.close();

    exit(1);

}

void writeExternError(){
    
    ofstream myFile("izlaz.txt");
    myFile << "****************************************\n";
    myFile << "SIMBOL JE VEC DEFINISAN" << endl;
    myFile << "****************************************\n";
    myFile.close();

    exit(1);

}

void writeErrorNotDefined(){

    ofstream myFile("izlaz.txt");
    myFile << "****************************************\n";
    myFile << "SIMBOL NIJE DEFINISAN" << endl;
    myFile << "****************************************\n";
    myFile.close();

    exit(1);
}