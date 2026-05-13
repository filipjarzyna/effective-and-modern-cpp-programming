#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code. 
 */
class Trie{
private:
    std::map<std::string, Trie> words;
    bool isEnd = false;

public:
    static void printSentence(const std::vector<std::string>  & sentence ){
        for(const auto & w : sentence)
            cout << w << " ";
    }

    void add(const std::vector<std::string>  & sentece ){
       cout << "Adding : ";
       printSentence(sentece);
       cout << "\n";

       /// TODO:
       Trie* node = this;
       for(const auto& word : sentece)
           node = &(node->words[word]);
        node->isEnd = true;
    }

    void printPossibleEndings(const std::vector<std::string>  & beginningOfSentece){
        cout << "Endings for \"";
        printSentence(beginningOfSentece);
        cout << "\" are :\n";

        // TODO:
        vector<string> wordStack(beginningOfSentece);
        std::reverse(wordStack.begin(), wordStack.end());
        vector<string> current;
        printAll(wordStack, current);
    }

    void printAll(vector<string> wordStack, vector<string>& current) {
        if(wordStack.empty()) {
            if(isEnd){
                cout << " > ";
                printSentence(current);
                cout << "\n";
            }

            for(auto& [word, child] : words){
                current.push_back(word);
                child.printAll(wordStack, current);
                current.pop_back();
            }
        } else {
            std::string wordMatch = wordStack.back();
            wordStack.pop_back();
            for(auto& [word, child] : words){
                if(wordMatch != word) continue;
                child.printAll(wordStack, current);
            }
        }

    }

    void load(const std::string & fileName){
        ifstream file(fileName);
        if(!file){
            cerr << "Error when openning file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while( file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if(word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }
};


int main(){
    Trie dictionary;
    dictionary.load("../sample.txt");
    //dictionary.load("hamletEN.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */
