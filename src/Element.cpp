#include "Element.h"
#include <cstdio>

/* Função Element
 * Construtor da classe Element.
 * Seta a tabela, o caractere e verifica se o caractere representa o
 * de fim de string (elemento inválido).
 */

Element::Element(Table * t, char c)
{
    table = t;
    carac = c;
    isElementValid = (c!='\0');
}

/* Operador +
 * Operação binária descrita pela tabela.
 */

Element Element::operator +(const Element &other){
    if (table==NULL){
        printf("Erro: refêrencia para a table NULL.\n");
        return Element(NULL, '\0');
    }
    else return Element(table, table->lookUp(carac, other.carac));
}

/* Operador *
 * Operação binária descrita pela tabela.
 * Mesma coisa que o operador +.
 */

Element Element::operator *(const Element &other){
    return (*this) + other;
}

/* Função ~Element
 * Destrutor da classe Element.
 */

Element::~Element()
{
    //dtor
}
