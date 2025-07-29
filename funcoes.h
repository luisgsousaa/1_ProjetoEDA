using namespace std;
#include "CriaEstruturas.h"
int n_seccoes();
int n_capacidade();
float preco();
int num_serie();
float prob_venda();
void le_ficheiro_marcas();
string marca_aleatoria();
void le_ficheiro_categorias();
string categoria_aleatoria();
string categorias_usadas(string categorias_pecas[],int numero_de_seccoes);
extern char id;
char cria_id();
void ler_ficheiros_e_inicicializar_seccoes(seccao seccoes_array[],int numero_de_seccoes, string*& categorias_pecas);
pecas f_lista_chegada();
extern int ocupacao_lista_chegada;
void inicializar_lista_chegada(pecas*& lista_chegada, string categorias_pecas[],int numero_de_seccoes);
void troca (pecas &a, pecas &b);
void organizarLC_5pecas(pecas*& lista_chegada, int num, string categorias_pecas[],int numero_de_seccoes);
void inserir_elemento(pecas array[], int tamanho, int posicao, pecas elemento);
void retirar_elemento(pecas*& array, int tamanho, int posicao);
void adiciona_peca(pecas*& lista_chegada,int num, seccao*& seccoes_array, int numero_de_seccoes);
void prob_venda_geral (seccao*& seccoes_array, int numero_de_seccoes);
extern float facturacao_total_armazem;
void retirar_peca(seccao &array, int posicao);
extern int dia;
void carrega_por_argumentos(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes, string *& categorias_pecas, char *argv[]);

