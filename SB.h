#ifndef SB_H
#define SB_H
#include "R.h"
#include "I.h"
#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
using namespace std;
string dtb(int n, int sign, int size)
{
    string bin = "";
    while (n > 0)
    {
        char c = char((n % 2) + 48);
        bin = c + bin;
        n = n / 2;
    }
    while (bin.size() != size)
    {
        if (sign == -1)
            bin = '1' + bin;
        else
            bin = '0' + bin;
    }
    return bin;
}
string fu3(string Mnemonic)
{
    if (Mnemonic == "beq")
        return "000";
    else if (Mnemonic == "bne")
        return "001";
    else if (Mnemonic == "blt")
        return "100";
    else
        return "101";
}
string SB(string s, int j, string Mnemonic, unordered_map<string, int> m_label, int PC)
{

    string rs1 = "";
    string rs2 = "";
    string label = "";
    int flag = 0;
    string ans = "";
    for (int i = j; i < s.size(); i++)
    {

        if (s[i] == 'x')
        {
            i++;
            if (flag == 0)
            {
                while (s[i] != ',' && s[i] != ' ')
                {
                    rs1 = rs1 + s[i];
                    i++;
                }
                flag++;
            }
            else if (flag == 1)
            {
                while ((s[i] != ',' && s[i] != ' ') || rs2 == "")
                {
                    rs2 = rs2 + s[i];
                    i++;
                }
                flag++;
            }
        }
        if (flag == 2)
        {
            i++;
            while (s[i] == ' ')
            {
                i++;
            }
            while (i != s.size() && s[i] != ' ')
            {
                label = label + s[i];
                i++;
            }
            flag = 0;
            break;
            // here the compiler terminates the instruction as soon as it gets the required values
        }
    }
    int pc_2 = m_label[label];
    int offset = pc_2 - PC;
    // Adding opcode
    ans = ans + "1100011";
    // Adding immediate
    string imm;
    if (offset < 0)
        imm = si(two(dec2bin(abs(offset))), 12) + ans;
    else
        imm = dtb(offset, 1, 13);
    // Adding imm[11]
    char eleven = imm[1];
    ans = eleven + ans;
    // Adding imm[4:1]
    string huu = imm.substr(8, 4);
    ans = huu + ans;
    // Adding func3
    huu = fu3(Mnemonic);
    ans = huu + ans;
    // Adding rs1
    int rs1_num = stoi(rs1);
    if (rs1_num > 31 || rs1_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs1_num) + ans;
    // Adding rs2
    int rs2_num = stoi(rs2);
    if (rs2_num > 31 || rs2_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs2_num) + ans;
    // Adding remaining immediate
    huu = imm.substr(2, 6);
    ans = huu + ans;
    char twelve = imm[0];
    ans = twelve + ans;
    // converting binary to hexa
    string hex = bintodec(ans);
    // returning in hexadecimal
    return hex;
}
#endif
