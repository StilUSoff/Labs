#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cstdio>
#include<map>

using namespace std;

// Функция для генерации случайного символа из алфавита
char getRandomChar() {
    string alphabet = "NnOoPpRrSsTt 0123456789$."; //НнОоПпРрСсТт
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

vector<int> encodeLZW(const string& text) {
    vector<int> encoded;
    map<string, int> dictionary;
    int dictSize = 256;
    string current;
    for (char c : text) {
        string temp = current + c;
        if (dictionary.count(temp)) {
            current = temp;
        } else {
            encoded.push_back(dictionary[current]);
            dictionary[temp] = dictSize++;
            current = string(1, c);
        }
    }
    if (!current.empty()) {
        encoded.push_back(dictionary[current]);
    }
    return encoded;
}

string decodeLZW(const vector<int>& encoded) {
    if (encoded.empty()) return "";

    string decoded;
    map<int, string> dictionary;
    int dictSize = 256;
    for (int i = 0; i < dictSize; ++i) {
        dictionary[i] = string(1, i);
    }

    int prevCode = encoded[0];
    string entry = dictionary[prevCode];
    decoded += entry;
    for (size_t i = 1; i < encoded.size(); ++i) {
        int code = encoded[i];
        if (dictionary.find(code) != dictionary.end()) {
            entry = dictionary[code];
        } else if (code == dictSize) {
            entry = dictionary[prevCode] + dictionary[prevCode][0];
        } else {
            throw "Error in decoding with LZW algorithm: Invalid code.";
        }
        decoded += entry;
        if (dictSize < 4096) { // Limit the size of the dictionary
            dictionary[dictSize++] = dictionary[prevCode] + entry[0];
        }
        prevCode = code;
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
        if (!isdigit(encoded[i])) {
            return "Error in decoding with RLE algorithm: Invalid input format.";
        }
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

    // Calculating encoding cost

    ofstream dictionaryFile("textfile.txt");
    if (!dictionaryFile.is_open()) {
        cerr << "Failed to open file for encoding dictionary." << endl;
        return 1; // Return non-zero code to indicate error
    }
    dictionaryFile << originalText << endl;
    
    vector<int> encodedText = encodeLZW(originalText);

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









    cout << endl;
    cout << endl;
    cout << "ORIGINAL: " << originalText.substr(0, 30) << endl;
    cout << endl;
    cout << endl;
    cout << "DECODED: " << decodedTextLZW.substr(0, 30) << endl;
    cout << endl;
    cout << endl;







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
    vector<int> encodedTextLZW = encodeLZW(originalText);

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
    vector<int> encodedTextRLE_LZW_LZW = encodeLZW(encodedTextRLE_LZW);

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
    if (remove("textfile.txt") != 0) {
        cerr << "Error deleting the file." << endl;
    } else {
        cout << "File dictionary.txt deleted successfully." << endl;
    }

    dictionaryFile.close();

    return 0;
}