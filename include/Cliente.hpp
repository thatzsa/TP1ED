#ifndef CLIENTE_HPP
#define CLIENTE_HPP

class Cliente {
private:
    int id;
    int* carteira; // ações compradas
    int capacidade; // tamanho do array da carteira
    int num_acoes;

    void redimensionarCarteira(); // função para redimensionar o array da carteira quando necessário

public:
    Cliente(); // construtor padrão
    Cliente(int id_cliente);
    ~Cliente(); //destrutor

    void setId(int id_cliente);
    int getId() const;
    int getNumAcoes() const;

    int getAcao(int indice) const;

    void adicionarAcao(int id_acao); //operação de compra

    void removerAcao(int id_acao);//operação de venda
};

#endif