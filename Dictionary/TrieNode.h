#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

constexpr int TrieSize = 69;

struct TrieNode
{
public:
    TrieNode()
    {
        for (int i = 0 ; i < TrieSize; ++i) edges[i] = nullptr;
        isEndOfWord = false;
    }

    ~TrieNode(){
        for(int i = 0; i < TrieSize; ++i)
            delete edges[i];
    }

    auto Serialize_Traversal_DFS(std::ofstream& fout, int index) -> TrieNode*;
    auto Deserialize_Traversal_DFS(std::ifstream& fin, int index) -> TrieNode*;

public:
    TrieNode* edges[TrieSize];
    bool isEndOfWord;
    std::vector<std::string> definition;
};

#endif
