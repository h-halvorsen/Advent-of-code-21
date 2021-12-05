#pragma once

//#define DEBUG_ENABLED


#define log(x) std::cout<<x<<std::endl;			//TEMPORARY!!! Replace with log class;


#include <stdint.h>
#include <iostream>
#include <string>
#include "node.h"


namespace custl {

	template<typename generic>
	class linkedlist
	{
		node<generic> dummy;				//Dummy node is always first node and makes things like insertion and deletion easier
		node<generic> *head = NULL;
		node<generic> *back = &dummy;

		uint32_t size = 0;
		
	private:

		/*		Unused (for now)
		void update_back() 
		{
			head = &dummy;
			while (head->next != NULL)
			{
				head = head->next;
			}
			back = head;
		}
		*/

		node<generic>* search(uint32_t idx) 
		{

			if (idx >= size)
			{
				log("ERROR! Search failed: Index out of bounds");
				return &dummy;
			}
			else if (idx == size-1)
			{
				return back;
			}

			head = dummy.next;

			for (int i = 0; i < idx; i++)
			{
				head = head->next;
			}

			return head;
		}
		
	public:
		

		generic operator[](uint32_t idx)
		{

			head = search(idx);
			if (head == &dummy)
			{
				return NULL;
			}

			return head->data;
		}

		uint32_t length() 
		{
			return size;
		}

		void append(generic val) 
		{
			back->next = new node<generic>{ val };
			back = back->next;
			size++;
		}
		
		void prepend(generic val) 
		{
			dummy.next = new node<generic>{val, dummy.next};
			size++;
		}
		
		void insert(uint32_t idx, generic data)
		{
			if (idx > size)
			{
				log("ERROR: Could not insert " << data << " at index " << idx << ". Index out of bounds");
				return;
			}

			head = search(idx-1);

			head->next = new node<generic>{ data, head->next };
			back = idx == size ? head->next : back;

			size++;
		}
		
		void swapRandom(uint32_t idxA, uint32_t idxB) 
		{
			node<generic>* nodeAPrev = search(idxA-1);
			node<generic>* nodeBPrev = search(idxB-1);
			node<generic>* nodeA = nodeAPrev->next;
			node<generic>* nodeB = nodeBPrev->next;
			node<generic>* temp = nodeA->next;
			nodeAPrev->next = nodeB;
			nodeBPrev->next = nodeA;
			nodeA->next = nodeB->next;
			nodeB->next = temp->next;


		}

		void swapNext(uint32_t idx)
		{
			head = search(idx-1);
			node<generic>* nodeA = head->next;
			node<generic>* nodeB = nodeA->next;
			nodeA->next = nodeB->next;
			nodeB->next = nodeA;
			head->next = nodeB;
		}

		void traverse() 
		{
			size = 0;
			head = dummy.next;
			if (head == NULL) return;
			std::cout << head->data;
			head = head->next;
			size++;
			while (true)
			{
	
				std::cout << "-->" << head->data;
				
				if (head == back) break;
				head = head->next;
				size++;
			}
			std::cout << std::endl << std::endl << std::endl;
		}

		void pop()  
		{
			head = dummy.next;
			head->data = NULL;
			dummy.next = head->next;
			delete head;
			size--;
		}

		void pop_back()
		{
			back = search(size - 2);
			head = back->next;

			back->next = NULL;

			head->data = NULL;
			delete head;
	
			size--;
		}

		void remove(uint32_t idx)
		{
			if (idx + 1 == size)
			{
				pop_back();
				return;
			}

			head = search(idx-1);
			node<generic>* deadNode = head->next;

			head->next = deadNode->next;

			delete deadNode;

			size--;
		}

		void sort()
		{

			uint32_t swapCount;

			do
			{
				static int j = size - 2;

				swapCount = 0;

				for (int i = 0; i < j; i++)
				{
					head = search(i);

						if (head->data > head->next->data)
					{
							swapNext(i);
							swapCount++;
					}
				}
				j--;
			} while (swapCount > 0);
		}

		~linkedlist()
		{
			while (true)
			{
				head = dummy.next;
				if (head == NULL) break;
				pop();
			}
		}
	};
	

}
