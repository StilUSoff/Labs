#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <ctime>

using namespace std;

vector<pair<char, int> > vectorize(const vector<int>& encoded) {
    vector<pair<char, int> > result;
    int count = 1;
    char current = static_cast<char>(encoded[0]);

    for (int i = 1; i < encoded.size(); ++i) {
        if (encoded[i] == encoded[i - 1]) {
            ++count;
        } else {
            result.push_back(make_pair(current, count));
            count = 1;
            current = static_cast<char>(encoded[i]);
        }
    }

    result.push_back(make_pair(current, count));
    return result;
}

// Функция для кодирования алгоритмом LZW
vector<int> encodeLZW(const string& input) {
    map<string, int> dictionary;
    vector<int> encoded;
    int dictSize = 256;

    for (int i = 0; i < 256; ++i) {
        dictionary[string(1, i)] = i;
    }

    string current;
    for (char c : input) {
        string combined = current + c;
        if (dictionary.find(combined) != dictionary.end()) {
            current = combined;
        } else {
            encoded.push_back(dictionary[current]);
            dictionary[combined] = dictSize++;
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        encoded.push_back(dictionary[current]);
    }

    return encoded;
}

// Функция для декодирования алгоритмом LZW
string decodeLZW(const vector<int>& encoded) {
    map<int, string> dictionary;
    string decoded;
    int dictSize = 256;

    for (int i = 0; i < 256; ++i) {
        dictionary[i] = string(1, i);
    }

    string current(1, encoded[0]);
    string next;
    decoded = current;

    for (int i = 1; i < encoded.size(); ++i) {
        if (dictionary.find(encoded[i]) != dictionary.end()) {
            next = dictionary[encoded[i]];
        } else if (encoded[i] == dictSize) {
            next = current + current[0];
        } else {
            throw "Неверный входной код";
        }

        decoded += next;
        dictionary[dictSize++] = current + next[0];
        current = next;
    }

    return decoded;
}

// Функция для кодирования алгоритмом RLE
vector<pair<char, int> > encodeRLE(const string& input) {
    vector<pair<char, int> > encoded;
    int count = 1;
    char current = input[0];

    for (int i = 1; i < input.length(); ++i) {
        if (input[i] == current) {
            count++;
        } else {
            encoded.push_back(make_pair(current, count));
            current = input[i];
            count = 1;
        }
    }

    encoded.push_back(make_pair(current, count));

    return encoded;
}

// Функция для декодирования алгоритмом RLE
string decodeRLE(const vector<pair<char, int> >& encoded) {
    string decoded;

    for (auto p : encoded) {
        decoded.append(p.second, p.first);
    }

    return decoded;
}

// Функция для генерации случайной строки из указанного алфавита
string generateRandomString(int length, const string& alphabet) {
    string result;
    int alphabetSize = alphabet.length();
    for (int i = 0; i < length; ++i) {
        result += alphabet[rand() % alphabetSize];
    }
    return result;
}

int main() {
    srand(time(nullptr));

    const string alphabet = "NnOoPpRrSsTt 0123456789$.";

    // Генерация случайной строки
    string input = generateRandomString(10000, alphabet);

    // Запись строки в файл
    ofstream outFile("input.txt");
    if (outFile.is_open()) {
        outFile << input;
        outFile.close();
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    // Кодирование и декодирование алгоритмом LZW
    vector<int> encodedLZW = encodeLZW(input);
    string decodedLZW = decodeLZW(encodedLZW);

    // Проверка корректности декодирования LZW
    if (input != decodedLZW) {
        cout << "Ошибка декодирования LZW." << endl;
        return 1;
    }

    // Кодирование и декодирование алгоритмом RLE
    vector<pair<char, int> > encodedRLE = encodeRLE(input);
    string decodedRLE = decodeRLE(encodedRLE);

    // Проверка корректности декодирования RLE
    if (input != decodedRLE) {
        cout << "Ошибка декодирования RLE." << endl;
        return 1;
    }

    // Вывод коэффициента сжатия для каждого метода
    cout << "Коэффициент сжатия LZW: " << static_cast<double>(input.length()) / encodedLZW.size() << endl;
    cout << "Коэффициент сжатия RLE: " << static_cast<double>(input.length()) / encodedRLE.size() << endl;

    // Кодирование и декодирование алгоритмом RLE + LZW

    // Преобразование закодированных данных RLE в вектор символов
    vector<char> rleData;
    for (auto& p : encodedRLE) {
        rleData.insert(rleData.end(), p.second, p.first);
    }

    // Кодирование закодированных данных RLE методом LZW
    vector<int> encodedRLELZW = encodeLZW(string(rleData.begin(), rleData.end()));

    string decodedRLELZW_1 = decodeLZW(encodedRLELZW);
    string decodedRLELZW = decodeRLE(decodedRLELZW_1);

    // Проверка корректности декодирования RLE + LZW
    if (input != decodedRLELZW) {
        cout << "Ошибка декодирования RLE + LZW." << endl;
        return 1;
    }

    // Кодирование и декодирование алгоритмом LZW + RLE

    // Кодирование закодированных данных алгоритмом LZW методом RLE
    
    vector<pair<char, int> > encodedLZWRLE = encodeRLE(vectorize(encodedLZW));

    string decodedLZWRLE_1 = decodeRLE(encodedLZWRLE);
    string decodedLZWRLE = decodeLZW(decodedLZWRLE_1);

    // Проверка корректности декодирования LZW + RLE
    if (input != decodedLZWRLE) {
        cout << "Ошибка декодирования LZW + RLE." << endl;
        return 1;
    }

    // Вывод коэффициента сжатия для двухступенчатого кодирования
    cout << "Коэффициент сжатия RLE + LZW: " << static_cast<double>(input.length()) / encodedRLELZW.size() << endl;
    cout << "Коэффициент сжатия LZW + RLE: " << static_cast<double>(input.length()) / encodedLZWRLE.size() << endl;

    return 0;
}
