#ifndef PROJECT_FRESHMAN_RABIN_KARP_H
#define PROJECT_FRESHMAN_RABIN_KARP_H

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using std::string, std::size_t, std::cout, std::vector, std::endl;

size_t text_hash(const string& sample, size_t len, const int d)
{
    size_t result = 0;
    for(int i = 0; i < len; i++)
        result += sample[i] * pow(d, len - i - 1);

    return result;
}

vector<size_t> RK_search(const string& text, const string& substr)
{
    vector<size_t> indexes;
    const int d = 13;
    size_t sublen = substr.length();
    size_t fragment_hash = text_hash(text, sublen, d);
    size_t substr_hash = text_hash(substr, sublen, d);

    for(size_t i = 0; i < text.length() - sublen + 1; i++)
    {
        if(fragment_hash == substr_hash)
        {
            bool is_equal = true;
            for(size_t j = 0; j < sublen; j++)
            {
                if(text[j + i] != substr[j])
                {
                    is_equal = false;
                    break;
                }
            }
            if(is_equal)
            {
                indexes.push_back(i);
            }
        }
        fragment_hash = (fragment_hash - text[i] * pow(d, sublen - 1)) * d + text[i + sublen];
    }
    return indexes;
}


#endif //PROJECT_FRESHMAN_RABIN_KARP_H
