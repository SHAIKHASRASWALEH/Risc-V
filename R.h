#ifndef R_H
#define R_H
#include <bits/stdc++.h>
#include <string>
using namespace std;
// converting decimal to binary
string dectobin(int n)
{
    string bin = "";
    while (n > 0)
    {
        char c = char((n % 2) + 48);
        bin = c + bin;
        n = n / 2;
    }
    while (bin.size() != 5)
    {
        bin = '0' + bin;
    }
    return bin;
}
// FUNC3 FOR INSTRUCTION
string func3(string Mnemonic)
{
    if (Mnemonic == "add" || Mnemonic == "sub" || Mnemonic == "mul")
        return "000";
    else if (Mnemonic == "sll")
        return "001";
    else if (Mnemonic == "slt")
        return "010";
    else if (Mnemonic == "xor" || Mnemonic == "div")
        return "100";
    else if (Mnemonic == "srl" || Mnemonic == "sra")
        return "101";
    else if (Mnemonic == "or" || Mnemonic == "rem")
        return "110";
    else
        return "111";
}
string func7(string Mnemonic)
{
    if (Mnemonic == "sub" || Mnemonic == "sra")
        return "0100000";
    else if (Mnemonic == "mul" || Mnemonic == "div" || Mnemonic == "rem")
        return "0000001";
    else
        return "0000000";
}
// gives hexadecimal of bin through dec     bin->dec->hex
string bintodec(string ans)
{
    string ru = "";
    for (int i = 0; i < 8; i++)
    {
        string hexa = ans.substr(i * 4, 4);
        int y = stoi(hexa);
        int u = 0;
        for (int j = 0; j < 4; j++)
        {
            int o = y % 10;
            y = y / 10;
            u += (o * pow(2, j));
        }
        if (u >= 10)
        {
            char c = 'A' + (u - 10);
            ru = ru + c;
        }
        else
        {
            char c = char(u + 48);
            ru = ru + c;
        }
    }
    ru = "0x" + ru;
    return ru;
}
string R(string s, int j, string Mnemonic)
{
    string rd = "";
    string rs1 = "";
    string rs2 = "";
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
            else if (flag == 2)
            {
                while (i != s.size() && s[i] != ' ')
                {
                    rs2 = rs2 + s[i];
                    i++;
                }
                flag = 0;
                // here we are not reading anything after we get the required instruction
                break;
            }
        }
    }
    // Adding opcode
    ans = ans + "0110011";
    // Getting rd into binary and adding to ans
    int rd_num = stoi(rd);
    if (rd_num > 31 || rd_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rd_num) + ans;
    // Getting func3 and adding into ans
    string func33 = func3(Mnemonic);
    ans = func33 + ans;
    // Getting rs1 and rs2 and adding into ans
    int rs1_num = stoi(rs1);
    if (rs1_num > 31 || rs1_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs1_num) + ans;
    int rs2_num = stoi(rs2);
    if (rs2_num > 31 || rs2_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(rs2_num) + ans;
    // Getting func7 and adding into ans
    string func77 = func7(Mnemonic);
    ans = func77 + ans;
    // converting binary to hexa
    string hex = bintodec(ans);
    // returning in hexadecimal
    return hex;
}
#endif
