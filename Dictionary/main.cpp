#include "Trie.h"

int main()
{
    // Question 1
    Trie *obj = new Trie(Datasets::Eng_Eng);
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

    obj->search_and_addToFavoriteList("asteroid");
    std::cout << "------------------------------------------\n";
    obj->viewFavoriteList();
    std::cout << "------------------------------------------\n";
    obj->removeAWordFromFavoriteList();
    std::cout << "------------------------------------------\n";
    obj->viewFavoriteList();
    std::cout << "------------------------------------------\n";

    obj->findWordFromSubDefi("An");
    std::cout << "------------------------------------------\n";


    // Do not delete because we already have destructor
    return 0;
}