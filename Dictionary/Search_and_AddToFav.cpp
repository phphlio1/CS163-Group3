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

// int main() {
//     TrieNode* rootEE = nullptr;
//     build_Trie_EngEng(rootEE);

//     std::vector<std::string> test;
//     searchForAWord_withSuggestion(rootEE, "hell", test);
//     for (int i = 0 ; i < test.size() ; i++) std::cout << test[i] << "\n";

//     delete_Whole_Trie(rootEE);
// }