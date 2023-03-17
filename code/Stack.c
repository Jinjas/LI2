#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Stack.h"
#include "stdbool.h"

STACK * new_stack(){
    return (STACK *)malloc(sizeof(STACK));  
}

void init(STACK *s){
   s -> tamanho = 200000 * sizeof(Valor);
   s -> stack = (Valor *)malloc(s -> tamanho);
   s -> variables = (Valor *)malloc(26 * sizeof(Valor));
   s -> sp = -1;
}

void initVariables(STACK *s){
     for (int i = 0; i < 6; i++){
       s -> variables[i].u.i = 10 + i;
       s -> variables[i].kind = INT;
   }
   s -> variables[13].u.c = '\n';
   s -> variables[13].kind = CHAR;
   s -> variables[18].u.c = ' ';
   s -> variables[18].kind = CHAR;
      for (int i = 23; i < 26; i++){
       s -> variables[i].u.i = i - 23;
       s -> variables[i].kind = INT;
   }
}

char * newString (){
  return (char *)malloc(BUFSIZ * sizeof(char));
}


STACK * realocador(STACK * s){
        STACK *aux = (STACK*)realloc(s,sizeof(s));
        if (aux != NULL) {
            aux -> tamanho *= 2;
            aux -> stack = (Valor *)realloc(s -> stack,aux -> tamanho);
            aux -> variables = (Valor *)realloc(s -> variables, 26 * sizeof(Valor));
            return aux;
        }
        return s;
}


STACK * memoryHandler(STACK *s){
    int something = (s -> tamanho)/(sizeof(Valor));
    if (s -> sp >= something - 2) {
      return realocador(s);
    }
    return s;
}

void push(STACK *s, Valor elem){
    s -> sp++;
    s -> stack[s->sp] = elem;
    s = memoryHandler(s);
}

Valor pop(STACK *s){
    Valor x = s -> stack[s->sp];
    s -> sp--;
    return x;
}

Valor popFromTheBottom(STACK *s){
    Valor x = s -> stack[0];
    s -> sp--;
    s -> stack++;
    return x;
}


void PrintStack(STACK *s, int x) {
  for (int i = 0; i <= x; i++){
        int aux = s-> stack[i].kind;
        if (INT == aux)
            printf("%lld", s->stack[i].u.i);
        else if (DOUBLE == aux){
             printf("%g", s-> stack[i].u.d);
        }
        else if (CHAR == aux)
            printf("%c", s->stack[i].u.c);
        else if (ARRAY == aux){ 
         PrintStack(s->stack[i].u.a, s -> stack[i].u.a -> sp);
        }    else 
            printf("%s", s->stack[i].u.s);
  }
}

void PrintStacktopo(STACK *s) {
        int i = s -> sp;
        int aux = s-> stack[i].kind;
        if (INT == aux)
            printf("%lld\n", s->stack[i].u.i);
        else if (DOUBLE == aux){
             printf("%g\n", s-> stack[i].u.d);
        }
        else if (CHAR == aux)
            printf("%c\n", s->stack[i].u.c);
        else if (ARRAY == aux){ 
            printf("\n\n%d\n\n", s -> stack[i].u.a -> sp);
         PrintStack(s->stack[i].u.a, s -> stack[i].u.a -> sp);
        }    else 
            printf("%s\n", s->stack[i].u.s);
}
/**função para dar print da tag do topo da stack*/
void PrintTopTag(STACK *s){
    Valor valor = s->stack[s->sp];
    if (valor.kind == CHAR) printf("\nCHAR\n");
    else if (valor.kind == ARRAY) printf("\nARRAY\n");
    else if (valor.kind == STRING) printf("\nSTRING\n");
    else if (valor.kind == INT) printf("\nINT\n");
    else if (valor.kind == DOUBLE) printf("\nDOUBLE\n");
    else if (valor.kind == STRING) printf("\nSTRING\n");
    else printf("\nBLOCK\n");
}