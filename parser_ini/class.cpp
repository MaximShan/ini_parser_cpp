#include "head.h"
#include <fstream>
#include <algorithm>

ini_parser::ini_parser(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open ini file: " + filename);

    std::string line;
    std::string section;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;

        
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        // Секция
        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
            continue;
        }

        // поиск позиции =
        auto eq_pos = line.find('=');
        if (eq_pos == std::string::npos)
            throw std::runtime_error("Syntax error at line " + std::to_string(line_number));

        std::string key = line.substr(0, eq_pos);
        std::string value = line.substr(eq_pos + 1);

        // Убираем комментарий после ;
        auto comment_pos = value.find(';');
        if (comment_pos != std::string::npos)
            value = value.substr(0, comment_pos);
      
        // Сохраняем только если ключ ещё не существует
        if (__file[section].count(key) == 0)
            __file[section][key] = value;
    }
}
