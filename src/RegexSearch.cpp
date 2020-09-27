#include "RegexSearch.h"
#include "SymbolTable.h"
#include <regex>
#include <string>
#include <list>
#include "DigitConvert.h"
#include "Adressing.h"
#include "SectionTable.h"
#include "Relocation.h"
#include "outputData.h"

using namespace std;

list <equNode> equList;
// NO ARGUMENT FUNCTIONS (halt, iret, ret)

bool jump = false;
bool firstArg = false;
bool oneArg = false;
bool lowHigh = false;

bool searchInsNoArg(string& line, int& code){

    string initialLine = line;
    char c = '1';
    bool retValue = false;
    
    regex exp("^(\\s*halt\\s*)$");
    if(regex_search(line,exp)){
        retValue = true;
        int position = line.find('t');
        line.erase(position + 1, line.size()-position);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        code = 0;
        opCode.push_back("00");
    }

    exp="^(\\s*iret\\s*)$";
    if(regex_search(line,exp)){
        retValue = true;
        int position = line.find('t');
        line.erase(position + 1, line.size()-position);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        code = 1;
        opCode.push_back("08");
    }

    exp="^(\\s*ret\\s*)$";
    if(regex_search(line,exp)){
        retValue = true;
        int position = line.find('t');
        line.erase(position + 1, line.size()-position);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        code = 2;
        opCode.push_back("10");
    }

    // FIRST BYTE OF INSTRUCTION
    if(retValue) {
        locationCounter++;
    }

    return retValue;


}

//LABEL
bool searchLabel(string &line, string &arg, int& code){
    
    bool retValue = false;
    string line1 = line;
    regex exp("^(\\s*\\w+\\s*:)");
    if(regex_search(line,exp)){

        int position = line.find(':');
        line.erase(position, line.size()-position);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

        setSymbolLabel(line,locationCounter, section, false, 0);

        int position1 = line1.find(':');
        line1.erase(0, position1 + 1);
        line = line1;

        string arg1, arg2;
        if(searchInsNoArg(line, code)){
            //locationCounter++;
        }else if(searchIns(line,arg, code)){

        }else if(searchIns2(line,arg1,arg2, code)){
            
        }else if(searchEqu(line)){

        }else if(searchSWB(line)){

        }else if(searchEG(line)){
        
        }else if(searchSection(line)){

        }
        retValue=true;
    }

    return retValue;

}

// ONE ARGUMENT FUNCTIONS(int, call, jmp, jeq, jne, jgt, push, pop)


bool searchIns(string &line, string &arg, int& code){

    string initialLine = line;
    char c = '1';
    bool retValue = false;
    regex exp;
    
    
    
    
    

    exp="^(\\s*int\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find('t');
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "int";
        retValue=true;
        code = 3;
        jump = true;
    }

    exp="^(\\s*call\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("l");
        line.erase(0, position + 2);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "call";
        retValue=true;
        code = 4;
        jump = true;
    }

    exp="^(\\s*jmp\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("p");
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "jmp";
        retValue=true;
        code = 5;
        jump = true;
    }

    exp="^(\\s*jeq\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find('q');
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "jeq";
        retValue=true;
        code = 6;
        jump = true;
    }

    exp="^(\\s*jne\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find('e');
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "jne";
        retValue=true;
        code = 7;
        jump = true;
    }

    exp="^(\\s*jgt\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find('t');
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "jgt";
        retValue=true;
        code = 8;
        jump = true;
    }

    exp="^(\\s*push\\s+[^\\s|,]+\\s*)$";
    
    if(regex_search(line,exp)){
        
        string line1 = line;
        int position = line.find('h');
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        arg = line;
        line = "push";
        retValue=true;
        code = 9;
    }

    exp="^(\\s*pop\\s+[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("p ");
        line.erase(0, position + 1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        arg = line;
        line = "pop";
        retValue=true;
        code = 10;
    }
    if(retValue){   // FIRST BYTE OF INSTRUCTION

        regex op(".*\\$.*");
        if(regex_search(arg,op) && line != "push") writeErrorDest();
        oneArg = true;
        adressing(initialLine,c,line);
        int b = makeFirstByte(code,c); 
        string res = intToHex(b);
        res = makeTwoBytes(res);
    

        string thirdByte = "-1", fourthByte = "-1";
        // SECOND,THIRD, FOURTH BYTE OF INSTRUCTION

        arg = changeArg(arg);

    
        string secondByte = makeSecondByte(arg,c, thirdByte, fourthByte);
        locationCounter = locationCounter + 2;
        setSymbol(arg,locationCounter,c, section );
        if(c == 'w' && fourthByte == "-1") fourthByte == "00";
        if(thirdByte != "-1") locationCounter++;
        if(fourthByte != "-1") locationCounter++;
        secondByte = makeTwoBytes(secondByte);
        thirdByte = makeTwoBytes(thirdByte);
        fourthByte = makeTwoBytes(fourthByte);
    
        string opWord = makeWord(res,secondByte,thirdByte,fourthByte, "-1", "-1", "-1");
    
        jump = false;
        oneArg = false;
        //cout << "\n WORD: " << opWord << '\n';
    }




    return retValue;

}

// TWO ARGUMENT FUNCTIONS(xchg, mov, add, sub, mul, div, cmp, not, and, or, xor, test, shl, shr)

bool searchIns2(string &line, string &arg1, string &arg2, int& code){

    

    string initialLine = line;
    char c = '1';
    bool retValue = false;
    regex exp;

    exp="^(\\s*xchg[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("xchg");
        line.erase(position, 5);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "xchg";
        retValue = true;
        code = 11;
    }

    exp="^(\\s*mov[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("mov");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "mov";
        retValue = true;
        code = 12;
    }

    exp="^(\\s*add[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("add");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "add";
        retValue = true;
        code = 13;
    }

    exp="^(\\s*sub[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("sub");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "sub";
        retValue=true;
        code = 14;
    }

    exp="^(\\s*mul[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("mul");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "mul";
        retValue=true;
        code = 15;
    }

    exp="^(\\s*div[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("div");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "div";
        retValue=true;
        code = 16;
    }

    exp="^(\\s*cmp[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("cmp");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "cmp";
        retValue=true;
        code = 17;
    }

    exp="^(\\s*not[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("not");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "not";
        retValue=true;
        code = 18;
    }

    exp="^(\\s*and[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("and");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "and";
        retValue=true;
        code = 19;
    }

    exp="^(\\s*or[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("or");
        line.erase(position, 3);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "or";
        retValue=true;
        code = 20;
    }

    exp="^(\\s*xor[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("xor");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "xor";
        retValue=true;
        code = 21;
    }

    exp="^(\\s*test[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("test");
        line.erase(position, 5);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "test";
        retValue=true;
        code = 22;
    }

    exp="^(\\s*shl[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("shl");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "shl";
        retValue=true;
        code = 23;
    }

    exp="^(\\s*shr[bw]?\\s+[^\\s|,]+\\s*,\\s*[^\\s|,]+\\s*)$";
    if(regex_search(line,exp)){
        string line1 = line;
        int position = line.find("shr");
        line.erase(position, 4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line1 = line;
        position = line.find(',');
        line.erase(position, line.size()- position);
        arg1 = line;
        line1.erase(0,position+1);
        arg2 = line1;
        line = "shr";
        retValue=true;
        code = 24;
        regex op(".*\\$.*");
        if(regex_search(arg1,op)) writeErrorDest();
        if(regex_search(arg2,op)) writeErrorDest();
    }
    
    if(retValue){

        regex op(".\\$.*");
        if(regex_search(arg2,op)) writeErrorDest();
        // FIRST BYTE OF INSTRUCTION
        adressing(initialLine,c,line);
        int b = makeFirstByte(code,c); 
        string res = intToHex(b);
        res = makeTwoBytes(res);
    

        string thirdByte = "-1", fourthByte = "-1", fifthByte = "-1", sixstByte = "-1", seventhByte = "-1";
        // SECOND,THIRD, FOURTH BYTE OF INSTRUCTION

        firstArg = true;
        arg1 = changeArg(arg1);

        string secondByte = makeSecondByte(arg1,c, thirdByte, fourthByte);
   
        locationCounter+=2;
        setSymbol(arg1,locationCounter, c, section);
        if(thirdByte != "-1") locationCounter++;
        if(fourthByte != "-1") locationCounter++;
        //else locationCounter+=1;

        firstArg = false;
        arg2 = changeArg(arg2);
    
        fifthByte = makeSecondByte(arg2,c,sixstByte,seventhByte);
    
    
        locationCounter+=1;
        setSymbol(arg2,locationCounter, c, section);
        if(sixstByte != "-1") locationCounter++;
        if(seventhByte != "-1") locationCounter++;
        //else locationCounter+=1;

        secondByte = makeTwoBytes(secondByte);
        thirdByte = makeTwoBytes(thirdByte);
        fourthByte = makeTwoBytes(fourthByte);
        fifthByte = makeTwoBytes(fifthByte);
        sixstByte = makeTwoBytes(sixstByte);
        seventhByte = makeTwoBytes(seventhByte);

        string opWord = makeWord(res,secondByte,thirdByte,fourthByte,fifthByte,sixstByte,seventhByte);
        //cout << "\n WORD: " << opWord << '\n';
    }

    

    return retValue;


}

// SKIP, WORD, BYTE

bool searchSWB(string &line){

    bool retValue = false;

    regex exp("^(\\s*.skip\\s+\\d+*\\s*)");
    if(regex_search(line, exp)){
        retValue = true;
        int pos = line.find("p");
        line.erase(0,pos+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pom = stoi(line);
        for(int i = 0; i < pom; i++){
            opCode.push_back("00");
            locationCounter++;
        }
    }

    exp="^(\\s*.byte\\s+[\\w\\+\\-][\\+\\w,\\-]*\\s*)";
    if(regex_search(line,exp)){
        retValue = true;
        bool uso = false;
        int pos = line.find("e");
        line.erase(0,pos+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        for(int i = 0; i < line.size();){
            string pom;
            while(line[i] != ',' && i < line.size()){
                pom = pom + line[i++];
            }
            i++;
            regex exp("^(\\-?[0-9]+)$");
            if(regex_search(pom,exp)){
                uso = true;
                int val = stoi(pom);
                string val1 = intToHex(val);
                if(val1.size() > 2) val1.erase(0,val1.size()-2);
                opCode.push_back(makeTwoBytes(val1));
                locationCounter+=1;

            }
            exp=("^(0x\\w+)$");
            if(regex_search(pom,exp)){
                uso = true;
                string pom1 = pom;
                pom.erase(0,2);
                int val = stoi(pom,0,16);
                string val1 = intToHex(val);
                opCode.push_back(makeTwoBytes(val1));
                locationCounter+=1;
                pom = pom1;

            }
            exp=("^(\\w+)$");
            if(regex_search(pom,exp) && !uso){
                int res = -1;
                addToRelTable(pom,6);
                if(findSymbol(pom, res)){
                    string val1 = intToHex(res);
                    opCode.push_back(makeTwoBytes(val1));
                    locationCounter+=1;
                }else{
                    if(res == -1) {
                        opCode.push_back("00");
                        setSymbol(pom,locationCounter, 'b', section);
                        locationCounter+=1;
                    }
                } 
            }
        }
        uso = false;
    }

    exp="^(\\s*.word\\s+[\\w\\+\\-][\\+\\w,\\-]*\\s*)";
    if(regex_search(line,exp)){
        retValue = true;
        bool uso = false;
        int pos = line.find("d");
        line.erase(0,pos+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        for(int i = 0; i < line.size();){
            string pom;
            while(line[i] != ',' && i < line.size()){
                pom = pom + line[i++];
            }
            i++;
            regex exp("^(\\-?\\d+)$");
            if(regex_search(pom,exp)){
                uso = true;
                int val = stoi(pom);
                string val1 = intToHex(val);
                if(val1.size() > 4) val1.erase(0,val1.size()-4);
                if(val1.size()>2){
                    string val2 = val1;
                    opCode.push_back(val2.erase(0,val2.size()-2));
                    opCode.push_back(makeTwoBytes((val1.erase(val1.size()-2,val1.size()))));
                    
                    locationCounter+=2;
                }else{
                    opCode.push_back(makeTwoBytes(val1));
                    opCode.push_back("00");
                    locationCounter+=2;
                }

            }
            exp=("^(0x\\w+)$");
            if(regex_search(pom,exp)){
                string pom1 = pom;
                uso = true;
                pom.erase(0,2);
                int val = stoi(pom,0,16);
                string val1 = intToHex(val);
                if(val1.size()>2){
                    string val2 = val1;
                    opCode.push_back((val1.erase(val1.size()-2,val1.size())));
                    opCode.push_back(val2.erase(0,val2.size()-2));
                    locationCounter+=2;
                }else{
                    opCode.push_back(makeTwoBytes(val1));
                    opCode.push_back("00");
                    locationCounter+=2;
                }
                pom = pom1;

            }
            exp=("^(\\w+)$");
            if(regex_search(pom,exp) && !uso){
                int res = -1;
                addToRelTable(pom,5);
                if(findSymbol(pom, res)){
                    string val1 = intToHex(res);
                    if(val1.size()>2){
                        string val2 = val1;
                        opCode.push_back((val1.erase(val1.size()-2,val1.size())));
                        opCode.push_back(val2.erase(0,val2.size()-2));
                        locationCounter+=2;
                    }else{
                        opCode.push_back(makeTwoBytes(val1));
                        opCode.push_back("00");
                        locationCounter+=2;
                }
                }else{
                    if(res == -1) {
                        opCode.push_back("00");
                        opCode.push_back("00");
                        setSymbol(pom,locationCounter, '1', section);
                        locationCounter+=2;
                    }
                } 
            }
            uso = false;
        }
    }

    return retValue;
}

// EXTERN GLOBAL

bool searchEG(string &line){

    regex exp;
    bool retValue=false;

    exp="^(\\s*\\.extern\\s+\\w+(,\\s*\\w+)*\\s*)$";
    if(regex_search(line,exp)){
        retValue = true;
        int pos = line.find("n");
        line.erase(0,pos+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        for(int i = 0; i < line.size();){
            string pom;
            while(line[i] != ',' && i < line.size()){
                pom = pom + line[i++];
                
            }
            i++;
            setSymbolExtern(pom,'E');

        }
    }
    exp="^(\\s*.global\\s+\\w+(,\\s*\\w)*\\s*)$";
    if(regex_search(line,exp)){
        retValue = true;
        int pos = line.find("bal");
        line.erase(0,pos+4);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        for(int i = 0; i < line.size();){
            string pom;
            while(line[i] != ',' && i < line.size()){
                pom = pom + line[i++];
                
            }
            i++;
            setSymbolGlobal(pom,'G', section);

        }

    }

    return retValue;

}

//EQU

bool searchEqu(string &line){

    bool retValue = false;

    regex exp("^(\\s*.equ\\s+\\w+\\s*,\\s*[\\+\\-\\w]+\\s*)");
    if(regex_search(line,exp)){
        retValue = true;
        int pos = line.find("u");
        line.erase(0,pos+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        string line1 = line;
        pos = line.find(',');
        line.erase(pos, line.size()- pos);
        string arg1 = line;
        line1.erase(0,pos+1);
        string arg2 = line1;
        int sec;
        if(countEqu(arg2,sec)){
            int pom = stoi(arg2);
            equ= true;
            setSymbolLabel(arg1, pom, section, true, sec);
            equ=false;
        }else{
            putInEquList(arg1,arg2);
        }

    }

    return retValue;

}

//SECTION

bool searchSection(string& line){
    
    bool retValue=false;
    regex exp("\\s*.section\\s+\\w+:\\s*");
    if(regex_match(line, exp)){
        section++;
        retValue = true;
        line.erase(0,line.find('n')+1);
        //line.erase(line.size()-1, line.size());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(line.size()-1,1);
        setSection(line,locationCounter);
        addList();
    }

    return retValue;

}

void adressing(string line, char& c, string ins){

    line.erase(line.find(ins) + ins.size() + 1, line.size());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
    if(line[line.size()-1] == 'w' && line.size() != ins.size()) c = 'w';
    else if(line[line.size()-1] == 'b'  && line.size() != ins.size()) c = 'b';
    else c = '1';


}

int makeFirstByte(int code, char c){
    int byte = 0;
    code = code << 3;
    byte = code;
    int mask = 1;
    if(c != 'b') byte = byte | (mask << 2);
    return byte;
}

bool inImmed = false;

string makeSecondByte(string arg,char c, string& thirdByte, string& fourthByte){
    int pom = -1;
    int adressing = -1;
    //cout << "USO";
    int reg = determinateAdressing(arg,pom,adressing); // return value of used register
    inImmed = true;

    bool imm=false;
    // IMMED
    if(adressing == 0){
        imm = true;
        reg = 0;
        thirdByte = intToHex(immed(arg));
        if(thirdByte.size()>2){
            string pom = thirdByte;
            if(thirdByte.size() > 4) thirdByte.erase(0,thirdByte.size()-4);
            fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
            thirdByte = pom.erase(0,pom.size()-2);
        }
    }
    inImmed = false;

    //REGDIR
    if(adressing == 1){
        /*thirdByte = intToHex(0);
        if(thirdByte.size()>2){
            string pom = thirdByte;
            fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
            thirdByte = pom.erase(0,pom.size()-2);
        }*/
    }

    //REGIND
    if(adressing == 2){
        /*thirdByte = intToHex(0);
        if(thirdByte.size()>2){
            string pom = thirdByte;
            fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
            thirdByte = pom.erase(0,pom.size()-2);
        }*/
    }

    // REGINDPOM
    if(adressing == 3){
        if(arg[0] == '*') arg.erase(0,1);
        arg.erase(arg.find('('),arg.size()-arg.find('('));
        thirdByte = intToHex(pom);
        if(reg == 7 && sym){
            if(oneArg){
                addToPomPcList(locationCounter+2,locationCounter+4,arg,section);
            }else{
                if(firstArg){
                    addToPomPcList(locationCounter+2,locationCounter+7,arg,section);
                }else{
                    addToPomPcList(locationCounter+1,locationCounter+3,arg,section);
                }
            }
        }
        sym = false;
        if(thirdByte.size() > 4) thirdByte.erase(0,4);
        if(thirdByte.size()>2){
            string pom = thirdByte;
            fourthByte = makeTwoBytes(thirdByte.erase(thirdByte.size()-2,thirdByte.size()));
            thirdByte = makeTwoBytes(pom.erase(0,pom.size()-2));
        }
    }
    

    // MEMDIR
    if(adressing == 4){
        //cout << "USO U MEMDIR" << endl;
        int pom = 0;
        regex exp;
        bool uso = false;
        exp="^(\\*?0x.*)$";
        if(regex_search(arg,exp)){
            uso = true;
            if(arg[0]=='*') arg.erase(0,1);
            thirdByte = arg.erase(0,2);
            if(thirdByte.size()>2){
                string pom = thirdByte;
                fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
                thirdByte = pom.erase(0,pom.size()-2);
            }
        }
        exp="^(\\*?\\d+)$";
        if(regex_search(arg,exp) && !uso){
            uso = true;
            if(arg[0]=='*') arg.erase(0,1);
            int pom1 = stoi(arg);
            thirdByte = intToHex(pom1);
            //cout << thirdByte << endl;
            if(thirdByte.size()>2){
                string pom = thirdByte;
                fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
                thirdByte = pom.erase(0,pom.size()-2);
            }
        }
        exp="^(\\*?\\w+)$";
        if(regex_search(arg,exp) && !uso){
            string lg;
            if(arg[0]=='*') arg.erase(0,1);
            addToRelTable(arg,4);
            list <symbolNode> :: iterator it;
            for(it = symbol_Table.begin(); it != symbol_Table.end(); ++it){
                if(it->name == arg){
                    if(it->LG == 'G') pom = 0;
                    else pom = it->value;
                }
            }
            thirdByte = intToHex(pom);
            if(thirdByte.size()>2){
                string pom = thirdByte;
                fourthByte = thirdByte.erase(thirdByte.size()-2,thirdByte.size());
                thirdByte = pom.erase(0,pom.size()-2);
            }
        }
        uso = false;
        
    }
    
    if(fourthByte == "-1" && c != 'b' && adressing != 1 && adressing != 2) fourthByte="00";
    adressing = adressing << 5;
    if(reg == -1) reg = 0;
    adressing = adressing | (reg << 1);
    if(lowHigh) adressing = adressing | 1;
    lowHigh = false;
    string res1 = intToHex(adressing);
    return res1;

}

bool countEqu(string &arg, int& equSection){

    int section = 0;
    int result = 0;
    string sign = "+";
    for(int i = 0; i < arg.size();){
        string pom;
        while(((arg[i] != '+') && (arg[i] != '-')) && i < arg.size()){
            pom = pom + arg[i];
            i++;
        }
        bool uso = false;
        regex exp("^(\\d+)$");
        if(regex_search(pom,exp)){
            uso = true;
            int num = stoi(pom);
            if(sign == "+") result +=num;
            else result -= num;
        }
        exp=("^(0x\\w+)$");
        if(regex_search(pom,exp)){
            uso = true;
            int num = stoi(pom,0,16);
            if(sign == "+") result +=num;
            else result -= num;
        }
        exp=("^(\\w+)$");
        if(regex_search(pom,exp) && !uso){
            int res;
            int sec;
            if(findSymbolSEC(pom, res, sec)){
                //cout << "SEC" << sec << endl;
                if(sign == "+"){ 
                    result +=res;
                    section += sec;
                }
                else{
                    result -= res;
                    section -= sec;
                } 
            }else{
                if(equSearched == true) {
                    cout<< "\nGRESKA U EQU\n";
                    //exit(1);
                }
                equSearched = true;
                return false;
            } 
        }
         
        if(i<arg.size()) sign = arg[i++];

    }
    
    arg = to_string(result);
    equSection = section;
    //cout << arg;
    
    return true;

}

void putInEquList(string arg1, string arg2){
    
    equNode node;
    node.symbol = arg1;
    node.equation = arg2;
    node.s = section;
    //node.section = section;
    equList.push_back(node);
}

string changeArg(string arg1){
    regex exppc("^(.*pc.*)$");
    if(regex_search(arg1,exppc)){
        regex exp1("\\b(pc)([^ ]*)");
        arg1 = regex_replace(arg1,exp1,"r7$2");
    }
    return arg1;
}

void countAllEques(){
    list <equNode> :: iterator it;
    for(it = equList.begin(); it != equList.end(); ++it){
        int sec;
        countEqu(it->equation, sec);
        int pom = stoi(it->equation);
        equ = true;
        setSymbolLabel(it->symbol, pom, it->s, true, sec);
        equ = false;
    }
}