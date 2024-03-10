#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>

const unsigned short file_size = 10000;
const short bitsSize = 16;

// Function declarations
void generateFile(const std::vector<std::string>& init_dict, const std::string& file_name);
void LZW_encoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name);
void LZW_decoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name);
void RLE_encoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name);
void RLE_decoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name);
int getIndex(const std::vector<std::string>& dictionary, const std::string& str);
int getNumFromBinStr(std::string binary_string);
int nearestPower2(int x);
std::vector<bool> binaryRepresentation(int num, int dict_size);
std::string binaryRepresentationStr(int num, int dict_size);
bool compareFiles(const std::string& file1_name, const std::string& file2_name);
int numberOfCharacters(const std::string& file_name);

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    std::vector<std::string> bin_dict = { "0", "1" };
    // std::vector<std::string> dict = { "Н", "О", "П", "Р", "С", "Т", "н", "о", "п", "р", "с", "т",
    //                                    " ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "$", "." };

    std::vector<std::string> dict = { "N", "O", "P", "R", "S", "T", "n", "o", "p", "r", "s", "t",
                                       " ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "$", "." };

    std::string file_name = "txt/orig.txt";
    generateFile(dict, file_name);

    LZW_encoder(dict, file_name, "txt/LZW_coded.txt");
    LZW_decoder(dict, "txt/LZW_coded.txt", "txt/LZW_decoded.txt");

    RLE_encoder(dict, file_name, "txt/RLE_coded.txt");
    RLE_decoder(dict, "txt/RLE_coded.txt", "txt/RLE_decoded.txt");

    // сравнение исходного файла и декодированных
    std::cout << "LZW decoding was " << (compareFiles(file_name, "txt/LZW_decoded.txt") ? "correct" : "incorrect");
    std::cout << "\nRLE decoding was " << (compareFiles(file_name, "txt/RLE_decoded.txt") ? "correct" : "incorrect");

    // коэффициенты сжатия
    std::cout << "\n\nLZW compression ratio: " << float(file_size) / (numberOfCharacters("txt/LZW_coded.txt") / 8) << std::endl;
    std::cout << "RLE compression ratio: " << float(file_size) / (numberOfCharacters("txt/RLE_coded.txt") / 8) << std::endl;

    // двухступенчатое кодирование и сравнение с исходным файлом
    LZW_encoder(bin_dict, "txt/RLE_coded.txt", "txt/RLE_LZW_coded.txt");
    LZW_decoder(bin_dict, "txt/RLE_LZW_coded.txt", "txt/RLE_coded_LZW_decoded.txt");
    RLE_decoder(dict, "txt/RLE_coded_LZW_decoded.txt", "txt/RLE_LZW_decoded.txt");
    std::cout << "\nRLE_LZW decoding was " << (compareFiles(file_name, "txt/RLE_LZW_decoded.txt") ? "correct" : "incorrect");

    RLE_encoder(bin_dict, "txt/LZW_coded.txt", "txt/LZW_RLE_coded.txt");
    RLE_decoder(bin_dict, "txt/LZW_RLE_coded.txt", "txt/LZW_coded_RLE_decoded.txt");
    LZW_decoder(dict, "txt/LZW_coded_RLE_decoded.txt", "txt/LZW_RLE_decoded.txt");
    std::cout << "\nLZW_RLE decoding was " << (compareFiles(file_name, "txt/LZW_RLE_decoded.txt") ? "correct" : "incorrect");

    std::cout << "\n\nRLE_LZW compression ratio: " << float(file_size) / (numberOfCharacters("txt/RLE_LZW_coded.txt") / 8) << std::endl;
    std::cout << "LZW_RLE compression ratio: " << float(file_size) / (numberOfCharacters("txt/LZW_RLE_coded.txt") / 8) << std::endl;

    std::cout << "\n\nFinish";

    return 0;
}

// Function definitions

// генерация файла на основе алфавита
void generateFile(const std::vector<std::string>& init_dict, const std::string& file_name) {
    std::ofstream file;
    file.open(file_name);
    int alphabet_size = init_dict.size();
    for (int i = 0; i < file_size; i++) {
        file << init_dict[rand() % alphabet_size];
    }
    file.close();
}

void LZW_encoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name) {
	std::ifstream fin;
	std::ofstream fout;

	fin.open(fin_name);
	fout.open(fout_name);

	std::vector<std::string> dictionary(init_dict);
	
	char symbol;
	std::string str = "";
	// посимвольное считывание файла
	while (fin >> std::noskipws >> symbol) {
		str += symbol;
		
		// поиск строки в словаре
		if (std::find(dictionary.begin(), dictionary.end(), str) == dictionary.end()) {
			// not found
			char eChar = str[str.size() - 1];
			str.pop_back();

			// отправка в поток
			std::vector<bool> tmp_code = binaryRepresentation(getIndex(dictionary, str), dictionary.size());
			for (int i = 0; i < tmp_code.size(); i++) {
				fout << tmp_code[i];
			}

			// добавление строки в словарь
			str.push_back(eChar);
			dictionary.push_back(str);
			
			// следующая строка начинается с последнего символа новой для словаря строки
			str = eChar;
		}
	}
	
	// отправка в поток последнего символа
	std::vector<bool> tmp_code = binaryRepresentation(getIndex(dictionary, str), dictionary.size());
	for (int i = 0; i < tmp_code.size(); i++) {
		fout << tmp_code[i];
	}

	fin.close();
	fout.close();
}

void LZW_decoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name) {
	std::ifstream fin;
	std::ofstream fout;

	fin.open(fin_name);
	fout.open(fout_name);

	bool first_sym = 1;
	bool flag = 1;
	std::vector<std::string> dictionary(init_dict);
	std::string str = "";
	char buff[50];
	while (!fin.eof()) {
		flag = 1;
		// считываем x бит из файла
		if (dictionary.size() == 2 and first_sym) {
			fin.get(buff, 2);
			first_sym = 0;
		}
		else {
			fin.get(buff, nearestPower2(dictionary.size() + 1) + 1);
		}
		
		std::string binary_string(buff);
		if (binary_string == "") break;
		std::string tmp; 

        // если строки ещё нет в словаре, то дополняем её самостоятельно (ссылка на объяснение)
		// http://vmath.ru/vf5/codes/lzw#dekodirovanie:~:text=%D0%9F-,%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80,-.%20%D0%97%D
		if (getNumFromBinStr(binary_string) == dictionary.size())
			tmp = str + str[0];
		else
			tmp = dictionary[getNumFromBinStr(binary_string)];

		// проход по всем символам считанной строки
		for (int i = 0; i < tmp.size(); i++) {
			str += tmp[i];
			// поиск строки в словаре
			if (std::find(dictionary.begin(), dictionary.end(), str) == dictionary.end() and flag) {
				// not found

				char eChar = str[str.size() - 1];
				str.pop_back();

				// отправка в поток
				fout << str;

				// добавление строки в словарь
				str.push_back(eChar);
				dictionary.push_back(str);

				// следующая строка начинается с невошедших символов tmp
				str = tmp.substr(i, tmp.size() - i); //tmp.size() - i символов начиная с i-го 
				flag = false;
			}
			if (!flag) break;
		}
	}
	
	// отправка в поток последнего символа
	fout << str;

	fin.close();
	fout.close();
}

void RLE_encoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name) {
	std::ifstream fin;
	std::ofstream fout;

	fin.open(fin_name);
	fout.open(fout_name);

	std::string different = "";
	char prev;
	char next;
	int count = 1;
	fin >> std::noskipws >> prev;
	// посимвольное считывание файла
	while (fin >> std::noskipws >> next) {
		if (next == prev) {
			count++;

			if (different != "") { 
				fout << "0" << binaryRepresentationStr(different.size(), pow(2, bitsSize - 1));
				for (int i = 0; i < different.size(); i++) {
					fout << binaryRepresentationStr(getIndex(init_dict, std::string(1, different[i])), init_dict.size());
				}
				different = "";
			}
		}
		else {
			
			if (count == 1) {
				different += prev;
			}
			else {
				fout << "1" << binaryRepresentationStr(count, pow(2, bitsSize - 1))
					<< binaryRepresentationStr(getIndex(init_dict, std::string(1, prev)), init_dict.size());
			}

			count = 1;
			prev = next;
		}
	}

	if (different == "") {
		fout << "1" << binaryRepresentationStr(count, pow(2, bitsSize - 1))
			<< binaryRepresentationStr(getIndex(init_dict, std::string(1, prev)), init_dict.size());
	}
	else {
		different += prev;
		fout << "0" << binaryRepresentationStr(different.size(), pow(2, bitsSize - 1));
		for (int i = 0; i < different.size(); i++) {
			fout << binaryRepresentationStr(getIndex(init_dict, std::string(1, different[i])), init_dict.size());
		}
	}
	
	fin.close();
	fout.close();
}

void RLE_decoder(const std::vector<std::string>& init_dict, const std::string& fin_name, const std::string& fout_name) {
	std::ifstream fin;
	std::ofstream fout;


	fin.open(fin_name);
	fout.open(fout_name);

	char buff[50];
	while (!fin.eof()) {
		fin.get(buff, bitsSize + 1);
		std::string binary_string(buff);
		if (binary_string == "") break;
		
		if (binary_string[0] == '1') {
			int num = 0;
			num = getNumFromBinStr(binary_string.substr(1, binary_string.size() - 1));

			fin.get(buff, nearestPower2(init_dict.size()) + 1);
			binary_string = buff;
			for (int i = 0; i < num; i++) {
				fout << init_dict[getNumFromBinStr(binary_string)];
			}
		}
		else {
			int num = 0;
			num = getNumFromBinStr(binary_string);

			for (int i = 0; i < num; i++) {
				fin.get(buff, nearestPower2(init_dict.size()) + 1);
				binary_string = buff;
				fout << init_dict[getNumFromBinStr(binary_string)];
			}
		}

	}

	fin.close();
	fout.close();
}

// индекс элемента в векторе
int getIndex(const std::vector<std::string>& dictionary, const std::string& str) {
	auto it = std::find(dictionary.begin(), dictionary.end(), str);
	if (it != dictionary.end()) {
		int ind = std::distance(dictionary.begin(), it);
		return ind;
	}
	else {
		std::cout << "\n Element " << str << " not found in vector" << std::endl;
        return 0;
	}
}

// число в 10-чной СС, полученное из его двоичного представления 
int getNumFromBinStr(std::string binary_string) {
	std::reverse(binary_string.begin(), binary_string.end());
	int decimal_number = 0;
	int base = 2;

	for (int i = 0; i < binary_string.size(); i++) {
		if (binary_string[i] == '1') {
			decimal_number += pow(base, i);
		}
	}
	return decimal_number;
}

// Ищет и возвращает ближайшую к x сверху степень двойки
int nearestPower2(int x) {
	int result = 0;
	int i = 1;
	while (i < x) {
		result++;
		i *= 2;
	}
	return result;
}

// бинарное представление числа с разрядностью x, где 2^x >= dict_size
std::vector<bool> binaryRepresentation(int num, int dict_size) {
	std::vector<bool> code(nearestPower2(dict_size));
	int i = 0;
	while (num > 0) {
		code[code.size() - 1 - i] = num % 2;
		num /= 2;
		i++;
	}

	return code;
}

std::string binaryRepresentationStr(int num, int dict_size) {
	std::vector<bool> code(nearestPower2(dict_size));
	int i = 0;
	while (num > 0) {
		code[code.size() - 1 - i] = num % 2;
		num /= 2;
		i++;
	}

	std::string result;
	for (int i = 0; i < code.size(); i++) {
		result += code[i] ? "1" : "0";
	}

	return result;
}

bool compareFiles(const std::string& file1_name, const std::string& file2_name) {
	std::ifstream file1(file1_name);
	std::ifstream file2(file2_name);

	const int buff_size = 500;
	char buff[buff_size];
	while (!file1.eof() and !file2.eof()) {
		file1.get(buff, buff_size);
		std::string line1(buff);

		file2.get(buff, buff_size);
		std::string line2(buff);

		if (line1 != line2) {
			return false;
		}
	}

	return !(file1.eof() != file2.eof());
}

int numberOfCharacters(const std::string& file_name) {
	std::ifstream fin;
	fin.open(file_name);

	char symbol;
	int result = 0;
	// посимвольное считывание файла
	while (fin >> std::noskipws >> symbol) {
		result++;
	}

	fin.close();
	return result;
}