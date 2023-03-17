/**Estas funções estão definidas em guiao3.c, isto é só para poder incluir na main */

/**Esta função devolve há stack o maior dos dois valores*/
void maior_logico (STACK *s);

/**Esta função devolve há stack o menor dos dois valores*/
void menor_logico (STACK *s);

/**A função verifica se os dois Valores são trues e se forem devolve há stack aquele que sofreu pop primeiro (x), caso um deles tenha valor false 
 * devolve o zero*/
void e_logico (STACK *s);

/**Esta função devolve há stack o Valor y se os dois valores forem verdadeiros, caso um deles seja igual a 0 devolve o que tem valor verdadeiro e por fim 
 * se os dois forem iguais a 0 devolve um deles*/
void ou_logico (STACK *s);

/**Verifica se o Valor y é igual que o Valor x, esta função converte os Valores recebidos em Doubles assim simplificando a função e torná-la mais simples,
 * visto que a função devolve á stack 0 se for falso ou 1 se for verdade */
void iguais (STACK *s);

/**Esta função nega o Valor x, convertendo o valor recebido em um int visto que a sua negação é um inteiro sendo assim devolve á stack 0 se o Valor x for 
 * diferente de zero e 1 caso o Valor x seja igual a 0*/ 
void nao (STACK *s);

/**Verifica se o Valor y é menor que o Valor x, esta função converte os Valores recebidos em Doubles assim simplificando a função e torná-la mais simples,
 * visto que a função devolve á stack 0 se for falso ou 1 se for verdade */
void menor (STACK *s);

/**Verifica se o Valor y é maior que o Valor x, esta função converte os Valores recebidos em Doubles assim simplificando a função e torná-la mais simples,
 * visto que a função devolve á stack 0 se for falso ou 1 se for verdade */
void maior (STACK *s);

/**Esta função retira da stack o Valor x,y e z, o ? verifica se o Valor z é igual a 0 devolve o Valor x caso o Valor de z seja diferente de 0 devolve há stack 
 * o Valor y*/
void if_then_else (STACK *s);
