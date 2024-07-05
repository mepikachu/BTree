/*
Btrees are balanced search trees not balanced binary trees(AVL trees). They are used because they
perform well on secondary memory as they minimize the no of I/O operations. There are 2 types of memories one is primary and other 
is secondary memory. Primary memory is made up of silicon semiconductors and they are really fast and requires less time for I/O 
operations but they are expensive on the other hand secondary memory requires more time for I/O operations but are relatively cheaper
and they are used for storing huge amount of memory. Btrees are used when the data is very very large, large enough that it can't
be stored in primary memory so secondary memory is used. In secondary memory they minimize the no of I/O operations. In secondary
memory data is accesssed using a physical read/write head as the spindle spins the read/write head reads the data. Now since Btrees 
are very large a continuous memory can't be used as it it possible the it is not available so we have to use pointers. Now due to
pointers when it goes from one pointer to another the read/write head should also adjust itself so that it can read the next pointer
data and this process takes huge time compartive to when read/write head is on the correct position so if every node can store some
data/value in an array then the no of times read/write head moves is greatly reduced so is the time complexity so as we call it as
minimized no of I/O operations.
Every btree has a minimum degree which is named as t (t>=2)(if t==2 it is a 2-3-4 tree). This degree decides the no of values that can be
stored in a node and the no of children of a node or the branching factor of the tree. The maximum value a node can store is 2t-1
keys and the minimum value a node store is t-1 keys. (except the root node it can atleat 1 key to max 2t-1 keys considering non 
empty btree). The no of child of any node is 1 greater than the no of keys in that node (so it ranges from t to 2t children per node)
Every node has the following elements -> x.n (the no of keys in that node), x.keys (an array consisting of 0 to n-1 keys value),
x.child (an array consisting of 0 to n children value) and x.leaf a boolean variable stating whether a node is leaf node(the last
node) or not. The leaf node will have x.child as an empty array.
The keys are arranged in a such fashion that they are in ascending order and they follow the particular order
x.child.key1 <= x.key1 <= x.child.key1 <= x.key2 <= ...... <= x.keyn <= x.child.keyn+1 (= implies that btree can store duplicate value)
Searching in the btree can be done by the same method as of binary search trees O(logn(base k)) ~ klogn(base k)
Searching in btree at first glance may seem to be better than bst but they are not in bst (when balanced like AVL trees) is O(logn)
with base 2 or logn(base 2) iterations but in btrees it is ~klogn(base k) iterations but n=2^a we get for bst : a and for btrees:
klog2(base k)*a and klog2(base k) is greater than ~2(minimum at 2.718 and value 1.884)
The insertion in a btree automatically balances the btree so there is no need for rotation to be performed
Same is with deletion btree automatically is balanced
The maximum height which can be achieved in a btree is h max = log((n+1)/2) (base k) which is obv less than logn(base k)
The minimum height of a btree is h min = log(n+1) (base 2k) - 1
Insertion is same as bst new values are inserted in the leaf nodes only. In insertion the btree is always balanced because new values
are inserted into the existing node only if node is full its parent are split but new value is inserted into the existing node only
whereas in bst during insertion height changes (may change) as values are inserted after the leaf nodes. The only insertion case in
btree which leads to change in height is when root is full so in this root spilts into two median becomes the new root which implies
that left and right subtree both height increases by equal amount 1.

*/


#include <iostream>
#include <cstring>
using namespace std;

template <typename dtype> class btree{
public:
	struct btree_node{
		int n;
		dtype* keys;
		btree_node** child; // it is a pointer to the array of pointer to the child hence btree_node**
		bool leaf;
	};
	
	btree_node* root = NULL; // pointing towards the root node of the btree
	int t = 2; // minimum degree of the btree
	
	btree(int degree){
		// constructor of the class
		t = degree;
	}
	
	btree(dtype* arr, int size, int degree){
		// constructor of the class
		t = degree;
		for (int i=0; i<size; i++){
			insert(arr[i]);
		}
	}
	
	void array_insert(dtype* arr, dtype ivalue, int ind, int size){
		// the return type is void because pointer to the array is passed
		// ind is the index where ivalue has to be inserted
		// index of last element in the array would size-1
		// insert into the array ivalue at index ind by shifting the successive index values by 1
		// shifting the array from last_element till index ind is reached
		for (int i=size-1; i>=ind; i--){
			arr[i+1] = arr[i];
		}
		arr[ind] = ivalue;
	}
	
	void array_insert_ptr(btree_node** arr, btree_node* ivalue, int ind, int size){
		// the return type is void because pointer to the array is passed
		// ind is the index where ivalue has to be inserted
		// index of last element in the array would size-1
		// insert into the array ivalue at index ind by shifting the successive index values by 1
		// shifting the array from last_element till index ind is reached
		for (int i=size-1; i>=ind; i--){
			arr[i+1] = arr[i];
		}
		arr[ind] = ivalue;
	}
	
	void array_delete(dtype* arr, int ind, int size){
		// the return type is void because pointer to the array is passed
		// ind is the index which has to be deleted
		// index of last element in the array would size-1
		// delete the index ind and shift the successive index values by -1
		// i<size-1 is because i+1 for i<size would reach size which may give segmentation fault
		for (int i=ind; i<size-1; i++){
			arr[i] = arr[i+1];
		}
	}
	
	void array_delete_ptr(btree_node** arr, int ind, int size){
		// the return type is void because pointer to the array is passed
		// ind is the index which has to be deleted
		// index of last element in the array would size-1
		// delete the index ind and shift the successive index values by -1
		// i<size-1 is because i+1 for i<size would reach size which may give segmentation fault
		for (int i=ind; i<size-1; i++){
			arr[i] = arr[i+1];
		}
	}
	
	dtype* dtype_alloc(dtype* arr, size_t size){
		dtype* temp = (dtype*)malloc(size);
		if (temp==NULL){
			printf("Memory Allocation Failed!\n");
			exit(1); // non zero exiting
		}
		memcpy(temp,arr,size);
		return temp;
	}
	
	btree_node** btree_alloc(btree_node** arr, size_t size){
		btree_node** temp = (btree_node**)malloc(size);
		if (temp==NULL){
			printf("Memory Allocation Failed!\n");
			exit(1); // non zero exiting
		}
		memcpy(temp,arr,size);
		return temp;
	}
	
	int search(btree_node* node, dtype svalue){
		// returns 1 if element is found else 0
		int i;
		for (i=0; i<node->n; i++){
			// (&node).n == node->n
			if (node->keys[i] > svalue) break;
			if (node->keys[i] == svalue) return 1;
		}
		// element is present in the ith child
		if (node->leaf == true){
			return 0; // element cannot be present in ith child as node is a leaf node
		}
		return search(node->child[i],svalue);
	}
	
	int search(dtype svalue){
		// return 1 if element is found else 0
		return search(root,svalue);
	}
	
	int insert(btree_node* node, dtype ivalue){
		// return 0 if insertion is successfull
		int i;
		if (node==NULL){
			return 1; // node can't be null so insertion is not successfull
		}
		for (i=0; i<node->n; i++){
			// (&node).n == node->n
			if (node->keys[i] > ivalue) break;
			// if (node->keys[i] == ivalue) return 1;
		}
		// element is to be inserted either in the ith position or in the ith child
		if (node->leaf == true || node->child==NULL){
			// insert the element as it is a leaf node
			// no need to take care of whether this node is full or not as it is already managed by spliting
			node->keys = dtype_alloc(node->keys,(node->n+1)*sizeof(dtype)); // increasing the size of array by 1
			// Using realloc will save memory as if we were not to use realloc then we would directly assign 2t-1 size to every array
			// and if btree was very large then this would consume huge amount of memory
			// In realloc we are increasing the size by 1 so the old values would still be there in the new array plus some one 
			// additional garbage value			
			array_insert(node->keys,ivalue,i,node->n);
			node->n = node->n + 1; // updating n
			return 0;
		}
		// now we have to manage split
		// firstly chect whether that child have 2t-1 keys or not
		if (node->child[i]->n == 2*t-1){
			// perform the spliting operation
			
			// updating the node
			node->keys = dtype_alloc(node->keys,(node->n+1)*sizeof(dtype));
			node->child = btree_alloc(node->child,(node->n+2)*sizeof(btree_node*)); // earlier this was dtype due to which segmentation fault occured
			// increasing the size of the array by 1
			dtype median = node->child[i]->keys[t-1];
			array_insert(node->keys,median,i,node->n);
			node->n = node->n + 1;
			
			// creating a new_node that would be extra child of the given node
			btree_node* new_node = (btree_node*)malloc(sizeof(btree_node));
			new_node->n = t-1; // t-1 will be the new keys
			new_node->leaf = node->child[i]->leaf;
			new_node->keys = (dtype*)malloc((t-1)*sizeof(dtype)); // t-1 nodes will be there on both the children nodes
			for (int j=t; j<=2*t-2; j++){
				new_node->keys[j-t] = node->child[i]->keys[j];
			}
			if (new_node->leaf==false){
				new_node->child = (btree_node**)malloc(t*sizeof(btree_node*)); // will have t children if that child node was not leaf node
				for (int j=t; j<=2*t-1; j++){
					new_node->child[j-t] = node->child[i]->child[j];
				}
			} else {
				new_node->child = NULL;
			}
			
			// updating the existing child node of the given node
			node->child[i]->n = t-1; // t-1 will be the new keys
			node->child[i]->keys = dtype_alloc(node->child[i]->keys,(t-1)*sizeof(dtype));
			// reducing the size of the array using realloc (to use minimum possible memory). In this case the values uptil
			// t-2 index remains the same and the further elements get deleted
			// So in realloc inc or dec the array size does not affect the element in the array if increased some garbage values 
			// will be there if decreased some elements would be erased or deleted
			// doing the same with the children array of the child node
			if (node->child[i]->leaf==false){
				node->child[i]->child = btree_alloc(node->child[i]->child,t*sizeof(btree_node*));
			}
			
			// now making new_node the i+1 th child of the given node
			array_insert_ptr(node->child,new_node,i+1,node->n+1);
			// and the no of child the previous node had was n+1 exactly the value of current node.n
			
			// now we need to chect whether we have to search in ith or i+1th child
			// comparing ivalue with median
			if (ivalue>node->keys[i]){
				return insert(node->child[i+1],ivalue);
			} else {
				return insert(node->child[i],ivalue);
			}
			
		} else {
			// no spliting is required just normal insertion
			return insert(node->child[i],ivalue);
		}
	}
	
	int insert(dtype ivalue){
		// return 0 if insertion is successfull
		// Firstly we chect whether root is NULL or not i.e. tree is empty or not
		if (root==NULL){
			root = (btree_node*)malloc(sizeof(btree_node));
			root->n = 1; // ivalue is to be inserted in the tree
			root->keys = (dtype*)malloc(sizeof(dtype));
			root->keys[0] = ivalue;
			root->child = NULL;
			root->leaf = true;
			return 0;
		}
		
		// Secondly we have to chect whether root is full or not
		if (root->n == 2*t-1){
			// root is full create a new btree_node
			btree_node* new_root = (btree_node*)malloc(sizeof(btree_node));
			new_root->n = 1; // ivalue is to be inserted in the tree
			new_root->keys = (dtype*)malloc(sizeof(dtype));
			new_root->keys[0] = root->keys[t-1];
			new_root->child = (btree_node**)malloc(2*sizeof(btree_node*)); // 2 children
			
			// creating the other child
			btree_node* new_node = (btree_node*)malloc(sizeof(btree_node));
			new_node->n = t-1; // t-1 will be the new keys
			new_node->leaf = root->leaf;
			new_node->keys = (dtype*)malloc((t-1)*sizeof(dtype)); // t-1 nodes will be there on both the children nodes
			for (int j=t; j<=2*t-2; j++){
				new_node->keys[j-t] = root->keys[j];
			}
			if (root->leaf==false){
				new_node->child = (btree_node**)malloc(t*sizeof(btree_node*)); // will have t children if that child node was not leaf node
				for (int j=t; j<=2*t-1; j++){
					new_node->child[j-t] = root->child[j];
				}
			} else {
				new_node->child = NULL;
			}
			
			// updating the first child
			root->n = t-1; // t-1 will be the new keys
			root->keys = dtype_alloc(root->keys,(t-1)*sizeof(dtype));
			// reducing the size of the array using realloc (to use minimum possible memory). In this case the values uptil
			// t-2 index remains the same and the further elements get deleted
			// So in realloc inc or dec the array size does not affect the element in the array if increased some garbage values 
			// will be there if decreased some elements would be erased or deleted
			// doing the same with the children array of the child node
			if (root->leaf==false){
				root->child = btree_alloc(root->child,t*sizeof(btree_node*));
			} else {
				root->child = NULL;
			}
			
			// assigning the children
			new_root->child[0] = root;
			new_root->child[1] = new_node;
			new_root->leaf = false;
			root = new_root;
			if (root->keys[0]>ivalue){
				// insert in the lchild
				return insert(root->child[0],ivalue);
			} else {
				return insert(root->child[1],ivalue);
			}
			
		} else {
			return insert(root,ivalue);
		}
	}
	
	int btree_delete(btree_node* node, dtype dvalue){
		// return 0 if deletion is successfull
		int i;
		for (i=0; i<node->n; i++){
			// (&node).n == node->n
			if (node->keys[i] > dvalue) break;
			if (node->keys[i] == dvalue){
				// we got the value that has to be deleted
				// our current node cannot have t-1 keys
				if (node->leaf==true){
					// now just simply delete that value
					array_delete(node->keys,i,node->n);
					node->keys = dtype_alloc(node->keys,(node->n-1)*sizeof(dtype));
					// this frees up the space used by the deleted element
					node->n = node->n-1;
					return 0; // successfull deletion
				} else {
					// immediate predecessor child is ith child and immediate successor child is (i+1)th child
					// we have to do recursive deletion
					// there are 3 cases in total
					
					// case (i) when immediate predecessor child has more than t keys
					// moving the rightmost key of immediate predecessor upwards to the ith position
					if (node->child[i]->n >= t){
						// case (i)
						node->keys[i] = node->child[i]->keys[node->child[i]->n - 1]; // assigning the right most key to the deleted key
						return btree_delete(node->child[i],node->keys[i]); // recursively deleting the new dvalue in the immediate predecessor child
					}
					
					// case (ii) when immediate succcessor child has more than t keys
					// moving the leftmost key of immediate successor upwards to the ith position
					if (node->child[i+1]->n >= t){
						// case (ii)
						node->keys[i] = node->child[i+1]->keys[0]; // assigning the left most key to the deleted key
						return btree_delete(node->child[i+1],node->keys[i]); // recursively deleting the new dvalue in the immediate predecessor child
					}
					
					// case (iii) when both case i and case ii does not holds good
					// both the children have t-1 keys so combining both of them into a single child and bring the deleted key as the
					// median of the single child and then recursively delete from that child the same dvalue
					
					// extending immediate predecessor child only
					
					node->child[i]->n = 2*t-1;
					// changing the size of keys and child
					node->child[i]->keys = dtype_alloc(node->child[i]->keys,(2*t-1)*sizeof(dtype)); // updating size of keys array
					
					if (node->child[i]->leaf == false){
						// first time i forgot to include this condition
						node->child[i]->child = btree_alloc(node->child[i]->child,(2*t)*sizeof(btree_node*)); // updating size of child array
					} else {
						node->child[i]->child = NULL;
					}
					
					node->child[i]->keys[t-1] = dvalue; // dvalue becomes the median
					// combining the keys of immediate successor with immediate predecessor
					for (int j=t; j<2*t-1; j++){
						node->child[i]->keys[j] = node->child[i+1]->keys[j-t]; 
					}
					
					if (node->child[i]->leaf == false){
						// now combining the child of immediate successor with immediate predecessor
						for (int j=t; j<2*t; j++){
							node->child[i]->child[j] = node->child[i+1]->child[j-t];
						}
					}
					
					btree_node* imm_suc_ptr = node->child[i+1]; // storing immediate successor in a variable so that memory can be set to free
					// now delete the immediate successor child of dvalue from the node
					array_delete(node->keys,i,node->n);
					array_delete_ptr(node->child,i+1,node->n+1);
					// now updating the value of n of the given node
					node->n = node->n - 1;
					node->keys = dtype_alloc(node->keys,(node->n)*sizeof(dtype));
					node->child = btree_alloc(node->child,(node->n+1)*sizeof(btree_node*));
					// now free up the space used by imm_suc_ptr
					free(imm_suc_ptr);
					// now recursively deleting from the immediate predecessor child the same dvalue
					return btree_delete(node->child[i],dvalue);
				}
			}
		}
		// break point occurs which means that dvalue does not exist in this node
		// now we need to maintain minimum of t keys in the child node which may have dvalue
		if (node->leaf == true){
			// leaf node and we still have not got the value so it does not exists in the btree
			return 1;
		}
		if (node->child[i]->n == t-1 && node->leaf==false){
			
			// case (i) when the left child of that dchild(child from which deletion has to occur) has >=t keys
			// we move the rightmost key of the left child to the given node (i-1)th key and the (i-1)th value of the node to the dchild forming almost a 
			// loop type structure and also the rightmost child of left child becomes leftmost child of the dchild and current node has 
			// no further changes. Left child n decreases by 1 and dchild n increases by 1 making it to t keys
			if ((i-1) >= 0 && node->child[i-1]->n >= t){
				node->child[i]->n = t;
				node->child[i]->keys = dtype_alloc(node->child[i]->keys,t*sizeof(dtype));
				if (node->child[i]->leaf == false){
					node->child[i]->child = btree_alloc(node->child[i]->child,(t+1)*sizeof(btree_node*));
				} else {
					node->child[i]->child = NULL;
				}
				// swapping the values
				array_insert(node->child[i]->keys, node->keys[i-1], 0, t-1); // inserting the current node value in dvalue
				if (node->child[i]->leaf == false){
					array_insert_ptr(node->child[i]->child, node->child[i-1]->child[node->child[i-1]->n], 0, t); // inserting the rightmost child of left child in dchild leftmost child
					// it [node->child[i-1]->n] not [node->child[i-1]->n - 1] because there are n+1 child of a node and also t not t-1 because dchild already has tchild
				}
				node->keys[i-1] = node->child[i-1]->keys[node->child[i-1]->n - 1];
				
				// now free up some memory by decreasing the size of left child keys and children
				node->child[i-1]->n = node->child[i-1]->n-1;
				node->child[i-1]->keys = dtype_alloc(node->child[i-1]->keys, (node->child[i-1]->n)*sizeof(dtype));
				// this removes the last key element
				if (node->child[i]->leaf == false){
					node->child[i-1]->child = btree_alloc(node->child[i-1]->child, (node->child[i-1]->n+1)*sizeof(btree_node*));
				}
				// this removes the last child of left child
				// now we can simply call delete
				return btree_delete(node->child[i],dvalue);
			}
			
			// case (ii) when the right child of that dchild(child from which deletion has to occur) has >=t keys
			// we move the leftmost key of the right child to the given node ith key and the ith value of the node to the dchild forming almost a 
			// loop type structure and also the leftmost child of right child becomes rightmost child of the dchild and current node has 
			// no further changes. Right child n decreases by 1 and dchild n increases by 1 making it to t keys
			if ((i+1) < (node->n+1) && node->child[i+1]->n >= t){
				node->child[i]->n = t;
				node->child[i]->keys = dtype_alloc(node->child[i]->keys,t*sizeof(dtype));
				if (node->child[i]->leaf == false){
					node->child[i]->child = btree_alloc(node->child[i]->child,(t+1)*sizeof(btree_node*));
				} else {
					node->child[i]->child = NULL;
				}
				// swapping the values
				node->child[i]->keys[t-1] = node->keys[i]; // inserting the current node value in dvalue
				if (node->child[i]->leaf == false){
					node->child[i]->child[t] = node->child[i+1]->child[0]; // inserting the leftmost child of right child in dchild rightmost child
				}
				node->keys[i] = node->child[i+1]->keys[0];
				
				// now free up some memory by decreasing the size of right child keys and children
				node->child[i+1]->n = node->child[i+1]->n-1;
				array_delete(node->child[i+1]->keys,0,node->child[i+1]->n+1); // as n is updated before
				node->child[i+1]->keys = dtype_alloc(node->child[i+1]->keys, (node->child[i+1]->n)*sizeof(dtype));
				// this frees up some space
				if (node->child[i]->leaf == false){
					array_delete_ptr(node->child[i+1]->child,0,node->child[i+1]->n+2); // as is update before
					node->child[i+1]->child = btree_alloc(node->child[i+1]->child, (node->child[i+1]->n+1)*sizeof(btree_node*));
					// this frees up some space
				}
				
				// now we can simply call delete
				return btree_delete(node->child[i],dvalue);
			}

			// case (iii) when case i and case ii does not follows
			// both the sibiling of dchild has k-1 keys. In this case we would perform same as the merging of left child and dchild
			// and bring in the median down
			// Firstly trying this with the right child (if it exists and if not then try with left child) of dchild
			if ((i+1) < (node->n+1)){
				// right child would exist and would not give segmentation fault
				node->child[i]->n = 2*t-1;
				// changing the size of keys and child
				node->child[i]->keys = dtype_alloc(node->child[i]->keys,(2*t-1)*sizeof(dtype)); // updating size of keys array
				if (node->child[i+1]->leaf == false){
					// first time i forgot to include this condition so the code gave segmentation fault
					node->child[i]->child = btree_alloc(node->child[i]->child,(2*t)*sizeof(btree_node*)); // updating size of child array
				} else {
					node->child[i]->child = NULL;
				}
				node->child[i]->keys[t-1] = node->keys[i]; // ith becomes the median
				// combining the keys of right child and dchild
				for (int j=t; j<2*t-1; j++){
					node->child[i]->keys[j] = node->child[i+1]->keys[j-t]; 
				}
				// now combining the child of right child and dchild
				if (node->child[i+1]->leaf == false){
					for (int j=t; j<2*t; j++){
						node->child[i]->child[j] = node->child[i+1]->child[j-t];
					}
				}
				
				btree_node* right_child = node->child[i+1]; // storing right_child in a variable so that memory can be set to free
				// now delete the median in the node->keys
				array_delete(node->keys,i,node->n);
				array_delete_ptr(node->child,i+1,node->n+1);
				// now updating the value of n of the given node
				node->n = node->n - 1;
				node->keys = dtype_alloc(node->keys,node->n*sizeof(dtype));
				node->child = btree_alloc(node->child,(node->n+1)*sizeof(btree_node*));
				// now free up the space used by right_child
				//free(right_child);
				// now recursively deleting from the immediate predecessor child the same dvalue
				return btree_delete(node->child[i],dvalue);
				
			} else {
				// right child does not exists merging left child and dchild
				// instead of merging left child into dchild and free left child merge dchild into left child and free dchild
				node->child[i-1]->n = 2*t-1;
				
				// changing the size of keys and child
				node->child[i-1]->keys = dtype_alloc(node->child[i-1]->keys,(2*t-1)*sizeof(dtype)); // updating size of keys array
				if (node->child[i-1]->keys==NULL){
					printf("Memory Allocation Failed!\n");
					return 1;
				}
				if (node->child[i]->leaf == false){
					// first time i forgot to include this condition so the code gave segmentation fault
					node->child[i-1]->child = btree_alloc(node->child[i-1]->child,(node->child[i-1]->n+1)*sizeof(btree_node*)); // updating size of child array
					if (node->child[i-1]->child==NULL){
						printf("Memory Allocation Failed!\n");
						return 1;
					}
				} else {
					node->child[i-1]->child = NULL;
				}
				
				node->child[i-1]->keys[t-1] = node->keys[i-1]; // (i-1)th becomes the median
				// combining the keys of right child and dchild
				for (int j=t; j<2*t-1; j++){
					node->child[i-1]->keys[j] = node->child[i]->keys[j-t]; 
				}
				if (node->child[i]->leaf == false){
					// now combining the child of right child and dchild
					for (int j=t; j<2*t; j++){
						node->child[i-1]->child[j] = node->child[i]->child[j-t];
					}
				}
				btree_node* dchild = node->child[i]; // storing dchild in a variable so that memory can be set to free
				// now delete the median in the node->keys
				array_delete(node->keys,i-1,node->n);
				array_delete_ptr(node->child,i,node->n+1);
				// now updating the value of n of the given node
				node->n = node->n - 1;
				node->keys = dtype_alloc(node->keys,(node->n)*sizeof(dtype));
				if (node->keys == NULL){
					printf("Memory Allocation Failed!\n");
					return 1;
				}
				node->child = btree_alloc(node->child,(node->n+1)*sizeof(btree_node*));
				if (node->child == NULL){
					printf("Memory Allocation Failed!\n");
					return 1;
				}
				// now free up the space used by dchild
				//free(dchild);
				// now recursively deleting from the immediate predecessor child the same dvalue
				return btree_delete(node->child[i-1],dvalue);
			}			
			
		} else {
			btree_delete(node->child[i],dvalue);
		}
	}
	
	int btree_delete(dtype dvalue){
		// We have only 2 cases in which height of the tree decreases one is 2c and other is 3b
		if (root == NULL){
			printf("Empty Btree\n");
			return 1;
		} else if (root->n==1 && root->leaf == true){
			// leaf node
			root = NULL;
			return 0;
		} else if (root->n==1 && root->leaf == false && root->keys[0]==dvalue && root->child[0]->n == t-1 && root->child[1]->n == t-1){
			// 2c case in this we have to shift the median downwards
			btree_node* new_root = (btree_node*)malloc(sizeof(btree_node)); // creating a new root
			new_root->n = 2*t-1;
			new_root->leaf = false;
			new_root->keys = (dtype*)malloc((2*t-1)*sizeof(dtype));
			if (root->child[0]->leaf == false){
				// initially made up a mistake and wrote it new_root->child
				new_root->child = (btree_node**)malloc((2*t)*sizeof(btree_node*));
			} else {
				new_root->child = NULL;
				new_root->leaf = true;
			}
			
			// putting the values of keys in new_root
			for (int i=0; i<t-1; i++){
				new_root->keys[i] = root->child[0]->keys[i]; // left child
			}
			new_root->keys[t-1] = root->keys[0]; // median
			for (int i=t; i<2*t-1; i++){
				new_root->keys[i] = root->child[1]->keys[i-t]; // right child
			}
			
			if (root->child[0]->leaf == false){
				// initially made up a mistake and wrote it new_root->child
				// putting the children into the new_root
				for (int i=0; i<t; i++){
					new_root->child[i] = root->child[0]->child[i]; // left child
				}
				
				for (int i=t; i<2*t; i++){
					new_root->child[i] = root->child[1]->child[i-t]; // right child
				}
			}
			
			root = new_root;
			return btree_delete(root,dvalue);
			
		} else if (root->n==1 && root->child[0]->n == t-1 && root->child[1]->n == t-1){
			// 3b case in this also we shift the median downwards
			// it also has the same code as of 2c
			btree_node* new_root = (btree_node*)malloc(sizeof(btree_node)); // creating a new root
			new_root->n = 2*t-1;
			new_root->leaf = false;
			new_root->keys = (dtype*)malloc((2*t-1)*sizeof(dtype));
			if (root->child[0]->leaf == false){
				// initially made up a mistake and wrote it new_root->child
				new_root->child = (btree_node**)malloc((2*t)*sizeof(btree_node*));
			} else {
				new_root->child = NULL;
				new_root->leaf = true;
			}
			
			// putting the values of keys in new_root
			for (int i=0; i<t-1; i++){
				new_root->keys[i] = root->child[0]->keys[i]; // left child
			}
			new_root->keys[t-1] = root->keys[0]; // median
			for (int i=t; i<2*t-1; i++){
				new_root->keys[i] = root->child[1]->keys[i-t]; // right child
			}
			
			if (root->child[0]->leaf == false){
				// initially made up a mistake and wrote it new_root->child
				// putting the children into the new_root
				for (int i=0; i<t; i++){
					new_root->child[i] = root->child[0]->child[i]; // left child
				}
				
				for (int i=t; i<2*t; i++){
					new_root->child[i] = root->child[1]->child[i-t]; // right child
				}
			}
			
			root = new_root;
			return btree_delete(root,dvalue);
			
		} else {
			return btree_delete(root,dvalue);
		}
	}
	
	dtype min(btree_node* node){
		// min element is the leftmost key of the leftmost child
		if (node->leaf==true){
			// the 0th key is minimum
			return node->keys[0]; // leftmost value
		}
		return min(node->child[0]); // leftmost child
	}
	
	dtype min(){
		return min(root);
	}
	
	void inorder(btree_node* node){
		// firstly checking whether the node is a leaf node or not
		if (node->leaf==true){
			for (int i=0; i<node->n; i++){
				// if node is a leaf nodes then all the keys are printed directly
				printf("%d ",node->keys[i]);
			}
			return;
		}		
		
		inorder(node->child[0]);
		for (int i=0; i<node->n; i++){
			printf("%d ",node->keys[i]);
			inorder(node->child[i+1]);
		}
		return;
	}
	
	void inorder(){
		inorder(root);
	}
	
	void preorder(btree_node* node){
		// firstly checking whether the node is a leaf node or not
		if (node->leaf==true){
			for (int i=0; i<node->n; i++){
				// if node is a leaf nodes then all the keys are printed directly
				printf("%d ",node->keys[i]);
			}
			return;
		}
		
		
		for (int i=0; i<node->n; i++){
			printf("%d ",node->keys[i]);
			preorder(node->child[i]);
			preorder(node->child[i+1]);
		}
		return;
	}
	
	void preorder(){
		preorder(root);
	}
};

int random(int start, int stop){
	// both start and stop included
	return rand()%(stop-start+1)+start;
}

int main(){
	int x = 1;
	while (x--){
		int size = random(100,400);
		int arr[size];
		for (int i=0; i<size; i++){
			arr[i] = random(1,1000);
		}
		int t=3;
		btree<int> Tree1(arr,size, t);
		Tree1.inorder();
		cout << "\nAfter deletion " << endl;
		for (int i=1; i<200;i++){
		    Tree1.btree_delete(i);
		}
		Tree1.inorder();
		cout << endl;
		//Tree1.preorder();
	}
	/*
	int size = 10;
    int arr[size] = {100, 10, 90, 20, 80, 30, 70, 40, 60, 50};
    int t = 2;
    btree<int> T1(arr,size,t);
    T1.inorder();
    cout << endl;
    cout << T1.search(11) << " " << T1.search(10) << endl;
    cout << T1.min() << endl;
    cout << "Deletion" << endl;
    cout << T1.btree_delete(10) << endl;
    cout << T1.btree_delete(20) << endl;
	cout << T1.btree_delete(100) << endl;
    T1.inorder();
	*/
}