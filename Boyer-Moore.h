#ifndef PROJECT_FRESHMAN_BOYER_MOORE_H
#define PROJECT_FRESHMAN_BOYER_MOORE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

std::vector<int> badChar(const std::string& pattern)
{
    const int N_ASCII_CHAR = 256;
    std::vector<int> bad_char(N_ASCII_CHAR, -1);
    for(int i = 0; i < pattern.size(); i++)
        bad_char[(int)pattern[i]] = i;

    return bad_char;
}

std::vector<size_t> BM_search(const std::string& main,const std::string& sub)
{
    std::vector<size_t> indexes;
    size_t n = main.size();
    size_t m = sub.size();
    std::vector<int> bad_char = badChar(sub);

    int i = 0;
    while(i <= (n - m))
    {
        int j = m - 1;
        while(j >= 0 && sub[j] == main[i + j])
            j--;

        if(j < 0)
        {
            indexes.push_back(i);
            if(i + m < n)
                i += m - bad_char[main[i + m]];
            else i++;
        }
        else
            i += fmax(1, j - bad_char[main[i + j]]);
    }
    return indexes;
}

int BM_test()
{
    std::string txt= "uabcabdabcabcabd";
    std::string pat = "abcabd";
    std::vector<size_t> indexes = BM_search(txt, pat);
    std::cout << "Record found at: ";
    for(size_t index : indexes)
        std::cout << index << ", ";

    return 0;
}
#endif //PROJECT_FRESHMAN_BOYER_MOORE_H