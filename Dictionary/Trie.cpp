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

void delete_Whole_Trie(TrieNode*& root)
{
    if(!root) 
        return;
    for(int i = 0; i < 69; ++i)
        delete_Whole_Trie(root->edges[i]);
    delete root;
}

void build_Trie_EngEng(TrieNode*& root)
{
	std::ifstream fin;
	fin.open("../data_set/English_English_original1.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
    root = new TrieNode;
    while(fin)
    {
        std::string word, defi;
        getline(fin, word, (char)9); // (char)9 indicate 'TAB'
        getline(fin, defi, '\n');
        if(word == "")              // Avoid reading lát empty line!
            break;
        addWordAndDefiToTrie(word, defi, root);
    }
    fin.close();
}

void addWordAndDefiToTrie(std::string word, std::string defi, TrieNode*& root)
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
        std::cout << '\n';
    }
	else
		std::cout << word << " NOT FOUND!\n";
}

/*
std::string serialize(TrieNode* root)
{
	if (!root) return "";
	std::string s = "";
	std::queue <TrieNode*> q;
	q.push(root);
	while (!q.empty())
	{
		TrieNode* tmp = q.front();
		q.pop();
		if (!tmp)
			s.append("#,");
		else
		{
            s.append("node,");
            for(int i = 0; i < 69; ++i)
                q.push(tmp->edges[i]);
            
            if(tmp->isEndOfWord == false)
                s.append("0,");
            else
            {
                s.append("1,");
                for(int i = 0; i < root->definition.size(); ++i)
                    s.append(root->definition[i] + ',');
            }
		}
	}
	return s;
}

TrieNode* deserialize(std::string data)
{
	if (data.size() == 0) return nullptr;
	std::stringstream s(data);
	std::string str;
	getline(s, str, ',');
	TrieNode* root = new TrieNode;
	std::queue<TrieNode*> q;
	q.push(root);
	while (!q.empty())
	{
		TrieNode* tmp = q.front();
		q.pop();
   
        getline(s,str, ',');
        if(str == "0")
            tmp->isEndOfWord = false;
        else if(str == "1")
            tmp->isEndOfWord = true;

        for(int i = 0; i < 69; ++i)
        {
		    getline(s, str, ',');
            if (str == "#")
                tmp->edges[i] = nullptr;
            else
            {
                tmp->edges[i] = new TrieNode;
                q.push(tmp->edges[i]);
            }
        }
	}
	return root;
}
*/

void serialization1(TrieNode* root)
{
    std::ofstream fout;
	fout.open("English_English_serialization1.txt");
    if(!fout.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }

	std::queue <TrieNode*> q;
	q.push(root);
	while (!q.empty())
	{
		TrieNode* tmp = q.front();
		q.pop();
		if (!tmp)
            fout << "#,";
		else
		{
            fout << "node,";
            if(tmp->isEndOfWord == false)
                fout << "0,";
            else
            {
                fout << "1,";
                for(int i = 0; i < tmp->definition.size(); ++i)
                    fout << tmp->definition[i] << ",";
            }
            for(int i = 0; i < 69; ++i)
                q.push(tmp->edges[i]);
        }
	}
    fout.close();
    std::cout << "Serialization complete!\n";
}

void deserialization1(TrieNode*& root)
{
    std::ifstream fin;
	fin.open("English_English_serialization1.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
	std::string str;
	getline(fin, str, ',');
	root = new TrieNode;
	std::queue<TrieNode*> q;
	q.push(root);
	while (!q.empty())
	{
		TrieNode* tmp = q.front();
		q.pop();
   
        getline(fin, str, ',');
        if(str == "0")
            tmp->isEndOfWord = false;
        else if(str == "1")
        {
            tmp->isEndOfWord = true;
            getline(fin, str, ',');
            //while()
          //  tmp->definition.push_back(str);
        }

        for(int i = 0; i < 69; ++i)
        {
		    getline(fin, str, ',');
            if (str == "#")
                tmp->edges[i] = nullptr;
            else
            {
                tmp->edges[i] = new TrieNode;
                q.push(tmp->edges[i]);
            }
        }
	}
    fin.close();
    std::cout << "Deserialization complete!\n";
}

///////////////////////////////////////////////////
// Question 7: Users can remove a word from the dictionary.
void remove_Word_FromTrie_EngEng(std::string word, TrieNode* root)
{
    for(int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if(!root->edges[index])
            return;
        root = root->edges[index];
    }
    if(root->isEndOfWord)
    {
        root->isEndOfWord = false;
        root->definition.clear();
    }
}

int main()
{
	TrieNode* rootEE = nullptr;
    build_Trie_EngEng(rootEE);
    //deserialization1(rootEE);
    /*
    findWordInTrie("'em", rootEE);
    findWordInTrie("'gainst", rootEE);
	findWordInTrie("apples", rootEE);
    findWordInTrie("mastax", rootEE);
	findWordInTrie("abc", rootEE);
    findWordInTrie("appeal", rootEE);
    
    findWordInTrie("appealable", rootEE);
    //remove_Word_FromTrie_EngEng("appealable", rootEE);
    findWordInTrie("appealable", rootEE);
    */
    
    findWordInTrie("third", rootEE);
    findWordInTrie("temse", rootEE);
    findWordInTrie("discoloring", rootEE);
    findWordInTrie("temulence", rootEE);
    remove_Word_FromTrie_EngEng("discoloring", rootEE);
    findWordInTrie("discoloring", rootEE);
    //rootEE = nullptr;
    serialization1(rootEE);
   // deserialization(rootEE);
    delete_Whole_Trie(rootEE);
    std::cout << "------------------------------------------\n";
	return 0;
}