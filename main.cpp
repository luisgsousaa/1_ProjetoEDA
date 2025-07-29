#include <iostream>
#include "funcoes.h"
#include "CriaEstruturas.h"
#include "Armazem.h"
#include <stdlib.h>
#include <time.h>





int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (argc==5){
        /**Luis
         * Para inicializar o armazem a partir de um estado guardado anteriormente em ficheiros é necessário passar os caminhos dos 4 ficheiros como argumentos,
         * com um espaço entre cada um, a ordem dos ficheiros passados nos argumentos é irrelevante.
         *
         * Esta porção do codigo apenas é corrida se a quantidade de argumentos for igual a 5, ou seja o caminho do projeto mais os 4 caminhos dos ficheiros para carregar o armazém
         * É incializado os ponteiros para os arrays/variaveis necessários ao armazém que irão ser apontados para os arays criados apartir dos ficheiros lidos.
         * É chamda a função que lê o ficheiro das marcas para poderem ser criadas novas peças.
         * Por fim é chamadada a função menu e o armazém aparece já com o estado guardado nos ficheiros.
         */
        int numero_de_seccoes;
        seccao * seccoes_array;
        string * categorias_pecas;
        pecas * lista_chegada;
        le_ficheiro_marcas();
        carrega_por_argumentos(lista_chegada,seccoes_array,numero_de_seccoes,categorias_pecas,argv);
        menu(lista_chegada,ocupacao_lista_chegada, seccoes_array, numero_de_seccoes,categorias_pecas);

    }
    else{
        /** Luis
     * @param numero_de_seccoes numero aleatorio gerado por n_seccoes() que irá dar o tamanho dos arrays dinamicos que guardam as secções e as categorias em uso no armazem
     * @param seccoes_array array dinamico do tipo seccao que irá guardar cada secção
     * @param categorias_pecas array dinamico do tipo string que guarda as categorias usadas nas secções de modo a apenas criar peças com as categorias em uso
     * Leitura dos ficheiros e inicializacao das secções
     * Chamada à função do menu.
     */
        int numero_de_seccoes = n_seccoes();
        seccao * seccoes_array = new seccao[numero_de_seccoes];
        string * categorias_pecas = new string[numero_de_seccoes];
        ler_ficheiros_e_inicicializar_seccoes(seccoes_array,numero_de_seccoes,categorias_pecas);
        pecas * lista_chegada = new pecas[50];

        inicializar_lista_chegada(lista_chegada,categorias_pecas,numero_de_seccoes);

        menu(lista_chegada,ocupacao_lista_chegada, seccoes_array, numero_de_seccoes,categorias_pecas);
    }
    return 0;
}
