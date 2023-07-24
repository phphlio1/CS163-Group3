#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>
#include <string>

struct TrieNode
{
public:
    TrieNode()
    {
        for (int i = 0 ; i < 69; ++i) edges[i] = nullptr;
        isEndOfWord = false;
    }

    ~TrieNode(){
        for(int i = 0; i < 69; ++i)
            delete edges[i];
    }

public:
    TrieNode* edges[69];
    bool isEndOfWord;
    std::vector<std::string> definition;
};

#endif
