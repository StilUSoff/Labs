#include "globals.h"
#include "MyGraph.h"
#include "Operations.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int VertexCNT = InputVertexCount();
    MyGraph graph(VertexCNT);
    cout << "Матрица смежности вершин:" << endl;
    PrintMatrix(graph.GetAdjMatrix());
    cout << endl;
    cout << "Весовая положительная матрица:" << endl;
    PrintMatrix(graph.GetWeightsMatrix(0));
    cout << endl;
    cout << "Весовая смешанная матрица:" << endl;
    PrintMatrix(graph.GetWeightsMatrix(1));
    cout << endl;

    char YesNo;
    int MenuItem, i;
    do {
        PrintMenu();
        cout << '\n';
        MenuItem = InputMenuItem();
        switch (MenuItem) {
        case 0: //Метод Шимбела
            ShimbellMethod(graph);
            break;
        case 1: //Матрица достижимости
            ReachabilityOperation(graph);
            break;
        case 2: //Алгоритм дейкстры
            DijkstraAlgorithm(graph);
            break;
        case 3: //Алгоритм Беллмана-Форда
            BellmanFordAlgorithm(graph);
            break;
        case 4: //Алгоритм Флойда-Уоршала
            FloydWarshallAlgorithm(graph);
            break;
        case 5: //Поиск в глубину
            graph.DFS(1);
            break;
        case 6: //Поиск в ширину
            graph.BFS(1);
            break;
        case 7: // Алгоритм Прима
            graph.PrimMST();
            break;
        case 8: // Алгоритм Прима для смешанной
            graph.PrimSMESH();
            break;
        case 9: // Минимальный поток с помощью Форда-Фларкенсона
            MinCostFlow(graph);
        default:
            break;
        }
    } while (IsContinue(YesNo));
}

