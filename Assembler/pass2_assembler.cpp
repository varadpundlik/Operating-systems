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

void getLitTab(vector<pair<string,int>>&litTab){
    ifstream fs;
    fs.open("literal_table.txt",ios::in);
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
        litTab.push_back({decodedInstruction[0],stoi(decodedInstruction[1])});
    }
}

int main(){
    vector<pair<string,int>> symTab;
    vector<pair<string,int>> litTab;

    getSymTab(symTab);
    getLitTab(litTab);
    
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
            else if(decodedInstruction[i][1]=='L'){
                int pos=int(decodedInstruction[i][3]-'0');
                fout<<litTab[pos].second<<" ";
            }
            else if(decodedInstruction[i][1]=='c'){
                decodedInstruction[i].pop_back();
                int n=decodedInstruction[i].length();
                if(decodedInstruction[i][n-1]=='\''){
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
