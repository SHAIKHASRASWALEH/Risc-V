#ifndef I_H
#define I_H
#include <bits/stdc++.h>
#include <string>
#include "R.h"
using namespace std;

string dectobin(int n, int size, int sign)
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
        if (sign == 1)
            bin = '0' + bin;
        else
            bin = '1' + bin;
    }
    return bin;
}
string dec2bin(int n)
{
    string bin = "";
    while (n > 0)
    {
        char c = char((n % 2) + 48);
        bin = c + bin;
        n = n / 2;
    }
    return bin;
}
char flip(char c) { return (c == '0') ? '1' : '0'; }
string two(string m)
{
    int n = m.length();
    int i;

    string ones, twos;
    ones = twos = "";

    // For ones complement flip every bit
    for (i = 0; i < n; i++)
        ones += flip(m[i]);

    twos = ones;
    for (i = n - 1; i >= 0; i--)
    {
        if (ones[i] == '1')
            twos[i] = '0';
        else
        {
            twos[i] = '1';
            break;
        }
    }
    if (i == -1)
        twos = '1' + twos;
    return twos;
}
string si(string m, int size)
{
    for (int i = m.size(); i <= size; i++)
        m = '1' + m;
    return m;
}
string func3I(string Mnemonic)
{
    if (Mnemonic == "lb" || Mnemonic == "jalr" || Mnemonic == "addi")
        return "000";
    else if (Mnemonic == "lh")
        return "001";
    else if (Mnemonic == "lw")
        return "010";
    else if (Mnemonic == "ld")
        return "011";
    else if (Mnemonic == "andi")
        return "111";
    else
        return "110";
}

string I(string s, int j, string Mnemonic)
{
    string ans = "";
    string rd = "";
    string rs1 = "";
    string imm = "";
    int flag = 0;
    // Extracting rd,rs1,imm fields
    if (Mnemonic == "addi" || Mnemonic == "andi" || Mnemonic == "ori" || Mnemonic == "jalr")
    {
        for (int i = j; i < s.size(); i++)
        {
            if (s[i] == 'x')
            {
                i++;
                if (flag == 0)
                {
                    while (s[i] != ',' && s[i] != ' ')
                    {
                        rd = rd + s[i];
                        i++;
                    }
                    flag++;
                }
                else if (flag == 1)
                {
                    while ((s[i] != ',' && s[i] != ' ') || rs1 == "")
                    {
                        rs1 = rs1 + s[i];
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
                    imm = imm + s[i];
                    i++;
                }
                flag = 0;
                break;
            }
        }
    }
    else
    {
        for (int i = j; i < s.size(); i++)
        {
            if (s[i] == 'x' && flag == 0)
            {
                i++;

                while (s[i] != ',' && s[i] != ' ')
                {
                    rd = rd + s[i];
                    i++;
                }
                flag++;
            }
            else if (flag == 1 && s[i] != ' ')
            {
                while (s[i] != '(')
                {
                    // taking offset
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
                    // here even if there is something after the complpetion of required instruction, the compiler ignores it
                    break;
                }
            }
        }
    }
    // Adding opcode
    if (Mnemonic == "andi" || Mnemonic == "ori" || Mnemonic == "addi")
        ans = ans + "0010011";
    else if (Mnemonic == "jalr")
        ans += "1100111";
    else
        ans += "0000011";
    // Adding rd
    int rd_num = stoi(rd);
    if (rd_num > 31 || rd_num < 0)
    {
        printf("register not found");
        exit(0);
    }

    ans = dectobin(rd_num) + ans;
    // Adding func3
    string func33 = func3I(Mnemonic);
    ans = func33 + ans;
    // Adding rs1
    int rs1_num = stoi(rs1);
    if (rs1_num > 31 || rs1_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs1_num) + ans;
    // Adding immediate
    int imm_num = stoi(imm);
    if (imm_num >= 0)
    {
        ans = dectobin(imm_num, 12, 1) + ans;
    }
    else
    {
        ans = si(two(dec2bin(abs(imm_num))), 11) + ans;
    }
    // converting binary to hexa
    string hex = bintodec(ans);
    // returning in hexadecimal
    return hex;
}
#endif
