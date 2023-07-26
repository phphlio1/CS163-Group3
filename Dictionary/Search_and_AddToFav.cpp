#include "Trie.h"

void allSuggestWord(TrieNode* root, std::string subWord, std::vector<std::string>& suggest) {
    for (int i = 0 ; i < TrieSize ; i++) {
        if (root->edges[i] != nullptr){
            subWord += convertNumToChar(i);
            if (root->edges[i]->isEndOfWord) suggest.push_back(subWord);
            allSuggestWord(root->edges[i], subWord, suggest);
            subWord.pop_back();
        }
    }
}

// Question 2 : User can search for a keyword. Users can add the word to their favorite list.
void searchForAWord_withSuggestion(TrieNode* root, std::string subWord, std::vector<std::string>& suggest) {
    TrieNode* cur = root;
    for (int i = 0 ; i < subWord.length() ; i++) {
        int index = convertCharToNum(subWord[i]);
        if (cur->edges[index] == nullptr) return ;
        cur = cur->edges[index];
    }

    if (cur->isEndOfWord) suggest.push_back(subWord);

    allSuggestWord(cur, subWord, suggest);
}

void search_and_addToFavoriteList(TrieNode* root, std::string subWord) {
    std::vector<std::string> test;
    searchForAWord_withSuggestion(root, subWord, test);
    for (int i = 0 ; i < test.size() ; i++) std::cout << "[" << i + 1 << "] " << test[i] << "\n";

    int choice;
    std::cout << "Your choice is : ";
    std::cin >> choice;

    std::ofstream fout("../data_set/favorite.txt", std::ios_base::app);
    if (!fout.is_open()) std::cout << "File not found";
    else fout << test[choice - 1] << "\n";
    fout.close();
}

// Question 10 : User can view their favorite list.
void readData_FavoriteList(std::vector<std::string> &fav) {
    std::ifstream fin;
    fin.open("../data_set/favorite.txt");
    if (!fin.is_open()) {
        std::cout << "File not found\n";
        return ; 
    }
    std::string word;
    while (fin >> word) fav.push_back(word);
    fin.close();
}

void viewFavoriteList() {
    std::vector<std::string> fav;
    readData_FavoriteList(fav);
    for (int i = 0 ; i < fav.size() ; i++) std::cout << "[" << i + 1 << "] " << fav[i] << "\n";
}

// Question 11 : User can remove a word from their favorite list.
void removeAWordFromFavoriteList() {
    std::vector<std::string> fav;
    readData_FavoriteList(fav);
    for (int i = 0 ; i < fav.size() ; i++) std::cout << "[" << i + 1 << "] " << fav[i] << "\n";

    std::cout << "Order of the word you want to remove : ";
    int order;
    std::cin >> order;

    std::ofstream fout("../data_set/favorite.txt", std::ios_base::trunc);
    if (!fout.is_open()) {
        std::cout << "File not found !\n";
        return ;
    }

    for (int i = 0 ; i < fav.size() ; i++) {
        if (i != order - 1) {
            fout << fav[i] << "\n";
        }
    }
    fout.close();
    std::cout << "Remove successfully !";
}

int main() {
    TrieNode* rootEE = nullptr;
    build_Trie_EngEng(rootEE);

    removeAWordFromFavoriteList();

    delete_Whole_Trie(rootEE);
}