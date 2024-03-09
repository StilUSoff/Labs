#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Структура для хранения символа и его частоты
struct SymbolFrequency {
    char symbol;
    int frequency;
};

// Функция для сжатия строки с использованием алгоритма RLE
static std::string rleEncode(const std::string& input) {
    std::string encoded;

    for (int i = 0; i < input.length(); i++) {
        int count = 1;

        while (static_cast<unsigned long long>(i) + 1 < input.length() && input[i] == input[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1]) {
            count++;
            i++;
        }

        encoded += input[i];
        encoded += std::to_string(count);
    }

    return encoded;
}

// Функция для декодирования строки, сжатой с помощью алгоритма RLE
std::string rleDecode(const std::string& input) {
    std::string decoded;

    for (int i = 0; i < input.length(); i += 2) {
        char symbol = input[i];
        int count = input[i + 1] - '0';

        for (int j = 0; j < count; j++) {
            decoded += symbol;
        }
    }

    return decoded;
}

// Функция для сортировки символов по частоте в порядке убывания
bool compareFrequency(const SymbolFrequency& sf1, const SymbolFrequency& sf2) {
    return sf1.frequency > sf2.frequency;
}

// Рекурсивная функция для построения таблицы кодов Фано
void buildFanoTable(const std::vector<SymbolFrequency>& frequencies, int start, int end, std::vector<std::string>& codes) {
    if (start == end) {
        return;
    }

    int mid = start;
    int diff = frequencies[mid].frequency;

    while (mid + 1 < end && diff <= frequencies[mid + 1].frequency) {
        mid++;
        diff += frequencies[mid].frequency;
    }

    int i;
    int diff1 = diff;
    int diff2 = diff - frequencies[mid].frequency;

    if (abs(diff1 - diff2) < abs(diff1 - diff2 - frequencies[mid + 1].frequency)) {
        mid++;
        diff += frequencies[mid].frequency;
    }

    for (i = start; i <= mid; i++) {
        codes[frequencies[i].symbol - 'A'] += "0";
    }

    for (i = mid + 1; i <= end; i++) {
        codes[frequencies[i].symbol - 'A'] += "1";
    }

    buildFanoTable(frequencies, start, mid, codes);
    buildFanoTable(frequencies, mid + 1, end, codes);
}

// Функция для сжатия строки с использованием алгоритма Фано
std::string fanoEncode(const std::string& input) {
    std::string encoded;
    std::vector<SymbolFrequency> frequencies(10000);

    // Инициализация структуры символов и их частот
    for (char c = 'A'; c <= 'Z'; c++) {
        frequencies[c-'A'].symbol = c;
        frequencies[c-'A'].frequency = 0;
    }

    // Подсчет частот каждого символа в строке
    for (char c : input) {
        frequencies[c - 'A'].frequency++;
    }

    // Сортировка символов по частоте
    std::sort(frequencies.begin(), frequencies.end(), compareFrequency);

    // Построение таблицы кодов Фано
    std::vector<std::string> codes(26, " ");
    buildFanoTable(frequencies, 0, 25, codes);

    // Сжатие строки с помощью таблицы кодов Фано
    for (char c : input) {
        encoded += codes[c - 'A'];
    }

    return encoded;
}

int main() {
    setlocale(LC_ALL, "ru");
    std::string alphabet;
    int n;

    std::cout << "Введите алфавит: ";
    std::cin >> alphabet;

    std::cout << "Введите количество символов: ";
    std::cin >> n;

    std::string input;

    for (int i = 0; i < n; i++) {
        char c;
        std::cout << "Введите символ: ";
        std::cin >> c;
        input += c;
    }

    std::cout << "Исходная строка: " << input << std::endl;

    std::string rleEncoded = rleEncode(input);
    std::cout << "RLE сжатие: " << rleEncoded << std::endl;

    std::string fanoEncoded = fanoEncode(rleEncoded);
    std::cout << "Фано сжатие: " << fanoEncoded << std::endl;

    std::string fanoDecoded = rleDecode(fanoEncoded);
    std::cout << "Декодирование: " << fanoDecoded << std::endl;

    if (input == fanoDecoded) {
        std::cout << "Декодирование прошло успешно!" << std::endl;
    }
    else {
        std::cout << "Декодирование не удалось!" << std::endl;
    }

    return 0;
}
