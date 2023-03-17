/**Esta função faz a soma entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 */
void adicionar(STACK *s);
/**Esta função faz a subtração entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void subtrair(STACK *s);
/**
 * Esta função faz a multiplicação entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 * */
void multiplicar(STACK *s);
/**
 * Esta função faz a divisão entre números, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 * */
void dividir(STACK *s);
/**Esta função faz a interceção dos bits entre dois inteiros, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * & 00011001
 *   ________
 *   00001000  = 8
*/
void andBitwise(STACK *s);
/**Esta função faz a dijunção dos bits entre dois inteiros, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * | 00011001
 *   ________
 *   00011101  = 29
*/
void orBitwise(STACK *s);
/**Esta função compara dois inteiros através dos bits, caso sejam iguais poe 0, caso contrário 1, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 *   00001100
 * ^ 00011001
 *   ________
 *   00010101  = 21
 */
void xorBitwise(STACK *s);
/**Esta função transforma um numero no seu complemento, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.
 * ~ 00100011 
 *   ________
 *   11011100  = 220
*/
void notBitwise(STACK *s);
/**Esta função faz a exponencial de x em função de y, sendo x o penúltimo valor da stack e y o último, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void exponenciacao(STACK *s);
/**Esta função incrementa uma unidade ao último elemento da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void incrementar(STACK *s);
/**Esta função decrementa uma unidade ao último elemento da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void decrementar(STACK *s);
/**Esta função devolve o resto da divisão inteira entre os dois últimos elementos da stack, fazendo para isso pop duas vezes e guardando os seus valores em variáveis x e y que serão usadas para realizar 
 * a operação cujo valor será guardado em x para evitar a criação de variáveis extra, depois da atribuição do valor a x, dá-se push a x.*/
void modulo(STACK *s);


