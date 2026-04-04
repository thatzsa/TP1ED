#include "Cliente.hpp"

Cliente::Cliente() {
    id = -1; //cliente ainda não foi inicializado com um ID válido
    capacidade = 10;
    num_acoes = 0;
    carteira = new int[capacidade];
}

Cliente::Cliente(int id_cliente) {
    id = id_cliente;
    capacidade = 10;
    num_acoes = 0;
    carteira = new int[capacidade];
}

Cliente::~Cliente() {
    delete[] carteira;
}

void Cliente::setId(int id_cliente) {
    id = id_cliente;
}

int Cliente::getId() const { return id; }
int Cliente::getNumAcoes() const { return num_acoes; }

// pra iterar pela carteira do cliente durante a consulta
int Cliente::getAcao(int indice) const {
    if (indice >= 0 && indice < num_acoes) {
        return carteira[indice];
    }
    return -1;
}

// parte gerenciamento da carteira de ações


void Cliente::redimensionarCarteira() {
    capacidade *= 2;
    int* nova_carteira = new int[capacidade];
    
    for (int i = 0; i < num_acoes; i++) {
        nova_carteira[i] = carteira[i];
    }
    
    delete[] carteira;
    carteira = nova_carteira;
}

void Cliente::adicionarAcao(int id_acao) {
    if (num_acoes == capacidade) {
        redimensionarCarteira();
    }
    carteira[num_acoes] = id_acao;
    num_acoes++;
}

void Cliente::removerAcao(int id_acao) {
    for (int i = 0; i < num_acoes; i++) {
        if (carteira[i] == id_acao) {
            
            //ID da última posição da carteira vai pra posição do elemento excluído
            carteira[i] = carteira[num_acoes - 1];

            num_acoes--;
            
            break;
        }
    }
}