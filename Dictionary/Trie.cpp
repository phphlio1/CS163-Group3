#include "Trie.h"
int convertCharToNum(char c)
{
    if('0' <= c && c <= '9')
        return c - '0';
    else if('!' <= c && c <= '/')
        return c - '!' + 10;
    else if(':' <= c && c <= '@')
        return c - ':' + 25;
    else if('[' <= c && c <= '`')
        return c - '[' + 32;
    else if('{' <= c && c <= '~')
        return c - '{' + 38;
    else if(c == 32) // Space character
        return 42;
    else if('a' <= c && c <= 'z')
        return c - 'a' + 43;
    else if('A' <= c && c <= 'Z')
        return c - 'A' + 43;
    return -1;
}

void build_Trie_EngEng(TrieNode*& root)
{
	std::ifstream fin;
    fin.open("../data_set/English_English_modify.txt");
    if(!fin.is_open())
	    fin.open("../data_set/English_English_original.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
    while(fin)
    {
        std::string word;
        getline(fin, word, (char)9); // (char)9 indicate 'TAB'
        addWordAndDefiToTrie(word, root, fin);
    }
    fin.close();
}

void addWordAndDefiToTrie(std::string word, TrieNode*& root, std::ifstream& fin)
{
    
	TrieNode* tmp = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!root->edges[index])
			root->edges[index] = new TrieNode;
		root = root->edges[index];
	}
	root->isEndOfWord = true;
    std::string defi;
    getline(fin, defi, '\n');
    root->definition.push_back(defi);
	root = tmp;
}

void findWordInTrie(std::string word, TrieNode* root)
{
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!root->edges[index])
        {
			std::cout << word << " NOT FOUND!\n";
            return;
        }
		root = root->edges[index];
	}
	if (root->isEndOfWord)
	{
        std::cout << word << " FOUND!\n";
        for(int i = 0; i < root->definition.size(); ++i)
            std::cout << i + 1 << ". " << root->definition[i] << '\n';
    }
	else
		std::cout << word << " NOT FOUND!\n";
}

int main()
{
	TrieNode* root = new TrieNode;
    build_Trie_EngEng(root);
    findWordInTrie("'em", root);
    findWordInTrie("'gainst", root);
	findWordInTrie("apples", root);
    findWordInTrie("mastax", root);
	findWordInTrie("abc", root);
	return 0;
}