/**Estas funções estão definidas em guiao5.c, isto é só para poder incluir na main */

/**
 * definindo o bloco como um novo tipo (no caso uma string)
 * e tendo em conta que o primeiro elemento da string e o ultimo são { e } respetivamente,
 * estes são ignorados ao iniciar a starter
 */
/**esta função executa o bloco ao elemento que estiver a seguir na stack*/
void aoElemento(STACK *s); // ~
/** 
 * Esta função  executa o bloco para cada caracter/elemento da string/array e mete na mesma o resultado.
*/
void aoConteudo(STACK *s); // %
/** 
 * Esta função replica a função 'aoConteudo' mas, ao invés de colocar na string/array, apenas coloca os que são verdadeiros 
*/
void blockfilter(STACK *s); // ,
/**
 * Esta função executa o bloco e no fim faz um pop, depois o bloco é executado novamente se o Valor que foi removido da stack tem um valor verdadeiro.
 */
void whileTrue (STACK *s); // w
/**
 * Esta função faz o Fold sobre um array usando o bloco 
*/
void fold (STACK *s);
/**
 * esta função ordena o array/string usando o bloco 
*/
void sort_using_blocks (STACK *s);

