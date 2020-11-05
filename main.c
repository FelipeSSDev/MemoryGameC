#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define TAML 6
#define TAMC 6

void pedirDimensoesTabuleiro(int *plinha, int *pcoluna){

    printf("Você deverá, em seguida, escolher o número de linhas e colunas de seu jogo.\nOs Valores podem variar entre 3 à 6\n");

    for( ; ; ){

    printf("\nDigite o Número de linhas desejadas: ");
    scanf("%d", plinha);
    printf("\nDigite o Número de colunas desejadas: ");
    scanf("%d", pcoluna);

        if(*plinha < 3 || *plinha > 6){

            printf("\nO valor da linha é inválido\n");

        }else{

            if(*pcoluna < 3 || *pcoluna > 6){

                printf("\nO valor da coluna é inválido\n");

            }else{

                system("cls");
                break;

            }

        }

    }

}

void checaChar(char tab[TAML][TAMC], char *valesp, int *vali, int *valj, int *numutz, int *plinha, int *pcoluna){

    //essencialmente o mesmo que i e j na função preencherTabuleiro
    int  ic, jc;

    for(ic=0 ; ic<*plinha ; ic++){

        for(jc=0 ; jc<*pcoluna ; jc++){

            //impossibilita que a função cheque as mesmas casas do vetor
            if(ic != *vali || jc != *valj){

                //checa os outros valores do vetor para ter certeza de que não existem valores duplicados
                if(tab[ic][jc] == *valesp){

                    //contador. vai adicionar 1 ao valor numutz e será validado caso mais de 1 seja encontrado
                    (*numutz)++;

                }

            }

        }

    }

}

void preencherTabuleiro(char tab[TAML][TAMC], int *plinha, int *pcoluna){

    int  i, j, remain=0, valespnum=0, numutz, linhaR, colunaR, divI;
    char valesp, reves;
    float div=0;

    //gerando a seed para funcionamento da função rand
    srand( (unsigned)time(NULL) );

            /*
             * Criando o limitador de numeros gerados; estes números serão convertidos em letras futuramente.
             * Dependendo dos números de linhas e colunas providos pelo usuário, o número de letras no jogo da memória vai variar.
             * Por este motivo, devemos fazer uma conta básica para determinar esse valor.
             * Caso a divisão por 2 dê um número decimal (float), o valor do float será removido e adaptado à um inteiro,
             * e futuramente adicionado um caracter "?" para substituílo.
             */

            remain = (*plinha)*(*pcoluna)%2;
            if(remain != 0){
            div = ((float)(*plinha)*(*pcoluna)/2)-0.5;

            //adicionando o caractere ? de forma aleatória
            reves = '?';
            linhaR = rand()%((*plinha));
            colunaR = rand()%((*pcoluna));
            tab[linhaR][colunaR] = reves;

            }else{
            div = (*plinha)*(*pcoluna)/2;
            }

            //transformando a div que era um float em um inteiro
            divI = (int)div;

    //preencher o tabuleiro

    for(i=0 ; i<*plinha ; i++){
        for(j=0 ; j<*pcoluna ; j++){


            for( ; ; ){ //este for cria tentativas infinitas para que o programa encontre um valor que não tenha sido utilizado mais de 1 vez e adicione na tabela

                numutz = 0; //esta variável será alterada na função checaChar(), portanto percisa ser igualada a zero no início da função for()

                /*
                 * gera um número aleatório que se tornará um char e armazena em uma variável de espera para a checagem
                 * 65 é o início da tabela ASCII para letras maiúsculas, por esse motivo é criado um range de 65 para o mínimo e 65 + [valor da divI] para o máximo
                 */

                valespnum = rand() % ((65 + divI - 1) + 1 - 65) + 65; //conta referente ao range da função rand
                valesp = (char)valespnum; //transformando em um caracter da tabela ASCII

                //checa o caracter e avalia se o mesmo já foi utilizado mais de uma vez
                checaChar(tab, &valesp, &i, &j, &numutz, plinha, pcoluna);

                if(numutz < 2 && tab[i][j] != reves){

                tab[i][j] = valesp;
                break;

                }else{ //caso as casas sejam ímpares e você encontre o caracter '?', então simplesmente ignora o for e segue em frente

                    if(tab[i][j] == reves){

                        break;

                    }

                }

            }

        }

    }

}

void limparTab(char tab[TAML][TAMC], int *plinha, int *pcoluna){

    int i, j;

    for(i=0; i<*plinha; i++){
        for(j=0; j<*pcoluna; j++){

            tab[i][j] = '#';

        }

    }

}

void construirTabuleiro(char tab[TAML][TAMC], int *plinha, int *pcoluna){


    // Pedir para o usuario as dimensões de linha e coluna
    pedirDimensoesTabuleiro(plinha, pcoluna);

    //limpa tabuleiro
    limparTab(tab, plinha, pcoluna);

    //preencher tabuleiro
    preencherTabuleiro(tab, plinha, pcoluna);


}

void preencherTabuleiroVis(char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *plinha, int *pcoluna){


    int i, j;

    for(i=0; i<*plinha; i++){
        for(j=0; j<*pcoluna; j++){

            tabVis[i][j] = '#';

        }

    }


}

void visualizarTabuleiro(int *i, int *j, int *plinha, int *pcoluna, char tab[TAML][TAMC], char tabVis[TAML][TAMC]){


    printf("\n");

    for(*i=0 ; *i<*plinha ; (*i)++){
            for(*j=0 ; *j<*pcoluna ; (*j)++){

                //caso o tabuleiro gabarito não contenha 'a' ou 't', mostra a forma oculta
                if(tabVis[*i][*j] != 'a' && tabVis[*i][*j] != 't'){
                printf(" - ");
                }

                //caso o tabuleiro gabarito contenha a letra 'a' ou o valor temporário 't', se pode mostrar os valores
                if(tabVis[*i][*j] == 'a' || tabVis[*i][*j] == 't'){
                printf(" %c ", tab[*i][*j]);
                }

                //caso chegue no limite da coluna, pula uma linha
                if(*j == *pcoluna-1){ //é removido 1 do valor da coluna pois o caracter "\0" que está em seu último valor não pode ser preenchido

                    printf("\n");

                }

            }

        }


}

void validaTabuleiro(int *i,int *j, int *plinha, int *pcoluna, char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *val, int *com1L, int *com1C, int *com2L, int *com2C, int *move, int *azar){

    int war1 = 0, war2 = 0;

    if(*azar == 0){

    for(*i=0 ; *i<*plinha ; (*i)++){
        for(*j=0 ; *j<*pcoluna ; (*j)++){

            //valida se o valor já foi encontrado
            if(tabVis[*i][*j] != 'a'){

                //valida se o usuário não selecionou o mesmo local duas vezes
                if(*com1L != *com2L || *com1C != *com2C){

                    *val = 1;

                }else{

                war1 = 1;

                }

            }else{

                if(tabVis[*i][*j] == tabVis[*com1L][*com1C]){

                    war2 = 1;

                }

                if(tabVis[*i][*j] == tabVis[*com2L][*com2C]){

                    war2 = 1;

                }

            }

        }

    }

    if (war1 == 1){

        (*move)--; //remove um movimento para que se realize a ação novamente
        printf("\nVocê selecionou o mesmo valor duas vezes seguidas\n");

    }

    if (war2 == 1){

        (*move)--; //remove um movimento para que se realize a ação novamente
        printf("\nO valor já foi encontrado\n");

    }

    }

}

void comparaValores(int *i, int *j, int *plinha, int *pcoluna, char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *com1L, int *com1C, int *com2L, int *com2C, int *tentativa){

    if(*com2L != 10 && *com2C != 10 && tabVis[*com2L][*com2C] != 'a'){ //valor adicionado ao primeiro movimento para evitar conflitos

        if(tab[*com1L][*com1C] != tab[*com2L][*com2C]){

            visualizarTabuleiro(i, j, plinha, pcoluna, tab, tabVis);
            Sleep(1000 * 3);
            system("cls");

            tabVis[*com1L][*com1C] = '#';
            tabVis[*com2L][*com2C] = '#';


        }else{

            tabVis[*com1L][*com1C] = 'a';
            tabVis[*com2L][*com2C] = 'a';

        }

    }


}

void verificaFim(int *i, int *j, int *plinha, int *pcoluna, char tabVis[TAML][TAMC], int *end){

    int count=0; //conta o número de casas que não são 'a' para jogos de casas ímpares
    *end = 1;

    if((*plinha)*(*pcoluna)/2 == 0){

        for(*i=0 ; *i<*plinha ; (*i)++){
            for(*j=0 ; *j<*pcoluna ; (*j)++){

                if(tabVis[*i][*j] != 'a'){

                    *end = 0;

                }
            }
        }

    }else{

        for(*i=0 ; *i<*plinha ; (*i)++){
            for(*j=0 ; *j<*pcoluna ; (*j)++){

                if(tabVis[*i][*j] != 'a'){

                    *end = 0;
                    count++;

                }
            }
        }

        if(count == 1){ //1 casa restante referente ao coringa. precisamos dessa flexibilidade para tornar possível finalizar o jogo sem encontrar o coringa.

            *end = 1;

        }

    }


}

void destruirJogada(int *i, int *j, int *plinha, int *pcoluna, char tab[TAML][TAMC], char tabVis[TAML][TAMC]){

    int linha, coluna, existe;

    //faz a verificação se um par já foi encontrado

    for(*i=0 ; *i<*plinha ; (*i)++){
        for(*j=0 ; *j<*pcoluna ; (*j)++){

                if(tabVis[*i][*j] == 'a'){

                    existe = 1;

                }

        }
    }

    if(existe == 1){

        for( ; ; ){

            linha = rand() % (*plinha);
            coluna = rand() % (*pcoluna);

            if(tabVis[linha][coluna] == 'a'){

                break;

            }

        }




        tabVis[linha][coluna] = '#';

        for(*i=0 ; *i<*plinha ; (*i)++){
            for(*j=0 ; *j<*pcoluna ; (*j)++){

                if(*i != linha || *j != coluna){

                    if(tab[*i][*j] == tab[linha][coluna]){

                            tabVis[*i][*j] = '#';

                    }

                }

            }

        }

    }


}

void validaCoringa(int *i,int *j, int *plinha, int *pcoluna, char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *com1L, int *com1C, int *com2L, int *com2C, int *move, int *azar){


            if(*move == 1 && tab[*com1L][*com1C] == '?'){

                *move = 0;
                *azar = 1;

                //destrói uma rodada acertada pelo usuário
                destruirJogada(i, j, plinha, pcoluna, tab, tabVis);

                tabVis[*com1L][*com1C] = 'a';

            }

            if(*move == 2 && tab[*com2L][*com2C] == '?'){

                *move = 0;
                *azar = 1;

                //destrói uma rodada acertada pelo usuário
                destruirJogada(i, j, plinha, pcoluna, tab, tabVis);

                tabVis[*com2L][*com2C] = 'a';
                tabVis[*com1L][*com1C] = '#';

            }


}

void jogarMemoria(char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *plinha, int *pcoluna){

    int linhaSel, colunaSel, i, j, move, val=0, com1L, com1C, com2L, com2C, end=0, tentativa=0, azar=0;

    /*
     * for() infinito para tornar possível diversas tentativas, não limitando o jogo em questão
     * caso seja necessário encerrar a função for(), será utilizado um break
     */

    for( ; ; ){

        move=0;

        //verifica se o tabuleiro foi completo
        verificaFim(&i, &j, plinha, pcoluna, tabVis, &end);

        if(end == 1){

            /*
             * Se a quantidade de tentativas for até 30% maior que a quantidade de
             * células, mostrar a mensagem: “Parabéns! Você tem boa memória.”
             */

            if( tentativa <= (30/100)*((*plinha)*(*pcoluna)) ){

                printf("Parabéns! Você tem boa memória");
                break;

            }else{

                printf("Você precisa treinar mais sua memória");
                break;

            }

        }

        for( ; ; ){ //for reference à uma jogada

        tentativa++;
        printf("\ntentativa %d\n", tentativa);

        //mostra na tela o tabuleiro para o jogador
        visualizarTabuleiro(&i, &j, plinha, pcoluna, tab, tabVis);

        printf("\nSelecione uma linha: ");
        scanf("%d", &linhaSel);
        printf("\nSelecione uma coluna: ");
        scanf("%d", &colunaSel);

            if(linhaSel > 0 && linhaSel <= *plinha){

                if(colunaSel > 0 && colunaSel <= *pcoluna){

                move++; // incrementa um movimento na jogada. cada jogada é composta de dois movimentos. cada um abre um campo do tabuleiro.

                if(move==1){ //cada movimento armazena em uma variável diferente o caracter encontrado

                system("cls");

                com2L = 10; //adicionando um valor não permitido para evitar conflitos. esse número será sobrescrito na próxima jogada.
                com2C = 10;
                com1L = linhaSel-1;
                com1C = colunaSel-1;

                //verifica se o jogador selecionou o caractere '?'
                validaCoringa(&i, &j, plinha, pcoluna, tab, tabVis, &com1L, &com1C, &com2L, &com2C, &move, &azar);
                if(move == 0){

                    printf("\nVocê encontrou o coringa, uma jogada correta será apagada (caso exista alguma).\n");
                    break;

                }

                //valida se o campo já está aberto
                validaTabuleiro(&i, &j, plinha, pcoluna, tab, tabVis, &val, &com1L, &com1C, &com2L, &com2C, &move, &azar);

                if(move > 0){ //caso a validação tenha acontecido com sucesso
                tabVis[com1L][com1C] = 't';
                tentativa--;
                }else{
                printf("\nOcorreu um erro, digite novamente\n");
                tentativa--;
                }

                }else{

                    if(move==2){

                    system("cls");

                    com2L = linhaSel-1;
                    com2C = colunaSel-1;

                    //verifica se o jogador selecionou o caractere '?'
                    validaCoringa(&i, &j, plinha, pcoluna, tab, tabVis, &com1L, &com1C, &com2L, &com2C, &move, &azar);
                    if(move == 0){

                        printf("Você encontrou o coringa, uma jogada correta será apagada (caso exista alguma).\n");
                        break;

                    }

                    //valida se o campo já está aberto
                    validaTabuleiro(&i, &j, plinha, pcoluna, tab, tabVis, &val, &com1L, &com1C, &com2L, &com2C, &move, &azar);

                    if(move > 1){ //caso a validação tenha acontecido com sucesso
                    tabVis[com2L][com2C] = 't';

                    comparaValores(&i, &j, plinha, pcoluna, tab, tabVis, &com1L, &com1C, &com2L, &com2C, &tentativa);

                    break;
                    }else{
                    printf("\nOcorreu um erro, digite novamente");
                    tentativa--;
                    }

                    }

                }

                }else{ //validações básicas

                    printf("\nNúmero da coluna é inválido");
                    tentativa--;
                    system("cls");

                }

            }else{

                printf("\nNúmero da linha é inválido");
                tentativa--;
                system("cls");

            }

        }

    }

}

void interacoesTabuleiroVisivel(char tab[TAML][TAMC], char tabVis[TAML][TAMC], int *plinha, int *pcoluna){

    //preenche o tabuleiro visível com caracteres fictícios
    preencherTabuleiroVis(tab, tabVis, plinha, pcoluna);

    //o jogo é realizado nesta função
    jogarMemoria(tab, tabVis, plinha, pcoluna);


}

int main()
{

    int linha, coluna;
    char tabuleiro[TAML][TAMC], tabuleiroVisivel[TAML][TAMC];

    //torna possível a utilização de caracteres especíais da língua portuguesa
    setlocale(LC_CTYPE, "portuguese");

    //armazena os valores aleatórios no tabuleiro gabarito
    construirTabuleiro(tabuleiro, &linha, &coluna);

    interacoesTabuleiroVisivel(tabuleiro, tabuleiroVisivel, &linha, &coluna);

}
