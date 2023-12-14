#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <sstream>
#include <stdio.h>

using namespace std;

string pathConverter(string *str);

int main(){
    string mainPath;
    cout << "Enter the path to the compiled file: ";
    cin >> mainPath;
    string command1 = "touch create.txt";
    string command3 = "objdump -M intel -D chunk.o >> create.txt";
    string command2 = "rm create.txt";
    string command_1 = "g++ -E " + pathConverter(&mainPath) +".cpp -o file.ii";
    string command_2 = "g++ -S file.ii -o file.s";
    string command_3 = "g++ -S file.ii -o chunk.s";
    string command_4 = "as chunk.s -o chunk.o";
    string command_5 = "rm file.s";
    string command_6 = "rm file.ii";
    string command_7 = "rm chunk.s";
    string command_8 = "rm chunk.o";
    string tmp;
    string endProgramm;
    vector<string> words;
    vector<string> code;
    string buf;
    string path = "create.txt";
    int konto = 0;
    char ch;

    system(command_1.c_str());
    system(command_2.c_str());
    system(command_3.c_str());
    system(command_4.c_str());
    system(command1.c_str());
    system(command3.c_str());

    ifstream file;
    file.open(path);

    while(file.get(ch)){
        buf += ch;
    }

    istringstream ist(buf);

    while(ist >> tmp){
        words.push_back(tmp);

        if(tmp[tmp.size()-1] != ':' && tmp.size() == 2){
            try{
                int a = stoi(tmp);
                code.push_back(tmp);
            } catch(...){}
        }
    }


    cout << "Machine code generated:\n";

    for(int i = 0; i < code.size(); ++i){
        cout << "0x" << code[i] << ", ";

        konto++;

        if(konto % 7 == 0) {
            cout << '\n';
        }
    }

    file.close();
    system(command2.c_str());
    system(command_5.c_str());
    system(command_6.c_str());
    system(command_7.c_str());
    system(command_8.c_str());
    cin >> endProgramm;

    return 0;
}

string pathConverter(string *str){
    string newStr;
    int border1 = 0;
    int border2 = 0;

    for(int i = 0; i < (*str).size(); ++i){
        if((*str)[i] == '.'){
            border1= i;
            break;
        }
    }

    for(int i = border1; i >= 0; --i){
        if((*str)[i] == '\\'){
            border2 = i;
            break;
        }
    }

    for(int i = border2+1; i < border1; ++i){
        newStr += (*str)[i];
    }

    return newStr;
}
