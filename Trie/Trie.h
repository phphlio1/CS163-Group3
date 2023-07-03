#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include <vector>
struct TrieNode
{
    char data;
    TrieNode* edges[68]{0};
    bool isEndOfWord = false;
};
// 68 characters in converting table. No need for 256 -> Minimize memory use.
int convertCharToNum(char c); 
void addWordToTrie(std::string word, TrieNode*& root);
bool findWordInTrie(std::string word, TrieNode* root);
#endif