#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Stack.h"
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"
#include "guiao5.h"
#include "handler.h"

/**função para colucar um numero na stack(inteiro ou double)*/
bool PutANumberToStack(STACK *s, char palavra[]){
  bool ponto = false;
  Valor valor;
  char *end;
   if ((47 < palavra[0] && palavra[0] < 58) || (47 < palavra[1] && palavra[1] < 58)){
    /**Neste loop é verificado se existe o caracter ponto na string e se houver o bool ponto passa a true e para-se o loop, porque ele já serviu
     * o seu propósito. Caso não encontre o bool ponto continua false;
     */
    for (int i = 0; palavra[i] && !ponto; i++){
      if (palavra[i] == '.') {
      ponto = true;
      }
    }
    /**Se ponto for true então a string é convertida para double, e se for falso é convertido para inteiro. No final da conversão é dado push para a stack */
    if (ponto) {
       sscanf(palavra, "%lf", &valor.u.d);
       valor.kind = DOUBLE;
    }else{
      valor.u.i = strtol(palavra, &end, 10);
      valor.kind = INT;
    }
      push(s, valor);
        return 0;
  }
return 1;
}

void PutStringToStack(STACK *s,char palavra[]){
     Valor valor;
      valor.kind = STRING;
      valor.u.s = (char*)malloc(strlen(palavra) * sizeof(char *));
      strcpy(valor.u.s, palavra);
      push (s, valor);
}

/**função que altera o conteudo da stack de variaveis*/
bool variableHandler(STACK *s, char palavra[]){
  Valor valor;
    if (palavra[0] >= 65 && palavra[0] <= 90){
      if (strlen(palavra) == 1 || palavra[1] == '\0'){
      valor.kind = s->variables[palavra[0] - 65].kind;
      if (valor.kind == ARRAY){
        valor.u.a = new_stack();
        init(valor.u.a);
        for (int i = 0; i <= s -> variables[palavra[0] - 65].u.a -> sp; i++){
          push(valor.u.a, s -> variables[palavra[0] - 65].u.a -> stack[i]);
        }
        push(s, valor);
        return true;
      }else if (valor.kind == STRING){
        valor.u.s = newString();
          for (int i = 0; s -> variables[palavra[0] - 65].u.s[i] != '\0'; i++){
          valor.u.s[i] =   s -> variables[palavra[0] - 65].u.s[i];
        }
        push(s, valor);
        return 1;
      }else if (valor.kind == BLOCK){
        valor.u.s = newString();
          for (int i = 0; s -> variables[palavra[0] - 65].u.s[i] != '\0'; i++){
          valor.u.s[i] =   s -> variables[palavra[0] - 65].u.s[i];
        }
        push(s, valor);
        return 1;
      }
      push(s, s->variables[palavra[0] - 65]);
      }
      else PutStringToStack(s, palavra);
      return true;
    }
    return false;
}
/**função que cria blocos de instruções*/
char *BlockHandler(STACK *s,char linha[]){
  int i  =0;
  int aberturas = 0;
  Valor valor;
  valor.kind = BLOCK;
  valor.u.s = (char *)malloc(strlen(linha) * sizeof(char));
  bool ender = true;
  int inside = 0;
  while(linha[0] == ' ') linha++;
  while(ender){
    if (linha[0] == '{'){
      inside++;
    }else if (linha[0] == '}'){
      inside--;
      if (inside == 0){
        ender = false;
      }
    }
    valor.u.s[i] = linha[0];
    linha++;
    i++;
  }
  linha++;
  valor.u.s[i] = '\0';
  push(s, valor);
  return linha;
}
/**função que cria strings*/
char *StringHandler(STACK *s,char linha[]){
  int i  =0;
  Valor valor;
  valor.kind = STRING;
    valor.u.s = (char *)malloc(strlen(linha) * sizeof(char));
  while(linha[0] == ' ') linha++;
  if (linha[0] == '"'){
    linha++;
  while(linha[0] != '"'){
    valor.u.s[i] = linha[0];
    linha++;
    i++;
  }
  linha++;
  valor.u.s[i] = '\0';
  push(s, valor);
  }
  return linha;
}

char *ArrayHandler(STACK *s, STACK *original, char linha[]){
    int i = strlen(linha);
  char *word = (char *)malloc(i * sizeof(char));
 Valor valor;
 long unsigned int aux;
    while (sscanf(linha, "%s%[^\n]", word, linha) == 2){
      aux = s -> sp;
      if (aux >= (original -> tamanho/sizeof(Valor*))/ (original -> sp + 2)) original = realocador(original);
      if (word[0] == ']') return linha;
      if (word[0] == '[') {
        valor.u.a = new_stack();
        init(valor.u.a);
        valor.kind = ARRAY;
        strcpy(linha, ArrayHandler(valor.u.a, original, linha));
        aux = s -> sp;
        if (aux >= (original -> tamanho/sizeof(Valor*))/ (original -> sp + 2)) original = realocador(original);
        push(s, valor);
        word[0] = ' ';
      } else if (word[0] == '"'){
        strcat(word, linha);
        strcpy(linha, StringHandler(s , word));
      }else {
        if ((word[0] >= 'A' && word[0] <= 'Z')){
        if (word[0] == 'S' && word[1] == '/') stringbywhitespace(s);
       else if (word[0] == 'N' && word[1] == '/') string_for_newlines(s);
       else
        push(s, original -> variables[word[0] - 65]);
       }else if (word[0] == ':'){
         valor = pop(s);
            original->variables[word[1] - 65] = valor;
            push(s, valor);
       }
        else handler(s, word);
      }
         memset(word,0,i);
}
      linha++;
      linha++;
      free(word);
      return linha;
}



char guiao1Handler(STACK *s, char palavra[]){
     switch(palavra[0]){
      case '+':
        adicionar(s);
          return 1;
      case '-':
        if (PutANumberToStack(s, palavra)){
            subtrair(s);
        }
          return 1;
      case '*':
        multiplicar(s);
         return 1;
      case '/':
        dividir(s);
          return 1;
         
      case '%':
        modulo(s);
          return 1;
      case '#':
        exponenciacao(s);
          return 1;
      case '(':
        decrementar(s);
          return 1;
      case ')':
        incrementar(s);
          return 1;
      case '&':
        andBitwise(s);
          return 1;
      case '|':
        orBitwise(s);
          return 1;
      case '^':
        xorBitwise(s);
          return 1;
      case '~':
        notBitwise(s);
          return 1;
      default:
          return 0;
     }
}

void starter(STACK *s, char linha[]){
  int i = strlen(linha);
  char *word = (char *)malloc(i * sizeof(char));
 Valor valor;
    while (sscanf(linha, "%s%[^\n]", word, linha) == 2){
      if (word[0] == '{'){
        strcat(word, linha);
        strcpy(linha, BlockHandler(s , word));
      }
      else if (word[0] == '[') {
        valor.u.a = new_stack();
        init(valor.u.a);
        valor.kind = ARRAY;
       strcpy(linha, ArrayHandler(valor.u.a, s, linha));
       push(s, valor);
      } else if (word[0] == '"'){
        strcat(word, linha);
        strcpy(linha, StringHandler(s , word));
      }else {
        handler(s, word);
      }
         memset(word,0,i);
}
  if (word[0] != '\0' && word[0] != ' '){
       if (word[0] == '{'){
        strcat(word, linha);
        strcpy(linha, BlockHandler(s , word));
      }
  else if (word[0] == '[') {
        valor.u.a = new_stack();
        init(valor.u.a);
        valor.kind = ARRAY;
       strcpy(word, ArrayHandler(valor.u.a, s, word));
       push(s, valor);
      } else if (word[0] == '"'){
        strcpy(linha, StringHandler(s , word));
        strcpy(linha, "");
        strcpy(word, "");
      }else {
        handler(s, word);
      }
  }
}


char guiao2Handler(STACK *s, char palavra[]){
  Valor valor;
  valor.kind = STRING;
  valor.u.s = newString();
    switch(palavra[0]) {
      case '_':
        duplicate(s);
         free(valor.u.s);
          return 1;
      case ';':
        pop(s);
         free(valor.u.s);
          return 1;
      case '\\':
        swap(s);
         free(valor.u.s);
          return 1;
      case '@':
        tripleSwap(s);
         free(valor.u.s);
          return 1;
      case '$':
        removeTerm(s);
         free(valor.u.s);
          return 1;
      case 'i':
          if (palavra[1] == '\0'){
        convertToInteger(s);
         free(valor.u.s);
          return 1;
          }
           free(valor.u.s);
          return 0;
      case 'f':
          if (palavra[1] == '\0'){
        convertToDouble(s);
         free(valor.u.s);
          return 1;
          }
             free(valor.u.s);
            return 0;
          
      case 'c':
          if (palavra[1] == '\0'){
        convertToChar(s); 
                free(valor.u.s);
          return 1;
  
          }
             free(valor.u.s);
            return 0;
          
      case 's':
      if (palavra[1] == '\0'){
        convertToString(s);
         free(valor.u.s);
          return 1;
      }
         free(valor.u.s);
        return 0;
      
      case 'l':
          if (palavra[1] == '\0'){
          readLine(valor.u.s);
          valor.u.s[strlen(valor.u.s)-1] = '\0';
          push(s, valor);
         return 1;
             free(valor.u.s);
            return 0;
          
      default:
       free(valor.u.s);
        return 0;
    }
   
}
free(valor.u.s);
return 0;
}

char guiao3Handler(STACK *s, char palavra[]){
    Valor valor;
    Valor aux;
     switch(palavra[0]){
      case 'e':
        switch (palavra[1]){
          case '>':
            maior_logico(s);
              return 1;
         case '<':
            menor_logico(s);
              return 1;
         case '&':
            e_logico(s);
              return 1;
         case '|':
           ou_logico(s);
              return 1;}
        PutStringToStack(s, palavra);
        return 1;
      case '!':
       nao(s);
        return 1;
       case '?':
         if_then_else(s);
         return 1;
      case '<':
        menor(s);
          return 1;
      case '>':
       maior(s); 
        return 1;
      case '=':
        iguais(s);
          return 1;
      case ':':
      valor = pop(s);
      s -> variables[palavra[1] -65] = valor;
      if (valor.kind == ARRAY){
        aux.kind = ARRAY;
        aux.u.a = new_stack();
        init(aux.u.a);
          for (int i = 0; i <= valor.u.a -> sp; i++){
          push(aux.u.a, valor.u.a -> stack[i]);
        }
        push(s, aux);
        return 1;
      }else if (valor.kind == STRING){
        aux.kind = STRING;
        aux.u.s = newString();
          for (int i = 0; valor.u.s[i] != '\0'; i++){
          aux.u.s[i] =  valor.u.s[i];
        }
        push(s, aux);
        return 1;
      }else if (valor.kind == BLOCK){
        aux.kind = BLOCK;
        aux.u.s = newString();
          for (int i = 0; valor.u.s[i] != '\0'; i++){
          aux.u.s[i] =  valor.u.s[i];
        }
        push(s, aux);
        return 1;
      }
      push(s, valor);
         return 1;
      default:
       return 0;
     }
}

char guiao4Handler(STACK * s, char palavra[]){
  switch (palavra[0])
  {
  case ',':
  lengthORrange(s);
    return 1;
  case 't':
  readALL(s);
  return 1;
  default:
    return 0;
  }
}

char guiao5Handler(STACK * s, char palavra[]){
  switch (palavra[0])
  {
  case 'w':
  whileTrue(s);
    return 1;
  case 'p':
  PrintStacktopo(s);
    return 1;
  default:
    return 0;
     }
}


/**Esta é a função onde são tratados as diferentes "palavras" que recebemos, ela analisa o tipo de palavra que é (se é um dígito ou símbolo) e
 * se for dígito é covertido em número e dá-se push para a stack, se for caracter entra no case para determinar que função deve ser utilizada e caso
 * não comece com nenhum caracter especial é dado push para a stack como string. No switch usamos return como alternativa ao bre ak, porque se não o 
 * fizermos o mooshack não aceita o código e neste caso é exatamente igual usar um ou outro, porque o switch é a última instrução do código
*/
void handler(STACK *s, char palavra[]){
  if (PutANumberToStack(s, palavra)){
   if (palavra[0] == 'S' && palavra[1] == '/') stringbywhitespace(s);
   else if (palavra[0] == 'N' && palavra[1] == '/') string_for_newlines(s);
   else if (variableHandler(s, palavra));
   else if (((guiao1Handler(s, palavra) == 1) || (guiao2Handler(s, palavra)) == 1) || (guiao3Handler(s, palavra)) || guiao4Handler(s, palavra) || guiao5Handler(s, palavra)){
     int i = 0;
     i++;
     i--;
   } else PutStringToStack(s, palavra);
}
}
