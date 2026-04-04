#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>

class Acao {
private:
    int id;         
    double* cotacoes;
    int capacidade; //tamanho do array de cotações
    int num_cotacoes;

    void redimensionarArray(); // função para redimensionar o array de cotações quando necessário

public:
    Acao(); // construtor padrão
    Acao(int id_acao);
    ~Acao(); //destrutor

    void setId(int id_acao);
    int getId() const;
    int getNumCotacoes() const;

    void adicionarCotacao(double preco);

    double calcularRET(int w) const;
    double calcularAVGRET(int w) const;
    double calcularSTAB(int w) const;
    double calcularCONS(int w) const;
};

#endif 