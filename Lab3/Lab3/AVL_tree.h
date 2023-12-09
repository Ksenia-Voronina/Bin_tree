#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right; 
};

unsigned char height(node* p)
{
	if (p == nullptr) 
		return 0;
	else {
		int leftHeight = height(p->left);
		int rightHeight = height(p->right);

		if (leftHeight > rightHeight) return leftHeight + 1;
		else return rightHeight + 1;
	}
}

int balance_factor(node* p)
{
	return height(p->right) - height(p->left);
}

void fix_height(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

class bin_tree {
public:
	bin_tree(); // конструктор по умолчанию

	void print(node* current = nullptr); // вывод дерева

private:
	node* root;
	size_t size;
	size_t levels;

	node* rotate_left(node* p);

	node* rotate_right(node* p);

	node* balance(node* p);

	node* insert(node* p, const int& k);

	node* find_min(node* p); // поиск минимального узла в дереве p

	node* remove_min(node* p); // удаление узла с минимальным ключом из дерева p

	node* remove_key(node* p, const int& k); // удаление узла по ключу

	node* find(node* p, const int& elem);

};

bin_tree::bin_tree() {
	root = nullptr;
	size = 0;
	levels = 0;
}

node* bin_tree::rotate_left(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

node* bin_tree::rotate_right(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

node* bin_tree::balance(node* p) // балансировка узла p
{
	fix_height(p);
	if (balance_factor(p) == 2)
	{
		if (balance_factor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if (balance_factor(p) == -2)
	{
		if (balance_factor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p; // балансировка не нужна
}

node* bin_tree::insert(node* p, const int& k) // вставка ключа k в дерево с корнем p
{
	if (!p) 
		return new node();
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* bin_tree::find_min(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? find_min(p->left) : p;
}

node* bin_tree::remove_min(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = remove_min(p->left);
	return balance(p);
}

node* bin_tree::remove_key(node* p, const int& k) // удаление ключа k из дерева p
{
	if (!p) 
		return 0;
	if (k < p->key)
		p->left = remove_key(p->left, k);
	else if (k > p->key)
		p->right = remove_key(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

node* bin_tree::find(node* p, const int& elem) {
	if (p == nullptr) {
		return nullptr;
	}
	else if (p->key < elem) {
		return find(p->right, elem);
	}
	else if (p->key > elem) {
		return find(p->left, elem);
	}
	else {
		return p;
	}
}

void bin_tree::print(node* current) {
	if (current != nullptr) {
		cout << current->key << ' ';
		print(current->left);
		print(current->right);
	}
}