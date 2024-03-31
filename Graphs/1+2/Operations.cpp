#include "Operations.h"
int InputEdgeCount(const MyGraph& graph) {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Введите кол-во ребер графа- \n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 1 && res <= graph.GetVertexCount() - 1) {
                flagInp = true;
            }
            else {
                cout << "Ошибочка( введите правильно!" << endl;
                flagInp = false;
            }
        }
        else {
            cout << "Ошибочка( введите правильно!!!" << endl;
            flagInp = false;
        }
    } while (!flagInp);
    cout << '\n';
    return res;
};
int InputShimbelMode() {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Желаемая матрица: матрица кратчайших путей [0], матрица длиннейших путей [1]\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 0 && res <= 1) {
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
};
int InputNumberOfVert(const MyGraph& graph){
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Введите номер вершины:\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 1 && res <= graph.GetVertexCount()) {
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
int InputStartVert(const MyGraph& graph) {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Введите исходную вершину:\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 1 && res <= graph.GetVertexCount()) {
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
int InputAlgorithmMode() {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "С какой матрицей работать (весов) ? [0] - с положительной. [1] - со смешанной.\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= 0 && res <= 1) {
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
};

int InputVertex(int f, int s) {
    string strInp;
    bool flagInp;
    int res;
    do {
        cout << "Введите число от " << f << " до " << s << ":\n";
        getline(cin, strInp);
        if (regex_match(strInp, kRxNumber)) {
            res = stoi(strInp);
            if (res >= f && res <= s) {
                flagInp = true;
            }
            else {
                cout << "Ошибочка" << endl;
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



void ShimbellMethod(const MyGraph& graph) {
    int edgesCnt = InputEdgeCount(graph);
    int ShimMode = InputShimbelMode();

    cout << "Матрица весов:\n";
    PrintMatrix(graph.GetWeightsMatrix(0));
    cout << '\n';
    cout << "Матрица Шиммбелла:\n";
    PrintMatrix(graph.CalcShimbell(edgesCnt, static_cast<ShimbellMode>(ShimMode)));
    cout << '\n';
}

void ReachabilityOperation(const MyGraph& graph) {
    // Нумерация с 1
    cout << "Вершина 1: ";
    int vert1 = InputNumberOfVert(graph);

    cout << "Вершина 2: ";
    int vert2 = InputNumberOfVert(graph);
    vector<vector<int> > MatrixReach = graph.GetReachMatrix();
    vert1--;
    vert2--;

    if (vert1 != vert2) {
        cout << "Матрица достижимости:\n";
        PrintMatrix(MatrixReach);
        cout << '\n';
        if (MatrixReach[vert1][vert2] != 0) {
            cout << "Есть " << MatrixReach[vert1][vert2] << " путей между этими вершинами!\n";
        }
        else {
            cout << "У этих вершин путей не существует!\n";
        }
    }
    else
        cout << "Попытка построить путь из " << vert1 + 1 << " в " << vert2 + 1 << "не удалась("<< endl;
    cout << '\n';
}

void DijkstraAlgorithm(const MyGraph& graph) {
    int decision = InputAlgorithmMode();
    if (decision == 0) {
        int inpVert = InputStartVert(graph), counter = 0;
        cout << '\n';
        inpVert--;

        cout << "Матрица весов:\n";
        PrintMatrix(graph.GetWeightsMatrix(0));
        cout << '\n';

        vector<int> distances = graph.Dijkstra(inpVert, counter);
        vector<vector<int> > paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(2));

        for (int i = 0; i < graph.GetVertexCount(); i++) {
            if (i != inpVert) {
                if (paths[i][0] != INF) {
                    for (int j = paths[i].size() - 1; j > 0; j--) {
                        cout << std::setw(2) << paths[i][j] + 1 << "--> ";
                    }
                    cout << std::setw(2) << paths[i][0] + 1;
                    cout << " это минимальный путь до вершины " << std::setw(2) << i + 1 << " длинною в " << std::setw(2) << distances[i];
                    cout << endl;
                }
                else {
                    cout << "До вершины " << std::setw(2) << i + 1 << " путя нет!\n";
                }
            }
        }
        cout << '\n';
        cout << " Кол-во итераций: " << counter << "\n\n";
    }
    else
        cout << "Алгоритм Дейкстры только с матрицей с положительными значениями!\n\n";
}

void BellmanFordAlgorithm(const MyGraph& graph) { 
    int decision = InputAlgorithmMode();
    if (decision == 1) {
        int inpVert = InputStartVert(graph), counter = 0;

        cout << '\n';
        inpVert--;

        cout << "Матрица весов:\n";
        PrintMatrix(graph.GetWeightsMatrix(1));
        cout << '\n';

        vector<int> distances = graph.BellmanFord(inpVert, counter, graph.GetWeightsMatrix(3));
        vector<vector<int> > paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(3));

        for (int i = 0; i < graph.GetVertexCount(); i++) {
            if (i != inpVert) {
                if (paths[i][0] != INF) {
                    for (int j = paths[i].size() - 1; j > 0; j--) {
                        cout << std::setw(2) << paths[i][j] + 1 << "--> ";
                    }
                    cout << std::setw(2) << paths[i][0] + 1;
                    cout << " Минимальный путь до вершины " << std::setw(2) << i + 1 << " длиною в " << std::setw(2) << distances[i];
                    cout << endl;
                }
                else {
                    cout << "До вершины" << std::setw(2) << i + 1 << " путя нет!\n";
                }
            }
        }
        cout << '\n';
        cout << " Количество итераций: " << counter << '\n';
        cout << '\n';
    }
    else {
        int inpVert = InputStartVert(graph), counter = 0;

        cout << '\n';
        inpVert--;

        cout << "Матрица весов:\n";
        PrintMatrix(graph.GetWeightsMatrix(0));
        cout << '\n';

        vector<int> distances = graph.BellmanFord(inpVert, counter, graph.GetWeightsMatrix(2));
        vector<vector<int> > paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(2));

        for (int i = 0; i < graph.GetVertexCount(); i++) {
            if (i != inpVert) {
                if (paths[i][0] != INF) {
                    for (int j = paths[i].size() - 1; j > 0; j--) {
                        cout << std::setw(2) << paths[i][j] + 1 << "--> ";
                    }
                    cout << std::setw(2) << paths[i][0] + 1;
                    cout << " это минимальный путь до вершины " << std::setw(2) << i + 1 << " длиною в " << std::setw(2) << distances[i];
                    cout << endl;
                }
                else {
                    cout << "До вершины " << std::setw(2) << i + 1 << " путя нет !\n";
                }
            }
        }
        cout << '\n';
        cout << " Количество итераций: " << counter << '\n';
        cout << '\n';
    }
}

//что бы восстонавить пути Флойда-Уоршалла улучшить алгоритм restore
void FloydWarshallAlgorithm(const MyGraph& graph) {
    int decision = InputAlgorithmMode();
    if (decision == 1) {
        int counter = 0;

        cout << "Матрица весов:\n";
        PrintMatrix(graph.GetWeightsMatrix(1));
        cout << '\n';

        vector<vector<int> > distancesMx = graph.FloydWarshall(counter, graph.GetWeightsMatrix(3));

        cout << "Матрица расстояний:\n";
        cout << "   |";
        for (int i = 0; i < graph.GetVertexCount(); i++) {
            cout << setw(3) << i + 1 << "|";
        }
        cout << endl;
        for (int i = 0; i < graph.GetVertexCount(); i++) {
            cout << setw(3) << i + 1 << "|";
            for (int j = 0; j < graph.GetVertexCount(); j++) {

                if (distancesMx[i][j] != INF) {
                    cout << std::setw(3) << distancesMx[i][j] << " ";
                }
                else {
                    cout << std::setw(3) << "inf" << " ";
                }
            }
            cout << '\n';
        }
        cout << '\n';

        cout << " Кол-во итераций: " << counter << '\n';
        cout << '\n';
    }
    else {
        int counter = 0;

        cout << "Матрица весов:\n";
        PrintMatrix(graph.GetWeightsMatrix(0));
        cout << '\n';

        vector<vector<int> > distancesMx = graph.FloydWarshall(counter, graph.GetWeightsMatrix(2));

        cout << "Матрица расстояний:\n";
        cout << "   |";
        for (int i = 0; i < graph.GetVertexCount(); i++) {
            cout << setw(3) << i + 1 << "|";
        }
        cout << endl;
        for (int i = 0; i < graph.GetVertexCount(); i++) {
            cout << setw(3) << i + 1 << "|";
            for (int j = 0; j < graph.GetVertexCount(); j++) {

                if (distancesMx[i][j] != INF) {
                    cout << std::setw(3) << distancesMx[i][j] << " ";
                }
                else {
                    cout << std::setw(3) << "inf" << " ";
                }
            }
            cout << '\n';
        }
        cout << '\n';

        cout << " Кол-во итераций: " << counter << "\n\n";
    }
}

void MinCostFlow(const MyGraph& graph) {
bool flag = false; int firstV, lastV;
do {
cout << "Введите номер первой вершины : " << endl;
firstV = InputVertex(1, graph.GetVertexCount());
cout << "Введите номер второй вершины : " << endl;
lastV = InputVertex(firstV+1, graph.GetVertexCount());
if (firstV == lastV)
cout << "Нельзя искать поток минимальной стоимости из вершины в нее саму !!!" << endl;
} while (firstV == lastV);


firstV--; lastV--;
int schetMin = graph.calcMinCostFlow(firstV, lastV);
cout << "Поток минимальной стоимости : " << schetMin << endl << endl;
}
