#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include <vector>
struct TrieNode
{
    TrieNode* edges[68];
    bool isEndOfWord;
    std::string definition;

    TrieNode()
    {
        for (int i = 0 ; i < 68 ; i++) edges[i] = nullptr;
        isEndOfWord = false;
    }
};
int convertCharToNum(char c); 
void addWordToTrie(std::string word, TrieNode*& root);
bool findWordInTrie(std::string word, TrieNode* root);
#endif