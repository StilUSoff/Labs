#include "MyGraph.h"
#include "globals.h"
#include "Shuffler.h"

// Конструктор :
MyGraph::MyGraph(int n) : vertexCnt(n), MatrixSmejn(n, vector<int>(n, 0)),
posWeightsMatrix(n, vector<int>(n, 0)), MatrixReach(),torrent(n , vector<int>(n, 0))//,Инициализирует переменные vertexCnt, MatrixSmejn, posWeightsMatrix и MatrixReach.

{
    int tmp;
    random_device rd;
    mt19937 mersenne(rd()); // случайные числа
    vector<int> vertDegrees = VertPrepare(); // вектор степеней графа вызов функции VertPrepare для инициализации вектора vertDegrees
    Shuffler<int> shuffler; //инициализация объекта shuffler типа Shuffler<int>.
    for (int i = 0; i < vertexCnt - 2; i++) { // цикл, который проходит по всем вершинам, кроме двух последних.
        shuffler.Clear(); //очистка объекта shuffler. для дальнейшего
        for (int j = i + 1; j < vertexCnt; j++) { //цикл, который проходит по всем вершинам, начиная с вершины i + 1
            shuffler.Push(j);//добавление вершины j в объект shuffler
        }
        shuffler.Shuffle(); //перемешивание вершин в объекте shuffler
        // поочерёдно в стоки ставим единички в случайные места с контролем того чтобы матрица смежность была верхняя треугольная
        for (int j = 0; j < vertDegrees[i]; j++) { //цикл, который проходит по всем вершинам, смежным с вершиной i.
            tmp = shuffler.Pop(); //получение вершины из объекта shuffler.
            MatrixSmejn[i][tmp] = 1; //установка значения в матрице смежности между вершинами i и tmp равным 1.
        }
    }
    // достиг до сети? :
    bool flag = true;   //избавляемся от тупиковых вершин
    for (int i = 0; i < vertexCnt-1; i++){
        flag = true;
        for (int j = 0; j < vertexCnt; j++) {
            if (MatrixSmejn[i][j] != 0) { //проверка, есть ли путь между вершинами i и j.
                flag = false; //роверка, является ли вершина i тупиковой.
                break;
            }
        }
        if (flag == true) {
            MatrixSmejn[i][i+1] = 1; //установка значения в матрице смежности между вершинами i и i + 1 равным 1.
        }
    }
    vector<int> sources; //инициализация вектора sources
    //избавление от дополнительных истоков
    flag = true;
    for (int i = 1; i < vertexCnt - 1; i++) { //цикл, который проходит по всем вершинам, кроме первой и последней
        flag = true;
        if (MatrixSmejn[0][i] == 0) { //проверка, есть ли путь между вершинами 0 и i.
            for (int j = 1; j < vertexCnt; j++) {
                if (MatrixSmejn[j][i] != 0) { //проверка, есть ли путь между вершинами j и i.
                    flag = false;
                    break;
                }
            }
            if (flag) { // тупикова вкршина?
                sources.push_back(i); //добавление вершины i в вектор sources
            }
        }
    }
    if (sources.size() != 0) { //проверка, является ли вектор sources пустым.
        for (int i = 0; i < sources.size(); i++) { //цикл, который проходит по всем вершинам в векторе sources.
            MatrixSmejn[0][sources[i]] = 1; //установка значения в матрице
        }
    }
    //MatrixSmejn[0][(vertexCnt / 2) + 1] = 0;
    //if(vertexCnt != 2)
    //    MatrixSmejn[0][vertexCnt-1] = 0;
    
    AssignWeights(); //весы
    MixWeights(); //смкшанные весы
    ModifyWeights(posWeightsMatrix, modPosWeightsMx); //вызов функции ModifyWeights для модификации весов ребер в матрице posWeightsMatrix.
    ModifyWeights(mixedWeightsMatrix, modMixedWeightsMx); //вызов функции ModifyWeights для модификации весов ребер в матрицк
    ReachMatrixGenerator(); //достежимости
    AssignTorrent(); // Стоимость пропуск
}

// Рекурсивная вспомогательная функция для обхода в глубину
void MyGraph::DFSUtil(int v, vector<bool>& visited, vector<int>& visitedNodes) {
    // Помечаем текущую вершину как посещенную
    visited[v] = true;
    // Добавляем вершину в список посещенных вершин
    visitedNodes.push_back(v);

    // Выводим текущую вершину
    cout << "Посещаем вершину " << v+1;
    if (!visitedNodes.empty() && visitedNodes.size() > 1) {
        cout << " -> ";
    }

    // Рекурсивно вызываем DFS для всех смежных вершин, если они еще не посещены
    for (int i = 0; i < vertexCnt; ++i) {
        if (MatrixSmejn[v][i] && !visited[i]) {
            cout << endl; // Перенос строки между вершинами
            DFSUtil(i, visited, visitedNodes);
        }
    }
}
    
// Функция для обхода в глубину с выводом путей
void MyGraph::DFS(int startVertex) {
    cout << "Поиск в Глубину (DFS)" << endl;
    // Массив для отслеживания посещенных вершин
    vector<bool> visited(vertexCnt, false);
    // Список посещенных вершин
    vector<int> visitedNodes;
    
    // Вызываем рекурсивную вспомогательную функцию для обхода в глубину
    cout << "Начинаем обход в глубину с вершины " << startVertex << endl;
    DFSUtil(startVertex, visited, visitedNodes);

    // Выводим завершение обхода в глубину
    cout << endl << "Обход в глубину завершен." << endl;
}

void MyGraph::BFS(int startVertex1) {
    vector<bool> visited(vertexCnt, false); // Массив для отслеживания посещенных вершин
    queue<int> q; // Очередь для BFS

    // Начальная вершина помечается как посещенная и добавляется в очередь
    visited[startVertex1] = true;
    q.push(startVertex1);

    cout << "Начинаем обход в ширину с вершины " << startVertex1 << endl;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        cout << "Посещаем вершину " << currentVertex + 1 << " -> " << endl;

        // Проходим по всем смежным вершинам текущей вершины
        for (int i = 0; i < vertexCnt; ++i) {
            // Если есть ребро между текущей и следующей вершиной, и следующая вершина еще не посещалась
            if (MatrixSmejn[currentVertex][i] && !visited[i]) {
                // Помечаем вершину как посещенную и добавляем ее в очередь
                visited[i] = true;
                q.push(i);
            }
        }
    }

    cout << endl << "Обход в ширину завершен." << endl;
}


//генерация вектора (отсортированного) с размером n-2 степеней вершин
vector<int> MyGraph::VertPrepare() const {
    vector<int> vertexDegrees;
    int tmpVertDeg;
    for (int i = 0; i < vertexCnt - 2; i++) {
        // цикл -2 потому что последняя вершина это сток и связь предпоследнего с последним в ручную в конструкторе
        do {
            tmpVertDeg = LaplaceD();
        } while (tmpVertDeg >= vertexCnt);
        vertexDegrees.push_back(tmpVertDeg);
    }
    std::sort(vertexDegrees.begin(), vertexDegrees.end(), std::greater<int>());
    return vertexDegrees;
}
// Задаем весы случайным оброзом
void MyGraph::AssignWeights() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (int i = 0; i < vertexCnt; i++) {
        for (int j = i + 1; j < vertexCnt; j++) {
            if (MatrixSmejn[i][j] != 0)
                posWeightsMatrix[i][j] = mersenne() % (MAX_POS_WEIGHT - 1) + 1;
        }
    }
}

void MyGraph::MixWeights() { // смешанная
    mixedWeightsMatrix = posWeightsMatrix;
    int posOrNeg;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (int i = 0; i < vertexCnt; i++) {
        for (int j = i + 1; j < vertexCnt; j++) {
            if (mixedWeightsMatrix[i][j] != 0) {
                posOrNeg = mersenne() % 2;
                if (posOrNeg == 1) {
                    mixedWeightsMatrix[i][j] *= -1;
                }
            }
        }
    }
}

void MyGraph::ModifyWeights(vector<vector<int> >& WeightsMatrix, vector<vector<int> >& modified) { // для Флойда-Уоршелла и др где 0 = inf
    modified = WeightsMatrix;
    for (int i = 0; i < vertexCnt; i++) {
        for (int j = 0; j < vertexCnt; j++) {
            if (modified[i][j] == 0) {
                modified[i][j] = INF;
            }
        }
    }
}

int MyGraph::GetVertexCount() const {
    return vertexCnt;
}

vector<vector<int> > MyGraph::GetAdjMatrix() const {
    return MatrixSmejn;
}

vector<vector<int> > MyGraph::GetWeightsMatrix(int type) const {
    switch (type) {
    case 0:
        return posWeightsMatrix; // что будет приниматся позитив веса или смешанные или дальнейшее модифицированные с inf 
        break;
    case 1:
        return mixedWeightsMatrix;
        break;
    case 2:
        return modPosWeightsMx;
        break;
    case 3:
        return modMixedWeightsMx;
        break;
    default:
        break;
    }
    return GetWeightsMatrix(3);
}

vector<vector<int>> MyGraph::GetTorrentMatrix() const{
    return torrent;
}

//Метод Шимбелла-------------------------------------------
//MultByShimbell используется для умножения двух матриц с использованием алгоритма Шимбелла. Он принимает две матрицы firstM и secM и режим mode, который может быть ShimbellMode::Short или ShimbellMode::Long. Если mode установлен в ShimbellMode::Short, то метод возвращает минимальное значение в каждой ячейке результирующей матрицы. Если mode установлен в ShimbellMode::Long, то метод возвращает максимальное значение в каждой ячейке результирующей матрицы.
//Метод CalcShimbell используется для вычисления матрицы кратчайших путей. Он принимает количество ребер в графе и режим mode. Метод проходит по всем ребрам графа и умножает матрицу весов на себя edgeCnt - 1 раз с использованием метода MultByShimbell.
vector<vector<int> > MyGraph::MultByShimbell(const vector<vector<int> > firstM, const vector<vector<int> > secM, ShimbellMode mode) const {
    vector<vector<int> > resM(vertexCnt, vector<int>(vertexCnt, 0));
    vector<int> tmp;
    bool isNotZero;
    for (int i = 0; i < vertexCnt; i++) {
        for (int j = 0; j < vertexCnt; j++) {
            tmp.clear();
            isNotZero = false;
            for (int k = 0; k < vertexCnt; k++) {
                // элемент строки + элемент столбца как при сложение эл матриц
                if ((firstM[i][k] != 0) && (secM[k][j] != 0)) {
                    tmp.push_back(firstM[i][k] + secM[k][j]);
                    isNotZero = true;
                }
            }
            if (isNotZero) {
                if (mode == ShimbellMode::Short) {
                    resM[i][j] = *std::min_element(tmp.begin(), tmp.end());
                }
                else {    //mode == ShimbellMode::Long
                    resM[i][j] = *std::max_element(tmp.begin(), tmp.end());
                }
            }
            else {
                resM[i][j] = 0;
            }
        }
    }
    return resM;
}
// a * b = b * a = a + b => max\min(a+b)i
// a + 0 = 0 + a = 0
vector<vector<int> > MyGraph::CalcShimbell(int edgeCnt, ShimbellMode mode) const {
    vector<vector<int> > resM = posWeightsMatrix;
    for (int i = 0; i < edgeCnt - 1; i++) {
        resM = MultByShimbell(resM, posWeightsMatrix, mode);
    }
    return resM;
}

//Матрица достижимости с кол-вом путей---------------------
void MyGraph::ReachMatrixGenerator() { // используем Уоршелла
    vector<vector<int> > boolExpMatrix = MatrixSmejn;
    MatrixReach = vector<vector<int> >(vertexCnt, vector<int>(vertexCnt, 0));
    for (int i = 0; i < vertexCnt - 1; i++) {
        boolExpMatrix = BMultMatrixs(boolExpMatrix, MatrixSmejn);
        MatrixReach = AddMatrixs(MatrixReach, boolExpMatrix);
    }
    for (int i = 0; i < vertexCnt; i++) {
        MatrixReach[i][i] = 1;
    }
}
vector<vector<int> > MyGraph::GetReachMatrix() const {
    return MatrixReach;
}

vector<int> MyGraph::Dijkstra(int vertNum, int& counter) const { //O(V3) до O(V*E*log(V))
    vector<int> distances(modPosWeightsMx[vertNum]); //инициализация массива расстояний.
    distances[vertNum] = 0; // начальное = 0

    vector<bool> isVisitedVector(vertexCnt, false); // инициализация массива посещенных вершин.
    isVisitedVector[vertNum] = true; //зашли в вершину

    int min, curVert = vertexCnt - 1; //нициализация переменной min и переменной curVert.

    for (int i = 0; i < vertexCnt; i++) { //цикл, который проходит по всем вершинам.
        min = INF; //инициализация переменной min значением INF
        // Поиск минимальной вершины
        for (int j = 0; j < vertexCnt; j++, counter++) {
            if (!isVisitedVector[j] && (distances[j] < min)) { //проверка, является ли вершина j не посещенной и имеет ли она меньшее расстояние, чем переменная min.
                min = distances[j]; //обновление переменной min на значение расстояния до вершины j.
                curVert = j; //обновление переменной curVert на значение индекса вершины j.
            }
        }
        // Соседи этой вершины
        isVisitedVector[curVert] = true; // установка флага посещенной для вершины curVert.
        for (int j = 0; j < vertexCnt; j++, counter++) {
            if (!isVisitedVector[j] && (modPosWeightsMx[curVert][j] != INF)//проверка, является ли вершина j не посещенной, есть ли путь между вершинами curVert и j, не является ли текущее расстояние до вершины curVert бесконечным и является ли сумма расстояния до вершины curVert и веса ребра между ними меньше текущего расстояния до вершины j.
                && (distances[curVert] != INF) && ((distances[curVert] + modPosWeightsMx[curVert][j]) < distances[j]))
            {
                distances[j] = distances[curVert] + modPosWeightsMx[curVert][j];//обновление расстояния до вершины j на сумму расстояния до вершины curVert и веса ребра между ними.
            }
        }
    }
    return distances; //возврат массива расстояний.
}

vector<vector<int> > MyGraph::RestorePaths(int inpVert, const vector<int>& distances, const vector<vector<int> > weightMx) const {
    vector<vector<int> > paths(vertexCnt, vector<int>());
    int tmp, curVert;
    for (int i = 0; i < vertexCnt; i++) {
        if (distances[i] != 0) {        //== 0 -- исходная вершина
            if (distances[i] != INF) {    //Если есть путь
                curVert = i;
                paths[i].push_back(curVert);
                while (curVert != inpVert) {    //Пока не дошли до исходной вершины
                    for (int j = 0; j < vertexCnt; j++) {    //Ищем такую смежную вершину с нынешней что бы
                                                            //значения ее метки было = разности значений
                                                            //метки нынешней и веса ребра между ними
                        if (weightMx[j][curVert] != INF) { // если есть ребра
                            if ((distances[curVert] - weightMx[j][curVert]) == distances[j]) { // вычисляем
                                curVert = j;
                                paths[i].push_back(j);
                                break;
                            }
                        }
                    }
                }
            }
            else {
                paths[i].push_back(INF);
            }
        }
        else {
            paths[i].push_back(INF);
        }
    }
    return paths;
}

// инициализируются расстояния от исходной вершины до всех остальных вершин, как бесконечные, а расстояние до самого src принимается равным 0.                         Создается контейнер размера |V| со всеми значениями равными бесконечности, за исключением элемента distances[inpVert], где src — исходная вершина.
//Вторым шагом вычисляются самые короткие расстояния. Следующие шаги нужно выполнять |V|-1 раз, где |V| — число вершин в данном графе.
//Произведите следующее действие для каждого ребра u-v:
//Если dist[j] > dist[i] + вес ребра ij, то обновите dist[v]
//dist [j] = dist [i] + вес ребра ij
//На этом шаге сообщается, присутствует ли в графе цикл отрицательного веса. Для каждого ребра u-v необходимо выполнить следующее:

//Если dist[i] > dist[j] + вес ребра jv, то в графе присутствует цикл отрицательного веса.

vector<int> MyGraph::BellmanFord(int inpVert, int& counter, vector<vector<int> > mx) const {// для смежности сложность O(|V||E|) против O(|E| + |V|\ln(|V|))
    counter = 0;
    vector<int> distances(vertexCnt, INF); //инициализация vec расстояний.
    distances[inpVert] = 0; // установка начального расстояния до вершины inpVert равным 0.

    int curVert, newDistance;

    deque<int> dq; //инициализация очереди
    dq.push_back(inpVert); //добавление вершины inpVert в очередь

    while (!dq.empty()) { //цикл, который продолжается до тех пор, пока очередь не станет пустой.
        curVert = dq.front();
        dq.pop_front(); //получение вершины из начала очереди и удаление ее из очереди.
        for (int i = curVert + 1; i < vertexCnt; i++, counter++) {//цикл, который проходит по всем вершинам, смежным с текущей вершиной.
            if (mx[curVert][i] != INF) { //проверка, есть ли путь между текущей и следующей вершиной.
                newDistance = distances[curVert] + mx[curVert][i]; //вычисление нового расстояния.
                if (newDistance < distances[i]) { //проверка, является ли новое расстояние меньше текущего расстояния до следующей вершины.
                    distances[i] = newDistance; //обновление расстояния до следующей вершины.
                    if (std::find(dq.begin(), dq.end(), i) == dq.end()) {        //вершины в очереди нет
                        dq.push_back(i);                                        //добавили в конец очереди
                    }
                    else {                                                        //вершина есть в очереди
                        std::remove(dq.begin(), dq.end(), i);                    //удалили из очереди
                        dq.push_front(i);                                        //добавили в начало очереди
                    }
                }
            }
        }
    }
    return distances;
}

vector<int> MyGraph::BellmanFord(int inpVert, vector<vector<int> > mx) const { //для весов сложность O(|V||E|) против O(|E| + |V|\ln(|V|))
    vector<int> distances(vertexCnt, INF);
    distances[inpVert] = 0;
    int counter = 0;
    int curVert, newDistance;

    deque<int> dq;
    dq.push_back(inpVert);

    while (!dq.empty()) {
        curVert = dq.front();
        dq.pop_front();
        for (int i = curVert + 1; i < vertexCnt; i++, counter++) {
            if (mx[curVert][i] != INF) {
                newDistance = distances[curVert] + mx[curVert][i];
                if (newDistance < distances[i]) {
                    distances[i] = newDistance;
                    if (std::find(dq.begin(), dq.end(), i) == dq.end()) {        //этой вершины нет в очереди
                        dq.push_back(i);                                        //добавили в конец
                    }
                    else {                                                        //вершина есть в очереди
                        std::remove(dq.begin(), dq.end(), i);                    //удалили ее из очереди
                        dq.push_front(i);                                        //добавили в начало очереди
                    }
                }
            }
        }
    }
    return distances;
}

vector<vector<int> > MyGraph::FloydWarshall(int& counter, vector<vector<int> > mx) const { //O(nˆ3) time O(nˆ2) mem берем только ребра => матрицу расстояний и перебераем затем присваеваем вершины k  а ребра i - j
    vector<vector<int> > distancesMx = mx; //инициализация матрицы расстояний.
    for (int i = 0; i < vertexCnt; i++) { //цикл, который проходит по всем вершинам.
        for (int j = 0; j < vertexCnt; j++) {
            for (int k = 0; k < vertexCnt; k++, counter++) {
                if (distancesMx[i][k] != INF && distancesMx[k][j] != INF) { //проверка, есть ли путь между вершинами i, k и k, j.
                    distancesMx[i][j] = min(distancesMx[i][j], (distancesMx[i][k] + distancesMx[k][j]));  //обновление расстояния между вершинами
                }
            }
        }
    }

    for (int i = 0; i < vertexCnt; i++) {
        distancesMx[i][i] = 0; //становка расстояния от вершины до самой себя равным 0. (так как граф без узлов)
    }

    return distancesMx;
}

// Алгоритм Прима что бы найти остовый граф (положительная матрица)
vector<tuple<int, int, int>> MyGraph::PrimMST() {
    int V = GetVertexCount();

    // Массив для хранения веса ключа для каждой вершины и индекса ребра
    vector<pair<int, pair<int, int>>> key(V + 1, {INT_MAX, {-1, -1}}); // Увеличиваем размер на 1 для вершин с 1 по V
    // Массив для отслеживания включенных вершин в MST
    vector<bool> inMST(V + 1, false); // Увеличиваем размер на 1 для вершин с 1 по V

    // Приоритетная очередь для хранения пар (вес, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Начать с первой вершины (нумерация с 1)
    int src = 1; // Используем первую вершину
    key[src] = {0, {0, src}}; // Используем индексацию с 1
    pq.push({0, src});

    // Пока приоритетная очередь не пуста
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Включаем текущую вершину в MST
        inMST[u] = true;

        // Пройтись по смежным вершинам и обновить ключи
        for (int v = 1; v <= V; ++v) {
            if (MatrixSmejn[u][v] && !inMST[v] && posWeightsMatrix[u][v] < key[v].first) {
                key[v] = {posWeightsMatrix[u][v], {u, v}};
                pq.push({key[v].first, v});
            }
        }
    }

    // Создать и вернуть список рёбер MST
    vector<tuple<int, int, int>> result;
    for (int i = 1; i <= V; ++i) {
        if (key[i].second.first != -1) {
            // Добавляем ребро в список рёбер MST, но исключаем вершину 0
            if (key[i].second.first != 0) {
                // Получаем индексы вершин из списка ключей
                int u = key[i].second.first;
                int v = key[i].second.second;
                // Используем вершины - 1 в качестве индексов в матрице весов
                result.push_back({u, v, posWeightsMatrix[u - 1][v - 1]});
            }
        }
    }

    // Вывод рёбер минимального остовного дерева
    cout << "Рёбра миним.остовного дерева:" << endl;
    for (const auto& edge : result) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int weight = get<2>(edge);
        cout << u << " -> " << v << " (Вес пути: " << weight << ")" << endl;
    }

    return result;
}

vector<tuple<int, int, int>> MyGraph::PrimSMESH() {
    int V = GetVertexCount();

    // Массив для хранения веса ключа для каждой вершины и индекса ребра
    vector<pair<int, pair<int, int>>> key(V + 1, {INT_MAX, {-1, -1}}); // Увеличиваем размер на 1 для вершин с 1 по V
    // Массив для отслеживания включенных вершин в MST
    vector<bool> inMST(V + 1, false); // Увеличиваем размер на 1 для вершин с 1 по V

    // Приоритетная очередь для хранения пар (вес, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Начать с первой вершины (нумерация с 1)
    int src = 1; // Используем первую вершину
    key[src] = {0, {0, src}}; // Используем индексацию с 1
    pq.push({0, src});

    // Пока приоритетная очередь не пуста
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Включаем текущую вершину в MST
        inMST[u] = true;

        // Пройтись по смежным вершинам и обновить ключи
        for (int v = 1; v <= V; ++v) {
            if (mixedWeightsMatrix[u - 1][v - 1] != 0 && !inMST[v] && mixedWeightsMatrix[u - 1][v - 1] < key[v].first) {
                key[v] = {mixedWeightsMatrix[u - 1][v - 1], {u, v}};
                pq.push({key[v].first, v});
            }
        }
    }

    // Создать и вернуть список рёбер MST
    vector<tuple<int, int, int>> result;
    for (int i = 1; i <= V; ++i) {
        if (key[i].second.first != -1) {
            // Добавляем ребро в список рёбер MST, но исключаем вершину 0
            if (key[i].second.first != 0) {
                // Получаем индексы вершин из списка ключей
                int u = key[i].second.first;
                int v = key[i].second.second;
                // Используем вершины - 1 в качестве индексов в матрице весов
                result.push_back({u, v, mixedWeightsMatrix[u - 1][v - 1]});
            }
        }
    }

    // Вывод рёбер минимального остовного дерева
    cout << "Рёбра миним.остовного дерева:" << endl;
    for (const auto& edge : result) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int weight = get<2>(edge);
        cout << u << " -> " << v << " (Вес пути: " << weight << ")" << endl;
    }

    return result;
}



void MyGraph::BuildFakeSource() {
    vector<int> sources;
    bool flag = true;
// Поиск подозрительных вершин для проверки
    for (int i = 1; i < vertexCnt-1; i++) {
        if (MatrixSmejn[0][i] == 0) {
            for (int j = 1; j < vertexCnt; j++) {
                if (MatrixSmejn[j][i] != 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) { //Столбик нулевой, для веришны нужно строить фиктивный исток
                sources.push_back(i);
            }
        }
    }
    if (sources.size() == 0) {
        MatrixFakeSource = MatrixSmejn;
    }
    else {
        for (int i = 0; i < vertexCnt + 1; i++) {
            if (i == 0 || (i != 0 && find(sources.begin(), sources.end(), (i)) != sources.end())) {
                MatrixFakeSource[0][i + 1] = 1;
            }
        }
        for (int j = 1; j < vertexCnt + 1; j++) {
            for (int k = 1; k < vertexCnt + 1; k++) {
                MatrixFakeSource[j][k] = MatrixSmejn[j - 1][k - 1];
            }
        }
    }
}

void MyGraph::AssignTorrent() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    for (int i = 0; i < vertexCnt; i++) {
        for (int j = i + 1; j < vertexCnt; j++) {
            if (MatrixSmejn[i][j] != 0)
                torrent[i][j] = mersenne() % (MAX_POS_WEIGHT - 1) + 1;
        }
    }
};

bool MyGraph::bfs_FordFulkerson(vector<vector<int>> matrix, int source, int sink, vector<int>& path) const {
    vector<bool> isVisitedArr(matrix.size(), false);
    queue<int> q;
    
    int curVert;

    q.push(source);
    isVisitedArr[source] = true;
    path[source] = -1;

while (!q.empty()) {
    curVert = q.front();
    q.pop();

for (int i = 0; i < matrix.size(); i++) {
    if ((isVisitedArr[i] == false) && (matrix[curVert][i] > 0)) {
        path[i] = curVert;
        if (i == sink) {
return true;
}
q.push(i);
        isVisitedArr[i] = true;
        }
    }
}
return false;
}

int MyGraph::fordFulkerson(int source, int sink) const {
    int tmpSink = sink;
    vector<vector<int>> tmptorrent = torrent;
    vector<int>path(tmptorrent.size(),0);
    int maxFlow = 0;
    int curFlow;
    while (bfs_FordFulkerson(tmptorrent,source,tmpSink,path)) {
        curFlow=INF;
        for(int i = tmpSink;i != source;i = path[i]){
            curFlow = std::min(curFlow,tmptorrent[path[i]][i]);
        }
        for(int i = tmpSink; i!=source; i = path[i]){
            tmptorrent[path[i]][i] -= curFlow;
            tmptorrent[path[i]][i] += curFlow;
        }
        maxFlow += curFlow;
    }
    return maxFlow;
}

int MyGraph::calcMinCostFlow(int s, int t) const {
int flow = fordFulkerson(s, t);
int minCostFlow = 0;

    cout << "Максимальный поток : " << flow << ". ";
    flow = flow * 2 / 3;
    cout << "Используемый поток : " << flow << '\n';

    vector<vector<int>> tmpmodMixedWeightsMx = modMixedWeightsMx;
    vector<vector<int>> tmpTorrent = torrent; // Матрица пропуск. способностей

cout << "Матрица стоимости :" << endl;
    PrintMatrix(modMixedWeightsMx);
cout << "Матрица пропускных способностей :" << endl;
    PrintMatrix(torrent);

while (flow != 0) {
    vector<int> route = RestorePaths(s, BellmanFord(s, tmpmodMixedWeightsMx), tmpmodMixedWeightsMx)[t];
    sort(route.begin(), route.end());

int bottleNeck = INF;
int cost = 0;
vector<pair<int, int>> edgesToDelete;

for (vector<int>::iterator it = route.begin(); it != route.end() - 1; it++) {
    if (tmpTorrent[*it][*(it + 1)] < bottleNeck)
        bottleNeck = tmpTorrent[*it][*(it + 1)];
    cout << *it + 1 << "->";
}

bottleNeck = min(bottleNeck, flow);
    cout << t + 1 << " Пускаем поток " << bottleNeck;

for (vector<int>::iterator it = route.begin(); it != route.end() - 1; it++) {
    tmpTorrent[*it][*(it + 1)] -= bottleNeck;
    cost = cost + tmpmodMixedWeightsMx[*it][*(it + 1)];
        if (!tmpTorrent[*it][*(it + 1)])
            edgesToDelete.push_back(pair<int, int>(*it, *(it + 1)));
    }

cout << " со стоимостью за единицу потока " << cost;

    minCostFlow = minCostFlow + (cost * bottleNeck);

cout << ". Итоговая стоимость " << cost * bottleNeck << "\n";

for (vector<pair<int,int>>::iterator it = edgesToDelete.begin(); it != edgesToDelete.end(); it++)
    tmpmodMixedWeightsMx[it->first][it->second] = INF;

    edgesToDelete.clear();

    flow -= bottleNeck;

}
cout << endl;
//cout << "Матрица стоимости (после работы) :" << endl;
//PrintMatrix(tmpmodMixedWeightsMx);
//cout << "Матрица пропускных способностей (тоже после):" << endl;
//PrintMatrix(tmpTorrent);
//cout << endl;
return minCostFlow;
}









