#ifndef _LINEHASH_H_
#define _LINEHASH_H_

#include <iostream>
#include <vector>

	template <class T >
	class LineHash
	{
	private:
		vector<T> hashtab;
		vector<bool> inuse;
		int(*HashFunc)(T t);
	public:
		LineHash(int n):hashtab(n),inuse(n,false),HashFunc = nullptr;
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
			while (inuse[h]) { ++h; ++count; }
			hashtab[h] = e;
			inuse[h] = true;
			std::cout << "³åÍ»!Î»ÒÆ£º" << count << endl;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e);
			while (h < hashtab)
			{
				if (hashtab[h] == T)
					return &(hashtab[h]);
				h++;
			}
			return NULL;
		}
		T &opreator[](int n)
		{
			return hashtab[n];
		}
	};

#endif