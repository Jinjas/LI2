/**Estas funções estão definidas em guiao4.c, isto é só para poder incluir na main */
/** função que junta a um array/string a um elemento ou a outro array/string */
void concat(STACK *s); // +

/** Função qe nplica o conteudo de uma stack/string 
 * na string copia a inicial e concatena n vezes e no array faz de forma recursiva com uma copia do msm
*/
void strConcaten(STACK *s); // *

/** põe na stack o sp do array ou o length da lista, se for caracter ou inteiro devolve uma lista com os caracteres/numeros até ao dado */
void lengthORrange(STACK *s);// ,

/** Função que troca uma string/array pelo elemento no indice dado.
 * Em ambos os casos é instantaneo porque ambos podem ser tratados como arrays
*/
void forIndices (STACK *s);// =

/**Função para tirar tds os elementos do array e por na stack principal*/
void moveALL(STACK *s, Valor valor); //~

/**Procurar substring na string e devolver o índice ou -1 se não encontrar*/
void findSubstring(STACK *s, Valor objetivo, Valor original);

/**Esta função devolve há stack o array/string sem o primeiro elemento/caracter e depois coloca na stack o que foi removido na dando push após do array/string*/
void remov_first_elem (STACK *s); // (

/**Esta função devolve há stack o array/string sem o último elemento/caracter e depois coloca na stack o que foi removido dando push do após do array/string*/
void remov_last_elem (STACK *s); // )

/**função que separa uma string por espaços em branco e coloca as palavras num array*/
void stringbywhitespace(STACK *s); // S/

/**funçao '>' retira elementos da cabeça até a string/array ficar com n elementos*/
void tail(STACK *s); // >

/**funçao '<' retira elementos do fim até a string/array ficar com n elementos*/
void head(STACK *s); // <

/** função que lê um ficheiro/todas as linhas da consola*/
void readALL (STACK *s); // t

/** função que separa uma string cada vez que ocorre uma substring dada e põe as novas string num array*/
void string_by_substring (STACK *s);// /

/** função que separa uma string cada vez que ocorre um '\n' e põe as novas string num array*/
void string_for_newlines(STACK *s);// M/


