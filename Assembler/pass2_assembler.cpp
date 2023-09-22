#include<bits/stdc++.h>
using namespace std;

void getSymTab(vector<pair<string,int>>&symTab){
    ifstream fs;
    fs.open("symbol_table.txt",ios::in);
    string rec;
    while(fs>>rec){
        getline(fs,rec);
        vector<string> decodedInstruction;
        string word;
        for (auto i : rec)
        {
            if (i == ' ')
            {
                decodedInstruction.push_back(word);
                word = "";
            }
            else
                word += i;
        }
        decodedInstruction.push_back(word);
        symTab.push_back({decodedInstruction[0],stoi(decodedInstruction[1])});
    }
}

int main(){
    vector<pair<string,int>> symTab;
    getSymTab(symTab);
    

    map<string, pair<string, int>> memo;
    memo["STOP"] = {"IS", 00};
    memo["ADD"] = {"IS", 01};
    memo["SUB"] = {"IS", 02};
    memo["MULT"] = {"IS", 03};
    memo["MOVER"] = {"IS", 04};
    memo["MOVEM"] = {"IS", 05};
    memo["COMP"] = {"IS", 06};
    memo["BC"] = {"IS", 07};
    memo["DIV"] = {"IS", 8};
    memo["READ"] = {"IS", 9};
    memo["PRINT"] = {"IS", 10};
    memo["START"] = {"AD", 01};
    memo["END"] = {"AD", 02};
    memo["ORIGIN"] = {"AD", 03};
    memo["EQU"] = {"AD", 04};
    memo["LTORG"] = {"AD", 05};
    memo["DS"] = {"DL", 01};
    memo["DC"] = {"DL", 02};

    map<string, int> reg;
    reg["AREG"] = 1;
    reg["BREG"] = 2;
    reg["CREG"] = 3;
    reg["DREG"] = 4;

    map<string, int> concode;
    concode["LT"] = 1;
    concode["LE"] = 2;
    concode["EQ"] = 3;
    concode["GT"] = 4;
    concode["GE"] = 5;
    concode["ANY"] = 6;

    ifstream fic;
    fic.open("intermediate_code.txt",ios::in);

    ofstream fout;
    fout.open("output.txt",ios::out);

    while (!fic.eof())
    {
        string instr;
        getline(fic, instr);
        vector<string> decodedInstruction;
        string word;
        for (auto i : instr)
        {
            if (i == ' ')
            {
                decodedInstruction.push_back(word);
                word = "";
            }
            else
                word += i;
        }
        decodedInstruction.push_back(word);

        for(int i=0;i<decodedInstruction.size();i++){
            if(decodedInstruction[i]=="(DL,02)"){
                fout<<"No Machine code";
                break;
            }
            else if(decodedInstruction[i]=="(DL,01)"){
                fout<<"00 ";
                continue;
            }
            else if(decodedInstruction[i][1]=='I'){
                fout<<decodedInstruction[i][4]<<decodedInstruction[i][5]<<" ";
            }
            else if(decodedInstruction[i].length()==3){
                fout<<decodedInstruction[i][1]<<" ";
            }
            else if(decodedInstruction[i][1]=='A'){
                fout<<"No machine code ";
                break;
            }
            else if(decodedInstruction[i][1]=='s'){
                int pos=int(decodedInstruction[i][3]-'0');
                fout<<symTab[pos].second<<" ";
            }
            else if(decodedInstruction[i][1]=='c'){
                decodedInstruction[i].pop_back();
                int n=decodedInstruction[i].length();
                if(decodedInstruction[i][n-1]=='\39'){
                    cout<<"ye kaha aa gaye hum"<<endl;
                    int pos=stoi(decodedInstruction[i].substr(4,decodedInstruction[i].size()-1));
                    fout<<pos<<" ";
                    continue;
                }
                int pos=stoi(decodedInstruction[i].substr(3,decodedInstruction[i].size()));
                fout<<pos<<" ";
                break;
            }

        }
        fout<<endl;
    }
    cout<<"Pass 2 completed check output.txt"<<endl;
}

