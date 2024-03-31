#pragma once
#include "globals.h"

enum class ShimbellMode {
    Short = 0,
    Long = 1
};

struct edge {
    int a, b, cost;
    edge(int a2, int b3, int cost4) {
        a = a2;
        b = b3;
        cost = cost4;
    }
};



class MyGraph {
private:
    int vertexCnt; // переменная, которая хранит количество вершин в графе.
    vector<vector<int> > MatrixSmejn; // двумерный вектор, который представляет матрицу смежности графа.
    vector<vector<int> > posWeightsMatrix; // двумерный вектор, который представляет матрицу весов ребер графа.
    vector<vector<int> > mixedWeightsMatrix; // двумерный вектор, который представляет смешанную матрицу весов ребер графа.
    vector<vector<int> > modPosWeightsMx; // двумерный вектор, который представляет модифицированную матрицу весов ребер графа.
    vector<vector<int> > modMixedWeightsMx; //двумерный вектор, который представляет модифицированную смкшанную матрицу весов ребер графа.
    vector<vector<int> > MatrixReach;  // двумерный вектор, который представляет матрицу достижимости графа.

    vector<int> VertPrepare() const; //функция, которая подготавливает вершины графа.
    void AssignWeights(); // функция, которая присваивает веса ребрам графа.
    void MixWeights(); // смешанные веса
    void ModifyWeights(vector<vector<int> >& WeightsMatrix, vector<vector<int> >& modified); // функция, которая модифицирует веса ребер в матрице.

    vector<vector<int>> MultByShimbell(const vector<vector<int> > fMx, // функция, которая умножает две матрицы с использованием алгоритма Шимбелла
        const vector<vector<int> > sMx, ShimbellMode mode) const;

    vector<vector<int>> throughPutMx; // двумерный вектор, который представляет матрицу пропускной способности ребер графа.
    vector<vector<int>> torrent;
    vector<vector<int>> MatrixFakeSource; //двумерный вектор, который представляет матрицу фиктивного источника графа. потом если не нужен то станет копией смежности
    
    
    
    vector<vector<int> > UnOrMxSmejn; //двумерный вектор, который представляет матрицу смежности графа без отрицательных весов ребер.
    vector<vector<int> > UnOrPosWeightMx; // веса >0
    //////////
    vector<vector<int> > minTree; // потом
    vector<pair<int, int> > PruferTree; // потом ???
public:
    MyGraph(int n); //конструктор класса MyGraph, который инициализирует переменные класса.
    int GetVertexCount() const; //функция, которая возвращает количество вершин в графе.
    vector<vector<int> > GetAdjMatrix() const; //возвращает матрицу смежности графа.
    vector<vector<int> > GetWeightsMatrix(int type) const; //весов
    vector<vector<int> > GetReachMatrix() const; // достижимости
    vector<vector<int> > GetTorrentMatrix() const; // матрица стоимости
    vector<vector<int>> CalcShimbell(int edgeCnt, ShimbellMode mode) const;
    void DFSUtil(int v, vector<bool>& visited, vector<int>& visitedNodes); //  обход в глубину для графа.
    void DFS(int startVertex); // обход в глубину для графа. выводы и т.д.
    void BFS(int startVertex1); //обход в ширину для графа, начиная с указанной вершины
    
    //vector<vector<int> > CalcShimbell(int edgeCnt, ShimbellMode mode) const; //функция, которая вычисляет матрицу экстримальных путей Шимбелл
    void ReachMatrixGenerator(); // матрица достижимости графа.
    
    void BuildFakeSource();
    //void AssignWeights(); // функция, которая присваивает веса ребрам графа.
    vector<int> Dijkstra(int inpVert, int& counter) const; //алгоритм Дейкстры для нахождения кратчайшего пути в графе
    vector<vector<int> > RestorePaths(int inpVert, const vector<int>& distances, const vector<vector<int> > weightMx) const;//восстанавливает пути в графе. потом
    vector<int> BellmanFord(int inpVert, int& counter, vector<vector<int> > mx) const; //алгоритм Беллмана-Форда для нахождения кратчайшего пути в графе.
    vector<int> BellmanFord(int inpVert, vector<vector<int> > mx) const; //алгоритм Беллмана-Форда для нахождения кратчайшего пути в графе но для весовой.
    vector<vector<int> > FloydWarshall(int& counter, vector<vector<int> > mx) const; //алгоритм Флойда-Уоршала с INF нахождения кратчайшего пути в графе.
    vector<tuple<int, int, int>> PrimMST(); // алгоритм Прима для минимального остовного графа
    vector<tuple<int, int, int>> PrimSMESH(); // для смешанной тоже
    bool bfs_FordFulkerson(vector<vector<int>> residualG, int source, int sink, vector<int>&path) const;
    int fordFulkerson(int source,int sink) const;
    int calcMinCostFlow(int s, int t) const;
    void AssignTorrent();
//    vector<int> Dijkstra(int inpVert, int& counter) const; //алгоритм Дейкстры для нахождения кратчайшего пути в графе
//    vector<vector<int> > RestorePaths(int inpVert, const vector<int>& distances, const vector<vector<int> > weightMx) const;//восстанавливает пути в графе. потом
//    vector<int> BellmanFord(int inpVert, int& counter, vector<vector<int> > mx) const; //алгоритм Беллмана-Форда для нахождения кратчайшего пути в графе.
//    vector<int> BellmanFord(int inpVert, vector<vector<int> > mx) const; //алгоритм Беллмана-Форда для нахождения кратчайшего пути в графе но для весовой.
//    vector<vector<int> > FloydWarshall(int& counter, vector<vector<int> > mx) const; //алгоритм Флойда-Уоршала с INF нахождения кратчайшего пути в графе.
//    vector<tuple<int, int, int>> PrimMST(); // алгоритм Прима для минимального остовного графа
//    vector<tuple<int, int, int>> PrimSMESH(); // для смешанной тоже
    //void AssignTorrent(); //пути
};
