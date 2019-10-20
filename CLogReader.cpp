#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std;

#define MAX_FILTER_SIZE     50 //random number for max length mask

class CLogReader
    {
    public:
        CLogReader(){
            
        };
        ~CLogReader(){
            Close();
        };

        bool Open(string fileName){
            file.open(fileName);
            if(!file.good()){
                cout << "File does not exist. Please run the program again\n";
                return false;
            } else {
                return true;
            }

        };
        void Close(){
            file.close();
        };
        bool SetFilter(const char *filter){
            if(strlen(filter) > MAX_FILTER_SIZE ) {
                cout<<"mask size is too large";
                return false;
            } else {
                thisFilter = filter;
                return true;
            }
        };

        bool GetNextLine(char *buf, const int bufsize){

            if (getline(file, str)){
                //managed to read a line

                //copy the line into buffer
                if (str.length() > bufsize){
                    cout<<"Error: string lenght is too long";
                    return false;
                } else {
                    for (int i = 0; i < sizeof(str); i ++){
                        buf[i] = str[i];
                    }
                }
                
                if (strlen(thisFilter) < 1){
                    //filter is not set
                    cout<<"Filter is not set";
                    return false;
                }
                int n = strlen(buf);
                int m = strlen(thisFilter);

                bool mask[n+1][m+1];

                //init DynamicProgramming array to false
                memset(mask, false, sizeof(mask));
                mask[0][0] = true; //for empty mask but empty mask is not possible anyway
                for (int j = 0; j < m; j++) {
                    //init the first row as only * mask can return true
                    if (thisFilter[j] == '*') {
                        mask[0][j + 1] = mask[0][j];
                    }
                }
                //complete the array with copying forward
                for (int i = 1; i <= n; i++) 
                { 
                    for (int j = 1; j <= m; j++) 
                    {   
                        //propagating * matches forward
                        if (thisFilter[j - 1] == '*') 
                            mask[i][j] = mask[i][j - 1] || mask[i - 1][j]; 

                        //actually adding 1 char to mask
                        else if (thisFilter[j - 1] == '?' || buf[i - 1] == thisFilter[j - 1]) 
                            mask[i][j] = mask[i - 1][j - 1]; 

                        //none of the matches worked
                        else 
                            mask[i][j] = false; 
                    } 
                } 
                //this is the DP result for our string with given mask
                if(mask[n][m]){
                    cout << buf <<endl;
                }
                //true as all went successfully with no errors
                return true;
            }
            return false;
        };
    
    private:
        ifstream file;
        const char* thisFilter;
        string str;
    };