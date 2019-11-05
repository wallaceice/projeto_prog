#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Disciplina{
    char codigo[8];
    char *nome;
    int creditos;
    char *Prerequisito;    
}Disciplina;


typedef struct Aluno{
    int ra;
    char nome[256];
    char login[32];
    char senha[16];
}Aluno;

typedef struct matricula{
    int ra;
    int CodigDisciplina;
    int semestre;
    int nota;
    int faltas;

}matricula;

typedef struct ord_matricula{

    matricula *vet;

}ordenacao;

int opcao;
int Login();
int ConsultaD();



int compara(const void *a,const void *b){
    matricula *aux = *(matricula **) a;
    matricula *aux2 = *(matricula **) b;
    
    if(aux->valor > aux2->valor)
        return 1;

    else{
        if(aux->valor < aux2->valor)
            return -1;
    }

    return 0;    

}

void OrdenaMatricula(){

    char *sub;
    char *linha[256];
    char linha_fake[256];
    int c = 0;

    ordenacao aluno;
    aluno->vet = (matricula*) malloc (10000 * sizeof(matricula));

    FILE *fp = fopen("AlunosDisciplinas.txt", "r");

    while(fgets(linha,256,fp)){
        if(strcmp(linha_fake,linha) == 0){
            break;
        }
        strcpy(linha_fake,linha);

        sub = strtok(linha,";");
        aluno->vet[c]->ra = atoi(sub);
        sub = strtok(NULL,";");
        strcpy(aluno->vet[c]->CodigDisciplina,sub);
        sub = strtok(NULL,";");
        aluno->vet[c]->semestre = atoi(sub);
        sub = strtok(NULL,";");
        aluno->vet[c]->nota = atoi(sub);
        sub = strtok(NULL,";");
        aluno->vet[c]->faltas = atoi(sub);
        c++;
    }
    fclose(fp);

    qsort(aluno->vet,c,sizeof(ordenacao *),compara);
    FILE *fp = fopen("AlunosDisciplinas.txt", "w");
    for(int j  = 0; j<c; j++){
        fprintf(fp"%d,"aluno->vet[c]->ra);
        fprintf(fp"%s,"aluno->vet[c]->CodigDisciplina);
        fprintf(fp"%d,"aluno->vet[c]->semestre);
        fprintf(fp"%d,"aluno->vet[c]->nota);
        fprintf(fp"%d,"aluno->vet[c]->faltas);

    }
    fclose(fp);
    
    
}
void Matricula(int ra){
    OrdenaMatricula();
    int semestre;
    int semestre_arq;
    int disciplina;
    FILE *fp = fopen("AlunosDisciplinas.txt", "a+");
    
    printf("\nMenu de Realizar Matrícula\n");
    printf("Digite o semestre: \n");
    scanf("%d", &semestre);
    do{
        printf("Digite a disciplina: \n");
        scanf("%s", &disciplina);
        
    }while(disciplina != "XX000");
    printf("Transação efetuada com sucesso");

}

void Cadastro(){
    
    int ra;
    char nome[256];
    char login[32];
    char senha[16];

    FILE* fp = fopen("Alunos.txt","a");
    Aluno test;
    printf("Menu Cadastro de Alunos:\n\n");
    printf("Digite o RA do Aluno:\n");
    scanf("%d",&test.ra);
    printf("Digite o nome do Aluno:\n");
    getchar();
    fgets(test.nome,256,stdin);
    printf("Digite o login do aluno:\n");
    fgets(test.login,32,stdin);
    printf("Digite a senha:\n");
    fgets(test.senha,16,stdin);
    
    test.nome[strlen(test.nome)-1]= '\0';
    test.login[strlen(test.login)-1]= '\0';
    test.senha[strlen(test.senha)-1]= '\0';

    fprintf(fp,"%d,",test.ra);
    fprintf(fp,"%s,",test.nome);
    fprintf(fp,"%s,",test.login);
    fprintf(fp,"%s\n",test.senha);
    fclose(fp);
}

/*int menuP(){
    printf("\nSistema de Gerência de Disciplinas Semestrais\n\n");
    printf("1- Cadastro de Aluno\n");
    printf("2- Login\n");
    printf("0- Sair do menu\n");
    printf("Digite a opção:\n");
    scanf("%d",&opcao);
    getchar();

    switch(opcao){
        case 0:
            return 0;

        case 1:
            Cadastro();        
            break;
        
        case 2:
            Login();
            break;

        default:
            printf("Opcao inválida");
            break;
    }
}*/

int menu(){
    int a;
    printf("\nMenu de Opcoes\n\n");
    printf("1- Cadastrar de Alunos\n");
    printf("2- Consultar Disciplinas\n");
    printf("3- Realizar Matrícula\n")
    printf("4- Atualizar Nota e Falta\n")
    printf("0- Sair\n");

    scanf("%d",&a);
    getchar();

    switch(a){
        case 1:
            Cadastro();// cadastro aluno em disciplinsa nao implementado
            break;
        
        case 2:
            ConsultaD();        
            break;
        case 3:
            Matricula();
            break;
        case 4:
            Notas();
            break;
        case 0:
            return 0;

        default:
            printf("Opcao inválida");
            break;
    }
}

int Login(){

    char login[32], senha[16], nome[256], nomefake[256];
    int ra;
    // login == entrada o usuario senha == entrada do usuario
    printf("\nLogin:\n");
    fgets(login,32,stdin);
    login[strlen(login)-1] = '\0';

    printf("Senha:\n");
    fgets(senha,16,stdin);

    char log_correto[32];//login Coletados do ARquivo
    char senha_correta[16];/// senha arquivo
    char *sub;

    FILE *fp = fopen("Alunos.txt","r");
    while(fgets(nome,256,fp)){
        if(strcmp(nomefake,nome) == 0){// EOF nao funciona , se o nome se repetir ele quebra o laço
            break;
        }
        strcpy(nomefake,nome);
        sub = strtok(nome,",");// strtok verifica a aparicao de um delimitador no caso ','
        ra = atoi(sub);
        sub = strtok(NULL,",");
        strcpy(nome,sub);
        sub = strtok(NULL,",");
        strcpy(log_correto,sub);
        sub = strtok(NULL,",");
        strcpy(senha_correta,sub);

/*        int compara_log = strcmp(login,log_correto);
        printf("Compara log: %d \nlogin: \nlog_correto:\n%s!\n%s!\n",compara_log,login,log_correto);
        compara_log = strcmp(senha,senha_correta);
        printf("Compara_senha: %d\nsenha:\n senhacorreta:\n%s!\n%s!\n",compara_log,senha,senha_correta);
*/
        if(strcmp(login,log_correto) == 0 && strcmp(senha,senha_correta) == 0){// compara login e senha de uma mesma linha dentro do arquivo com a entrada do usuario
            printf("\nBem vindo %s\n\n", nome);
            menu();
            break;
        }
    }

    fclose(fp);
    if(strcmp(login,log_correto) != 0 && strcmp(senha,senha_correta) != 0){
        printf("Usuario ou senha inválidas\n");
    }
}

int ConsultaD(){
    char linha[256];
    char linha_fake[256];// linha fake mesma logica nome fake
    char codigo[30];
    char nome[50],nomeP[50];// nomep == nome prerequisito
    int creditos,codS = 0,creditoP;// cods == verificacao de algum erro ou invalides creditoP == credito do prerequisito
    char Prerequisito[2][60];
    char *sub;
    char cod_correto[8];

    printf("\nDigite o Codigo da disciplina: ");
    fgets(codigo, 8, stdin);
    codigo[strlen(codigo)-1]= '\0';

    FILE* fp= fopen("Disciplinas.txt","r");
    int c = 0;

    while(fgets(linha, 256, fp)){
        if(strcmp(linha,linha_fake) == 0){
            break;
        }
        strcpy(linha_fake,linha);
        sub = strtok(linha,";");
        strcpy(cod_correto,sub);
        sub = strtok(NULL,";");
        strcpy(nome,sub);
        sub = strtok(NULL,";");
        creditos = atoi(sub);
        fscanf(fp,"\n");

        if(strcmp(codigo,cod_correto) == 0 ){
            codS = 1;// inutil
            break;
        }
    
    }if(codS != 1){
        printf("Codigo invalido\n");
        ConsultaD();
    }
        

    codS = 0;
    fclose(fp);// fecha disciplinas
    fp = fopen("Prerequisitos.txt","r");
    int b = 1;
    while(fgets(linha, 256, fp)){//EOF
        if(strcmp(linha_fake, linha) == 0)// ler duas linhas iguais quebra o laço
            break;
        strcpy(linha_fake, linha);
    //real>>
        //printf("%s\n", linha);
        sub = strtok(linha,";");
        strcpy(cod_correto,sub);
        sub = strtok(NULL,";");
        //printf("%s\n", sub);
        //strcpy(Prerequisito,sub);
        
        if(strcmp(cod_correto,codigo)== 0){//teste de codigo de entrada e codigo
                                                            //lido do arquivo se equivalente quebra o laco e permaneçe no codigo atual lido
        int j = 0;
        int i = 0;
        
            if(sub[5] == ' '){
                sscanf(sub,"%s %s",Prerequisito[0],Prerequisito[1]);
                //printf("teste: %s e %s\n", Prerequisito[0],Prerequisito[1]);
                b = 2;
            }else{
                strcpy(Prerequisito[0],sub);
                //printf("teste: %s\n", Prerequisito[b]);
            }

            codS = 1;
            break;
        }
        Prerequisito[b][strlen(Prerequisito[b])-1] = '\0';
        // printf("valor de b:%d\n", b);

    }if(codS != 1){
        printf("Codigo de disciplina invalido\n");
        ConsultaD();
    }

    fclose(fp);
    int i = 0;
    char *codis[2];
    for(int i = 0; i < 2; i++){
        codis[i] = (char*)malloc(sizeof(char)*5);
    }
    char nomes[2][100];

    //if(strcmp(Prerequisito[b],"Nãohá") == 0){//pre requisito
        // strcpy(nomeP,"Não há");
        // strcpy(nomes[0],"Não há");
    // }else{

    for(i = 0; i < b; i++){
        fp = fopen("Disciplinas.txt","r");
        strcpy(codigo,Prerequisito[i]);
        // printf("%s!\n", codigo);
        
        if (codigo[strlen(codigo) - 1] == '\n')
            codigo[strlen(codigo) - 1] = '\0';

        while(fgets(linha,256,fp)){
            if(strcmp(linha_fake,linha) == 0)
                break;

            strcpy(linha_fake,linha);
            sub = strtok(linha,";");
            strcpy(cod_correto,sub);
            sub = strtok(NULL,";");
            strcpy(nomeP,sub);
            sub = strtok(NULL,";");
            // printf("Pre:%s", nomeP);
            creditoP = atoi(sub);
            fscanf(fp,"\n");
            
            // printf(" \t%s -  %s\t ", cod_correto, codigo);
            if(strcmp(cod_correto,codigo)== 0 ){
                codS = 1;
                break;
            }
        }

        if(codS != 1){
            printf("Codigo de Prerequisito invalido\n");
            ConsultaD();
            fclose(fp);
        }else{
            // printf("teste do codigo %s: \n",codigo);
            strcpy(codis[i],codigo);
            // printf("teste do codigo 2: %s",codis[0]);
            strcpy(nomes[i],nomeP);            
        }
    }
    
    printf("\nNome: %s\n",nome);
    printf("Quantidade de Créditos: %d\n",creditos);
    // printf("Pré-requisitos: %s - %s\n",codigo,nomeP);
    printf("Pré-requisitos: ");
    if(strcmp(codis[0],"Nãohá") == 0){
        printf("Não há requisitos.\n");
    }else{    
        for(int i = 0; i < b; i++){
            printf("%s - %s \n",codis[i],nomes[i]);
        }
    }
    fclose(fp);
    codS = 0;
    
    menu();
}

int main(){

    FILE * fp = fopen("Alunos.txt","r");
    if(fp == NULL){
        fp = fopen("Alunos.txt","w");
        fprintf(fp,"478596,Marcelo Stonks,1,1\n");
        fclose(fp);
    }

    printf("\nSistema de Gerência de Disciplinas Semestrais\n\n");
    printf("1- Cadastro de Aluno\n");
    printf("2- Login\n");
    printf("0- Sair do menu\n");
    printf("Digite a opção:\n");
    scanf("%d",&opcao);
    getchar();

    switch(opcao){
        case 0:
            return 0;

        case 1:
            Cadastro();        
            break;
        
        case 2:
            Login();
            break;

        default:
            printf("Opcao inválida");
            break;
    }    
                
    /*do{
        menuP();
    }while(1);
    */

    return 0;
}
