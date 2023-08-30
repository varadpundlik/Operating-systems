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

    vector<pair<string, int>> symTab;
    vector<pair<string, int>> litTab;

    ifstream fin;
    fin.open("input.txt", ios::in);

    ofstream fout;
    fout.open("intermediate_code.txt", ios::out);

    int lc = 0;

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
            if (decodedInstruction[i] == "START")
                lc = stoi(decodedInstruction[i + 1]) - 1;

            if (decodedInstruction[i] == "DC")
            {
                fout << "(DL,02) (c," << decodedInstruction[i + 1] << ") ";
                i++; // Skip the immediate constant value
            }
            else if (decodedInstruction[i] == "EQU")
            {
                int pos = findElement(symTab, decodedInstruction[i - 1]);
                if (pos != -1)
                {
                    symTab[pos].second = stoi(decodedInstruction[i + 1]);
                }
                i++; // Skip the EQU value
            }
            else if (decodedInstruction[i] == "LTORG")
            {
                for (const auto &literal : litTab)
                {
                    fout << "(DL,01) (c," << literal.first.substr(2) << ") ";
                }
                litTab.clear(); // Clear literal table after outputting literals
            }
            // ... (existing code)
            if (memo.find(decodedInstruction[i]) != memo.end())
                fout << "(" << memo[decodedInstruction[i]].first << "," << memo[decodedInstruction[i]].second << ") ";

            else if (reg.find(decodedInstruction[i]) != reg.end())
                fout << "(" << reg[decodedInstruction[i]] << ") ";

            else if (concode.find(decodedInstruction[i]) != concode.end())
                fout << "(" << concode[decodedInstruction[i]] << ") ";

            else if (decodedInstruction[i][0] == '=')
                litTab.push_back({decodedInstruction[i], lc});

            else if (decodedInstruction[i][0] >= '0' && decodedInstruction[i][0] <= '9')
                fout << "(c," << decodedInstruction[i] << ") ";

            else if (isdigit(decodedInstruction[i][0]))
            {
                fout << "(c," << decodedInstruction[i] << ") ";
            }

            else if (decodedInstruction[i][1] >= '0' && decodedInstruction[i][1] <= '9')
            {
                fout << "(c," << decodedInstruction[i] << ") ";
            }

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
    displaySymTab(symTab);
    displayLitTab(litTab);
    cout << "Pass 1 completed... Check generated files" << endl;
}
