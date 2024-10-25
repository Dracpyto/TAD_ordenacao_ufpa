#include "sorting_manager.h"
#include <iostream>

using namespace std;

/*

Discente: Adan Alexey Mafra de Meneses
Matricula: 202311140032
Doscente: Denis Lima do Rosário 

*/



int main() {
    int size;
    char descendingChoice;
    bool descending = false;

    cout << "Digite o tamanho do vetor: ";
    cin >> size;

    cout << "Deseja ordenar o vetor em ordem decrescente? (s/n): ";
    cin >> descendingChoice;
    if (descendingChoice == 's' || descendingChoice == 'S') {
        descending = true;
    }

    SortingManager manager(size, descending);
    
    cout << "Vetor original:\n";
    manager.displayData();

    // Escolha de 3 algoritmos de diferentes grupos
    for (int i = 1; i <= 3; i++) {
        int algorithmChoice;

        if (i == 1) {
            cout << "Escolha um algoritmo: Bubblesort(1), Selectionsort(2), Insertionsort(3): ";
        } else if (i == 2) {
            cout << "Escolha um algoritmo: Mergesort(1), Quicksort(2), Heapsort(3): ";
        } else {
            cout << "Escolha um algoritmo: Radixsort(1), Bucketsort(2), Countingsort(3): ";
        }
        cin >> algorithmChoice;

        // Reseta o vetor para o estado original antes de cada ordenação
        manager.resetData();

        // Executa a ordenação com base na escolha do usuário
        manager.sortData(i, algorithmChoice);

        // Exibe o vetor ordenado
        cout << "\nVetor ordenado pelo algoritmo " << i << ":\n";
        manager.displayData();
        cout << endl;
    }

    return 0;
}
