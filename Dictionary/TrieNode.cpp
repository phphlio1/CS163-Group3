#include "TrieNode.h"

auto TrieNode::Serialize_Traversal_DFS(std::ofstream& fout, int index) -> TrieNode*
{
    // if(!this)
    //     return this;
    fout << "node_";
    fout << index << "_";
    if(this->isEndOfWord == false)
        fout << "0_";
    else
    {
        fout << "1_";
        for(int i = 0; i < this->definition.size(); ++i)
        {
            if(i == this->definition.size() - 1)
                fout << this->definition[i] << '\n';
            else
                fout << this->definition[i] << "_";
        }
    }
    for(int i = 0; i < TrieSize; ++i)
        if(this->edges[i])
            this->edges[i] = this->edges[i]->Serialize_Traversal_DFS(fout, i);
    fout << "#_";
    return this;
}

auto TrieNode::Deserialize_Traversal_DFS(std::ifstream& fin, int index) -> TrieNode*
{
    std::string str;
    getline(fin, str, '_');
    if(str == "#")
        return this;
    else if(str == "node")
    {
        fin >> index;
        fin.ignore(10, '_'); 
        this->edges[index] = new TrieNode;
        getline(fin, str, '_');
        if(str == "0")
            this->edges[index]->isEndOfWord = false;
        else if(str == "1")
        {
            this->edges[index]->isEndOfWord = true;
            getline(fin, str, '\n');
            std::stringstream s;
            s << str;
            while(!s.eof())
            {
                getline(s, str, '_');
                this->edges[index]->definition.push_back(str);
            }
        }
        this->edges[index] = this->edges[index]->Deserialize_Traversal_DFS(fin, 0);
    }
    return this->Deserialize_Traversal_DFS(fin, index);
}