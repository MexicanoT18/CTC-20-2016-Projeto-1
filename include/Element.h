#ifndef ELEMENT_H
#define ELEMENT_H

#include "Table.h"

class Element
{
    public:
        Element(Table * t, char c);
        virtual ~Element();
        Element operator +(const Element &other);
        Element operator *(const Element &other);
        bool operator <(const Element& other) const {
            return carac < other.carac;
        }
        bool operator !=(const Element& other) const {
            return !(*this == other);
        }
        bool operator ==(const Element& other) const {
            return carac == other.carac;
        }
        char carac;
        Table * table;
        bool isValid() { return isElementValid; }
    protected:
    private:
        bool isElementValid;
};

#endif // ELEMENT_H
