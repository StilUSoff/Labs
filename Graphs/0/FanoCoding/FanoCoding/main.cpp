#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


/*
 Объявляется структура Node, которая представляет узел дерева. В ней содержатся данные узла (символ), частота встречаемости символа, а также указатели на левый и правый дочерние узлы.
 Создается функция compareNodes, которая будет использоваться для сортировки узлов по убыванию их частоты вектора nodes.
 Создается функция buildHuffmanTree, которая принимает вектор узлов и строит дерево Хаффмана. В цикле выполняется сортировка узлов, затем создается новый узел, объединяющий два узла с наименьшей частотой. Узлы удаляются из вектора и добавляется объединенный узел. Функция возвращает корень дерева Хаффмана.
 Создается функция generateCodes, которая на основе дерева Хаффмана и строки кода генерирует коды для каждого символа. Если узел не является объединенным узлом, то для символа создается код в map codes. Рекурсивно вызывается функция для левого и правого поддерева.
 Создается функция printCodeTable, которая выводит на экран таблицу кодов для каждого символа из map codes.
 Создается функция encodeText, которая на основе текста и таблицы кодов codes возвращает закодированный текст.
 Создается функция decodeText, которая на основе корня дерева и закодированного текста возвращает декодированный текст.
 В функции main задается алфавит символов и пустая строка text.
 Генерируется случайный текст, состоящий из символов алфавита.
 Создается map frequencies, в котором для каждого символа из текста подсчитывается его частота встречаемости.
 Создается вектор узлов nodes, в котором каждому символу из frequencies соответствует узел с данными символа и его частотой.
 Вызывается функция buildHuffmanTree для построения дерева Хаффмана на основе вектора узлов nodes. Результат сохраняется в переменную root.
 Создается map codes, в котором для каждого символа из дерева Хаффмана генерируется его код при помощи функции generateCodes.
 Вызывается функция printCodeTable для вывода на экран таблицы кодов codes.
 Вызывается функция encodeText для кодирования текста при помощи таблицы кодов codes. Результат сохраняется в переменную encodedText.
 Вызывается функция decodeText для декодирования закодированного текста при помощи корня дерева. Результат сохраняется в переменную decodedText.
 Выводятся на экран исходный текст, закодированный текст и декодированный текст для проверки корректности работы алгоритма.
 Расчитывается цена кодирования (стоимость записи одного символа закодированного текста). Для этого длина закодированного текста делится на длину исходного текста.
 Расчитывается коэффициент сжатия. Для этого длина исходного текста делится на длину закодированного текста.
 Проверяется, совпадает ли исходный текст с декодированным текстом. Если да, то выводится сообщение "Оно работает!", иначе выводится сообщение "Эх.. что-то пошло не так(".
 Удаляется дерево для освобождения памяти */


using namespace std;


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
// Коды
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
// Таблица кодов
void printCodeTable(const map<char, string>& codes) {
    cout << "Табличка кодов:" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}
// Кодируем код
string encodeText(const string& text, const map<char, string>& codes) {
    string encodedText = "";

    for (char c : text) {
        encodedText += codes.at(c);
    }

    return encodedText;
}
// Декодируем код
string decodeText(Node* root, const string& encodedText) {
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

int main() {
    setlocale(LC_ALL, "ru");
    string alphabet = "kemsyarKEMSYAR 123456789[.";
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

    // Кодирование текста
    string encodedText = encodeText(text, codes);

    // Декодирование текста
    string decodedText = decodeText(root, encodedText);

    // Печать результатов
    cout << "\n Сам текст: " << text << endl;
    cout << "Закодированный текст: " << encodedText << endl;
    cout << "Декодированный текст: " << decodedText << endl;

    // Расчет цены кодирования
    double encodingPrice = static_cast<double>(encodedText.size()) / text.size();
    cout << "Цена кодированмя: " << encodingPrice << endl;

    // Расчет коэффициента сжатия
    double compressionRatio = static_cast<double>(text.size()) / encodedText.size();
    cout << "Коэфф. сжатия: " << compressionRatio << endl;


    // Проверка
    if (text == decodedText) {
        cout << "Оно работает!" << endl;
    }
    else {
        cout << "Эх.. что-то пошло не так(" << endl;
    }

    // Очистка памяти
    delete root;

    return 0;
}

