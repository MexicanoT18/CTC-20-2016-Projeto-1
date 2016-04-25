#ifndef ELEMENT_H
#define ELEMENT_H

#include "Table.h"

class Element
{
    public:
        Element(Table * t, char c);                     //Construtor da classe Element.
        virtual ~Element();                             //Destrutor da classe Element.
        Element operator +(const Element &other);       //Operador com a opera��o bin�rio do grupo.
        Element operator *(const Element &other);       //Mesma opera��o que acima, por�m com outra representa��o.
        bool operator <(const Element& other) const {   //Comparador de elementos.
            return carac < other.carac;
        }
        bool operator !=(const Element& other) const {  //Verifica a desigualdade de elementos.
            return !(*this == other);
        }
        bool operator ==(const Element& other) const {  //Verifica a igualdade de elementos.
            return carac == other.carac;
        }
        char carac;                                     //Caracatere do elemento.
        Table * table;                                  //Ponteiro para a tabela.
        bool isValid() { return isElementValid; }       //Verifica a validade de um elemento.
    protected:
    private:
        bool isElementValid;                            //Guarda se o elemento � v�lido ou n�o.
};

#endif // ELEMENT_H
