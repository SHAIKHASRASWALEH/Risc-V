#ifndef S_H
#define S_H
#include <bits/stdc++.h>
#include <string>
#include "I.h"
#include "R.h"
using namespace std;
string funn3(string Mnemonics)
{
    if (Mnemonics == "sd")
        return "011";
    else if (Mnemonics == "sw")
        return "010";
    else if (Mnemonics == "sh")
        return "001";
    else
        return "000";
}
string S(string s, int j, string Mnemonic)
{
    string rs1 = "";
    string rs2 = "";
    string imm = "";
    string ans = "";
    int flag = 0;
    for (int i = j; i < s.size(); i++)
    {

        if (s[i] == 'x' && flag == 0)
        {
            i++;
            while (s[i] != ',' && s[i] != ' ')
            {
                rs2 = rs2 + s[i];
                i++;
            }
            flag++;
        }
        else if (flag == 1 && s[i] != ' ')
        {
            while (s[i] != '(')
            {
                imm = imm + s[i];
                i++;
            }
            flag++;
        }
        else if (flag == 2 && s[i] != ' ')
        {
            if (s[i] == 'x')
            {
                i++;
                while (s[i] != ')' && s[i] != ' ')
                {
                    rs1 = rs1 + s[i];
                    i++;
                }
                break;
                // here again the compiler terminates the line once it gets required values from the instruction
            }
        }
    }
    // Adding opcode
    ans = ans + "0100011";
    // Adding imm[4:0]
    int imm_num = stoi(imm);
    string imm_complete;
    if (imm_num >= 0)
        imm_complete = dectobin(imm_num, 12, 1);
    else
        imm_complete = si(two(dec2bin(abs(imm_num))), 11) + ans;
    // imm1=imm[4:0]
    string imm1 = imm_complete.substr(7, 5);
    ans = imm1 + ans;
    // Adding func3
    string fun3 = funn3(Mnemonic);
    ans = fun3 + ans;
    // Adding rs1
    int rs1_num = stoi(rs1);
    if (rs1_num > 31 || rs1_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs1_num, 5, 1) + ans;
    // Adding rs2
    int rs2_num = stoi(rs2);
    if (rs2_num > 31 || rs2_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs2_num, 5, 1) + ans;
    // Adding imm[11:5]
    string imm2 = imm_complete.substr(0, 7);
    ans = imm2 + ans;
    // converting binary to hexa
    string hex = bintodec(ans);
    // returning in hexadecimal
    return hex;
}
#endif
