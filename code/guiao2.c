#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Stack.h"
#include "guiao2.h"
#include "guiao5.h"
/**A função duplicate copia o elemento que está no topo da stack para uma variável x
 *  e dá-lhe push,apenas para os casos de arrays e string é que temos de inicializar novas variáveis, desta forma evitamos dar push
 * dos mesmos elementos (do mesmo endereço).
 */
void duplicate(STACK *s) {
   Valor x = pop (s);
   if(x.kind == ARRAY){
        Valor elem;
        Valor aux;
        aux.kind = ARRAY;
        aux.u.a = new_stack();
        init(aux.u.a);
        aux.u.a->variables = s->variables;
         for (int i = 0;i <= x.u.a->sp;i++){
            elem = x.u.a->stack[i];
            push(aux.u.a,elem);
         }
         push (s, x);
         push (s, aux);
         return;

   }else if (x.kind == STRING){
        Valor string;
        string.kind = STRING;
        string.u.s = newString();
        strcpy(string.u.s,x.u.s);

   push (s, x);
   push (s, string);
      return;
   }else{
   push (s, x);
   push (s, x);
}
}

/**A função swap troca os dois elementos que estão no topo da stack */
void swap(STACK *s) {
   Valor x = pop (s);
   Valor y = pop (s);
   push (s, x);
   push (s, y);
}
/**A função tripleSwap troca a ordem dos 3 elementos que estão no topo da stack */
void tripleSwap(STACK *s) {
   Valor x = pop (s);
   Valor y = pop (s);
   Valor z = pop (s);
   push (s, y);
   push (s, x);
   push (s, z);
}
/**A função removeTerm remove o termo da stack que está na posição correspondente ao valor
 * inteiro do valor do top da stack
 */
void removeTerm(STACK *s) {
    Valor verifica = pop (s);
    if(verifica.kind == BLOCK){
      push(s,verifica);
      sort_using_blocks(s);
      return;
    }
    push(s,verifica);
    convertToInteger(s);
    Valor x = pop (s);
    Valor y = s -> stack[s->sp - x.u.i];
    push(s, y);
}

/** Esta função serve para converter o elemento que está no topo da stack para uma int. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToInteger(STACK *s){
   Valor x = pop (s);
   char *end;
   if(x.kind == STRING){
      x.u.i = strtol(x.u.s, &end, 10);
      x.kind = INT;
      push(s, x); 
   }else if(x.kind == CHAR){
      x.u.i = x.u.c;
      x.kind = INT;
      push(s, x);
   }
   else if(x.kind == DOUBLE){
       x.u.i = (x.u.d);
       x.kind = INT;
       push(s,x);
   }else   if(x.kind == INT){
        push(s, x);
   }
   else printf("\n Erro de conversão");
   }


/** Esta função serve para converter o elemento que está no topo da stack para uma string. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToString(STACK *s){
   Valor x = pop (s);
   Valor valor;
          valor.u.s = newString();
         valor.kind = STRING;
      if(x.kind == INT){
      sprintf(valor.u.s, "%lld", x.u.i);
      push (s,valor);
      }
      else if(x.kind ==CHAR){
        sprintf(valor.u.s, "%c", x.u.c);
      push (s,valor);
      }
      else if(x.kind ==DOUBLE){
        sprintf(valor.u.s, "%f", x.u.d);
      push (s,valor);
      }else if(x.kind == STRING){
           push(s, x);
      }
      else printf("\n Erro de conversão");
   }

/** Esta função serve para converter o elemento que está no topo da stack para um double. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToDouble(STACK *s){
   Valor x = pop (s);
    if(x.kind == INT){
      x.u.d = x.u.i;
    }
     else if(x.kind == STRING){
     char *ptr;
     x.u.d = strtod(x.u.s, &ptr);
     }
      else if(x.kind == CHAR){
      x.u.d = x.u.c;
      } 
      x.kind = DOUBLE;
      push(s, x);
}
     
   

/** Esta função serve para converter o elemento que está no topo da stack para um char. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToChar(STACK *s){
   Valor x = pop (s);
   if(x.kind == INT){
      x.u.c = x.u.i;
      x.kind =CHAR;
      push(s, x);
   } else if(x.kind == STRING){
      x.u.c = x.u.s[0];
      x.kind = CHAR;
      push (s, x);
   } else if(x.kind == DOUBLE){
      x.u.c = (x.u.d);
      x.kind =CHAR;
      push (s,x);
   }else if(x.kind == CHAR){
        push(s, x);
   }
   else printf("\n Erro de conversão");
}

/**Esta função lê e retorna uma linha */
void readLine (char *linha){
   if (fgets(linha, BUFSIZ, stdin) == 0){
      printf("Erro ao ler linha");
   }
}

