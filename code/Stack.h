/**Tudo o que está aqui está definido em Stack.c, isto é só para poder incluir na main */

/**Optei por utilizar unions, porque é mais fácil armazenar diferentes tipos de dados e mais eficiente (pelo menos em termos de memória)
     *  do que ter uma stack de strings com um caracter no início a indicar qual o seu tipo*/

/**typedef da stack*/
typedef struct STACK STACK;
/**typedef dos elementos*/
typedef struct Valor Valor;
/**estrotura dos elementos deste projeto*/
struct Valor{
    enum{INT, DOUBLE, CHAR, STRING, ARRAY, BLOCK} kind;        //Tag field
    union{
       long long int i;
       double d;
       char c;
       char *s;
       STACK *a;
    }u;
};

/**Isto é a struct da stack */    
struct STACK
{
    unsigned long int tamanho;
    Valor *stack;
    /** O sp é a variável onde é guardado a posição atual do topo da stack */
    int sp;
    Valor *variables;
};

/**Esta é a função que inicializa os valores da STACK */
void init(STACK *s);

/** Esta função serve para aumentar dinamicamente o tamanho da stack à medida que for necessário*/
STACK * memoryHandler(STACK *s);

/**Esta é a função que cria a STACK e atribui dinamicamente o tamanho da stack*/
STACK * new_stack();

/**Esta função serve para imprimir n número de elementos da stack começando pelo topo. Para isso a função executa um loop n vezes onde é verificado qual
 * é o tipo do elemento para poder atribuir a versão do printf apropriada.
*/
void PrintStack(STACK *s, int x);

/**Esta é a função para acrescentar um elemento à stack aumentando o sp*/
void push(STACK *s, Valor elem);

/** Esta é a função para retirar um elemento da stack e retornar o seu valor diminuindo o sp*/
Valor pop(STACK *s);

/**Faz pop do valor que está na última posição da stack*/
Valor popFromTheBottom(STACK *s);

/**função para iniciar o array das variaveis*/
void initVariables(STACK *s);
/**realock da stack*/
STACK * realocador(STACK * s);
/**Esta é a função que cria uma string e atribui dinamicamente o seu tamanho*/
char * newString ();

/**Esta função serve para imprimir o topo da stack*/
void PrintStacktopo (STACK *s);
