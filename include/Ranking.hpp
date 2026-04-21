#pragma once

struct ParOrdenacao {
    double pontuacao;
    int id;
};

void quickSort(ParOrdenacao* arr, int inicio, int fim);