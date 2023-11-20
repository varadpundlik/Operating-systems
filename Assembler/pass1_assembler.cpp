#include <bits/stdc++.h>
using namespace std;

void displaySymTab(vector<pair<string, int>> &s)
{
    ofstream fsym;
    fsym.open("symbol_table.txt", ios::out);
    for (auto i : s)
    {
        fsym << i.first << " " << i.second << endl;
    }
}

void displayLitTab(vector<pair<string, int>> &s)
{
    ofstream flit;
    flit.open("literal_table.txt", ios::out);
    for (auto i : s)
    {
        flit << i.first << " " << i.second << endl;
    }
}

void displayPoolTab(vector<int> &s)
{
    ofstream fpool;
    fpool.open("pool_table.txt", ios::out);
    for (auto i : s)
    {
        fpool << i << endl;
    }
}

int findElement(vector<pair<string, int>> s, string k)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i].first == k)
            return i;
    }
    return -1;
}

int main()
{
    map<string, pair<string, string>> memo;
    memo["STOP"] = {"IS", "00"};
    memo["ADD"] = {"IS", "01"};
    memo["SUB"] = {"IS", "02"};
    memo["MULT"] = {"IS", "03"};
    memo["MOVER"] = {"IS", "04"};
    memo["MOVEM"] = {"IS", "05"};
    memo["COMP"] = {"IS", "06"};
    memo["BC"] = {"IS", "07"};
    memo["DIV"] = {"IS", "08"};
    memo["READ"] = {"IS", "09"};
    memo["PRINT"] = {"IS", "10"};
    memo["START"] = {"AD", "01"};
    memo["END"] = {"AD", "02"};
    memo["ORIGIN"] = {"AD", "03"};
    memo["EQU"] = {"AD", "04"};
    memo["LTORG"] = {"AD", "05"};
    memo["DS"] = {"DL", "01"};
    memo["DC"] = {"DL", "02"};

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

    vector<pair<string, int>> symTab;
    vector<pair<string, int>> litTab;
    vector<int> poolTab;

    ifstream fin;
    fin.open("input.txt", ios::in);

    ofstream fout;
    fout.open("intermediate_code.txt", ios::out);

    int lc = 0;
    int pc=0;

    while (!fin.eof())
    {
        string instr;
        getline(fin, instr);
        vector<string> decodedInstruction;
        string word;
        lc++;
        for (auto i : instr)
        {
            if (i == ' ' || i == ',')
            {
                decodedInstruction.push_back(word);
                word = "";
            }
            else
                word += i;
        }
        decodedInstruction.push_back(word);
        for (int i = 0; i < decodedInstruction.size(); i++)
        {
            if (decodedInstruction[i] == "START"){
                lc = stoi(decodedInstruction[i + 1]) - 1;
                cout<<lc<<endl;
                fout << "(AD,01) ";
            }
            else if (decodedInstruction[i] == "DC")
            {
                fout << "(DL,02) (c," << decodedInstruction[i + 1] << ") ";
                i++;
                continue;
            }
            else if (decodedInstruction[i] == "EQU")
            {
                fout << "(AD,04) ";
                int pos = findElement(symTab, decodedInstruction[i - 1]);
                if (pos != -1)
                {
                    symTab[pos].second = symTab[findElement(symTab,decodedInstruction[i + 1])].second;
                }
                i++;
                fout<<"(c,"<<symTab[pos].second<<") ";
            }
            else if (decodedInstruction[i]=="ORIGIN"){
                //update origin handling code for statement like ORIGIN A+5

                int pos=findElement(symTab,decodedInstruction[i+1]);
                if(pos!=-1){
                    lc=symTab[pos].second+stoi(decodedInstruction[i+2]);
                }
                else{
                    lc=stoi(decodedInstruction[i+1]);
                }
                i++;
                fout << "(AD,03) (c," << lc << ") ";
                i+=2;
            }
            else if (decodedInstruction[i] == "LTORG")
            {
                fout << "(AD,05) "<<endl;

                poolTab.push_back(pc+1);

                for (int i=pc;i<litTab.size();i++)
                {
                    if (litTab[i].second == 0)
                    {
                        string s=litTab[i].first.substr(2);
                        s.pop_back();
                        fout << "(DL,01) (c," << s << ") "<<endl;
                        litTab[i].second = lc++;
                        pc=i;
                    }
                }
                
            }
            else if (memo.find(decodedInstruction[i]) != memo.end())
                fout << "(" << memo[decodedInstruction[i]].first << "," << memo[decodedInstruction[i]].second << ") ";

            else if (reg.find(decodedInstruction[i]) != reg.end())
                fout << "(" << reg[decodedInstruction[i]] << ") ";

            else if (concode.find(decodedInstruction[i]) != concode.end())
                fout << "(" << concode[decodedInstruction[i]] << ") ";

            else if (decodedInstruction[i][0] == '='){
                litTab.push_back({decodedInstruction[i], 0});
                fout << "(L," << litTab.size() - 1 << ") ";
            }
            else if (decodedInstruction[i][0] >= '0' && decodedInstruction[i][0] <= '9')
                fout << "(c," << decodedInstruction[i] << ") ";

            else if (decodedInstruction[i][1] >= '0' && decodedInstruction[i][1] <= '9')
                fout << "(c," << decodedInstruction[i] << ") ";

            else
            {
                if (i == 0)
                {
                    int pos = findElement(symTab, decodedInstruction[i]);
                    if (pos == -1)
                    {
                        symTab.push_back({decodedInstruction[i], lc});
                    }
                    else
                    {
                        symTab[pos].second = lc;
                    }
                }
                else
                {
                    int pos = findElement(symTab, decodedInstruction[i]);
                    if (pos == -1)
                    {
                        symTab.push_back({decodedInstruction[i], lc});
                        fout << "(s," << symTab.size() - 1 << ") ";
                    }
                    else
                    {
                        fout << "(s," << pos << ") ";
                    }
                }
            }
        }
        fout << endl;
    }
    for (auto &literal : litTab)
    {   
        //write code to add in pooltable
        poolTab.push_back(pc+1);
        if (literal.second == 0)
        {
            string s=literal.first.substr(2);
            s.pop_back();
            fout << "(DL,01) (c," << s << ") ";
            literal.second = lc++;
        }

    }
    displaySymTab(symTab);
    displayLitTab(litTab);
    displayPoolTab(poolTab);
    std::cout << "Pass 1 completed... Check generated files" << endl;
}