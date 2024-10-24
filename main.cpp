#include "sorting_manager.h"
#include <iostream>

/*

Discente: Adan Alexey Mafra de Meneses
Matrícula: 202311140032
Doscente: Denis Lima Ferreira 

*/

using namespace std;

int main() {
    int size, orderOption, algorithmType, algorithmChoice;

    // Escolher o tamanho do vetor
    cout << "Escolha a quantidade de valores (10, 100, 1000, 10000): ";
    cin >> size;

    // Escolher a disposição inicial (aleatório ou descendente)
    cout << "Escolha a disposição dos valores (0 - aleatório, 1 - descendente): ";
    cin >> orderOption;
    bool descending = (orderOption == 1);

    // Criar o gerenciador de ordenação
    SortingManager manager(size, descending);

    // Exibir os valores iniciais
    cout << "Vetor inicial: ";
    manager.displayData();

    // Executar três escolhas de algoritmos
    for (int i = 1; i <= 3; ++i) {
        cout << "Escolha o tipo de algoritmo para grupo " << i << ":\n";
        if (i == 1) {
            cout << "1 - Bubblesort, 2 - Selectionsort, 3 - Insertionsort\n";
        } else if (i == 2) {
            cout << "1 - Mergesort, 2 - Quicksort, 3 - Heapsort\n";
        } else {
            cout << "1 - Radixsort, 2 - Bucketsort, 3 - Countingsort\n";
        }
        cin >> algorithmChoice;

        // Ordenar os dados com o algoritmo escolhido
        manager.sortData(i, algorithmChoice);

        // Resetar os dados após a execução do algoritmo
        manager.resetData(descending);
    }

    return 0;
}
