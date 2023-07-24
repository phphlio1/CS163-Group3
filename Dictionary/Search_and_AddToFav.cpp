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

int main() {
    TrieNode* rootEE = nullptr;
    build_Trie_EngEng(rootEE);

    search_and_addToFavoriteList(rootEE, "hell");

    delete_Whole_Trie(rootEE);
}