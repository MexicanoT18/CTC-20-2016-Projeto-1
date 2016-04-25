#include "Table.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define MAXN 1009

using namespace std;

/* Função Table
 * Construtor da classe Table.
 */

Table::Table()
{
    //ctor
}

/* Função addElement
 * Adiciona um elemento ao mapa de operações.
 */

bool Table::addElement(char key1, char key2, char t)
{
    table[key1][key2] = t;
    return true;
}

/* Função lookUp
 * Retorna o caractere equivalente à operação a*b.
 * Retorna o caractere de fim de string caso a ou b não
 * sejam válidos os não estejam na tabela.
 */

char Table::lookUp(char a, char b)
{
    if (!table.count(a) || !table[a].count(b)){
        return '\0';
    }
    return table[a][b];
}

/* Função readFile
 * Lê a tabela descrita pelo diretório path.
 * Constrói o mapa de operações e o vetor de elementos.
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
			printf("Tabela inválida, número de elementos nas linhas desigual\n");
			return false;
		}
		for (i = 0; i<n; i++) {
			addElement(elements[j], elements[i], str[i]);
		}
		j++;
	}

	if (n != j) {
		printf("Tabela inválida, número de linhas (%d) diferente do número de colunas (%d)\n", j, n);
		return false;
	}

	fclose(in);

	return true;
}

/* Função isInTable
 * Verifica se um elemento está na tabela por meio do mapa de operações.
 */

bool Table::isInTable(char c)
{
    return table.count(c);
}

/* Função ~Table
 * Destrutor da classe Table.
 */

Table::~Table()
{
    //dtor
}
