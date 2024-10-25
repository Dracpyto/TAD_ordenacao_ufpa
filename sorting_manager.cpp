#include "sorting_manager.h"
#include <iostream> // input e output do código 
#include <vector> // usar dados em vetor 
#include <chrono> // calcular o tempo de execução e de trocas reqlizadas por cada algorimo de ordenação
#include <cstdlib>// alocação de memória e gerar números aleatórios 
#include <algorithm> // corderna a busca, organização e ordenação dos dados em um intervalo definido, exemplo: Std::swap
#include <queue> // Usa o princípio FIFO (First in, first out) para escalar o fluxo de entrada e sáida dos dados 

using namespace std;
using namespace std::chrono;

// Construtor que inicializa o vetor e armazena o estado original
SortingManager::SortingManager(int size, bool descending) {
    comparisons = 0;
    swaps = 0;
    data.resize(size);
    originalData.resize(size);

    // Gera valores aleatórios e os armazena em `originalData`
    for (int i = 0; i < size; ++i) {
        originalData[i] = rand() % 10000;
    }

    data = originalData; // Copia para o vetor principal

    // Ordena em ordem descendente, se necessário
    if (descending) {
        sort(data.rbegin(), data.rend());
        originalData = data; // Armazena o original em ordem decrescente
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
void SortingManager::resetData() {
    comparisons = 0;
    swaps = 0;
    data = originalData; // Restaura o vetor original
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

// QuickSort
void SortingManager::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int SortingManager::partition(int low, int high) {
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (data[j] < pivot) {
            swaps++;
            i++;
            swap(data[i], data[j]);
        }
    }
    swaps++;
    swap(data[i + 1], data[high]);
    return (i + 1);
}

// HeapSort
void SortingManager::heapSort() {
    int n = data.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
    for (int i = n - 1; i > 0; i--) {
        swaps++;
        swap(data[0], data[i]);
        heapify(i, 0);
    }
}

void SortingManager::heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    comparisons++;
    if (left < n && data[left] > data[largest])
        largest = left;

    comparisons++;
    if (right < n && data[right] > data[largest])
        largest = right;

    if (largest != i) {
        swaps++;
        swap(data[i], data[largest]);
        heapify(n, largest);
    }
}

// Radix Sort
void SortingManager::radixSort() {
    int maxVal = *max_element(data.begin(), data.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortForRadix(exp);
}

void SortingManager::countingSortForRadix(int exp) {
    int n = data.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(data[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(data[i] / exp) % 10] - 1] = data[i];
        count[(data[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        data[i] = output[i];
}

// Bucket Sort
void SortingManager::bucketSort() {
    int n = data.size();
    vector<int> bucket[n];

    for (int i = 0; i < n; i++) {
        int idx = data[i] * n / (10000 + 1);
        bucket[idx].push_back(data[i]);
    }

    for (int i = 0; i < n; i++)
        sort(bucket[i].begin(), bucket[i].end());

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            data[index++] = bucket[i][j];
        }
    }
}

// Counting Sort
void SortingManager::countingSort() {
    int maxVal = *max_element(data.begin(), data.end());
    vector<int> count(maxVal + 1, 0);
    vector<int> output(data.size());

    for (int i = 0; i < data.size(); i++)
        count[data[i]]++;

    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i - 1];

    for (int i = data.size() - 1; i >= 0; i--) {
        output[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }

    for (int i = 0; i < data.size(); i++)
        data[i] = output[i];
}

// Função para realizar a ordenação com base na escolha do usuário
void SortingManager::sortData(int algorithmType, int algorithmChoice) {
    auto start = high_resolution_clock::now();

    if (algorithmType == 1) {
        if (algorithmChoice == 1) bubbleSort();
        else if (algorithmChoice == 2) selectionSort();
        else insertionSort();
    } else if (algorithmType == 2) {
        if (algorithmChoice == 1) quickSort(0, data.size() - 1);
        else if (algorithmChoice == 2) heapSort();
        else mergeSort(0, data.size() - 1);
    } else if (algorithmType == 3) {
        if (algorithmChoice == 1) radixSort();
        else if (algorithmChoice == 2) bucketSort();
        else countingSort();
    }

    auto end = high_resolution_clock::now();
    double duration = duration_cast<microseconds>(end - start).count();
    printResults(duration);
}

// Função para imprimir os resultados
void SortingManager::printResults(double time) {
    cout << "Comparações: " << comparisons << endl;
    cout << "Trocas: " << swaps << endl;
    cout << "Tempo de execução: " << time << " microssegundos" << endl;
}
