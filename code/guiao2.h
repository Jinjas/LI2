/**A função duplicate copia o elemento que está no topo da stack para uma variável x
 *  e dá-lhe push */
void duplicate(STACK *s);
/**A função swap troca os dois elementos que estão no topo da stack */
void swap(STACK *s);
/**A função tripleSwap troca a ordem dos 3 elementos que estão no topo da stack */
void tripleSwap(STACK *s);
/**A função removeTerm remove o termo da stack que está na posição correspondente ao valor
 * inteiro do valor do top da stack
 */
void removeTerm(STACK *s);
/** Esta função serve para converter o elemento que está no topo da stack para uma int. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToInteger(STACK *s);
/** Esta função serve para converter o elemento que está no topo da stack para uma string. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToString(STACK *s);
/** Esta função serve para converter o elemento que está no topo da stack para um double. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToDouble(STACK *s);
/** Esta função serve para converter o elemento que está no topo da stack para um char. Para isso é dado pop da stack e guarda-se o seu valor e 
 *  posteriormente verifica-se qual o seu tipo para poder aplicar a função de conversão adequada. Após a conversão dá-se push do valor convertido
 *  para a stack.
*/
void convertToChar(STACK *s);
/**Esta função lê e retorna uma linha */
void readLine ();
