#pragma once

#include <iostream>

class CVetv
{
public:
	int key;
	int inf;
	CVetv *l, *r;
	CVetv(int n, int key);
};

class CTree
{
private:
	char * name;
	int n;
	CVetv *root;

public:
	CTree(const char* n_name, int n_n, int n_key);
	CTree(const char* fn, const char* n_name);
	~CTree();
	CVetv* add(int i, int n_key);
	void del_vet(CVetv* dr);
	void view(CVetv* t, int lv);
	void view_all();
	CVetv* find(int fnd);
	CVetv* find(int fnd, CVetv* dr);
	int odd_cnt(CVetv* t);
	int odd_cnt();
	int r_key(CVetv* dr);
	int l_key(CVetv* dr);
	CVetv* find_key(int key, CVetv* dr);
	CVetv* find_key();
}; 