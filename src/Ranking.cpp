#include "Ranking.hpp"

void quickSort(ParOrdenacao* arr, int inicio, int fim) {
    if (inicio >= fim) return;

    // pivô central evita O(n^2) em listas quase ordenadas
    int meio = inicio + (fim - inicio) / 2;
    ParOrdenacao pivot = arr[meio];
    
    int i = inicio;
    int j = fim;

    while (i <= j) {
        while ((arr[i].pontuacao > pivot.pontuacao) || 
               (arr[i].pontuacao == pivot.pontuacao && arr[i].id < pivot.id)) {
            i++;
        }
        
        while ((arr[j].pontuacao < pivot.pontuacao) || 
               (arr[j].pontuacao == pivot.pontuacao && arr[j].id > pivot.id)) {
            j--;
        }

        if (i <= j) {
            ParOrdenacao temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    if (inicio < j) quickSort(arr, inicio, j);
    if (i < fim) quickSort(arr, i, fim);
}