#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <vector>
using namespace std;

class Table
{
    public:
        Table();                                            //Construtor da classe Table.
        virtual ~Table();                                   //Destrutor da classe Table.
        char lookUp(char a, char b);                        //Retorna o caractere equivalente � opera��o a*b.
        bool readFile(const char *path);                    //L� um arquivo descrito pela string path.
        vector<char> & getElements() { return elements; }   //Retorna o vetor de caracteres com todos os elementos.
        bool isInTable(char c);                             //Verifica se um elemento est� na tabela.
    protected:
    private:
        bool addElement(char key1, char key2, char t);      //Adiciona ou substitui um elemento na tabela.
        map<char, map<char, char> > table;                  //Mapa para todas as opera��es.
        vector<char> elements;                              //Vetor com todos os elementos.
};

#endif // TABLE_H
