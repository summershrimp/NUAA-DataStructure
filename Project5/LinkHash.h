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
		vector<hash_node*> hashtab;
		int(*HashFunc)(T t);
	public:
		LinkHash(int n) :hashtab(n,nullptr), HashFunc = nullptr;
		void setHashFunc(int(*hashfunc)(T t))
		{
			HashFunc = hashfunc;
		}
		int add(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e);
			int count = 0;
			hash_node *no = new hash_node;
			if (hashtab[h]!=nullptr)
				std::cout << "³åÍ»!²åÈë" << h << endl;
			no->next = hashtab[n];
			hashtab[n] = no;
			no->e = e;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e);
			hash_node *p = hashtab[h];
			while (h)
			{
				if (h->e == T)
					return &(h->e);
				h = h->next;
			}
			return NULL;
		}
		T &opreator[](int n)
		{
			return hashtab[n];
		}
	};


#endif