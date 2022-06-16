#ifndef PROJECT_FRESHMAN_KNUTH_MORRIS_PRATT_H
#define PROJECT_FRESHMAN_KNUTH_MORRIS_PRATT_H

#include <iostream>
#include <vector>

std::vector<int> piVector(const std::string & substring)
{
    std::vector<int> pi(substring.size());
    pi[0] = 0;
    int i = 1, j = 0;

    while(i < substring.size())
    {
        if(substring[i] == substring[j])
        {
            pi[i] = j + 1;
            j++;
            i++;
        }
        else if(j > 0)
            j = pi[j - 1];
        else
        {
            pi[i] = 0;
            i++;
        }
    }
    return pi;
}

std::vector<size_t> KMP_search(const std::string& main, const std::string& sub)
{
    size_t n = main.size();
    size_t m = sub.size();
    std::vector<std::size_t> indexes;
    std::vector<int> failures = piVector(sub);

    size_t i = 0, j = 0;
    while(i < n)
    {
        if(main[i] == sub[j])
        {
            i++, j++;
            if(j == m)
            {
                indexes.push_back(i - m);
                j = 0;
            }
        }
        else if(j > 0)
            j = failures[j - 1];
        else
        {
            i++;

        }
    }
    return indexes;
}

bool KMP_test() {
    std::string txt = "uabcabdabcabcabd";
    std::string sub = "abcabd";
    std::vector<size_t> indexes = KMP_search(txt, sub);

    for (int i = 0; i < indexes.size(); i++)
    {
        std::cout << indexes[i] << "\n";
    }
}
#endif //PROJECT_FRESHMAN_KNUTH_MORRIS_PRATT_H
