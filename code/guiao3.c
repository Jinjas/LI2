
#include <string.h>
#include "Stack.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"

/**Verifica se o Valor y é igual que o Valor x, esta função devolve á stack 0 se for falso ou 1 se for verdade */
void iguais (STACK *s){
    Valor x = pop (s);
    Valor y = pop (s);
    Valor valor;
    valor.kind = INT;

    if (x.kind == ARRAY && y.kind == ARRAY){
        if ((y.u.a -> sp) == (x.u.a -> sp)){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else if (x.kind == INT && (y.kind == ARRAY|| y.kind == STRING)){
        push (s,y);
        push (s,x);
        forIndices (s);
    }
    else if (x.kind == STRING && y.kind == STRING){
        if (strcmp (y.u.s, x.u.s) == 0){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else{
        push (s,y);
        push (s,x);
        convertToDouble (s);
        Valor x = pop (s);
        convertToDouble (s);
        Valor y = pop (s);
         x.u.i = (y.u.d == x.u.d);
         x.kind = INT;
           push (s, x);   
    }

}

/**Verifica se o Valor y é menor que o Valor x, esta função devolve á stack 0 se for falso ou 1 se for verdade */
void menor (STACK *s){
    Valor x = pop (s);
    Valor y = pop (s);
    Valor valor;
    valor.kind = INT;

    if (x.kind == ARRAY && y.kind == ARRAY){
        if ((y.u.a -> sp) < (x.u.a -> sp)){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else if (x.kind == INT && (y.kind == ARRAY|| y.kind == STRING)){
        push (s,y);
        push (s,x);
        head (s);
    }
    else if (x.kind == STRING && y.kind == STRING){
        if(strcmp (y.u.s, x.u.s) < 0){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else{
        push (s,y);
        push (s,x);
        convertToDouble (s);
        Valor x = pop(s);
        convertToDouble (s);
        Valor y = pop(s);

        x.u.i = (y.u.d < x.u.d);
        x.kind = INT;
        push (s, x);
    }
}

/**Verifica se o Valor y é maior que o Valor x, esta função devolve á stack 0 se for falso ou 1 se for verdade */
void maior (STACK *s){
    Valor x = pop (s);
    Valor y = pop (s);
    Valor valor;
    valor.kind = INT;

    if (x.kind == ARRAY && y.kind == ARRAY){
        if ((y.u.a -> sp) > (x.u.a -> sp)){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else if (x.kind == INT && (y.kind == ARRAY|| y.kind == STRING)){
        push (s,y);
        push (s,x);
        tail (s);
    }
    else if (x.kind == STRING && y.kind == STRING){
        if(strcmp (y.u.s, x.u.s) > 0){
            valor.u.i = 1;
            push (s, valor);
        }
        else{ 
            valor.u.i = 0;
            push (s, valor);
        }
    }
    else {
        push (s,y);
        push (s,x);
        convertToDouble (s);
        Valor x = pop(s);
        convertToDouble (s);
        Valor y = pop(s);

         x.u.i = (y.u.d > x.u.d);
         x.kind = INT;
         push (s, x);
    }
}

/**Esta função nega o Valor x, convertendo o valor recebido em um int visto que a sua negação é um inteiro sendo assim devolve á stack 0 se o Valor x for 
 * diferente de zero e 1 caso o Valor x seja igual a 0*/
void nao (STACK *s){
    convertToInteger (s);
    Valor x = pop (s);   
    x.u.i = !x.u.i;
      push (s, x);
}

/**Função auxiliar da maior_logico, devolvendo há stack o maior dos dois valores*/
void maiorLogicoNumInt (STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);

    if (x.kind == INT && y.kind == INT){
        if (x.u.i > y.u.i)
            push (s, x);
        else 
            push (s, y);
    }
    else if (x.kind == INT && y.kind == DOUBLE){
        if (x.u.i > y.u.d)
            push (s, x);
        else 
            push (s, y);        
    }
    else if (x.kind == DOUBLE && y.kind == INT){
        if (x.u.d >= y.u.i) 
            push (s, x);
        else 
            push (s, y);          
    }
}

/**Esta função devolve há stack o maior dos dois valores*/
void maior_logico (STACK *s){
   Valor x = pop(s);
   Valor y = pop(s);

    if (x.kind == STRING && y.kind == STRING){
        if(strcmp (y.u.s, x.u.s) > 0){
            push (s, y);
        }
        else push (s, x);
    }
    else if (x.kind == ARRAY && y.kind == ARRAY){
        if ((y.u.a -> sp) > (x.u.a -> sp)){
            push (s, y);
        }
        else push (s, x);
    }
    else if (x.kind == DOUBLE && y.kind == DOUBLE){
        if (x.u.d > y.u.d)
            push (s, x);
        else 
            push (s, y);         
    }
    else {
        push(s, x);
        push(s, y);
        maiorLogicoNumInt(s);
    }
}


/*  CASO SEJA NECESSÁRIO PARA CHAR maior_logico
 else if (x.kind == CHAR && y.kind == CHAR){
        if (x.u.c > y.u.c){
            push (s, x);
        }
        else if (x.u.c <= y.u.c){
            push (s, y);
        }
    }
     else if (x.kind == CHAR && y.kind == DOUBLE){
        if (x.u.c > y.u.d){
            x.kind = CHAR;
            push (s, x);
        }
        if (x.u.c < y.u.d){
            y.kind = DOUBLE;
            push (s, y);
        }         
    }        
    else if (x.kind == CHAR && y.kind == INT){
        if (x.u.c > y.u.i){
            x.kind = CHAR;
            push (s, x);
        }
        if (x.u.c < y.u.i){
            y.kind = INT;
            push (s, y);
        }          
    }

    else if (x.kind == INT && y.kind == CHAR){
        if (x.u.i > y.u.c){
            x.kind = INT;
            push (s, x);
        }
        if (x.u.d < y.u.c){
            y.kind = CHAR;
            push (s, y);
        }          
    }
    else if (x.kind == DOUBLE && y.kind == CHAR){
        if (x.u.d > y.u.c){
            x.kind = DOUBLE;
            push (s, x);
        }
        if (x.u.d < y.u.c){
            y.kind = CHAR;
            push (s, y);
        }          
    }
*/


/**Função auxiliar da função menor_logico, devolvendo há stack o menor dos dois valores*/
void menorLogicoNumInt (STACK *s){
   Valor x = pop(s);
   Valor y = pop(s);
    if (x.kind == INT && y.kind == INT){
        if (x.u.i < y.u.i)
            push (s, x);
        else
            push (s, y);
    }
    else if (x.kind == INT && y.kind == DOUBLE){
        if (x.u.i < y.u.d)
            push (s, x);
        else
            push (s, y);
    }      
    else if (x.kind == DOUBLE && y.kind == INT){
        if (x.u.d <= y.u.i)
            push (s, x);
        else
            push (s, y);          
    } 
}

/**Esta função devolve há stack o menor dos dois valores*/
void menor_logico (STACK *s){
   Valor x = pop(s);
   Valor y = pop(s);
    if (x.kind == STRING && y.kind == STRING){
        if(strcmp (y.u.s, x.u.s) < 0){
            push (s, y);
        }
        else push (s, x);
    }
    else if (x.kind == ARRAY && y.kind == ARRAY){
        if ((y.u.a -> sp) < (x.u.a -> sp)){
            push (s, y);
        }
        else push (s, x);
    }
    else if (x.kind == DOUBLE && y.kind == DOUBLE){
        if (x.u.d < y.u.d)
            push (s, x);
        else 
            push (s, y);
    }
    else {
        push(s, x);
        push(s, y);
        menorLogicoNumInt(s);
    }
}

/*CASO SEJA NECESSÁRIO PARA CHAR NO menor_logico
    }
     else if (x.kind == CHAR && y.kind == CHAR){
        if (x.u.c < y.u.c){
            push (s, x);
        }
        else if (x.u.c >= y.u.c){
            push (s, y);
        }
     }
     else if (x.kind == CHAR && y.kind == DOUBLE){
        if (x.u.c < y.u.d){
            x.kind = CHAR;
            push (s, x);
        }
        if (x.u.c > y.u.d){
            y.kind = DOUBLE;
            push (s, y);
        }         
    }        
    else if (x.kind == CHAR && y.kind == INT){
        if (x.u.c < y.u.i){
            x.kind = CHAR;
            push (s, x);
        }
        if (x.u.c > y.u.i){
            y.kind = INT;
            push (s, y);
        }          
    }

    else if (x.kind == INT && y.kind == CHAR){
        if (x.u.i < y.u.c){
            x.kind = INT;
            push (s, x);
        }
        if (x.u.d > y.u.c){
            y.kind = CHAR;
            push (s, y);
        }          
    }

    else if (x.kind == DOUBLE && y.kind == CHAR){
        if (x.u.d < y.u.c){
            x.kind = DOUBLE;
            push (s, x);
        }
        if (x.u.d > y.u.c){
            y.kind = CHAR;
            push (s, y);
        }          
    }
*/


/**Função auxiliar da e_logico, que verifica se os dois Valores são trues e se forem devolve há stack aquele que sofreu pop primeiro (x), caso um deles tenha valor 
 * valor devolve o zero */
void e_logicomix (STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == INT && y.kind == DOUBLE){
        if (!y.u.d && x.u.i){
             push (s, y);
        }
        else push(s, x);
    }
    else if (x.kind == DOUBLE && y.kind == INT){
        if (!y.u.i && x.u.d){
         push (s, y);
        }
        else push(s, x);
    }    
}

/**A função verifica se os dois Valores são trues e se forem devolve há stack aquele que sofreu pop primeiro (x), caso um deles tenha valor valor 
 * devolve o zero*/
void e_logico (STACK *s){
    Valor x = pop(s);
    Valor y = pop(s);
    if (x.kind == INT && y.kind == INT){
        if (!y.u.i && x.u.i){
            push (s, y);
        } 
        else push(s, x);
    }
    else if (x.kind == DOUBLE && y.kind == DOUBLE){
        if (!y.u.d && x.u.d){ 
            push (s, y);  
        }
        else push(s, x);
    }
    else {
        push(s, x);
        push(s, y);
        e_logicomix(s);
    }

}

/* CASO SEJA NECESSÁRIO PARA CHAR e_logico
    else if (x.kind == DOUBLE && y.kind == DOUBLE){
        if (!y.u.d && x.u.d){ 
            push (s, y);  
        }
        else push(s, x);
    }
    else if (x.kind == INT && y.kind == CHAR){
        if (!y.u.c && x.u.i) push (s, y);
        else push (s, x);
    }
    else if (x.kind == DOUBLE && y.kind == CHAR){
        if (!y.u.c && x.u.d) push (s, y);
        else push (s, x);
    }
    else if (x.kind == CHAR && y.kind == INT){
        if (!y.u.i && x.u.c) push (s, y);
        else push (s, x);
    }
    else if (x.kind == CHAR && y.kind == DOUBLE){
        if (!y.u.d && x.u.c) push (s, y);
        else push (s, x);
    }
    else if (x.kind == CHAR && y.kind == CHAR){
        if (!y.u.c && x.u.c) push (s, y);
        else push (s, x);
    }
*/

/**Esta função devolve há stack o Valor y se os dois valores forem verdadeiros, caso um deles seja igual a 0 devolve o que tem valor verdadeiro e por fim 
 * se os dois forem iguais a 0 devolve um deles*/
void ou_logico (STACK *s){
   Valor x = pop(s);
   Valor y = pop(s);

    if (y.kind == INT){
        if (y.u.i) push (s, y);
          else push (s, x);
    }
    else if (y.kind == DOUBLE){
        if (y.u.d) push (s, y);
          else push (s, x);
    }
    else if (y.kind == CHAR){
        if (y.u.c) push (s, y);
          else push (s, x);
    }
}

/**Esta função retira da stack o Valor x,y e z, o ? verifica se o Valor z é igual a 0 devolve o Valor x caso o Valor de z seja diferente de 0 devolve há stack 
 * o Valor y*/
Valor valorarray (Valor x){
    if ((x.u.a -> sp) > 0){
        x.u.i = 1;
        x.kind = INT;
    }
    else{
       x.u.i = 0;
       x.kind = INT;
    }  
    return x;
}

/**Esta função retira da stack o Valor x,y e z, o ? verifica se o Valor z é igual a 0 devolve o Valor x caso o Valor de z seja diferente de 0 devolve há stack 
 * o Valor y*/
void if_then_else (STACK *s){
   Valor x = pop(s);
   Valor y = pop(s);
   Valor z = pop(s);
    if (x.kind == INT && y.kind == INT && z.kind == ARRAY){
       z.kind = INT;
       z = valorarray(z);
    }
    else if (x.kind == ARRAY && y.kind == INT && z.kind == INT){
       x.kind = INT;
       x = valorarray(x);
    }
       if (!z.u.i) push(s,x);
       else push(s,y);
}
