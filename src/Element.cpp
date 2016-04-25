#include "Element.h"
#include <cstdio>

/* Fun��o Element
 * Construtor da classe Element.
 * Seta a tabela, o caractere e verifica se o caractere representa o
 * de fim de string (elemento inv�lido).
 */

Element::Element(Table * t, char c)
{
    table = t;
    carac = c;
    isElementValid = (c!='\0');
}

/* Operador +
 * Opera��o bin�ria descrita pela tabela.
 */

Element Element::operator +(const Element &other){
    if (table==NULL){
        printf("Erro: ref�rencia para a table NULL.\n");
        return Element(NULL, '\0');
    }
    else return Element(table, table->lookUp(carac, other.carac));
}

/* Operador *
 * Opera��o bin�ria descrita pela tabela.
 * Mesma coisa que o operador +.
 */

Element Element::operator *(const Element &other){
    return (*this) + other;
}

/* Fun��o ~Element
 * Destrutor da classe Element.
 */

Element::~Element()
{
    //dtor
}
