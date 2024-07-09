#ifndef J_H
#define J_H
#include <bits/stdc++.h>
#include <string>
#include "R.h"
#include "I.h"
#include "SB.h"
#include <unordered_map>
string J(string s, int j, string Mnemonic, unordered_map<string, int> m_label, int PC)
{
    string ra = "";
    string label = "";
    string ans = "";
    int flag = 0;
    for (int i = j; i < s.size(); i++)
    {
        if (s[i] == 'x')
        {
            i++;
            if (flag == 0)
            {

                while (s[i] != ',' && s[i] != ' ')
                {
                    ra = ra + s[i];
                    i++;
                }
                flag++;
            }
        }
        if (flag == 1)
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
        }
    }

    // Adding opcode
    ans = ans + "1101111";
    // Adding ra
    int ra_num = stoi(ra);
    if (ra_num > 31 || ra_num < 0)
    {
        printf("register not found");
        exit(0);
    }
    ans = dectobin(ra_num) + ans;
    // Calculating offset for label
    int pc_2 = m_label[label];
    int offset = pc_2 - PC;
    // Adding imm
    string imm;
    if (offset < 0)
    {
        imm = si(two(dec2bin(abs(offset))), 20) + ans;
    }
    else
        imm = dtb(offset, 1, 21);
    // imm[19:12]
    string h = imm.substr(1, 8);
    ans = h + ans;
    // imm[11]
    char eleven = imm[9];
    ans = eleven + ans;
    // imm[10:1]
    h = imm.substr(10, 10);
    ans = h + ans;
    // imm[20]
    char twenty = imm[0];
    ans = twenty + ans;
    // converting binary to hexa
    string hex = bintodec(ans);
    // returning in hexadecimal
    return hex;
}
#endif
