#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>

// ��������� ��� ������������� ���������
const double student_mean = 0.0;
const double student_variance = 1.0;
const unsigned int graph_size = 5; // ������ �����

// ������� ��� ��������� ���������� ����� � �������������� ���������
double generate_student_random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::student_t_distribution<> student_dist(student_mean, student_variance);
    return student_dist(gen);
}

// ��������� ���������� �������� ������������� �����
std::vector<std::vector<int>> generate_random_dag(unsigned int size) {
    std::vector<std::vector<int>> adjacency_matrix(size, std::vector<int>(size, 0));

    // ��������� ����, ���� ���� �� ������ �������
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = i + 1; j < size; ++j) {
            // ���������� ��������� ��� �����
            double weight = generate_student_random();

            // ��������� �����
            adjacency_matrix[i][j] = weight > 0 ? 1 : 0;
            adjacency_matrix[j][i] = weight < 0 ? 1 : 0;
        }
    }

    // ��������� ������� ������ � ������� ����, ����� ������� ���� ������������
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = i + 1; j < size; ++j) {
            if (adjacency_matrix[i][j] == 1 && adjacency_matrix[j][i] == 1) {
                // ���� ��������� ����, ������� ��������� �����
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

// ������� ��� ������ ������� ��������� ����� � �������
void print_adjacency_matrix(const std::vector<std::vector<int>>& adjacency_matrix) {
    for (const auto& row : adjacency_matrix) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // ���������� ��������� ������� ������������ ����
    std::vector<std::vector<int>> graph = generate_random_dag(graph_size);

    // ������� ������� ��������� ����� � �������
    std::cout << "Adjacency Matrix:" << std::endl;
    print_adjacency_matrix(graph);

    return 0;
}
