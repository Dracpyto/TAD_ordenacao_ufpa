#ifndef SORTING_MANAGER_H
#define SORTING_MANAGER_H

#include <vector>
using namespace std;

class SortingManager {
private:
    vector<int> data;     // Vetor de dados a serem ordenados
    vector<int> originalData; // Vetor original para reset
    int comparisons;      // Contador de comparações
    int swaps;            // Contador de trocas

    // Funções de suporte para ordenações específicas
    void merge(int left, int mid, int right);
    int partition(int low, int high);
    void heapify(int n, int i);
    void countingSortForRadix(int exp);

public:
    SortingManager(int size, bool descending); // Construtor

    // Funções de exibição e reset de dados
    void displayData() const;
    void resetData(); // Reset para o estado original

    // Algoritmos de ordenação
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void mergeSort(int left, int right);
    void quickSort(int low, int high);
    void heapSort();
    void radixSort();
    void bucketSort();
    void countingSort();

    // Função para realizar a ordenação com base na escolha do usuário
    void sortData(int algorithmType, int algorithmChoice);

    // Função para imprimir os resultados
    void printResults(double time);
};

#endif
