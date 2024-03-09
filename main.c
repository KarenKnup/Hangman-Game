#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char minuscula(char c) {
if (c>='A' && c<='Z'){//Checks if "c" is capitalized
     c=c-'A'+'a';//If so, turn it into LOWER SIZE
    } 

return c;
}

char maiuscula(char c) {
 if (c>='a' && c<='z'){
    c=c-'a'+'A';
    }
return c;
}

int VerificaMai(char c, char c2){
  c=minuscula(c);
  c2=minuscula(c2);

  if(c2!=c){//k = K
    return -1;
  } 

  return 0;
}

int Espacos(char s[]){
  int i, cont=0;
  for(i=0; s[i]; i++){
    if(s[i]==' ' || s[i]=='-'){
      cont++;
    }  
  }

  return cont;
}

int busca(char s[], char c){
  int i;
  for(i=0; s[i]; i++){
    if(s[i] == c || VerificaMai(s[i], c)==0){
      return 0;
    }
  }
  return -1;
}

void imprime (char s[]){
  int i;
  for(i=0; s[i]; i++){
      printf("%c ",s[i]);
  }
}

void zeraVetor(char v2[]){
  for ( int i = 0 ; i<(strlen(v2)) ; i++){
    if(v2[i]==' '){
      v2[i]=' ';
    } else if(v2[i]=='-'){
      v2[i]='-';
    } else {
      v2[i]='?';
    }
  }
}

void Boneco(int n){
  if(n==6){
   printf("\n\n   _________\n   |       |\n   |\n   |\n   |\n   |\n   _____________________"); 
  }

  for(int i=0; i<=n; i++){
    if(n==5){
      printf("\n\n   _________\n   |       |\n   |       O\n   |\n   |\n   |\n   _____________________"); 
      break;
    } else if(n==4){
     printf("\n\n   _________\n   |       |\n   |       O\n   |       |\n   |\n   |\n   _____________________"); 
      break;
    } else if (n==3){
      printf("\n\n   _________\n   |       |\n   |       O\n   |      /|\n   |\n   |\n   _____________________"); 
      break;
    } else if (n==2){
     printf("\n\n   _________\n   |       |\n   |       O\n   |      /|\\\n   |\n   |\n   _____________________"); 
      break;
      } else if (n==1){
      printf("\n\n   _________\n   |       |\n   |       O\n   |      /|\\\n   |      / \n   |\n   _____________________"); 
      break;
    } else if(n==0) {
       printf("\n\n   _________\n   |       |\n   |       O\n   |      /|\\\n   |      / \\\n   |\n   _____________________"); 
      break;
    }
  }
}

int buscaLetra(char p[], char c){
  char c2=minuscula(c);
  char c3=maiuscula(c);

  for(int i=0; p[i]; i++){
    if(p[i]==c2 || p[i]==c3){
      return 0;
    }
  }
  return -1;
}

void Forca(char *p, int l, char *d, int *fim) {
    int i, cont = l - Espacos(p), erro = 6, flag = 6; // a cada acerto cont diminui e a pessoa pode errar 5 vezes
    char s2[50], c;

    strcpy(s2, p);

    printf("\n\t----- WORD: -------\n\t");
    zeraVetor(s2);
    imprime(s2);
    Boneco(6);

    printf("\n\nHint: %s", d);

    printf("\n\nTry a letter: ");
    scanf(" %c", &c);

    while (cont >= 0 && erro > 0) {
        if (busca(p, c) == -1) {
            erro--;
            flag--;
            printf("\033[2J\033[H"); // Limpa a tela
            printf("\n\tWrong! You can fail more %d times.\n", erro);
            Boneco(erro);
            
        } else {
            printf("\033[2J\033[H"); // Limpa a tela
            Boneco(flag);
        }

        for (i = 0; p[i]; i++) {
            if (p[i] == c || VerificaMai(p[i], c) == 0) {
                s2[i] = p[i];
                cont--;
            }
        }
        printf("\n\nHint: %s", d);
        printf("\n__________________________________________\n");
        printf("\n\t----- WORD: -------\n\t");
        imprime(s2);

        if (cont==0) {
          printf("\n\n\tWIN, CONGRATULATIONS!!!\n\nWait 5 seconds . . .\n\n\n ", *p);
            sleep(5);
            free(d);
            free(p);
            return; // Added to exit function when word is guessed correctly
        } else {
            printf("\n\nTry a letter: ");
            scanf(" %c", &c);

            while (buscaLetra(s2, c) == 0) {
                printf("\nYou already tried this letter! Try a letter: ");
                scanf(" %c", &c);
            }

            if (erro == 0) {
                printf("\033[2J\033[H"); // Limpa a tela
                Boneco(0);
                printf("\n\n\tLOST!\n\n\tANSWER:\t%s\n\nWait 5 seconds . . .\n\n\n ", p);
                sleep(5);
                free(p);
                free(d);
                return; // Adicionado para sair da função quando o jogador perde
            }
        }
    }
}

void regras(){
  printf("\n\t\t========== RULES ==========\n");
  printf("\t1- With each correct answer, the letter will appear in place of the '?'.\n");
  printf("\t2- You have 5 chances to make a mistake.\n");
  printf("\t3- Words with accents are not accepted.");
  printf("\n__________________________________________\n\n");
}

void palavra_dica(char **p, char **d) {
    printf("\n\tEnter the game word: ");
    scanf(" %[^\n]", *p);
    *p = realloc(*p, strlen(*p) + 1);
  
    printf("\tEnter a hint to guess the word: ");
    scanf(" %[^\n]", *d);
    *d = realloc(*d, strlen(*d) + 1); // Includes \n
    printf("\033[2J\033[H"); // Clean the screen
}


int main(void) {
  int fim=0;
  
  while(fim==0){
    char *palavra=malloc(1), *dica=malloc(1);
    regras();
    palavra_dica(&palavra,&dica);

    Forca(palavra,strlen(palavra), dica, &fim);
    printf("\033[2J\033[H"); // Limpa a tela
  }

  return 0;
}
