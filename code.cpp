#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "R.h"
#include "I.h"
#include "S.h"
#include "U.h"
#include "SB.h"
#include "J.h"
#include <unordered_map>
using namespace std;
int PC = 0;
int PC_2 = 0; // for label
unsigned int dat = 268435456;
int factor = 0;
// R format
vector<string> Rf;
// I format
vector<string> If;
// S format
vector<string> Sf;
// UJ format
vector<string> Uf;
// SB format
vector<string> Sbf;
// J format
vector<string> Jf;
// Function to determine id .data type is word or other
void data_func(string data_type)
{
    if (data_type == "byte")
        factor = 1;
    else if (data_type == "half")
        factor = 2;
    else if (data_type == "word")
        factor = 4;
    else
        factor = 8;
}
// Function to convert PC into hexdecimal
string hexa_convert(int y)
{
    int ty = 0;
    string an = "";
    if (y == 0)
        ty++;
    while (y > 0)
    {
        int r = y % 16;
        y = y / 16;
        if (r >= 10)
        {
            if (r == 10)
                an = 'A' + an;
            else if (r == 11)
                an = 'B' + an;
            else if (r == 12)
                an = 'C' + an;
            else if (r == 13)
                an = 'D' + an;
            else if (r == 14)
                an = 'E' + an;
            else if (r == 15)
                an = 'F' + an;
        }

        else
        {
            an = char(r + '0') + an;
        }
    }
    if (ty)
        return an = "0";
    return an;
}

int main()
{
    // Opening the assembly file
    ifstream file("assembly_code.asm");
    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return 0;
    }
    // Taking every line of assembly code as strings in vector
    vector<string> lines;
    string s;
    while (getline(file, s))
    {
        lines.push_back(s);
    }
    // Completed taking file as input
    file.close();
    // Adding R format instructions
    Rf.push_back("add");
    Rf.push_back("and");
    Rf.push_back("or");
    Rf.push_back("sll");
    Rf.push_back("slt");
    Rf.push_back("sra");
    Rf.push_back("srl");
    Rf.push_back("sub");
    Rf.push_back("xor");
    Rf.push_back("mul");
    Rf.push_back("div");
    Rf.push_back("rem");
    // Adding I format Instruction
    If.push_back("addi");
    If.push_back("andi");
    If.push_back("ori");
    If.push_back("lb");
    If.push_back("ld");
    If.push_back("lh");
    If.push_back("lw");
    If.push_back("jalr");
    // Adding S format
    Sf.push_back("sb");
    Sf.push_back("sw");
    Sf.push_back("sd");
    Sf.push_back("sh");
    // Addig Sb format
    Sbf.push_back("beq");
    Sbf.push_back("bne");
    Sbf.push_back("bge");
    Sbf.push_back("blt");
    // Adding U format
    Uf.push_back("auipc");
    Uf.push_back("lui");
    // Adding UJ format
    Jf.push_back("jal");
    // END of inserting Mnemonics

    int flag = 0;
    // Creating output file
    ofstream output("ans.mc");
    int counter_2 = 0;
    // Initializing map for label
    unordered_map<string, int> m_label;
    for (int i = 0; i < lines.size(); i++)
    {
        string ans = "";
        string Mnemonic = "";
        int j = 0;
        // Getting the opcode until space and avoiding space in from of the opcode
        while ((lines[i][j] != ' ' || Mnemonic == "") && j < lines[i].size())
        {
            // Checking if the instruction is comment or not
            if (lines[i][j] == '#')
            {
                flag++;
                break;
            }
            Mnemonic = Mnemonic + lines[i][j];
            j++;
        }
        // Checking if its a comment
        if (flag)
        {
            flag = 0;
            continue;
        }
        // If not a comment then proceeding with instruction
        if (Mnemonic == ".data:")
        {
            i++;
            // the assumption that .data is in a separate line and anything following it is on the next line
            int j = 0;
            while ((lines[i] != ".text:") && i < lines.size()) // the assumption that while starting the text segment it should start exactly with the line ".text"
                                                               // meaning no other char before or after this exact word
            {
                string data_type = "";
                while (lines[i][j] != '.')
                {
                    j++;
                }
                j++;
                while (lines[i][j] != ' ')
                {
                    data_type += lines[i][j];
                    j++;
                }

                if (data_type == "asciiz" || data_type == "string")
                {
                    string str = "";
                    while (lines[i][j] != '\"')
                    {
                        j++;
                    }
                    j++;
                    while (lines[i][j] != '\"')
                    {
                        int y = lines[i][j];
                        string h = hexa_convert(y);
                        output << "0x" << hexa_convert(dat) << " 0x" << h << "\n";
                        dat++;
                        j++;
                    }
                    dat++;
                }
                else
                {

                    data_func(data_type);
                    vector<string> arr;
                    while (lines[i][j] == ' ')
                        j++;
                    while (j < lines[i].size())
                    {
                        string id = "";
                        while (lines[i][j] != ' ' && j < lines[i].size())
                        {
                            id = id + lines[i][j];
                            j++;
                        }
                        arr.push_back(id);
                        j++;
                    }
                    for (int t = 0; t < arr.size(); t++)
                    {
                        int yt = stoi(arr[t]);
                        string h = hexa_convert(yt);
                        output << "0x" << hexa_convert(dat) << " 0x" << h << "\n";
                        dat += factor;
                    }
                }
                i++;
                j = 0;
            }
        }
        else
        {

            // Creating map function for labels
            if (!counter_2)
            {
                for (int ot = i; ot < lines.size(); ot++)
                {
                    string lab = "";
                    if (lines[ot][lines[ot].size() - 1] == ':') // assuming that label is in a separate line
                    {
                        for (int re = 0; re < lines[ot].size(); re++)
                        {
                            if (lines[ot][re] != ' ' && lines[ot][re] != ':')
                            {
                                if (lines[ot][re] == '#')
                                    break;
                                lab = lab + lines[ot][re];
                            }
                        }

                        m_label[lab] = PC_2;
                    }
                    else
                    {
                        int flag_32 = 0;
                        for (int yu = 0; yu < lines[ot].size(); yu++)
                        {
                            if (lines[ot][yu] == '#')
                                flag_32++;
                        }
                        if (!flag_32)
                            PC_2 += 4;
                    }
                }
                counter_2++;
            }
            // Checking if its R_format Mnemonics
            if (ans == "")
            {
                for (int k = 0; k < Rf.size(); k++)
                {
                    if (Mnemonic == Rf[k])
                    {
                        ans = R(lines[i], j, Mnemonic);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }

            // Checking if its I format Mnemonic
            if (ans == "")
            {
                for (int k = 0; k < If.size(); k++)
                {
                    if (Mnemonic == If[k])
                    {
                        ans = I(lines[i], j, Mnemonic);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }
            // Checking if its S format Mnemonic
            if (ans == "")
            {
                for (int k = 0; k < Sf.size(); k++)
                {
                    if (Mnemonic == Sf[k])
                    {
                        ans = S(lines[i], j, Mnemonic);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }
            // Checking if its SB format Mnemonics
            if (ans == "")
            {
                for (int k = 0; k < Sbf.size(); k++)
                {
                    if (Mnemonic == Sbf[k])
                    {
                        ans = SB(lines[i], j, Mnemonic, m_label, PC);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }
            // Checking if its U format Mnemonics
            if (ans == "")
            {
                for (int k = 0; k < Uf.size(); k++)
                {
                    if (Mnemonic == Uf[k])
                    {
                        ans = U(lines[i], j, Mnemonic);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }
            // Checking if its UJ format Mnemonics
            if (ans == "")
            {
                for (int k = 0; k < Jf.size(); k++)
                {
                    if (Mnemonic == Jf[k])
                    {
                        ans = J(lines[i], j, Mnemonic, m_label, PC);
                        break;
                    }
                }
                if (ans != "")
                {
                    output << "0x" << hexa_convert(PC) << " " << ans << "\n";
                    PC += 4;
                }
            }
        }
    }
    output << "0x" << hexa_convert(PC) << " Termination of code";
}
