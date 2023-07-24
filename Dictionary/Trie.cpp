#include "Trie.h"

////////////////////////////////////////////////// General function
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

//////////////////////////////////////////////////////////////////

Trie::Trie(Datasets::ID _type):
    root(nullptr), typeOfDict(_type), num_line(0){}

Trie::~Trie(){ delete root;}

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
        ++num_line;
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
        ++num_line;
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

void Trie::Serialization_DFS()
{
    std::ofstream fout;
	fout.open("English_English_serializationDFS.txt");
    if(!fout.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
    root = root->Serialize_Traversal_DFS(fout, 0);
    fout.close();
    std::cout << "Serialization complete!\n";
}

void Trie::Deserialization_DFS()
{
    std::ifstream fin;
	fin.open("English_English_serializationDFS.txt");
    if(!fin.is_open()) 
    {
        std::cout << "File cannot open!\n";
        return;
    }
    std::string str1;
	getline(fin, str1, '_');
	root = new TrieNode;
    getline(fin, str1, '_');
    getline(fin, str1, '_');
    root->isEndOfWord = false;
    root = root->Deserialize_Traversal_DFS(fin, 0);
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
    
    std::cout << "There are " << cur->definition.size() << " definition in the dictionary:\n";
    for(int i = 0; i < cur->definition.size(); ++i)
        std::cout << i + 1 << ". " << cur->definition[i] << "\n";
    std::cout << "------------------------------------------\n";
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
    while(true)
    {
        int line = generator() % num_line;
        for(int i = 1; i < line; ++i)
            fin.ignore(500,'\n');
        getline(fin, word, (char)9);
        if(findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    std::cout << "Random Word: " << word << '\n';
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
    while(true)
    {
        int line = generator() % num_line;
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
    while(true)
    {
        int line = generator() % num_line;
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
    // Question 1
    Trie* obj = new Trie(Datasets::Eng_Eng);
    obj->build_Trie_EngEng();

    std::cout << "SET 1:\n";
    obj->findWordInTrie("'em");
    obj->findWordInTrie("'gainst");
	obj->findWordInTrie("apples");
    obj->findWordInTrie("mastax");
	obj->findWordInTrie("abc");
    obj->findWordInTrie("appeal");
    obj->findWordInTrie("spondaic");
    obj->Serialization_DFS();
    obj->delete_Whole_Trie();
    std::cout << "------------------------------------------\n";

    std::cout << "SET 2:\n";
    obj->Deserialization_DFS();
    obj->findWordInTrie("'em");
    obj->findWordInTrie("'gainst");
	obj->findWordInTrie("apples");
    obj->findWordInTrie("mastax");
	obj->findWordInTrie("abc");
    obj->findWordInTrie("appeal");
    obj->findWordInTrie("spondaic");
    std::cout << "------------------------------------------\n";

    // Question 6
    obj->editExistedWordDefi("appeal", "doraemon");
    obj->findWordInTrie("appeal");
    
    // Question 7
    obj->findWordInTrie("appealable");
    obj->remove_Word_FromTrie("appealable");
    obj->findWordInTrie("appealable");
    std::cout << "------------------------------------------\n";

    // Question 9
    obj->getRandomWordAndDefi();
    std::cout << "------------------------------------------\n";

    // Question 12
    obj->quiz_1Word4Defis();
    std::cout << "------------------------------------------\n";

    // Question 13
    obj->quiz_1Defi4Words();
    std::cout << "------------------------------------------\n";

    // Do not delete because we already have destructor
	return 0;
}