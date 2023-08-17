#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
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
void build_Trie_EngEng(TrieNode*& root);
void delete_Whole_Trie(TrieNode*& root);

void serialization(TrieNode* root);
void deserialization(TrieNode*& root);

void remove_Word_FromTrie_EngEng(std::string word, TrieNode* root);
void addWordAndDefiToTrie(std::string word, std::string defi, TrieNode*& root);
void findWordInTrie(std::string word, TrieNode* root);
#endif