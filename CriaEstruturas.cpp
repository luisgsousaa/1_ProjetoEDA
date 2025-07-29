#include <iostream>
#include <string>
#include "funcoes.h"
#include "CriaEstruturas.h"

using namespace std;


/**
 * Luis
 * Esta função cria as seccoes do armazem e guarda-as num array
 * @param seccoes_array Array dinamico com o tamanho dado pela função n_seccoes() para decidir o numero de secções, este array contém as secções
 * @param numero_de_seccoes O numero de secções dado pela funcção n_seccoes()
 * @param categorias_pecas Array com o tamanho dado pela função n_seccoes() para guardar apenas as categorias usadas nas secções.
 * O Ciclo for preenche o array seccoes_array com cada seccao e as suas caracteristicas , usando as funcoes definifidas em funcoes.cpp
 * temp_categorias guarda a categoria que a seccao que está a ser criada vai ter, e depois adiciona essa categoria ao array categorias_pecas
 * É inicializado o tamanho do array de numeros de serie vendidos usando o valor fixo 10, este array irá crescer tendo em conta a necessidade do programa
 * É inicializado o tamanho do array das peças onde estas irão ser postas usando a capacidade da propria secção
 */
void cria_seccoes(seccao seccoes_array[],int numero_de_seccoes, string*& categorias_pecas){
    string temp_categorias;
    for (int i = 0; i < numero_de_seccoes; ++i) {
        temp_categorias = categoria_aleatoria();
        seccoes_array[i] = {n_capacidade(),0,cria_id(),0, nullptr,0,10,temp_categorias};
        seccoes_array[i].num_serie_vendidos = new int[seccoes_array[i].tamanho_num_serie];
        seccoes_array[i].pecas_seccao = new pecas[seccoes_array[i].capacidade];
        for (int j = 0; j < seccoes_array[i].capacidade; ++j) { //inicializa as pecas da seccao com valores vazios
            seccoes_array[i].pecas_seccao[j] = {"","",0,0,0};
        }
        categorias_pecas[i] = temp_categorias;
    }

}

/** Cria uma nova peça com valores aleatórios
 * Esta função cria uma nova peça com valores aleatórios para marca, categoria, preço, probabilidade de venda
 * e número de série. A marca é gerada aleatoriamente, a categoria é escolhida entre as categorias disponíveis,
 * o preço é definido aleatoriamente, a probabilidade de venda é calculada e o número de série é atribuído.
 * @param categorias_pecas Um array de strings contendo as categorias de peças disponíveis
 * @param numero_de_seccoes O número total de secções disponíveis
 * @return Uma estrutura de peças contendo os valores gerados para a nova peça
 */
pecas criaPeca(string categorias_pecas[],int numero_de_seccoes){
    pecas nova;
    nova.marca = marca_aleatoria();
    nova.categoria = categorias_usadas(categorias_pecas,numero_de_seccoes);
    nova.preco = preco();
    nova.prob_venda = prob_venda();
    nova.num_serie=num_serie();
    nova.tem_promocao = false;
    return nova;
}

