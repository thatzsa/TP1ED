#include "Acao.hpp"
#include <cmath> 

Acao::Acao() {
    id = -1; //ação ainda não foi inicializada com um ID válido
    capacidade = 10;
    num_cotacoes = 0;
    cotacoes = new double[capacidade];
}

Acao::Acao(int id_acao) {
    id = id_acao;
    capacidade = 10;
    num_cotacoes = 0;
    cotacoes = new double[capacidade];
}

Acao::~Acao() {
    delete[] cotacoes;
}

void Acao::setId(int id_acao) {
    id = id_acao;
}

int Acao::getId() const { return id; }
int Acao::getNumCotacoes() const { return num_cotacoes; }

// parte gerenciamento de cotações/preços

void Acao::redimensionarArray() {
    capacidade *= 2;
    double* novo_array = new double[capacidade];
    
    for (int i = 0; i < num_cotacoes; i++) {
        novo_array[i] = cotacoes[i];
    }
    
    delete[] cotacoes;
    cotacoes = novo_array;
}

void Acao::adicionarCotacao(double preco) {
    if (num_cotacoes == capacidade) {
        redimensionarArray();
    }
    cotacoes[num_cotacoes] = preco;
    num_cotacoes++;
}

// métricas

double Acao::calcularRET(int w) const {
    if (num_cotacoes < w) return 0.0;

    int indice_p0 = num_cotacoes - w;
    int indice_pw_minus_1 = num_cotacoes - 1;

    double p_0 = cotacoes[indice_p0];
    double p_w_minus_1 = cotacoes[indice_pw_minus_1];

    return (p_w_minus_1 / p_0) - 1.0; 
}

double Acao::calcularAVGRET(int w) const {
    if (num_cotacoes < w) return 0.0;

    double soma_retornos = 0.0;
    int base = num_cotacoes - w;

    for (int i = 1; i < w; i++) {
        double p_i = cotacoes[base + i];
        double p_i_minus_1 = cotacoes[base + i - 1];

        double r_i = (p_i / p_i_minus_1) - 1.0; 
        soma_retornos += r_i;
    }

    return soma_retornos / (w - 1); 
}

double Acao::calcularSTAB(int w) const {
    if (num_cotacoes < w) return 0.0;

    // reaproveitar método AVGRET pra STAB pq STAB usa AVGRET no cálculo da volatilidade
    double r_barra = calcularAVGRET(w); 
    double soma_variancia = 0.0;
    int base = num_cotacoes - w;

    for (int i = 1; i < w; i++) {
        double p_i = cotacoes[base + i];
        double p_i_minus_1 = cotacoes[base + i - 1];
        double r_i = (p_i / p_i_minus_1) - 1.0;
        
        // Somatório
        soma_variancia += (r_i - r_barra) * (r_i - r_barra); 
    }

    double vol_w = std::sqrt(soma_variancia / (w - 1)); 

    return 1.0 / (1.0 + vol_w); 
}

double Acao::calcularCONS(int w) const {
    if (num_cotacoes < w) return 0.0;

    int contagem_positivos = 0;
    int base = num_cotacoes - w;

    for (int i = 1; i < w; i++) {
        double p_i = cotacoes[base + i];
        double p_i_minus_1 = cotacoes[base + i - 1];
        double r_i = (p_i / p_i_minus_1) - 1.0;
        
        if (r_i > 0.0) {
            contagem_positivos++; 
        }
    }

    return (double)contagem_positivos / (w - 1); 
}