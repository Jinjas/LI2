/**Esta é a função onde são tratados as diferentes "palavras" que recebemos, ela analisa o tipo de palavra que é (se é um dígito ou símbolo) e
 * se for dígito é covertido em número e dá-se push para a stack, se for caracter entra no case para determinar que função deve ser utilizada e caso
 * não comece com nenhum caracter especial é dado push para a stack como string. No switch usamos return como alternativa ao bre ak, porque se não o 
 * fizermos o mooshack não aceita o código e neste caso é exatamente igual usar um ou outro, porque o switch é a última instrução do código
*/
void handler (STACK *s, char palavra[]);
/**simbolos para guião1*/
char guiao1Handler (STACK *s, char palavra []);
/**simbolos para guião2*/
char guiao2Handler (STACK *s, char palavra[]);
/**simbolos para guião3*/
char guiao3Handler (STACK *s, char palavra[]);
/**simbolos para guiao4*/
char guiao4Handler(STACK * s, char palavra[]);
/**simbolos para guiao5*/
char guiao5Handler(STACK * s, char palavra[]);
/**função para criar um array*/
char *ArrayHandler(STACK *s, STACK *original, char linha[]);
/**copiar um array para o colocar na stack(nao perder o original)*/
void PutStringToStack(STACK *s,char palavra[]);
/** recebe a stack atual e uma linha de insturcoes;*/
void starter(STACK *s, char linha[]);