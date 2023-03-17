
#include <math.h>
#include "Stack.h"
#include "guiao1.h"
#include "guiao2.h"
#include "guiao4.h"
#include "guiao5.h"

/**esta função faz a soma entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 */
    void adicionar(STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == ARRAY || y.kind == ARRAY || x.kind == STRING || y.kind == STRING){
       push(s, y);
       push(s, x);
      concat(s);
      return;
    }
    else if (x.kind == CHAR && y.kind == CHAR){
        x.u.c += y.u.c;
    }else if(x.kind == DOUBLE || y.kind == DOUBLE){
        push(s, y);
       push(s, x);
       convertToDouble (s);
       x = pop(s);
         convertToDouble (s);
         y = pop(s);
        x.u.d += y.u.d;
        x.kind = DOUBLE;
    }else{
       push(s, y);
       push(s, x);
       convertToInteger (s);
       x = pop(s);
       convertToInteger (s);
       y = pop(s);
       x.u.i += y.u.i;
       x.kind = INT;
    }
    
        push(s,x);
}


/**Esta função faz a subtração entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void subtrair(STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == CHAR && y.kind == CHAR){
        x.u.c -= y.u.c;
    }else if(x.kind == DOUBLE || y.kind == DOUBLE){
        push(s, y);
       push(s, x);
       convertToDouble (s);
       y = pop(s);
         convertToDouble (s);
         x = pop(s);
        x.u.d -= y.u.d;
        x.kind = DOUBLE;
    }else{
       push(s, y);
       push(s, x);
       convertToInteger (s);
       y = pop(s);
       convertToInteger (s);
       x = pop(s);
       x.u.i -= y.u.i;
       x.kind = INT;
    }

        push(s,x);
}


/**Esta função faz a multiplicação entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void multiplicar(STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == BLOCK){
        push(s,y),push(s,x); fold(s); return;
    }
    if (x.kind == INT && (y.kind == STRING || y.kind == ARRAY)){
        push(s,y),push(s,x); strConcaten(s); return;
    } else if (x.kind == CHAR && y.kind == CHAR){
        x.u.c *= y.u.c;
    }else if(x.kind == DOUBLE || y.kind == DOUBLE){
        push(s, y);
       push(s, x);
       convertToDouble (s);
       y = pop(s);
         convertToDouble (s);
         x = pop(s);
        x.u.d *= y.u.d;
        x.kind = DOUBLE;
    }else{
       push(s, y);
       push(s, x);
       convertToInteger (s);
       y = pop(s);
       convertToInteger (s);
       x = pop(s);
       x.kind = INT;
       x.u.i *= y.u.i;
    }
        push(s,x);
}

/**Esta função faz a divisão entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void dividir(STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == STRING && y.kind == STRING){
        push(s, y);
        push(s, x);
        string_by_substring(s);
        return;
    }else if (x.kind == ARRAY || y.kind == ARRAY || x.kind == STRING || y.kind == STRING){
       push(s, x);
       push(s, y);
       concat(s);
       return;
    }else if(x.kind == DOUBLE || y.kind == DOUBLE){
        push(s, y);
       push(s, x);
       convertToDouble (s);
       y = pop(s);
         convertToDouble (s);
         x = pop(s);
        x.u.d /= y.u.d;
        x.kind = DOUBLE;
    }else{
       push(s, y);
       push(s, x);
       convertToInteger (s);
       y = pop(s);
       convertToInteger (s);
       x = pop(s);
       x.kind = INT;
       x.u.i /= y.u.i;
    }

        push(s,x);
}
/**Esta função faz a interceção dos bits entre dois inteiros, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * & 00011001
 *   ________
 *   00001000  = 8
*/
void andBitwise(STACK *s) {
    convertToInteger(s);
    Valor x = pop(s);
    convertToInteger(s);
    Valor y = pop(s);
    x.u.i &= y.u.i;
    push(s, x);
}
/**Esta função faz a dijunção dos bits entre dois inteiros, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * | 00011001
 *   ________
 *   00011101  = 29
*/
void orBitwise(STACK *s) {
    convertToInteger(s);
    Valor x = pop(s);
    convertToInteger(s);
    Valor y = pop(s);
    x.u.i |= y.u.i;
    push(s, x);
}
/**Esta função compara dois inteiros através dos bits, caso sejam iguais poe 0, caso contrário 1, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * ^ 00011001
 *   ________
 *   00010101  = 21
 */
void xorBitwise(STACK *s) {
    convertToInteger(s);
    Valor x = pop(s);
    convertToInteger(s);
    Valor y = pop(s);
    x.u.i ^= y.u.i;
    push(s, x);
}
/**Esta função transforma um numero no seu complemento, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 * ~ 00100011 
 *   ________
 *   11011100  = 220
*/
void notBitwise(STACK *s) {
   Valor x = pop(s);
   if (x.kind == ARRAY){
       moveALL(s,x);
       return;
   }else if (x.kind == BLOCK){
       push (s,x);
       aoElemento (s);
   }else {
    push (s,x);
    convertToInteger(s);
    x = pop(s);
    x.u.i = ~x.u.i;
    push(s, x);
    }
}
/**Esta função decrementa uma unidade ao último elemento da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void decrementar(STACK *s){
    Valor x = pop(s);
    if (x.kind == ARRAY || x.kind == STRING){
        push (s, x);
        remov_first_elem (s);
        return;
    }    
    else if(x.kind == DOUBLE){
    x.u.d = x.u.d-1;
    push (s, x);
    }else { 
    x.u.i =  x.u.i-1;
    push (s, x);
    }
}


/**Esta função incrementa uma unidade ao último elemento da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void incrementar(STACK *s){
    Valor x = pop(s);
    if (x.kind == ARRAY || x.kind == STRING){
        push (s, x);
        remov_last_elem (s);
        return;
    }
    if(x.kind == DOUBLE){
        x.u.d = x.u.d+1;
        push (s, x);
    }else  { 
        x.u.i =  x.u.i+1;
        push (s, x);
    }
}

/**Esta função devolve o resto da divisão inteira entre os dois últimos elementos da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void modulo(STACK *s){
    Valor y = pop (s);
    if (y.kind == BLOCK){
        push (s,y);
        
        aoConteudo (s);
    }
    else{
    push (s,y);
    convertToInteger(s);
    y = pop(s);
    convertToInteger(s);
    Valor x = pop(s);
    x.u.i =  x.u.i % y.u.i;
    push (s, x);
   }
}
/**Esta função faz a exponencial de x em função de y, sendo x o penúltimo valor da stack e y o último, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void exponenciacao(STACK *s) {
   Valor y = pop(s);
    Valor x = pop(s);
    if(x.kind == INT && y.kind == INT){
    x.kind = INT;
    x.u.i = pow(x.u.i,y.u.i);
    push (s, x);
    }else if(x.kind == INT && y.kind == DOUBLE){
    x.u.d = x.u.i;
    x.kind=DOUBLE;
    x.u.d = pow(x.u.d,y.u.d);
    push (s, x);
    }else if(x.kind == DOUBLE && y.kind == DOUBLE){
    x.u.d = pow(x.u.d,y.u.d);
    push (s, x);
    } else  if ((y.kind == STRING) || (x.kind == STRING)){ 
        findSubstring(s, y, x);
        return;

}
}

