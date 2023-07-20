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

char convertNumToChar(int n)
{
    if(0 <= n && n <= 9)
        return n + '0';
    else if(10 <= n && n <= 24)
        return n + '!' - 10;
    else if(25 <= n && n <= 31)
        return n + ':' - 25;
    else if(32 <= n && n <= 37)
        return n + '[' - 32;
    else if(38 <= n && n <= 41)
        return n + '{' - 38;
    else if(n == 42) // Space character
        return 32;
    else if(43 <= n && n <= 68)
        return n + 'a' - 43;
    return 0;
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
	fin.open("../data_set/English_English_original.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
    root = new TrieNode;
    while(!fin.eof())
    {
        std::string word, defi;
        getline(fin, word, (char)9); // (char)9 indicate 'TAB'
        getline(fin, defi, '\n');
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

bool findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi, TrieNode* root)
{
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!root->edges[index])
            return false;
		root = root->edges[index];
	}
	if (root->isEndOfWord)
    {
        defi = root->definition;
        return true;
    }
	else
		return false;
}

void serialization(TrieNode* root)
{
    std::ofstream fout;
	fout.open("English_English_serialization.txt");
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
            fout << "#_";
		else
		{
            fout << "node_";
            if(tmp->isEndOfWord == false)
                fout << "0_";
            else
            {
                fout << "1_";
                for(int i = 0; i < tmp->definition.size(); ++i)
                {
                    if(i == tmp->definition.size() - 1)
                        fout << tmp->definition[i] << '\n';
                    else
                        fout << tmp->definition[i] << "_";
                }
            }
            for(int i = 0; i < 69; ++i)
                q.push(tmp->edges[i]);
        }
	}
    fout.close();
    std::cout << "Serialization complete!\n";
}

void deserialization(TrieNode*& root)
{
    std::ifstream fin;
	fin.open("English_English_serialization.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
	std::string str;
	getline(fin, str, '_');
	root = new TrieNode;
    getline(fin, str, '_');
    root->isEndOfWord = false;
	std::queue<TrieNode*> q;
	q.push(root);
	while (!q.empty())
	{
		TrieNode* tmp = q.front();
		q.pop();

        for(int i = 0; i < 69; ++i)
        {
		    getline(fin, str, '_');
            if (str == "#")
                tmp->edges[i] = nullptr;
            else if(str == "node")
            {
                tmp->edges[i] = new TrieNode;
                getline(fin, str, '_');
                if(str == "0")
                    tmp->edges[i]->isEndOfWord = false;
                else if(str == "1")
                {
                    tmp->edges[i]->isEndOfWord = true;
                    getline(fin, str, '\n');
                    std::stringstream s;
                    s << str;
                    while(!s.eof())
                    {
                        getline(s, str, '_');
                        tmp->edges[i]->definition.push_back(str);
                    }
                }
                q.push(tmp->edges[i]);
            }
        }         
	}
    fin.close();
    std::cout << "Deserialization complete!\n";
}

///////////////////////////////////////////////////
// Question 7: Users can remove a word from the dictionary.
void remove_Word_FromTrie(std::string word, TrieNode* root)
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

///////////////////////////////////////////////////
// Question 9: Users can view a word and its definition
void getRandomWordAndDefi(TrieNode* root)
{
    std::ifstream fin;
    std::string word, tmp;
    std::vector<std::string> defi;
    srand(time(0));
    fin.open("../data_set/English_English_original.txt");
    int word_num = 100500, line; 
    while(true)
    {
        line = rand() % word_num;
        for(int i = 1; i < line; ++i)
        {
            getline(fin, word, (char)9); // (char)9 indicate 'TAB'
            getline(fin, tmp, '\n');
        }
        if(findWordExistedToGetDefi(word, defi, root))
            break;
    }
    fin.close();
    std:: cout << "Random Word: " << word << '\n';
    std::cout << "Definition: " << '\n';
    for(int i = 0; i < defi.size(); ++i)
        std::cout << i + 1 << ". " << defi[i] << '\n';
    std::cout << '\n';
}

int main()
{
    // Question 1
	TrieNode* rootEE = nullptr;
    build_Trie_EngEng(rootEE);
    //deserialization(rootEE);
    findWordInTrie("'em", rootEE);
    findWordInTrie("'gainst", rootEE);
	findWordInTrie("apples", rootEE);
    findWordInTrie("mastax", rootEE);
	findWordInTrie("abc", rootEE);
    findWordInTrie("appeal", rootEE);
    std::cout << "------------------------------------------\n";

    // Question 7
    findWordInTrie("appealable", rootEE);
    remove_Word_FromTrie("appealable", rootEE);
    findWordInTrie("appealable", rootEE);
    std::cout << "------------------------------------------\n";

    // Question 9
    getRandomWordAndDefi(rootEE);
    std::cout << "------------------------------------------\n";

    //serialization(rootEE);
    delete_Whole_Trie(rootEE);
	return 0;
}