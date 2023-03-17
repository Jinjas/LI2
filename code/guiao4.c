#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Stack.h"
#include "guiao4.h"
#include "guiao2.h"
#include "guiao5.h"
#include "handler.h"

/** Função qe nplica o conteudo de uma stack/string 
 * na string copia a inicial e concatena n vezes e no array faz de forma recursiva com uma copia do msm
*/

void strConcaten(STACK *s) {
    Valor times = pop (s); // n vezes
    Valor thing = pop (s); // string/array
    if (thing.kind == STRING) {
        char extra[10000];
        strcpy(extra,thing.u.s);
        for (int i = 1; i < times.u.i; i++){
            strcat (thing.u.s, extra);
        }
    }
    else if(thing.kind == ARRAY) {
            Valor valor;
            valor.kind = ARRAY;
            valor.u.a = new_stack();
            init(valor.u.a);
        for (int i = 0; i < times.u.i; i++){
          for (int j = 0; j <= thing.u.a -> sp; j++){
            push(valor.u.a, thing.u.a -> stack[j]);
          }
        }
        push(s, valor);
        return;
    }
    push(s,thing);
}
/**função auxiliar para o range*/
Valor range(Valor object){
    if (object.kind == INT) {
            int max = object.u.i;
            object.kind = ARRAY;
            object.u.a = new_stack();
            init(object.u.a);
            Valor i;
            i.kind = INT;
            for (i.u.i = 0; i.u.i < max; i.u.i++){
                push (object.u.a,i);
            }
            return object;
        }
        else if (object.kind == CHAR) {
            Valor cont;
            cont.kind = ARRAY;
            cont.u.a = new_stack();
            init(cont.u.a);
            Valor c;
            c.kind = CHAR;
            for (c.u.c = 'a'; c.u.c < 'z'+ 1 && c.u.c < object.u.c; c.u.c++)
                push (cont.u.a,c);
            return cont;
        }

}

/** põe na stack o sp do array ou o length da lista, se for caracter ou inteiro devolve uma lista com os caracteres/numeros até ao dado */
void lengthORrange(STACK *s) {
    Valor cont,object = pop (s);
    cont.kind = INT;

    if(object.kind == STRING){ // && object.u.s[0] == '"'
        int enters= 0;
        for (cont.u.i = 0; object.u.s[cont.u.i] != '\0';cont.u.i++){
           if(object.u.s[cont.u.i] == '\\' && object.u.s[cont.u.i+1] == 'n') enters ++;
        }
        cont.u.i -= enters;
    }
    if(object.kind == ARRAY) {    // && object.u.s[0] == '['
        cont.u.i = (object.u.a)->sp + 1;
        free(object.u.a->stack);
        free(object.u.a);
    }
    if (object.kind == INT || object.kind == CHAR) {
        cont = range(object);
    }
    if (object.kind == BLOCK) {
        push (s,object),
        blockfilter (s);
        return;
    }
    push (s,cont);
}

/** põe na stack o sp do array ou o length da lista, se for caracter ou inteiro devolve uma lista com os caracteres/numeros até ao dado */
void lengthORrange(STACK *s) {
    Valor cont,object = pop (s);
    cont.kind = INT;

    if(object.kind == STRING){ // && object.u.s[0] == '"'
        int enters= 0;
        for (cont.u.i = 0; object.u.s[cont.u.i] != '\0';cont.u.i++){
           if(object.u.s[cont.u.i] == '\\' && object.u.s[cont.u.i+1] == 'n') enters ++;
        }
        cont.u.i -= enters;
    }
    if(object.kind == ARRAY) {    // && object.u.s[0] == '['
        cont.u.i = (object.u.a)->sp + 1;
        free(object.u.a->stack);
        free(object.u.a);
    }
    if (object.kind == INT || object.kind == CHAR) {
        cont = range(object);
    }
    if (object.kind == BLOCK) {
        push (s,object),
        blockfilter (s);
        return;
    }
    push (s,cont);
}


/** Função que troca uma string/array pelo elemento no indice dado.
 * Em ambos os casos é instantaneo porque ambos podem ser tratados como arrays
*/

void forIndices (STACK *s) {
    Valor indice = pop(s),object = pop (s);
    if(object.kind == STRING){
        Valor x;
        x.kind = CHAR;
        x.u.c = object.u.s[indice.u.i];
        push (s,x);
        free(object.u.s);
    }
    else if (object.kind == ARRAY){
        Valor x;
        x.kind = (object.u.a)->stack->kind;
        x = ((object.u.a)->stack [indice.u.i]);
        push (s,x);
    }
    else push (s,object);
}

/* 
---------------------------- função substituta---------------------

void forindicesinstead (STACK *s){
   Valor object = pop(s);
   Valor indice = pop(s);
   if(object.kind == STRING){
        Valor x;
        x.kind = CHAR;
        x.u.c = object.u.s [indice.u.i];
        push (s,x); 
   }
   else if (object.kind == ARRAY){
        Valor x;
        x.kind = (object.u.a)->stack->kind;
        x = ((object.u.a)->stack [indice.u.i]);
        push (s,x);    
   }
   else push(s, object);
}
*/

/** função que lê um ficheiro/todas as linhas da consola*/
void readALL (STACK *s){
        char *linha = (char*)malloc(BUFSIZ * sizeof(char *));
     Valor valor;
     valor.kind = STRING;
       valor.u.s = newString();
     valor.u.s[0] = '\0';
        while (fgets(linha, BUFSIZ, stdin) != 0){
        linha[strlen(linha)] = '\0';
        strcat(valor.u.s, linha);
}
push(s, valor);
free(linha);
}

/** auxiliar da tail para o poder fazer de forma recursiva*/
STACK *auxiliarTail (STACK *s, int quantos){
    if (quantos) {
        Valor member = pop (s);
        push (auxiliarTail(s,quantos-1),member);
    }
    else {
        while (s->sp+1)
        pop (s);
    }
    return s;
}

/**funçao '>' retira elementos da cabeça até a string/array ficar com n elementos*/
void tail (STACK *s) {
    Valor n = pop(s),object = pop (s);
    if(object.kind == STRING){
       int last = strlen(object.u.s);
       int j = 0;
       for (int i = last-n.u.i; object.u.s[i] != '\0'; i++){
           n.u.s[j] = object.u.s[i];
           j++;
       }
       n.u.s[j] = '\0';
       n.kind = STRING;
       push(s, n);
       return;
    }
    else if(object.kind == ARRAY){
        object.u.a = auxiliarTail(object.u.a, n.u.i);
        push (s,object);
        return;
    }
}


/**funçao '<' retira elementos do fim até a string/array ficar com n elementos*/
void head (STACK *s) {
    Valor n = pop(s),object = pop (s);
    if(object.kind == STRING){
        object.u.s[n.u.i] = '\0';
        push (s,object);
    }
    else if(object.kind == ARRAY){
        while (object.u.a->sp >= n.u.i){
            pop (object.u.a);
        }
        push(s,object);
        return;
    }
}

/**Função para tirar tds os elementos do array e por na stack principal*/
void moveALL(STACK *s, Valor valor){
  Valor auxiliar;
  int x = valor.u.a -> sp;
  for (int i = 0; i <= x; i++){
      auxiliar = valor.u.a->stack[i];
      push(s, auxiliar);
  }
}

/**Procurar substring na string e devolver o índice ou -1 se não encontrar*/
void findSubstring(STACK *s, Valor objetivo, Valor original){
bool verdadeiro = true;
int i;
if (objetivo.kind == CHAR){
for (i = 0; original.u.s[i] != '\0'; i++){
    verdadeiro = true;
    if (original.u.s[i] == objetivo.u.c){
     objetivo.u.i = i;
     objetivo.kind = INT;
     push(s, objetivo);
     free(original.u.s);
     return;
    }
}

}else{
for (i = 0; original.u.s[i] != '\0'; i++){
    verdadeiro = true;
    if (original.u.s[i] == objetivo.u.s[0]){
      for (int j = 0; verdadeiro; j++){
          if (objetivo.u.s[j] == '\0'){
              free(objetivo.u.s);
              objetivo.u.i = i;
              objetivo.kind = INT;
              push(s, objetivo);
                   free(original.u.s);
              return;
          } else if (objetivo.u.s[j] != original.u.s[j+i]){
               verdadeiro = false;
          } else if (original.u.s[j+i] == '\0') verdadeiro = false;
      }
    }
}
}   
     free(original.u.s);
        objetivo.u.i = -1;
              objetivo.kind = INT;
              push(s, objetivo);
}

/**Esta função devolve há stack o array/string sem o primeiro elemento/caracter e depois coloca na stack o que foi removido na dando push após do array/string*/
void remov_first_elem (STACK *s){
    Valor x = pop (s);
    Valor valor;
    valor.kind = CHAR;
    if (x.kind == STRING){
        valor.u.c = x.u.s[0];
        int tamanho = strlen (x.u.s) -1;
            for (int i = 0; i < tamanho; i++){
                x.u.s[i] = x.u.s[i + 1];
      }
      x.u.s[tamanho] = '\0';
        push (s, x);
        push (s, valor);
    } 
    else if (x.kind == ARRAY){
       valor = popFromTheBottom (x.u.a);
           push(s, x);
       push (s, valor);
    }
}


/**Esta função devolve há stack o array/string sem o último elemento/caracter e depois coloca na stack o que foi removido dando push do após do array/string*/
void remov_last_elem (STACK *s){
    Valor x = pop (s);
    Valor valor;
    valor.kind = CHAR;
    if (x.kind == STRING){
        int tamanho = strlen (x.u.s);
        valor.u.c = x.u.s[tamanho - 1];
        x.u.s[tamanho -1] = '\0';
        push (s, x);
        push (s, valor);
    }
    else if (x.kind == ARRAY){
        valor = pop (x.u.a);
        push(s, x);
        push (s, valor);
    }
}


/**Estas funções estão definidas em guiao4.c, isto é só para poder incluir na main */
/** função que junta a um array/string a um elemento ou a outro array/string */
void concat(STACK *s){
    Valor indice = pop(s);
    Valor object = pop(s);
    Valor aux;
    if(object.kind == ARRAY && indice.kind != ARRAY){
        push(object.u.a,indice);
    }
    else if(object.kind != ARRAY && indice.kind == ARRAY){
        aux.u.a = new_stack();
        init(aux.u.a);
        push(aux.u.a, object);
        aux.kind = ARRAY;
       for (int i = 0; i <= indice.u.a-> sp; i++){
           push (aux.u.a, indice.u.a->stack[i]);
       }
       push(s, aux);
       return;
    }
    else if(indice.kind == ARRAY && object.kind == ARRAY){
        int i = indice.u.a->sp;
        for(int f = 0;(i!=-1);f++){
            aux = indice.u.a->stack[f];
            push(object.u.a, aux);
            i--;
        }
     }else{
         push(s, object);
         convertToString(s);
         push(s, indice);
         convertToString(s);
         indice = pop(s);
         object = pop(s);
         Valor valor;
         valor.kind = STRING;
         valor.u.s=newString();
       strcat(valor.u.s, object.u.s);
       strcat(valor.u.s,indice.u.s);
       free(indice.u.s);
       push(s, valor);
       free(object.u.s);
       return;
    }
            push(s, object);
}

/**função que separa uma string por espaços em branco e coloca as palavras num array*/
void stringbywhitespace(STACK *s){
    Valor indice = pop(s);
    Valor array;
    array.kind = ARRAY;
    array.u.a = new_stack();
    init(array.u.a);
    char *aux = newString();
    int j = 0;
   while(indice.u.s[j] != '\0'){
       int i = 0;
       while(indice.u.s[j] != '\0' && indice.u.s[j] != '\n' && indice.u.s[j] != ' '  ){
         aux[i] = indice.u.s[j];
         j++;
         i++;
       }
       j++;
       if (strlen(aux) > 0){
       aux[i] = '\0';
       PutStringToStack(array.u.a, aux);
       }
   }
    free(aux);
    free(indice.u.s);
    push(s,array);

}

/** função que separa uma string cada vez que ocorre um '\n' e põe as novas string num array*/
void string_for_newlines(STACK *s){
    Valor indice = pop(s);
    Valor array;
    array.kind = ARRAY;
    array.u.a = new_stack();
    init(array.u.a);
    char *aux = newString();
    int j = 0;
   while(indice.u.s[j] != '\0'){
       int i = 0;
       while(indice.u.s[j] != '\0' && indice.u.s[j] != '\n'){
         aux[i] = indice.u.s[j];
         j++;
         i++;
       }
       j++;
       if (strlen(aux) > 0){
       aux[i] = '\0';
       PutStringToStack(array.u.a, aux);
       }
   }
    free(aux);
    free(indice.u.s);
    push(s,array);

}


/** função que separa uma string cada vez que ocorre uma substring dada e põe as novas string num array*/
void string_by_substring (STACK *s){
    Valor objetivo = pop(s);
    Valor indice = pop(s);
    Valor array;
    array.kind = ARRAY;
    array.u.a = new_stack();
    init(array.u.a);
    char *aux = newString();
    int j = 0;
   while(indice.u.s[j] != '\0'){
       int i = 0;
       bool verdadeiro  = true;
       while(indice.u.s[j] != '\0' && verdadeiro){
         if (indice.u.s[j] == objetivo.u.s[0]){
             int k;
             for (k = 0; objetivo.u.s[k] != '\0' && verdadeiro && indice.u.s[j+k] ; k++)
             {
                 if (objetivo.u.s[k] != indice.u.s[j+k]){
                   verdadeiro = false;
                 }
             }
            verdadeiro  = !verdadeiro; 
             if (!verdadeiro)
            j += k;

         }
         if (verdadeiro){
         aux[i] = indice.u.s[j];
         j++;
         i++;
         }
       }
       if (strlen(aux) > 0){
       aux[i] = '\0';
       PutStringToStack(array.u.a, aux);
       }
   }
    free(aux);
    free(objetivo.u.s);
    free(indice.u.s);
    push(s,array);
 }

