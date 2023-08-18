#include <fstream>
#include <iostream>
#include <vector>

void addToHistory(std::string word) {
    std::ofstream fout("../data_set/history.txt", std::ios_base::app);
    if (fout.is_open()) {
        fout << word << "\n";
    }
    else {
        std::cout << "Error opening file !";
        return ;
    }
    fout.close();
}

std::vector<std::string> historyWords() {
    std::vector<std::string> history_vector;
    std::ifstream fin("../data_set/history.txt");
    if (fin.is_open()) {
        std::string s;
        while (getline(fin, s)) {
            history_vector.push_back(s);
        }
    }
    else {
        std::cout << "Error opening file !";
        return history_vector;
    }
    fin.close();
    return history_vector;
}


// // uncomment code for testing if you want
// int main() {
//     addToHistory("meo meo");
//     addToHistory("gau gau");
//     addToHistory("xin chao");

//     std::vector<std::string> test = historyWords();
//     for (int i = 0 ; i < test.size() ; i++) {
//         std::cout << test[i] << "\n";
//     }

//     return 0;
// }