#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <random>
struct TrieNode
{
    TrieNode* edges[69];
    bool isEndOfWord;
    std::vector<std::string> definition;

    TrieNode()
    {
        for (int i = 0 ; i < 69; ++i) edges[i] = nullptr;
        isEndOfWord = false;
    }
};
int convertCharToNum(char c); 
char convertNumToChar(int n);

void build_Trie_EngEng(TrieNode*& root);
void delete_Whole_Trie(TrieNode*& root);

void serialization(TrieNode* root);
void deserialization(TrieNode*& root);

TrieNode* Serialize_Traversal_DFS(TrieNode* root, std::ofstream& fout);
void Serialization_DFS(TrieNode* root);
TrieNode* Deserialize_Traversal_DFS(TrieNode* root, std::ifstream& fin, int index);
void Deserialization_DFS(TrieNode*& root);

void remove_Word_FromTrie(std::string word, TrieNode* root);
void addWordAndDefiToTrie(std::string word, std::string defi, TrieNode*& root);
void findWordInTrie(std::string word, TrieNode* root);
bool findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi, TrieNode* root);

// Special Notice: Get the seed for random ONCE only! If not, same set of numbers every time
std::mt19937 generator(time(0));
void getRandomWordAndDefi(TrieNode* root);
std::string getRandomWord(TrieNode* root);
std::string getRandomDefi_Of_Its_Word(TrieNode* root, std::string word);
std::string getRandomDefi_Of_Random_Word(TrieNode* root);

void quiz_1Word4Defis(TrieNode* root);
void quiz_1Defi4Words(TrieNode* root);
#endif