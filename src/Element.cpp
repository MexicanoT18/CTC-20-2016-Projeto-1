#include "Element.h"
#include <cstdio>

Element::Element(Table * t, char c)
{
    table = t;
    carac = c;
    isElementValid = (c!='\0');
}

Element Element::operator +(const Element &other){
    if (table==NULL){
        printf("Erro: refêrencia para a table NULL.\n");
        return Element(NULL, '\0');
    }
    else return Element(table, table->lookUp(carac, other.carac));
}

Element Element::operator *(const Element &other){
    return (*this) + other;
}

Element::~Element()
{
    //dtor
}
