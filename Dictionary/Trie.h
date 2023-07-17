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
    std::string definition;

    TrieNode()
    {
        for (int i = 0 ; i < 69; ++i) edges[i] = nullptr;
        isEndOfWord = false;
    }
};
int convertCharToNum(char c); 
void build_Trie_EngEng(TrieNode*& root);

void addWordAndDefiToTrie(std::string word, TrieNode*& root, std::ifstream& fin);
bool findWordInTrie(std::string word, TrieNode* root);

std::string serialize(TrieNode* root);
TrieNode* deserialize(std::string data);
#endif