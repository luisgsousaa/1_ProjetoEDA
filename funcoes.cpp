#include <iostream>
#include "funcoes.h"
#include "CriaEstruturas.h"
#include <stdlib.h>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;



/**
 * Esta função gera e retorna um número aleatório de secções entre 7 e 10 para o armazém ter um número de secções variável
 * @return número aleatório entre 7 e 10
 */
int n_seccoes(){
    return rand()% 4 + 7;
}

/**
 * Esta função gera e retorna um número aleatório para a capacidade de uma secção entre 3 e 6
 * @return numero aleatório entre 3 e 6
 */
int n_capacidade(){
    return rand()% 4 + 3;
}

/**
 * Esta função gera e retorna um número aleatório entre 2 e 180 (2*5=10, 180*5=900) para o preço de uma peça ser um múltiplo de 5 entre 10 e 900
 * @return multiplica o numero gerado por 5, obtém-se um multiplo de 5 entre 10 e 900
 */
float preco(){
    return (rand()% 179 +2) * 5;
}


/**LUIS
 * Inicialização da variavel do numero de serie em 999 para o primeiro numero de serie ser 1000.
 */
int numero_serie_novo = 999;

/**
 * Incrementa o numero de serie por 1, cada vez que a função é chamada.
 * Deste modo cada produto criado irá ter um numero de serie diferente do anterior
 * Caso o numero de serie chegue a 9999 o programa irá exibir um erro e terminar.
 * @return numero de serie a dar a um produto novo.
 */
int num_serie(){
    if (numero_serie_novo == 9999){
        cerr << "O numero de produtos excedeu o maximo";
        exit(1);
    }
    else{
        numero_serie_novo++;
        return numero_serie_novo;
    }
}


/**
 * Esta função gera e retorna um número aleatório entre 5 e 50 que representa a probabilidade de venda de uma peça em percentagem
 * @return
 */
float prob_venda(){
    return rand()% 46+5;
}


/**
 * Inicialização da variavel global neste ficheiro para as outras funções poderem aceder
 */
int n_linhas_marcas = 0;
string * array_de_marcas;

/**LUIS
 * Lê o ficheiro das marcas para serem usadas no programa
 * Abre o ficheiro marcas.txt, caso este não seja aberto dá erro e o programa acaba.
 * Caso seja aberto conta quantas linhas tem o ficheiro, cria um array dinamico com o tamanho correspondente à quantidade linhas/marcas
 * Depois retorna a leitura para o inicio do ficheiro e percorre-o outra vez e preenche o array com as respetivas marcas
 * Por fim fecha o ficheiro.
 */
void le_ficheiro_marcas() {

    fstream marcas;
    marcas.open("marcas.txt");
    if (marcas.is_open()){
        string linha;
        while (getline(marcas, linha)) {
            n_linhas_marcas++;
        }

        marcas.clear();
        marcas.seekg(0, ios::beg);

        array_de_marcas = new string[n_linhas_marcas];


        for (int i = 0; i < n_linhas_marcas; i++) {
            getline(marcas, linha);
            array_de_marcas[i] = linha;
        }
        marcas.close();
    }
    else{
        cerr << "Erro. Nao foi possivel abrir o ficheiro marcas.txt";
        exit(1);
    }


}
/**LUIS
 * Escolhe uma marca aleatoria do array_de_marcas
 * escolhe um indice aleatorio de 0 a n_linhas_marcas(quantidade de linhas/marcas do ficheiro) - 1
 * @return retorna o valor do indice escolhido no array_de_marcas
 */
string marca_aleatoria(){

    int indice;
    indice = rand() % n_linhas_marcas;
    return array_de_marcas[indice];
}
/**
 * Inicialização da variavel global neste ficheiro para as outras funções poderem aceder
 */
int n_linhas_categorias;
string * array_de_categorias;
/** LUIS
 * Lê o ficheiro das marcas para serem usadas no programa
 * Abre o ficheiro categorias.txt, caso este não seja aberto dá erro e o programa acaba.
 * Caso seja aberto conta quantas linhas tem o ficheiro, cria um array dinamico com o tamanho correspondente à quantidade linhas/categorias
 * Depois retorna a leitura para o inicio do ficheiro e percorre-o outra vez e preenche o array com as respetivas categorias
 * Por fim fecha o ficheiro.
 */
void le_ficheiro_categorias(){
    fstream categorias;
    categorias.open("categorias.txt");
    if (categorias.is_open()){
        string linha;
        while (getline(categorias, linha)) {
            n_linhas_categorias++;
        }

        categorias.clear();
        categorias.seekg(0, ios::beg);

        array_de_categorias = new string[n_linhas_categorias];


        for (int i = 0; i < n_linhas_categorias; i++) {
            getline(categorias, linha);
            array_de_categorias[i] = linha;
        }
        categorias.close();
    }
    else{
        cerr << "Erro. Nao foi possivel abrir o ficheiro categorias.txt";
        exit(1);
    }
}
/**Luis
 * Escolhe uma categoria aleatoria do array_de_categorias
 * escolhe um indice aleatorio de 0 a n_linhas_categorias(quantidade de linhas/categorias do ficheiro) - 1
 * @return retorna o valor do indice escolhido no array_de_marcas
 */
string categoria_aleatoria(){
    int indice;
    indice = rand() % n_linhas_categorias;
    return array_de_categorias[indice];
}

/**
 * Luis
 * Indica a categoria que a peça a ser criada vai ter a partir das categorias ja usadas nas secções, de modo a apenas criar peças com as categorias existentes nas seccoes
 * @param categorias_pecas Recebe o array criado na função cria_seccoes() com apenas as categorias usadas nas secções
 * @param numero_de_seccoes Numero de elementos no array para escolher um aleatorio
 * @return Retorna uma posição aleatoria do array categorias_pecas
 */
string categorias_usadas(string categorias_pecas[],int numero_de_seccoes){

    int indice;
    indice = rand() % numero_de_seccoes;
    return categorias_pecas[indice];
}

/**
 * Inicialização da variavel do ID das secções
 */
char id = 'A';
/**
 * Luis
 * Na primeira chamada esta função retorna A e muda o valor de id para B
 * Nas seguintes chamadas retorna a variavel id e apenas depois é que a incrementa.
 * @return Variavel id antes de ser incrementada
 */
char cria_id() {
    if (id == 'A'){
        id = 'B';
        return 'A';
    }
    return id++;
}


/**Luis
 * Elimina a necessidade de chamar as 3 funções separadamente para inicializar o armazém e desaloca a memoria de array_de_categorias que já não é necessario a partir do momento que as seccoes estão criadas
 * para inicializar -> ler_ficheiros_e_inicicializar_seccoes(seccoes_array,numero_de_seccoes,categorias_pecas);
 */
void ler_ficheiros_e_inicicializar_seccoes(seccao seccoes_array[],int numero_de_seccoes, string*& categorias_pecas){
    le_ficheiro_categorias();
    le_ficheiro_marcas();
    cria_seccoes(seccoes_array,numero_de_seccoes,categorias_pecas);
    delete[] array_de_categorias;
}


/** Algoritmo do tipo BubbleSort
 * Esta função troca duas estruturas de peças através de referência, representadas pelos parâmetros 'a' e 'b'.
 * Para fazer a troca, cria-se uma variável temporária e copia-se o valor de 'a' para ela.
 * Em seguida, copia-se o valor de 'b' para 'a' e, finalmente, copia-se o valor temporário de volta para 'b', realizando assim a troca.
 * @param a peça passada por referência
 * @param b peça passada por referência
 */
void troca (pecas &a, pecas &b){
    pecas temp=a;
    a=b;
    b=temp;
}

/**
 * Variavel global para guardar a ocupação da lista de chegada
 */
int ocupacao_lista_chegada = 0;


/** Criação de 10 peças aleatórias
 * Esta função preenche a lista de chegada de peças com 10 peças criadas aleatoriamente.
 * As peças são classificadas de acordo com sua marca em ordem crescente.
 * As peças são corretamente ordenadas de acordo com a marca, organizando todos os parâmetros associados.
 * Para realizar a ordenação é utilizado o algoritmo troca.
 * @param lista_chegada Uma matriz de estruturas de peças que representa a lista de chegada a ser inicializada.
 * @param categorias_pecas Um array de strings contendo as categorias de peças disponíveis.
 * @param numero_de_seccoes O número de secções a ser considerado na criação de cada peça.
 */
void inicializar_lista_chegada(pecas*& lista_chegada,string categorias_pecas[],int numero_de_seccoes){
    for (int i=0;i<50;i++){
        lista_chegada[i].preco=-1;
    }
    pecas pecas_Array [10];
    for (int i = 0; i < 10; i++) {
        pecas_Array[i] = criaPeca(categorias_pecas,numero_de_seccoes);
        ocupacao_lista_chegada++;
    }
    for (int j=0; j<10-1;j++){
        for (int k=0; k<10-j-1;k++){
            if (pecas_Array[k].marca>pecas_Array[k+1].marca){
                troca(pecas_Array[k],pecas_Array[k+1]);
            }
        }
    }
    for (int m=0; m<10; m++)
        lista_chegada[m]=pecas_Array[m];
}



/** Insere um elemento em uma posição específica de um array de peças.
 * Esta função insere um elemento numa posição específica de um array de peças.
 * Se a posição fornecida estiver fora dos limites do array, uma mensagem de erro é exibida.
 * Os elementos do array após a posição para inserção são movidos para a direita para conseguir espaço para o novo elemento.
 *
 * @param array Um array de estruturas de peças onde o elemento será inserido
 * @param tamanho O tamanho atual do array
 * @param posicao A posição onde o elemento será inserido
 * @param elemento A estrutura de peças a ser inserida no array
 */
void inserir_elemento(pecas array[], int tamanho, int posicao, pecas elemento) {
    if (posicao < 0 || posicao >= 50) {
        cout << "Posição inválida!" << endl;
        return;
    }
    for (int i = tamanho; i > posicao; i--) {
        array[i] = array[i-1];
    }
    array[posicao] = elemento;
    tamanho++;
}


/** Organiza e insere 5 peças na lista de chegada
 * Esta função gera 5 peças aleatórias, organiza-as em ordem crescente de marca e insere as mesmas
 * na lista de chegada. Em seguida, verifica se há peças com a mesma marca na lista e estas são inseridas
 * em posições consecutivas.
 * É respeitada a ordem de chegada das peças à lista de chegada, apenas são organizadas as 5 peças mais recentes e de acordo com a marca.
 *
 * @param lista_chegada Uma matriz de estruturas de peças que representa a lista de chegada onde as peças serão inseridas.
 * @param num O número total de peças na lista de chegada
 * @param categorias_pecas Um array de strings contendo as categorias de peças disponíveis.
 * @param numero_de_seccoes O número de secções a ser considerado na criação de cada peça.
 *
 * Exemplo de utilização:
 * organizarLC_5pecas(lista_chegada,ocupacao_lista_chegada+5,categorias_pecas,numero_de_seccoes)
 * Para inicializar é necessário utilizar o indicado acima, onde adicionamos 5 peças à ocupação da lista de chegada
 */
void organizarLC_5pecas(pecas*& lista_chegada, int num, string categorias_pecas[],int numero_de_seccoes) {
    pecas pecas_Array[5];
    for (int i = 0; i < 5; i++) {
        pecas_Array[i] = criaPeca(categorias_pecas, numero_de_seccoes);

    }
    ocupacao_lista_chegada+=5;
    for (int j = 0; j < 5 - 1; j++) {
        for (int k = 0; k < 5 - j - 1; k++) {
            if (pecas_Array[k].marca > pecas_Array[k + 1].marca) {
                troca(pecas_Array[k], pecas_Array[k + 1]);
            }
        }
    }
    int i = num-5, j = 0;
    while (i < num) {
        lista_chegada[i]=pecas_Array[j];
        j++;
        i++;
    }

    int k = 0, m = num-5;
    while (m < num) {
        k = 0;
        while (k < m) {
            if (lista_chegada[k].marca == lista_chegada[m].marca) {
                inserir_elemento(lista_chegada, m, k+1, lista_chegada[m]);
                k++;
                m++;

            } else {
                k++;
            }
        }
        m++;
    }
}


/**
 * Retira um elemento de uma posição específica de um array de peças
 * Esta função remove um elemento de uma posição específica de um array de peças.
 * Se a posição fornecida estiver fora dos limites do array, uma mensagem de erro é exibida.
 * Os elementos do array após a posição de retirada são movidos para a esquerda para preencher o espaço deixado pelo elemento removido.
 * O tamanho do array é atualizado para refletir a remoção do elemento.
 *
 * @param array Um array de estruturas de peças do qual o elemento será retirado.
 * @param tamanho O tamanho atual do array.
 * @param posicao A posição do elemento que será retirado.
 */
void retirar_elemento(pecas*& array, int tamanho, int posicao) {
    if (posicao < 0 || posicao >= tamanho) {
        cout << "Posição inválida!" << endl;
        return;
    }
    for (int i = posicao; i < tamanho; i++) {
        array[i] = array[i + 1];
    }
    tamanho--;
}


/** Luis
 * Adiciona peças às secções disponíveis do armazém, apenas adiciona 1 peça quando é chamada (será chamada 8 vezes por ciclo).
 * Se a lista de chegada tiver vazia(preco==-1) a função não continua.
 * O indice da lista de chegada começa a 0 para a primeira peça mas pode ser incrementado, dependendo da disponibilidade das secções
 * Esta função adiciona peças da lista de chegada às secções disponíveis, tendo em conta a categoria e a capacidade das secções.
 * Se a categoria da peça corresponder à categoria de uma secção e a quantidade de peças na secção for inferior à capacidade da secção(a secção não estiver cheia), a peça é copiada para a secção e é retirada da lista de chegada, a quantidade de peças na secção é incrementada e o ciclo for termina.
 * Se as categorias corresponderem e a quantidade de peças na secção for igual ou superior à da capacidade da secção(a secção estiver cheia), o ciclo irá percorrer as outras secções e verificar as condições, ao fim do ciclo for se a não tiver nenhuma secção disponivel, o indice da lista de chegada é incrementado e o indice do ciclo for passa a 0 para recomeçar a procura de uma secção disponível.
 * O ciclo for não é atingido se encontrada for true, ou seja, se já estiver sido encontrada uma secção disponível para a peça.
 *
 * @param lista_chegada Um array de estruturas de peças contendo as peças disponíveis para adição às secções.
 * @param num O número total de peças na lista de chegada.
 * @param seccoes_array Um apontador para o array de estruturas de secção representando as secções para adição das peças.
 * @param numero_de_seccoes O número total de secções.
 */
void adiciona_peca(pecas*& lista_chegada,int num, seccao*& seccoes_array, int numero_de_seccoes){
    int indice = 0;
    if (lista_chegada[0].preco == -1){
        return;
    }

    while (indice < ocupacao_lista_chegada) {
        bool encontrada = false;
        for (int i = 0; i < numero_de_seccoes; i++) {
            if (seccoes_array[i].categoria == lista_chegada[indice].categoria) {
                if (seccoes_array[i].quantidade < seccoes_array[i].capacidade) {
                    seccoes_array[i].pecas_seccao[seccoes_array[i].quantidade] = lista_chegada[indice];
                    retirar_elemento(lista_chegada, num, indice);
                    ocupacao_lista_chegada--;
                    seccoes_array[i].quantidade++;
                    encontrada = true;
                    break;
                }
            }
        }
        if (encontrada)
            break;
        else
            indice++;
    }
}

/** Retira uma peça de uma posição específica de uma secção
 * Esta função remove uma peça de uma posição específica de uma secção.
 * Se a posição fornecida estiver fora dos limites da capacidade da secção, uma mensagem de erro é exibida.
 * As peças na secção após a posição indicada são movidas para a esquerda para preencher o espaço deixado pela peça removida.
 * A quantidade de peças na secção é atualizada após a retirada da peça.
 *
 * @param array A estrutura de secção de onde a peça será retirada
 * @param posicao A posição da peça que será retirada
 */
void retirar_peca(seccao &array, int posicao){
    if (posicao < 0 || posicao >= array.capacidade) {
        cout << "Posição inválida!" << endl;
        return;
    }
    for (int i = posicao; i < array.quantidade - 1; i++) {
        array.pecas_seccao[i] = array.pecas_seccao[i + 1];
    }
    array.quantidade--;
}

/**
 * Variável global para guardar a faturação total do armazém
 */
float facturacao_total_armazem = 0;

/** Simula vendas nas secções com base na probabilidade de venda das peças
 * Esta função simula vendas nas secções com base na probabilidade de venda associada a cada peça.
 * Para cada peça em cada secção, é gerado um número aleatório entre 0 e 99. Se esse número for menor do que
 * a probabilidade de venda da peça, a peça é considerada vendida e seu preço é adicionado à faturação total da secção.
 * Além disso, o número de série da peça vendida é armazenado num array e a peça é retirada da secção.
 * Caso o array com os numeros de serie esteja cheio irá ser criado um array dinamico temp com o dobro do espaço(dado por tamanho_num_serie), copiados todos os numeros
 * de serie para o temp e desalocada a memoria do array inicial, e depois o array inicial passa a apontar para o temp.
 * Depois disto o tamanho_num_serie é atualizado com o valor duplicado na secção para poder ser usado da proxima vez que for necessario aumentar o tamanho do array
 *
 * @param seccoes_array Um apontador para o array de estruturas de secção contendo as secções a serem simuladas para vendas.
 * @param numero_de_seccoes O número total de secções a serem simuladas.
 */
void prob_venda_geral (seccao*& seccoes_array, int numero_de_seccoes) {
    for (int i = 0; i < numero_de_seccoes; i++) {
        int vendidas = 0;
        seccao seccao_atual = seccoes_array[i];
        seccao_atual.num_serie_vendidos = new int[seccao_atual.capacidade];
        for (int j = 0; j < seccao_atual.quantidade; j++) {
            if (rand() % 100 < seccao_atual.pecas_seccao[j].prob_venda) {
                seccoes_array[i].total_facturacao += seccoes_array[i].pecas_seccao[j].preco;
                facturacao_total_armazem += seccoes_array[i].pecas_seccao[j].preco;

                vendidas++;

                if (seccoes_array[i].quantidade_vendida == seccoes_array[i].tamanho_num_serie - 1) {
                    int *temp = new int[seccoes_array[i].tamanho_num_serie * 2];
                    for (int h = 0; h < seccoes_array[i].tamanho_num_serie; h++) {
                        temp[h] = seccoes_array[i].num_serie_vendidos[h];
                    }
                    delete[] seccoes_array[i].num_serie_vendidos;
                    seccoes_array[i].num_serie_vendidos = temp;
                    seccoes_array[i].tamanho_num_serie *= 2;
                }
                seccoes_array[i].num_serie_vendidos[seccoes_array[i].quantidade_vendida] = seccoes_array[i].pecas_seccao[j].num_serie;
                seccoes_array[i].quantidade_vendida++;

                retirar_peca(seccao_atual, j);
                j--;

            }
        }
        seccoes_array[i].quantidade-=vendidas;

    }
}



/** Variável global
 * Para inicializar e controlar o número de dias do programa
 */
int dia = 0;

/**
 *
 * @param lista_chegada array com tamanho 50 onde as peças são introduzidas antes de serem postas nas secções
 * @param seccoes_array array com tamanho do numero de secções onde as secções são guardadas
 * @param numero_de_seccoes numero de seccoes no armazém
 * @param categorias_pecas array de peças com o tamanho de numero de seccções com as categorias usadas nas secções, este array é usado na criação das peças
 * @param argv argumentos passados na execução do programa com os caminhos dos ficheiros que serão usados para carregar o estado do armazém
 *
 * Esta função tem como objetivo receber os caminhos dos ficheiros como argumentos e usa-los para carregar um estado anterior do armazém
 * Tem um funcionamento igual à função carregar_armazem, exceto a verificação dos argumentos passados e o desalocamento da memoria dos arrays usados no armazém, que não é necessário pois neste caso apenas inicializamos os ponteiros para os arrays necessários.
 *
 * A verificação percorre os argumentos e iguala as variáveis do tipo string ao caminho do ficheiro caso o nome do ficheiro seja igual ao esperado,
 * se alguma variavel não for alterada pois não possui o nome do ficheiro correto, ou seja continuar a ª1ª o programa irá parar com um erro antes de tentar abrir os ficheiros.
 * De seguida a função lê os ficheiros tendo em conta a sua formatação e guarda os dados em arrays e variáveis temporárias que no fim serão apontados pelas variáveis inicializadas no main.cpp e também mudar os valores das variaveis globais do id,ocupacao_lista_chegada e numero_de_seccoes, dia, facturacao_total_armazem.
 * Se algum ficheiro não for aberto corretamente o programa irá apresentar um erro e terminar.
 * Por fim é imprimida uma mensagema a informar o sucesso do carregamento do estado do armazém.
 */
void carrega_por_argumentos(pecas*& lista_chegada, seccao*& seccoes_array, int& numero_de_seccoes, string *& categorias_pecas, char *argv[]){
    string f_caracteristicas = "1";
    string f_pecas = "1";
    string f_numeros_serie = "1";
    string f_seccoes = "1";

    for (int p=1;p<5;p++){
        filesystem::path f(argv[p]);
        if(f.filename()=="caracteristicas.txt"){
            f_caracteristicas=argv[p];
        }
        if(f.filename()=="pecas.txt"){
            f_pecas=argv[p];
        }
        if(f.filename()=="numeros_serie.txt"){
            f_numeros_serie=argv[p];
        }
        if(f.filename()=="seccoes.txt"){
            f_seccoes=argv[p];
        }
    }

    if (f_caracteristicas == "1" or f_pecas == "1" or f_numeros_serie == "1" or f_seccoes == "1"){
        cerr << "Erro nos argumentos, verifique se os caminhos dos ficheiros estao corretos.";
        exit(1);
    }

    char ignora; // para ficar os "|"
/////////////////////////////////////////Características//////////////////////////////////////////////////////////////////

    ifstream caracteristicas(f_caracteristicas);

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
        exit(1);
    }

//////////////////////////////////////Secções///////////////////////////////////////////////////////////////
    ifstream seccoes(f_seccoes);
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
        exit(1);
    }

///////////////////////////////Números de Serie/////////////////////////////////////////////////////////
    ifstream numeros_serie(f_numeros_serie);
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
        exit(1);
    }

/////////////////////////////////////Peças(secções e lista de chegada)/////////////////////////////////////

    ifstream fpecas(f_pecas);

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
            exit(1);
        }

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