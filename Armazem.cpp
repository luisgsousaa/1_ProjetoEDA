#include <iostream>
#include "Armazem.h"
#include "funcoes.h"
#include <iomanip>
#include <fstream>
#include "CriaEstruturas.h"

using namespace std;



/** Função que imprime o menu armazem EDA e a lista de chegada atual // André
*A função imprime o menu do armazém EDA, com o dia atual e a faturação total do armazém.
*De seguida, imprime as secções do armazém, com o ID, categoria, capacidade, quantidade, total de faturação e se está em promoção.
*Por fim, imprime a lista de chegada, com a marca, categoria, preço e número de série das peças.
*@param lista_chegada Lista de chegada de peças
*@param num Tamanho da lista de chegada
*@param seccoes_array Array de secções
*@param numero_de_seccoes Número de secções no array
*@param categorias_pecas Array de categorias de peças
*/
void armazem_EDA(pecas*& lista_chegada,int num, seccao*& seccoes_array, int& numero_de_seccoes, string *& categorias_pecas) {
    cout << setw(60) << "************************************************" << endl;
    cout << setw(32) << "Armazem EDA | Dia "<< dia <<" |Total Faturacao "<< facturacao_total_armazem << endl;
    cout << setw(60) << "************************************************" << endl;

    for (int i = 0; i <numero_de_seccoes; ++i) {
        string prom = " ";
        if (seccoes_array[i].promocao_ativa){
            prom = "Em promocao";
        }
        cout << endl << "ID: " << seccoes_array[i].id
             << " | Categoria: " << seccoes_array[i].categoria
             << " | Capacidade: " << seccoes_array[i].capacidade
             << " | Quantidade: " << seccoes_array[i].quantidade
             << " | Total Facturacao: " << seccoes_array[i].total_facturacao
             << " | " << prom  << endl;
        for (int j = 0; j < seccoes_array[i].quantidade; ++j) {
            cout << " - " << seccoes_array[i].pecas_seccao[j].marca
                 << " | " << seccoes_array[i].pecas_seccao[j].categoria
                 << " | " << seccoes_array[i].pecas_seccao[j].preco
                 << " | " << seccoes_array[i].pecas_seccao[j].num_serie
                 << "\n";
        }
    }
    cout << "" << endl;
    cout << setw(60) << "****************************************" << endl;
    cout << setw(60) << "********** Lista de Chegada ************" << endl;
    cout << setw(60) << "****************************************" << endl;
    cout << "" << endl;

    cout << "Marca | categoria | Preco | Numero de serie " << endl;
    cout <<""<<endl;
    for(int i=0;i<ocupacao_lista_chegada;i++){
        if (lista_chegada[i].preco == -1)
            break;
        cout << lista_chegada[i].marca
        << " | " << lista_chegada[i].categoria
        << " | " << lista_chegada[i].preco
        << " | " << lista_chegada[i].num_serie
        << endl;

    }
}

void menu_gestao() {
    cout << "(1). Venda Manual" << endl;
    cout << "(2). Promocao" << endl;
    cout << "(3). Alterar categoria" << endl;
    cout << "(4). Adicionar seccao" << endl;
    cout << "(5). Numeros de Serie das Pecas Vendidas" << endl;
    cout << "(6). Gravar Armazem" << endl;
    cout << "(7). Carregar Armazem" << endl;
    cout << "(8). Imprimir Armazem" << endl;
    cout << "(0). Sair" << endl;
    cout << "Selecione a sua opcao: ";
}

/** Menu principal do armazém EDA
*
* A função menu é a função principal do armazém EDA, onde primeiramente é chamada a função armazem_EDA para imprimir as opções disponíveis.
* Inserindo 's', é chamada a função dia_seguinte para simular o comportamento do armazém EDA e chama-se novamente a função armazem_EDA para permitir que o utilizador observe as mudanças no armazém.
* Inserindo 'g', é chamado o menu de gestão do armazém EDA, onde o utilizador pode escolher entre as opções disponíveis.
* Se o utilizador inserir uma opção inválida, é exibida uma mensagem de erro.
* A função menu é chamada recursivamente em todos os casos até que o utilizador insira a opção '0' para sair.
* @param lista_chegada Lista de chegada de peças
* @param num ocupacção da lista de chegada
* @param seccoes_array Array de secções
* @param numero_de_seccoes Número de secções no array
* @param categorias_pecas Array de categorias de peças
*/
void menu(pecas*& lista_chegada,int num, seccao*& seccoes_array, int& numero_de_seccoes,string*& categorias_pecas){
    char tecla;
    bool sair = false;
    armazem_EDA(lista_chegada,num, seccoes_array, numero_de_seccoes,categorias_pecas);
    while (!sair) {
        cout << "\nDia (s)eguinte *********** (g)estao: ";
        cin >> tecla;
        if (tecla == 's' or tecla == 'S') {
            dia_seguinte(lista_chegada,ocupacao_lista_chegada,seccoes_array,numero_de_seccoes,categorias_pecas);
            armazem_EDA(lista_chegada,num, seccoes_array, numero_de_seccoes, categorias_pecas);

        } else if (tecla == 'g' or tecla == 'G') {
            menu_gestao();
            do {
                cin >> tecla;
                switch (tecla) {
                    case '1':
                        cout << "Venda Manual selecionada." << endl;
                        vende_peca(lista_chegada,ocupacao_lista_chegada,seccoes_array,numero_de_seccoes);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '2':
                        cout << "Promocao selecionada." << endl;
                        aplica_desconto(seccoes_array,numero_de_seccoes);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '3':
                        cout << "Alterar categoria selecionada." << endl;
                        alterar_categoria(seccoes_array,numero_de_seccoes,categorias_pecas,lista_chegada);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '4':
                        cout << "Adicionar seccao selecionada." << endl;
                        criar_nova_seccao(seccoes_array,numero_de_seccoes,categorias_pecas);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '5':
                        cout << "Numeros de serie de peças vendidas selecionado." << endl;
                        imprime_numeros_serie(seccoes_array,numero_de_seccoes);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '6':
                        cout << "Gravar Armazem selecionado." << endl;
                        grava_armazem(seccoes_array, lista_chegada,numero_de_seccoes);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '7':
                        cout << "Carregar Armazem selecionado." << endl;
                        carrega_armazem(lista_chegada,seccoes_array,numero_de_seccoes,categorias_pecas);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '8':
                        cout << "Imprimir Armazem selecionado." << endl;
                        imprime_armazem(lista_chegada,seccoes_array,numero_de_seccoes);
                        voltar_ao_menu();
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    case '0':
                        cout << "Sair selecionado" << endl;
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                    default:
                        cout << "Opcao invalida, tente denovo." << endl;
                        menu(lista_chegada, num, seccoes_array, numero_de_seccoes,categorias_pecas);
                        break;
                }

            } while (!sair);
        } else {
            cout << "Opcao invalida, tente denovo." << endl;

        }
    }
}


/** Função para simular o comportamento do dia num armazém.
 * A função verifica o dia atual da simulação, caso este seja 0 apenas são adicionadas peças às secções, uma vez que com secções varias não faz sentido realizar a venda de peças que não existem.
 * Quando o dia aumenta, diferente de zero, chama-se uma função para simular a venda de peças (prob_venda_geral), uma função para adicionar 5 peças à lista de chegada (organizarLC_5pecas) e adicionamos peças às secções (adiciona_peca).
 * A função adiciona_peca é chamada 8 vezes, sendo que vai adicionar 8 peças (no máximo) às secções.
 * Por fim, verifica se existem promoções ativas (usando verifica_promo) e retira a promoção de secções que já expiraram o tempo de promoção (retira_desconto).
 * A última ação é incrementar o dia da simulação.
 *
 * @param lista_chegada Apontador para a lista de chegada de peças.
 * @param num Número de algum parâmetro desconhecido.
 * @param seccoes_array Array de secções.
 * @param numero_de_seccoes Número de secções no array.
 * @param categorias_pecas Apontador para o array de categorias de peças.
 */
void dia_seguinte(pecas*& lista_chegada,int num, seccao*& seccoes_array, int numero_de_seccoes, string*& categorias_pecas){
    if (dia==0){
        for (int i = 0; i < 8 ; i++)
            adiciona_peca(lista_chegada,ocupacao_lista_chegada,seccoes_array,numero_de_seccoes);
    }
    else{
        prob_venda_geral(seccoes_array,numero_de_seccoes); //funciona
        organizarLC_5pecas(lista_chegada,ocupacao_lista_chegada+5,categorias_pecas,numero_de_seccoes);
        for (int i = 0; i < 8 ; i++)
            adiciona_peca(lista_chegada,ocupacao_lista_chegada,seccoes_array,numero_de_seccoes);

    }
    verifica_promo(seccoes_array,numero_de_seccoes);
    retira_desconto(seccoes_array, numero_de_seccoes);
    dia++;
}

/**
 * Função para imprimir os números de série das peças vendidas em uma secção específica ou em todas as secções.
 * @param seccoes_array Array de secções.
 * @param numero_de_seccoes Número de secções no array.
 */
void imprime_numeros_serie(seccao*& seccoes_array, int numero_de_seccoes){
    cout << endl;
    char opcao;
    for (int i = 0; i < numero_de_seccoes; i++)
        cout << seccoes_array[i].id << ". " << endl;
    cout << "Todas(Z). " << endl;
    cout << "Escolha qual seccao quer consultar: ";
    cin >> opcao;

    if (toupper(opcao) == toupper('z') )
        for (int indice = 0; indice < numero_de_seccoes; indice++){
            cout << endl << "Foram vendidas " << seccoes_array[indice].quantidade_vendida << " pecas na seccao " << seccoes_array[indice].id << endl;
            for (int indice_arrays = 0; indice_arrays < seccoes_array[indice].quantidade_vendida; indice_arrays++)
                cout << seccoes_array[indice].num_serie_vendidos[indice_arrays] << " | ";
        }


    else
        for (int j = 0; j < numero_de_seccoes; j++){
            if (toupper(opcao) == toupper(seccoes_array[j].id)){
                cout << "Foram vendidas " << seccoes_array[j].quantidade_vendida << " pecas na seccao " << seccoes_array[j].id << endl;
                for (int m = 0; m < seccoes_array[j].quantidade_vendida;m++)
                    cout << seccoes_array[j].num_serie_vendidos[m] << ", ";
                break;
            }
            else if (j == numero_de_seccoes -1){
                cout << "Escolha uma seccao valida!" << endl;
                imprime_numeros_serie(seccoes_array,numero_de_seccoes);
            }

        }



        cout << endl;
}
/**Luis
 *Pede que o utilizador pressione enter para poder voltar ao menu após usar uma função do armazem, de modo a facilitar a leitura dos dados
 */
void voltar_ao_menu(){
    cout << endl
         << "Pressione Enter para voltar ao menu. ";
    cin.ignore();
    cin.get();
}

/**
 * Função para realizar a venda manual de uma peça.
 * Após a venda da peça, uma nova peça é adicionada à secção onde a peça foi vendida vinda da lista de chegada, e a faturação da secção e do armazém é atualizada.
 * Se a peça vendida não estiver disponível, uma mensagem de erro é exibida.
 * Se a lista de chegada estiver vazia é exibida uma mensagem de erro.
 *
 * Caso o array com os numeros de serie esteja cheio irá ser criado um array dinamico temp com o dobro do espaço(dado por tamanho_num_serie), copiados todos os numeros
 * de serie para o temp e desalocada a memoria do array inicial, e depois o array inicial passa a apontar para o temp.
 * Depois disto o tamanho_num_serie é atualizado com o valor duplicado na secção para poder ser usado da proxima vez que for necessario aumentar o tamanho do array.
 *
 * @param lista_chegada Um array de peças disponíveis para venda.
 * @param num O número total de peças na lista de chegada.
 * @param seccoes_array Um array de secções que contém as peças disponíveis para venda.
 * @param numero_de_seccoes O número total de secções no armazém.
 */
void vende_peca(pecas*& lista_chegada, int num, seccao *& seccoes_array, int numero_de_seccoes) {
    char nome_seccao;
    cout << "Introduza o ID da secao para vender a peca" << "(entre " << seccoes_array[0].id << " e " << seccoes_array[numero_de_seccoes - 1].id << "): " << endl;
    cin >> nome_seccao;
    char nome_seccao_Maiuscula = toupper(nome_seccao);
    if (nome_seccao_Maiuscula > toupper(seccoes_array[numero_de_seccoes - 1].id) ) {
        vende_peca(lista_chegada, num, seccoes_array, numero_de_seccoes);

    } else {
        for (int i = 0; i < numero_de_seccoes; i++) {
            if (nome_seccao_Maiuscula == seccoes_array[i].id) {
                if (seccoes_array[i].quantidade == 0) {
                    cout << "A seccao " << seccoes_array[i].id << " esta vazia" << endl;
                    vende_peca(lista_chegada, num, seccoes_array, numero_de_seccoes);
                } else {
                    cout << "Pecas disponiveis na secao " << seccoes_array[i].id << " - " << seccoes_array[i].categoria <<endl;
                    int j = 0;
                    while(j<seccoes_array[i].quantidade) {
                        cout << j + 1 << ". " << seccoes_array[i].pecas_seccao[j].marca << " - Preco: " << seccoes_array[i].pecas_seccao[j].preco << endl;
                        j++;
                    }
                    // Seleção da peça a vender
                    cout << "Escolha a peca a ser vendida entre 1 e " << j << " ou 0 para voltar: ";
                    int opcao;
                    cin >> opcao;
                    if (opcao == 0) {
                        vende_peca(lista_chegada, num,seccoes_array, numero_de_seccoes);
                    }

                    if (opcao > 0 && opcao <= j + 1) {
                        if (seccoes_array[i].pecas_seccao[opcao - 1].preco == 0) {
                            cout << "Peça indisponível no momento" << endl;

                        } else {
                            cout << "Venda realizada com sucesso!" << endl;

                            seccoes_array[i].total_facturacao += seccoes_array[i].pecas_seccao[opcao-1].preco;

                            facturacao_total_armazem += seccoes_array[i].pecas_seccao[opcao-1].preco;

                            if (seccoes_array[i].quantidade_vendida == seccoes_array[i].tamanho_num_serie - 1) {
                                int *temp = new int[seccoes_array[i].tamanho_num_serie * 2];
                                for (int h = 0; h < seccoes_array[i].tamanho_num_serie; h++) {
                                    temp[h] = seccoes_array[i].num_serie_vendidos[h];
                                }
                                delete[] seccoes_array[i].num_serie_vendidos;
                                seccoes_array[i].num_serie_vendidos = temp;
                                seccoes_array[i].tamanho_num_serie *= 2;
                            }

                            seccoes_array[i].num_serie_vendidos[seccoes_array[i].quantidade_vendida] = seccoes_array[i].pecas_seccao[opcao-1].num_serie;
                            seccoes_array[i].quantidade_vendida++;
                            retirar_peca(seccoes_array[i], opcao - 1);
                            // Realiza a substituição da peça vendida
                            for (int n = 0; n < num; n++) {
                                if (lista_chegada[n].preco == -1) {
                                    cout << "A lista de chegada esta vazia" << endl;
                                } else {
                                    if (seccoes_array[i].categoria == lista_chegada[n].categoria) {
                                        if (seccoes_array[i].capacidade != seccoes_array[i].quantidade){
                                            seccoes_array[i].pecas_seccao[seccoes_array[i].quantidade] = lista_chegada[n];


                                            retirar_elemento(lista_chegada, num, n);

                                            ocupacao_lista_chegada--;
                                            seccoes_array[i].quantidade++;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        cout << "Opcao invalida" << endl;
                        vende_peca(lista_chegada, num, seccoes_array, numero_de_seccoes);

                    }
                }
            }
        }
    }
}


/**
 * LUIS
 * @param seccoes_array array de seccoes do armazem para atualizar
 * @param numero_de_seccoes numero de seccoes do armazem para atualizar
 * @param categorias_pecas array de categorias usadas nas seccoes para adicionar a nova categoria escolhida pelo utilizador
 * Esta funcao pede ao utilizador a categoria da seccçao a adicionar ao armazem, e a sua capacidade(entre 3 e 6), e não avança caso o utilizador não forneça uma capacidade válida.
 * Depois incrementa o numero de seccoes e cria um array dinamico temp com o numero de seccoes(já incrementado) para onde copia todas as seccoes do armazem, o mesmo acontece com as o array de categorias para criar peças
 * Desaloca a memoria do seccoes_array e do categoria_pecas
 * Adiciona a nova seccao ao ultimo lugar do array temp usando a categoria e capacidade dadas pelo utilizador, e a função cria_id() para dar o ID da seccao, os restantes valores são inicializados a 0
 * Aponta os seccoes_array e categorias_pecas para os arrays temp criados anteriormente
 * Copia a categoria nova para a ultima posicao de categoria_pecas para poder ser usada na criação das peças seguintes
 */
void criar_nova_seccao(seccao*& seccoes_array,int& numero_de_seccoes, string*& categorias_pecas){

    string categoria_nova;
    int capacidade;
    bool sair = false;

    cout << endl << "Introduza a categoria da seccao: ";
    cin >> categoria_nova;

    do {
        cout << endl << "Introduza a capacidade da seccao, um numero inteiro entre 3 e 6: ";
        cin >> capacidade;
        cout << endl;

        if (capacidade < 3 || capacidade > 6) {
            cout << endl << "Introduza uma capacidade valida!" << endl;
        } else {
            sair = true;
        }
    } while (!sair);

    numero_de_seccoes++;

    seccao* temp_seccoes_array = new seccao[numero_de_seccoes];
    string* temp_categorias_pecas = new string[numero_de_seccoes];


    for (int i = 0; i < numero_de_seccoes - 1; i++) {
        temp_seccoes_array[i] = seccoes_array[i];
        temp_categorias_pecas[i] = categorias_pecas[i];
    }

    delete[] seccoes_array;
    delete[] categorias_pecas;

    temp_seccoes_array[numero_de_seccoes - 1] = {capacidade, 0, cria_id(), 0, nullptr, 0, 10, categoria_nova};
    temp_seccoes_array[numero_de_seccoes - 1].num_serie_vendidos = new int[capacidade];
    temp_seccoes_array[numero_de_seccoes - 1].pecas_seccao = new pecas[capacidade];
    for (int j = 0; j < capacidade; j++) {
        temp_seccoes_array[numero_de_seccoes - 1].pecas_seccao[j] = {"", "", 0, 0, 0};
    }

    seccoes_array = temp_seccoes_array;
    categorias_pecas = temp_categorias_pecas;
    categorias_pecas[numero_de_seccoes-1] = categoria_nova;
    cout << endl << "A seccao " << seccoes_array[numero_de_seccoes-1].id << " com a categoria " << categoria_nova << " foi criada." << endl;
}

/** Função para aplicar desconto às peças de uma secção durante um período de tempo
 * Esta função aplica um desconto às peças de uma secção durante um período de tempo especificado pelo utilizador.
 * O utilizador deve fornecer o ID da secção e a percentagem de desconto a ser aplicada, entre 1 e 99.
 * Se a secção estiver vazia, a percentagem de desconto fornecida for inválida ou o número de dias inserido for inválido, uma mensagem de erro é exibida.
 * O desconto é aplicado às peças existentes na secção durante o período de tempo especificado.
 * O valor do desconto é calculado e aplicado a cada peça, reduzindo o preço da peça pelo valor do desconto.
 * A probabilidade de venda das peças da secção aumenta em 15% durante o período de desconto.
 * O número de dias é decrementado a cada iteração do ciclo for, e o desconto é aplicado a cada peça durante o período de tempo especificado.
 * Se o número de dias for igual a 0, o ciclo for é interrompido e o desconto é removido das peças.
 *
 * @param seccoes_array Um apontador para o array de estruturas de secção contendo as secções a serem simuladas para vendas.
 * @param numero_de_seccoes O número total de secções a serem simuladas.
 */
void aplica_desconto(seccao *& seccoes_array, int numero_de_seccoes){
    char nome_seccao;
    cout << "Introduza o ID da seccao para aplicar o desconto" << "(entre " << seccoes_array[0].id << " e " << seccoes_array[numero_de_seccoes - 1].id << ", introduza 0 para sair): " << endl;
    cin >> nome_seccao;
    if (nome_seccao == 0)
        return;
    char nome_seccao_Maiuscula = toupper(nome_seccao);
    if (nome_seccao_Maiuscula > seccoes_array[numero_de_seccoes - 1].id) {
        aplica_desconto(seccoes_array, numero_de_seccoes);
    } else {
        for (int i = 0; i < numero_de_seccoes; i++) {
            if (nome_seccao_Maiuscula == seccoes_array[i].id) {
                if (seccoes_array[i].quantidade == 0) {
                    cout << "A seccao " << seccoes_array[i].id << " esta vazia" << endl;
                    aplica_desconto(seccoes_array, numero_de_seccoes);
                } else {
                    cout << "Insira uma percentagem de desconto valida (1-99): " << endl;
                    cin >> seccoes_array->valor_prom;
                    if (seccoes_array->valor_prom < 1 || seccoes_array->valor_prom > 99) {
                        cout << "Desconto invalido. Por favor, insira um valor entre 1 e 99." << endl;
                        aplica_desconto(seccoes_array, numero_de_seccoes);
                    }
                    seccoes_array->valor_prom /=100;
                    cout << "Aplicando desconto de " << seccoes_array->valor_prom * 100 << "% as pecas existentes na seccao..." << endl << endl;

                    seccoes_array[i].inicio_promocao=dia;
                    cout << "Quantos dias deseja aplicar o desconto? " << endl;
                    cin >> seccoes_array[i].dias_promocao;
                    if (seccoes_array[i].dias_promocao < 0) {
                        cout << "Numero de dias invalido. Por favor, insira um valor positivo." << endl;
                        aplica_desconto(seccoes_array, numero_de_seccoes);
                    }
                    cout << "Desconto de " << seccoes_array->valor_prom * 100 << "% aplicado com sucesso as pecas existentes durante um periodo de " << seccoes_array[i].dias_promocao << " dias." << endl << endl;

                    for (int j = 0; j < seccoes_array[i].quantidade; j++) {
                        if (!seccoes_array[i].pecas_seccao[j].tem_promocao) {
                            seccoes_array[i].pecas_seccao[j].preco = seccoes_array[i].pecas_seccao[j].preco * (1-seccoes_array->valor_prom);
                            seccoes_array[i].pecas_seccao[j].prob_venda += 15;
                            seccoes_array[i].pecas_seccao[j].tem_promocao = true;
                        }
                        seccoes_array[i].promocao_ativa = true;
                    }
                }
            }
        }
    }
}
/**
 * Função para retirar o desconto aplicado quando o período de promoção termina.
 * Começa por verificar se existem secções com promoções ativas, em caso afirmativo
 * verifica se o período de promoção para uma secção específica chegou ao fim.
 * Se o período de promoção terminou, o desconto aplicado é revertido para o preço original
 * das peças na secção e a probabilidade de venda de cada peça é reduzida em 15%, voltando à probabilidade original.
 *
 * @param seccoes_array Um apontador para a secção onde o desconto foi aplicado.
 * @param numero_de_seccoes O número total de secções no armazém.
 */
void retira_desconto (seccao *& seccoes_array, int numero_de_seccoes){
    for (int i=0; i<numero_de_seccoes; i++) {
        if (seccoes_array[i].promocao_ativa) {
            if (seccoes_array[i].promocao_ativa && (dia - seccoes_array[i].inicio_promocao) >= seccoes_array[i].dias_promocao) {
                cout << "Periodo de promocao da seccao " << seccoes_array[i].id << " chegou ao fim passados " << seccoes_array[i].dias_promocao << " dias." << endl << endl;
                seccoes_array[i].promocao_ativa = false;

                for (int j = 0; j < seccoes_array[i].quantidade; j++) {
                    if (seccoes_array[i].pecas_seccao[j].tem_promocao){
                        seccoes_array[i].pecas_seccao[j].preco = seccoes_array[i].pecas_seccao[j].preco / (1 - seccoes_array->valor_prom);
                        seccoes_array[i].pecas_seccao[j].prob_venda -= 15;
                        seccoes_array[i].pecas_seccao[j].tem_promocao = false;
                    }
                }
            }
        }
    }
}

/** Função para aplicar desconto a peças novas na secção
 * Verifica, numa secção com promoção ativa, se existe alguma peça que não tem promoção ativa.
 * Se se verificar vai aplicar o desconto à peça e muda o estado da peça para promoção ativa
 * @param seccoes_array Um apontador para a secção onde o desconto foi aplicado.
 * @param numero_de_seccoes O número total de secções no armazém.
 */
void verifica_promo (seccao *& seccoes_array, int numero_de_seccoes){
    for (int i=0;i<numero_de_seccoes;i++){
        if (seccoes_array[i].promocao_ativa){
            for (int j=0; j<seccoes_array[i].quantidade; j++){
                if (!seccoes_array[i].pecas_seccao[j].tem_promocao){
                        seccoes_array[i].pecas_seccao[j].preco = seccoes_array[i].pecas_seccao[j].preco * (1 - seccoes_array->valor_prom);
                        seccoes_array[i].pecas_seccao[j].prob_venda += 15;
                        seccoes_array[i].pecas_seccao[j].tem_promocao = true;
                }
            }
        }
    }
}

/**Luis
 * @param seccoes_array Apontador para o array onde estão guardadas as secções
 * @param numero_de_seccoes Quantidade de secções no armazém
 * @param categorias_pecas Array de categorias usadas nas secçõeses para criar peças novas
 * @param lista_chegada Array onde as peças criadas ficam antes de serem postas nas secções
 * A função dá ao utilizador a lista de seccões e as suas respetivas categorias, se não fornecer um id valido a função irá avisar ao utilizador e pedir para introduzir novamente.
 * Quando o utilizador der um id valido a função irá comparar este com os ids das secções no seccoes_array de modo a encontrar o indice da secção a ser alterada.
 * De seguida irá pedir ao utilizador para introduzir a nova categoria, é pedido que a primeira letra seja maiscula para caso já tenha alguma categoria igual no armazém não serem apagadas as peças na lista de chegada com a mesma categoria
 * Neste menu o utilizador não poderá introduzir a mesma categoria que a secção já tem, caso isto aconteça a função irá informar ao utilizador que pode introduzir uma categoria diferente ou introduzir 0 para voltar ao menu e cancelar a alteração de categoria
 * Após introduzir uma nova categoria valida a função irá guardar a categoria atual da secção e de seguida desalocar a memoria do array que contém as peças dentro da secção, eliminado-as, e volta a alocar memoria para esse array com o mesmo tamanho que o anterior, a capacidade da secção
 * Depois a quantidade de peças na secção vai ser definida como 0 e a secção irá passar a ter a categoria dada pelo utilizador
 * Por fim a função irá verificar se há mais alguma secção com a categoria anterior, se houver o utilizador apenas irá receber uma confirmação da alteração da categoria, se não houver a função ira verificar se há peças com essa categoria na lista de chegada,
 * se houver alguma peça esta será eliminada de modo a não existir peças que não conseguem entrar em nenhuma secção. Caso isto aconteça o utilizador irá receber uma confirmação que foram apagadas peças e que a categoria foi alterada com sucesso.
 */
void alterar_categoria(seccao*& seccoes_array, int& numero_de_seccoes, string*& categorias_pecas, pecas*& lista_chegada){
    char opcao;
    int indice_seccao = -1; // o indice da seccao vai ser o mesmo no seccao arrays e no categorias_pecas para mudar a categoria
    cout << endl;
    for (int i = 0; i < numero_de_seccoes; i++)
        cout << seccoes_array[i].id << ". " << seccoes_array[i].categoria << endl;
    do{
        cout << "Escolha a seccao em que quer alterar a categoria:";
        cin >> opcao;

        for (int j = 0; j < numero_de_seccoes; j++){
            if (toupper(opcao) == toupper(seccoes_array[j].id))
                indice_seccao = j;
            else
                continue;
        }
        if (indice_seccao== -1)
            cout << endl << "Opcao invalida." << endl;
    }while(indice_seccao == -1);

    string nova_categoria;
    cout << "Escolheu a seccao " << seccoes_array[indice_seccao].id << " que tem a categoria " << seccoes_array[indice_seccao].categoria << "." << endl;

    bool sair = false;
    do{
        cout << endl <<"Escolha a categoria para qual quer mudar(Use letra Maiuscula na primeira letra): ";
        cin >> nova_categoria;

        if (nova_categoria == "0")
            return;
        if (nova_categoria == seccoes_array[indice_seccao].categoria)
            cout << "A categoria que inseriu e a mesma!" << endl << "Escolha uma categoria diferente ou introduza 0 para voltar ao menu do armazem." << endl;
        else{
            sair = true;
        }
    }while(!sair);

    string categoria_antiga = seccoes_array[indice_seccao].categoria; // guardar a categoria antiga

    delete[] seccoes_array[indice_seccao].pecas_seccao; //desalocar array de pecas da categoria antiga
    seccoes_array[indice_seccao].pecas_seccao = new pecas[seccoes_array[indice_seccao].capacidade];
    seccoes_array[indice_seccao].quantidade = 0;

    seccoes_array[indice_seccao].categoria = nova_categoria;

    categorias_pecas[indice_seccao] = nova_categoria;

    bool eliminar = true;
    for (int k = 0; k < numero_de_seccoes; k++) {
        if (categorias_pecas[k] == categoria_antiga){
            eliminar = false;
            break;
        }
    }

    if (eliminar){
        for (int m = ocupacao_lista_chegada; m >= 0;m--) {
            if (lista_chegada[m].categoria == categoria_antiga) {
                retirar_elemento(lista_chegada, ocupacao_lista_chegada, m);
                ocupacao_lista_chegada--;
            }
        }
        cout << endl << "A categoria da seccao " << seccoes_array[indice_seccao].id << " foi alterada de " << categoria_antiga << " para " << nova_categoria << " com sucesso." << endl
                << "Todas as pecas com a categoria " << categoria_antiga << " foram removidas da lista de chegada.";
    }
    else{
        cout << endl << "A categoria da seccao " << seccoes_array[indice_seccao].id << " foi alterada de " << categoria_antiga << " para " << nova_categoria << " com sucesso." << endl;
    }
}

/** Função para imprimir o armazém na consola
 * Imprime todas as peças do armazém de acordo com a escolha do utilizador.
 * É possível imprimir por ordem alfabética das peças e pelo preço de cada peça.
 *
 * @param lista_chegada Apontador para o array de peças disponíveis para adicionar às secções.
 * @param seccoes_array Apontador para o array onde estão guardadas as secções do armazém.
 * @param numero_de_seccoes Quantidade de secções no armazém.
 */
void imprime_armazem(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes){
    char escolha;
    int tam_array_pecas = 0;
    for (int i=0; i<numero_de_seccoes; i++){
        tam_array_pecas+=seccoes_array[i].quantidade;
    }
    tam_array_pecas+=ocupacao_lista_chegada;
    pecas * array_pecas = new pecas[tam_array_pecas];

    int indice = 0;
    for (int i=0; i<numero_de_seccoes;i++) {
        for (int j = 0; j < seccoes_array[i].quantidade; j++) {
            array_pecas[indice] = seccoes_array[i].pecas_seccao[j];
            indice++;
        }
    }
    int indice_while = 0;
    while (indice_while < ocupacao_lista_chegada and lista_chegada[indice_while].preco !=-1){
        array_pecas[indice] = lista_chegada[indice_while];
        indice_while++;
        indice++;
    }


    bool sair = false;
    cout << "\n=== Sub-menu de Impressao ===\n";
    cout << "(1). Por ordem alfabetica da marca \n";
    cout << "(2). Por preco \n";
    cout << "(0). Sair \n";
    cout <<endl;
    while (!sair) {
        cout << "Indique como deseja organizar a lista do Armazem: ";
        cin >> escolha;
        switch (escolha){
            case '1':
                cout << "Impressao das pecas por ordem alfabetica da marca: " << endl;
                for (int j=0; j<tam_array_pecas-1;j++){
                    for (int k=0; k<tam_array_pecas-j-1;k++){
                        if (array_pecas[k].marca>array_pecas[k+1].marca){
                            troca(array_pecas[k],array_pecas[k+1]);
                        }
                    }
                }
                for (int teste = 0; teste < tam_array_pecas; teste++)
                    cout << array_pecas[teste].marca << endl;
                sair = true;
                break;
            case '2':
                cout << "Impressao ordenada por preco: " << endl;
                for (int j=0; j<tam_array_pecas-1;j++){
                    for (int k=0; k<tam_array_pecas-j-1;k++){
                        if (array_pecas[k].preco > array_pecas[k+1].preco){
                            troca(array_pecas[k],array_pecas[k+1]);
                        }
                    }
                }
                for (int teste = 0; teste < tam_array_pecas; teste++)
                    cout << array_pecas[teste].preco << endl;
                sair = true;
                break;
            case '0':
                return;
                break;
            default:
                cout << endl <<"Opcao invalida. Por favor, escolha novamente.\n";
                break;
        }
    }
    delete[] array_pecas;
}
/**
* Função para gravar as informações do armazém em ficheiros de texto as informações do armazém em 4 ficheiros de texto: caracteristicas.txt, seccoes.txt, pecas.txt e numeros_serie.txt.
*O ficheiro caracteristicas.txt contém o número de secções, o número de peças na lista de chegada, o ID da secção, a faturação total do armazém e o dia atual.
*O ficheiro seccoes.txt contém as informações de cada secção, incluindo a capacidade, quantidade de peças, ID da secção, faturação total, quantidade de peças vendidas,
*tamanho do array de números de série, categoria, dias de promoção, dia do início da promoção, valor do desconto aplicado e se a secção tem promoção ativa.
*O ficheiro pecas.txt contém as informações de cada peça (nas secções e na lista de chegada), incluindo a marca, categoria, preço, probabilidade de venda, número de série e se a peça tem promoção ativa.
*O ficheiro numeros_serie.txt contém os números de série das peças vendidas em cada secção.
@param seccoes_array Array de secções do armazém.
@param lista_chegada Array de peças disponíveis para inserir nas secções.
@param numero_de_seccoes Número total de secções no armazém.
*/
void grava_armazem (seccao*& seccoes_array,pecas*& lista_chegada, int& numero_de_seccoes) {
    ofstream caracteristicas("caracteristicas.txt");
    if (caracteristicas.is_open()) {
        caracteristicas << numero_de_seccoes << endl;
        caracteristicas << ocupacao_lista_chegada << endl;
        caracteristicas << id << endl;
        caracteristicas << facturacao_total_armazem << endl;
        caracteristicas << dia << endl;
        caracteristicas.close();
    } else
        cerr << "Erro a editar o ficheiro caracteristicas";


    ofstream seccoes("seccoes.txt");
    if (seccoes.is_open()) {
        for (int i = 0; i < numero_de_seccoes; i++) {
            seccoes << seccoes_array[i].capacidade
                    << "|" << seccoes_array[i].quantidade
                    << "|" << seccoes_array[i].id
                    << "|" << seccoes_array[i].total_facturacao
                    << "|" << seccoes_array[i].quantidade_vendida
                    << "|" << seccoes_array[i].tamanho_num_serie
                    << "|" << seccoes_array[i].categoria
                    << "|" << seccoes_array[i].dias_promocao
                    << "|" << seccoes_array[i].inicio_promocao
                    << "|" << seccoes_array[i].valor_prom
                    << "|" << seccoes_array[i].promocao_ativa << endl;
        }
        seccoes.close();
    } else
        cerr << "Erro a editar o ficheiro seccoes";

    ofstream fpecas("pecas.txt");
    if (fpecas.is_open()){
        fpecas << "|";
        for (int i = 0; i < numero_de_seccoes; i++){
            for (int j = 0; j < seccoes_array[i].quantidade;j++){
                fpecas << seccoes_array[i].pecas_seccao[j].marca
                      << "|" << seccoes_array[i].pecas_seccao[j].categoria
                      << "|" << seccoes_array[i].pecas_seccao[j].preco
                      << "|" << seccoes_array[i].pecas_seccao[j].prob_venda
                      << "|" << seccoes_array[i].pecas_seccao[j].num_serie
                      << "|" << seccoes_array[i].pecas_seccao[j].tem_promocao << endl;
            }
        }
        for (int m = 0; m < ocupacao_lista_chegada; m++){
            fpecas << lista_chegada[m].marca
            << "|" << lista_chegada[m].categoria
            << "|" << lista_chegada[m].preco
            << "|" << lista_chegada[m].prob_venda
            << "|" << lista_chegada[m].num_serie
            << "|" << lista_chegada[m].tem_promocao << endl;
        }

        fpecas.close();
    }
    else
        cerr << "Erro ao editar o ficheiro pecas.txt";

    ofstream numeros_serie("numeros_serie.txt");
    if (numeros_serie.is_open()) {
        for (int i = 0; i < numero_de_seccoes; i++) {
            for (int j = 0; j < seccoes_array[i].quantidade_vendida; j++) {
                numeros_serie << seccoes_array[i].num_serie_vendidos[j] << "|";
            }
            numeros_serie << endl;
        }
        numeros_serie.close();

    }

    else
        cerr << "Erro ao editar o ficheiro numeros_serie.txt";

    cout<<"O armazem foi gravado com sucesso!"<<endl;
}
/**
 * Luís
 * @param lista_chegada array das peças da lista de chegada
 * @param seccoes_array array onde as secções estão guardadas
 * @param numero_de_seccoes quantidade de secções no armazém
 * @param categorias_pecas array de categorias usado para criar peças novas
 * Esta função lê os ficheiros criados pela função grava_armazem e carrega o estado do armazem no momento em que foi guardado, isto inclui os dias, a existencia de promoções, a quantidade de secções,
 * as peças presentes no armazém, a facturação tanto do armazém em geral como de cada secção e os números de serie das peças vendidas.
 * Os 4 ficheiros são lidos tendo em conta a formatação usada na função grava_armazem e cada aspeto do armazém é armazenado em variáveis temporárias
 * Caso a leitura de algum ficheiro falhe, o programa irá retornar ao menu e apresentar um erro com o nome do ficheiro que não foi aberto corretamente,
 * deste modo o armazém apenas será alterado após todos os ficheiros serem lidos, assim não há o risco de perder o estado do armazém antes de carregar os ficheiros.
 * O array temp_categoria_pecas é criado a partir das categorias presentes em temp_seccoes_array
 * Após a leitura, a memória de lista_chegada, seccoes_array, e categoria_pecas é desalocada e apontadas para as variáveis temp que foram preenchidas com os dados dos ficheiros
 * e uma mensagem a informar o sucesso da operação é apresentada ao utilizador.
 */
void carrega_armazem(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes, string *& categorias_pecas) {
    char ignora; // para ficar os "|"
/////////////////////////////////////////Características//////////////////////////////////////////////////////////////////
    ifstream caracteristicas("caracteristicas.txt");

    int temp_numero_de_seccoes;
    int temp_ocupacao_lista_chegada;
    char temp_id;
    float temp_facturacao_total_armazem;
    int temp_dia;

    if (caracteristicas.is_open()) {
        caracteristicas >> temp_numero_de_seccoes >> temp_ocupacao_lista_chegada >> temp_id
                        >> temp_facturacao_total_armazem >> temp_dia;
        caracteristicas.close();
    }
    else {
        cerr << endl << "Nao foi possivel abrir o ficheiro caracteristicas.txt, tente guardar o armazem novamente.";
        return;
    }

//////////////////////////////////////Secções///////////////////////////////////////////////////////////////
    ifstream seccoes("seccoes.txt");
    seccao *temp_seccoes_array = new seccao[temp_numero_de_seccoes];

    int temp_capacidade;
    int temp_quantidade;
    char temp_id_seccao;
    float temp_total_facturacao_seccao;
    int temp_quantidade_vendida;
    int temp_tamanho_num_serie;
    string temp_categoria;
    int temp_dias_promocao;
    int temp_inicio_promocao;
    float temp_valor_prom;
    bool temp_promocao_ativa;

    if (seccoes.is_open()) {
        for (int i = 0; i < temp_numero_de_seccoes; i++) {
            seccoes >> temp_capacidade >> ignora >> temp_quantidade >> ignora >> temp_id_seccao
                    >> ignora >> temp_total_facturacao_seccao >> ignora >> temp_quantidade_vendida
                    >> ignora >> temp_tamanho_num_serie >> ignora;
            getline(seccoes, temp_categoria, '|');
            seccoes >> temp_dias_promocao >> ignora >> temp_inicio_promocao
                    >> ignora >> temp_valor_prom >> ignora >> temp_promocao_ativa;

            temp_seccoes_array[i] = {temp_capacidade, temp_quantidade, temp_id_seccao, temp_total_facturacao_seccao,
                                     nullptr, temp_quantidade_vendida, temp_tamanho_num_serie,
                                     temp_categoria, nullptr, temp_dias_promocao, temp_inicio_promocao,
                                     temp_valor_prom, temp_promocao_ativa};
        }
        seccoes.close();
    }
    else {
        cerr << endl << "Nao foi possivel abrir o ficheiro seccoes.txt, tente guardar o armazem novamente.";
        return;
    }

///////////////////////////////Números de Serie/////////////////////////////////////////////////////////
    ifstream numeros_serie("numeros_serie.txt");
    string temp_numero_serie;

    if (numeros_serie.is_open()) {
        for (int i = 0; i < temp_numero_de_seccoes; i++) {
            temp_seccoes_array[i].num_serie_vendidos = new int[temp_seccoes_array[i].tamanho_num_serie];
            for (int j = 0; j < temp_seccoes_array[i].quantidade_vendida; j++) {
                getline(numeros_serie, temp_numero_serie, '|');
                temp_seccoes_array[i].num_serie_vendidos[j] = stoi(temp_numero_serie);
            }
        }
        numeros_serie.close();
    }
    else {
        cerr << endl << "Nao foi possivel abrir o ficheiro numeros_serie.txt, tente guardar o armazem novamente.";
        return;
    }

/////////////////////////////////////Peças(secções e lista de chegada)/////////////////////////////////////

    ifstream fpecas("pecas.txt");

    string temp_marca;
    float temp_preco;
    float temp_prob_venda;
    int temp_num_serie;
    bool temp_tem_promocao;


    pecas *temp_lista_chegada = new pecas[50];

    if (fpecas.is_open()) {
        for (int i = 0; i < temp_numero_de_seccoes; i++) {
            temp_seccoes_array[i].pecas_seccao = new pecas[temp_seccoes_array[i].capacidade];
            for (int j = 0; j < temp_seccoes_array[i].quantidade; j++) {

                fpecas.ignore();
                getline(fpecas, temp_marca, '|');
                getline(fpecas, temp_categoria, '|');

                fpecas >> temp_preco >> ignora
                       >> temp_prob_venda >> ignora >> temp_num_serie >> ignora >> temp_tem_promocao;

                pecas peca_atual;
                peca_atual.marca = temp_marca;
                peca_atual.categoria = temp_categoria;
                peca_atual.preco = temp_preco;
                peca_atual.prob_venda = temp_prob_venda;
                peca_atual.num_serie = temp_num_serie;
                peca_atual.tem_promocao = temp_tem_promocao;

                temp_seccoes_array[i].pecas_seccao[j] = peca_atual;
            }
        }
        if (temp_ocupacao_lista_chegada > 0) {
            for (int m = 0; m < temp_ocupacao_lista_chegada; m++) {
                fpecas.ignore();
                getline(fpecas, temp_marca, '|');
                getline(fpecas, temp_categoria, '|');

                fpecas >> temp_preco >> ignora
                       >> temp_prob_venda >> ignora >> temp_num_serie >> ignora >> temp_tem_promocao;

                pecas lc_peca_atual;
                lc_peca_atual.marca = temp_marca;
                lc_peca_atual.categoria = temp_categoria;
                lc_peca_atual.preco = temp_preco;
                lc_peca_atual.prob_venda = temp_prob_venda;
                lc_peca_atual.num_serie = temp_num_serie;
                lc_peca_atual.tem_promocao = temp_tem_promocao;

                temp_lista_chegada[m] = lc_peca_atual;
            }
            fpecas.close();
        }
        else {
            cerr << endl << "Nao foi possivel abrir o ficheiro numeros_serie.txt, tente guardar o armazem novamente.";
            return;
        }

        delete[] seccoes_array;
        delete[] lista_chegada;
        delete[] categorias_pecas;

        string *temp_categorias_pecas = new string[temp_numero_de_seccoes];

        numero_de_seccoes = temp_numero_de_seccoes;
        ocupacao_lista_chegada = temp_ocupacao_lista_chegada;
        id = temp_id;
        facturacao_total_armazem = temp_facturacao_total_armazem;
        dia = temp_dia;

        seccoes_array = temp_seccoes_array;
        lista_chegada = temp_lista_chegada;

        for (int i = 0; i < temp_numero_de_seccoes; i++)
            temp_categorias_pecas[i] = temp_seccoes_array[i].categoria;
        categorias_pecas = temp_categorias_pecas;

        cout << endl << "O armazem foi carregado com sucesso." << endl;
    }

}