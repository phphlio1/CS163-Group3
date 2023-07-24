#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <random>
constexpr int TrieSize = 69;

struct TrieNode
{
    TrieNode* edges[TrieSize];
    bool isEndOfWord;
    std::vector<std::string> definition;

    TrieNode()
    {
        for (int i = 0 ; i < TrieSize; ++i) edges[i] = nullptr;
        isEndOfWord = false;
    }
};
int convertCharToNum(char c); 
char convertNumToChar(int n);

void build_Trie_EngEng(TrieNode*& root);
void delete_Whole_Trie(TrieNode*& root);

TrieNode* Serialize_Traversal_DFS(TrieNode* root, std::ofstream& fout, int index);
void Serialization_DFS(TrieNode* root);
TrieNode* Deserialize_Traversal_DFS(TrieNode* root, std::ifstream& fin, int index);
void Deserialization_DFS(TrieNode*& root);

void remove_Word_FromTrie(std::string word, TrieNode* root);
void addWordAndDefiToTrie(std::string word, std::string defi, TrieNode*& root);
void findWordInTrie(std::string word, TrieNode* root);
bool findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi, TrieNode* root);

void getRandomWordAndDefi(TrieNode* root);
std::string getRandomWord(TrieNode* root);
std::string getRandomDefi_Of_Its_Word(TrieNode* root, std::string word);
std::string getRandomDefi_Of_Random_Word(TrieNode* root);

void quiz_1Word4Defis(TrieNode* root);
void quiz_1Defi4Words(TrieNode* root);

void searchForAWord_withSuggestion(TrieNode* root, std::string subWord, std::vector<std::string>& suggest);
#endif

////////////////////////////////////////////////////////////////
// Thinh - cpp
/*
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

void Trie::delete_Whole_Trie() { delete root; }

void Trie::build_Trie_EngEng()
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
        addWordAndDefiToTrie(word, defi);
    }
    fin.close();
}

void Trie::build_Trie_From_Origin()
{
    std::ifstream fin;
    fin.open(preAdress + originFileName[typeOfDict]);
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
        addWordAndDefiToTrie(word, defi);
    }
    fin.close();
}

void Trie::addWordAndDefiToTrie(std::string word, std::string defi)
{
	TrieNode* cur = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!cur->edges[index])
			cur->edges[index] = new TrieNode;
		cur = cur->edges[index];
	}
	cur->isEndOfWord = true;
    cur->definition.push_back(defi);
}

void Trie::findWordInTrie(std::string word)
{
    TrieNode* cur = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!cur->edges[index])
        {
			std::cout << word << " NOT FOUND!\n";
            return;
        }
		cur = cur->edges[index];
	}
	if (cur->isEndOfWord)
	{
        std::cout << word << " FOUND!\n";
        for(int i = 0; i < cur->definition.size(); ++i)
            std::cout << i + 1 << ". " << cur->definition[i] << '\n';
        std::cout << '\n';
    }
	else
		std::cout << word << " NOT FOUND!\n";
}

bool Trie::findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi)
{
    TrieNode* cur = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!cur->edges[index])
            return false;
		cur = cur->edges[index];
	}
	if (cur->isEndOfWord)
    {
        defi = cur->definition;
        return true;
    }
	else
		return false;
}

void Trie::serialization()
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

void Trie::deserialization()
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
// Question 5: Users can add a new word and its definition
// ham addword

///////////////////////////////////////////////////
// Question 6: Users can edit the defi of an existing word
void Trie::editExistedWordDefi(std::string word, std::string newDefi){
    // The std::cout << code below can be edit by frontend coders
    
    ////////////////////////////////// find the word
    TrieNode* cur = root;
	for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		if (!cur->edges[index]){
            std::cout << "There is no " << word << " in the dictionary\n";    
            return;
        }
        cur = cur->edges[index];
	}
	if (!cur->isEndOfWord){
        std::cout << "There is no " << word << " in the dictionary\n";    
        return;
    }
    //////////////////////////////////////////////////
    
    std::cout << "There are " << cur->definition.size() << " definition in the dictionary\n";
    std::cout << "1. Adding new definition for this word.\n";
    std::cout << "2. Replacing one existed definition by new definition.\n";
    std::cout << "3. Replacing all definition by this new definition.\n";
    std::cout << "Please input what do you want (only by number 1, 2, 3):\n";
    int userInput;
    while(std::cin >> userInput){
        if(userInput < 1 || userInput > 3)
            std::cout << "Please input what do you want (only by number 1, 2, 3):\n";
        else 
            break;
    }

    int typeOfAction = userInput;

    if(typeOfAction == 1){
        cur->definition.push_back(newDefi);
        std::cout << "Change successfully\n";
    }
    
    if(typeOfAction == 2){
        std::cout << "Please input the number (from 1 to " << cur->definition.size() << ") to choose the editing definition\n";
    
        while(std::cin >> userInput){
            if(userInput < 1 || userInput > cur->definition.size())
                std::cout << "Please input the number (from 1 to " << cur->definition.size() << ") to choose the editing definition\n";
            else {
                cur->definition[userInput - 1] = newDefi;
                std::cout << "Change successfully\n";
                break;
            }    
        }
    }

    if(typeOfAction == 3){
        cur->definition.clear();
        cur->definition.push_back(newDefi);
        std::cout << "Change successfully\n";
    }
}

///////////////////////////////////////////////////
// Question 7: Users can remove a word from the dictionary.
void Trie::remove_Word_FromTrie(std::string word)
{
    TrieNode* cur = root;
    for(int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if(!cur->edges[index])
            return;
        cur = cur->edges[index];
    }
    if(cur->isEndOfWord)
    {
        cur->isEndOfWord = false;
        cur->definition.clear();
    }
}

///////////////////////////////////////////////////
// Question 8: Users can reset the dictionary to its original state.

void Trie::resetToOriginal(){
    delete_Whole_Trie();
    build_Trie_From_Origin();
}

///////////////////////////////////////////////////
// Question 9: Users can view a word and its definition
void Trie::getRandomWordAndDefi()
{
    std::ifstream fin;
    std::string word;
    std::vector<std::string> defi;
    fin.open("../data_set/English_English_original.txt");
    int word_num = 160000, line; 
    while(true)
    {
        line = generator() % word_num;
        for(int i = 1; i < line; ++i)
            fin.ignore(500,'\n');
        getline(fin, word, (char)9);
        if(findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    std:: cout << "Random Word: " << word << '\n';
    std::cout << "Definition: " << '\n';
    for(int i = 0; i < defi.size(); ++i)
        std::cout << i + 1 << ". " << defi[i] << '\n';
    std::cout << '\n';
}

///////////////////////////////////////////////////
// Question 12: Random word - 4 defis - choose correct defi
std::string Trie::getRandomWord()
{
    std::ifstream fin;
    std::string word;
    std::vector<std::string> defi;
    fin.open("../data_set/English_English_original.txt");
    int word_num = 160000, line; 
    while(true)
    {
        line = generator() % word_num;
        for(int i = 1; i < line; ++i)
            fin.ignore(500,'\n');
        getline(fin, word, (char)9);
        if(findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    return word;
}

std::string Trie::getRandomDefi_Of_Random_Word()
{
    std::ifstream fin;
    std::string word;
    std::vector<std::string> defi;
    srand(time(0));
    fin.open("../data_set/English_English_original.txt");
    int word_num = 160000, line; 
    while(true)
    {
        line = generator() % word_num;
        for(int i = 1; i < line; ++i)
            fin.ignore(500,'\n');
        getline(fin, word, (char)9);
        if(findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    int bound = defi.size();
    int index_defi = generator() % bound;
    return defi[index_defi];
}

std::string Trie::getRandomDefi_Of_Its_Word(std::string word)
{
    TrieNode* cur = root;
    std::string defi;
    for (int i = 0; i < word.size(); ++i)
	{
        int index = convertCharToNum(word[i]);
		cur = cur->edges[index];
	}
	if (cur->isEndOfWord)
    {
        int bound = cur->definition.size();
        int index_defi = generator() % bound;
        defi = cur->definition[index_defi];
    }
    return defi;
}

void Trie::quiz_1Word4Defis()
{
    std::string word = getRandomWord();
    std::string correct_defi = getRandomDefi_Of_Its_Word(word);
    std::string wrong_defi1 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi2 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi3 = getRandomDefi_Of_Random_Word();

    std::vector<std::string> defis = {correct_defi, wrong_defi1, wrong_defi2, wrong_defi3};
    shuffle(defis.begin(), defis.end(), std::default_random_engine(generator()));

    std::cout << "The given word is: " << word << '\n';
    std::cout << "With 4 given definitions, choose the correct one!\n";
    std::cout << "A. " << defis[0] << '\n';
    std::cout << "B. " << defis[1] << '\n';
    std::cout << "C. " << defis[2] << '\n';
    std::cout << "D. " << defis[3] << '\n';

    char ans;
    int index_ans = -1;
    while(index_ans == -1)
    {
        std::cout << "Your answer is: ";
        std::cin >> ans;
        if(ans == 'A' || ans == 'a') 
            index_ans = 0;
        else if(ans == 'B' || ans == 'b')
            index_ans = 1;
        else if(ans == 'C' || ans == 'c')
            index_ans = 2;
        else if(ans == 'D' || ans == 'd')
            index_ans = 3;
        else 
            std::cout << "Answer Invalid! Please choose again!\n";
    }
    if(defis[index_ans] == correct_defi)
        std::cout << "Correct Answer!\n";
    else
    {
        std::cout << "Incorrect Answer!\n";
        for(int i = 0; i < 4; ++i)
            if(defis[i] == correct_defi)
                index_ans = i;
        char tmp = index_ans + 'A';
        std::cout << "The correct answer is: " << tmp << ". " << correct_defi << '\n';
    }
}

void Trie::quiz_1Defi4Words()
{
    std::string correct_word = getRandomWord();
    std::string defi = getRandomDefi_Of_Its_Word(correct_word);
    std::string wrong_word1 = getRandomWord();
    std::string wrong_word2 = getRandomWord();
    std::string wrong_word3 = getRandomWord();

    std::vector<std::string> words = {correct_word, wrong_word1, wrong_word2, wrong_word3};
    shuffle(words.begin(), words.end(), std::default_random_engine(generator()));

    std::cout << "The given definition is: " << defi << '\n';
    std::cout << "With 4 given words, choose the correct one!\n";
    std::cout << "A. " << words[0] << '\n';
    std::cout << "B. " << words[1] << '\n';
    std::cout << "C. " << words[2] << '\n';
    std::cout << "D. " << words[3] << '\n';

    char ans;
    int index_ans = -1;
    while(index_ans == -1)
    {
        std::cout << "Your answer is: ";
        std::cin >> ans;
        if(ans == 'A' || ans == 'a') 
            index_ans = 0;
        else if(ans == 'B' || ans == 'b')
            index_ans = 1;
        else if(ans == 'C' || ans == 'c')
            index_ans = 2;
        else if(ans == 'D' || ans == 'd')
            index_ans = 3;
        else 
            std::cout << "Answer Invalid! Please choose again!\n";
    }
    if(words[index_ans] == correct_word)
        std::cout << "Correct Answer!\n";
    else
    {
        std::cout << "Incorrect Answer!\n";
        for(int i = 0; i < 4; ++i)
            if(words[i] == correct_word)
                index_ans = i;
        char tmp = index_ans + 'A';
        std::cout << "The correct answer is: " << tmp << ". " << correct_word << '\n';
    }
}

int main()
{
    Trie* obj = new Trie(Datasets::Eng_Eng);
    obj->build_Trie_From_Origin();
    // // Question 1
	// TrieNode* rootEE = nullptr;
    // build_Trie_EngEng(rootEE);
    // //deserialization(rootEE);
    // /*
    // findWordInTrie("'em", rootEE);
    // findWordInTrie("'gainst", rootEE);
	// findWordInTrie("apples", rootEE);
    // findWordInTrie("mastax", rootEE);
	// findWordInTrie("abc", rootEE);
    // findWordInTrie("appeal", rootEE);
    // std::cout << "------------------------------------------\n";

    // // Question 7
    // findWordInTrie("appealable", rootEE);
    // remove_Word_FromTrie("appealable", rootEE);
    // findWordInTrie("appealable", rootEE);
    // std::cout << "------------------------------------------\n";
    // */
    
    // // editExistedWordDefi("brace", "doraemon", rootEE);

    // std::vector<std::string>* adele = &defihehe;
    // std::vector<std::string> defihehe;
    // findWordExistedToGetDefi("brace", defihehe, rootEE);
    // defihehe[0] = "hehe";
    // findWordExistedToGetDefi
    // for(std::string s : defihehe)
    //     std::cout << s << "\n";

    // // // Question 9
    // // getRandomWordAndDefi(rootEE);
    // // std::cout << "------------------------------------------\n";

    // // // Question 12
    // // quiz_1Word4Defis(rootEE);
    // // std::cout << "------------------------------------------\n";

    // // // Question 13
    // // quiz_1Defi4Words(rootEE);
    // // std::cout << "------------------------------------------\n";
    // // //serialization(rootEE);
    // delete_Whole_Trie(rootEE);
	//return 0;
//}
//*/


//////////////
// .h
/*

#ifndef TRIE_H
#define TRIE_H

#include "DatasetIdentifiers.h"
#include "TrieNode.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <random>

const std::string preAdress = "../data_set/";
const std::string FileName[4] = {"English_English"};
const std::string originFileName[4] = {"English_English_original.txt", "English_Vietnamese_original.txt", 
                                        "Vietnamese_English_original.txt", "slang_emoji_original.txt"};

// Special Notice: Get the seed for random ONCE only! If not, same set of numbers every time
std::mt19937 generator(time(0));

int convertCharToNum(char c); 
char convertNumToChar(int n);

struct Trie{
public:

    Trie(Datasets::ID _type){
        typeOfDict = _type;
    }

    ~Trie(){
        delete root;
    }

    void build_Trie_EngEng();
    void build_Trie_From_Origin();
    void delete_Whole_Trie();
    void resetToOriginal();

    void serialization();
    void deserialization();

    void remove_Word_FromTrie(std::string word);
    void addWordAndDefiToTrie(std::string word, std::string defi);
    void findWordInTrie(std::string word);
    bool findWordExistedToGetDefi(std::string word, std::vector<std::string>& defi);
    void editExistedWordDefi(std::string word, std::string newDefi);

    void getRandomWordAndDefi();
    std::string getRandomWord();
    std::string getRandomDefi_Of_Its_Word(std::string word);
    std::string getRandomDefi_Of_Random_Word();

    void quiz_1Word4Defis();
    void quiz_1Defi4Words();

private:
    TrieNode* root;
    Datasets::ID typeOfDict;
};

#endif

*/