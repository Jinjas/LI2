#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "handler.h"
/**Esta é a função main, é aqui onde toda a lógica do programa é processada */
int main(){

    STACK *mystack = new_stack();
    init(mystack);
    initVariables(mystack);

    char *linha = (char*)malloc(BUFSIZ * sizeof(char *));
    if (fgets(linha, BUFSIZ, stdin) != 0){
      starter(mystack, linha);
    }

  /**Imprime a stack inteira, começando por baixo*/
  PrintStack(mystack, mystack-> sp);
  printf("\n");
  
    return 0;
}




