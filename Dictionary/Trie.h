#ifndef TRIE_H
#define TRIE_H

#include "DatasetIdentifiers.h"
#include "TrieNode.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <random>

const std::string preAdress = "../data_set/";
const std::string FileName[4] = {"English_English"};
const std::string originFileName[4] = {"English_English_original.txt", "English_Vietnamese_original.txt", 
                                        "Vietnamese_English_original.txt", "slang_emoji_original.txt"};

// Special Notice: Get the seed for random ONCE only! If not, same set of numbers every time
std::mt19937 generator(time(0));

int convertCharToNum(char c); 
char convertNumToChar(int n);

struct Trie{
public:

    Trie(Datasets::ID _type){
        typeOfDict = _type;
    }

    ~Trie(){
        delete root;
    }

    void build_Trie_EngEng();
    void build_Trie_From_Origin();
    void delete_Whole_Trie();
    void resetToOriginal();

    void serialization();
    void deserialization();

    void remove_Word_FromTrie(std::string word);
    void addWordAndDefiToTrie(std::string word, std::string defi);
    void findWordInTrie(std::string word);
    bool findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi);
    void editExistedWordDefi(std::string word, std::string newDefi);

    void getRandomWordAndDefi();
    std::string getRandomWord();
    std::string getRandomDefi_Of_Its_Word(std::string word);
    std::string getRandomDefi_Of_Random_Word();

    void quiz_1Word4Defis();
    void quiz_1Defi4Words();

private:
    TrieNode* root;
    Datasets::ID typeOfDict;
};

#endif