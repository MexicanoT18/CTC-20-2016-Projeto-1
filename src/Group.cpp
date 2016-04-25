#include "Group.h"
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

/* Fun��o Group
 * Construtor da classe Group.
 * Constr�i a partir de um vetor de elementos.
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

/* Fun��o Group
 * Construtor da classe Group.
 * Constr�i a partir de um vetor de caracteres e do ponteiro para a tabela.
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

/* Fun��o belongTo
 * Verifica se o grupo pertence a um outro fazendo a busca de caracteres
 * desete grupo no pr�ximo.
 */

bool Group::belongsTo(Group & other){
    int otherIndex;
    for(int i=0; i<(int)elements.size(); i++){
        otherIndex = other.findIndexOf(elements[i].carac);
        if (!other.isValidIndex(otherIndex)) return false;
    }
    return true;
}

/* Fun��o isValidIndex
 * Verifica se o n�mero n representa uma posi��o v�lida no vetor de elementos.
 */

bool Group::isValidIndex(int n){
    return n >= 0 && n < (int)elements.size();
}

/* Fun��o neutralElement
 * Retorna o elemento neutro do grupo.
 * Caso n�o haja elemento neutro, retorna um elemento inv�lido com o caractere '\0'.
 */

Element Group::neutralElement()
{
    if (isValidIndex(neutralElementIndex)){
        return elements[neutralElementIndex];
    }
    else return Element(NULL, '\0');
}

/* Fun��o verifyAssociativity
 * Verifica se vale a propriedade da associatividade neste grupo para todas as possibilidades.
 * Tr�s loops para fazer a verifica��o.
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

/* Fun��o isNeutralElement
 * Verifica se o elemento de �ndice n � o elemento neutro.
 * Faz todos os testes de opera��es para verificar as propriedades do elemento neutro.
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

/* Fun��o isNeutralElement
 * Verifica se o elemento parametrado � o elemento neutro.
 * Procura o �ndice do elemento no vetor e verifica se o �ndice � o do elemento neutro.
 * Poderia verificar se o elemento representa o caractere '1', mas
 * foi feito um grupo para todos os modelos de tabela.
 */

bool Group::isNeutralElement(Element element)
{
    int elementIndex = findIndexOf(element.carac);
	return isNeutralElement(elementIndex);
}

/* Fun��o inverse
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

/* Fun��o isClosed
 * Verifica se a opera��o � fechada para o grupo.
 * Executa todas as possibilidades de opera��o e procura o elemento resultante no grupo.
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

/* Fun��o findNeutralElementIndex
 * Procura pelo elemento neutro do grupo.
 * Testa a propriedade do elemento neutro para todos os elementos.
 * Poderia simplesmente procurar pelo elemento com o caractere '1',
 * mas foi feito um grupo para tipo gen�rico de elemento neutro.
 * Retorna -1 caso n�o ache.
 */

int Group::findNeutralElementIndex()
{
	for (int i = 0; i < (int)elements.size(); i++) {
		if (isNeutralElement(i)) return i;
	}
	return -1;
}

/* Fun��o inverseElementOf
 * Procura pelo elemento inverso do que est� no �ndice n.
 * Procura por todos os elementos e faz o teste de inversibilidade.
 * Retorna -1 caso n�o ache.
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

/* Fun��o isValidGroup
 * Verifica se o grupo � v�lido.
 * Verifica a propriedade da associatividade, do elemento neutro e do elemento inverso.
 */

bool Group::isValidGroup()
{
    return isClosed() && inverse() && verifyAssociativity();
}

/* Fun��o generateSubgroups
 * Gera todos os subgrupos do grupo atual e retorna uma lista com eles.
 * Inicializa os vetores de presen�a no backtrack e as pulhas auxiliares.
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

/* Fun��o clearStack
 * Esvazia uma pilha recebendo uma refer�ncia pra ela.
 */

bool Group::clearStack(stack<int> & stck){
    while(!stck.empty()) stck.pop();
    return true;
}

/* Fun��o backTrack
 * Executa o algoritmo de backTrack para o n-�simo elemento.
 * Caso n seja o final, monta o grupo, verifica a validade dele e adiciona na lista.
 * Caso ele j� tenha sido marcado como presente ou ausente, prossegue.
 * Sup�e que o elemento n�o est� e prossegue.
 * Sup�e que o elemento est� e utiliza DFS para procurar pelos elementos que tamb�m deve estar
 * segundo os elementos que j� est�o e segundo o que acabou de adicionado.
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
                    printf("Erro, opera��o n�o fechada\n");
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
                    printf("Erro, opera��o n�o fechada\n");
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

/* Fun��o findIndexOf
 * Executa busca bin�ria para achar o �ndice de um elemento no vetor de elementos.
 * Caso n�o ache, retorna -1.
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

/* Fun��o toString
 * Pega todos os elementos e concatena seus caracteres em uma string.
 */

string Group::toString(){
    string name;
    for(int i = 0; i < (int)elements.size(); i++){
        name.push_back(elements[i].carac);
    }
    return name;
}

/* Fun��o ~Group
 * Destrutor da classe Group.
 */

Group::~Group()
{
    //dtor
}
