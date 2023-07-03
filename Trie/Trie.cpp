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
    else if('a' <= c && c <= 'z')
        return c - 'a' + 42;
    else if('A' <= c && c <= 'Z')
        return c - 'A' + 42;
    return -1;
}
void addWordToTrie(std::string word, TrieNode*& root)
{
	TrieNode* tmp = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!root->edges[index])
        {
			root->edges[index] = new TrieNode;
            root->isEndOfWord = false;
        }
		root = root->edges[index];
	}
	root->isEndOfWord = true;
	root = tmp;
}

bool findWordInTrie(std::string word, TrieNode* root)
{
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!root->edges[index])
			return false;
		root = root->edges[index];
	}
	if (root->isEndOfWord)
		return true;
	else
		return false;
}

void print(std::string ans, TrieNode* root)
{
	if (!findWordInTrie(ans, root))
		std::cout << ans << " NOT FOUND!\n";
	else
		std::cout << ans << " FOUND!\n";
}

int main()
{
	TrieNode* root = new TrieNode;
    root->isEndOfWord = false;
	addWordToTrie("apples", root);
	addWordToTrie("apps", root);
	print("apples", root);
	print("abc", root);
	return 0;
}