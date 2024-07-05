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

