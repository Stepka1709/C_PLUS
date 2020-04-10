#include "CTree.h"
#include <math.h>

void CTree::view_all()
{
	view(root, 0);
}

CTree::CTree(const char* n_name, int n_n, int n_key)
{
	CVetv * t = new CVetv(n_n, n_key);
	root = t;
}

CTree::CTree(const char* fn, const char* n_name)
{
	FILE * f;
	fopen_s(&f, fn, "rt");
	if (!f)
	{
		printf("file not found");
		return;
	}
	char ts[255] = "";
	fgets(ts, 255, f);
	int inkey, ininf;
	sscanf_s(ts, "%i %i", &inkey, &ininf);
	CVetv * t = new CVetv(ininf, inkey);

	root = t;

	while (fgets(ts, 255, f)) {
		sscanf_s(ts, "%i %i", &inkey, &ininf);
		add(ininf, inkey);
	}
	fclose(f);
}

CVetv* CTree::find(int fnd)
{
	return find(fnd, root);
}

CVetv* CTree::find(int fnd, CVetv* dr) 
{
	if (!dr) return NULL;
	if (dr->key == fnd) return dr;
	if (dr->key > fnd) return find(fnd, dr->l);
	else if (dr->key < fnd) return find(fnd, dr->r);
	else return NULL;
}

CVetv* CTree::add(int n_inf, int n_key)
{
	int	find = 0;
	CVetv *	prev = NULL;

	CVetv * t = root;				
	while (t && !find) {
		prev = t;
		if (n_key == t->key)
			find = 1;	 
		else
			if (n_key < t->key) t = t->l;
			else   t = t->r;
	}

	if (!find) {					
		t = new CVetv(n_inf, n_key);				
		if (n_key < prev->key)		
			prev->l = t;	
		else    prev->r = t;		
		return t;
	}
	else
		return NULL;
}

CVetv::CVetv(int inf, int key)
{
	this->inf = inf;
	this->key = key;
	l = r = NULL;
}

void CTree::view(CVetv* t, int lv)
{
	if (t) {
		view(t->r, lv + 1);		
		for (int i = 0; i < lv; i++)  printf("    ");
		printf(" %i\n", t->key);
		view(t->l, lv + 1); 		
	}
}

CTree::~CTree()
{
	del_vet(root->r);
	del_vet(root->l);
	delete root;
}

// нет удаления (нужна ссылка на предка которого мы удаляем)
void CTree::del_vet(CVetv* dr)
{
	if (dr) {
		del_vet(dr->r); dr->r = NULL;
		del_vet(dr->l); dr->l = NULL;
	}
}

int CTree::odd_cnt(CVetv* t)
{
	int c = 0;
	if (t) {
		c += odd_cnt(t->r);		
		if (fmod(t->key, 2) == 0) c++;
		c += odd_cnt(t->l); 		
	}
	return c;
}

int CTree::odd_cnt()
{
	return odd_cnt(root);
}

/* поиск максимального ключа */
int CTree::r_key(CVetv* dr) {
	if (dr) {
		if (dr->r == NULL) return dr->key; // если правый узел равный нулю, то он максимальный, возвращаем ключ
		else return r_key(dr->r); // иначе идём право
	}
	else return NULL;
}

/* поиск минимального ключа */
int CTree::l_key(CVetv* dr) {
	if (dr) {
		if (dr->l == NULL) return dr->key; // если левый узел равный нулю, то он минимальный, возвращаем ключ
		else return l_key(dr->l); // иначё идём влево
	}
	else return NULL;
}

CVetv* CTree::find_key(int key, CVetv* dr) {
	if (!dr) return NULL; // если узла не существует, то возвращаем ноль
	if (dr->key == key) return dr; // если нашли ключ равный указателю key (среднему ключу), то возвращаем указатель dr
	if (dr->key > key && dr->l->key > key) return find_key(key, dr->l); // если ключ больше указателя key и его левый узел тоже, то идём на лево 
	else if (dr->key > key && dr->l->key < key) return dr; // если ключ больше указателя key и его левый узел меньше указателя key, то возвращаем указатель dr
	if (dr->key < key && dr->r->key > key) return find_key(key, dr->r); // если ключ меньше указателя key и его правый узел больше указателя key, то идём право
	else if (dr->key < key && dr->r->key < key) return dr; // если ключ ключ больше указателя key и его правый узел меньше указателя key, то возвращаем указатель dr
	else return NULL; // если ниодно условие не сработало, возвращаем ноль
}

/* метод который начинает поиск с корня дерева */
CVetv* CTree::find_key() {
	return find_key(((r_key(root) + l_key(root)) / 2), root); // вызываем метод для поиска минимального и максимального ключа, затем делим на два
}
