#include "SectionTable.h"
#include <iostream>

using namespace std;

list<sectionNode> sectionTable;


void setSection(string name, int locationCounter){

    sectionNode node;
    node.name = name;
    node.GL = 'L';
    node.offset = "00";
    node.realLC = locationCounter;

    sectionTable.push_back(node);

}

int findLC(int section){
    list <sectionNode> :: iterator it1;
    int cnt = 1;
    for(it1 = sectionTable.begin(); it1 != sectionTable.end(); ++it1){
        if(cnt == section) return it1->realLC;
        else cnt++;
    }

    return 0;
}