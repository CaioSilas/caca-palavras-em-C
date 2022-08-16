  // caio silas de araujo amaro
 //turma:41
//matrizricula:21.1.4111

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cor2.h"
#include <time.h>
#include <ctype.h>

typedef struct 
{
  char palavra[30];
  int inicio_lin;
  int inicio_col;
  int termino_lin;
  int termino_col;
  int achou;
}Localizacao;

typedef struct 
{
  char cmd[30];
  int p_lin;
  int p_col;
  int pt_lin;
  int pt_col;
}Comando;

typedef struct 
{
  char cmd[30];
  char palavra[30];
  int p_lin;
  int p_col;
  int pt_lin;
  int pt_col;
}ComandoSal;

typedef struct
{
  int cont;
  int reg;
}Contador;

int menu(){
  printf("\n./caca-palavra\n\n");
  printf("Bem vindo ao caca palavra\nO que deseja fazer:\n\n");

  //escolhendo a opção inicial
  printf("1. comecar um novo jogo\n2. continuar um existente\n3. ver instrucoes de como jogar\n\n\n");
  printf("Escolha a opcao(digite sair em qualquer lugar para sair do jogo): ");

  char inicio[5];
  scanf("%s",inicio);
  while (1)
  {
    if (strcmp(inicio,"sair") == 0){
      exit(0);
    }
    else if (strcmp(inicio,"1") == 0){
      return 1;
    }
    else if (strcmp(inicio,"2") == 0){
      return 2;
    }
    else if (strcmp(inicio,"3") == 0){
      return 3;
    }
    else {
      printf("comando invalido\n");
      exit(0);
    }
  }
  return 0;
}
void regras(){
    printf(BOLD(WHITE("marcar : para marcar uma palavra encontrada. O usuario deve digitar, logo apos o comando digitar as coordenadas de inıcio e fim\nda palavra, respectivamente. Exemplo: “marcar CD CJ” indica que a palavra comeca na linha “C”, coluna “D”\ne termina na linha“C”, coluna “J”.")) "\n\n");
    printf(BOLD(WHITE("salvar : para armazenar em um arquivo o jogo em seu estado atual. O usuario deve digitaro nome do arquivo logo apos\no comando. Exemplo: “salvar jogo.txt” salva o jogo no arquivo “jogo.txt”.")) "\n\n");
    printf(BOLD(WHITE("resolver : exibe a matriz resolvida com as palavras em destaque e finaliza o jogo.")) "\n\n");
    printf(BOLD(WHITE("sair : encerra o programa, abandonando o jogo (sem salvar as alteracoes).")) "\n\n");
    printf(BOLD(GREEN("FACIL (1) : no nivel facil, as palavras devem ser dispostas na horizontal ou na vertical\nAs palavras na horizontal devem ser lidas da esquerda para a direita, enquanto as palavras na vertical devem ser lidas de cima para baixo.\n")) "\n");
    printf(BOLD(YELLOW("MEDIO (2) : no nıvel medio, as palavras podem ser dispostas como no nivel facil e tambem na diagonal, sempre da esquerda\npara direita.")) "\n\n");
    printf(BOLD(RED("DIFICIL (3) : no nıvel difıcil, as palavras podem ser dispostas na horizontal, vertical e diagonal.\nA diferenca dos demais nıveis e que as palavras podem ser lidas tambem de baixo para cima e da direita para a esquerda")) "\n\n");

}
char **criaMatrizR(int linha,int coluna){
    char **matriz;
    matriz = calloc(linha , sizeof(char*));
    for (int i = 0; i < linha;i++){
        matriz[i] = calloc(coluna , sizeof(char));
    }
    if (matriz == NULL){
      printf("matriz errro");
      exit(1);
    }
    return matriz;
}
void desaloca_matriz(char **A, int linha)
{
  for (int i = 0; i < linha;i++){
    free(A[i]);
  }
  free(A);
}
char **facil(char **tabu,char **matriz,int numero,int lin,int col,Localizacao *loca){
  srand(time(NULL));
  for (int i = 0; i < numero;i++){
    int tan = strlen(matriz[i]); 
    

    int controle = 0;
    int cont = 0;
    
    while (!controle)
    {
      controle = 1;
      cont++;
      
      int opcao = rand() %2;
      if (opcao == 0)//horizontal
      {
        int linp = rand () %(lin);
        int colp = col > tan ? rand () %(col - tan) : 0;
        int inlin = linp;
        int incol = colp;
        int j = 0;
        int finlin,fincol;
        //verifica a possibilidade da palavra caber na matrix
        for (j = 0; j < tan;j++){
          if (tabu[linp][colp + j] != matriz[i][j] && tabu[linp][colp + j] != 0){
            controle = 0;
          }
        }
        if (controle){
          for (int j = 0;j < tan; j++){
            tabu [linp][colp + j] = matriz[i][j];
            finlin = linp;
            fincol = colp + j;
          }
          //salvando a localização da palavra
          strcpy(loca[i].palavra,matriz[i]);
          loca[i].inicio_lin = inlin;
          loca[i].inicio_col = incol;;
          loca[i].termino_lin = finlin;
          loca[i].termino_col = fincol;
        }
      }
      else if(opcao == 1)//vertical
      {
        //printf("tentando vertical\n");
        int linp = lin > tan ? rand () %(lin - tan) : 0;
        int colp = rand () %(col);
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //verifica a posicao selecionada
        //palavras ja selecionadas
        for (int j = 0; j < tan;j++){
          if (tabu[linp +j][colp] != matriz[i][j] && tabu[linp + j][colp] != 0){
            controle = 0;
          }
        }
        if (controle){
          for (int j = 0;j < tan; j++){
            tabu [linp + j][colp] = matriz[i][j];
            finlin = linp +j;
            fincol = colp;
          }
          //salvando a localização da palavra
          strcpy(loca[i].palavra,matriz[i]);
          loca[i].inicio_lin = inlin;
          loca[i].inicio_col = incol;;
          loca[i].termino_lin = finlin;
          loca[i].termino_col =fincol;
        }
      }
      
      if (cont >= 20){
        break;
      }
    }
    if (cont >= 20){
      break;
    }
  }

  return tabu;
}
char **medio(char **tabu,char **matriz,int numero,int lin,int col,Localizacao *loca){
  srand(time(NULL));
  for (int i = 0; i < numero;i++){
    int tan = strlen(matriz[i]); 

    int controle = 0;
    int cont =0;
    while (!controle)
    {
      controle = 1;
      cont++;
      
      int opcao = rand () %3;
      if (opcao == 0)//horizontal
      {
        int linp = rand () %(lin);
        int colp = col > tan ? rand () %(col - tan) : 0;
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //verifica a posicao selecionada
        //palavras ja selecionadas
        for (int j = 0; j < tan;j++){
          if (tabu[linp][colp + j] != matriz[i][j] && tabu[linp][colp + j] != 0){
            controle = 0;
          }
        }
        if (controle){
          for (int j = 0;j < tan; j++){
            tabu [linp][colp + j] = matriz[i][j];
            finlin = linp;
            fincol = colp +j;
          }
          //salvando a localização da palavra
          strcpy(loca[i].palavra,matriz[i]);
          loca[i].inicio_lin = inlin;
          loca[i].inicio_col = incol;;
          loca[i].termino_lin = finlin;
          loca[i].termino_col = fincol;
        }
      }
      else if(opcao == 1)//vertical
      {
        // printf("tentando vertical\n");
        int linp = lin > tan ? rand () %(lin - tan) : 0;
        int colp = rand () %(col);
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //verifica a posicao selecionada
        //palavras ja selecionadas
        for (int j = 0; j < tan;j++){
          if (tabu[linp +j][colp] != matriz[i][j] && tabu[linp + j][colp] != 0){
            controle = 0;
          }
        }
        if (controle){
          for (int j = 0;j < tan; j++){
            tabu [linp + j][colp] = matriz[i][j];
            finlin = linp +j;
            fincol = colp;
          }
          //salvando a localização da palavra
          strcpy(loca[i].palavra,matriz[i]);
          loca[i].inicio_lin = inlin;
          loca[i].inicio_col = incol;;
          loca[i].termino_lin = finlin;
          loca[i].termino_col =fincol;
        }
      }
      else if (opcao == 2)//diagonal
      {
        int linp =lin > tan ? rand () %(lin - tan) : 0;
        int colp =col > tan ? rand () %(col - tan) : 0;
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //conferindo se a palavra cabe nessa posicao
        for (int j = 0; j < tan;j++)
        {
          if (tabu[linp +j][colp + j] != matriz[i][j] && tabu[linp + j][colp + j] != 0){
            controle = 0;
          }
        } 
        if (controle)
        {
          for (int j = 0;j < tan; j++){
            tabu [linp + j][colp +j] = matriz[i][j];
            finlin = linp + j;
            fincol = colp + j;
          }
          //salvando a localização da palavra
          strcpy(loca[i].palavra,matriz[i]);
          loca[i].inicio_lin = inlin;
          loca[i].inicio_col = incol;;
          loca[i].termino_lin = finlin;
          loca[i].termino_col = fincol;
        }
      }


      if (cont >= 35){
        break;
      }
    }
    if (cont >= 35){
      break;
    }
  }
  return tabu;
}
char **dificil(char **tabu,char **matriz,int numero,int lin,int col,Localizacao *loca){
  srand(time(NULL));
  for (int i = 0; i < numero;i++){
    int tan = strlen(matriz[i]); 

    int controle = 0;
    int cont =0;
    while (!controle)
    {
      controle = 1;
      cont++;
      
      int opcao = rand () %3;
      int direcao = rand () %2;
      if (opcao == 0)//horizontal
      {
        int linp = rand () %(lin);
        int colp = col > tan ? rand () %(col - tan) : 0;
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //verifica a posicao selecionada
        //palavras ja selecionadas
        for (int j = 0; j < tan;j++){
          if (direcao == 0){
            if (tabu[linp][colp + j] != matriz[i][j] && tabu[linp][colp + j] != 0){
              controle = 0;
            }
          }
          else {
            if (tabu[linp][colp + j] != matriz[i][tan - 1 -j] && tabu[linp][colp + j] != 0){
              controle = 0;
            }
          }
        }
        if (controle){
          if (direcao == 0)//horizontal
          {
            for (int j = 0;j < tan; j++){
              tabu [linp][colp + j] = matriz[i][j];
              finlin = linp;
              fincol = colp + j;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = inlin;
            loca[i].inicio_col = incol;;
            loca[i].termino_lin = finlin;
            loca[i].termino_col = fincol;
          }
          else //horizontal contraria
          {
            for (int j = 0;j < tan; j++){
            tabu [linp][colp + j] = matriz[i][tan - 1 - j];
              finlin = linp;
              fincol = colp + j;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = finlin;
            loca[i].inicio_col = fincol;;
            loca[i].termino_lin = inlin;
            loca[i].termino_col = incol;
          }
          // printf("inseriu na horizontal\n");
        }
      }
      else if(opcao == 1)//vertical
      {
        int linp = lin > tan ? rand () %(lin - tan) : 0;
        int colp = rand () %(col);
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //verifica a posicao selecionada
        //palavras ja selecionadas
        for (int j = 0; j < tan;j++){
          if (direcao == 0){
            if (tabu[linp +j][colp] != matriz[i][j] && tabu[linp + j][colp] != 0){
              controle = 0;
            }
          }
          else {
            if (tabu[linp +j][colp] != matriz[i][tan - 1 - j] && tabu[linp + j][colp] != 0){
              controle = 0;
            }
          }
        }
        if (controle){
          if (direcao == 0)//vertical
          {
            for (int j = 0;j < tan; j++){
              tabu [linp + j][colp] = matriz[i][j];
              finlin = linp + j;
              fincol = colp;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = inlin;
            loca[i].inicio_col = incol;;
            loca[i].termino_lin = finlin;
            loca[i].termino_col = fincol;
          }
          else //vertical contraria
          {
            for (int j = 0;j < tan; j++){
              tabu [linp + j][colp] = matriz[i][tan - 1 -j];
              finlin = linp + j;
              fincol = colp;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = finlin;
            loca[i].inicio_col = fincol;;
            loca[i].termino_lin = inlin;
            loca[i].termino_col = incol;
          }
        }
      }
      else if (opcao == 2)//diagonal
      {
        int linp =lin > tan ? rand () %(lin - tan) : 0;
        int colp =col > tan ? rand () %(col - tan) : 0;
        int inlin = linp;
        int incol = colp;
        int finlin,fincol;
        //conferindo se a palavra cabe nessa posicao
        for (int j = 0; j < tan;j++)
        {
          if (direcao == 0)
          {
            if (tabu[linp +j][colp + j] != matriz[i][j] && tabu[linp + j][colp + j] != 0){
              controle = 0;
            }
          }
          else {
            if (tabu[linp +j][colp + j] != matriz[i][tan - 1 - j] && tabu[linp + j][colp + j] != 0){
              controle = 0;
            }
          }
        } 
        if (controle)
        {
          if (direcao == 0){
            for (int j = 0;j < tan; j++){
              tabu [linp + j][colp +j] = matriz[i][j];
              finlin = linp + j;
              fincol = colp + j;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = inlin;
            loca[i].inicio_col = incol;;
            loca[i].termino_lin = finlin;
            loca[i].termino_col = fincol;
          }
          else {
            for (int j = 0;j < tan; j++){
              tabu [linp + j][colp +j] = matriz[i][tan - 1 - j];
              finlin = linp + j;
              fincol = colp + j;
            }
            //salvando a localização da palavra
            strcpy(loca[i].palavra,matriz[i]);
            loca[i].inicio_lin = finlin;
            loca[i].inicio_col = fincol;;
            loca[i].termino_lin = inlin;
            loca[i].termino_col = incol;
          }
        }
      }
      

      if (cont >= 35){
        break;
      }
    }
    if (cont >= 35){
      break;
    }
  }
  return tabu;
}
void impremematriz (char **tabu,int lin,int col){
  int i,j;
  printf(" ");
  for (i = 0; i < col;i++)//montando o tabuleiro
    {
      printf("   %c",i + 65); //parte superior
    }
    printf("\n  "TAB_TL);
    for (i = 0; i < col - 1;i++){
      printf(TAB_HOR TAB_HOR TAB_HOR  TAB_TJ);
    }
    printf(TAB_HOR TAB_HOR TAB_HOR TAB_TR"\n");
    for (i = 0;i < lin;i++)
    {
      printf("%-2c"TAB_VER,i + 65);
      for(j = 0; j < col;j++)
      {
        if (isupper(tabu[i][j])){
          printf(BOLD(BLUE(" %c "))TAB_VER,tabu[i][j]);
        }
        else{
          printf(" %c "TAB_VER,tabu[i][j]);
        }
      }
      printf("%2c",i + 65);
      
      if (i == lin - 1)
      {
        printf("\n  "TAB_BL);
        for (j = 0; j < col - 1;j++){
          printf(TAB_HOR TAB_HOR TAB_HOR TAB_BJ);
        }
        printf(TAB_HOR TAB_HOR TAB_HOR TAB_BR "\n");
      }
      else {
        printf("\n  "TAB_ML);
        for (j = 0; j < col - 1;j++){
          printf(TAB_HOR TAB_HOR TAB_HOR TAB_MJ);
        }
        printf(TAB_HOR TAB_HOR TAB_HOR TAB_MR "\n");
      }
    }
    printf(" ");
    for (i = 0; i < col;i++)//fim da montagem do tabuleiro
    {
      printf("   %c",i +65); //parte inferior
    }
    printf("\n");
}
char **marcamatriz (char **tabu,int lin,int col,Comando comandos){
  int i;
  if (comandos.p_lin == comandos.pt_lin)//horizontal
  {
    if (comandos.p_col < comandos.pt_col){
      for (i = 0; i < comandos.pt_col - comandos.p_col + 1;i++){
        tabu[comandos.p_lin][comandos.p_col + i] = toupper(tabu[comandos.p_lin][comandos.p_col + i]);
      }
    }
    else{
      for (i = 0; i < comandos.p_col - comandos.pt_col + 1;i++){
        tabu[comandos.p_lin][comandos.p_col - i] = toupper(tabu[comandos.p_lin][comandos.p_col - i]);
      }
    }
  }
  else if (comandos.p_col == comandos.pt_col)//vertical
  {
    if (comandos.p_lin < comandos.pt_lin){
      for (i = 0; i < comandos.pt_lin - comandos.p_lin + 1;i++){
        tabu[comandos.p_lin + i][comandos.p_col] = toupper(tabu[comandos.p_lin + i][comandos.p_col]);
      }
    }
    else{
      for (i = 0; i < comandos.p_lin - comandos.pt_lin + 1;i++){
        tabu[comandos.p_lin - i][comandos.p_col] = toupper(tabu[comandos.p_lin - i][comandos.p_col]);
      }
    }
  }
  else //diagonal
  {
    if (comandos.p_lin < comandos.pt_lin && comandos.p_col < comandos.pt_col){
      for (i = 0; i < comandos.pt_lin - comandos.p_lin + 1;i++){
        tabu[comandos.p_lin + i][comandos.p_col + i] = toupper(tabu[comandos.p_lin + i][comandos.p_col + i]);
      }
    }
    else{
      for (i = 0; i < comandos.p_lin - comandos.pt_lin + 1;i++){
        tabu[comandos.p_lin - i][comandos.p_col - i] = toupper(tabu[comandos.p_lin - i][comandos.p_col - i]);
      }
    }
  }
  return tabu;
}
int marcasalva (char **tabu,int lin,int col,ComandoSal coman,Localizacao *l2,int quantidade){
  int i;
  char verifica [30];
  for (int ve = 0; ve < 30; ve++){
    verifica[ve] = '\0';
  }
  if (coman.p_lin == coman.pt_lin)//horizontal
  {
    if (coman.p_col < coman.pt_col){
      for (int j = 0; j < coman.pt_col - coman.p_col + 1;j++){
        verifica[j] = tabu[coman.p_lin][coman.p_col + j];
      }
      
      for (int m = 0; m < coman.pt_col - coman.p_col + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.pt_col - coman.p_col + 1;i++){
            tabu[coman.p_lin][coman.p_col + i] = toupper(tabu[coman.p_lin][coman.p_col + i]);
            l2[k].achou = 1;
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;
        }
      }
    }
    else //horizontal contraria
    {
      for (int j = 0; j < coman.p_col - coman.pt_col + 1;j++){
        verifica[j] = tabu[coman.p_lin][coman.p_col - j];
      }
      for (int m = 0; m < coman.p_col - coman.pt_col + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.p_col - coman.pt_col + 1;i++){
            tabu[coman.p_lin][coman.p_col - i] = toupper(tabu[coman.p_lin][coman.p_col - i]);
            l2[k].achou = 1;
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;
        } 
      } 
    }
  }

  else if (coman.p_col == coman.pt_col)//vertical
  {
    if (coman.p_lin < coman.pt_lin){
      for (i = 0; i < coman.pt_lin - coman.p_lin + 1;i++){
        verifica[i] = tabu[coman.p_lin + i][coman.p_col];
      }
      for (int m = 0; m < coman.pt_lin - coman.p_lin + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.pt_lin - coman.p_lin + 1;i++){
            tabu[coman.p_lin + i][coman.p_col] = toupper(tabu[coman.p_lin + i][coman.p_col]);
            l2[k].achou = 1;
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;
        }
      }
    }
    
    else //vertical contraria
    {
      for (i = 0; i < coman.p_lin - coman.pt_lin + 1;i++){
        verifica[i] = tabu[coman.p_lin - i][coman.p_col];
      }
      for (int m = 0; m < coman.p_lin - coman.pt_lin + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.p_lin - coman.pt_lin + 1;i++){
            tabu[coman.p_lin - i][coman.p_col] = toupper(tabu[coman.p_lin - i][coman.p_col]);
            l2[k].achou = 1;
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;            
        }
      }
    }
  }

  else //diagonal
  {
    if (coman.p_lin < coman.pt_lin && coman.p_col < coman.pt_col){
      for (i = 0; i < coman.pt_lin - coman.p_lin + 1;i++){
        verifica [i] = tabu[coman.p_lin + i][coman.p_col + i];
      }
      for (int m = 0; m < coman.pt_lin - coman.p_lin + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.pt_lin - coman.p_lin + 1;i++){
            tabu[coman.p_lin + i][coman.p_col + i] = toupper(tabu[coman.p_lin + i][coman.p_col + i]);
            l2[k].achou = 1;         
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;
        }
      }
    }
    
    else //diagonal contraria
    {
      for (i = 0; i < coman.p_lin - coman.pt_lin + 1;i++){
        verifica[i] = tabu[coman.p_lin - i][coman.p_col - i];
      }
      for (int m = 0; m < coman.p_lin - coman.pt_lin + 1;m++){
        if(verifica[m] < 97){
          verifica[m] = tolower(verifica[m]);
        }
      }
      for (int k = 0; k < quantidade;k++){
        if (strcmp(verifica,l2[k].palavra) == 0 && l2[k].achou == 0){
          for (i = 0; i < coman.p_lin - coman.pt_lin + 1;i++){
            tabu[coman.p_lin - i][coman.p_col - i] = toupper(tabu[coman.p_lin - i][coman.p_col - i]);
            l2[k].achou = 1;
          }
          l2[k].inicio_lin = coman.p_lin;
          l2[k].inicio_col = coman.p_col;
          l2[k].termino_lin = coman.pt_lin;
          l2[k].termino_col = coman.pt_col;
          return 1;
        }
      }
    }
  }
  return 0;
}
void confere_hor (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( k + i < col); i++){
    A[i] = tabu[j][k + i];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){
    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = j;
    l2[indice].termino_col = (k + i - 1);

  }
  free(A);

}
void confere_vet (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( j + i < lin); i++){
    A[i] = tabu[j + i][k];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){
    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = (j + i - 1);
    l2[indice].termino_col = k;

    
  }
  free(A);

}
void confere_dia (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( j + i < lin) && (k + i < col); i++){
    A[i] = tabu[j + i][k + i];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){
    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = (j + i - 1);
    l2[indice].termino_col = (k + i -1);

  }
  free(A);

}
void confere_horiv (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( k + i >= 0); i++){
    A[i] = tabu[j][k - i];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){

    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = j;
    l2[indice].termino_col = (k - i + 1);

 
  }
  free(A);

}
void confere_vetiv (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( j - i >= 0); i++){
    A[i] = tabu[j - i][k];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){
    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = (j - i + 1);
    l2[indice].termino_col = k;
  }

  free(A);
}
void confere_diaiv (char **tabu,int lin ,int col, Localizacao *l2,int tam,int j,int k,int indice,char *palavra){
  char *A = malloc ((tam + 1) * sizeof(char));
  int i;
  for (i = 0; i < tam && ( j - i >= 0) && (k - i >= 0); i++){
    A[i] = tabu[j - i][k - i];
    if(A[i] < 97)//caso a palavra ja tenha sido marcada e uma letra esta em maiusculo
    {
      A[i] = tolower(A[i]);
    }
  }
  A[i] = '\0';
  
  if (strcmp(palavra,A) == 0){
    l2[indice].inicio_lin = j;
    l2[indice].inicio_col = k;
    l2[indice].termino_lin = (j - i + 1);
    l2[indice].termino_col = (k - i + 1);
  }
  free(A);

}
int resolve (char **tabu,int lin, int col, Localizacao *l2,int quantidade){
  int tam;
  Comando pos;
  for(int i = 0; i < quantidade;i++){
    if (l2[i].inicio_lin == -1) //conferindo se a palavra ja foi encontrada
    {
      tam = strlen(l2[i].palavra);
      for (int j = 0;j < lin;j++){
        for (int k = 0;k < col;k++){
          confere_hor(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra);       //confere se ela esta na horizontal
          confere_vet(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra);      //confere se ela esta na vertical
          confere_dia(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra);     //confere se ela esta na diagonal
          confere_horiv(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra);  //confere se ela esta na horizontal contraria
          confere_vetiv(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra); //confere se ela esta na vertical contraria
          confere_diaiv(tabu,lin,col,l2,tam,j,k,i,l2[i].palavra);//confere se ela esta na diagonal contraria
        }
      }
      pos.p_lin = l2[i].inicio_lin;
      pos.p_col = l2[i].inicio_col;
      pos.pt_lin = l2[i].termino_lin;
      pos.pt_col = l2[i].termino_col;
    }
    
   marcamatriz(tabu,lin,col,pos);
  }
  
  impremematriz(tabu,lin,col);
  return 0;
}


int main (){

  do{
    system("clear");
    int in = menu();
    //iniando o game
    switch (in)
    {
    case 1:
      printf("digite o nome do arquivo:");
      char nomeArquivo[26];
      scanf("%s",nomeArquivo);
      if (strcmp(nomeArquivo,"sair") == 0)//caso o usuario saia do programa
      {
        printf(BOLD(WHITE("tenha um otimo dia!!"))"\n");
        exit(0);
      }
      FILE *arquivo = fopen(nomeArquivo,"r");
      if (arquivo == NULL)//conferindo se o arquivo foi aberto
      {
        printf("nao foi possivel abrir o arquivo");
        exit(1);
      }
      int lin,col;
      fscanf(arquivo,"%d %d",&lin,&col);
      int numero_palavras;
      fscanf(arquivo,"%d",&numero_palavras);
      getchar();

      //criando a matriz para amarzenar as palavras e o tabuleiro
      char **matriz = criaMatrizR(numero_palavras,lin < col ? col : lin);
      char **tabu = criaMatrizR(lin,col);
      int i =0;
      int j =0;

      //salvando as palavras na matriz
      while (!feof(arquivo)){
        for(i = 0;i < numero_palavras;i++){
          fscanf(arquivo,"%s",matriz[i]);
        }
      }
      fclose(arquivo);
      printf("qual o nivel de dificuldade desejado:");
      
      char dificuldade[5];
      

      Localizacao *loca = malloc(numero_palavras * sizeof(Localizacao));
      for (i = 0; i < numero_palavras; i++){
        loca[i].achou = 0;
      }

      
      for (int para = 0;para < 1;){
        printf(BOLD(GREEN("facil(1)")", "YELLOW("medio(2)")", "RED("dificil(3):")));
        scanf ("%s", dificuldade);
        if (strcmp(dificuldade,"sair")== 0){
          free(loca);
          desaloca_matriz(matriz,numero_palavras);
          desaloca_matriz(tabu,lin);
          return 0;
        }
        else if (strcmp(dificuldade,"1") == 0)//apenas palavras na vertical e horizontal
        {
          tabu = facil(tabu,matriz,numero_palavras,lin,col,loca);
          para++;
        }
        else if (strcmp(dificuldade,"2") == 0)//palavras na horizontal, vertical e diagonal
        {
          tabu = medio(tabu,matriz,numero_palavras,lin,col,loca);
          para++;
        }
        else if (strcmp(dificuldade,"3") == 0)//horizontal,vertical e diagonal(ao contrario tambem)
        {
          tabu = dificil(tabu,matriz,numero_palavras,lin,col,loca);
          para++;
        }
        else {
          printf("comando invalido\n");
        }
      }

      for (i = 0; i < lin; i++)//completando a matriz
      {
        for (j = 0; j < col; j++){
          if (tabu [i][j] == 0){
            tabu[i][j] = 97 + rand()%26;
          }
        }
      }

      //imprimindo o tabuleiro
      impremematriz(tabu,lin,col);
      printf("\n");
      
      int contador = 0;
      int acabou = 0;
      printf ("Exemplos de execucao: marcar AA BB / salvar / resolver\n");
      Comando *comandos = malloc(numero_palavras * sizeof(Comando));
      char *salva = calloc(30, sizeof(char));

      while (contador != numero_palavras && !acabou) //comandos sendo executados
      {
        getchar();
        for (i = 0; i < numero_palavras; i++){
          printf ("Digite o comando: ");
          

          fgets(comandos[i].cmd,30,stdin);

          //tirando o \n
          comandos[i].cmd[strlen(comandos[i].cmd)-1] = '\0';

          //comando MARCAR
          if (strstr(comandos[i].cmd,"marcar") != NULL){
            
            //caso o usuario digite em letra minuscula
            if (comandos[i].cmd[7] >= 91 && comandos[i].cmd[8] >= 91 && comandos[i].cmd[10] >= 91 && comandos[i].cmd[11] >= 91){
              printf("\nindice desconhecido \nOBS:o indice deve estar em maiusculo\n");
            }

            // //salvando as cordenadas para comparação
            else {
              comandos[i].p_lin = comandos[i].cmd[7] - 65;
              comandos[i].p_col = comandos[i].cmd[8] - 65;
              comandos[i].pt_lin = comandos[i].cmd[10] - 65;
              comandos[i].pt_col = comandos[i].cmd[11] - 65;
            }

            int encontrou = 0;
            for (int k = 0; k < numero_palavras; k++){
              if (comandos[i].p_lin == loca[k].inicio_lin && comandos[i].p_col == loca[k].inicio_col && comandos[i].pt_lin == loca[k].termino_lin && comandos[i].pt_col == loca[k].termino_col)
              {
                marcamatriz(tabu,lin,col,comandos[i]);
                system("clear");
                impremematriz(tabu,lin,col);
                contador++;
                encontrou++;
                loca[k].achou = 1;
              }
            }
            
            if (encontrou == 0) {
              printf(BOLD(WHITE("INDICE INVALIDO\n"))"\n");
              i--;
            }  
          }
          else if (contador == numero_palavras){
            acabou = 1;
          }
          

          //comando RESOLVER
          else if (strcmp(comandos[i].cmd,"resolver") == 0){
            Comando res2;
            for (int res = 0;res < numero_palavras;res++){
              res2.p_lin = loca[res].inicio_lin;
              res2.p_col= loca[res].inicio_col;
              res2.pt_lin = loca[res].termino_lin;
              res2.pt_col = loca[res].termino_col;
              marcamatriz(tabu,lin,col,res2);
            }
            system("clear");
            impremematriz(tabu,lin,col);
            printf(BOLD(WHITE("\nATE A PROXIMA!! TALVEZ VOCE CONSIGA :) \n"))"\n");
            acabou = 1;
            break;
          }
          
          //comando SAIR
          else if (strcmp(comandos[i].cmd,"sair") == 0){
            printf(BOLD(WHITE("tenha um otimo dia!!"))"\n");
            acabou = 1;
            exit(0);
          }

          //comando SALVAR
          else if (strstr(comandos[i].cmd,"salvar") != NULL){
            
            for (int sal = 0; sal < strlen(comandos[i].cmd); sal++){
              salva[sal] = comandos[i].cmd[7 + sal];
            }

            //abrindo o arquivo
            FILE *arquivo2 = fopen(salva,"w+");
            if (arquivo == NULL){
              printf("nao foi possivel abrir o arquivo");
              exit(1);
            }
            printf("Arquivo salvo com sucesso em %s\n",salva);

            //salvando no arquivo
            fprintf(arquivo2,"%d %d\n",lin,col);
            for (int linha = 0; linha < lin; linha++){
              for (int coluna = 0; coluna < col; coluna++){
                fprintf(arquivo2,"%c ",toupper(tabu[linha][coluna]));
              }
              fprintf(arquivo2,"\n");
            }
            fprintf(arquivo2,"%d\n",numero_palavras);
            for (int g = 0; g < numero_palavras;g++){
              fprintf(arquivo2,"%s ",loca[g].palavra);
              if (loca[g].achou == 1){
                fprintf(arquivo2,"%c%c %c%c\n",loca[g].inicio_lin + 97,loca[g].inicio_col + 97,loca[g].termino_lin + 97,loca[g].termino_col + 97);
              }
              else if (loca[g].achou == 0){
                fprintf(arquivo2,"-- --\n");
              }
            }
            i--;
            //fechando tudo
            fclose(arquivo2);
          }
          
          else {
            printf("COMANDO INVALIDO!!!\n");
            i--;
          }
        }
      }

      

      if (contador == numero_palavras)//caso o usuario tenha achado todas as palavras
      {
        printf(BOLD(WHITE("\nPARABENS VOCE E UM CACADOR\n         END GAME!!!!"))"\n");
        
        //libetando e deslacondo as memorias
        free(loca);
        desaloca_matriz(matriz,numero_palavras);
        desaloca_matriz(tabu,lin);
        free(comandos);
        free(salva);
      }
      //se o usuario quiser jogar novamente
      int novo;
        printf(BOLD(WHITE("voce quer jogar novamente ? (1-SIM/0-NAO)"))"\n");
        scanf("%d",&novo);
        if (novo == 0){
          exit(0);
        }
      
      break;
    
    case 2:
      printf("digite o nome do arquivo que contem o jogo salvo: ");
      char num[28];
      scanf("%s",num);

      if (strcmp(num,"sair")==0)//caso o usuario saia do programa
      {
        printf(BOLD(WHITE("tenha um otimo dia!!"))"\n");
        exit(0);
      }
      FILE *salvo = fopen(num,"r");
      
      if (salvo == NULL)//conferindo se o arquivo foi aberto
      {
        printf("nao foi possivel abrir o arquivo\n");
        exit(1);
      }
      int linha,coluna;
      int quantidadePalavras;
      fscanf(salvo,"%d %d",&linha,&coluna);

      char **tabuleiro = criaMatrizR(linha,coluna);
      char mar[56];
      //lendo o tabuleiro
      fgetc(salvo);
      for (int l = 0; l < linha;l++){
        fgets(mar,56,salvo);
        for (int c = 0, x = 0 ; c < coluna;x++){
          if (mar[x] != ' ' && mar[x] != '\n'){
            tabuleiro[l][c] = tolower(mar[x]);
            c++;
          }
        }
      }

      fscanf(salvo,"%d",&quantidadePalavras);
      Localizacao *l2 = calloc(quantidadePalavras,sizeof(Localizacao));
      char il,ic,fl,fc;

      //salvando as palavras e as cordenadas
      for (int t = 0; t < quantidadePalavras;t++)
      { 
        fscanf(salvo,"%s",l2[t].palavra);
        fgetc(salvo);
        fscanf(salvo,"%c%c",&il,&ic);
        fgetc(salvo);
        fscanf(salvo,"%c%c",&fl,&fc);
        if (il == '-'){
          l2[t].inicio_lin = -1;
        }
        else {
          l2[t].inicio_lin = il - 97;
        }

        if (ic == '-'){
          l2[t].inicio_col = -1;
        }
        else {
          l2[t].inicio_col = ic - 97;
        }

        if (fl == '-'){
          l2[t].termino_lin = -1;
        }
        else {
          l2[t].termino_lin = fl - 97;
        }

        if (fc == '-'){
        l2[t].termino_col = -1;
        }
        else {
          l2[t].termino_col = fc - 97;
        }

        if (l2[t].inicio_col >= 0 && l2[t].inicio_lin >= 0 && l2[t].termino_lin >= 0 && l2[t].termino_col >= 0)//se a palavra ja tiver sido achada
        {
          l2[t].achou = 1;
        }
      }
      for (int k =0; k < quantidadePalavras;k++)//caso a palavra ja tenha sido encontrada
      {
        if (l2[k].achou == 1){
          Comando marca;
          marca.p_lin = l2[k].inicio_lin;
          marca.p_col = l2[k].inicio_col;
          marca.pt_lin = l2[k].termino_lin;
          marca.pt_col = l2[k].termino_col;

          marcamatriz(tabuleiro,linha,coluna,marca);
        }
      }
      fclose(salvo);

      printf("\n");
      system("clear");
      impremematriz(tabuleiro,linha,coluna);

      
      Contador conts;
      char *salva2 = calloc(30, sizeof(char));
      ComandoSal *coman = malloc(quantidadePalavras * sizeof(ComandoSal));
      printf ("\nExemplos de execucao: marcar AA BB / salvar / resolver\n");
      int regula = 0;
      conts.cont = 0;
      conts.reg = 0;
      for (int k =0; k < quantidadePalavras;k++)//caso a palavra ja tenha sido encontrada
      {
        if (l2[k].achou == 1){
          conts.cont++;
          regula++;
        }
      }
      
      while (conts.cont != quantidadePalavras && !conts.reg)//comandos sendo executados
      { 
        getchar();
        for (int a = 0; a < quantidadePalavras - regula; a++){
          printf("\n");

          printf ("Digite o comando: ");
          fgets(coman[a].cmd,30,stdin);

          printf("\n");

          //tirando o \n
          coman[a].cmd[strlen(coman[a].cmd)-1] = '\0';

          //comando MARCAR
          if (strstr(coman[a].cmd,"marcar") != NULL){
            
            //caso o usuario digite em letra minuscula
            if (coman[a].cmd[7] >= 91 && coman[a].cmd[8] >= 91 && coman[a].cmd[10] >= 91 && coman[a].cmd[11] >= 91){
              printf("\nComando ou indice desconhecido \nOBS:o indice deve estar em maiusculo\n");
            }

          //salvando as cordenadas para comparação
            else {
              coman[a].p_lin = coman[a].cmd[7] - 65;
              coman[a].p_col = coman[a].cmd[8] - 65;
              coman[a].pt_lin = coman[a].cmd[10] - 65;
              coman[a].pt_col = coman[a].cmd[11] - 65;
            }

            if (marcasalva(tabuleiro,linha,coluna,coman[a],l2,quantidadePalavras) == 1){
              conts.cont++;
            }
            else {
              printf("indice invalido\n");
              a--;
            }
            system("clear");
            impremematriz(tabuleiro,linha,coluna);
          }

          //comando sair
          else if (strcmp(coman[a].cmd,"sair") == 0)
          {
            printf(BOLD(WHITE("tenha um otimo dia!!\n"))"\n");
            conts.reg = 1;
            exit(0);
          }

          //comando resolver
          else if (strcmp(coman[a].cmd,"resolver") == 0){
            system("clear");
            resolve(tabuleiro,linha,coluna,l2,quantidadePalavras);
            printf(BOLD(WHITE("\nATE A PROXIMA!! TALVEZ VOCE CONSIGA :) \n"))"\n");
            conts.reg = 1;
            break;
          }

          //comando salvar
          else if (strstr(coman[a].cmd,"salvar") != NULL){
            
            for (int sal = 0; sal < strlen(coman[a].cmd); sal++){
              salva2[sal] = coman[a].cmd[7 + sal];
            }

            //abrindo o arquivo
            FILE *new = fopen(salva2,"w+");
            if (new == NULL){
              printf("nao foi possivel abrir o arquivo");
              exit(1);
            }
            printf("Arquivo salvo com sucesso em %s\n",salva2);

            //salvando no arquivo
            fprintf(new,"%d %d\n",linha,coluna);
            for (int lin = 0; lin < linha; lin++){
              for (int col = 0; col < coluna; col++){
                fprintf(new,"%c ",toupper(tabuleiro[lin][col]));
              }
              fprintf(new,"\n");
            }
            fprintf(new,"%d\n",quantidadePalavras);
            for (int g = 0; g < quantidadePalavras;g++){
              fprintf(new,"%s ",l2[g].palavra);
              if (l2[g].achou == 1){
                fprintf(new,"%c%c %c%c\n",l2[g].inicio_lin + 97,l2[g].inicio_col + 97,l2[g].termino_lin + 97,l2[g].termino_col + 97);
              }
              else if (l2[g].achou == 0){
                fprintf(new,"-- --\n");
              }
            }
            a--;

            //fechando arquivo
            fclose(new);
          }

          else {
            printf("COMANDO INVALIDO!!!\n");
            a--;
          }

        }
      }
      if (conts.cont == quantidadePalavras)//caso o usuario tenha achado todas as palavras
      {
        printf(BOLD(WHITE("\nPARABENS VOCE E UM CACADOR\n        END GAME!!!!!"))"\n");
        
        //fechando e liberando tudo
        free(salva2);
        free(coman);
        free(l2);
        desaloca_matriz(tabuleiro,linha);
      }

      int novos;
        printf(BOLD(WHITE("voce quer jogar novamente ? (1-SIM/0-NAO)"))"\n");
        scanf("%d",&novos);
        if (novos == 0){
          exit(0);
        }
      break;

    case 3:
      regras();
      break;
  }
  }while (1);
  
  

  return 0;
}