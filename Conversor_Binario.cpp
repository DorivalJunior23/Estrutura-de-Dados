#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//OBS: Deixei alguns printf que usei para observar o andamento do codigo caso voce queira ver


typedef struct {
  int vetor[100];
  int topo;
}pilhaEstatica;
void inicializadorPilha(pilhaEstatica *pilha){
  pilha->topo=0;
}
void empilharPilha(pilhaEstatica *pilha, int x) {
    pilha->vetor[pilha->topo] = x;
    pilha->topo++;
}
void imprimePilha(pilhaEstatica *pilha) {
  printf("Pilha = [");
  for(int i = 0; i < pilha->topo; i++) {
    printf("%d ", pilha->vetor[i]);
  }
  printf("]\n");
}
int desempilhaPilha(pilhaEstatica *pilha) {
  int aux;
   pilha->topo--;
   aux=pilha->vetor[pilha->topo];
   //printf("aux = %i\n",aux);
   return aux;
}
void inverteVetor(int i,int *vetorRecebido){
    int l;
    int vetorAux[i];
for( l=0; l<i;l++) {
        vetorAux[l]=vetorRecebido[i-l-1];
    }
for( l=0; l<i;l++) {
        vetorRecebido[l]=vetorAux[l];
    }
}
int transformaVetorEmDecimal(int i,int *vetorAux){
    //Transforma o vetor binario em um unico valor binario int
    int binario=0;
    int aux=i,m=1;
for(int l=0; l<i ; l++){
  for(int j=0;j<aux-1;j++){
      m*=10;//coloca os numeros em suas casas decimais
  }
  binario+=vetorAux[l]*m;
  aux--;
  m=1;
}
//printf("binario= %i\n", binario);
return binario;
}
int transformaBinario(int decimal){
    if(decimal==1){
        return 1;
    }else if(decimal==0){
        return 0;
    }
    //transforma em binario
    int binario;
    int divisor = 2;
    int resultado;
    int resto;
    int vetorBinario[100];
    int i=0;
    
    while(resultado!=1){//Toda divisao de binario termina em 1
    
    resto = decimal%divisor;
    resultado = decimal/divisor;
    decimal=resultado;
    vetorBinario[i]=resto;
    i++;

    //printf("resultado= %i, resto = %i\n", resultado, resto);

    if(resultado==1){
        vetorBinario[i]=resultado;
    }
    }
    i++;

    //inverte vetor binario unico para ajeitar o valor binario
   
   inverteVetor(i,vetorBinario);
   return binario=transformaVetorEmDecimal(i,vetorBinario);
   
}

int main(int argc, const char * argv[]){
pilhaEstatica pilha;
FILE *arqEntrada;
FILE *arqSaida;
int numero, resultado;
int resultadoSaida;
int vetorEntrada[100];
int contador=0;

inicializadorPilha(&pilha);

printf("Numeros de parametros fornecidos: %i\n",argc);
if(argc!= 3) {//verifica a quantidade de parametros
  printf("Quantidade de parametros invalida\n");
  return 1;
}  
for(int i=0;i<argc;i++){//Mostra os parametros passados
  printf("argv[%i] = %s\n",i,argv[i]);
}
  
//abrindo os arquivos
arqEntrada = fopen(argv[1], "rt"); // abre o arquivo de entrada
if(arqEntrada == NULL){//verificação de erro
  printf("Warning!: Problemas em abrir o arquivo de entrada\n");
  fclose(arqEntrada);
  return 2;
}
arqSaida = fopen(argv[2], "wt");  // abre o arquivo de saida
  if (arqSaida == NULL){ //verificacao de erro
    printf("Warning!: Problemas na criacao do arquivo de saida\n");
     fclose(arqSaida);
     fclose(arqEntrada);
    return 3;
  }


//coloca o arquivo de entrada em um vetor e verifica se o arquivo esta vazio ou se nao ha apenas inteiros
while(resultado!=EOF){
resultado = fscanf(arqEntrada, "%i", &numero); //o 'fscanf' le os numeros do arquivo como o 'scanf' le os do teclado
if(contador>100){//verifica se nao e um inteiro
  printf("Warning!: Arquivo Invalido!");
  resultadoSaida = fprintf(arqSaida,"Warning!: Arquivo Invalido!");
  fclose(arqSaida);
  fclose(arqEntrada);
  return 4;
}
if(resultado!=EOF){
//printf("Linha %i : %i\n",contador,numero);
vetorEntrada[contador]=numero;
contador++;
}
if(contador<1){//verifica se o arquivo esta vazio
  printf("Warning!: Arquivo Vazio Invalido!");
  resultadoSaida = fprintf(arqSaida,"Warning!: Arquivo Vazio Invalido!");
  fclose(arqSaida);
  fclose(arqEntrada);
  return 5;
}
}


//aloca os valores do vetor dentro da pilha estatica, enquanto converte os decimais em binarios
for(int l=0;l<contador;l++){
  printf("vetorEntrada[%i] = %i\n", l , vetorEntrada[l]);
  empilharPilha(&pilha,transformaBinario(vetorEntrada[l]));
  
}
//imprimePilha(&pilha);


//aloca os valores da pilha dentro do arquivo
for (int i = 0; i<contador;i++){
  resultadoSaida = fprintf(arqSaida,"%i\n",desempilhaPilha(&pilha)); //como ao desempilhar os valores saem ao contrario nao ha necessidade de se inverter
  if(resultadoSaida==EOF){
	  printf("Warning!: Erro na Gravacao\n");
    fclose(arqSaida);
    fclose(arqEntrada);
    return 6;
  }
}
  //Fecha arquivos
  fclose(arqSaida);
  fclose(arqEntrada);
  printf("Executado com Sucesso!");
  return 0;
}
