#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_OP 3

struct pessoa { //inicialização da lista ligada para as pessoas
    char nome[30];
    char email[30];
    int identificador;
    struct tarefa* tarefaspessoa[MAX_OP];
    struct pessoa *prox;
    };

struct tarefa { //inicialização da lista ligada para as tarefas
    char nome[50];
    int idtarefa;
    int prioridade;
    int dia, mes, ano;
    int diaf,mesf,anof;
    struct tarefa *prox;
};

struct ToDo{ //inicialização da lista ligada ToDo que consiste apenas de um pointer para a lista tarefa e para a sua proxima posição
    struct tarefa *ptr;
    struct ToDo *prox;
    };

struct Doing { //inicialização da lista ligada Doing com pointers para a lista pessoa e a lista tarefa. Assim como variaveis inteiras para armazenar datas
    struct pessoa *pessoa;
    struct tarefa * ptr;
    int diaprazo,mesprazo,anoprazo;
    int diadeadline,mesdeadline,anodeadline;
    struct Doing *prox;
    };

struct Done //inicialização da lista ligada Done com pointers para a lista pessoa e a lista tarefa
{
    struct pessoa *ptrpessoas;
    struct tarefa *ptrtarefa;
    struct Done *prox;
};

int idtarefas =1 ; //inicialização a 1 do idtarefas que será incrementado sempre que se adicione uma tarefa

void InsereTarefa(int id, struct tarefa *listatarefas,struct ToDo *listatodo)  //funcao para inserir uma nova tarefa na lista tarefa e na lista ToDo
{
    int  priori, erro;
    struct tarefa *tarefanova = malloc(sizeof(struct tarefa)); //alocação da memória a tarefanova
    struct tarefa *temp2 = listatarefas->prox;
    struct ToDo *nodenovo = malloc(sizeof(struct ToDo));  //alocação da memória ao nodenovo
    struct ToDo *ant,*current;  //inicialização de um anterior e de um current para podermos "navegar" a lista ligada com facilidade
    struct tarefa *anterior;
    ant = listatodo;
    current =listatodo->prox; //saltamos o head , apontamos para o primeiro membro
    printf("Nome da Tarefa:");
    scanf(" %[^\n]s ", &tarefanova->nome); //pedido e recolha de informação do nome da tarefa

    printf("Prioridade:");
    erro=1;

   do {           //verificação se a prioridade está entre 0 e 10 e pedido da mesma caso não esteja
    scanf("%d",&priori);
    fflush(stdin);
    if(priori>=0 && priori<=10)
        erro=0;

    else {
            printf("Prioridade invalida, insira de novo:");
            erro=1;
    }

   } while(erro);

    printf("Data (dd mm aa):");         //pedido e recolha da data de criação da tarefa
    scanf("%d", &tarefanova->dia);
    scanf("%d", &tarefanova->mes);
    scanf("%d", &tarefanova->ano);
    tarefanova->prioridade=priori;   //armazenamento da prioridade na lista ligada
    tarefanova->idtarefa=id;         //armazenamento do id na lista ligada

    if(listatarefas->prox == NULL) //caso a lista ligada esteja vazia, ou seja, seja o primeiro membro a ser inserido
    {
        tarefanova->prox = NULL ;  //a proxima posição da tarefa a ser adicionada será NULL
        listatarefas->prox = tarefanova; //a proxima posição da lista das tarefas será então a tarefa a ser adicionada
        nodenovo->ptr = tarefanova;  //o pointer para a lista tarefas da lista ToDo fica a apontar para a posição da tarefa nova
        nodenovo->prox= NULL;       //como também é o primeiro membro da lista ligada, a sua proxima posição sera NULL
        listatodo->prox = nodenovo;   //a proxima posição da lista das ToDo será então a tarefa a ser adicionada
        printf("\n\n");
        return;
    }
    anterior = listatarefas;
    while(temp2!= NULL && temp2->prioridade >= tarefanova->prioridade ) //verificação se existe alguma coisa no proximo elemento da lista tarefas e
    {                                                                   //se a sua prioridade é maior que a prioridade da tarefa a inserir
        ant = ant->prox;              //ant, current, anterior e temp2 passam para a proxima posição
        current = current->prox;
        anterior = anterior->prox;
        temp2 = temp2->prox;        //com este while avançamos para a posição a inserir a nova tarefa. ficando assim as tarefas ordenadas por prioridade
    }
    anterior->prox = tarefanova;     //ao chegar à posição correta, anterior->prox passa a ser a nova tarefa e tarefa->prox passa a ser o temp2
    tarefanova->prox = temp2;
    nodenovo->ptr = tarefanova;     //o pointer para a lista tarefa da lista ToDo fica a apontar para a posiçao atual da tarefanova
    ant->prox = nodenovo;
    nodenovo->prox = current;
    printf("\n\n");
    return ;
}

void printtodo(struct ToDo *lista){ //impressão da lista ToDo

    struct ToDo *aux = lista; //inicialização de uma variavel auxiliar igual à struct ToDo
    aux = aux->prox; //saltar o head

    while(aux != NULL) {
        printf("%d. Tarefa: %s\nPrioridade: %d\nData: %d\\%d\\%d\n\n",aux->ptr->idtarefa, aux->ptr->nome, aux->ptr->prioridade, aux->ptr->dia, aux->ptr->mes, aux->ptr->ano);
        aux=aux->prox; //passagem para o próximo elemento da lista
    }
    printf("\n");
}

void printdoing(struct Doing *listadoing) //impressão da lista Doing
{
    struct Doing *aux = listadoing; //inicialização de uma variavel auxiliar igual à struct Doing
    aux = aux->prox; //saltar o head
    while(aux!= NULL)
    {
        printf("%d. Tarefa: %s  (Pessoa: %s)\n   Data de Inicio: %d\\%d\\%d\n   Data limite: %d\\%d\\%d\n", aux->ptr->idtarefa, aux->ptr->nome, aux->pessoa->nome,aux->diaprazo,aux->mesprazo,aux->anoprazo,aux->diadeadline,aux->mesdeadline,aux->anodeadline);
        aux = aux->prox; //passagem para o próximo elemento da lista
    }
    printf("\n\n");
}

void alterardoing(struct Doing *listadoing,struct pessoa *listapessoas) //alterar a pessoa a realizar uma tarefa escolhida pelo utilizador
{
    int idtarefas,idpessoa;
    char nome[50];
    printdoing(listadoing);  //display das tarefas em doing para o utilizador escolher
    printf("Digite o ID da tarefa que deseja alterar o utilizador:");
    scanf(" %d",&idtarefas); //recolha da escolha do utilizador
    printpessoas(listapessoas); //display das pessoas
    printf("Digite o ID da pessoa:");
    scanf(" %d",&idpessoa); //recolha da escolha
    printf("\n");
    listadoing = listadoing->prox; //saltar o head
    listapessoas = listapessoas->prox;

    while(listapessoas->identificador != idpessoa) //encontrar a pessoa certa na lista pessoa
    {
        listapessoas = listapessoas->prox;
    }
    while(listadoing->ptr->idtarefa != idtarefas) //encontrar a tarefa certa na lista Doing
    {
        listadoing = listadoing->prox;
    }
    if(listadoing->pessoa->identificador == idpessoa) //caso o utilizador escolha a pessoa que ja se encontra a efetuar a tarefa, display de uma mensagem de erro e saida da função
    {
        printf("Essa pessoa ja se encontra a realizar a tarefa selecionada.\n\n");
        return;
    }
    listadoing->pessoa = listapessoas; //o pointer para pessoas da lista Doing passa agora a apontar para a posição onde se encontra a pessoa escolhida pelo utilizador
    return;
}
void moverparaadone(struct Done *listadone,struct Doing *listadoing) //passagem de uma tarefa de Doing para Done
{
    int idt,dd,mm,aa, excede=0;
    struct Done *nodenovo = malloc(sizeof(struct Done)); //alocação de memoria
    struct Done *prevdone,*atualdone;
    struct Doing *prev , *atual; //inicialização de variáveis auxiliares para ajudar a "navegar" as listas
    prev = listadoing;
    atual = listadoing->prox;
    atualdone = listadone->prox;
    prevdone = listadone;
    printdoing(listadoing); //display das tarefas em Doing
    printf("Digite o ID da tarefa que quer terminar:"); //recolha de informaçao do utilizador
    scanf("%d",&idt);
    printf("Introduza a data de conclusao(dd mm aa):");
    scanf("%d",&dd);
    scanf("%d",&mm);
    scanf("%d",&aa);
    while(atual->ptr->idtarefa != idt ) //procura pela posiçao da tarefa escolhida
    {
        prev = prev->prox;
        atual = atual->prox;
    }

    if(aa>atual->anodeadline) //verificação se excede o prazo estipulado de uma semana
        excede=1;

    if(aa==atual->anodeadline)
        if(mm>atual->mesdeadline)
        excede=1;

    if(aa==atual->anodeadline)
        if(mm==atual->mesdeadline)
            if(dd>atual->diadeadline)
            excede=1;

    if(excede)  //mensagem de erro caso exceda
        printf("Atencao! Excedeu o prazo estipulado.\n\n");

    for(int i=0; i<MAX_OP;i++){ //remover a tarefa da lista de tarefas a ser executada pela pessoa
        if(!atual->pessoa->tarefaspessoa[i])
            continue;
        if(atual->pessoa->tarefaspessoa[i]->idtarefa == atual->ptr->idtarefa){
            atual->pessoa->tarefaspessoa[i]=0;
            break;
        }
    }

    if(listadone == NULL) //caso a lista esteja vazia
    {
        nodenovo->ptrpessoas = atual->pessoa; //o pointer passa a apontar para a posição da pessoa
        nodenovo->ptrtarefa = atual->ptr;
        nodenovo->ptrtarefa->diaf = dd;
        nodenovo->ptrtarefa->mesf = mm;
        nodenovo->ptrtarefa->anof = aa;
        nodenovo->prox = NULL;
        listadone->prox = nodenovo;
        prev->prox = atual->prox;
        free(atual);  //libertação da memoria de atual, apagando assim o node da tarefa em Doing
        return;
    }
    while(atualdone != NULL ) //caso a lista não esteja vazia
    {
        if(aa < atualdone->ptrtarefa->anof)
            break;

        if ( aa == atualdone->ptrtarefa->anof)
            if(mm < atualdone->ptrtarefa->mesf)
                break;

        if ( aa == atualdone->ptrtarefa->anof)
            if(mm == atualdone->ptrtarefa->mesf)
                if(dd< atualdone->ptrtarefa->diaf)
                   break;


        atualdone = atualdone->prox;
        prevdone = prevdone->prox;
    }
    nodenovo->ptrpessoas = atual->pessoa; //pointers agora apontam para as posições certas na lista pessoa e na lista tarefa e armazenamento da data
    nodenovo->ptrtarefa = atual->ptr;
    nodenovo->ptrtarefa->diaf = dd;
    nodenovo->ptrtarefa->mesf = mm;
    nodenovo->ptrtarefa->anof = aa;
    nodenovo->prox = atualdone; //introdução do node na lista Done
    prevdone->prox = nodenovo;
    prev->prox = atual->prox;
    free(atual); //libertação da memória de atual, apgando assim a tarefa em Doing
    return;
}

void printdone(struct Done *listadone) //impressão da lista done
{
    struct Done *aux = listadone;
    aux = aux->prox;
    while(aux!= NULL)
    {
        printf("%d. Tarefa: %s  (Feito por: %s)\n   Data de inicio: %d\\%d\\%d\n   Data de conclusao: %d\\%d\\%d\n\n",
               aux->ptrtarefa->idtarefa,aux->ptrtarefa->nome,aux->ptrpessoas->nome,aux->ptrtarefa->dia,aux->ptrtarefa->mes,
               aux->ptrtarefa->ano,aux->ptrtarefa->diaf,aux->ptrtarefa->mesf,aux->ptrtarefa->anof);

        aux = aux->prox ;
    }
    printf("\n\n");
}

void printpessoas(struct pessoa *listapessoas) //impressão da lista pessoas
{
    struct pessoa *temp = listapessoas;
    temp = temp->prox;
    while(temp!=NULL)
    {
        printf("%d. Nome:%s  (Email: %s)\n",temp->identificador, temp->nome,temp->email);
        temp = temp->prox;
    }
    printf("\n");
    printf("\n");
}

void prazo_final(int diai,int mesi,int anoi,int *diaf,int *mesf,int *anof) //função para calcular o deadline de qualquer data dada pelo utilizador
{

    if(mesi==12 && diai>25) {
        *diaf = diai+7-31;
        *mesf = 1;
        *anof = anoi+1;
        return;
    }

    if((mesi== 1 || mesi== 3 || mesi== 5 || mesi== 7 || mesi== 8 || mesi== 10) && diai > 25) {
        *diaf = diai+7-31;
        *mesf = mesi+1;
        *anof = anoi;
        return;
    }

    if((mesi== 4 || mesi== 6 || mesi== 9 || mesi== 11) && diai > 24) {
        *diaf = diai+7-30;
        *mesf = mesi+1;
        *anof = anoi;
        return;
    }

    if((mesi==2 && diai>22)) {
        *diaf=diai+7-28;
        *mesf=3;
        *anof=anoi;
        return ;
    }
    else{
        *diaf = diai + 7;
        *mesf = mesi;
        *anof = anoi;
        return;
    }

}

void moverparadoing(struct ToDo *listatodo , struct Doing *listadoing, struct pessoa *listapessoas) //passar uma tarefa de ToDo para Doing e atribuiçao da pessoa
{
    struct Doing *novonode = malloc(sizeof(struct Doing)); //alocação de memória ao node a ser introduzido na Done
    struct ToDo *anterior,*atual;
    struct Doing *prevdoing,*atualdoing;    //inicialização de variáveis auxiliares para facil "navegação" nas listas
    prevdoing = listadoing;
    atualdoing = listadoing->prox;
    int idpessoa,idtarefa,diai,mesi,anoi,diaf = 0,mesf = 0,anof = 0, aux_introduzido=0;
    printpessoas(listapessoas);

    printf("Selecione o ID da pessoa:");        //recolha da escolha
    scanf("%d",&idpessoa);

    printf("Introduza a data de inicio da realizacao da tarefa(dd mm aa):");
    scanf("%d",&diai);
    scanf("%d",&mesi);
    scanf("%d",&anoi);
    printf("\n");

    novonode->diaprazo=diai;        //armazenamento da data inicial
    novonode->mesprazo=mesi;
    novonode->anoprazo=anoi;

    prazo_final(diai,mesi,anoi,&diaf,&mesf,&anof); //chamada da função prazo_final que devolve o prazo final (deadline) para a conclusão da tarefa

    novonode->diadeadline=diaf;   //armazenamento do prazo (deadline)
    novonode->mesdeadline=mesf;
    novonode->anodeadline=anof;

    listapessoas = listapessoas->prox;
    anterior = listatodo;
    atual= listatodo->prox;

    while(listapessoas->identificador != idpessoa)  //encontrar a posição da pessoa na lista
    {
        listapessoas = listapessoas->prox;
    }

    int pos_tarefa=-1;

    for(int i=0; i<MAX_OP; i++) {       //for para correr o array de pointers correspondente as tarefas da pessoa
        if(!listapessoas->tarefaspessoa[i]) {
            if(pos_tarefa == -1)
                pos_tarefa=i;
        }
        else
        {
            static const int dias_mes[12] = {  //para comparar as datas convertemos a data em dias, então estamos neste array a converter os meses em dias
                0,
                31,
                31 + 28,
                31 + 28 + 31,
                31 + 28 + 31 + 30,
                31 + 28 + 31 + 30 + 31,
                31 + 28 + 31 + 30 + 31 + 30,
                31 + 28 + 31 + 30 + 31 + 30 + 31,
                31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
                31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
                31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
                31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
                31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31
                };

            int inicio_dias_aux = diai + dias_mes[mesi - 1] + anoi * 365; //cálculo e armazenamento da data de inicio
            int prazo_dias_aux = diaf + dias_mes[mesf - 1] + anof * 365; //cálculo e armazenamento da deadline
            int prazo_atual_dias_aux = listapessoas->tarefaspessoa[i]->diaf + dias_mes[listapessoas->tarefaspessoa[i]->mesf - 1] + listapessoas->tarefaspessoa[i]->anof * 365;
                                                                            //cálculo e armazenamento dos dias da tarefa ja inserida no array
            if(inicio_dias_aux > prazo_atual_dias_aux - 7 && inicio_dias_aux < prazo_atual_dias_aux)  //mensagem de erro e saida da função caso a tarefa esteja dentro do prazo
            {
                printf("Erro, este utilizador ja tem uma tarefa atribuida para este prazo\n");
                return;
            }

            if(prazo_dias_aux > prazo_atual_dias_aux - 7 && prazo_dias_aux < prazo_atual_dias_aux)  //mensagem de erro e saida da função caso a tarefa esteja dentro do prazo
            {
                printf("Erro, este utilizador ja tem uma tarefa atribuida para este prazo\n");
                return;
            }
        }
    }

    if(pos_tarefa==-1){  //caso o array esteja cheio
        printf("Essa pessoa ja se encontra a executar 3 tarefas nessa data. Operacao interrompida.\n\n");
        return;
    }

    listapessoas->tarefaspessoa[pos_tarefa] = atual->ptr; //ligação do pointer do array para a posição da tarefa

    atual->ptr->diaf = diaf;  //armazenamento da data
    atual->ptr->mesf = mesf;
    atual->ptr->anof = anof;


    if(listadoing->prox == NULL) //caso a lista esteja vazia
    {
        novonode->pessoa = listapessoas;   //inserção do novo node na lista
        novonode->ptr = atual->ptr;
        novonode->prox = NULL;
        listadoing->prox = novonode;
        anterior->prox = atual->prox;
        free(atual);
        return;
    }
    while((atualdoing != NULL) && strcmp(strlwr(listapessoas->nome),strlwr(atualdoing->pessoa->nome)) > 0 )  //verifica se está em ordem alfabetica e avança na lista ligada caso não esteja
    {
        atualdoing = atualdoing->prox;
        prevdoing = prevdoing->prox;

    }
    novonode->pessoa = listapessoas;  //inserção do novo node na lista
    novonode->ptr = atual->ptr;
    novonode->prox = atualdoing;
    prevdoing->prox = novonode;
    anterior->prox = atual->prox;
    free(atual); //libertação da memória em atual, apagando assim a tarefa no ToDo
    return;
}

void reabrirocartao(struct Done *listadone, struct ToDo *listatodo,struct tarefa *tarefas) //passar uma tarefa de Done para ToDo
{
    int idt;
    struct ToDo *nodenovo = malloc(sizeof(struct ToDo));
    struct Done *prev,*atual;
    struct ToDo *prevtodo,*atualtodo;
    printdone(listadone);
    printf("Introduza o ID da tarefa que pretende reabrir:");
    scanf("%d",&idt);
    prev = listadone;
    atual = listadone->prox;
    int tarefaExiste = 0;
    while(atual!=NULL)   //procura da posição da tarefa escolhida pelo utilizador
    {
        if(atual->ptrtarefa->idtarefa == idt){
            tarefaExiste = 1;
            break;
        }
        prev = prev->prox;
        atual = atual->prox;

    }
    if(tarefaExiste==1){ //caso a tarefa exista
        if(listatodo->prox == NULL && atual != NULL) //caso a lista ToDo esteja vazia
        {
            listatodo->prox = nodenovo;
            nodenovo->ptr = atual->ptrtarefa;
            nodenovo->prox= NULL;
            listatodo->prox = nodenovo;
            prev->prox = atual->prox;
            free(atual);  //libertação da memoria de atual, apagando assim a tarefa em Done
            printf("\n\n");
            return;
        }
        atualtodo = listatodo->prox;
        prevtodo = listatodo;
        while(atualtodo!= NULL && atualtodo->ptr->prioridade > atual->ptrtarefa->prioridade )  //procura pela posição correta para continuar ordenado por prioridade
        {
            prevtodo = prevtodo->prox;
            atualtodo = atualtodo->prox;
        }
        prevtodo->prox = nodenovo; //inserção do novo node na lista ToDo
        nodenovo->ptr = atual->ptrtarefa;
        nodenovo->prox = atualtodo;
        prev->prox = atual->prox;
        free(atual); //libertação da memoria de atual, apagando assim a tarefa em Done
        printf("\n\n");
        return ;
    }
    return;
}

void moverdoingparatodo(struct ToDo *listatodo, struct Doing *listadoing) //passar uma tarefa de Doing para ToDo
{
    int idt;
    struct ToDo *nodenovo = malloc(sizeof(struct ToDo));
    struct Doing *prev,*atual;
    struct ToDo *prevtodo,*atualtodo;
    struct pessoa *pessoa;
    printdoing(listadoing);
    printf("Introduza o ID da tarefa que pretende reabrir:");
    scanf("%d",&idt);
    prev = listadoing;
    atual = listadoing->prox;
    int tarefaExiste = 0;
    while(atual!=NULL) //procura pela posição certa da tarefa
    {
        if(atual->ptr->idtarefa == idt){
            tarefaExiste = 1;
            break;
        }
        prev = prev->prox;
        atual = atual->prox;
    }

    for(int i=0; i<MAX_OP;i++){  //remoção da tarefa do array de pointers para as tarefas da pessoa
        if(atual->pessoa->tarefaspessoa[i]->idtarefa == atual->ptr->idtarefa){
            atual->pessoa->tarefaspessoa[i]=0;
            break;
        }
    }

    if(tarefaExiste==1){
        if(listatodo->prox == NULL && atual != NULL) //caso a lista Doing esteja vazia
        {
            listatodo->prox = nodenovo;
            nodenovo->ptr = atual->ptr;
            nodenovo->prox= NULL;
            listatodo->prox = nodenovo;
            prev->prox = atual->prox;
            free(atual);    //libertação da memoria de atual, apagando assim a tarefa em Doing
            printf("\n\n");
            return;
        }
        atualtodo = listatodo->prox;
        prevtodo = listatodo;
        while(atualtodo!= NULL && atualtodo->ptr->prioridade > atual->ptr->prioridade ) //encontrar a posição correta para continuar ordenado por prioridade
        {
            prevtodo = prevtodo->prox;
            atualtodo = atualtodo->prox;
        }
        prevtodo->prox = nodenovo;
        nodenovo->ptr = atual->ptr;
        nodenovo->prox = atualtodo;
        prev->prox = atual->prox;
        free(atual);   //libertação da memoria de atual, apagando assim a tarefa em Doing
        printf("\n\n");
        return ;
    }
    return;
}

void copiatarefa(struct tarefa *listacopia,struct tarefa *listatarefas)  //criar uma copia da lista de tarefas mas organizada por data
{
     struct tarefa *prev,*atual;
     listatarefas = listatarefas->prox;

     //corre todos os nodes da lista
     while(listatarefas != NULL) {
            prev = listacopia;
            atual = listacopia->prox;

          struct tarefa *novonode = (struct tarefa*)malloc(sizeof(struct tarefa)); //alocara memoria do novo node


          novonode->ano = listatarefas->ano;  //copia da data para o novo node
          novonode->mes = listatarefas->mes;
          novonode->dia = listatarefas->dia;
          novonode->idtarefa = listatarefas->idtarefa;
          strcpy(novonode->nome,listatarefas->nome);
          novonode->prioridade = listatarefas->prioridade;

          if (listacopia == NULL) { //caso a lista esteja vazia

                novonode->prox = NULL;
                listacopia->prox = novonode;
          }
          else {
                while(atual != NULL ) //encontrar a posição correta para o novo node
                {
                    if(novonode->ano < atual->ano)
                        break;

                    if ( novonode->ano == atual->ano)
                        if(novonode->mes < atual->mes)
                            break;

                    if ( novonode->ano == atual->ano)
                        if(novonode->mes == atual->mes)
                            if(novonode->dia < atual->dia)
                            break;
                    prev = prev->prox;
                    atual = atual->prox;
                }
                novonode->prox = atual; //inserção do node na lista copia
                prev->prox = novonode;
          }
          listatarefas = listatarefas->prox;
     }
    return ;
}

void printcopia(struct tarefa *listacopia) //display da lista das tarefas ordenadas por data
{
    struct tarefa * temp = listacopia;
    temp = temp->prox ;
    while(temp!=NULL)
    {
        printf("%d. Tarefa: %s\n",temp->idtarefa, temp->nome);
        printf("Prioridade: %d\n", temp->prioridade);
        printf("Data: %d\\%d\\%d\n ", temp->dia,temp->mes,temp->ano);
        temp = temp->prox;
        printf("\n\n");
    }
    printf("\n");
    printf("\n");
}

void print_tarefaspessoa(struct pessoa *listapessoa){  //display das tarefas a ser realizadas por uma pessoa em especifico

    int idpessoa;

    printpessoas(listapessoa);
    printf("\nIndique qual a pessoa que deseja visualizar:");
    scanf("%d", &idpessoa);

    while(listapessoa!=NULL) {
        if(listapessoa->identificador== idpessoa)
            break;

    listapessoa=listapessoa->prox;
    }


        for(int i=0; i<MAX_OP;i++) {
            if(listapessoa->tarefaspessoa[i]){
                printf("%d. Tarefa: %s\n  Prioridade: %d\n\n", listapessoa->tarefaspessoa[i]->idtarefa,
                        listapessoa->tarefaspessoa[i]->nome, listapessoa->tarefaspessoa[i]->prioridade);
            }
        }
}

int menu_principal() {

    int op;

  printf("1. Adicionar / Atribuir tarefa: \n");
  printf("2. Visualizar pessoas: \n");
  printf("3. Visualizar tarefas: \n");
  printf("4. Visualizar Kanban: \n");
  printf("5. Encerrar programa. \n\n");
  printf("Por favor escolha a operacao que deseja efetuar: ");
  scanf("%d", &op);  //recolha da escolha do utilizador
  printf("\n\n");
  return op;
}

int menu_tarefas() {

    int op;

    printf("1. Adicionar tarefa: \n");
    printf("2. Atribuir uma tarefa a uma pessoa (ToDo -> Doing): \n");
    printf("3. Completar uma tarefa (Doing -> Done): \n");
    printf("4. Reabrir uma tarefa (Done -> ToDo): \n");
    printf("5. Alterar o utilizador de uma tarefa em Doing: \n");
    printf("6. Mover Tarefa (Doing -> ToDo): \n");
    printf("7. Voltar. \n");
    printf("8. Encerrar programa. \n\n");
    printf("Por favor escolha a operacao que deseja efetuar: ");
    scanf("%d", &op); //recolha da escolha do utilizador
    printf("\n\n");
    return op;
}

int switch_tarefa(int operador,int *menu_tarefas, int *acabar,struct tarefas *listatarefas,struct pessoa *pessoas,struct ToDo *listatodo,struct Doing *listadoing,struct Done *listadone){

     switch(operador) {

                case 1:
                    InsereTarefa(idtarefas,listatarefas,listatodo);
                    idtarefas++;
                    return 0;

                case 2:
                    moverparadoing(listatodo,listadoing,pessoas);
                    return 0;
                case 3:
                    moverparaadone(listadone,listadoing);
                    return 0;
                case 4:
                    reabrirocartao(listadone,listatodo,listatarefas);
                    return 0;

                case 5:
                    alterardoing(listadoing,pessoas);
                    return 0;

                case 6:
                    moverdoingparatodo(listatodo,listadoing);
                    return 0;

                case 7:
                    menu_tarefas=1;
                    return 1;

                case 8:
                    menu_tarefas=1;
                    acabar=1;
                    return 1;
            }

}

int menu_visualizar(){

        int op;

        printf("1. Visualizar tarefas ToDo: \n");
        printf("2. Visualizar tarefas Doing: \n");
        printf("3. Visualizar tarefas Done: \n");
        printf("4. Visualizar todas as tarefas : \n");
        printf("5. Visualizar as tarefas por pessoa: \n");
        printf("6. Voltar. \n");
        printf("7. Encerrar programa. \n\n");
        printf("Por favor escolha a operacao que deseja efetuar: ");
        scanf("%d", &op); //recolha da escolha do utilizador
        printf("\n\n");
        return op;
}

int switch_visualizar(int operador, int *acabar,struct ToDo *listaOrdenada,struct Doing *listadoing,struct Done *listadone, struct pessoa *listapessoa,struct tarefa *listacopiada,struct tarefa *listatarefas) {

    switch(operador) {

    case 1:
        printtodo(listaOrdenada);
        return 0;

    case 2:
        printdoing(listadoing);
        return 0;

    case 3:
        printdone(listadone);
        return 0;

    case 4:
        copiatarefa(listacopiada,listatarefas);
        printcopia(listacopiada);
        return 0;

    case 5:
        print_tarefaspessoa(listapessoa);

    case 6:
        return 1;

    case 7:
        acabar=1;
        return 1;
    }
}

void menu_acabar(struct pessoa *listapessoas, struct tarefa *listatarefas, struct ToDo *headtodo, struct Doing *headdoing, struct Done *headdone) {
    char op;
    printf("Deseja guardar as alteracoes (Y\\N): ");
    scanf(" %c", &op);

    listapessoas=listapessoas->prox;
    listatarefas=listatarefas->prox;
    headtodo=headtodo->prox;
    headdoing=headdoing->prox;
    headdone=headdone->prox;  //salta o head

                while(listapessoas) {

                        struct pessoa *aux = listapessoas;
                        listapessoas=listapessoas->prox;
                        free(aux);  //libertação da memória da lista pessoas
                }

       FILE *f =fopen("Tarefas.txt", "w"); //abre o ficheiro Tarefas.txt com a função write

                while(listatarefas){

                        struct tarefa *aux = listatarefas;

                        if(op == 'Y' || op == 'y') //caso requesitado pelo utilizador, armazenamento dos dados num ficheiro .txt
                            fprintf(f,"%s,%d,%d,%d,%d,%d,%d,%d,%d\n", listatarefas->nome, listatarefas->idtarefa,
                                     listatarefas->prioridade, listatarefas->dia, listatarefas->mes, listatarefas->ano,
                                     listatarefas->diaf, listatarefas->mesf, listatarefas->anof);

                        listatarefas=listatarefas->prox;
                        free(aux); //libertação da memória da lista tarefas
                }
                fclose(f); //fecha o ficheiro

        f =fopen("ToDo.txt", "w"); //abre o ficheiro ToDo.txt com a função write

                while(headtodo) {
                        struct ToDo *aux = headtodo;

                        if(op == 'Y' || op == 'y') //caso requesitado pelo utilizador, armazenamento dos dados num ficheiro .txt
                            fprintf(f,"%d\n", headtodo->ptr->idtarefa);

                        headtodo=headtodo->prox;
                        free(aux); //libertação da memória da lista ToDo
                }
                fclose(f); //fecha o ficheiro

        f =fopen("Doing.txt", "w"); //abre o ficheiro Doing.txt

                while(headdoing){
                        struct Doing *aux = headdoing;

                        if(op == 'Y' || op == 'y') //caso requesitado pelo utilizador, armazenamento dos dados num ficheiro .txt
                            fprintf(f,"%d,%d,%d,%d,%d,%d,%d,%d\n",headdoing->pessoa->identificador,
                                     headdoing->ptr->idtarefa, headdoing->diaprazo, headdoing->mesprazo,
                                      headdoing->anoprazo, headdoing->diadeadline, headdoing->mesdeadline, headdoing->anodeadline);

                        headdoing=headdoing->prox;
                        free(aux); //libertação da memória da lista Doing
                }
                fclose(f); //fecha o ficheiro

        f =fopen("Done.txt", "w");  //abre o ficheiro Done.txt com a função write

                while(headdone){
                        struct Done *aux = headdone;

                        if(op == 'Y' || op == 'y')  //caso requesitado pelo utilizador, armazenamento dos dados num ficheiro .txt
                            fprintf(f,"%d,%d\n", headdone->ptrpessoas->identificador, headdone->ptrtarefa->idtarefa);

                        headdone=headdone->prox;
                        free(aux); //libertação da memória da lista Done
                }
                fclose(f); //fecha o ficheiro



    printf("As alteracoes foram guardadas com sucesso.\n");

    printf("Ate a proxima.\n");
}

void recupera_dados(struct pessoa *listapessoas, struct tarefa *listatarefas, struct ToDo *headtodo, struct Doing *headdoing, struct Done *headdone) {
                            //função para guardar os dados dos ficheiros .txt nas respetivas listas ligadas
        struct pessoa *listapessoas_copia = listapessoas; // cria uma copia de todos os parametros porque vamos incrementá-los mais tarde
        struct tarefa *listatarefas_copia = listatarefas;
        struct ToDo *headtodo_copia = headtodo;
        struct Doing *headdoing_copia = headdoing;
        struct Done *headdone_copia = headdone;
        char *buff = malloc(256); // aloca um buffer para guardar os dados (linhas) dos ficheiros
        int temp, buff_pos=0; // pointer para a localização na qual vamos escrever no buffer e espaço temporário para o caracter lido

        FILE *f =fopen("Pessoas.txt", "r"); // abre o ficheiro pessoas

                    while(temp = fgetc(f)){ // enquanto houver conteúdo

                        if(temp=='\n' || temp==-1){ // se o conteúdo for um EOL ou EOF (-1) significa que podemos interpretar os dados

                            if(buff_pos) { // só interpreta se tiver lido alguma coisa

                                buff[buff_pos]=0; // o último caracter lido tem de ser nulo para as funções xscanf não ficarem presas

                                struct pessoa *aux = malloc(sizeof(struct pessoa)); // novo membro da lista pessoas
                                char* buff_aux=buff; // cópia do pointer para o buffer para nunca perdermos a localização original
                                memset(aux, 0, sizeof(struct pessoa)); // zerar a memória do novo membro

                                sscanf(buff_aux,"%[^,]s", aux->nome); // lê o nome até encontrar uma virgula
                                buff_aux=strstr(buff_aux, ",") + 1; // avança o pointer de leitura

                                sscanf(buff_aux,"%[^,]s", aux->email); // lê o email até encontrar uma virgula
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->identificador); // lê o id da pessoa


                                listapessoas->prox=aux; // define o link do elemento anterior para o próximo (o novo que acabamos de criar)
                                listapessoas=aux; // o elemento anterior passa a ser o que acabamos de criar, para continuar a lista
                            }


                            if(temp==-1){ // se for um EOF
                                free(buff); // liberta a memória alocada para o buffer
                                break; // sai do loop
                            }

                            buff_pos=0; // se for só um EOL, quer dizer que há mais linhas para ler, coloca o ponteiro para o buffer a 0
                            buff = realloc(buff, 256); // reduz o tamanho do buffer para o original
                        }

                        else {

                            if(buff_pos!=0 && buff_pos % 256 == 0) // se tivermos usado todo o buffer
                                buff = realloc(buff, buff_pos + 256); // aloca mais memória

                            buff[buff_pos++]=temp; // escreve o caracter que acabamos de ler e incrementa o pointer para o buffer
                        }

                    }
        fclose(f);

            buff = malloc(256);
            buff_pos=0;

            f =fopen("Tarefas.txt", "r");

                    while(temp = fgetc(f)){

                        if(temp=='\n' || temp==-1){

                            if(buff_pos) {

                                buff[buff_pos]=0;
                                struct tarefa *aux = malloc(sizeof(struct tarefa));
                                char* buff_aux=buff;
                                memset(aux, 0, sizeof(struct tarefa));

                                sscanf(buff_aux,"%[^,]s", aux->nome);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->idtarefa);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->prioridade);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->dia);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->mes);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->ano);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->diaf);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->mesf);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->anof);

                                // restaura o id da proxima tarefa
                                if(aux->idtarefa >= idtarefas) // se o id desta tarefa for maior que o id inicial de tarefas
                                    idtarefas = aux->idtarefa + 1; // coloca o id global certo para não termos tarefas com o mesmo ID

                                listatarefas->prox=aux;
                                listatarefas=aux;
                            }


                            if(temp==-1){
                                free(buff);
                                break;
                            }

                            buff_pos=0;
                            buff = realloc(buff, 256);
                        }

                        else {

                            if(buff_pos!=0 && buff_pos % 256 == 0)
                                buff = realloc(buff, buff_pos + 256);

                            buff[buff_pos++]=temp;
                        }
                }


        fclose(f);

        buff = malloc(256);
        buff_pos=0;


        f =fopen("ToDo.txt", "r");

                    while(temp = fgetc(f)){

                        if(temp=='\n' || temp==-1){

                            if(buff_pos) {

                                buff[buff_pos]=0;
                                struct tarefa *listatarefas_aux = listatarefas_copia;
                                struct ToDo *aux = malloc(sizeof(struct ToDo));
                                int idtarefa=-1;
                                memset(aux, 0, sizeof(struct ToDo));

                                sscanf(buff,"%d", &idtarefa);
                                listatarefas_aux=listatarefas_aux->prox;

                                while(listatarefas_aux){ // loop para procurar a tarefa na lista tarefas

                                    if(listatarefas_aux->idtarefa == idtarefa){ // encontrou
                                        aux->ptr=listatarefas_aux; // atribui o pointer certo
                                        break;
                                    }

                                    listatarefas_aux=listatarefas_aux->prox;
                                }

                                if(aux->ptr) { // se tivermos encontrado uma tarefa com este ID
                                    headtodo->prox=aux; // cria o link na lista
                                    headtodo=aux; // a cabeça passa a ser este elemento
                                }
                            }

                            if(temp==-1){
                                free(buff);
                                break;
                            }

                            buff_pos=0;
                            buff = realloc(buff, 256);
                        }

                        else {

                            if(buff_pos!=0 && buff_pos % 256 == 0)
                                buff = realloc(buff, buff_pos + 256);

                            buff[buff_pos++]=temp;
                        }

                    }
        fclose(f);

            buff = malloc(256);
            buff_pos=0;


             f =fopen("Doing.txt", "r");

                    while(temp = fgetc(f)){

                        if(temp=='\n' || temp==-1){

                            if(buff_pos) {

                                buff[buff_pos]=0;
                                char* buff_aux=buff;
                                struct tarefa *listatarefas_aux = listatarefas_copia;
                                struct pessoa *listapessoas_aux = listapessoas_copia;
                                struct Doing *aux = malloc(sizeof(struct Doing));
                                int idtarefa=-1, idpessoa=-1;
                                memset(aux, 0, sizeof(struct Doing));

                                sscanf(buff_aux,"%d", &idpessoa);
                                buff_aux=strstr(buff_aux, ",") + 1;
                                sscanf(buff_aux,"%d", &idtarefa);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                listatarefas_aux=listatarefas_aux->prox;

                                while(listatarefas_aux){

                                    if(listatarefas_aux->idtarefa == idtarefa){
                                        aux->ptr=listatarefas_aux;
                                        break;
                                    }

                                    listatarefas_aux=listatarefas_aux->prox;
                                }

                                listapessoas_aux=listapessoas_aux->prox;


                                while(listapessoas_aux){ // loop para encontrar a pessoa com este ID

                                        if(listapessoas_aux->identificador == idpessoa){
                                            aux->pessoa=listapessoas_aux;

                                            for(int i=0;i<MAX_OP;i++){ // coloca a tarefa no array das tarefas dentro desta pessoa, numa posição livre
                                                if(!listapessoas_aux->tarefaspessoa[i]){
                                                    listapessoas_aux->tarefaspessoa[i] = aux->ptr;
                                                    break;
                                                }
                                            }

                                            break;
                                        }

                                    listapessoas_aux=listapessoas_aux->prox;
                                }

                                sscanf(buff_aux,"%d", &aux->diaprazo);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->mesprazo);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->anoprazo);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->diadeadline);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->mesdeadline);
                                buff_aux=strstr(buff_aux, ",") + 1;

                                sscanf(buff_aux,"%d", &aux->anodeadline);


                                if(aux->ptr) {
                                    headdoing->prox=aux;
                                    headdoing=aux;
                                }
                            }

                            if(temp==-1){
                                free(buff);
                                break;
                            }

                            buff_pos=0;
                            buff = realloc(buff, 256);
                        }

                        else {

                            if(buff_pos!=0 && buff_pos % 256 == 0)
                                buff = realloc(buff, buff_pos + 256);

                            buff[buff_pos++]=temp;
                        }

                    }
        fclose(f);

            buff = malloc(256);
            buff_pos=0;

            f =fopen("Done.txt", "r");

                    while(temp = fgetc(f)){

                        if(temp=='\n' || temp==-1){

                            if(buff_pos) {

                                buff[buff_pos]=0;
                                char* buff_aux=buff;
                                struct tarefa *listatarefas_aux = listatarefas_copia;
                                struct pessoa *listapessoas_aux = listapessoas_copia;
                                struct Done *aux = malloc(sizeof(struct Done));
                                int idtarefa=-1, idpessoa=-1;
                                memset(aux, 0, sizeof(struct Done));

                                sscanf(buff_aux,"%d", &idpessoa);
                                buff_aux=strstr(buff_aux, ",") + 1;
                                sscanf(buff_aux,"%d", &idtarefa);

                                listatarefas_aux=listatarefas_aux->prox;

                                while(listatarefas_aux){

                                    if(listatarefas_aux->idtarefa == idtarefa){
                                        aux->ptrtarefa=listatarefas_aux;
                                        break;
                                    }

                                    listatarefas_aux=listatarefas_aux->prox;
                                }

                                listapessoas_aux=listapessoas_aux->prox;


                                while(listapessoas_aux){

                                        if(listapessoas_aux->identificador == idpessoa){
                                            aux->ptrpessoas=listapessoas_aux;
                                            break;
                                        }

                                    listapessoas_aux=listapessoas_aux->prox;
                                }


                                if(aux->ptrtarefa) {
                                    headdone->prox=aux;
                                    headdone=aux;
                                }
                            }

                            if(temp==-1){
                                free(buff);
                                break;
                            }

                            buff_pos=0;
                            buff = realloc(buff, 256);
                        }

                        else {

                            if(buff_pos!=0 && buff_pos % 256 == 0)
                                buff = realloc(buff, buff_pos + 256);

                            buff[buff_pos++]=temp;
                        }

                    }
        fclose(f);
}

int main()
{
  struct tarefa *listatarefas = NULL;           //inicialização das cabeças de lista e alocação da memória
      listatarefas =(struct tarefa *)calloc(sizeof(struct tarefa),1);
      struct pessoa *listapessoas = NULL;
      listapessoas = (struct pessoa*)malloc(sizeof(struct pessoa));
      memset(listapessoas, 0, sizeof(struct pessoa));  //inicialização da memoria a 0's
      struct ToDo *headtodo = NULL;
      headtodo =(struct ToDo*)calloc(sizeof(struct ToDo),1);
      struct Doing *headdoing = NULL;
      headdoing = (struct Doing*)calloc(sizeof(struct Doing),1);
      struct Done *headdone = NULL;
      headdone = (struct Done*)calloc(sizeof(struct Done),1);
      struct tarefa * listacopiada = NULL;
      listacopiada = (struct tarefa*)calloc(sizeof(struct tarefa),1);
      listacopiada->prox = NULL;
      listatarefas->prox=NULL;
      listapessoas->prox=NULL;
      headtodo->prox=NULL;
      headdoing->prox=NULL;
      headdone->prox=NULL;
      int op, op2, op3, acabar=0, switch_t=0, switch_v=0;
      char dados;

  printf("________________________________________________________________\n");
  printf("|                           BEM VINDO                           |\n");
  printf("|_______________________________________________________________|\n");
  printf("\n\n\n");

  printf("Deseja carregar os dados guardados(Y\\N)? ");
  scanf(" %c", &dados);
  printf("\n");

  if(dados == 'Y' || dados == 'y')
    recupera_dados(listapessoas, listatarefas, headtodo, headdoing, headdone);

  while(!acabar) {  //while para estar sempre a correr os switchs dos menus
    op=menu_principal();

        switch(op) {  //switch principal

        case 1:
            switch_t=0;
            while(!switch_t){ //mantém-se no switch tarefas enquanto o return das tarefas for 0

                op2=menu_tarefas();
                switch_t = switch_tarefa(op2, menu_tarefas, acabar,listatarefas,listapessoas,headtodo,headdoing,headdone);
            }
            break;

        case 2:
            printpessoas(listapessoas);
            break;

        case 3:
            switch_v=0;
            while(!switch_v){ //mantém-se no switch visualizar enquanto o return das tarefas for 0

                op3=menu_visualizar();
                switch_v = switch_visualizar(op3, acabar,headtodo,headdoing,headdone, listapessoas,listacopiada,listatarefas);
            }
            break;

        case 4: //display da lista KanBan
            printf("TAREFAS EM TODO\n\n");
            printtodo(headtodo);
            printf("_____________________________________\n\n");
            printf("TAREFAS EM DOING\n\n");
            printdoing(headdoing);
            printf("_____________________________________\n\n");
            printf("TAREFAS EM DONE\n\n");
            printdone(headdone);
            printf("\n\n");
            break;

        case 5:
            acabar=1;  //faz com que saia do while
            break;

        }
  }

  menu_acabar(listapessoas, listatarefas, headtodo, headdoing, headdone); //chamada da função menu_acabar onde é guardada a informação em ficheiros

return 0;
}  //fim do programa
