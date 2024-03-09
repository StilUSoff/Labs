#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
};

bool compareNodes(const Node* a, const Node* b) {
    return a->frequency > b->frequency;
}

Node* buildHuffmanTree(vector<Node*>& nodes) {
    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), compareNodes);

        Node* mergedNode = new Node('#', nodes[nodes.size() - 2]->frequency + nodes[nodes.size() - 1]->frequency);
        mergedNode->left = nodes[nodes.size() - 2];
        mergedNode->right = nodes[nodes.size() - 1];

        nodes.pop_back();
        nodes.pop_back();

        nodes.push_back(mergedNode);
    }

    return nodes[0];
}

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '#') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

void printCodeTable(const map<char, string>& codes) {
    cout << "Табличка кодов:" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

string encodeText(const string& text, const map<char, string>& codes) {
    string encodedText = "";

    for (char c : text) {
        encodedText += codes.at(c);
    }

    return encodedText;
}

string runLengthEncode(const string& text) {
    string encodedText;

    int count = 1;
    for (size_t i = 1; i <= text.size(); ++i) {
        if (i == text.size() || text[i] != text[i - 1]) {
            encodedText += text[i - 1];
            if (count > 1) {
                encodedText += to_string(count);
            }
            count = 1;
        }
        else {
            count++;
        }
    }

    return encodedText;
}

string runLengthDecode(const string& encodedText) {
    string decodedText;

    string countStr; // Добавленная строка для хранения цифр

    for (size_t i = 0; i < encodedText.size(); ++i) {
        char character = encodedText[i];

        if (isdigit(character)) {
            countStr += character;
        }
        else {
            int count = (countStr.empty()) ? 1 : stoi(countStr);
            while (count > 0) {
                decodedText += character;
                count--;
            }

            countStr = ""; // Обнуляем строку для следующего символа
        }
    }

    return decodedText;
}

string decodeText(const map<string, char>& codes, const string& encodedText) {
    string decodedText = "";
    string currentCode = "";

    for (char bit : encodedText) {
        currentCode += bit;
        auto it = codes.find(currentCode);

        if (it != codes.end()) {
           // cout << "Decoded Character: " << it->second << endl;  // Print decoded character
            decodedText += it->second;
            currentCode = "";  // Сброс текущего кода для следующего символа
        }
    }

    return decodedText;
}


bool checkEquality(const string& originalText, const string& decodedText) {
    return originalText == decodedText;
}

void printTreeStructure(Node* root, int indent = 0) {
    if (root != nullptr) {
        cout << string(indent, ' ') << root->data << "(" << root->frequency << ")" << endl;
        printTreeStructure(root->left, indent + 2);
        printTreeStructure(root->right, indent + 2);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    string alphabet = "кемсярКЕМСЯР 123456789[.";
    string text;

    // Генерация случайного текста
    srand(time(NULL));
    for (int i = 0; i < 10000; ++i) {
        text += alphabet[rand() % alphabet.size()];
    }

    // Создание алфавита и частот символов
    map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }

    // Построение дерева для кодирования
    vector<Node*> nodesEncode;
    for (const auto& pair : frequencies) {
        nodesEncode.push_back(new Node(pair.first, pair.second));
    }
    Node* rootEncode = buildHuffmanTree(nodesEncode);

    // Построение дерева для декодирования
    vector<Node*> nodesDecode;
    for (const auto& pair : frequencies) {
        nodesDecode.push_back(new Node(pair.first, pair.second));
    }
    Node* rootDecode = buildHuffmanTree(nodesDecode);

    // Генерация кодов для символов
    map<char, string> codes;
    generateCodes(rootEncode, "", codes);

    // Преобразование в обратное отображение (код -> символ) для декодирования Фано
    map<string, char> reverseCodes;
    for (const auto& pair : codes) {
        reverseCodes[pair.second] = pair.first;
    }

    // Печать таблицы кода
    printCodeTable(codes);

    // Кодирование текста алгоритмом Фано
    string encodedTextFano = encodeText(text, codes);

    // Кодирование текста алгоритмом RLE
    string encodedTextRLE = runLengthEncode(encodedTextFano);

    // Декодирование текста из RLE
    string decodedTextRLE = runLengthDecode(encodedTextRLE);

    // Декодирование текста из алгоритма Фано
    string decodedTextFano = decodeText(reverseCodes, encodedTextFano);

    // Печать результатов
    cout << "\n Сам текст: " << text << endl;
    cout << "Кодировка Фано: " << encodedTextFano << endl;
    cout << "Кодировка RLE: " << encodedTextRLE << endl;
    cout << "Декодированный текст весь: " << decodedTextFano << endl;

    // Расчет коэффициента сжатия для алгоритма Фано
    double compressionRatioFano = static_cast<double>(encodedTextFano.size()) / text.size();
    cout << "Коэффициент сжатия (Fano): " << compressionRatioFano << endl;

    // Расчет коэффициента сжатия для алгоритма RLE
    double compressionRatioRLE = static_cast<double>(encodedTextRLE.size()) / encodedTextFano.size();
    cout << "Коэффициент сжатия (RLE): " << compressionRatioRLE << endl;

    // Общий коэффициент сжатия 
    double comperrsionRatioAll = static_cast<double>(encodedTextRLE.size()) / text.size();
    cout << "Коэффициент сжатия (общий): " << comperrsionRatioAll << endl;
    // Проверка равенства исходного и декодированного текста
    if (text == decodedTextFano) {
        cout << "Все хорошо!" << endl;
    }
    else { cout << "Что то пошло не так (((" << endl; }
    assert(checkEquality(text, decodedTextFano) && "Ошибка!!: Декодированный текст не равен самому тексту(");

    // Очистка памяти
    delete rootEncode;
    delete rootDecode;

    return 0;
}
