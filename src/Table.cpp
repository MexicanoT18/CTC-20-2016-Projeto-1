#include "Table.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define MAXN 100009

using namespace std;

Table::Table()
{
    //ctor
}

bool Table::addElement(char key1, char key2, char t)
{
    table[key1][key2] = t;
    return true;
}

char Table::lookUp(char a, char b)
{
    if (!table.count(a) || !table[a].count(b)){
        return '\0';
    }
    return table[a][b];
}

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

bool Table::isInTable(char c)
{
    return table.count(c);
}

Table::~Table()
{
    //dtor
}
