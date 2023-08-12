#include "Trie.h"
// Special Notice: Get the seed for random ONCE only! If not, same set of numbers every time
// extern unsigned int seed;
// unsigned int seed = time(0);
std::mt19937 generator(0);

Trie::Trie(Datasets::ID _type) : root(nullptr), typeOfDict(_type), num_line(0) {}

Trie::~Trie() { delete root; }

void Trie::delete_Whole_Trie() { delete root; }

void Trie::build_Trie_EngEng()
{
    std::ifstream fin;
    fin.open("../data_set/English_English_original.txt");
    if (!fin.is_open())
    {
        std::cout << "File cannot open!\n";
        return;
    }
    root = new TrieNode;
    while (!fin.eof())
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

    if (typeOfDict == Datasets::Eng_Viet)

        if (!fin.is_open())
        {
            std::cout << "File cannot open!\n";
            return;
        }
    root = new TrieNode;
    while (!fin.eof())
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
    TrieNode *cur = root;
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
    TrieNode *cur = root;
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
        for (int i = 0; i < cur->definition.size(); ++i)
            std::cout << i + 1 << ". " << cur->definition[i] << '\n';
        std::cout << '\n';
    }
    else
        std::cout << word << " NOT FOUND!\n";
}

bool Trie::findWordExistedToGetDefi(std::string word, std::vector<std::string> &defi)
{
    TrieNode *cur = root;
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
    if (!fout.is_open())
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
    if (!fin.is_open())
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
// Question 3: Users can search for a definition.
void Trie::findWordFromSubDefi(std::string subDefi){
    std::vector<std::string> keywords;
    root->checkSubString("", subDefi, keywords, checkerST);
    int cnt = 0;
    for(std::string tmp : keywords){ 
        ++cnt;
        std::cout << tmp << "\n";
        if(cnt == 5)
            return;
    }
}

///////////////////////////////////////////////////
// Question 5: Users can add a new word and its definition
// ham addword

///////////////////////////////////////////////////
// Question 6: Users can edit the defi of an existing word
void Trie::editExistedWordDefi(std::string word, std::string newDefi)
{
    // The std::cout << code below can be edit by frontend coders

    ////////////////////////////////// find the word
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
        {
            std::cout << "There is no " << word << " in the dictionary\n";
            return;
        }
        cur = cur->edges[index];
    }
    if (!cur->isEndOfWord)
    {
        std::cout << "There is no " << word << " in the dictionary\n";
        return;
    }
    //////////////////////////////////////////////////

    std::cout << "There are " << cur->definition.size() << " definition in the dictionary:\n";
    for (int i = 0; i < cur->definition.size(); ++i)
        std::cout << i + 1 << ". " << cur->definition[i] << "\n";
    std::cout << "------------------------------------------\n";
    std::cout << "1. Adding new definition for this word.\n";
    std::cout << "2. Replacing one existed definition by new definition.\n";
    std::cout << "3. Replacing all definition by this new definition.\n";
    std::cout << "Please input what do you want (only by number 1, 2, 3):\n";
    int userInput;
    std::cin >> userInput;
    while (userInput < 1 || userInput > 3)
    {
        std::cout << "Please input what do you want (only by number 1, 2, 3):\n";
        std::cin >> userInput;
    }

    int typeOfAction = userInput;

    if (typeOfAction == 1)
    {
        cur->definition.push_back(newDefi);
        std::cout << "Change successfully\n";
    }

    if (typeOfAction == 2)
    {
        std::cout << "Please input the number (from 1 to " << cur->definition.size() << ") to choose the editing definition\n";

        while (std::cin >> userInput)
        {
            if (userInput < 1 || userInput > cur->definition.size())
                std::cout << "Please input the number (from 1 to " << cur->definition.size() << ") to choose the editing definition\n";
            else
            {
                cur->definition[userInput - 1] = newDefi;
                std::cout << "Change successfully\n";
                break;
            }
        }
    }

    if (typeOfAction == 3)
    {
        cur->definition.clear();
        cur->definition.push_back(newDefi);
        std::cout << "Change successfully\n";
    }
}

///////////////////////////////////////////////////
// Question 7: Users can remove a word from the dictionary.
void Trie::remove_Word_FromTrie(std::string word)
{
    TrieNode *cur = root;
    for (int i = 0; i < word.size(); ++i)
    {
        int index = convertCharToNum(word[i]);
        if (!cur->edges[index])
            return;
        cur = cur->edges[index];
    }
    if (cur->isEndOfWord)
    {
        cur->isEndOfWord = false;
        cur->definition.clear();
    }
}

///////////////////////////////////////////////////
// Question 8: Users can reset the dictionary to its original state.

void Trie::resetToOriginal()
{
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
    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, word, (char)9);
        if (findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    std::cout << "Random Word: " << word << '\n';
    std::cout << "Definition: " << '\n';
    for (int i = 0; i < defi.size(); ++i)
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
    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, word, (char)9);
        if (findWordExistedToGetDefi(word, defi))
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
    fin.open("../data_set/English_English_original.txt");
    while (true)
    {
        int line = generator() % num_line;
        for (int i = 1; i < line; ++i)
            fin.ignore(500, '\n');
        getline(fin, word, (char)9);
        if (findWordExistedToGetDefi(word, defi))
            break;
    }
    fin.close();
    int bound = defi.size();
    int index_defi = generator() % bound;
    return defi[index_defi];
}

std::string Trie::getRandomDefi_Of_Its_Word(std::string word)
{
    TrieNode *cur = root;
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


void Trie::choose_1Word4Defis()
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
    while (index_ans == -1)
    {
        std::cout << "Your answer is: ";
        std::cin >> ans;
        if (ans == 'A' || ans == 'a')
            index_ans = 0;
        else if (ans == 'B' || ans == 'b')
            index_ans = 1;
        else if (ans == 'C' || ans == 'c')
            index_ans = 2;
        else if (ans == 'D' || ans == 'd')
            index_ans = 3;
        else
            std::cout << "Answer Invalid! Please choose again!\n";
    }
    if (defis[index_ans] == correct_defi)
        std::cout << "Correct Answer!\n";
    else
    {
        std::cout << "Incorrect Answer!\n";
        for (int i = 0; i < 4; ++i)
            if (defis[i] == correct_defi)
                index_ans = i;
        char tmp = index_ans + 'A';
        std::cout << "The correct answer is: " << tmp << ". " << correct_defi << '\n';
    }
}

void Trie::choose_1Defi4Words()
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
    while (index_ans == -1)
    {
        std::cout << "Your answer is: ";
        std::cin >> ans;
        if (ans == 'A' || ans == 'a')
            index_ans = 0;
        else if (ans == 'B' || ans == 'b')
            index_ans = 1;
        else if (ans == 'C' || ans == 'c')
            index_ans = 2;
        else if (ans == 'D' || ans == 'd')
            index_ans = 3;
        else
            std::cout << "Answer Invalid! Please choose again!\n";
    }
    if (words[index_ans] == correct_word)
        std::cout << "Correct Answer!\n";
    else
    {
        std::cout << "Incorrect Answer!\n";
        for (int i = 0; i < 4; ++i)
            if (words[i] == correct_word)
                index_ans = i;
        char tmp = index_ans + 'A';
        std::cout << "The correct answer is: " << tmp << ". " << correct_word << '\n';
    }
}

void Trie::prepare_1Word4Defis()
{
    std::vector<std::string> wordSet(10);
    std::vector<std::vector<std::string>> defiSet(10);
    std::vector<int> correctOption(10);
    for(int i = 0; i < 10; ++i)
        getComponent_1Word4Defis(wordSet, defiSet, correctOption, i);
}

void Trie::getComponent_1Word4Defis(std::vector<std::string>& wordSet, std::vector<std::vector<std::string>>& defiSet,
std::vector<int>& correctOption, int index)
{
    std::string word = getRandomWord();
    std::string correct_defi = getRandomDefi_Of_Its_Word(word);
    std::string wrong_defi1 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi2 = getRandomDefi_Of_Random_Word();
    std::string wrong_defi3 = getRandomDefi_Of_Random_Word();

    std::vector<std::string> defis = {correct_defi, wrong_defi1, wrong_defi2, wrong_defi3};
    shuffle(defis.begin(), defis.end(), std::default_random_engine(generator()));

    wordSet[index] = word;
    defiSet[index] = defis;
    for(int i = 0; i < 4; ++i)
        if(correct_defi == defis[i])
            correctOption[index] = i;
}

void Trie::prepare_1Defi4Words()
{
    std::vector<std::string> defiSet(10);
    std::vector<std::vector<std::string>> wordSet(10);
    std::vector<int> correctOption(10);
    for(int i = 0; i < 10; ++i)
        getComponent_1Word4Defis(defiSet, wordSet, correctOption, i);
}

void Trie::getComponent_1Defi4Words(std::vector<std::string>& defiSet, std::vector<std::vector<std::string>>& wordSet,
std::vector<int>& correctOption, int index)
{
    std::string correct_word = getRandomWord();
    std::string defi = getRandomDefi_Of_Its_Word(correct_word);
    std::string wrong_word1 = getRandomWord();
    std::string wrong_word2 = getRandomWord();
    std::string wrong_word3 = getRandomWord();

    std::vector<std::string> words = {correct_word, wrong_word1, wrong_word2, wrong_word3};
    shuffle(words.begin(), words.end(), std::default_random_engine(generator()));

    defiSet[index] = defi;
    wordSet[index] = words;
    for(int i = 0; i < 4; ++i)
        if(correct_word == words[i])
            correctOption[index] = i;
}

// Favourite list
// Question 2 : User can search for a keyword. Users can add the word to their favorite list.
void Trie::searchForAWord_withSuggestion(std::string subWord, std::vector<std::string> &suggest)
{
    TrieNode *cur = root;
    for (int i = 0; i < subWord.length(); i++)
    {
        int index = convertCharToNum(subWord[i]);
        if (cur->edges[index] == nullptr)
            return;
        cur = cur->edges[index];
    }

    if (cur->isEndOfWord)
        suggest.push_back(subWord);

    cur->allSuggestWord(subWord, suggest);
}

void Trie::search_and_addToFavoriteList(std::string subWord)
{
    std::vector<std::string> test;
    searchForAWord_withSuggestion(subWord, test);
    for (int i = 0; i < test.size(); i++)
        std::cout << "[" << i + 1 << "] " << test[i] << "\n";

    int choice;
    std::cout << "Your choice is : ";
    std::cin >> choice;

    std::ofstream fout(preAdress + preFavoriteName + favoriteFileName[typeOfDict], std::ios_base::app);
    if (!fout.is_open())
        std::cout << "File not found";
    else
        fout << test[choice - 1] << "\n";
    fout.close();
}

// Question 10 : User can view their favorite list
void Trie::readData_FavoriteList(std::vector<std::string> &fav)
{
    std::ifstream fin;
    fin.open(preAdress + preFavoriteName + favoriteFileName[typeOfDict]);
    if (!fin.is_open())
    {
        std::cout << "File not found\n";
        return;
    }
    std::string word;
    while (fin >> word)
        fav.push_back(word);
    fin.close();
}

void Trie::viewFavoriteList()
{
    std::vector<std::string> fav;
    readData_FavoriteList(fav);
    for (int i = 0; i < fav.size(); i++)
        std::cout << "[" << i + 1 << "] " << fav[i] << "\n";
}

// Question 11 : User can remove a word from their favorite list.
void Trie::removeAWordFromFavoriteList()
{
    std::vector<std::string> fav;
    readData_FavoriteList(fav);
    for (int i = 0; i < fav.size(); i++)
        std::cout << "[" << i + 1 << "] " << fav[i] << "\n";

    std::cout << "Order of the word you want to remove : ";
    int order;
    std::cin >> order;

    std::ofstream fout(preAdress + preFavoriteName + favoriteFileName[typeOfDict], std::ios_base::trunc);
    if (!fout.is_open())
    {
        std::cout << "File not found !\n";
        return;
    }

    for (int i = 0; i < fav.size(); i++)
    {
        if (i != order - 1)
        {
            fout << fav[i] << "\n";
        }
    }
    fout.close();
    std::cout << "Remove successfully !";
}
