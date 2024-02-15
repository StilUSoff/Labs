#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cstdio> // Для функции remove

using namespace std;

// Функция для генерации случайного символа из алфавита
char getRandomChar() {
    string alphabet = "НнОоПпРрСсТт 0123456789$.";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, alphabet.size() - 1);
    return alphabet[dis(gen)];
}

// Function to generate random text
string generateRandomText(int length) {
    string text;
    text.reserve(length);
    for (int i = 0; i < length; ++i) {
        text += getRandomChar();
    }
    return text;
}

// Function to encode text using the LZW algorithm
vector<int> encodeLZW(const string& text, ofstream& dictionaryFile) {
    vector<int> encoded;
    vector<string> dictionary;
    string current;
    for (char c : text) {
        string temp = current + c;
        auto it = find(dictionary.begin(), dictionary.end(), temp);
        if (it != dictionary.end()) {
            current = temp;
        } else {
            encoded.push_back(find(dictionary.begin(), dictionary.end(), current) - dictionary.begin());
            dictionary.push_back(temp);
            current = string(1, c);
            // Save value to file
            dictionaryFile << current << endl;
        }
    }
    if (!current.empty()) {
        encoded.push_back(find(dictionary.begin(), dictionary.end(), current) - dictionary.begin());
    }
    return encoded;
}

// Function to decode text using the LZW algorithm
string decodeLZW(const vector<int>& encoded) {
    if (encoded.empty())
        return "";

    string decoded;
    vector<string> dictionary;
    string lastEntry;
    for (int index : encoded) {
        if (index >= dictionary.size()) {
            return "Error in decoding with LZW algorithm.";
        }
        string entry = dictionary[index];
        decoded += entry;
        if (!lastEntry.empty()) {
            dictionary.push_back(lastEntry + entry[0]);
        }
        lastEntry = entry;
    }
    return decoded;
}

// Function to encode text using the RLE algorithm
string encodeRLE(const string& text) {
    string encoded;
    int count = 1;
    for (size_t i = 1; i <= text.size(); ++i) {
        if (i == text.size() || text[i] != text[i - 1]) {
            encoded += to_string(count) + text[i - 1];
            count = 1;
        } else {
            ++count;
        }
    }
    return encoded;
}

// Function to decode text using the RLE algorithm
string decodeRLE(const string& encoded) {
    string decoded;
    for (size_t i = 0; i < encoded.size(); i += 2) {
        int count = encoded[i] - '0';
        char c = encoded[i + 1];
        decoded.append(count, c);
    }
    return decoded;
}

int main() {
    // Generating random text
    int textLength = 10000;
    string originalText = generateRandomText(textLength);

    // (a) Encoding text with the LZW algorithm
    ofstream dictionaryFile("dictionary.txt");
    if (!dictionaryFile.is_open()) {
        cerr << "Failed to open file for encoding dictionary." << endl;
        return 1; // Return non-zero code to indicate error
    }
    vector<int> encodedText = encodeLZW(originalText, dictionaryFile);
    dictionaryFile.close();

    // Calculating encoding cost
    int originalSize = originalText.size() * 8; // Number of bits in original text
    int encodedSize = encodedText.size() * 12; // Assuming each LZW code takes 12 bits
    double compressionRateLZW = (double)encodedSize / originalSize;
    cout << "(a) Encoding cost with LZW algorithm: " << compressionRateLZW << endl;

    // Decoding text with the LZW algorithm
    string decodedTextLZW = decodeLZW(encodedText);

    // Checking if decoding was successful
    if (originalText == decodedTextLZW) {
        cout << "Decoding with LZW algorithm was successful." << endl;
    } else {
        cout << "Error in decoding with LZW algorithm." << endl;
    }

    // Calculating LZW compression ratio
    compressionRateLZW = (double)originalSize / encodedSize;
    cout << "(a) Compression ratio with LZW algorithm: " << compressionRateLZW << endl;

    // (b) Encoding text with the RLE algorithm
    string encodedTextRLE = encodeRLE(originalText);

    // Calculating RLE compression ratio
    double compressionRateRLE = (double)encodedTextRLE.size() * 8 / originalSize;
    cout << "(b) Compression ratio with RLE algorithm: " << compressionRateRLE << endl;

    // Decoding text with the RLE algorithm
    string decodedTextRLE = decodeRLE(encodedTextRLE);

    // Checking if decoding was successful
    if (originalText == decodedTextRLE) {
        cout << "Decoding with RLE algorithm was successful." << endl;
    } else {
        cout << "Error in decoding with RLE algorithm." << endl;
    }

    // (c) Comparing the efficiency of LZW + RLE and RLE + LZW encoding
    // Encoding text with the LZW algorithm followed by RLE
    ofstream dictionaryFile2("dictionary.txt");
    if (!dictionaryFile2.is_open()) {
        cerr << "Failed to open file for encoding dictionary." << endl;
        return 1; // Return non-zero code to indicate error
    }
    vector<int> encodedTextLZW = encodeLZW(originalText, dictionaryFile2);
    dictionaryFile2.close();
    string encodedTextLZW_RLE = encodeRLE(decodeLZW(encodedTextLZW));

    // Checking if decoding was successful
    string decodedTextLZW_RLE = decodeRLE(encodedTextLZW_RLE);
    if (originalText == decodedTextLZW_RLE) {
        cout << "Decoding with LZW + RLE algorithm was successful." << endl;
    } else {
        cout << "Error in decoding with LZW + RLE algorithm." << endl;
    }

    // LZW + RLE compression ratio
    int encodedSizeLZW_RLE = encodedTextLZW_RLE.size() * 8; // Assuming each symbol-count pair in RLE is encoded in 8 bits
    double compressionRateLZW_RLE = (double)encodedSizeLZW_RLE / originalSize;

    // Encoding text with RLE followed by LZW
    string encodedTextRLE_LZW = encodeRLE(originalText);
    vector<int> encodedTextRLE_LZW_LZW = encodeLZW(encodedTextRLE_LZW, dictionaryFile);

    // Checking if decoding was successful
    string decodedTextRLE_LZW = decodeLZW(encodedTextRLE_LZW_LZW);
    string decodedTextRLE_LZW_RLE = decodeRLE(decodedTextRLE_LZW);
    if (originalText == decodedTextRLE_LZW_RLE) {
        cout << "Decoding with RLE + LZW algorithm was successful." << endl;
    } else {
        cout << "Error in decoding with RLE + LZW algorithm." << endl;
    }

    // RLE + LZW compression ratio
    int encodedSizeRLE_LZW = encodedTextRLE_LZW_LZW.size() * 12; // Assuming each LZW code takes 12 bits
    double compressionRateRLE_LZW = (double)encodedSizeRLE_LZW / originalSize;

    cout << "(c) Comparing encoding efficiency:" << endl;
    cout << "Compression ratio of LZW + RLE: " << compressionRateLZW_RLE << endl;
    cout << "Compression ratio of RLE + LZW: " << compressionRateRLE_LZW << endl;

    if (compressionRateLZW_RLE < compressionRateRLE_LZW) {
        cout << "LZW + RLE is more efficient." << endl;
    } else if (compressionRateLZW_RLE > compressionRateRLE_LZW) {
        cout << "RLE + LZW is more efficient." << endl;
    } else {
        cout << "Both methods have the same efficiency." << endl;
    }

    // Removing the file
    if (remove("dictionary.txt") != 0) {
        cerr << "Error deleting the file." << endl;
    } else {
        cout << "File dictionary.txt deleted successfully." << endl;
    }

    return 0;
}