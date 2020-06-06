# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <fcntl.h>
#include <windows.h>
#include <unistd.h>



//=================== STRUCTS ===============================
typedef struct
{

    int id;
    int prioridade;
    int tamanho;
    int tamanho_rest;
    int quantum;
    char tipo;          //io-bound ou cpu-bound
    int iteracao;
    int preempcao;



} processo;



typedef struct
{

    int tempo;
    int id;


} cpu;



typedef struct
{

    int num_fila;
    int prioridade_fila;
    int id_proc_atual;
    int id_proc_anterior;
    int id_proc_proximo;

} fila;

struct no
{
    processo dado;
    struct no *prox;
};

typedef struct
{

    struct no *inicio;

} Lista;
//------------------------------------------------------------
//=================== variaveis globais ===================

processo proc;
cpu cp;
fila f;

FILE *documento;
int totalLita1;
int totalLita2;
int totalLita3;
int totalLita4;
int totalLita5;
int totalDeProcessos;
int totalExecucoes;
int auxTam;
int aux2;
int temporario;
float tamanhoMedioLista1;
float tamanhoMedioLista2;
float tamanhoMedioLista3;
float tamanhoMedioLista4;
float tamanhoMedioLista5;

int vetorlista1[200];
int vetorlista2[200];
int vetorlista3[200];
int vetorlista4[200];
int vetorlista5[200];
int vetor[35];

int auxTempMedio,auxTamanhoRest;
int contador,i,contaPreempcao, processosTerminados, pCPU, pIO;
FILE *relatorio;
FILE *relatorio2;
FILE *relatorio3;
FILE *relatorio4;
FILE *relatorio5;



//-------------------------------------------------------


void criaListas(Lista *q)
{

    q->inicio=NULL;

}

int isEmpty(Lista *q)
{

    q->inicio=NULL;

}


int insert(Lista * q, processo d)
{
    struct no *aux, *atual, *anterior;
    aux = (struct no *) malloc(sizeof(struct no));
    if (aux!=NULL)
    {
        aux->dado=d;
        aux->prox=NULL;
        anterior = NULL;
        atual = q->inicio;
        while ((atual != NULL) && (d.prioridade > atual->dado.prioridade))
        {
            anterior = atual;
            atual = atual->prox;
        }
        if (anterior == NULL)
        {
            aux->prox = q->inicio;
            q->inicio = aux;
        }
        else
        {
            anterior->prox=aux;
            aux->prox = atual;
        }
    }
}









void criaProcesso();
void GerarProcesso(int temp);
void atualiza_estatisticas(int id, int tempo, int iteracao);
void criaListas(Lista *q);
int isEmpty(Lista *q);
void reemove(Lista *q);
void geraEstatisticas(int total_de_processos,int total_processos_executados);
int insert(Lista *q, processo d);
void executeProcess(int flag_fila, processo proc, Lista *q);



void GerarProcesso(int temp)
{

    int p,probabilidade;
    char escolha;

    p=70;
    probabilidade=rand()%100;

    if(probabilidade<=p)
    {

        contador++;
        criaProcesso(temp);


    }


}



int main()
{
    Lista listaDeProcessos1;
    Lista listaDeProcessos2;
    Lista listaDeProcessos3;
    Lista listaDeProcessos4;
    Lista listaDeProcessos5;

    int flag_fila=0, tecla,temp=0, i=0,k1=0,k2=0,k3=0,k4=0,k5=0;
    contador=0;
    contaPreempcao=0;
    auxTamanhoRest=0;
    processosTerminados=0;
    float throuput=0;
    totalLita1=0;
    totalLita2=0;
    totalLita3=0;
    totalLita4=0;
    totalLita5=0;
    pCPU=0;
    pIO=0;

    documento = fopen("estatisticas.txt","wt");
    relatorio = fopen("relatorio.txt","wt");
    relatorio2 = fopen("relatorio2.txt","wt");
    relatorio3 = fopen("relatorio3.txt","wt");
    relatorio4 = fopen("relatorioIteracoes.txt","wt");
    relatorio5 = fopen("relatorioPreempcao.txt","wt");

    tamanhoMedioLista1 = 0;
    tamanhoMedioLista2 = 0;
    tamanhoMedioLista3 = 0;
    tamanhoMedioLista4 = 0;
    tamanhoMedioLista5 = 0;


    criaListas(&listaDeProcessos1);
    criaListas(&listaDeProcessos2);
    criaListas(&listaDeProcessos3);
    criaListas(&listaDeProcessos4);
    criaListas(&listaDeProcessos5);
    printf("\nESCOLHA O NUMERO DE PROCESSOS: ");
    scanf("%d", &temp);
    temp=temp-1;
    aux2 = temp;
    temporario = temp;

    while(contador<=temp )
    {

        GerarProcesso(temp);


        if(proc.prioridade == 0)
        {
            vetorlista1[k1] = totalLita1;
            k1++;
            insert(&listaDeProcessos1, proc);
            totalLita1++;



            flag_fila=0;

            executeProcess(flag_fila, proc, &listaDeProcessos1);


        }

        else if(proc.prioridade == 1)
        {
            vetorlista2[k2]= totalLita2;
            k2++;
            insert(&listaDeProcessos2, proc);
            totalLita2++;

            flag_fila=0;

            executeProcess(flag_fila, proc, &listaDeProcessos2);


        }

        else if(proc.prioridade == 2)
        {
            vetorlista3[k3]= totalLita3;
            k3++;
            insert(&listaDeProcessos3, proc);
            totalLita3++;



            flag_fila=0;

            executeProcess(flag_fila, proc, &listaDeProcessos3);


        }
        else if(proc.prioridade == 3)
        {
            vetorlista4[k4] = totalLita4;
            k4++;
            insert(&listaDeProcessos4, proc);
            totalLita4++;


            flag_fila=0;
            executeProcess(flag_fila, proc, &listaDeProcessos4);


        }
        else if(proc.prioridade == 4)
        {
            vetorlista5[k5] = totalLita5;
            k5++;
            insert(&listaDeProcessos5, proc);
            totalLita5++;


            flag_fila=0;

            executeProcess(flag_fila, proc, &listaDeProcessos5);


        }
        else
        {
            printf("\nPRIORIDADE FOI DIFERENTE");
        }



    }

    printf("\n ESCALONADOR EXECUTOU COM SUCESSO!!");
    printf("\n FORAM EXECUTADOS Nº %d PROCESSOS EM %d TEMPO DE CPU",totalDeProcessos,cp.tempo);
    printf("\n TOTAL DE PREEMPCOES: %d", contaPreempcao);
    fprintf(relatorio5,"\n NUMERO DE PREEMPCOES: %d", contaPreempcao);
    throuput = calculaThroughtput2();

    calculaMediaFila(vetorlista1);
    calculaMediaFila(vetorlista2);
    calculaMediaFila(vetorlista3);
    calculaMediaFila(vetorlista4);
    calculaMediaFila(vetorlista5);
    printf("\nNUMERO DE PROCESSOS CPU BOUND: %d", pCPU);
    printf("\nNUMERO DE PROCESSOS IO BOUND : %d", pIO);



}



void criaProcesso(int temp)
{
    int i=0;
    int p=30;
    int preempcao=0;
    proc.id = rand()%100;
    proc.prioridade = rand()%5;
    proc.tamanho = 4+rand()%500;
    proc.tamanho_rest= proc.tamanho;
    proc.quantum=proc.tamanho / 2;
    proc.preempcao = rand()%2;
    proc.tipo = rand()%2;
    p = rand()%100;
    if(p<=80)
    {
        proc.tipo = 1;
        pCPU++;
    }
    else
    {

        proc.tipo = 0;
        pIO++;

    }
       if(p<=20)
    {
        proc.preempcao = 1;
    }
    else{

        proc.preempcao = 0;
    }

    totalDeProcessos++;
    return(1);


}





void geraEstatisticas(int total_de_processos,int total_processos_executados)
{

    fprintf(relatorio2,"\nTOTAL DE PROCESSOS GERADOS: %d", total_de_processos);
    fprintf(relatorio2,"\nTOTAL DE PROCESSOS EXECUTADOS: %d", total_processos_executados);

    fprintf(relatorio2,"\n--------------------------------------------------------------");
    fprintf(relatorio3,"\n--------------------------------------------------------------");
    fprintf(relatorio3,"\nTAMANHO MEDIO DE FILA 0: %d", totalLita1);
    fprintf(relatorio3,"\nTAMANHO MEDIO DE FILA 1: %d", totalLita2);
    fprintf(relatorio3,"\nTAMANHO MEDIO DE FILA 2: %d", totalLita3);
    fprintf(relatorio3,"\nTAMANHO MEDIO DE FILA 3: %d", totalLita4);
    fprintf(relatorio3,"\nTAMANHO MEDIO DE FILA 4: %d", totalLita5);
    fprintf(relatorio3,"\nTOTAL DE EXECUÇÕES:  %d", totalExecucoes);
    fprintf(relatorio3,"\n--------------------------------------------------------------");
    fprintf(relatorio2,"\n--------------------------------------------------------------");





}



void atualiza_estatisticas(int id, int tempo, int iteracao)
{


    fprintf(relatorio,"\n PROCESSOS TERMINADOS: ");
    fprintf(relatorio,"\n ID:                 %d",id);
    fprintf(relatorio,"\n TEMPO:              %d", tempo);
    fprintf(relatorio,"\n NUMERO DE ITERACOES DESSE PROCESSO: %d", iteracao);
    fprintf(relatorio,"\n----------------------------------");
    fprintf(relatorio5,"\n----------------------------------");
    fprintf(relatorio5,"\n NUMERO DE PREEMPCOES: %d", contaPreempcao);
    fprintf(relatorio5,"\n TEMPO:              %d", tempo);


}


void executeProcess(int flag_fila, processo proc, Lista *q)
{

    struct no *aux, *atual, *anterior;
    int tempID,temp_Tempo_De_Execucao,iteracao;
    if ((q->inicio)->dado.prioridade == 0)
    {
        totalExecucoes++;
        geraEstatisticas(totalDeProcessos,totalExecucoes);
        printf("\nEXECUTANDO PROCESSO NA FILA 0");
        fprintf(documento,"\nEXECUTANDO PROCESSO NA FILA 0");
        /*if(totalLita1<=10)
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho;          // formula com o tamanho de fila incluso
        }
        if(totalLita1>=11 && totalLita1<=30)
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/2 + ((q->inicio)->dado.tamanho*0.3);
        }
        if(totalLita1>=31)
        {
            (q->inicio)->dado.quantum =(q->inicio)->dado.tamanho/2 + ((q->inicio)->dado.tamanho*0.4);
        }*/

        (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho;
        printf("\nVALOR DA PREEMPCAO: %d", (q->inicio)->dado.preempcao);
    if((q->inicio)->dado.preempcao == 1)
        {
            auxTamanhoRest = (q->inicio)->dado.quantum;
            (q->inicio)->dado.quantum = (q->inicio)->dado.quantum - (auxTamanhoRest * 0.2);
            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
            contaPreempcao++;

        }
        else
        {

            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;

        }

        //(q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;  // execucação do quantum para quando há preempçao
        cp.tempo = cp.tempo + (q->inicio)->dado.quantum;
        if ((q->inicio)->dado.tamanho_rest <= 10)
        {

            tempID = (q->inicio)->dado.id;
            temp_Tempo_De_Execucao = cp.tempo;
            iteracao = (q->inicio)->dado.iteracao;
            processosTerminados++;
            calculaThroughtput(cp.tempo);
            atualiza_estatisticas(tempID, temp_Tempo_De_Execucao,iteracao);



            reemove(&q);
            totalLita1--;


            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTADO");
            fprintf(documento,"\nEXECUTANDO NA FILA: %0");
            fprintf(documento,"\nPRIORIDADE DA FILA:  0");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita1);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);

            fprintf(documento,"\n---------------------------------------------");

            return(0);
        }
        else
        {


            proc.id = (q->inicio)->dado.id;
            proc.prioridade = (q->inicio)->dado.prioridade;
            proc.tamanho = (q->inicio)->dado.tamanho;
            proc.tamanho_rest = (q->inicio)->dado.tamanho_rest;
            proc.quantum = (q->inicio)->dado.quantum;
            proc.iteracao = (q->inicio)->dado.iteracao++;
            printf("\nITERACOES DO PROCESSO: %d",(q->inicio)->dado.iteracao);


            reemove(&q);

            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nEXECUTANDO NA FILA: %0");
            fprintf(documento,"\nPRIORIDADE DA FILA:  0");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita1);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            fprintf(documento,"\nPROCESSO ID    : %d", proc.id);
            fprintf(documento,"\nITERACOES      : %d", proc.id);

            return(1);
        }






    }
    else if((q->inicio)->dado.prioridade ==1)
    {
        int tempID, temp_Tempo_De_Execucao;
        printf("\nEXECUTANDO PROCESSO NA FILA 1");
        fprintf(documento,"\nEXECUTANDO PROCESSO NA FILA 1");

        totalExecucoes++;
        geraEstatisticas(totalDeProcessos,totalExecucoes);

        /*if(totalLita2<=10)
        {
            (q->inicio)->dado.quantum = ((q->inicio)->dado.tamanho/4);          // formula com o tamanho de fila incluso
        }
        if(totalLita2>=11 && totalLita2<=30)
        {
            (q->inicio)->dado.quantum = 6;
        }
        if(totalLita2>=31)
        {
            (q->inicio)->dado.quantum = 3;
        }*/

        (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.2);
        printf("\nVALOR DA PREEMPCAO: %d", (q->inicio)->dado.preempcao);
        if((q->inicio)->dado.tipo == 1)
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.2) + ((q->inicio)->dado.tamanho*0.09);   //cpu bound e io bound
            //pCPU++;
        }
        else
        {

            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.2);
            //pIO++;

        }

        if((q->inicio)->dado.preempcao == 1)
        {                                                                                           //preempção
            auxTamanhoRest = (q->inicio)->dado.quantum;
            (q->inicio)->dado.quantum = (q->inicio)->dado.quantum - (auxTamanhoRest * 0.2);
            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
            contaPreempcao++;

        }
        else
        {


            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;

        }

        //(q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
        cp.tempo = cp.tempo + (q->inicio)->dado.quantum;
        if ((q->inicio)->dado.tamanho_rest <= 10)
        {

            tempID = (q->inicio)->dado.id;
            temp_Tempo_De_Execucao = cp.tempo;
            iteracao = (q->inicio)->dado.iteracao;
            printf("\nITERACOES1 DO PROCESSO: %d",iteracao);
            processosTerminados++;
            calculaThroughtput(cp.tempo);
            atualiza_estatisticas(tempID, temp_Tempo_De_Execucao,iteracao);

            reemove(&q);
            totalLita2--;

            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTADO");
            fprintf(documento,"\nEXECUTANDO NA FILA: %1");
            fprintf(documento,"\nPRIORIDADE DA FILA:  1");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita2);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(0);
        }
        else
        {


            proc.id = (q->inicio)->dado.id;
            proc.prioridade = (q->inicio)->dado.prioridade;
            proc.tamanho = (q->inicio)->dado.tamanho;
            proc.tamanho_rest = (q->inicio)->dado.tamanho_rest;
            proc.quantum = (q->inicio)->dado.quantum;
            proc.iteracao = (q->inicio)->dado.iteracao++;

            aux = q->inicio;
            q->inicio = (q->inicio)->prox;
            //q->inicio = aux->prox;
            free(aux);

            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTANDO ...");
            fprintf(documento,"\nEXECUTANDO NA FILA: %1");
            fprintf(documento,"\nPRIORIDADE DA FILA:  1");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita2);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(1);
        }





    }
    else if((q->inicio)->dado.prioridade ==2)
    {
        int tempID, temp_Tempo_De_Execucao,iteracao;
        printf("\nEXECUTANDO PROCESSO NA FILA 2");
        fprintf(documento,"\nEXECUTANDO PROCESSO NA FILA 2");

        totalExecucoes++;
        geraEstatisticas(totalDeProcessos,totalExecucoes);

        /*if(totalLita3<=10)
        {                                                       // formula com o tamanho de fila incluso
            (q->inicio)->dado.quantum = ((q->inicio)->dado.tamanho/6);
        }
        if(totalLita3>=11 && totalLita3<=30)
        {
            (q->inicio)->dado.quantum = 4;
        }
        if(totalLita3>=31)
        {
            (q->inicio)->dado.quantum = 2;
        }*/

        (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.4);
        printf("\nVALOR DA PREEMPCAO: %d", (q->inicio)->dado.preempcao);
        if((q->inicio)->dado.tipo == 1)
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.4) + ((q->inicio)->dado.tamanho*0.09);       //cpu bound e io bound
            //pCPU++;
        }
        else
        {

            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.4);
            //pIO++;

        }


        if((q->inicio)->dado.preempcao == 1)            //preempção
        {
            auxTamanhoRest = (q->inicio)->dado.quantum;
            (q->inicio)->dado.quantum = (q->inicio)->dado.quantum - (auxTamanhoRest * 0.2);
            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
            contaPreempcao++;

        }
        else
        {


            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;

        }

        //(q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
        cp.tempo = cp.tempo + (q->inicio)->dado.quantum;
        if ((q->inicio)->dado.tamanho_rest <= 10)
        {


            tempID = (q->inicio)->dado.id;
            temp_Tempo_De_Execucao = cp.tempo;
            iteracao = (q->inicio)->dado.iteracao;
            printf("\nITERACOES DO PROCESSO: %d",iteracao);
            processosTerminados++;
            calculaThroughtput(cp.tempo);
            atualiza_estatisticas(tempID, temp_Tempo_De_Execucao,iteracao);


            reemove(&q);
            totalLita3;

            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTADO NA FILA 2");
            fprintf(documento,"\nEXECUTANDO NA FILA: %2");
            fprintf(documento,"\nPRIORIDADE DA FILA:  2");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita3);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(FALSE);
        }
        else
        {

            proc.id = (q->inicio)->dado.id;
            proc.prioridade = (q->inicio)->dado.prioridade;
            proc.tamanho = (q->inicio)->dado.tamanho;
            proc.tamanho_rest = (q->inicio)->dado.tamanho_rest;
            proc.quantum = (q->inicio)->dado.quantum;
            proc.iteracao = (q->inicio)->dado.iteracao++;

            reemove(&q);

            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTANDO ...");
            fprintf(documento,"\nEXECUTANDO NA FILA: %2");
            fprintf(documento,"\nPRIORIDADE DA FILA:  2");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita3);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(TRUE);
        }




    }
    else if((q->inicio)->dado.prioridade ==3)
    {
        int tempID, temp_Tempo_De_Execucao;
        totalExecucoes++;
        geraEstatisticas(totalDeProcessos, totalExecucoes);
        printf("\nEXECUTANDO PROCESSO NA FILA 3");
        fprintf(documento,"\nEXECUTANDO PROCESSO NA FILA 3");

        /*if(totalLita4<=10)
        {
            (q->inicio)->dado.quantum = ((q->inicio)->dado.tamanho/8);
        }
        if(totalLita4>=11 && totalLita4<=30)
        {
            (q->inicio)->dado.quantum = 3;
        }
        if(totalLita4>=31)
        {
            (q->inicio)->dado.quantum = 1;
        }*/
        (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.6);
        printf("\nVALOR DA PREEMPCAO: %d", (q->inicio)->dado.preempcao);

        if((q->inicio)->dado.tipo == 1)                         //cpu bound e io bound
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.6) + ((q->inicio)->dado.tamanho*0.09);
            //pCPU++;
        }
        else
        {

            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.6);
            //pIO++;

        }

        if((q->inicio)->dado.preempcao == 1)                    //preempção
        {
            auxTamanhoRest = (q->inicio)->dado.quantum;
            (q->inicio)->dado.quantum = (q->inicio)->dado.quantum - (auxTamanhoRest * 0.2);
            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
            contaPreempcao++;

        }
        else
        {


            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;

        }

        //(q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
        cp.tempo = cp.tempo + (q->inicio)->dado.quantum;
        if ((q->inicio)->dado.tamanho_rest <= 10)
        {



            tempID = (q->inicio)->dado.id;
            temp_Tempo_De_Execucao = cp.tempo;
            iteracao = proc.iteracao;
            processosTerminados++;
            calculaThroughtput(cp.tempo);
            atualiza_estatisticas(tempID, temp_Tempo_De_Execucao,iteracao);



            reemove(&q);
            totalLita3--;



            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTADO NA FILA 3");
            fprintf(documento,"\nEXECUTANDO NA FILA: %3");
            fprintf(documento,"\nPRIORIDADE DA FILA:  3");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita4);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(FALSE);
        }
        else
        {


            proc.id = (q->inicio)->dado.id;
            proc.prioridade = (q->inicio)->dado.prioridade;
            proc.tamanho = (q->inicio)->dado.tamanho;
            proc.tamanho_rest = (q->inicio)->dado.tamanho_rest;
            proc.quantum = (q->inicio)->dado.quantum;
            proc.iteracao = (q->inicio)->dado.iteracao++;
            printf("\nITERACOES DO PROCESSO: %d",(q->inicio)->dado.iteracao);

            aux = q->inicio;
            q->inicio = (q->inicio)->prox;
            //q->inicio = aux->prox;
            free(aux);


            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTANDO ...");
            fprintf(documento,"\nEXECUTANDO NA FILA: %3");
            fprintf(documento,"\nPRIORIDADE DA FILA:  3");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita4);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(TRUE);
        }





    }
    else if((q->inicio)->dado.prioridade ==4)
    {
        int tempID, temp_Tempo_De_Execucao;
        totalExecucoes++;
        geraEstatisticas(totalDeProcessos, totalExecucoes);
        printf("\nEXECUTANDO PROCESSO NA FILA 4");
        fprintf(documento,"\nEXECUTANDO PROCESSO NA FILA 4");
        /*if(totalLita5<=10)
        {
            (q->inicio)->dado.quantum = ((q->inicio)->dado.tamanho/10);
        }
        if(totalLita5>=11 && totalLita5<=30)
        {
            (q->inicio)->dado.quantum = 2;
        }
        if(totalLita5>=31)
        {
            (q->inicio)->dado.quantum = 1;
        }*/

        (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.8);
        printf("\nVALOR DA PREEMPCAO: %d", (q->inicio)->dado.preempcao);
        if((q->inicio)->dado.tipo == 1)                                 // cpu bound e IO bound
        {
            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.8) + ((q->inicio)->dado.tamanho*0.09);
            //pCPU++;
        }
        else
        {

            (q->inicio)->dado.quantum = (q->inicio)->dado.tamanho/4 + ((q->inicio)->dado.tamanho*0.8);
            //pIO++;

        }

        if((q->inicio)->dado.preempcao == 1)                        //preempção
        {
            auxTamanhoRest = (q->inicio)->dado.quantum;
            (q->inicio)->dado.quantum = (q->inicio)->dado.quantum - (auxTamanhoRest * 0.2);
            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
            contaPreempcao++;

        }
        else
        {


            (q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
        }

        //(q->inicio)->dado.tamanho_rest = (q->inicio)->dado.tamanho_rest - (q->inicio)->dado.quantum;
        cp.tempo = cp.tempo + (q->inicio)->dado.quantum;
        if ((q->inicio)->dado.tamanho_rest <= 4)
        {



            tempID = (q->inicio)->dado.id;
            temp_Tempo_De_Execucao = cp.tempo;
            iteracao = proc.iteracao;
            processosTerminados++;
            calculaThroughtput(cp.tempo);
            atualiza_estatisticas(tempID, temp_Tempo_De_Execucao,iteracao);

            reemove(&q);
            totalLita4--;



            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTADO NA FILA 4");
            fprintf(documento,"\nEXECUTANDO NA FILA: %4");
            fprintf(documento,"\nPRIORIDADE DA FILA:  4");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita5);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");

            return(FALSE);
        }
        else
        {


            proc.id = (q->inicio)->dado.id;
            proc.prioridade = (q->inicio)->dado.prioridade;
            proc.tamanho = (q->inicio)->dado.tamanho;
            proc.tamanho_rest = (q->inicio)->dado.tamanho_rest;
            proc.quantum = (q->inicio)->dado.quantum;
            iteracao = (q->inicio)->dado.iteracao++;
            proc.iteracao = (q->inicio)->dado.iteracao;

            aux = q->inicio;
            q->inicio = (q->inicio)->prox;
            //q->inicio = aux->prox;
            free(aux);


            fprintf(documento,"\n---------------------------------------------");
            fprintf(documento,"\nPROCESSO EXECUTANDO ...");
            fprintf(documento,"\nEXECUTANDO NA FILA: %4");
            fprintf(documento,"\nPRIORIDADE DA FILA:  4");
            fprintf(documento,"\nNUMERO DE PROCESSOS EM FILA:  %d",totalLita5);
            fprintf(documento,"\nPROCESSO ATUAL    : %d", proc.id);
            fprintf(documento,"\nTAMANHO TOTAL     : %d", proc.tamanho);
            fprintf(documento,"\nTAMANHO RESTANTE  : %d", proc.tamanho_rest);
            fprintf(documento,"\nTEMPO DE CPU      : %d", cp.tempo);
            fprintf(documento,"\n---------------------------------------------");


            return(TRUE);
        }


    }








}


void reemove(Lista *q)
{

    struct no *aux,*inicio,*prox;


    aux = q->inicio;
    q->inicio = aux->prox;
    free(aux);

    //return TRUE;



}

void calculaThroughtput(int tempo)          // coleta os dados para futuro calculo do throughput em calculaThroughput2()
{


    if(tempo>0  && tempo <500)
    {
        vetor[1]=vetor[1] + processosTerminados;
    }
    if(tempo>500 && tempo <1000)
    {
        vetor[2]=vetor[2] + processosTerminados;
    }

    if(tempo>1000 && tempo<1500)
    {
        vetor[3] =vetor[3] + processosTerminados;
    }

    if(tempo>1500 && tempo<2000)
    {

        vetor[4]=vetor[4] + processosTerminados;
    }

    if(tempo>2000 && tempo<2500)
    {
        vetor[5]=vetor[5] + processosTerminados;
    }

    if(tempo<2500 && tempo<3000)
    {
        vetor[6]=vetor[6] + processosTerminados;

    }

    if(tempo>3500 && tempo<4000)
    {
        vetor[7]=vetor[7] + processosTerminados;
    }
    if(tempo>4000 && tempo<4500)
    {
        vetor[8]=vetor[8] + processosTerminados;
    }
    if(tempo>4500 && tempo<5000)
    {
        vetor[9]=vetor[9] + processosTerminados;

    }

    if(tempo>5000 && tempo<5500)
    {
        vetor[10]=vetor[10] + processosTerminados;
    }

    if(tempo>5500 && tempo<6000)
    {
        vetor[11]=vetor[11] + processosTerminados;
    }
    if(tempo>6000 && tempo<6500)
    {
        vetor[12]=vetor[12] + processosTerminados;
    }

    if(tempo>6500 && tempo<7000)
    {
        vetor[13]=vetor[13] + processosTerminados;
    }

    if(tempo>7000 && tempo<7500)
    {
        vetor[14]=vetor[14] + processosTerminados;
    }
    if(tempo>7500 && tempo<8000)
    {
        vetor[15]=vetor[15] + processosTerminados;
    }
    if(tempo>8000 && tempo<8500)
    {
        vetor[16]=vetor[16] + processosTerminados;
    }
    if(tempo>8500 && tempo<9000)
    {
        vetor[17]=vetor[17] + processosTerminados;
    }

    if(tempo>9000 && tempo<9500)
    {
        vetor[18]=vetor[18] + processosTerminados;
    }

    if(tempo>9500 && tempo<10000)
    {
        vetor[19]=vetor[19] + processosTerminados;
    }
    if(tempo>10000 && tempo<10500)
    {
        vetor[20]=vetor[20] + processosTerminados;
    }
    if(tempo>10500 && tempo<11000)
    {
        vetor[21]=vetor[21] + processosTerminados;
    }
    if(tempo>11000 && tempo<11500)
    {
        vetor[22]=vetor[22] + processosTerminados;
    }
    if(tempo>12000 && tempo<12500)
    {
        vetor[23]=vetor[23] + processosTerminados;
    }

    if(tempo>12500 && tempo<13000)
    {
        vetor[24]=vetor[24] + processosTerminados;
    }

    if(tempo>13000 && tempo<13500)
    {
        vetor[25]=vetor[25] + processosTerminados;
    }

    if(tempo>13500 && tempo<14000)
    {
        vetor[26]=vetor[26] + processosTerminados;
    }

    if(tempo>14000 && tempo<14500)
    {
        vetor[27]=vetor[27] + processosTerminados;
    }

    if(tempo>14500 && tempo<15000)
    {
        vetor[28]=vetor[28] + processosTerminados;
    }

    if(tempo>15000 && tempo<15500)
    {
        vetor[29]=vetor[29] + processosTerminados;
    }
    if(tempo>15500 && tempo<16000)
    {
        vetor[30]=vetor[30] + processosTerminados;
    }
    if(tempo>16000 && tempo<16500)
    {
        vetor[31]=vetor[31] + processosTerminados;
    }
    if(tempo>16500 && tempo<17000)
    {
        vetor[32]=vetor[32] + processosTerminados;
    }



}


void calculaThroughtput2()                  // calcula o throughput
{
    int i;
    float throuput=0;

    for(i=0; i<=32; i++)
    {
        // printf("\nvalor vetor na posicao %d: %d",i,vetor[i]);
        throuput = throuput +(float)vetor[i];

    }

    throuput = throuput/32;
    printf("\nVALOR DO THROUGHPUT1: %.3f", throuput);
    return throuput;
}

void calculaMediaFila(int vetort[])         // calcula o tamanho medio de fila;
{
    int i;
    float retorno=0;

    for(i=0; i<100; i++)
    {
        retorno = retorno +vetort[i];
    }

    retorno = retorno / 100;
    printf("\n tamanho medio de fila: %.4f", retorno);



}


