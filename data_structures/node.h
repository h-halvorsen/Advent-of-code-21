#pragma once

namespace custl //CUStom Template Library
{
	template<typename generic>
	struct node{
		generic data = NULL;
		node* next = NULL;
	};
}