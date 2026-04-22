#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Acao.hpp"
#include "Cliente.hpp"
#include "Ranking.hpp"

using std::cin;
using std::cout;
using std::string;
using std::getline;
using std::stringstream;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    // Otimização de I/O em C++ para ler arquivos grandes mais rapidamente
    //std::ios_base::sync_with_stdio(false);
   // cin.tie(NULL);
   // talvez eu use 

    char tipo_linha;
    int w = 0;
   
    string metricas_globais[4]; 
    int num_metricas_globais = 0;

    int capacidade_acoes = 1000;
    Acao* vetor_acoes = new Acao[capacidade_acoes];
    int total_acoes_cadastradas = 0;

    int capacidade_clientes = 1000;
    Cliente* vetor_clientes = new Cliente[capacidade_clientes];

    // 0 = Sob Demanda || 1 = Imediata
    int estrategia = 0; 
    
    if (argc > 1) {
        string arg = argv[1];
        if (arg == "imediata") {
            estrategia = 1;
        }
    }

    // todas p análise experimental
    double tempo_total = 0;
    double tempo_cotacoes = 0;
    double tempo_consultas = 0;
    int total_cotacoes = 0;
    int total_consultas = 0;
    int reconstrucoes_ranking = 0;
    int total_clientes_cadastrados = 0;

    while (cin >> tipo_linha) {
        
        if (tipo_linha == 'M') {
            cin >> w; 
            
            string resto_da_linha;
            getline(cin, resto_da_linha);
            stringstream ss(resto_da_linha);
            string metrica;
            
            // extrai cada métrica e guarda no array
            while (ss >> metrica) {
                metricas_globais[num_metricas_globais] = metrica;
                num_metricas_globais++;
            }
                        
        } 
        else if (tipo_linha == 'A') {
            int id_acao;
            cin >> id_acao;

            // Verifica se o ID da ação é maior ou igual à capacidade atual do vetor de ações e redimensiona o vetor
            if (id_acao >= capacidade_acoes) {
                int nova_capacidade = capacidade_acoes * 2 + id_acao;
                Acao* novo_vetor = new Acao[nova_capacidade];
                for(int i = 0; i < capacidade_acoes; i++) novo_vetor[i] = vetor_acoes[i];
                delete[] vetor_acoes;
                vetor_acoes = novo_vetor;
                capacidade_acoes = nova_capacidade;
            }

            vetor_acoes[id_acao].setId(id_acao);

            // Atualiza o total de ações cadastradas
            if (id_acao >= total_acoes_cadastradas) {
                total_acoes_cadastradas = id_acao + 1;
            }
        }
        else if (tipo_linha == 'U') {
            int id_cliente;
            cin >> id_cliente;

            // Verifica se o ID do cliente é maior ou igual à capacidade atual do vetor de clientes e redimensiona o vetor
            if (id_cliente >= capacidade_clientes) {
                int nova_capacidade = capacidade_clientes * 2 + id_cliente;
                Cliente* novo_vetor = new Cliente[nova_capacidade];
                for(int i = 0; i < capacidade_clientes; i++) novo_vetor[i] = vetor_clientes[i];
                delete[] vetor_clientes;
                vetor_clientes = novo_vetor;
                capacidade_clientes = nova_capacidade;
            }
            vetor_clientes[id_cliente].setId(id_cliente);

            if (id_cliente >= total_clientes_cadastrados) {
                total_clientes_cadastrados = id_cliente + 1;
            }

        }
        else if (tipo_linha == 'P') {
            int id_acao;
            double preco;
            cin >> id_acao >> preco;

            // tempo p analise experimental
            auto inicio_p = std::chrono::high_resolution_clock::now();

            // Vai até a ação no vetor de ações e adiciona a cotação
            vetor_acoes[id_acao].adicionarCotacao(preco);

            auto fim_p = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duracao = fim_p - inicio_p;
            tempo_cotacoes += duracao.count();
            total_cotacoes++;

        }

        else if (tipo_linha == 'B') {
            int id_cliente, id_acao;
            cin >> id_cliente >> id_acao;

            // add a ação na carteira do cliente
            vetor_clientes[id_cliente].adicionarAcao(id_acao);
        } 
        else if (tipo_linha == 'V') {
            int id_cliente, id_acao;
            cin >> id_cliente >> id_acao;

            // remove a ação da carteira do cliente} 
            vetor_clientes[id_cliente].removerAcao(id_acao);
        }
        else if (tipo_linha == 'Q') {

            // tempo p/ analise experimental
            auto inicio_q = std::chrono::high_resolution_clock::now();

            int id_consulta, id_cliente, n, m;
            cin >> id_consulta >> id_cliente >> n >> m; 
            
            string* metricas_consulta = new string[m];
            double* pesos_consulta = new double[m];
            
            // Lê quais métricas serão avaliadas e seus respectivos pesos
            for (int i = 0; i < m; i++) {
                cin >> metricas_consulta[i] >> pesos_consulta[i];
            }

            int N = total_acoes_cadastradas;
            double* pontuacoes_globais = new double[N];
            
            // Zera as pontuações antes de começar
            for (int i = 0; i < N; i++) {
                pontuacoes_globais[i] = 0.0;
            }

            ParOrdenacao* ranking_temporario = new ParOrdenacao[N];

            // Para cada métrica pedida
            for (int i = 0; i < m; i++) {
                string metrica_atual = metricas_consulta[i];
                double peso_atual = pesos_consulta[i];

                // Calcula o valor da métrica para todas as N ações
                for (int j = 0; j < N; j++) {
                    ranking_temporario[j].id = j;
                    
                    if (metrica_atual == "RET") {
                        ranking_temporario[j].pontuacao = vetor_acoes[j].calcularRET(w);
                    } else if (metrica_atual == "AVGRET") {
                        ranking_temporario[j].pontuacao = vetor_acoes[j].calcularAVGRET(w);
                    } else if (metrica_atual == "STAB") {
                        ranking_temporario[j].pontuacao = vetor_acoes[j].calcularSTAB(w);
                    } else if (metrica_atual == "CONS") {
                        ranking_temporario[j].pontuacao = vetor_acoes[j].calcularCONS(w);
                    }
                }

                // Ordena o ranking dessa métrica usando o meu quicksort
                quickSort(ranking_temporario, 0, N - 1);

                // Distribui os pontos: (N - posicao) multiplicado pelo peso
                for (int posicao = 0; posicao < N; posicao++) {
                    int id_da_acao = ranking_temporario[posicao].id;
                    pontuacoes_globais[id_da_acao] += (double)(N - posicao) * peso_atual;
                }
            }

            // filtro apenas as ações que o cliente tem e monto o ranking
            Cliente& cliente = vetor_clientes[id_cliente];
            int num_na_carteira = cliente.getNumAcoes();

            if (num_na_carteira > 0) {
                ParOrdenacao* carteira_rankeada = new ParOrdenacao[num_na_carteira];

                for (int i = 0; i < num_na_carteira; i++) {
                    int id_acao = cliente.getAcao(i);
                    carteira_rankeada[i].id = id_acao;
                    carteira_rankeada[i].pontuacao = pontuacoes_globais[id_acao];
                }

                // Ordena a carteira usando as pontuações globais somadas
                quickSort(carteira_rankeada, 0, num_na_carteira - 1);

                // imprimir 
                std::cout << std::fixed << std::setprecision(2);
                
                // Evita tentar imprimir mais ações do que o cliente possui na carteira
                int quantidade_imprimir = (n < num_na_carteira) ? n : num_na_carteira;

                // Imprime as melhores ações
                for (int i = 0; i < quantidade_imprimir; i++) {
                    std::cout << "R " << id_consulta << " M " << i << " " 
                              << carteira_rankeada[i].id << " " 
                              << carteira_rankeada[i].pontuacao << "\n";
                }

                // Imprime as piores ações
                for (int i = 0; i < quantidade_imprimir; i++) {
                    int indice_pior = (num_na_carteira - 1) - i;
                    std::cout << "R " << id_consulta << " P " << i << " " 
                              << carteira_rankeada[indice_pior].id << " " 
                              << carteira_rankeada[indice_pior].pontuacao << "\n";
                }

                delete[] carteira_rankeada;
            }

            delete[] pontuacoes_globais;
            delete[] ranking_temporario;
            delete[] metricas_consulta;
            delete[] pesos_consulta;

            auto fim_q = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duracao = fim_q - inicio_q;
            tempo_consultas += duracao.count();
        }
    }

    std::cout << "\nESTATISTICAS," 
              << estrategia << "," 
              << total_acoes_cadastradas << "," 
              << total_clientes_cadastrados << "," 
              << tempo_cotacoes << "," 
              << tempo_consultas << "," 
              << reconstrucoes_ranking << "\n";


    delete[] vetor_acoes;
    delete[] vetor_clientes;
    return 0;
}