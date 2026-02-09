#pragma once
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

class ini_parser {
public:
    ini_parser(const std::string& filename);

    template<typename T>
    T get_value(const std::string& full_key) const {
        // Проверка формата ключа
        auto dot_pos = full_key.find('.');
        if (dot_pos == std::string::npos)
            throw std::runtime_error("Invalid key format");

        // секция и ключ
        std::string section = full_key.substr(0, dot_pos);
        std::string key = full_key.substr(dot_pos + 1);

        // поиск секции
        auto sec_it = __file.find(section);
        if (sec_it == __file.end())
            throw std::runtime_error("Section not found: " + section);

        // поиск ключа
        auto key_it = sec_it->second.find(key);
        if (key_it == sec_it->second.end()) {
            std::string hint = "Available keys: ";
            for (const auto& i : sec_it->second)
                hint += i.first + " ";
            throw std::runtime_error("Key not found: " + key + ". " + hint);
        }

        //поиск значения
        const std::string& value_it = key_it->second;
        if (value_it.empty())
            throw std::runtime_error("Value for key '" + key + "' is empty.");

        // Превращаем в нужный тип для возврата
        std::stringstream ss(value_it);
        T value;
        ss >> value;

        return value;
    }

private:
    std::map<std::string, std::map<std::string, std::string>> __file;
};
