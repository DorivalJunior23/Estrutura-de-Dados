#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int i=0;
// ---------------------------------------
// ---------------------------------------
// PtrNoArvore = NoArvore* -> PtrNoArvore
typedef struct NoArvore* PtrNoArvore;
// NoArvore
typedef struct NoArvore {
  char chave[100];// valor armazenado
  PtrNoArvore direita;
  PtrNoArvore esquerda;
} NoArvore;

// ---------------------------------------
// ---------------------------------------
void iniciaArvoreBinaria(PtrNoArvore *r) {
  (*r) = NULL;
}
// ---------------------------------------
// ---------------------------------------
bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
  return((*r) == NULL);
}
// ---------------------------------------
// ---------------------------------------
bool inserirArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base (true, false)
  // 1. NULL (ponto de inserção)
  // Toda vez que achar um NULL é onde vamos inserir o novo elemento:
  if((*no) == NULL) {
    (*no) = (NoArvore*)malloc(sizeof(NoArvore));
    //printf("%s\n ", valor);
    strcpy((*no)->chave,valor);
   //printf("%s\n ", (*no)->chave);
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return (true);
  }
  // 2. no que já possui o valor que eu quero inserir
  if(strcmp((*no)->chave, valor)==0) return (false); // warning

  // clausula recursiva
   if(strcmp(valor,(*no)->chave)>0){
    return(inserirArvoreBinaria(&(*no)->direita, valor));
  } else{
    return(inserirArvoreBinaria(&(*no)->esquerda, valor));
  }
}

// ---------------------------------------
// ---------------------------------------
// print, dir, esq
//PREORDEM
// 1 Printa
// 2 PREORDEM(Esq)
// 3 PREORDEM(Dir)


void PreOrdemArvoreBinaria(PtrNoArvore *no) {
  if((*no) == NULL) return; //clausula base
  printf("%s ", (*no)->chave);
  PreOrdemArvoreBinaria(&(*no)->esquerda);
  PreOrdemArvoreBinaria(&(*no)->direita);
}

void PreOrdemPrincipal(PtrNoArvore *no) {
  printf("PreOrdem = { ");
  PreOrdemArvoreBinaria(&(*no));
  printf("}\n");
}
// ---------------------------------------
// ---------------------------------------

void imprimirSaida(char* valor,char*argv){
  FILE *arqErro;
  char msg[90];
  int resultado;
  arqErro = fopen(argv, "at"); // Cria um arquivo texto para gravação
  if (arqErro == NULL)         // Se não conseguiu criar
  {
    printf("Problemas na CRIACAO do arquivo\n");
    exit(1);
  }
    strcat(valor,"\n");
    strcpy(msg, valor);
    printf("%s ",msg);
    resultado = fputs(msg, arqErro);
    if (resultado == EOF)
    {
        printf("Erro na Gravacao\n");
    }
  fclose(arqErro);
}
// ---------------------------------------
// ---------------------------------------
//EMORDEM
// 1 EMORDEM(Esq)
// 2 Printa
// 3 EMORDEM(Dir)
// ---------------------------------------
// ---------------------------------------
void EmOrdemArvoreBinaria(PtrNoArvore *no,char*argv) {
  if((*no) == NULL) return; //clausula base
  EmOrdemArvoreBinaria(&(*no)->esquerda,argv);
  //printf("%s ",(*no)->chave);
  imprimirSaida((*no)->chave,argv);
  EmOrdemArvoreBinaria(&(*no)->direita,argv);
}
// ---------------------------------------
// ---------------------------------------
void EmOrdemPrincipal(PtrNoArvore *no,char*argv) {
  printf("EmOrdem = { ");
   EmOrdemArvoreBinaria(&(*no),argv);
  printf("}\n");
}
// ---------------------------------------
// ---------------------------------------

bool pesquisaArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base - recursao
 // printf("\nPesquisa = %s \n",valor);
  //printf("Chave = %s \n",(*no)->chave);
  // se o elemento nao existir -> false [ ptr == NULL] [X]
  if((*no) == NULL) return false;
  // se existir o elemento -> true [X]
  if(strcmp((*no)->chave, valor)==0) return (true);
  // recursiva
  if(strcmp(valor,(*no)->chave)>0) {
    return(pesquisaArvoreBinaria(&(*no)->direita, valor));
  } else { // <
    return(pesquisaArvoreBinaria(&(*no)->esquerda, valor));
  }
}
// ---------------------------------------
// ---------------------------------------

int main(int argc, const char * argv[]){
PtrNoArvore raiz;
FILE *arqEntrada;
FILE *arqSaida;
char Linha[1000];
char *resultado;
char arqSaidaRef[50]="";
 iniciaArvoreBinaria(&raiz); //raiz = NULL;

strcat(arqSaidaRef,argv[2]);

arqSaida = fopen(argv[2], "wt");  // abre o arquivo de saida
  if (arqSaida == NULL){ //verificacao de erro
    printf("Warning!: Problemas na criacao do arquivo de saida\n");
     fclose(arqSaida);
     fclose(arqEntrada);
    return 3;
  }


arqEntrada = fopen(argv[1], "rt");
  if (arqEntrada == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
   
  }
 
    
  char termos[8][100];
  memset(&termos[1], 0, sizeof(char*));
   memset(&termos[2], 0, sizeof(char*));//Limpa Vetor
  memset(&termos[4], 0, sizeof(char*));
  char saida[8][100];
  memset(&saida[1], 0, sizeof(char*));
   memset(&saida[2], 0, sizeof(char*));//Limpa Vetor
  memset(&saida[4], 0, sizeof(char*));
  char c[3] = "<";
  int n=0;


  while (!feof(arqEntrada))//ate o arquivo de entrada ser nulo
  {
	// Lê uma linha (inclusive com o '\n')
      resultado = fgets(Linha, 1000, arqEntrada);// o 'fgets' lê até 999 caracteres ou até o '\n'
       if (resultado){ // Se foi possível ler

        //printf("%s\n ", Linha);
      strlwr(Linha);//deixa minusculo a linha do arquivo lida
        //printf("%s\n ", Linha);

      if(i==0){ //aloca os termos da primera linha em um vetor
       char *t;
       memset(&t, 0, sizeof(char*));
       t = strtok(Linha,">");
       t = strtok(Linha,":");
       t=strtok(NULL,",");
       while(t!=NULL){
        memset(&termos[n], 0, sizeof(char*)); //Limpa Vetor
        memset(&saida[n], 0, sizeof(char*)); 
       strcat(termos[n],t);
      // printf("%s\n",termos[n]);
       n++;
       t=strtok(NULL,",");
        }
        for(int x=0;x<n;x++){
         strcat(saida[x],termos[x]);//passa os termos para um vetor de saida
     }
       i++;
      }else if(strncmp("<",Linha,1)==0){//identifica <page>
          //PreOrdemPrincipal(&raiz);
     for(int x=0;x<n;x++){
        // printf("%s \n",termos[x]);
     if(pesquisaArvoreBinaria(&raiz, termos[x])){//pesquisa
         //printf("%s = %i \n",termos[x],i-1);
         char aux[45];
         sprintf(aux,"%s%d", ",", i-1);//coloca no vetor de saida
         strcat(saida[x],aux);
      }
     }
     i++;
      iniciaArvoreBinaria(&raiz); //limpa arvore binaria
      }else{//le as linhas da page separa por palavras e armazena na arvore
	   char *l;
     memset(&l, 0, sizeof(char*));
     l = strtok(Linha,".,; ");
       while(l!=NULL){
       inserirArvoreBinaria(&raiz,l);    
       //printf("%s\n",l);
       l=strtok(NULL,".,;() ");
        }
      }
  }
}
   
//PreOrdemPrincipal(&raiz);
for(int x=0;x<n;x++){//ultima pesquisa
  printf("%s \n",termos[x]);
     if(pesquisaArvoreBinaria(&raiz, termos[x])){
       //  printf("%s = %i \n",termos[x],i-1);
       char aux[45];
         sprintf(aux,"%s%d", ",", i-1);
         strcat(saida[x],aux);
      }
     }
 //iniciaArvoreBinaria(&raiz);
//for(int x=0;x<n;x++){
 // printf("%s \n",termos[x]);
    // inserirArvoreBinaria(&raiz,termos[x]); 
   //  }
 // EmOrdemPrincipal(&raiz);
  iniciaArvoreBinaria(&raiz);//limpa arvore
 //printf("Saida = {");
 for(int x=0;x<n;x++){
 // printf("%s ",saida[x]);
  inserirArvoreBinaria(&raiz,saida[x]); //armazena o vetor de saida na arvore
 }
 //printf("}");
 EmOrdemPrincipal(&raiz,arqSaidaRef);//coloca dentro do arquivo de saida em ordem
  //Fecha arquivo
  fclose(arqEntrada);
  printf("Executado com Sucesso!");//mensagem de sucesso
  return 0;
}
