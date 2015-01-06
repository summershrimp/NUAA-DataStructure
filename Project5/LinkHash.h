#ifndef _LINKHASH_H_
#define _LINKHASH_H_
#include <iostream>
#include <vector>
	template <class T>
	struct hash_node
	{
		T e;
		hash_node *next = nullptr;
	};

	template <class T >
	class LinkHash
	{
	private:
		std::vector<hash_node<T>*> hashtab;
		int(*HashFunc)(T t,int n);
		int size;
	public:
		LinkHash(int n) :size(n), hashtab(n, nullptr), HashFunc(nullptr){};
		void setHashFunc(int(*hashfunc)(T t,int n))
		{
			HashFunc = hashfunc;
		}
		int add(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e,size);
			int count = 0;
			hash_node<T> *no = new hash_node<T>;
			if (hashtab[h]!=nullptr)
				std::cout << "³åÍ»!²åÈë" << h << endl;
			no->next = hashtab[h];
			hashtab[h] = no;
			no->e = e;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return NULL;
			int h = HashFunc(e,size);
			hash_node<T> *p = hashtab[h];
			while (p)
			{
				if (p->e == e)
					return &(p->e);
				p = p->next;
			}
			return NULL;
		}
		T &operator[](int n)
		{
			return hashtab[n];
		}
	};


#endif