#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <pugixml.hpp>

// Структура для хранения информации о ритме слова
struct WordInfo {
    int syllables;
    std::vector<int> stresses;
};

// Глобальный словарь слов с их ритмической структурой
std::unordered_map<std::string, WordInfo> words_dict;

// Функция для загрузки словаря из файла OpenCorpora
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
            int syllables = 0;  // Пример значения
            std::vector<int> stresses = {0};  // Пример значения

            words_dict[word] = {syllables, stresses};
        }
    }
}

int main() {
    // Загрузка словаря OpenCorpora
    loadOpenCorporaDictionary("dict.opcorpora.xml");

    // Ввод ритмического шаблона пользователем
    std::string pattern;
    std::cout << "Введите ритмический шаблон (например, '3 0,2'): ";
    std::getline(std::cin, pattern);

    // Поиск слов, соответствующих заданному ритму
    auto matching_words = findRhythmicWords(pattern);

    // Вывод найденных слов
    std::cout << "Matching words: ";
    for (const auto& word : matching_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
