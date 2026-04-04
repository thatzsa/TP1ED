#include <iostream>
#include <string>
#include <sstream>
#include "Acao.hpp"
#include "Cliente.hpp"

using std::cin;
using std::cout;
using std::string;
using std::getline;
using std::stringstream;

int main() {
    // Otimização de I/O em C++ para ler arquivos grandes mais rapidamente
    //std::ios_base::sync_with_stdio(false);
   // cin.tie(NULL);
   // talvez eu use 

    char tipo_linha;
    int w = 0;
   
    string metricas_globais[4]; 
    int num_metricas_globais = 0;

    while (cin >> tipo_linha) {
        
        if (tipo_linha == 'M') {
            cin >> w; 
            
            string resto_da_linha;
            getline(cin, resto_da_linha);
            stringstream ss(resto_da_linha);
            string metrica;
            
            // Extrai cada métrica da linha e guarda no array
            while (ss >> metrica) {
                metricas_globais[num_metricas_globais] = metrica;
                num_metricas_globais++;
            }
                        
        } 
        else if (tipo_linha == 'A') {
            int id_acao;
            cin >> id_acao;
        } 
        else if (tipo_linha == 'U') {
            int id_cliente;
            cin >> id_cliente;
        } 
        else if (tipo_linha == 'P') {
            int id_acao;
            double preco;
            cin >> id_acao >> preco;
            
            // IMPORTANTE: Se você estiver usando a "Estratégia Imediata",
            // é aqui que você deve atualizar os rankings globais!
        } 
        else if (tipo_linha == 'B') {
            int id_cliente, id_acao;
            cin >> id_cliente >> id_acao;
            // A ação passa a pertencer à carteira do cliente
        } 
        else if (tipo_linha == 'V') {
            int id_cliente, id_acao;
            cin >> id_cliente >> id_acao;
            // A ação é removida da carteira do cliente
        } 
        else if (tipo_linha == 'Q') {
            int id_consulta, id_cliente, n, m;
            cin >> id_consulta >> id_cliente >> n >> m; 
            
            string* metricas_consulta = new string[m];
            double* pesos_consulta = new double[m];
            
            for (int i = 0; i < m; i++) {
                cin >> metricas_consulta[i] >> pesos_consulta[i];
            }
            
            // LÓGICA DA CONSULTA VEM AQUI:
            // 1. Se for "Estratégia Sob Demanda", reconstrua os rankings aqui.
            // 2. Calcule os pontos e pesos 
            // 3. Imprima as linhas 'R' formatadas com 2 casas decimais

            delete[] metricas_consulta;
            delete[] pesos_consulta;
        }
    }

    return 0;
}