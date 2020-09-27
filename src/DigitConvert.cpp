#include <iostream>
#include <string>
#include "DigitConvert.h"
#include "SymbolTable.h"
#include <iomanip>

using namespace std;

string intToHex(int num){
    std::stringstream sstream;
    sstream << std::hex << num;
    std::string result = sstream.str();
    return result;
}

string makeTwoBytes(string hex){
    string ret = hex;
    if(hex.size()==1){
        ret= "0" + hex;
    }
    return ret;
}

string makeWord(string first, string second, string third, string fourth, string fifth, string sixst, string seventh){
    string ret;
    ret = first + second;
    opCode.push_back(first);
    opCode.push_back(second);
    if(third != "-1"){
        ret = ret + third;
        opCode.push_back(third);
    }
    if(fourth != "-1"){
        ret = ret + fourth;
        opCode.push_back(fourth);
    }
    if(fifth != "-1"){
        ret = ret + fifth;
        opCode.push_back(fifth);
    }
    if(sixst != "-1"){
        ret = ret + sixst;
        opCode.push_back(sixst);
    }
    if(seventh != "-1"){
        ret = ret + seventh;
        opCode.push_back(seventh);
    }
    return ret;

}