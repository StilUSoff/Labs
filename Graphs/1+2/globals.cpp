#include "globals.h"


double LaplacePDF(double x, double a, double b) {
    return 0.5 * a * exp(-1 * a * abs(x - b));
}


int LaplaceD() {
    random_device rd;
       mt19937 mersenne(rd());

        const double a = 10.0; // Параметр a для распределения Лапласа
        const double b = 6.0; // Параметр b для распределения Лапласа

        std::uniform_real_distribution<double> dist(0, 1);
        double u = dist(mersenne); // Генерируем u из равномерного распределения на [0, 1]
        //Если u равно 0, тогда 1 - u равно 1, и log(2 * (1 - u)) равно 0. Таким образом, x будет равно b, и это соответствует максимальной вероятности для значения x в      распределении Лапласа.
        //Если u равно 1, тогда 1 - u равно 0, и log(2 * (1 - u)) стремится к минус бесконечности. Таким образом, x будет стремиться к бесконечности отрицательной стороны,   что также соответствует распределению Лапласа.
        //Целая часть x: После того, как мы вычислили значение x, мы возвращаем его целую часть, так как в исходной функции указано, что результат должен быть целым числом.
        // то есть u определяет, какое конкретное значение из Лапласа будет выбрано для возврата
        // Используем обратное преобразование для генерации случайного числа
        double x;
        if (u < 0.5)
            x = b + a * log(2 * u);
        else
            x = b - a * log(2 * (1 - u));

        return static_cast<int>(x); // Возвращаем целую часть
}

// Общее для матрицы :
void PrintMatrix(const vector<vector<int> > mx) {
    int n = mx.size();
    int m = mx[0].size();
    cout << "   |";
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i + 1 << "|";
    }
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i+1 << "|";
        for (int j = 0; j < m; j++) {
            if(mx[i][j] != INF)
                cout << setw(3) << mx[i][j] << " ";
            else
                cout << setw(3) << "inf" << " ";
        }
        cout << '\n';
    }
}

vector<vector<int> > BMultMatrixs(const vector<vector<int> > fMx, const vector<vector<int> > sMx) {
    vector<vector<int> > res(fMx.size(), vector<int>(fMx.size(), 0));
    vector<int> buf;
    for (int i = 0; i < fMx.size(); i++) {
        for (int j = 0; j < fMx.size(); j++) {
            buf.clear();
            for (int k = 0; k < fMx.size(); k++) {
                buf.push_back(fMx[i][k] && sMx[k][j]);
            }
            res[i][j] = *std::max_element(buf.begin(), buf.end());
        }
    }
    return res;
}

vector<vector<int> > AddMatrixs(const vector<vector<int> > fMx, const vector<vector<int> > sMx) {
    vector<vector<int> > res(fMx.size(), vector<int>(fMx.size(), 0));
    for (int i = 0; i < fMx.size(); i++) {
        for (int j = 0; j < fMx.size(); j++) {
            res[i][j] = fMx[i][j] + sMx[i][j];
        }
    }
    return res;
}

// Main:
int InputVertexCount() {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Введите число вершин графа от " << MIN_NUM_of_VERT << " до " << MAX_NUM_of_VERT << ":\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= MIN_NUM_of_VERT && res <= MAX_NUM_of_VERT) {
                flagInp = true;
            }
            else {
                cout << "Ошибочка!" << endl;
                flagInp = false;
            }
        }
        else {
            cout << "Ошибочка!" << endl;
            flagInp = false;
        }
    } while (!flagInp);
    cout << '\n';
    return res;
}

void PrintMenu() {
    for (int i = 0; i < 10; i++) {
        cout << MenuItems[i] << " [" << i << "]" << endl;
    }
}

char InputMenuItem() {
    string strInp;
    bool flagInp;
    char res;
    do {
        cout << "Выберите пункт меню нажав нужную цифру:\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 0 && res < 10 /*Если будет ошибка ввода в меню !!!!!!!!!!!!*/ ) {
                flagInp = true;
            }
            else {
                cout << "Ошибочка! Введите цифру из того что есть в меню" << endl;
                flagInp = false;
            }
        }
        else {
            cout << "Ошибочка!" << endl;
            flagInp = false;
        }
    } while (!flagInp);
    cout << '\n';
    return res;
}

bool IsContinue(char& d) {
    string strInp;
    bool isOk = false;
    do {
        cout << "Продолжаем? (Y/N): ";
        getline(cin, strInp);
        if (regex_match(strInp, kRxYn)) {
            isOk = true;
            d = strInp[0];
            switch (d) {
            case 'Y':
            case 'y':
                return true;
            case 'N':
            case 'n':
                return false;
            }
        }
        else {
            isOk = false;
            cout << "Ошибочка! Вводите y/Y либо n/N! \n";
        }
    } while (!isOk);
    return d;
}


