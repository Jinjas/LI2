#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "guiao2.h"
#include "guiao4.h"
#include "guiao5.h"
#include "handler.h"

void aoElemento(STACK *s) {
    Valor bloco = pop(s);
    bloco.u.s[strlen(bloco.u.s)-1] = '\0';
    starter(s, &bloco.u.s[1]);

}

void aoConteudo(STACK *s) {
    Valor bloco = pop(s);
    Valor object = pop(s);
    int spStack = s->sp,j = 0;
    bloco.u.s[strlen(bloco.u.s)-1] = '\0';
    char *aux = (char*)malloc(sizeof(char)*strlen(bloco.u.s));

    if (object.kind == STRING) {
        Valor caracter;
        Valor strings;
        Valor valor;
        caracter.kind = CHAR;
        strings.kind = STRING;
        strings.u.s = newString();
        for (int i = 0; object.u.s[i] != '\0'; i++) {
            strcpy(aux, bloco.u.s);
            caracter.u.c = object.u.s[i];
            push(s,caracter);
            starter(s, &aux[1]);
            while(spStack < s->sp){
             valor = pop(s);
             if (valor.kind == CHAR)
             strings.u.s[j++] =  valor.u.c;
             else {
                 push(s,valor);
                 convertToString(s);
                 valor = pop(s);
                 for (int i = 0; valor.u.s[i] != '\0'; i++)
                 strings.u.s[j++] =  valor.u.s[i];
             }
            }
        }
        strings.u.s[j] = '\0';
        push (s,strings);
    }
     else {//kind == ARRAY
        Valor elem;
        Valor newArray;
        newArray.kind = ARRAY;
        newArray.u.a = new_stack();
        init(newArray.u.a);
        newArray.u.a->variables = s->variables;
        for (int i = 0;i <= object.u.a->sp;i++){
            strcpy(aux, bloco.u.s);
            elem = object.u.a->stack[i];
            push(newArray.u.a,elem);
            starter(newArray.u.a, &aux[1]);
        }
    push (s,newArray);
    }
        free(aux);
        free(object.u.a);
}


void blockfilter(STACK *s) {
    Valor bloco = pop(s);
    Valor object = pop(s);
    int j,i;
    char *augha = (char*)malloc(sizeof(char)*strlen(bloco.u.s));
    bloco.u.s[strlen(bloco.u.s)-1] = '\0';
    if (object.kind == STRING) {
        Valor caracter;
        for (j = 0,i = 0; object.u.s[i] != '\0'; i++) {
            caracter.kind = CHAR;
            caracter.u.c = object.u.s[i];
            push(s,caracter);
            strcpy(augha, bloco.u.s);
            starter(s, &augha[1]); 
            caracter = pop(s);
            if (caracter.u.i) object.u.s[j++] = object.u.s[i];
        }
        object.u.s[j] = '\0';
        push (s,object);
    }
    else{
        Valor elem;
        Valor aux;
        aux.kind = ARRAY;
        aux.u.a = new_stack();
        init(aux.u.a);
        for (int i = 0;i <= object.u.a->sp;i++){
            elem = object.u.a->stack[i];
            push(s,elem);
            strcpy(augha, bloco.u.s);
            starter(s, &augha[1]);
            elem = pop(s);
            if (elem.u.i) push(aux.u.a,object.u.a->stack[i]);
        }

        push (s, aux);
        free(augha);
        free(object.u.a->stack);
       free(object.u.a);
    }
}

void whileTrue (STACK *s){
    Valor bloco = pop(s); 
    Valor x = pop(s);
    char *aux = (char*)malloc(sizeof(char)*strlen(bloco.u.s));
    bloco.u.s[strlen(bloco.u.s)-1] = '\0';
    push (s, x);
    if ((x.kind) == INT || x.kind == DOUBLE){
        while (x.u.i != 0 || x.u.d != 0){
            strcpy(aux, bloco.u.s);
            starter(s, &aux[1]); 
            x = pop (s);
      }
     }
    else if (x.kind == STRING){
        while (strlen(x.u.s) != 0){
            strcpy(aux, bloco.u.s);
            starter(s, &aux[1]);
            x = pop(s);
      }
      free(x.u.s);
    }
    else if (x.kind == ARRAY){
        while ((x.u.a -> sp) != -1){
             strcpy(aux, bloco.u.s);
             starter(s, &aux[1]);
             x = pop(s);
      }
            free(x.u.a-> stack);
                free(x.u.a);
    }
    free(aux);
}

void fold (STACK *s){
    Valor bloco = pop(s);
    Valor array = pop(s);
    Valor valor;
    valor.kind = ARRAY;
    valor.u.a = new_stack();
    init(valor.u.a);
    valor.u.a->variables = s->variables;

     push(valor.u.a, popFromTheBottom(array.u.a));
    char aux[strlen(bloco.u.s)];
     bloco.u.s[strlen(bloco.u.s)-1] = '\0';
    while(array.u.a->sp >= 0){
        push(valor.u.a, popFromTheBottom(array.u.a));
          strcpy(aux, bloco.u.s);
        starter(valor.u.a, &aux[1]);
    }

    push(s, valor);
    free(array.u.a);
}

void sort_using_blocks (STACK *s){
    Valor bloco = pop(s);
    Valor valor = pop(s);

    if(bloco.kind ==BLOCK && valor.kind == ARRAY){
        Valor newArray;
        Valor aux1;
        newArray.kind = ARRAY;
        newArray.u.a = new_stack();
        init(newArray.u.a);
        newArray.u.a->variables = s->variables;
        int i, j,min;

        for(i = 0; i <=valor.u.a->sp;i++){ // array copy 
            aux1 = valor.u.a->stack[i];
            push(newArray.u.a,aux1);
        }
        push(s,newArray);
        push(s,bloco);
        aoConteudo(s);
        newArray = pop(s); // resultado é o que sobreu do sort

        
        for(i=0; i <= valor.u.a->sp; i++){
            min = i;
            for(j = i+1; j<=valor.u.a->sp;j++){ // encontra o minimo dos que faltam?
                if(newArray.u.a->stack[j].u.i < newArray.u.a->stack[min].u.i) min = j;
            }
            if( i!=min){
                aux1 = newArray.u.a->stack[i];
                newArray.u.a->stack[i] = newArray.u.a->stack[min]; // ordena o auxiliar
                newArray.u.a->stack[min]= aux1; 
                aux1 = valor.u.a->stack[i];
                valor.u.a->stack[i] = valor.u.a->stack[min]; //ordena o principal
                valor.u.a->stack[min] = aux1; 
            }
        }
        free(newArray.u.a);
        push(s,valor);
    }

}