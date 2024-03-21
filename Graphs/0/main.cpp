#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;

void generateFile(const string &file_name, const string &orig_text) {
	ofstream file;
	file.open(file_name);
	file << orig_text;
	file.close();
}

// Дерево 
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
// Сортировка частот
bool compareNodes(const Node* a, const Node* b) {
    return a->frequency > b->frequency;
}
// Построение дерева
Node* buildHuffmanTree(vector<Node*> &nodes) {
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
// Коды 
void generateCodes(Node* root, string code, map<char, string> &codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '#') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}
// Таблица кодов
void printCodeTable(const map<char, string> &codes) {
    cout << "Code Table:" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}
// Кодируем код
string Fano_Encode(const string &text, const map<char, string> &codes) {
    string encodedText = "";

    for (char c : text) {
        encodedText += codes.at(c);
    }

    return encodedText;
}
// Декодируем код
string Fano_Decode(Node* root, const string &encodedText) {
    string decodedText = "";

    Node* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->data != '#') {
            decodedText += current->data;
            current = root;
        }
    }

    return decodedText;
}

// Функция для сжатия строки с использованием алгоритма RLE
string RLE_Encode(const string &orig_text) {
    string encoded;

    for (int i = 0; i < orig_text.length(); ++i) {
        int count = 1;

        while (static_cast<unsigned long long>(i) + 1 < orig_text.length() && orig_text[i] == orig_text[static_cast<basic_string<char, char_traits<char>, allocator<char>>::size_type>(i) + 1]) {
            count++;
            i++;
        }

        encoded += orig_text[i];
        encoded += to_string(count);
    }

    return encoded;
}

// Функция для декодирования строки, сжатой с помощью алгоритма RLE
string RLE_Decode(const string &orig_text) {
    string decoded;

    for (int i = 0; i < orig_text.length(); i += 2) {
        char symbol = orig_text[i];
        int count = orig_text[i + 1] - '0';

        for (int j = 0; j < count; ++j) {
            decoded += symbol;
        }
    }

    return decoded;
}

int main() {

    setlocale(LC_ALL, "ru");
    string alphabet = "MOPGSHmopgsh 0123456789^.";
    int n = 10000;

    string orig_text;
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        orig_text += alphabet[rand() % alphabet.size()];
    }

    string file_name = "txt/Original.txt";
    generateFile(file_name, orig_text);

    // Создание алфавита и частот символов
    map<char, int> frequencies;
    for (char c : orig_text) {
        frequencies[c]++;
    }

    // Построение дерева
    vector<Node*> nodes;
    for (const auto& pair : frequencies) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    Node* root = buildHuffmanTree(nodes);

    // Генерация кодов для символов
    map<char, string> codes;
    generateCodes(root, "", codes);

    // Печать таблицы кода
    printCodeTable(codes);

    // 1

    string fano = Fano_Encode(orig_text, codes);
    file_name = "txt/Solo_Fano_Encode.txt";
    generateFile(file_name, fano);

    string fano_de = Fano_Decode(root, fano);
    file_name = "txt/Solo_Fano_Decoded.txt";
    generateFile(file_name, fano_de);

    if (orig_text == fano_de) {
        cout << "FANO Success" << endl;
    }
    else {
        cout << "FANO Failed" << endl;
    }

    // 2

    string rle = RLE_Encode(orig_text);
    file_name = "txt/Solo_RLE_Encode.txt";
    generateFile(file_name, fano);

    string rle_de = RLE_Decode(rle);
    file_name = "txt/Solo_RLE_Decoded.txt";
    generateFile(file_name, fano_de);

    if (orig_text == rle_de) {
        cout << "RLE Success" << endl;
    }
    else {
        cout << "RLE Failed" << endl;
    }

    // 3

    // RLE+Fano

    string rle_encoded = RLE_Encode(orig_text);
    file_name = "txt/R_F_RLE_Encode.txt";
    generateFile(file_name, rle_encoded);

    string fano_rle_encoded = Fano_Encode(rle_encoded, codes);
    file_name = "txt/R_F_full_Encode.txt";
    generateFile(file_name, fano_rle_encoded);

    string fano_decoded = Fano_Decode(root, fano_rle_encoded);
    string fano_rle_decoded = RLE_Decode(fano_decoded);
    file_name = "txt/RLE_FANO_Decoded.txt";
    generateFile(file_name, fano_rle_decoded);

    if (orig_text == fano_rle_decoded) {
        cout << "RLE+FANO Success" << endl;
    }
    else {
        cout << "RLE+FANO Failed" << endl;
    }

    // Fano+RLE

    string fano_encoded = Fano_Encode(orig_text, codes);
    file_name = "txt/F_R_Fano_Encode.txt";
    generateFile(file_name, fano_encoded);

    string rle_fano_encoded = RLE_Encode(fano_encoded);
    file_name = "txt/F_R_full_Encode.txt";
    generateFile(file_name, rle_fano_encoded);

    string rle_decoded = RLE_Decode(rle_fano_encoded);
    string rle_fano_decoded = Fano_Decode(root, fano_encoded);
    file_name = "txt/FANO_RLE_Decoded.txt";
    generateFile(file_name, rle_fano_decoded);

    if (orig_text == rle_fano_decoded) {
        cout << "FANO+RLE Success" << endl;
    }
    else {
        cout << "FANO+RLE Failed" << endl;
    }

    return 0;
}