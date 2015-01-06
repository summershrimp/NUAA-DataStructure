#ifndef _LINEHASH_H_
#define _LINEHASH_H_

#include <iostream>
#include <vector>

	template <class T >
	class LineHash
	{
	private:
		std::vector<T> hashtab;
		std::vector<bool> inuse;
		int(*HashFunc)(T t,int n);
		int size;
	public:
		LineHash(int n) :size(n), hashtab(n), inuse(n, false), HashFunc(nullptr){};
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
			int th = h;
			do
			{
				if (inuse[h])
				{
					++h; ++count;
					if (h == size)
						h %= size;
				}
				else break;
			} while (th != h);

			if (h == size)
			{
				std::cout << "±íÂú£¡Ê§°Ü" << endl;
				return -1;
			}
			hashtab[h] = e;
			inuse[h] = true;
			if (count>0)std::cout << "³åÍ»!Î»ÒÆ£º" << count << endl;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return NULL;
			int h = HashFunc(e,size);
			int th = h;
			do
			{
				if (hashtab[h] == e)
					return &(hashtab[h]);
				h++;
				if (h == size)
					h %= size;
			} while (th!=h);
			return NULL;
		}
		T &operator[](int n)
		{
			return hashtab[n];
		}
	};

#endif