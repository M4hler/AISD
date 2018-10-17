/*
*	Oskar Makowski
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <functional> //template for hash function
#define HMAP_SIZE 128
#define LIST_CHANGE 90
using namespace std;

class Node //basic node
{
	public:
		string key;
		Node * left;
		Node * right;
		Node * parent;

		Node()
		{
			key = "";
			left = NULL;
			right = NULL;
			parent = NULL;
		}

		void setKey(string s) //setters
		{
			key = s;
		}

		void setLeft(Node * node)
		{
			left = node;
		}

		void setRight(Node * node)
		{
			right = node;
		}

		void setParent(Node * node)
		{
			parent = node;
		}
};

class BST //Binary Search Tree class
{
	public:
		Node * root; //pointer to root, to get access to the 'top' of the tree from the instantion of class
		int insert_counter;
		int delete_counter;
		int search_counter;
		int min_counter;
		int max_counter;
		int succesor_counter;
		int inOrder_counter;
		int max_fill;
		int number_of_el;

		BST()
		{
			root = NULL;
			insert_counter = 0;
			delete_counter = 0;
			search_counter = 0;
			min_counter = 0;
			max_counter = 0;
			succesor_counter = 0;
			inOrder_counter = 0;
			max_fill = 0;
			number_of_el = 0;
		}
		
		Node * insert(string word)
		{
			insert_counter++;
			number_of_el++;

			if(number_of_el > max_fill)
				max_fill = number_of_el;

			Node * newNode = new Node(); //create new node
			newNode -> setKey(word);
			newNode -> setParent(NULL);
			newNode -> setLeft(NULL);
			newNode -> setRight(NULL);
			if(root == NULL) //if tree is empty, set root to new node
			{
				root = newNode;
			}
			else //if tree isn't empty, find place to put new node
			{
				Node * prev = NULL; //used to set parent
				Node * curr = root;

				while(curr != NULL)
				{
					prev = curr;

					if(newNode -> key < curr -> key)
						curr = curr -> left;
					else
						curr = curr -> right;
				}

				newNode -> setParent(prev);

				if(newNode -> key < prev -> key) //check which child new node is
					prev -> left = newNode;
				else
					prev -> right = newNode;
			}
			return newNode;
		}

		void inOrderWalk(Node * node) //recursive in order walk
		{
			if(node != NULL)
			{
				inOrderWalk(node -> left);
				cout << node -> key << " ";
				inOrderWalk(node -> right);
			}
		}

		Node * search(Node * node, string pattern)
		{
			search_counter++;

			if(node == NULL) //empty tree
			{
				return NULL;
			}
			else if(pattern == node -> key) //found correct node
			{
				return node;
			}
			else if(pattern < node -> key) //recursive calls based on BST properties
				return search(node -> left, pattern);
			else
				return search(node -> right, pattern);
		}

		Node * min(Node * node) //go 'left' as much as possible
		{
			min_counter++;

			if(node == NULL)
			{
				return NULL;
			}
			else
			{
				while(node -> left != NULL)
				{
					node = node -> left;
				}
				return node;
			}
		}

		Node * max(Node * node) //go 'right' as much as possible
		{
			max_counter++;

			if(node == NULL)
			{
				return NULL;
			}
			else
			{
				while(node -> right != NULL)
				{
					node = node -> right;
				}
				return node;
			}
		}

		Node * succesor(string s) //succesor is used during deleting from tree
		{
			succesor_counter++;

			Node * node = search(root, s);

			if(node == NULL)
			{
				return NULL;
			}

			if(node -> right != NULL)
			{
				Node * y = min(node -> right); //minimum element from right subtree is next element in in-order 
				return y;
			}

			Node * y = node -> parent; //if there is no right sub-tree, succesor is somewhere 'higher'
			while(y != NULL && node == y -> right)
			{
				node = y;
				y = y -> parent;
			}
			
			return y;
		}

		void del(string s)
		{
			delete_counter++;

			if(root == NULL)
			{
				return;
			}

			Node * node = search(root, s);

			if(node == NULL)
			{
				return;
			}

			number_of_el--;

			if(node -> left == NULL)
				transplant(node, node -> right); //transplant one of the subtrees to place of the node
			else if(node -> right == NULL)
				transplant (node, node -> left);
			else
			{
				Node * y = min(node -> right);
				if(y -> parent != node)
				{
					transplant(y, y -> right);
					y -> right = node -> right;
					y -> right -> parent = y;
				}

				transplant(node, y);
				y -> left = node -> left;
				y -> left -> parent = y;
			}
		}

		void transplant(Node * node_to_replace, Node * new_node) //switch pointers to move subtrees
		{
			if(node_to_replace -> parent == NULL)
				root = new_node;
			else if(node_to_replace == node_to_replace -> parent -> left)
				node_to_replace -> parent -> left = new_node;
			else
				node_to_replace -> parent -> right = new_node;

			if(new_node != NULL)
				new_node -> parent = node_to_replace -> parent;
		}
};

class RBNode
{
	public:
		int color; //0 - black, 1 - red
		string key;
		RBNode * left;
		RBNode * right;
		RBNode * parent;

		void setColor(int node_color)
		{
			color = node_color;
		}

		void setKey(string s)
		{
			key = s;
		}

		void setLeft(RBNode * node)
		{
			left = node;
		}

		void setRight(RBNode * node)
		{
			right = node;
		}

		void setParent(RBNode * node)
		{
			parent = node;
		}
};

class RBT
{
	public:
		RBNode * root;
		int insert_counter;
		int delete_counter;
		int search_counter;
		int min_counter;
		int max_counter;
		int succesor_counter;
		int inOrder_counter;
		int max_fill;
		int number_of_el;

		RBT()
		{
			root = NULL;
			insert_counter = 0;
			delete_counter = 0;
			search_counter = 0;
			min_counter = 0;
			max_counter = 0;
			succesor_counter = 0;
			inOrder_counter = 0;
			max_fill = 0;
			number_of_el = 0;
		}

		void leftRotate(RBNode * node)
		{
			RBNode * y = (RBNode *)node -> right;
			node -> right = y -> left;

			if(y -> left != NULL)
				y -> left -> parent = node;

			y -> parent = node -> parent;

			if(node -> parent == NULL)
			{
				root = y;
			}
			else if(node == node -> parent -> left)
			{
				node -> parent -> left = y;
			}
			else
				node -> parent -> right = y;

			y -> left = node;
			node -> parent = y;
		}

		void rightRotate(RBNode * node)
		{
			RBNode * y = (RBNode *)node -> left;
			node -> left = y -> right;

			if(y -> right != NULL)
				y -> right -> parent = node;

			y -> parent = node -> parent;

			if(node -> parent == NULL)
			{
				root = y;
			}
			else if(node == node -> parent -> right)
			{
				node -> parent -> right = y;
			}
			else
				node -> parent -> left = y;

			y -> right = node;
			node -> parent = y;
		}

		RBNode * insert2(string word)
		{
			insert_counter++;
			number_of_el++;

			if(number_of_el > max_fill)
				max_fill = number_of_el;

			RBNode * newNode = new RBNode();
			newNode -> setKey(word);
			newNode -> setParent(NULL);
			newNode -> setLeft(NULL);
			newNode -> setRight(NULL);
			if(root == NULL)
			{
				root = newNode;
			}
			else
			{
				RBNode * prev = NULL;
				RBNode * curr = root;

				while(curr != NULL)
				{
					prev = curr;

					if(newNode -> key < curr -> key)
						curr = curr -> left;
					else
						curr = curr -> right;
				}

				newNode -> setParent(prev);

				if(newNode -> key < prev -> key)
					prev -> left = newNode;
				else
					prev -> right = newNode;
			}
			return newNode;
		}

		void insert(string word)
		{
			RBNode * newNode = (RBNode *)insert2(word);
			newNode -> setColor(1);

			while(newNode != root && ((RBNode *)newNode -> parent) -> color == 1)
			{
				if(newNode -> parent == newNode -> parent -> parent -> left)
				{
					RBNode * y = (RBNode *)newNode -> parent -> parent -> right;
					
					if(y -> color == 1)
					{
						((RBNode *)newNode -> parent) -> setColor(0);
						y -> setColor(0);
						((RBNode *)newNode -> parent -> parent) -> setColor(1);
						newNode = ((RBNode *)newNode -> parent -> parent);
					}
					else 
					{
						if(newNode == newNode -> parent -> right)
						{
							newNode = ((RBNode *)newNode -> parent);
							leftRotate(newNode);
						}

						((RBNode *)newNode -> parent) -> setColor(0);
						((RBNode *)newNode -> parent -> parent) -> setColor(1);
						rightRotate(((RBNode *)newNode -> parent -> parent));
					}
				}
				else
				{
					RBNode * y = (RBNode *)newNode -> parent -> parent -> left;
					
					if(y -> color == 1)
					{
						((RBNode *)newNode -> parent) -> setColor(0);
						y -> setColor(0);
						((RBNode *)newNode -> parent -> parent) -> setColor(1);
						newNode = ((RBNode *)newNode -> parent -> parent);
					}
					else 
					{
						if(newNode == newNode -> parent -> left)
						{
							newNode = ((RBNode *)newNode -> parent);
							leftRotate(newNode);
						}

						((RBNode *)newNode -> parent) -> setColor(0);
						((RBNode *)newNode -> parent -> parent) -> setColor(1);
						rightRotate(((RBNode *)newNode -> parent -> parent));
					}
				}
			}

			((RBNode *)root) -> setColor(0);
		}

		void rbTransplant(RBNode * node_to_replace, RBNode * new_node)
		{
			if(node_to_replace -> parent == NULL)
				root = new_node;
			else if(node_to_replace == node_to_replace -> parent -> left)
				node_to_replace -> parent -> left = new_node;
			else
				node_to_replace -> parent -> right = new_node;

			new_node -> parent = node_to_replace -> parent;
		}

		void del(string s)
		{
			delete_counter++;

			if(root == NULL)
			{
				return;
			}

			RBNode * node = (RBNode *)search(root, s);

			if(node == NULL)
			{
				return;
			}

			RBNode * y = node;
			RBNode * x = NULL;
			int y_original_color = y -> color;

			if(node -> left == NULL)
			{
				x = ((RBNode *)node -> right);
				rbTransplant(node, ((RBNode *)node -> right));
			}
			else if(node -> right == NULL)
			{
				x = ((RBNode *)node -> left);
				rbTransplant(node, ((RBNode *)node -> left));
			}
			else
			{
				y = (RBNode *)min(((RBNode *)node -> right));
				y_original_color = y -> color;
				x = ((RBNode *)y -> right);

				if(y -> parent == node)
				{
					x -> parent = y;
				}
				else
				{
					rbTransplant(y, ((RBNode *)y -> right));
					y -> right = node -> right;
					y -> right -> parent = y;
				}

				rbTransplant(node, y);
				y -> left = node -> left;
				y -> left -> parent = y;
				y -> color = node -> color;
			}

			if(y_original_color == 0)
				rbDelFixup(x);
		}

		void rbDelFixup(RBNode * node)
		{
			while(node != root && node -> color == 0)
			{
				if(node == ((RBNode *)node -> parent -> left))
				{
					RBNode * w = ((RBNode *)node -> parent -> right);

					if(w -> color == 1)
					{
						w -> setColor(0);
						((RBNode *)node -> parent) -> setColor(1);
						leftRotate(((RBNode *)node -> parent));
						w = ((RBNode *)node -> parent -> right);
					}
					if(((RBNode *)w -> left) -> color == 1 && ((RBNode *)w -> right) -> color == 1)
					{
						w -> setColor(1);
						node = ((RBNode *)node -> parent);
					}
					else
					{
						if(((RBNode *)w -> right) -> color == 0)
						{
							((RBNode *)w -> left) -> setColor(0);
							w -> setColor(1);
							rightRotate(w);
							w = ((RBNode *)node -> parent -> right);
						}

						w -> setColor(((RBNode *)node -> parent) -> color);
						((RBNode *)node -> parent) -> setColor(0);
						((RBNode *)w -> right) -> setColor(0);
						leftRotate(((RBNode *)node -> parent));
						node = (RBNode *)root;
					}
				}
				else
				{
					RBNode * w = ((RBNode *)node -> parent -> left);

					if(w -> color == 1)
					{
						w -> setColor(0);
						((RBNode *)node -> parent) -> setColor(1);
						leftRotate(((RBNode *)node -> parent));
						w = ((RBNode *)node -> parent -> left);
					}
					if(((RBNode *)w -> right) -> color == 1 && ((RBNode *)w -> left) -> color == 1)
					{
						w -> setColor(1);
						node = ((RBNode *)node -> parent);
					}
					else
					{
						if(((RBNode *)w -> left) -> color == 0)
						{
							((RBNode *)w -> right) -> setColor(0);
							w -> setColor(1);
							rightRotate(w);
							w = ((RBNode *)node -> parent -> left);
						}

						w -> setColor(((RBNode *)node -> parent) -> color);
						((RBNode *)node -> parent) -> setColor(0);
						((RBNode *)w -> left) -> setColor(0);
						leftRotate(((RBNode *)node -> parent));
						node = (RBNode *)root;
					}
				}
			}
			node -> setColor(0);
		}

		void inOrderWalk(RBNode * node)
		{
			if(node != NULL)
			{
				inOrderWalk(node -> left);
				cout << node -> key << " ";
				inOrderWalk(node -> right);
			}
		}

		RBNode * search(RBNode * node, string pattern)
		{
			search_counter++;

			if(node == NULL)
			{
				return NULL;
			}
			else if(pattern == node -> key)
			{
				return node;
			}
			else if(pattern < node -> key)
				return search(node -> left, pattern);
			else
				return search(node -> right, pattern);
		}

		RBNode * min(RBNode * node)
		{
			min_counter++;

			if(node == NULL)
			{
				return NULL;
			}
			else
			{
				while(node -> left != NULL)
				{
					node = node -> left;
				}
				return node;
			}
		}

		RBNode * max(RBNode * node)
		{
			max_counter++;

			if(node == NULL)
			{
				return NULL;
			}
			else
			{
				while(node -> right != NULL)
				{
					node = node -> right;
				}
				return node;
			}
		}

		RBNode * succesor(string s)
		{
			succesor_counter++;

			RBNode * node = search(root, s);

			if(node == NULL)
			{
				return NULL;
			}

			if(node -> right != NULL)
			{
				RBNode * y = min(node -> right);
				return y;
			}

			RBNode * y = node -> parent;
			while(y != NULL && node == y -> right)
			{
				node = y;
				y = y -> parent;
			}
			
			return y;
		}
};

class ListNode
{
	public:
		string key;
		struct ListNode * next;
};

class SingleLinkedList
{
	public:
		ListNode * root;

		SingleLinkedList()
		{
			root = NULL;
		}

		void insert(string value)
		{
			if(root == NULL)
			{	
				ListNode * new_node = new ListNode;

				new_node -> key = value;
				new_node -> next = NULL;

				root = new_node;
			}
			else
			{
				ListNode * new_node = new ListNode;

				new_node -> key = value;
				new_node -> next = NULL;

				ListNode * last = root;
				while(last -> next != NULL)
					last = last -> next;

				last -> next = new_node; 
			}
		}

		int search(ListNode * n, string value)
		{
			if(n == NULL)
			{
				return 0;
			}
			else if(n -> key == value)
				return 1;

			while(n -> next != NULL)
			{
				if(n -> key == value)
					return 1;

				n = n -> next;
			}
			return 0;
		}

		void del(string value)
		{
			if(root == NULL)
				return;
			else if(root -> next == NULL)
			{
				delete root;
				root = NULL;
			}
			else
			{
				ListNode * prev = root;
				ListNode * to_del = root -> next;

				while(to_del -> key != value && to_del -> next != NULL)
				{
					prev = to_del;
					to_del = to_del -> next;
				}

				if(to_del -> key == value)
				{
					if(to_del -> next == NULL)
					{
						delete(to_del);
						prev -> next == NULL;
					}
					else
					{
						prev -> next = to_del -> next;
						delete(to_del);
					}
				}
			}
		}
};

class HashNode
{
	public:
		RBT * rbt;
		SingleLinkedList * list;
		int elements;

		HashNode()
		{
			rbt = NULL;
			list = NULL;
			elements++;
		}
};

class HashTable
{
	public:
		HashNode * table;
		int insert_counter;
		int delete_counter;
		int search_counter;
		int min_counter;
		int max_counter;
		int succesor_counter;
		int inOrder_counter;
		int max_fill;
		int number_of_el;

		HashTable()
		{
			table = new HashNode[HMAP_SIZE];
			insert_counter = 0;
			delete_counter = 0;
			search_counter = 0;
			min_counter = 0;
			max_counter = 0;
			succesor_counter = 0;
			inOrder_counter = 0;
		}

		int hash_function(string value)
		{
			size_t str_hash = hash<string>{}(value);
			return str_hash % HMAP_SIZE;
		}

		void insert(string value)
		{
			insert_counter++;
			number_of_el++;

			if(number_of_el > max_fill)
				max_fill = number_of_el;

			int hash_value = hash_function(value);
			table[hash_value].elements++;

			if(table[hash_value].list == NULL && table[hash_value].rbt == NULL)
			{
				table[hash_value].list = new SingleLinkedList();
				table[hash_value].list -> insert(value);
			}
			else if(table[hash_value].list != NULL && table[hash_value].elements < LIST_CHANGE)
			{
				table[hash_value].list -> insert(value);
			}
			else if(table[hash_value].list != NULL && table[hash_value].elements >= LIST_CHANGE)
			{
				RBT * new_rbt = new RBT();
				while(table[hash_value].list -> root != NULL)
				{
					new_rbt -> insert(table[hash_value].list -> root -> key);
					table[hash_value].list -> del(table[hash_value].list -> root -> key);
				}
				table[hash_value].list == NULL;
				table[hash_value].rbt = new_rbt;
			}
			else
				table[hash_value].rbt -> insert(value);
		}

		int search(string value)
		{
			search_counter++;

			int hash_value = hash_function(value);
			if(table[hash_value].list != NULL)
			{
				if(table[hash_value].list == NULL)
					return 0;
				else
					return table[hash_value].list -> search(table[hash_value].list -> root, value);
			}
			else if(table[hash_value].rbt != NULL)
			{
				if(table[hash_value].rbt == NULL)
					return 0;
				else
				{
					RBNode * node = (RBNode *)(table[hash_value].rbt -> search(table[hash_value].rbt -> root, value));
					if(node == NULL)
						return 0;
					else
						return 1;
				}
			}
		}

		void del(string value)
		{
			delete_counter++;
			number_of_el--;

			int hash_value = hash_function(value);

			if(table[hash_value].list != NULL)
			{
				if(table[hash_value].list -> search(table[hash_value].list -> root, value) == 1)
				{
					table[hash_value].elements--;
					table[hash_value].list -> del(value);
				}
			}
			else if(table[hash_value].rbt != NULL)
			{
				RBNode * node = (RBNode *)(table[hash_value].rbt -> search(table[hash_value].rbt -> root, value));
				if(node != NULL)
				{
					table[hash_value].elements--;
					table[hash_value].rbt -> del(value);
				}
			}
		}

		void min()
		{
			min_counter++;
			cout << endl;
		}

		void max()
		{
			max_counter++;
			cout << endl;
		}

		void inOrderWalk()
		{
			inOrder_counter++;
			cout << endl;
		}

		void succesor()
		{
			succesor_counter++;
			cout << endl;
		}
};

int main(int argc, char * argv[])
{
	clock_t start = clock();

	if(strcmp(argv[1], "--type") != 0)
	{
		cout << "Second parameter is wrong" << endl;
		exit(0);
	}

	BST * tree = NULL;
	RBT * rbt = NULL;
	HashTable * hashTable = NULL;

	if(strcmp(argv[2], "bst") == 0)
		tree = new BST();
	else if(strcmp(argv[2], "rbt") == 0)
		rbt = new RBT();
	else if(strcmp(argv[2], "hmap") == 0)
		hashTable = new HashTable();
	else
	{
		cout << "There is no such a structure" << endl;
		exit(0);
	}

	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		string instruction;
		cin >> instruction;

		if(instruction == "insert")
		{
			string param;
			cin >> param;

			if(tree != NULL)
				tree -> insert(param);
			else if(rbt != NULL)
				rbt -> insert(param);
			else if(hashTable != NULL)
				hashTable -> insert(param);
		}
		else if(instruction == "load")
		{
			string param;
			cin >> param;

			fstream f;
			f.open(param.c_str(), ios::in);

			if(!f.good())
			{
				cout << "Access denied or file doesnt exist" << endl;
				continue;
			}

			while(!f.eof())
			{
				string word;
				f >> word;

				if(word.length() < 1)
					continue;
				if(word[0] < 65 || word[0] > 122)
					word = word.substr(1, word.length() - 1);
				if(word[word.length() - 1] < 65 || word[word.length() - 1] > 122)
					word = word.substr(0, word.length() - 1);

				if(tree != NULL)
					tree -> insert(word);
				else if(rbt != NULL)
					rbt -> insert(word);
				else if(hashTable != NULL)
				{
					hashTable -> insert(word);
				}
			}
		}
		else if(instruction == "delete")
		{
			string param;
			cin >> param;

			if(tree != NULL)
				tree -> del(param);
			else if(rbt != NULL)
				rbt -> del(param);
			else if(hashTable != NULL)
				hashTable -> del(param);
		}
		else if(instruction == "find")
		{
			string param;
			cin >> param;

			if(tree != NULL)
			{
				Node * result = tree -> search(tree -> root, param);

				if(result == NULL)
					cout << "0" << endl;
				else
					cout << "1" << endl;
			}
			else if(rbt != NULL)
			{
				RBNode * result = ((RBNode *)rbt -> search(rbt -> root, param));

				if(result == NULL)
					cout << "0" << endl;
				else
					cout << "1" << endl;
			}
			else if(hashTable != NULL)
			{
				int result = hashTable -> search(param);
				if(result == 0)
					cout << "0" << endl;
				else
					cout << "1" << endl;
			}
		}
		else if(instruction == "min")
		{
			if(tree != NULL)
			{
				Node * result = tree -> min(tree -> root);
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(rbt != NULL)
			{
				RBNode * result = ((RBNode *)rbt -> min(rbt -> root));
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(hashTable != NULL)
				hashTable -> min();
		}
		else if(instruction == "max")
		{
			if(tree != NULL)
			{
				Node * result = tree -> max(tree -> root);
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(rbt != NULL)
			{
				RBNode * result = ((RBNode *)rbt -> max(rbt -> root));
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(hashTable != NULL)
				hashTable -> max();
		}
		else if(instruction == "succesor")
		{
			string param;
			cin >> param;

			if(tree != NULL)
			{
				Node * result = tree -> succesor(param);
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(rbt != NULL)
			{
				RBNode * result = ((RBNode *)rbt -> succesor(param));
				if(result == NULL)
					cout << endl;
				else
					cout << result -> key << endl;
			}
			else if(hashTable != NULL)
				hashTable -> succesor();
		}
		else if(instruction == "inorder")
		{
			if(tree != NULL)
			{
				(tree -> inOrder_counter)++;
				tree -> inOrderWalk(tree -> root);
				cout << endl;
			}
			else if(rbt != NULL)
			{
				(rbt -> inOrder_counter)++;
				rbt -> inOrderWalk(rbt -> root);
				cout << endl;
			}
			else if(hashTable != NULL)
				hashTable -> inOrderWalk();
		}
		else
		{
			cout << "Wrong instruction" << endl;
		}
	}

	clock_t end = clock();
	double result = end - start;
	cerr << "Time: " << result / CLOCKS_PER_SEC << endl;

	if(tree != NULL)
	{
		cerr << "insert: " << tree -> insert_counter << endl;
		cerr << "delete: " << tree -> delete_counter << endl;
		cerr << "find: " << tree -> search_counter << endl;
		cerr << "min: " << tree -> min_counter << endl;
		cerr << "max: " << tree -> max_counter << endl;
		cerr << "succesor: " << tree -> succesor_counter << endl;
		cerr << "in order: " << tree -> inOrder_counter << endl;
		cerr << "max fill: " << tree -> max_fill << endl;
		cerr << "elements at end: " << tree -> number_of_el << endl;
	}
	else if(hashTable != NULL)
	{
		cerr << "insert: " << hashTable -> insert_counter << endl;
		cerr << "delete: " << hashTable -> delete_counter << endl;
		cerr << "find: " << hashTable -> search_counter << endl;
		cerr << "min: " << hashTable -> min_counter << endl;
		cerr << "max: " << hashTable -> max_counter << endl;
		cerr << "succesor: " << hashTable -> succesor_counter << endl;
		cerr << "in order: " << hashTable -> inOrder_counter << endl;
		cerr << "max fill: " << hashTable -> max_fill << endl;
		cerr << "elements at end: " << hashTable -> number_of_el << endl;
	}
}








