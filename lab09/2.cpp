#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    s1.erase(std::remove_if(s1.begin(), s1.end(),
                [](char c) { return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c){ return std::tolower(c);});
}

int main(){
    int count = 0;
    string s;
    std::map<std::string, int> words;
    while(std::cin >> s) {
        toLowerAlpha(s);
        if(!s.empty())
            words[s]++;
    }
    count = words.size();

    std::multimap<int, std::string, std::greater<int>> popularWords;

    for(auto& x : words)
        popularWords.insert({x.second, x.first});

    cout << "Number of distinct words : " << count << endl;
    cout << "\nThe top 20 most popular words: \n";
    auto it = popularWords.begin();
    for(int i = 0; i < 20; ++i, ++it)
        cout << (*it).first << " : " << (*it).second << endl;

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4725

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */
