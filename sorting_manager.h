#ifndef SORTING_MANAGER_H
#define SORTING_MANAGER_H

#include <vector>

class SortingManager {
private:
    std::vector<int> data;   // Vetor de dados
    int comparisons;         // Contador de comparações
    int swaps;               // Contador de trocas

    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void mergeSort(int left, int right);
    void quickSort(int left, int right);
    void heapSort();
    void radixSort();
    void bucketSort();
    void countingSort();
    void merge(int left, int mid, int right);
    int partition(int left, int right);
    void heapify(int n, int i);

public:
    SortingManager(int size, bool descending);   // Inicializa os dados
    void displayData() const;                    // Exibe os dados
    void sortData(int algorithmType, int algorithmChoice);  // Realiza a ordenação
    void printResults(double time);              // Exibe os resultados (tempo, comparações e trocas)
    void resetData(bool descending);             // Reseta os dados para nova execução
};

#endif
