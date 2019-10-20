#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "CLogReader.cpp"

using namespace std;

#define MAX_LINE_LENGTH     500 //assume that no log line is longer than 500

int main (int argc, char *argv[]){
    
    string fileName;
    char* mask;

    if(argc != 3){
        cout <<"You entered incorrect amount of input arguments. Please run the program again\n";
        cout <<"Instructions to run:$> parser.exe fileName.log m*a*s*k\n ";
        return 0;
        
    } else {
        fileName = argv[1];
        mask = argv[2];
    }
    CLogReader* logReader = new CLogReader();
    if(!logReader->Open(fileName) || !logReader->SetFilter(mask)){
        return 0;
    }; 

    //was not clear what *buf should be used for
    char *buf = (char *)malloc(MAX_LINE_LENGTH * sizeof(char)); 
    while(logReader->GetNextLine(buf, MAX_LINE_LENGTH));
    cout << "--------------------------------------\n"; //signalise end of program
    delete logReader;

    return 0;
}


