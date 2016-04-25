#include <cstdio>
#include <vector>
#include <ctime>
#include "Table.h"
#include "Element.h"
#include "Group.h"
#include "HasseDiagram.h"
#define MAXN 1009

using namespace std;

/* Função main
 * Chama todas as outras funções para executar a atividade.
 */

int main()
{
    clock_t last, current;
    char inFile[MAXN], outFile[MAXN];

    printf("Inicializando tabela...\n");
    last = clock();
    Table table;
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Lendo tabela...\n");
    printf("Digite o nome do arquivo que contém a tabela de entrada. Não esqueça da extensão.\n");
    gets(inFile);
    last = clock();
    if(!table.readFile(inFile)){
        current = clock();
        printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));
        return 1;
    }
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Tabela lida, recebendo lista de elementos...\n");
    last = clock();
    vector<char> & elements = table.getElements();
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Inicializando grupo...\n");
    last = clock();
    Group G(elements, &table);
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Verificando validade do grupo...\n");
    last = clock();
    if (!G.isValidGroup()){
        current = clock();
        printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));
        printf("Grupo não válido. Programa finalizando.\n");
        return 0;
    }
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Gerando subgrupos...\n");
    last = clock();
    list<Group> subGroups = G.generateSubgroups();
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Inicializando diagrama de Hasse...\n");
    last = clock();
    HasseDiagram hasse(subGroups);
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Construindo diagrama de Hasse...\n");
    last = clock();
    hasse.buildDiagram();
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Escrevendo diagrama de Hasse em arquivo .dot...\n");
    printf("Digite o nome do arquivo onde será escrita a saída. Use um formato compatível com o GraphViz.\n");
    gets(outFile);
    last = clock();
    hasse.writeFile(outFile);
    current = clock();
    printf("Tempo de execução: %f segundos.\n\n", ((double)(current - last)/CLOCKS_PER_SEC));

    printf("Finalizando programa...\n");
    return 0;
}
