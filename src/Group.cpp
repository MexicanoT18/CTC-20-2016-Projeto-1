#include "Group.h"
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

/* Função Group
 * Construtor da classe Group.
 * Constrói a partir de um vetor de elementos.
 * Ordena o vetor de elementos.
 * Define o elemento neutro.
 */

Group::Group(const vector<Element> &arr)
{
    elements = arr;
    sort(elements.begin(), elements.end());

    table = arr[0].table;

    neutralElementIndex = findNeutralElementIndex();
}

/* Função Group
 * Construtor da classe Group.
 * Constrói a partir de um vetor de caracteres e do ponteiro para a tabela.
 * Ordena o vetor de elementos.
 * Define o elemento neutro.
 */

Group::Group(const vector<char> &arr, Table * t)
{
    for(int i=0; i<(int)arr.size(); i++){
        elements.push_back(Element(t, arr[i]));
    }
    sort(elements.begin(), elements.end());

    table = t;

    neutralElementIndex = findNeutralElementIndex();
}

/* Função belongTo
 * Verifica se o grupo pertence a um outro fazendo a busca de caracteres
 * desete grupo no próximo.
 */

bool Group::belongsTo(Group & other){
    int otherIndex;
    for(int i=0; i<(int)elements.size(); i++){
        otherIndex = other.findIndexOf(elements[i].carac);
        if (!other.isValidIndex(otherIndex)) return false;
    }
    return true;
}

/* Função isValidIndex
 * Verifica se o número n representa uma posição válida no vetor de elementos.
 */

bool Group::isValidIndex(int n){
    return n >= 0 && n < (int)elements.size();
}

/* Função neutralElement
 * Retorna o elemento neutro do grupo.
 * Caso não haja elemento neutro, retorna um elemento inválido com o caractere '\0'.
 */

Element Group::neutralElement()
{
    if (isValidIndex(neutralElementIndex)){
        return elements[neutralElementIndex];
    }
    else return Element(NULL, '\0');
}

/* Função verifyAssociativity
 * Verifica se vale a propriedade da associatividade neste grupo para todas as possibilidades.
 * Três loops para fazer a verificação.
 */

bool Group::verifyAssociativity()
{
    for (int i = 0; i < (int)elements.size(); i++){
		for (int j = 0; j < (int)elements.size(); j++){
			for (int k = 0; k < (int)elements.size(); k++){
				if ((elements[i] + elements[j]) + elements[k] !=
					elements[i] + (elements[j] + elements[k])){
					return false;
				}
			}
		}
	}
	return true;
}

/* Função isNeutralElement
 * Verifica se o elemento de índice n é o elemento neutro.
 * Faz todos os testes de operações para verificar as propriedades do elemento neutro.
 * Poderia verificar se o elemento representa o caractere '1', mas
 * foi feito um grupo para todos os modelos de tabela.
 */

bool Group::isNeutralElement(int n)
{
    if (!isValidIndex(n)) return false;
    for(int i=0; i<(int)elements.size(); i++){
        if ((elements[n]*elements[i]) != elements[i] || (elements[i]*elements[n]) != elements[i])
            return false;
    }
	return true;
}

/* Função isNeutralElement
 * Verifica se o elemento parametrado é o elemento neutro.
 * Procura o índice do elemento no vetor e verifica se o índice é o do elemento neutro.
 * Poderia verificar se o elemento representa o caractere '1', mas
 * foi feito um grupo para todos os modelos de tabela.
 */

bool Group::isNeutralElement(Element element)
{
    int elementIndex = findIndexOf(element.carac);
	return isNeutralElement(elementIndex);
}

/* Função inverse
 * Verifica se o grupo satisfaz a propriedade do elemento inverso.
 * Procura o elemento inverso de cada elemento e o inverso deste e compara os dois.
 */

bool Group::inverse()
{
	int inverseindex, inverseindex1;
	for (int i = 0; i < (int)elements.size(); i++)
	{
		inverseindex = inverseElementOf(i);
		inverseindex1 = inverseElementOf(inverseindex);
		if (inverseindex1 != i){
			return false;
		}
	}
	return true;
}

/* Função isClosed
 * Verifica se a operação é fechada para o grupo.
 * Executa todas as possibilidades de operação e procura o elemento resultante no grupo.
 */

bool Group::isClosed()
{
    int sumIndex;
	for (int i = 0; i < (int)elements.size(); i++){
		for (int j = 0; j < (int)elements.size(); j++){
			sumIndex = findIndexOf((elements[i] + elements[j]).carac);
			if (!isValidIndex(sumIndex)) return false;
		}
	}
	return true;
}

/* Função findNeutralElementIndex
 * Procura pelo elemento neutro do grupo.
 * Testa a propriedade do elemento neutro para todos os elementos.
 * Poderia simplesmente procurar pelo elemento com o caractere '1',
 * mas foi feito um grupo para tipo genérico de elemento neutro.
 * Retorna -1 caso não ache.
 */

int Group::findNeutralElementIndex()
{
	for (int i = 0; i < (int)elements.size(); i++) {
		if (isNeutralElement(i)) return i;
	}
	return -1;
}

/* Função inverseElementOf
 * Procura pelo elemento inverso do que está no índice n.
 * Procura por todos os elementos e faz o teste de inversibilidade.
 * Retorna -1 caso não ache.
 */

int Group::inverseElementOf(int n)
{
	if (!isValidIndex(n)) return -1;
	Element searchElement = elements[n];
	for (int i = 0; i < (int)elements.size(); i++){
		if (isNeutralElement(elements[i] + searchElement)){
			return i;
		}
	}
	return -1;
}

/* Função isValidGroup
 * Verifica se o grupo é válido.
 * Verifica a propriedade da associatividade, do elemento neutro e do elemento inverso.
 */

bool Group::isValidGroup()
{
    return isClosed() && inverse() && verifyAssociativity();
}

/* Função generateSubgroups
 * Gera todos os subgrupos do grupo atual e retorna uma lista com eles.
 * Inicializa os vetores de presença no backtrack e as pulhas auxiliares.
 * Chama o backtrack.
 */

list<Group> Group::generateSubgroups()
{
    list<Group> ans;

    if (!isValidGroup() || !isValidIndex(neutralElementIndex)){
        ans.clear();
        return ans;
    }

    isPresent = new int[(int)elements.size()];
    for(int i=0; i<(int)elements.size(); i++) isPresent[i]=0;
    isPresent[neutralElementIndex]=1;

    dfsVec = new stack<int>[(int)elements.size()];
    toRemoveVec = new stack<int>[(int)elements.size()];

    backTrack(ans, 0);

    return ans;
}

/* Função clearStack
 * Esvazia uma pilha recebendo uma referência pra ela.
 */

bool Group::clearStack(stack<int> & stck){
    while(!stck.empty()) stck.pop();
    return true;
}

/* Função backTrack
 * Executa o algoritmo de backTrack para o n-ésimo elemento.
 * Caso n seja o final, monta o grupo, verifica a validade dele e adiciona na lista.
 * Caso ele já tenha sido marcado como presente ou ausente, prossegue.
 * Supõe que o elemento não está e prossegue.
 * Supõe que o elemento está e utiliza DFS para procurar pelos elementos que também deve estar
 * segundo os elementos que já estão e segundo o que acabou de adicionado.
 */

void Group::backTrack(list<Group> & ans, int n)
{
    if (n==(int)elements.size()){
        newElements.clear();
        for(int i=0; i<n; i++){
            if (isPresent[i]==1) newElements.push_back(elements[i]);
        }
        Group H(newElements);
        if (H.isValidGroup()) ans.push_back(H);
        return;
    }

    if (isPresent[n]!=0){
        backTrack(ans, n+1);
        return;
    }

    isPresent[n]=-1;
    backTrack(ans, n+1);

    stack<int> & toRemove = toRemoveVec[n];
    stack<int> & dfs = dfsVec[n];

    isPresent[n]=1;
    clearStack(toRemove); toRemove.push(n);
    clearStack(dfs); dfs.push(n);

    int newToAdd, current;
    bool possible = true;

    while(!dfs.empty()){
        current = dfs.top();
        dfs.pop();
        for(int i=0; possible && i<(int)elements.size(); i++){
            if (isPresent[i]==1)
            {
                newToAdd = findIndexOf((elements[i]+elements[current]).carac);
                if (newToAdd == -1)
                {
                    printf("Erro, operação não fechada\n");
                    return;
                }
                if (isPresent[newToAdd]==-1) possible = false;
                if (isPresent[newToAdd]==0){
                    toRemove.push(newToAdd);
                    dfs.push(newToAdd);
                    isPresent[newToAdd]=1;
                }
                newToAdd = findIndexOf((elements[current]*elements[i]).carac);
                if (newToAdd == -1)
                {
                    printf("Erro, operação não fechada\n");
                    return;
                }
                if (isPresent[newToAdd]==-1) possible = false;
                if (isPresent[newToAdd]==0){
                    toRemove.push(newToAdd);
                    dfs.push(newToAdd);
                    isPresent[newToAdd]=1;
                }
            }
        }
    }

    if (possible) backTrack(ans, n+1);

    while(!toRemove.empty()){
        isPresent[toRemove.top()]=0;
        toRemove.pop();
    }
}

/* Função findIndexOf
 * Executa busca binária para achar o índice de um elemento no vetor de elementos.
 * Caso não ache, retorna -1.
 */

int Group::findIndexOf(char c)
{
    if (elements[0].carac > c) return -1;

    int low = 0;
    int high = elements.size();
    int middle;

    while(high>low+1){
        middle = (high+low)/2;
        if (elements[middle].carac <= c) low = middle;
        else high = middle;
    }

    if (elements[low].carac == c) return low;
    else return -1;
}

/* Função toString
 * Pega todos os elementos e concatena seus caracteres em uma string.
 */

string Group::toString(){
    string name;
    for(int i = 0; i < (int)elements.size(); i++){
        name.push_back(elements[i].carac);
    }
    return name;
}

/* Função ~Group
 * Destrutor da classe Group.
 */

Group::~Group()
{
    //dtor
}
