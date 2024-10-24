#include "sorting_manager.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
using namespace std::chrono;

// Construtor que inicializa o vetor
SortingManager::SortingManager(int size, bool descending) {
    comparisons = 0;
    swaps = 0;
    data.resize(size);

    // Gera valores aleatórios
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 10000;
    }

    // Ordena em ordem descendente, se necessário
    if (descending) {
        sort(data.rbegin(), data.rend());
    }
}

// Função para exibir os dados
void SortingManager::displayData() const {
    for (int val : data) {
        cout << val << " ";
    }
    cout << endl;
}

// Função para resetar os dados ao estado original
void SortingManager::resetData(bool descending) {
    comparisons = 0;
    swaps = 0;

    // Regenerar valores aleatórios
    for (int i = 0; i < data.size(); ++i) {
        data[i] = rand() % 10000;
    }

    // Ordenar em ordem descendente, se necessário
    if (descending) {
        sort(data.rbegin(), data.rend());
    }
}

// Implementação dos algoritmos de ordenação
void SortingManager::bubbleSort() {
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (data[j] > data[j + 1]) {
                swaps++;
                swap(data[j], data[j + 1]);
            }
        }
    }
}

void SortingManager::selectionSort() {
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        swaps++;
        swap(data[i], data[minIdx]);
    }
}

void SortingManager::insertionSort() {
    int n = data.size();
    for (int i = 1; i < n; ++i) {
        int key = data[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && data[j] > key) {
            swaps++;
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// MergeSort
void SortingManager::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void SortingManager::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) L[i] = data[left + i];
    for (int i = 0; i < n2; ++i) R[i] = data[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) data[k++] = L[i++];
        else data[k++] = R[j++];
    }
    while (i < n1) data[k++] = L[i++];
    while (j < n2) data[k++] = R[j++];
}

// Funções para outros algoritmos: Quicksort, Heapsort, etc. (implementar conforme necessário)

// Função para realizar a ordenação com base na escolha do usuário
void SortingManager::sortData(int algorithmType, int algorithmChoice) {
    auto start = high_resolution_clock::now();

    if (algorithmType == 1) {
        if (algorithmChoice == 1) bubbleSort();
        else if (algorithmChoice == 2) selectionSort();
        else insertionSort();
    } else if (algorithmType == 2) {
        if (algorithmChoice == 1) mergeSort(0, data.size() - 1);
        // Implementar Quicksort e Heapsort aqui
    } else if (algorithmType == 3) {
        // Implementar Radixsort, Bucketsort, Countingsort aqui
    }

    auto end = high_resolution_clock::now();
    double duration = duration_cast<microseconds>(end - start).count();
    printResults(duration);
}

// Função para imprimir os resultados
void SortingManager::printResults(double time) {
    cout << "Vetor ordenado: ";
    displayData();
    cout << "Tempo de execução: " << time << " microsegundos" << endl;
    cout << "Comparações: " << comparisons << endl;
    cout << "Trocas: " << swaps << endl;
}
