#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <fstream>

using namespace std;

void Generate_File(const string &file_name, const string &orig_text) {
	ofstream file;
	file.open(file_name);
	file << orig_text;
	file.close();
}

// Дерево 
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char d, int freq) : data(d), freq(freq), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
};

// Сортировка частот
bool Nodes_Comparing(const Node* a, const Node* b) {
    return a->freq > b->freq;
}

// Построение дерева
Node* Build_Tree(vector<Node*> &nodes) {
    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), Nodes_Comparing);

        Node* merged_node = new Node('#', nodes[nodes.size() - 2]->freq + nodes[nodes.size() - 1]->freq);
        merged_node->left = nodes[nodes.size() - 2];
        merged_node->right = nodes[nodes.size() - 1];

        nodes.pop_back();
        nodes.pop_back();

        nodes.push_back(merged_node);
    }

    return nodes[0];
}

// Коды 
void Codes_Generation(Node* root, string code, map<char, string> &codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '#') {
        codes[root->data] = code;
    }

    Codes_Generation(root->left, code + "0", codes);
    Codes_Generation(root->right, code + "1", codes);
}

// Таблица кодов
void Print_Table_of_Codes(const map<char, string> &codes) {
    cout << "Code Table:" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Кодируем код
string Fano_Encode(const string &text, const map<char, string> &codes) {
    string encoded_text = "";

    for (char c : text) {
        encoded_text += codes.at(c);
    }

    return encoded_text;
}
// Декодируем код
string Fano_Decode(Node* root, const string &encoded_text) {
    string decodedText = "";

    Node* current = root;

    for (char bit : encoded_text) {
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
    string alphabet = "МОПГСЩмопгсщ 0123456789^.";
    double encoding_price, compression_ratio;
    int n = 10000;

    string orig_text;
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        orig_text += alphabet[rand() % alphabet.size()];
    }

    string file_name = "txt/Original.txt";
    Generate_File(file_name, orig_text);

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

    Node* root = Build_Tree(nodes);

    // Генерация кодов для символов
    map<char, string> codes;
    Codes_Generation(root, "", codes);

    // Печать таблицы кода
    cout << endl;
    Print_Table_of_Codes(codes);

    // 1 (Fano)

    cout << "\nFANO:" << endl;

    string fano = Fano_Encode(orig_text, codes);
    file_name = "txt/Solo_Fano_Encode.txt";
    Generate_File(file_name, fano);

    string fano_de = Fano_Decode(root, fano);
    file_name = "txt/Solo_Fano_Decoded.txt";
    Generate_File(file_name, fano_de);

    if (orig_text == fano_de) {
        cout << "FANO Success" << endl;
        // Расчет цены кодирования
        encoding_price = static_cast<double>(fano.size()) / orig_text.size();
        cout << "Encoding Price: " << encoding_price << endl;
        // Расчет коэффициента сжатия
        compression_ratio = static_cast<double>(orig_text.size()) / (fano.size()/8);
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else {
        cout << "FANO Failed" << endl;
    }

    // 2 (RLE)
    
    cout << "\nRLE:" << endl;

    string rle = RLE_Encode(orig_text);
    file_name = "txt/Solo_RLE_Encode.txt";
    Generate_File(file_name, rle);

    string rle_de = RLE_Decode(rle);
    file_name = "txt/Solo_RLE_Decoded.txt";
    Generate_File(file_name, rle_de);

    if (orig_text == rle_de) {
        cout << "RLE Success" << endl;
        // Расчет коэффициента сжатия
        compression_ratio = static_cast<double>(orig_text.size()) / rle.size();
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else {
        cout << "RLE Failed" << endl;
    }

    // 3

    // RLE+Fano

    cout << "\nRLE+FANO:" << endl;

    string rle_encoded = RLE_Encode(orig_text);
    file_name = "txt/R_F_RLE_Encode.txt";
    Generate_File(file_name, rle_encoded);

    string fano_rle_encoded = Fano_Encode(rle_encoded, codes);
    file_name = "txt/R_F_full_Encode.txt";
    Generate_File(file_name, fano_rle_encoded);

    string fano_decoded = Fano_Decode(root, fano_rle_encoded);
    string fano_rle_decoded = RLE_Decode(fano_decoded);
    file_name = "txt/RLE_FANO_Decoded.txt";
    Generate_File(file_name, fano_rle_decoded);

    if (orig_text == fano_rle_decoded) {
        cout << "RLE+FANO Success" << endl;
        // Расчет коэффициента сжатия
        compression_ratio = static_cast<double>(orig_text.size()) / fano_rle_encoded.size();
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else {
        cout << "RLE+FANO Failed" << endl;
    }

    // Fano+RLE

    cout << "\nFANO+RLE:" << endl;

    string fano_encoded = Fano_Encode(orig_text, codes);
    file_name = "txt/F_R_Fano_Encode.txt";
    Generate_File(file_name, fano_encoded);

    string rle_fano_encoded = RLE_Encode(fano_encoded);
    file_name = "txt/F_R_full_Encode.txt";
    Generate_File(file_name, rle_fano_encoded);

    string rle_decoded = RLE_Decode(rle_fano_encoded);
    string rle_fano_decoded = Fano_Decode(root, fano_encoded);
    file_name = "txt/FANO_RLE_Decoded.txt";
    Generate_File(file_name, rle_fano_decoded);

    if (orig_text == rle_fano_decoded) {
        cout << "FANO+RLE Success" << endl;
        // Расчет коэффициента сжатия
        compression_ratio = static_cast<double>(orig_text.size()) / rle_fano_encoded.size();
        cout << "Compression Ratio: " << compression_ratio << endl;
    }
    else {
        cout << "FANO+RLE Failed" << endl;
    }

    cout << endl;

    return 0;
}