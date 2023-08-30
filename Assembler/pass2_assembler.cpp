#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin;
    fin.open("intermediate_code.txt", ios::in);

    ofstream fout;
    fout.open("machine_code.txt", ios::out);

    map<string, string> opcodes;
    opcodes["STOP"] = "00";
    opcodes["ADD"] = "01";
    opcodes["SUB"] = "02";
    opcodes["MULT"] = "03";
    opcodes["MOVER"] = "04";
    opcodes["MOVEM"] = "05";
    opcodes["COMP"] = "06";
    opcodes["BC"] = "07";
    opcodes["DIV"] = "08";
    opcodes["READ"] = "09";
    opcodes["PRINT"] = "10";

    map<string, string> assemblyDirectives;
    assemblyDirectives["START"] = "01";
    assemblyDirectives["END"] = "02";
    assemblyDirectives["ORIGIN"] = "03";
    assemblyDirectives["EQU"] = "04";
    assemblyDirectives["LTORG"] = "05";

 string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string token;

        while (ss >> token)
        {
            if (token[0] == '(')
            {
                if (token[1] == 's')
                {
                    int pos = stoi(token.substr(4, token.length() - 5));
                    fout << "(" << setw(2) << setfill('0') << pos << ") ";
                }
                else if (token[1] == 'c')
                {
                    fout << "(" << setw(2) << setfill('0') << token.substr(3, token.length() - 4) << ") ";
                }
                else if (token[1] == 'A')
                {
                    string dircode = assemblyDirectives[token.substr(3, token.length() - 4)];
                    fout << "(" << dircode << ") ";
                }
                else if (token[1] == 'I')
                {
                    string opcode = opcodes[token.substr(3, token.length() - 4)];
                    fout << "(" << opcode << ") ";
                }
            }
        }

        fout << endl;
    }

    fin.close();
    fout.close();

    cout << "Pass 2 completed... Check generated machine code" << endl;

    return 0;
}
