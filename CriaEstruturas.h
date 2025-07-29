#ifndef CRIA_ESTRUTURAS_H
#define CRIA_ESTRUTURAS_H


using namespace std;
struct pecas{
    string marca;
    string categoria;
    float preco;
    float prob_venda;
    int num_serie;
    bool tem_promocao;
};

struct seccao{
    int capacidade;
    int quantidade;
    char id;
    float total_facturacao;
    int* num_serie_vendidos;
    int quantidade_vendida;  // quantidade de peçcas vendidas na seccao
    int tamanho_num_serie;  // tamanho do array dos num serie
    string categoria;
    pecas* pecas_seccao;
    int dias_promocao;
    int inicio_promocao;
    float valor_prom;
    bool promocao_ativa;
};

void cria_seccoes(seccao seccoes_array[],int tamanho_seccoes, string*& categorias_pecas);
pecas criaPeca(string categorias_pecas[],int numero_de_seccoes);

#endif CRIA_ESTRUTURAS_H