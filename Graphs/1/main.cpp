#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>

// Константы для распределения Стьюдента
const double student_mean = 0.0;
const double student_variance = 1.0;
const unsigned int graph_size = 5; // Размер графа

// Функция для генерации случайного числа с распределением Стьюдента
double generate_student_random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::student_t_distribution<> student_dist(student_mean, student_variance);
    return student_dist(gen);
}

// Генерация случайного связного ациклического графа
std::vector<std::vector<int>> generate_random_dag(unsigned int size) {
    std::vector<std::vector<int>> adjacency_matrix(size, std::vector<int>(size, 0));

    // Добавляем рёбра, пока граф не станет связным
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = i + 1; j < size; ++j) {
            // Генерируем случайный вес ребра
            double weight = generate_student_random();

            // Добавляем ребро
            adjacency_matrix[i][j] = weight > 0 ? 1 : 0;
            adjacency_matrix[j][i] = weight < 0 ? 1 : 0;
        }
    }

    // Проверяем наличие циклов и удаляем рёбра, чтобы сделать граф ациклическим
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = i + 1; j < size; ++j) {
            if (adjacency_matrix[i][j] == 1 && adjacency_matrix[j][i] == 1) {
                // Если обнаружен цикл, удаляем случайное ребро
                if (generate_student_random() > 0) {
                    adjacency_matrix[i][j] = 0;
                } else {
                    adjacency_matrix[j][i] = 0;
                }
            }
        }
    }

    return adjacency_matrix;
}

// Функция для вывода матрицы смежности графа в консоль
void print_adjacency_matrix(const std::vector<std::vector<int>>& adjacency_matrix) {
    for (const auto& row : adjacency_matrix) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Генерируем случайный связный ациклический граф
    std::vector<std::vector<int>> graph = generate_random_dag(graph_size);

    // Выводим матрицу смежности графа в консоль
    std::cout << "Adjacency Matrix:" << std::endl;
    print_adjacency_matrix(graph);

    return 0;
}
