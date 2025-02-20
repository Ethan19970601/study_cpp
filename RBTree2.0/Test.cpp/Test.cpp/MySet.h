#pragma once

#include "RBTree.h"

namespace myspace
{
	template<class K>
	class set
	{
	private:
		RBTree<K, K> _t;
	};
}



