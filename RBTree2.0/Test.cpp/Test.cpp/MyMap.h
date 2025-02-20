#pragma once


#include "RBTree.h"

namespace myspace
{
	template<class K,class T>
	class map
	{
	private:
		RBTree<K, pair<K, T>> _t; 
	};
}


