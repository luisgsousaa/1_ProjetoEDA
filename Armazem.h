#ifndef ARMAZEM_H
#define ARMAZEM_H
#include "CriaEstruturas.h"
using namespace std;



void armazem_EDA(pecas*& lista_chegada,int num, seccao*& seccoes_array, int& numero_de_seccoes,string*& categorias_pecas);
void menu_gestao();
void menu(pecas*& lista_chegada,int num, seccao*& seccoes_array, int& numero_de_seccoes,string*& categorias_pecas);
void dia_seguinte(pecas*& lista_chegada,int num, seccao*& seccoes_array, int numero_de_seccoes, string *&categorias_pecas);
void imprime_numeros_serie(seccao*& seccoes_array, int numero_de_seccoes);
void voltar_ao_menu();
void vende_peca(pecas*& lista_chegada, int num, seccao *& seccoes_array, int numero_de_seccoes);
void criar_nova_seccao(seccao*& seccoes_array,int& numero_de_seccoes, string*& categorias_pecas);
void aplica_desconto(seccao *& seccoes_array, int numero_de_seccoes);
void alterar_categoria(seccao*& seccoes_array,int& numero_de_seccoes, string*& categorias_pecas, pecas*& lista_chegada);
void retira_desconto (seccao *& seccoes_array, int numero_de_seccoes);
void imprime_armazem(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes);
void verifica_promo (seccao *& seccoes_array, int numero_de_seccoes);
void grava_armazem (seccao*& seccoes_array,pecas*& lista_chegada, int& numero_de_seccoes);
void carrega_armazem(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes, string *& categorias_pecas);
#endif //ARMAZEM_H
