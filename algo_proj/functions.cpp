

#include "functions.h"
using namespace std;

template <class T>
void insert(T x, list<T> &l, int i)
{
	typename list<T>::iterator list_iter = l.begin();
	for (int j = 0; j < i; j++) {
		list_iter++;
	}
	l.insert(list_iter, x);
	
	return;
}

template <class T>
T index(list<T> &l, int i)
{
	typename list<T>::iterator list_iter = l.begin();
	for (int j = 0; j < i; j++) {
		list_iter++;
	}
	
	return *list_iter;
}
