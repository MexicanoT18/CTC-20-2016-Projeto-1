#include "Group.h"
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

Group::Group(const vector<Element> &arr)
{
    elements = arr;
    sort(elements.begin(), elements.end());

    table = arr[0].table;

    neutralElementIndex = findNeutralElementIndex();
}

Group::Group(const vector<char> &arr, Table * t)
{
    for(int i=0; i<(int)arr.size(); i++){
        elements.push_back(Element(t, arr[i]));
    }
    sort(elements.begin(), elements.end());

    table = t;

    neutralElementIndex = findNeutralElementIndex();
}

bool Group::belongsTo(Group & other){
    int otherIndex;
    for(int i=0; i<(int)elements.size(); i++){
        otherIndex = other.findIndexOf(elements[i].carac);
        if (!other.isValidIndex(otherIndex)) return false;
    }
    return true;
}

bool Group::isValidIndex(int n){
    return n >= 0 && n < (int)elements.size();
}

Element Group::neutralElement()
{
    if (isValidIndex(neutralElementIndex)){
        return elements[neutralElementIndex];
    }
    else return Element(NULL, '\0');
}

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

bool Group::isNeutralElement(int n)
{
    if (!isValidIndex(n)) return false;
    for(int i=0; i<(int)elements.size(); i++){
        if ((elements[n]*elements[i]) != elements[i] || (elements[i]*elements[n]) != elements[i])
            return false;
    }
	return true;
}

bool Group::isNeutralElement(Element element)
{
    int elementIndex = findIndexOf(element.carac);
	return isNeutralElement(elementIndex);
}

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

int Group::findNeutralElementIndex()
{
	for (int i = 0; i < (int)elements.size(); i++) {
		if (isNeutralElement(i)) return i;
	}
	return -1; //Não existe elemento neutro
}

int Group::inverseElementOf(int n)
{
	if (!isValidIndex(n)) return -1;
	Element searchElement = elements[n];
	for (int i = 0; i < (int)elements.size(); i++){
		if (isNeutralElement(elements[i] + searchElement)){
			return i;
		}
	}
	return -1;//Elemento não encontrado
}

bool Group::isValidGroup()
{
    return isClosed() && inverse() && verifyAssociativity();
}

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

    backTrack(ans, 0);

    return ans;
}

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

    stack<int> toRemove;
    stack<int> dfs;
    isPresent[n]=1;
    toRemove.push(n);
    dfs.push(n);

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

string Group::toString(){
    string name;
    for(int i = 0; i < (int)elements.size(); i++){
        name.push_back(elements[i].carac);
    }
    return name;
}

Group::~Group()
{
    //dtor
}
