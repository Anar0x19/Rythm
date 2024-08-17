#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <pugixml.hpp>

struct WordInfo {
    int syllables;
    std::vector<int> stresses;
};

std::unordered_map<std::string, WordInfo> words_dict;

void loadOpenCorporaDictionary(const std::string& filename) {
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str())) {
        std::cerr << "Failed to load file " << filename << std::endl;
        return;
    }

    for (pugi::xml_node lemma : doc.child("dictionary").children("lemma")) {
        for (pugi::xml_node form : lemma.child("l").children("f")) {
            std::string word = form.attribute("t").as_string();
            // Для простоты предположим, что у нас есть информация о слогах и ударениях
            // В реальной реализации вам потребуется анализировать и извлекать эти данные
            int syllables = 0;  
            std::vector<int> stresses = {0}; 

            words_dict[word] = {syllables, stresses};
        }
    }
}

int main() {
    loadOpenCorporaDictionary("dict.opcorpora.xml");

    std::string pattern;
    std::cout << "Введите ритмический шаблон (например, '3 0,2'): ";
    std::getline(std::cin, pattern);

    auto matching_words = findRhythmicWords(pattern);

    std::cout << "Matching words: ";
    for (const auto& word : matching_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
