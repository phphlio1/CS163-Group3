#ifndef TRIE_H
#define TRIE_H

#include "DatasetIdentifiers.h"
#include "TrieNode.h"
#include "checkerSubString.h"

#include <queue>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>

const std::string preAdress = "../data_set/";
const std::string FileName[4] = {"English_English"};
const std::string originFileName[4] = {"English_English_original.txt", "English_Vietnamese_original.txt",
                                       "Vietnamese_English_original.txt", "slang_emoji_original.txt"};
const std::string favoriteFileName[4] = {"_Eng_Eng.txt", "_Eng_Viet.txt", "_Viet_Eng.txt", "_emoji.txt"};
const std::string preFavoriteName = "favorite";

class Trie
{
public:
    Trie(Datasets::ID _type);
    ~Trie();

    void build_Trie_EngEng();
    void build_Trie_From_Origin();
    void delete_Whole_Trie();
    void resetToOriginal();

    void Serialization_DFS();
    void Deserialization_DFS();

    void remove_Word_FromTrie(std::string word);
    void addWordAndDefiToTrie(std::string word, std::string defi);
    void findWordInTrie(std::string word);
    bool findWordExistedToGetDefi(std::string word, std::vector<std::string> &defi);
    void findWordFromSubDefi(std::string subDefi);
    void editExistedWordDefi(std::string word, std::string newDefi);

    void getRandomWordAndDefi();
    std::string getRandomWord();
    std::string getRandomDefi_Of_Its_Word(std::string word);
    std::string getRandomDefi_Of_Random_Word();

    void quiz_1Word4Defis();
    void quiz_1Defi4Words();

    // Favourite list task
    void search_and_addToFavoriteList(std::string subWord);
    void viewFavoriteList();
    void removeAWordFromFavoriteList();

private:
    void searchForAWord_withSuggestion(std::string subWord, std::vector<std::string> &suggest);
    void readData_FavoriteList(std::vector<std::string> &fav);

    TrieNode *root;
    Datasets::ID typeOfDict;
    int num_line;
    checker checkerST;
};
#endif
