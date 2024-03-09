#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string generateRandomText(const string& alphabet, int length) {
    string randomText;
    int alphabetSize = alphabet.size();

    srand(time(NULL));

    for (int i = 0; i < length; ++i) {
        randomText += alphabet[rand() % alphabetSize];
    }

    return randomText;
}

string runLengthEncode(const string& text) {
    string encodedText;

    int count = 1;
    for (size_t i = 1; i <= text.size(); ++i) {
        if (i == text.size() || text[i] != text[i - 1]) {
            encodedText += text[i - 1];
            encodedText += to_string(count);
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

    for (size_t i = 0; i < encodedText.size(); i += 2) {
        char character = encodedText[i];
        int count = encodedText[i + 1] - '0';

        for (int j = 0; j < count; ++j) {
            decodedText += character;
        }
    }

    return decodedText;
}

int main() {
    setlocale(LC_ALL, "ru");
    string alphabet = "kemsyarKEMSYAR 123456789[.";
    int textLength = 10000;

    // Генерация случайного текста
    string originalText = generateRandomText(alphabet, textLength);

    // Запись случайного текста в файл
    ofstream file("random_text.txt");
    if (file.is_open()) {
        file << originalText;
        file.close();
    }
    else {
        cout << "Unable to open file for writing." << endl;
        return 1;
    }

    // Чтение текста из файла
    ifstream readFile("random_text.txt");
    string readText;
    if (readFile.is_open()) {
        char c;
        while (readFile.get(c)) {
            readText += c;
        }
        readFile.close();
    }
    else {
        cout << "Unable to open file for reading." << endl;
        return 1;
    }

    // Вывод оригинального текста
    cout << "Original Text: " << originalText << endl;

    // Кодирование текста алгоритмом RLE
    string encodedText = runLengthEncode(readText);

    // Вывод закодированного текста
    cout << "\nEncoded Text: " << encodedText << endl;

    // Декодирование текста
    string decodedText = runLengthDecode(encodedText);

    // Вывод декодированного текста
    cout << "\nDecoded Text: " << decodedText << endl;

    // Проверка корректности декодирования
    if (decodedText == readText) {
        cout << "\nСработало!" << endl;
    }
    else {
        cout << "\nНе сработало(" << endl;
    }

    // Расчет коэффициента сжатия
    double compressionRatio = static_cast<double>(encodedText.size()) / readText.size();
    cout << "Коэффициент сжатия: " << compressionRatio << endl;

    // Расчет цены кодирования
    //double encodingPrice = static_cast<double>(readText.size()) / encodedText.size();
    //cout << "Цена кодированмя: " << encodingPrice << endl; // po form izmenit


    return 0;
}
