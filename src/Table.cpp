#include "Table.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define MAXN 1009

using namespace std;

/* Fun��o Table
 * Construtor da classe Table.
 */

Table::Table()
{
    //ctor
}

/* Fun��o addElement
 * Adiciona um elemento ao mapa de opera��es.
 */

bool Table::addElement(char key1, char key2, char t)
{
    table[key1][key2] = t;
    return true;
}

/* Fun��o lookUp
 * Retorna o caractere equivalente � opera��o a*b.
 * Retorna o caractere de fim de string caso a ou b n�o
 * sejam v�lidos os n�o estejam na tabela.
 */

char Table::lookUp(char a, char b)
{
    if (!table.count(a) || !table[a].count(b)){
        return '\0';
    }
    return table[a][b];
}

/* Fun��o readFile
 * L� a tabela descrita pelo diret�rio path.
 * Constr�i o mapa de opera��es e o vetor de elementos.
 */

bool Table::readFile(const char *path)
{
	FILE* in = fopen(path, "r");

	char str[MAXN];
	int n, m, i, j;

	fscanf(in, " %s ", str);
	n = strlen(str);

	elements.clear();
	for (i = 0, j = 1; i<n; i++) {
		elements.push_back(str[i]);
		addElement('1', elements[i], str[i]);
	}

	while (!feof(in)) {
		fscanf(in, " %s ", str);
		m = strlen(str);
		if (n != m) {
			printf("Tabela inv�lida, n�mero de elementos nas linhas desigual\n");
			return false;
		}
		for (i = 0; i<n; i++) {
			addElement(elements[j], elements[i], str[i]);
		}
		j++;
	}

	if (n != j) {
		printf("Tabela inv�lida, n�mero de linhas (%d) diferente do n�mero de colunas (%d)\n", j, n);
		return false;
	}

	fclose(in);

	return true;
}

/* Fun��o isInTable
 * Verifica se um elemento est� na tabela por meio do mapa de opera��es.
 */

bool Table::isInTable(char c)
{
    return table.count(c);
}

/* Fun��o ~Table
 * Destrutor da classe Table.
 */

Table::~Table()
{
    //dtor
}
