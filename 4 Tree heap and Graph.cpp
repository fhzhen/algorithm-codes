struct BTNode
{
	int data;
	BTNode *lchild, *rchild, *parent;
	BTNode(): lchild(NULL), rchild(NULL), parent(NULL){}
};
//4.1 Binary Tree basic function, creat, delete, insert, find
//a. creat BT by using recursion from an array, begin from a[1]
BTNode *makeBTByArray(int a[], int n, int i)
{
	//base case
	if(a == NULL || n-1 < i || i < 1)
		return NULL;
	//creat root node,
	BTNode *root = new BTNode;
	root->data = a[i];//begin from a[1]
	root->lchild = makeBTByArray(a,n,2*i);
	root->rchild = makeBTByArray(a,n,2*i+1);
	return root;
}
//creat BT by using iteration from an array, begin from a[1]
BTNode *creatBTbyArray(int arr[], int num)
{	
	if(arr == NULL || num < 2)
		return NULL;
	BTNode *root = new BTNode[num];
	for(int i=1; i<=num/2; ++i)
	{
		//from a[1] to creat the BT, a[1] is root
		root[i].data = arr[i];
		if(2*i < num)
		{			


			root[i].lchild = &root[2*i];
			root[2*i].data = arr[2*i];
			root[2*i].lchild = NULL;
			root[2*i].rchild = NULL;
		}
		else
			root[i].lchild = NULL;
		if(2*i + 1 < num)
		{
			root[i].rchild = &root[2*i+1];
			root[2*i+1].data = arr[2*i+1];
			root[2*i+1].lchild = NULL;
			root[2*i+1].rchild = NULL;
		}
		else
			root[i].rchild = NULL;
	}
	return &root[1];
}
//creat BT by using iteration from an array, begin from a[0]
BTNode *creatBTbyArray(int arr[], int num)
{
	//from a[0] to creat the BT, a[0] is root
	if(arr == NULL || num < 1)
		return NULL;
	BTNode *root = new BTNode[num];
	root[0].data = arr[0];
	root[0].lchild = NULL;
	root[0].rchild = NULL;
	for(int i=1; i<=num/2; ++i)
	{
		if(2*i-1 < num)
		{			
			root[i-1].lchild = &root[2*i-1];
			root[2*i-1].data = arr[2*i-1];
			root[2*i-1].lchild = NULL;
			root[2*i-1].rchild = NULL;
		}
		else
			root[i-1].lchild = NULL;
		if(2*i < num)
		{
			root[i-1].rchild = &root[2*i];
			root[2*i].data = arr[2*i];
			root[2*i].lchild = NULL;
			root[2*i].rchild = NULL;
		}
		else
			root[i-1].rchild = NULL;
	}
	return root;
}
//bad creat BT function by input a num
BTNode *makeBTimput()
{
	int getNum = 0;
	BTNode *node = NULL;
	cout<<"please input a number as a tree node"<<endl;
	cin>>getNum;
	if(getNum == -1)
		return NULL;
	node = new BTNode;
	node->data = getNum;
	node->lchild = makeBTimput();
	node->rchild = makeBTimput();
	return node;
}

//b. Given a sorted (increasing order) array, create a binary tree (BST) with balanced (minimal height).
BTNode* create_min_BT(BTNode* parent, int a[], int start, int end)//0,n-1
{
	if(start > end)
		return NULL;
	int mid = start + (end - start) / 2;
	BTNode *root = new BTNode;
	root->data = a[mid];
	root->parent = parent;
	root->lchild = create_min_BT(root, a, start, mid-1);
	root->rchild = create_min_BT(root, a, mid+1, end);
	return root;	
}

//c. Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
//need get length n of list first, then b=0, e=n-1
Node* list2bst(List *&list, int b, int e)
{
	if (list == NULL || b > e)
		return NULL;
	int m = b + (e - b) / 2;
	Node *left = list2bst(list, b, m - 1);
	Node *root = new Node(list->data);
	root->left = left;
	list = list->next;
	root->right = list2bst(list, m + 1, e);
	return root;
}

//d. delete whole BT by recursion
void deleteBT(BTNode *root)
{
	if(root == NULL)
		return;
	deleteBT(root->lchild);
	deleteBT(root->rchild);
	//lchild & rchild both NULL
	delete root;
	root = NULL;	
	return;
}
//e. find a data
BTNode *findNode(BTNode *root, int val)
{
	BTNode *node = NULL;
	if(root == NULL)
		return NULL;
	else if(root->data == val)
		return root;
	else if(( node = findNode(root->lchild, val)) != NULL)
		return node;
	else
		return findNode(root->rchild, val);
}
//f. insert node
bool insertBT(Node **node, int data)
{
	if(*node == NULL)
	{
		*node = new Node;
		if(*node == NULL)
			return false;
		(*node)->data = data;
		(*node)->lchild = NULL;
		(*node)->rchild = NULL;		
	}
	else
	{
		if(depthBT((*node)->lchild) > depthBT((*node)->rchild))
			insertBT(&((*node)->rchild),data);
		else
			insertBT(&((*node)->lchild),data);
	}
	return true;
}

//g. Implement BST
class BST
{
private:
	static const int iMax = 1000;
	BTNode *root_, *parent_, node_[iMax];
	int size_;
	BTNode* minimum(BTNode *node)
	{
		if(node == NULL)
			return NULL;
		while(node->lchild != NULL)
			node = node->lchild;
		return node;
	}
	BTNode* maximum(BTNode* node)
	{
		if(node == NULL)
			return NULL;
		while(node->rchild != NULL)
			node = node->rchild;
		return node;
	}
	BTNode* successor(BTNode* node)
	{
		if(node->rchild != NULL)
			return minimum(node->rchild);
		BTNode* temp = node->parent;
		while(temp != NULL && node == temp->rchild)
		{
			node = temp;
			temp = node->parent;
		}
		return temp;
	}
	BTNode* predecessor(BTNode* node)
	{
		if(node->lchild != NULL)
			return maximum(node->lchild);
		BTNode *temp = node->parent;
		while(temp != NULL && node == temp->lchild)
		{
			node = temp;
			temp = node->parent;
		}
		return temp;
	}
	BTNode* find(BTNode* node, int val)
	{
		if(node == NULL)
			return NULL;
		else if(val < node->data)
			return find(node->lchild, val);
		else if(val > node->data)
			return find(node->rchild, val);
		else
			return node;
	}
	void insert(BTNode* &node, int val)
	{
		if(node == NULL)
		{
			node_[size_].data = val;
			node_[size_].parent = parent_;
			node = &node_[size_];
			++size_;
			return;
		}
		parent_ = node;
		if(val < node->data)
			insert(node->lchild, val);
		else
			insert(node->rchild, val);
	}
	void inorderTraver(BTNode* node)
	{
		if(node == NULL)
			return;
		inorderTraver(node->lchild);
		cout<<node->data<<" ";
		inorderTraver(node->rchild);
	}
public:
	BST(): root_(NULL), parent_(NULL), size_(0)
	{
		memset(node_, 0, sizeof(node_));
	}
	BTNode* find(int val)
	{
		return find(root_, val);
	}
	void insert(int val)
	{
		insert(root_, val);
	}
	void inorderTraver()
	{
		inorderTraver(root_);
	}
	void remove(BTNode* node)
	{
		if(node->lchild == NULL && node->rchild == NULL)
		{
			if(node == root_)
				root_ = NULL;
			else if(node == node->parent->lchild)
				node->parent->lchild = NULL;
			else
				node->parent->rchild = NULL;
		}
		else if(node->lchild == NULL || node->rchild == NULL)
		{
			if(node == root_)
			{
				if(node->lchild != NULL)
					root_ = node->lchild;
				else
					root_ = node->rchild;
				root_->parent = NULL;
			}
			else
			{
				if(node == node->parent->lchild && node->lchild != NULL)
				{
					node->parent->lchild = node->lchild;
					node->lchild->parent = node->parent;
				}
				else if(node == node->parent->lchild && node->rchild != NULL)
				{
					node->parent->lchild = node->rchild;
					node->rchild->parent = node->parent;
				}
				else if(node == node->parent->rchild && node->lchild != NULL)
				{
					node->parent->rchild = node->lchild;
					node->lchild->parent = node->parent;
				}
				else
				{
					node->parent->rchild = node->rchild;
					node->rchild->parent = node->parent;
				}
			}
		}
		else
		{
			BTNode *temp = predecessor(node);
			node->data = temp->data;
			if(node == temp->parent)
				temp->parent->lchild = temp->lchild;
			else
				temp->parent->rchild = temp->lchild;
			if(temp->lchild != NULL)
				temp->lchild->parent = temp->parent;
		}
	}	
};

//4.2 Depth of BT O(n)
int depthBT(BTNode *node)
{
	if(node == NULL)
		return 0;
	int left = depthBT(node->lchild);
	int right = depthBT(node->rchild);
	return max(left, right) + 1;
}
//b. minimum depth
int minDepthBT(BTNode *node)
{
	if(node == NULL)
		return 0;
	int l = minDepthBT(node->left);
	int r = minDepthBT(node->right);
	return min(l, r)+1;
}

//c. iteration method, post order
int depthBT(BTNode *root)
{
	if (!root)
		return 0;
	stack<BTNode*> s;
	s.push(root);
	int depth = 0;
	BTNode *pre = NULL;
	while (!s.empty())
	{
		BTNode *cur = s.top();
		if (pre == NULL || pre->left == cur || pre->right == cur)
		{
			if (cur->left != NULL)
				s.push(cur->left);
			else if (cur->right != NULL)
				s.push(cur->right);
		}
		else if (cur->left == pre)
		{
			if (cur->right != NULL)
				s.push(cur->right);
		}
		else
			s.pop();
		pre = cur;
		if (s.size() > depth)
			depth = s.size();
	}
	return depth;
}

//4.3 a. convert binary tree to double linked list. In order sequence
BTNode *BT2DLL(BTNode *root)
{
	if(root == NULL)
		return NULL;
	static BTNode *pre = NULL;
	static BTNode *head = NULL;
	BT2DLL(root->lchild);
	if(pre == NULL)
		head = root;	
	else
	{
		pre->rchild = root;
		root->lchild = pre;
	}
	pre = root;
	BT2DLL(root->rchild);
	return head;
}
// Circular
Node *bt2dllc(Node *root)
{
	if (root == NULL)
		return NULL;
	static Node* pre = NULL, *head = NULL;
	bt2dllc(root->left);
	if (pre == NULL)
		head = root;
	else
	{
		root->left = pre;
		pre->right = root;
	}		
	pre = root;
	head->left = root;
	Node *right = root->right;
	root->right = head;
	bt2dllc(right);
	return head;
}

// Given a binary tree, flatten it to a sigle linked list in-place.时间复杂度O(n)，空间复杂度O(logn)
void flatten(BTNode *root)
{
	if (root == nullptr)
		return;
	flatten(root->left);
	flatten(root->right);
	if (root->left == nullptr)
		return;
	// 三方合并，将左子树所形成的链表插入到root 和root->right 之间
	BTNode *p = root->left;
	while (p->right != nullptr)//寻找左链表最后一个节点
		p = p->right;
	root->right = root->left;
	root->left = nullptr;
}
//recursion method 2, 把root 所代表树变成链表后，tail 跟在该链表后面 
BTNode* flatten(BTNode *root, BTNode *tail)//flatten(root, NULL);
{
	if (root == NULL)
		return tail;
	root->right = flatten(root->left, flatten(root->right, tail));
	root->left = NULL;
	return root;
}
// better 迭代版，时间复杂度O(n)，空间复杂度O(logn)
void flatten(BTNode *root)
{
	if (root == nullptr)
		return;
	stack<BTNode*> s;
	s.push(root);
	while (!s.empty())
	{
		BTNode *p = s.top();
		s.pop();
		if (p->right)
			s.push(p->right);
		if (p->left)
			s.push(p->left);
		p->left = nullptr;
		if (!s.empty())
			p->right = s.top();
	}
}

//b. Populate Inorder Successor for all nodes
struct node
{
  int data;
  struct node* left;
  struct node* right;
  struct node* next;
}
/* Set next of p and all descendents of p by traversing them in reverse Inorder */
void populateNext(struct node* p)
{
    // The first visited node will be the rightmost node
    // next of the rightmost node will be NULL
    static struct node *next = NULL; 
    if (p!= NULL)
    {
        // First set the next pointer in right subtree
        populateNext(p->right); 
        // Set the next as previously visited node in reverse Inorder
        p->next = next; 
        // Change the prev for subsequent node
        next = p; 
        // Finally, set the next pointer in left subtree
        populateNext(p->left);
    }
}

//c. print ancestor of a node
bool printAcestor(Node *root, int data)
{
	if(root == NULL)
		return false;
	if(root->data == data)
		return true;
	//print acestor of the data
	if(printAcestor(root->lchild,data) ||
		printAcestor(root->rchild,data))
	{
		cout<<root->data<<" ";
		return true;
	}
	return false;
}

//d. find the next’node (i.e., in-order successor) of a given node in a BST where each node has a link to its parent.
BTNode *getInorderSucsor(BTNode *node)
{
	if(node == NULL)
		return NULL;
	else if(node->rchild != NULL)
	{
		node = node->rchild;
		while(node->lchild != NULL)
			node = node->lchild;
		return node;
	}
	else
	{
		BTNode *next = node->parent;
		while(next != NULL && next->data < node->data)
			next = next->parent;
		return next;
	}
}
//e. find the next’node (i.e., in-order successor) of a given node in a BST
Node* getInorderSucsor(Node *node, Node *root)
{
	if(node == NULL || root == NULL)
		return NULL;
	if(node->right != NULL)
	{
		node = node->right;
		while(node->left != NULL)
			node = node->left;
		return node;
	}
	else
	{
		Node *suc = NULL;
		while(root != NULL && root != node)
		{
			if(root->data > node->data)
			{
				suc = root;
				root = root->left;
			}
			else
				root = root->right;
		}
		return suc;
	}
}

//4.4 a. Count BT leaf number, time O(n)
int leafNumBT(BTNode *root)
{	
	if(root == NULL)
		return 0;
	else if(root->lchild == NULL && root->rchild == NULL)
		return 1;
	else
		return leafNumBT(root->lchild) + leafNumBT(root->rchild);
}
//b. count all node num, time O(n)
int allNodeNumBT(BTNode *node)
{
	if(node == NULL)
		return 0;
	else
		return allNodeNumBT(node->lchild) + allNodeNumBT(node->rchild) + 1; 
}

//4.5 pre, in, post order BT recursion, time O(n)
//a. Pre Order recursion
void preOrderBT(Node *node)
{
	if(node == NULL)
		return;
	cout<<node->data<<", ";
	preOrderBT(node->lchild);
	preOrderBT(node->rchild);
	return;
}
//Pre Order interator, 使用栈，时间复杂度O(n)，空间复杂度O(n)
void preorder(Node *node)
{
	if(node == NULL)
		return;
	stack<Node *> stackNode;

	while(node != NULL || !stackNode.empty())
	{
		if(node != NULL)
		{
			stackNode.push(node);
			cout<<node->data<<", ";
			node = node->lchild;
		}		
		else
		{
			node = stackNode.top();
			stackNode.pop();			
			node = node->rchild;
		}
	}
}
vector<int> preorder(BTNode *root)
{
	vector<int> result;
	stack<BTNode*> sbt;
	BTNode *node = root;
	if (node != nullptr)
		sbt.push(node);
	while (!sbt.empty())
	{
		node = sbt.top();
		sbt.pop();
		result.push_back(node->data);
		if (node->right != nullptr)
			sbt.push(node->right);
		if (node->left != nullptr)
			sbt.push(node->left);
	}
	return result;
}
// Morris 先序遍历，时间复杂度O(n)，空间复杂度O(1)
vector<int> preorder(BTNode *root)
{
	vector<int> result;
	BTNode *cur = root, *pre = NULL, *node = nullptr;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			result.push_back(cur->data);
			pre = cur;
			cur = cur->right;
		}
		else//查找前驱
		{
			node = cur->left;
			while (node->right != nullptr && node->right != cur)
				node = node->right;
			if (node->right == nullptr)// 还没线索化，则建立线索
			{
				result.push_back(cur->data);// 仅这一行的位置与中序不同
				node->right = cur;
				pre = cur;
				cur = cur->left;
			}
			else// 已经线索化，则删除线索
			{
				node->right = nullptr;
				cur = cur->right;
			}
		}
	}
	return result;
}

//b. In Order
void inOrderBT(Node *node)
{
	if(node == NULL)
		return;
	inOrderBT(node->lchild);
	cout<<node->data<<", ";
	inOrderBT(node->rchild);
	return;
}
void inorder(Node *root)
{
	if(root == NULL)
		return;
	stack<Node *> sn;
	while(root != NULL || !sn.empty())
	{
		if(root != NULL)
		{
			sn.push(root);
			root = root->lchild;
		}
		else
		{
			root = sn.top();
			cout<<root->data<<", ";
			sn.pop();
			root = root->rchild;
		}
	}
}
// Morris 中序遍历，时间复杂度O(n)，空间复杂度O(1)
vector<int> inorder(BTNode *root)
{
	vector<int> result;
	BTNode *cur = root, *pre = nullptr, *node = nullptr;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			result.push_back(cur->data);
			pre = cur;
			cur = cur->right;
		}
		else// 查找前驱
		{
			node = cur->left;
			while (node->right != nullptr && node->right != cur)
				node = node->right;
			if (node->right == nullptr)//还没线索化，则建立线索
			{
				node->right = cur;
				cur = cur->left;
			}
			else//已经线索化，则访问节点，并删除线索
			{
				result.push_back(cur->data);
				node->right = nullptr;
				pre = cur;
				cur = cur->right;
			}
		}
	}
	return result;
}

//c. Post Order
void postOrderBT(Node *node)
{
	if(node == NULL)
		return;
	postOrderBT(node->lchild);
	postOrderBT(node->rchild);
	cout<<node->data<<", ";
	return;
}
void postOrder(Node* root)//space O(h)
{
	if(root == NULL)
		return;
	stack<Node*> sn;
	Node *cur = NULL, *pre = NULL;
	sn.push(root);
	while(!sn.empty())
	{
		cur = sn.top();
		if((cur->lchild == NULL && cur->rchild == NULL) || 
			(pre!=NULL && (pre == cur->lchild || pre == cur->rchild)))
		{
			cout<<cur->data<<" ";
			sn.pop();
			pre = cur;
		}
		else
		{
			if(cur->rchild != NULL)
				sn.push(cur->rchild);
			if(cur->lchild != NULL)
				sn.push(cur->lchild);
		}
	}
	return;
}
void postOrder2Stack(Node *root) //space O(n)
{
	if (!root)
		return;
	stack<Node*> s;
	stack<Node*> output;
	s.push(root);
	while (!s.empty())
	{
		Node *cur = s.top();
		output.push(cur);
		s.pop();
		if (cur->left)
			s.push(cur->left);
		if (cur->right)
			s.push(cur->right);
	}
	while (!output.empty())
	{
		cout << output.top()->data << " ";
		output.pop();
	}
}

//4.6 build unique tree by in order + pre/post order array, can't be unique by pre + post order array.
// creat a node + input array
Node *newNode(int data)
{
/*
	int in[9] = {8,4,9,2,5,1,6,3,7};
	int pre[9] = {1,2,4,8,9,5,3,6,7};
	int post[9] = {8,9,4,5,2,6,7,3,1};
	int pre1[9] = {1,2,3,4,5,6,8,9,7};
	int post1[9] = {2,4,8,9,6,7,5,3,1};
*/
	Node *node = new Node;
	node->data = data;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}
// search the node in inorder array
int search(int a[], int start, int end, int data)
{
	for(int i=start; i<=end; ++i)
		if(a[i] == data)
			return i;
	return -1;
}
//a. build tree by preorder and inorder array
Node *buildBT(int in[], int pre[], int inStart, int inEnd)
{
	if(in == NULL || pre == NULL || inStart > inEnd)
		return NULL;
	static int preIndex = 0;
	Node *tNode = newNode(pre[preIndex++]);
	if(inStart == inEnd)
		return tNode;
	int inIndex = search(in, inStart, inEnd, tNode->data);
	tNode->lchild = buildBT(in, pre, inStart, inIndex-1);
	tNode->rchild = buildBT(in, pre, inIndex+1, inEnd);
	return tNode;
}
//b. build BT by inorder and postorder 2 --time O(n);
Node *InPostBuildBT(int in[], int post[], int n)
{
	if(in == NULL || post == NULL || n < 1)
		return NULL;
	int i = n-1;
	while(post[n-1] != in[i])
		--i;
	Node *node = new Node;
	node->data = post[n-1];
	node->lchild = InPostBuildBT(in, post, i);
	node->rchild = InPostBuildBT(in+i+1, post+i, n-i-1);
	return node;
}
//c. build tree by preorder + postorder
Node *PPBuildBT(int pre[], int post[], int start, int end)
{
	static int preIndex = 0;
	static int size = end;
	if(preIndex > size || start > end)
		return NULL;
	Node *node = new Node;
	node->data = pre[preIndex++];
	node->lchild = NULL;
	node->rchild = NULL;
	if(start == end)
		return node;
	int i = 0;
	for(i = start; i<=end; ++i)
		if(pre[preIndex] == post[i])
			break;
	if(i<=end)
	{
		node->lchild = PPBuildBT(pre, post, start, i);
		node->rchild = PPBuildBT(pre, post, i+1, end);
	}
	return node;
}
//hash table to find index of element
const int MAX = 256; int mapIndex[MAX];//ASCII
void map2Index(int in[], int n)
{
	for(int i=0; i<n; ++i)
	{
		assert(in[i] >= 0 && in[i] < MAX);
		mapIndex[in[i]] = i;
	}
}
Node *preInorder(int in[], int pre[], int n, int offset)
{
	if(n == 0)
		return NULL;
	int rootVal = pre[0];
	int i = mapIndex[rootVal] - offset;
	Node *root = new Node(rootVal);
	root->left = preInorder(in, pre+1, i, offset);
	root->right = preInorder(in+i+1, pre+i+1, n-i-1, offset+i+1);
	return root;
}
Node *postInorder(int in[], int post[], int n, int offset)
{
	if(n == 0)
		return NULL;
	int rootVal = post[n-1];
	int i = mapIndex[rootVal] - offset;
	Node *root = new Node(rootVal);
	root->left = postInorder(in, post, i, offset);
	root->right = postInorder(in+i+1, post+i, n-i-1, offset+i+1);
}

//d. Saving a Binary Search Tree to a File (use pre-order sequence), restore to the exact original BST using the saved format. time O(n)
void readBST(int min, int max, int &val, BTNode *&node, ifstream &fin)
{
	if (val > min && val < max)
	{
		int v = val;
		node = new BTNode(v, NULL, NULL);
		if (fin >> val)
		{
			readBST(min, v, val, node->left, fin);
			readBST(v, max, val, node->right, fin);
		}
	}
}
void buildBST(BTNode *&root, ifstream &fin)
{
	int val = 0;
	fin >> val;
	readBST(INT_MIN, INT_MAX, val, root, fin);
}
//e. serialize and deserialize a binary tree. Writing the tree to a file is called ‘serialization’ and reading back from the file to reconstruct the exact same binary tree is ‘deserialization’.
void writeBT(BTNode *root, ostream &out)
{
	if (root == NULL)
		out << "-1 ";//all element are positive.
	else
	{
		out << root->data << " ";
		writeBT(root->left, out);
		writeBT(root->right, out);
	}
}
void readBT(BTNode *&root, ifstream &in)
{
	int val = 0;
	in >> val;
	if (val == -1)
		return;
	root = new BTNode(val, NULL, NULL);
	readBT(root->left, in);
	readBT(root->right, in);
}

//4.7 Level Order Tree Traversal recursion, level begin from 1
//time O(N^2);
void PrintNodeAtLevel(BTNode *node, int level)
{
	if(node == NULL || level < 1)
		return;
	else if(level == 1)
		cout<<node->data<<", ";
	else
	{
		PrintNodeAtLevel(node->lchild, level-1);
		PrintNodeAtLevel(node->rchild, level-1);
	}
}
void levelOrderBT(BTNode *node)
{
	if(node == NULL)
		return;
	//end condition is level<=depth
	int depth = depthBT(node);
	for(int level=1; level<=depth ;++level)
	{
		PrintNodeAtLevel(node,level);
		cout<<endl;
	}
	return;
}
//iterator, vector, time O(n)
void LevelOrderBTIter(BTNode *node)
{
	if(node == NULL)
		return;
	vector<BTNode *> vecNode;
	int cur = 0, last = 1;
	vecNode.push_back(node);
	while(cur<vecNode.size())
	{
		last = vecNode.size();

		while(cur<last)
		{
			cout<<vecNode[cur]->data<<", ";
			if(vecNode[cur]->lchild != NULL)
				vecNode.push_back(vecNode[cur]->lchild);
			if(vecNode[cur]->rchild != NULL)
				vecNode.push_back(vecNode[cur]->rchild);
			++cur;
		}
		cout<<endl;
	}
}
//iterator, queue, time O(n)
void levelOrderBTbyQue(BTNode *root)
{
	if(root == NULL)
		return;
	queue<BTNode *> qn;
	qn.push(root);
	while(!qn.empty())
	{
		root = qn.front();
		qn.pop();
		cout<<root->data<<", ";
		if(root->lchild != NULL)
			qn.push(root->lchild);
		if(root->rchild != NULL)
			qn.push(root->rchild);
	}
}
//queue+vector
vector<vector<int>> levelOrder(BTNode *root) //space O(n)
{
	queue<BTNode*> cur, next;
	vector<vector<int>> result;
	vector<int> level;
	if (root != nullptr)
		cur.push(root);
	while (!cur.empty())
	{
		while (!cur.empty())
		{
			BTNode *node = cur.front();
			cur.pop();
			level.push_back(node->data);
			if (node->left != nullptr)
				next.push(node->left);
			if (node->right != nullptr)
				next.push(node->right);
		}
		result.push_back(level);
		level.clear();
		swap(next, cur);
	}
	return result;
}

//Given a binary tree, print out the tree in zig zag level order (ie, from left to right, then right to left for the next level and alternate between). Output a newline after the end of each level.
void levelOrderZigZag(Node *root)
{
	if (root == NULL)
		return;
	stack<Node*> curlvl, nextlvl;
	bool left2right = true;
	curlvl.push(root);
	while (!curlvl.empty())
	{
		Node *curNode = curlvl.top();
		curlvl.pop();		
		cout << curNode->data << " ";
		if (left2right)
		{
			if (curNode->left != NULL)
				nextlvl.push(curNode->left);
			if (curNode->right != NULL)
				nextlvl.push(curNode->right);
		}
		else
		{
			if (curNode->right != NULL)
				nextlvl.push(curNode->left);
			if (curNode->left != NULL)
				nextlvl.push(curNode->right);
		}
		if (curlvl.empty())
		{
			cout << endl;
			left2right = !left2right;
			swap(curlvl, nextlvl);
		}
	}
}

//b. Given a BST, design an algorithm which creates a linked list of all the nodes at each depth (i.e., if you have a tree with depth D, you’ll have D linked lists).
vector<list<BTNode *>> getLvlLinklist(BTNode *root)
{
	vector<list<BTNode *>> veclist;
	int level = 0;
	list<BTNode *> li;
	li.push_back(root);
	veclist.push_back(li);
	while(!veclist[level].empty())
	{
		list<BTNode *> listBT;
		list<BTNode *>::iterator it;
		for(it=veclist[level].begin(); it!=veclist[level].end(); ++it)
		{
			root = *it;
			if(root->lchild != NULL)
			{
				listBT.push_back(root->lchild);
			}
			if(root->rchild != NULL)
			{
				listBT.push_back(root->rchild);
			}
		}
		++level;
		veclist.push_back(listBT);
	}
	veclist.pop_back();
	return veclist;
}

//c. Find the immediate right neighbor of the given node, with parent links given, but without root node.
Node *getByLvl(Node *node, int lvl)
{
	if(node == NULL)
		return NULL;
	if(lvl == 0)
		return node;
	Node *left = getByLvl(node->left, lvl+1);
	if(left != NULL)
		return left;
	else
		return getByLvl(node->right, lvl+1);
}
Node *rightNeighbor(Node *node)
{
	Node *parent = node->parent;
	int level = 0;
	while(parent != NULL)
	{
		while(parent != NULL && node != parent->left)
		{
			node = parent;
			parent = node->parent;
			--level;
		}
		if(parent == NULL)
			return NULL;
		Node *cur = getByLvl(parent->right, level);
		if(cur != NULL)
			return cur;
		else
		{
			node = parent;
			parent = node->parent;
			--level;
		}
	}
	return NULL;
}

//d. Given a binary tree, Populate the nextRight pointers in each node. You may assume that it is a full binary tree(ie, each node other than the leaves has two children.)
void nextRight(BTNode *root)
{
	if (root == NULL)
		return;
	if (root->left == NULL || root->right == NULL)
		return;
	BTNode *rsibling = NULL, *cur = root;
	while (cur != NULL)
	{
		if (cur->nextright != NULL)
			rsibling = cur->nextright->left;
		else
			rsibling = NULL;
		cur->left->nextright = cur->right;
		cur->right->nextright = rsibling;
		cur = cur->nextright;
	}
	nextRight(root->left);
}
//more elegant
void nextRight(BTNode *root)
{
	if (root == NULL)
		return;
	if (root->left != NULL)
		root->left->nextright = root->right;
	if (root->right != NULL)
		root->right->nextright = (root->nextright != NULL) ? root->nextright->left : NULL;
	nextRight(root->left);
	nextRight(root->right);
}
//时间复杂度O(n)，空间复杂度O(logn)
void connect(BTNode *root, BTNode *sibling)//connect(root, NULL);
{
	if (root == NULL)
		return;
	else
		root->next = sibling;
	connect(root->left, root->right);
	if (sibling)
		connect(root->right, sibling->left);
	else
		connect(root->right, nullptr);
}
//iterator 时间复杂度O(n)，空间复杂度O(1)
void connect(BTNode *root)
{
	while (root != nullptr)
	{
		BTNode* next = NULL, *pre = NULL;
		while (root != NULL)
		{
			if (next == NULL)
				next = root->left != NULL ? root->left : root->right;// the first node of next level
			if (root->left != NULL)
			{
				if (pre != nullptr)
					pre->nextright = root->left;
				pre = root->left;
			}
			if (root->right != NULL)
			{
				if (pre != NULL)
					pre->nextright = root->right;
				pre = root->right;
			}
			root = root->nextright;
		}
		root = next;// turn to next level
	}
}

//4.8 get BT max width by recursion, level begin 0, time O(n)
void getMaxWidthRecur(BTNode *root, int count[], int level)
{
  if(root != NULL)
  {
    ++count[level];
	getMaxWidthRecur(root->lchild, count, level+1);
    getMaxWidthRecur(root->rchild, count, level+1);
  }
}

//4.9 get longest distance of 2 node in BT, the same as diameter of tree.
//normal method, time O(N^2)
int diameterBT(BTNode *root)
{
	if(root == 0)
		return 0;
	int lh = depthBT(root->lchild);
	int rh = depthBT(root->rchild);
	int ld = diameterBT(root->lchild);
	int rd = diameterBT(root->rchild);
	return max(lh+rh+1, max(ld,rd));
}
//better method, return diameter of BT, height is the depth of BT, time O(N)
int diameterBT(BTNode *root, int &height)
{
	if(root == NULL)
	{
		height = 0;
		return 0;
	}	
	int lh = 0, rh = 0;//lh/rh --> Height of left/right subtree
	//ld/rd --> Diameter of left/right subtree
	int ld = diameterBT(root->lchild, lh);
	int rd = diameterBT(root->rchild, rh);
	//Height of current node is max of heights of left/right subtrees plus 1
	height = max(lh, rh) + 1;
	return max(lh+rh+1, max(ld, rd));
}
//add 2 more elements in Node struct, time O(N)
int findMaxLen(Node *root)
{
	static int nMaxLen = 0;
	if(root == NULL)
		return 0;
	if(root->lchild == NULL)
		root->nMaxLeft = 0;
	if(root->rchild == NULL)
		root->nMaxRight = 0;
	findMaxLen(root->lchild);
	findMaxLen(root->rchild);
	if(root->lchild != NULL)
		root->nMaxLeft = max(root->lchild->nMaxLeft, root->lchild->nMaxRight) + 1;
	if(root->rchild != NULL)
		root->nMaxRight = max(root->lchild->nMaxLeft, root->lchild->nMaxRight) + 1;
	return nMaxLen = max(root->nMaxLeft+root->nMaxRight, nMaxLen);
}

//4.10 a. is height balanced tree or is AVL (Adelson-Velskii and Landis') tree, time O(n),
//AVL tree is a self balancing binary search tree, the heights of 2 child subtree of any node differ by at most one.
bool isAVL(BTNode *root, int &high)
{
	if(root == NULL)
	{
		high = 0;
		return true;
	}
	int highLeft = 0, highRight = 0;
	bool bleft = isAVL(root->lchild, highLeft);
	bool bright = isAVL(root->rchild, highRight);	
	high = max(highLeft, highRight) + 1;
	if(abs(highLeft - highRight)<=1)		
		return bleft&bright;
	else
		return false;
}

//b. Implement a function to check if a tree is balanced. For the purposes of this question, a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one.
//检查一棵树是否平衡，平衡指的是这棵树任意两个叶子结点到根结点的距离之差不大于1, 非平衡二叉树，即AVL tree
static int num = 0;
void getDepth(BTNode *phead, int arrDep[])
{
	if(phead == NULL)
		return;
	static int depth = 0;
	++depth;
	getDepth(phead->lchild, arrDep);
	//only save the leaf node
	if(phead->lchild == NULL && phead->rchild == NULL)
		arrDep[num++]=depth;
	getDepth(phead->rchild, arrDep);
	--depth;
}
bool isBalance(BTNode *phead, int arrDep[])
{
	if(phead == NULL)
		return true;
	getDepth(phead, arrDep);
	int maxDep = arrDep[0], minDep = arrDep[0];
	for(int i=0; i<num; ++i)
	{
		if(arrDep[i] > maxDep)
			maxDep = arrDep[i];
		else if(arrDep[i] < minDep)
			minDep = arrDep[i];
		else;
	}
	if(maxDep - minDep > 1)
		return false;
	else
		return true;
}
//Returns the height of BT if it is a balanced tree, otherwise, returns `-1`.
int isBalanceBT(BTNode * root)
{
	if (root == nullptr)
		return 0;
	int left = isBalanceBT(root->left);
	int right = isBalanceBT(root->right);
	if (left < 0 || right < 0 || abs(left - right) > 1)
		return -1;
	return max(left, right) + 1;
}

//4.11 check if the BT is completed, time O(n)
bool isBTCompleted(BTNode *root)
{
	if(root == NULL)
		return true;
	queue<BTNode *> qNode;
	qNode.push(root);
	bool flag = false;
	while(!qNode.empty())
	{
		BTNode *node = qNode.front();
		qNode.pop();
		if(node->lchild != NULL)
		{
			if(flag == true)
				return false;
			qNode.push(node->lchild);			
		}
		else
			flag = true;
		if(node->rchild != NULL)
		{
			if(flag)
				return false;
			qNode.push(node->rchild);
		}
		else
			flag = true;
	}
	return true;
}

//4.12 Mirror the tree, time O(n)
BTNode *mirror(BTNode *root)
{
	if(root == NULL)
		return NULL;
	BTNode *pLeft = mirror(root->lchild);
	BTNode *pRight = mirror(root->rchild);
	root->lchild = pRight;
	root->rchild = pLeft;
	return root;
}

//4.13 is binary search tree, time O(n), Returns true if the given tree is a BST and its values are > min and < max
//check if max value in left subtree is smaller than the node and min value in right subtree greater than the node
//isBST(node, INT_MIN, INT_MAX), time O(n)
bool isBST(NodeBT *node, int min, int max)
{
	if(node == NULL)//an empty tree is BST
		return true;
	if(node->data < min || node->data > max)
		return false;
	return isBST(node->left_child, min, node->data-1) &&// Allow only distinct values
		isBST(node->right_child,node->data+1, max);
}

//better, save prev value do In order traversal, time O(n), space no.
bool isBST(NodeBT *node)
{
	static NodeBT *prev = NULL;
	if(node != NULL)
	{
		if(isBST(node->left) == false)
			return false;
		if(prev != NULL && prev->data >= node->data)
			return false;
		prev = node;
		return isBST(node->right);
	}
	return true;
}
//isBST(NodeBT *node, INT_MIN),  time O(n), space O(1).
bool isBST(NodeBT *node, int &prev)
{
	if(node == NULL)
		return true;
	if(isBST(node->lchild, prev) == true)
	{
		if(node->data > prev)
		{
			prev = node->data;
			return isBST(node->rchild,prev);
		}
		else
			return false;
	}
	else
		return false;
}

//save in order val to array and Check if the array is sorted in ascending order, time O(n)+O(n), space O(n)
class CBT
{
private:
	struct BT
	{
		BT *lchild, *rchild, *parent;
		int data;
	};
	static int abt[100];
	static int num;
	void TraverseBT(BT *node);
public:
	bool VerifyBST(BT *node);
	CBT(){};
	~CBT(){};
};
int CBT::abt[100] = {0}; int CBT::num = 0;
void CBT::TraverseBT(BT *node)
{
	if(node == NULL)
		return;
	TraverseBT(node->lchild);
	abt[num++] = node->data;
	TraverseBT(node->rchild);
}
bool CBT::VerifyBST(BT *node)
{
	if(node == NULL)
		return true;
	TraverseBT(node);
	for(int i=0; i<num - 1; ++i)
	{
		if(abt[i] >= ab[i+1])
			return false;
	}
	return true;
}

//b. Two elements of a binary search tree (BST) are swapped by mistake. Recover the tree without changing its structure.
//Morris 中序遍历，时间复杂度O(n)，空间复杂度O(1)
void detect(pair<BTNode*, BTNode*> &broken, BTNode *pre, BTNode *cur)
{
	if (pre != nullptr && pre->data > cur->data)
	{
		if (broken.first == nullptr)
			broken.first = pre;
		broken.second = cur;
	}
}
void recoverBT(BTNode *root)
{
	pair<BTNode*, BTNode*> broken;
	BTNode* cur = root, *pre = nullptr, *node = nullptr;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			detect(broken, pre, cur);
			pre = cur;
			cur = cur->right;
		}
		else
		{
			node = cur->left;
			while (node->right != nullptr && node->right != cur)
				node = node->right;
			if (node->right == nullptr)
			{
				node->right = cur;
				cur = cur->left;
			}
			else
			{
				detect(broken, pre, cur);
				node->right = nullptr;
				pre = cur;
				cur = cur->right;
			}
		}
	}
	swap(broken.first->data, broken.second->data);
}

//4.14 a. LCA (Lowest Common Ancestor) for BST, the n1 & n2 are exist
//a. recursion, find first n as n1<n<n2, time O(h) space O(h) where h is height of tree.
BTNode *LCAinBST(BTNode *root, BTNode *node1, BTNode *node2)
{
	if(root == NULL || node1 == NULL || node2 == NULL)
		return NULL;	
	else if(root->data > max(node1->data, node2->data))
		return LCAinBST(root->lchild, node1, node2);
	else if(root->data < min(node1->data, node2->data))
		return LCAinBST(root->rchild, node1, node2);
	else
		return root;
}
//iterator
BTNode *getLCAinBST(BTNode *root, int val1, int val2)
{
	while(root != NULL)
	{
		if(root->data > val1 && root->data > val2)
			root = root->lchild;
		else if(root->data < val1 && root->data < val2)
			root = root->rchild;
		else
			return root;
	}
	return NULL;
}

//b. LCA of 2 node in BT O(n)
//both data1 and data2 should be exist, returns pointer to LCA
Node *LCA(Node *root, int data1, int data2)
{
	if(root == NULL)//base case
		return NULL;	
	//if a key is ancestor of other, then the ancestor key becomes LCA
	if(root->data == data1 || root->data == data2)
		return root;
	Node *ln = LCA(root->lchild, data1, data2);
	Node *rn = LCA(root->rchild, data1, data2);
	// If both of the above calls return Non-NULL, then one key
    // is present in once subtree and other is present in other,
    // So this node is the LCA
	if(ln != NULL && rn != NULL)
		return root;
	// Otherwise check if left subtree or right subtree is LCA
	else
		return (ln != NULL)? ln : rn;
}
//handles all cases even d1 or d2 is not exist, returns pointer to LCA
// b1/b2 are set as true if d1/d2 are found
BTNode *findLCA2Node(BTNode *root, int d1, int d2, bool &b1, bool &b2)
{
	if(root == NULL)
		return NULL;
	else if(root->data == d1)
	{
		b1 = true;
		return root;
	}
	else if(root->data == d2)
	{
		b2 = true;
		return root;
	}
	else
	{
		BTNode *ln = findLCA2Node(root->lchinld, d1, d2, b1, b2);
		BTNode *rn = findLCA2Node(root->rchinld, d1, d2, b1, b2);
		// If both of the above calls return Non-NULL, then one key
		// is present in once subtree and other is present in other, So this node is the LCA
		if(ln != NULL && rn != NULL)
			return root;
		// Otherwise check if left subtree or right subtree is LCA
		return (ln != NULL)? ln : rn;
	}
}

//c. LCA of 2 node in BT with parent point.time is O(h), space O(h)
Node *LCABT(Node *root, Node *p, Node *q)
{
	hash_set<Node *> vist;
	while(p != NULL || q != NULL)
	{
		if(p != NULL)
		{
			if(!vist.insert(p).second)
				return p;
			p = p->parent;
		}
		if(q != NULL)
		{
			if(!vist.insert(q).second)
				return q;
			q = q->parent;
		}
	}
	return NULL;
}
//LCA of 2 node in BT with parent point.time 3*O(n) is O(n), space O(1)
int getHeight(Node *p)
{
	int height = 0;
	while(p)
	{
		++height;
		p = p->parent;
	}
	return height;
}
Node *getLCA(Node *p, Node *q)
{
	int h1 = getHeight(p);
	int h2 = getHeight(q);
	//make h2 > h1
	if(h1 > h2)
	{
		swap(h1, h2);
		swap(p,q);
	}
	int dh = h2 -h1;
	for(int h=0; h<dh; ++h)
		q = q->parent;
	while(p !=NULL && q !=NULL)
	{
		if(p == q)
			return p;
		p = p->parent;
		q = q->parent;
	}
	return NULL;
}

//4.15 distance of 2 node in BT = d1 + d2 - 2*(root->LCA), Time O(n)
//return pointer to LCA, dist1/dist2 To store distance of data1/data2 from root
//Level (or distance from root) of current node, dist is distance between n1 and n2
int findlevel(BTNode *root, int data, int level)
{
	if(root == NULL)
		return -1;
	else if(root->data == data)
		return level;
	else
	{
		int l = findlevel(root->lchild, data, level+1);
		return (l != -1)? l : findlevel(root->rchild,data, level +1);
	}
}
BTNode *LCA2NodeBT(BTNode *root, int data1, int data2, int &dist1, int &dist2, int &dist, int level)
{
	if(root == NULL)
		return NULL;
	else if(root->data == data1)
	{
		dist1 = level;
		return root;
	}
	else if(root->data == data2)
	{
		dist2 = level;
		return root;
	}
	else
	{
		BTNode *ln = LCA2NodeBT(root->lchild, data1, data2, dist1, dist2, dist, level+1);
		BTNode *rn = LCA2NodeBT(root->rchild, data1, data2, dist1, dist2, dist, level+1);
		if(ln != NULL && rn != NULL)
		{
			dist = dist1 + dist2 - 2*level;
			return root;
		}
		else
			return (ln != NULL)? ln : rn;
	}
}
int dist2NodeBT(BTNode *root, int data1, int data2)
{
	int dist1 = -1, dist2 = -1, dist = -1;
	BTNode *lca = LCA2NodeBT(root, data1, data2, dist1, dist2, dist, 1);
	// If both n1 and n2 were present in Binary Tree, return dist
	if(dist1 != -1 && dist2 != -1)
		return dist;
	//data1 as root and find level of data2 in subtree
	else if(dist1 != -1)
	{
		dist = findlevel(lca, data2, 0);
		return dist;
	}
	//data2 as root and find level of data1 in subtree
	else if(dist2 != -1)
	{
		dist = findlevel(lca, data1, 0);
		return dist;
	}
	else
		return -1;
}

//4.16 Print Edge Nodes (Boundary) of a Binary Tree
void printLeftEdge(Node *root, bool print)
{
	if(root == NULL)
		return;
	if(print || (root->lchild == NULL && root->rchild == NULL))
		cout<<root->data<<" ";
	printLeftEdge(root->lchild, print);
	printLeftEdge(root->rchild, (print && ((root->lchild == NULL)?true:false)));
}
void printRightEdge(Node *root, bool print)
{
	if(root == NULL)
		return;
	printRightEdge(root->lchild, (print && ((root->rchild == NULL)?true:false));
	printRightEdge(root->rchild, print);
	if(print || (root->lchild == NULL && root->rchild == NULL))
		cout<<root->data<<" ";
}
void printAllEdge(Node *root)
{
	if(root == NULL)
		return;
	cout<<root->data<<" ";
	printLeftEdge(root->lchild,true);
	printRightEdge(root->rchild,true);
}

//4.17 Print all nodes that are at distance k from all leaf nodes
void KDistFromLeaf(BTNode *root, int path[], bool visit[], int pathlen, int k)
{
	if(root == NULL)
		return;
	path[pathlen] = root->data;
	visit[pathlen] = false;
	++pathlen;
	//it's a leaf, print the ancestor at distance k only if not be printed
	if(root->lchild == NULL && root->rchild == NULL &&
		pathlen-k-1 >= 0 && visit[pathlen-k-1] == false)
	{
		cout<<path[pathlen-k-1]<<", ";
		visit[pathlen-k-1] = true;
		return;
	}
	KDistFromLeaf(root->lchild,path, visit, pathlen, k);
	KDistFromLeaf(root->rchild,path, visit, pathlen, k);
}
void printKdistFromLeaf(BTNode *root, int k)
{
	int path[20] = {0};
	bool visit[20] = {false};
	int pathlen = 0;
	KDistFromLeaf(root, path, visit, pathlen, k);
}

//4.18 Decide if T2 is a subtree of T1: T1, with millions of nodes, and T2, with hundreds of nodes.
//a. We could create a string representing the inorder and preorder traversals. If T2’s preorder traversal is a substring of T1’s preorder traversal, 
//and T2’s inorder traversal is a substring of T1’s inorder traversal, then T2 is a substring of T1. We can check this using a suffix tree.
// However, we may hit memory limitations because suffix trees are extremely memory intensive.

//b. brute force, time O(n + k * m),k is the number of occurrences of T2’s root in T1
bool matchBT(BTNode *root1, BTNode *root2)
{
	if(root1 == NULL && root2 == NULL)
		return true;
	else if(root1 == NULL || root2 == NULL)
		return false;
	else if(root1->data != root2->data)
		return false;
	else
		return matchBT(root1->lchild, root2->lchild) && matchBT(root1->rchild, root2->rchild);
}
bool subBT(BTNode *root1, BTNode *root2)
{
	if(root2 == NULL)
		return true;
	else if(root1 == NULL)
		return false;
	else if(root1->data = root2->data)
		return matchBT(root1, root2);
	else
		return subBT(root1->lchild, root2) || subBT(root1->rchild, root2);
}

//4.19 You are given a binary tree in which each node contains a value. Design an algorithm to print all paths which sum up to that value. Note that it can be any path in the tree - it does not have to start at the root.
//给定一棵二叉树，每个结点包含一个值。打印出所有满足以下条件的路径： 路径上结点的值加起来等于给定的一个值。注意：这些路径不必从根结点开始
//a. 如果结点中包含指向父亲结点的指针，那么，只需要去遍历这棵二叉树， 然后从每个结点开始，不断地去累加上它父亲结点的值直到父亲结点为空(这个具有唯一性， 因为每个结点都只有一个父亲结点。也正因为这个唯一性， 可以不另外开额外的空间来保存路径)，如果等于给定的值sum，则打印输出。
// 打印输出时，只需要提供当前结点的指针，及累加的层数即可。然后从当前结点开始， 不断保存其父亲结点的值(包含当前结点)直到达到累加层数，然后逆序输出即可。
void printPath(BTNode *node, int level)
{
	vector<int> vec;
	for(int i=0; i<level; ++i)
	{
		vec.push_back(node->data);
		node = node->parent;
	}
	while(vec.empty())
	{
		cout<<vec.back()<<" ";
		vec.pop_back();
	}
	cout<<endl;
}
void findSum(BTNode *node, int sum)
{
	if(node == NULL)
		return;
	BTNode *cur = node;
	int add = 0;
	for(int i=1; cur!=NULL; ++i)
	{
		add += cur->data;
		if(add == sum)
			printPath(node, i);
		cur = cur->parent;
	}
	findSum(node->lchild, sum);
	findSum(node->rchild, sum);
}
//b. 如果结点中不包含指向父亲结点的指针，则在二叉树从上向下查找路径的过程中， 需要为每一次的路径保存中间结果，累加求和仍然是从下至上的，对应到保存路径的数组， 即是从数组的后面开始累加的，这样能保证遍历到每一条路径。
void printPath2(vector<int> vec, int level)
{
	for(int i=level; i<vec.size(); ++i)
		cout<<vec.at(i)<<" ";
	cout<<endl;
}
void getSum(BTNode *node, int sum, vector<int> vec, int level)
{
	if(node == NULL)
		return;
	vec.push_back(node->data);
	int add = 0;
	for(int i=level; i>-1; --i)
	{
		add += vec.at(i);
		if(add == sum)
			printPath2(vec,i);
	}
	vector<int> vec1(vec), vec2(vec);
	getSum(node->lchild, sum, vec1, level+1);
	getSum(node->rchild, sum, vec2, level+1);
}

//4.20 Find the largest BST subtree in a given Binary Tree
// method 1:Start from root and do an inorder traversal of the tree, top --> down. Time O(n^2)
int bigSubBST(BTNode *root)
{
	if(isBST(root))
		return size(root);
	else
		return max(bigSubBST(root->lchild), bigSubBST(root->rchild));
}
//method 2: bottom --> up, Time O(n)
int largeBSTUtil(BTNode *root, int &min, int &max, int &maxsize, bool &isBST)
{
	if(root == NULL)
	{
		isBST = true; // An empty tree is BST 
		return 0; // Size is 0
	}
	/* A flag variable for left subtree property i.e., max(root->left) < root->data */
	bool left_flag = false;
	// A flag variable for right subtree property i.e., min(root->right) > root->data 
	bool right_flag = false;
	/* Following tasks are done by recursive call for left subtree
    a) Get the maximum value in left subtree (Stored in *max_ref)
    b) Check whether Left Subtree is BST or not (Stored in *is_bst_ref)
    c) Get the size of maximum size BST in left subtree (updates *max_size) */
	int mini = INT_MAX;
	max = INT_MIN;
	int ls = largeBSTUtil(root->lchild, min, max, maxsize, isBST);
	if(isBST && root->data > max)
		left_flag = true;
	/* Before updating *min_ref, store the min value in left subtree. So that we have the correct minimum value for this subtree */
	mini = min;
	/* The following recursive call does similar (similar to left subtree) task for right subtree */
	min = INT_MAX;
	int rs = largeBSTUtil(root->rchild, min, max, maxsize, isBST);
	if(isBST && root->data < min)
		right_flag = true;
	// Update min and max values for the parent recursive calls
	if(mini < min)
		min = mini;
	if(root->data < min)
		min = root->data;
	if(root->data > max)
		max = root->data;
	/* If both left and right subtrees are BST. And left and right
     subtree properties hold for this node, then this tree is BST.
     So return the size of this tree */
	if(left_flag && right_flag)
	{
		if(ls + rs + 1 > maxsize)
			maxsize = ls + rs + 1;
		return ls + rs + 1;
	}
	else
	{
		 //Since this subtree is not BST, set is_bst flag for parent calls
		isBST = false;
		return 0;
	}
}
int largestBST(BTNode *root)
{
	int min = INT_MAX; // for min value in right subtree
	int max = INT_MIN; // for max value in left subtree
	int maxsize = 0;   // for size of the largest BST
	bool isBST = false;
	largeBSTUtil(root, min, max, maxsize, isBST);
	return maxsize;
}
//better
int LargestBSTSubtree(Node *node, int &min, int &max, int &size, Node *&bst)
{
	if (node == NULL)
		return 0;
	bool isBST = true;
	int left = LargestBSTSubtree(node->left, min, max, size, bst);
	int curmin = (left == 0) ? node->data : min;
	if (left == -1 || (left != 0 && node->data <= max))
		isBST = false;
	int right = LargestBSTSubtree(node->right, min, max, size, bst);
	int curmax = (right == 0) ? node->data : max;
	if (right == -1 || (right != 0 && node->data >= min))
		isBST = false;
	if (isBST)
	{
		min = curmin;// is the minimum of right subtree
		max = curmax;// is the maximum of left subtree
		int all = left + right + 1;
		if (all > size)
		{
			size = all;
			bst = node;
		}
		return all;
	}
	else
		return -1;// This subtree is not a BST
}
Node * largestBST(Node *root)
{
	int min = 0, max = 0;
	int maxsize = 0;
	Node *bst = NULL;
	LargestBSTSubtree(root, min, max, maxsize, bst);
	return bst;
}

//b. The largest BST may or may not include all of its descendants.
struct Node
{
	int data;
	Node *left, *right;
	Node(int d, Node *l, Node *r)
	{
		data = d;
		left = l;
		right = r;
	}
};
int findBST(Node *node, int min, int max, int &size, Node *&bst, Node *&child)
{
	if (node == NULL)
		return 0;
	if (min < node->data && node->data < max)
	{
		int l = findBST(node->left, min, node->data, size, bst, child);
		Node *left = (l == 0) ? NULL : child;
		int r = findBST(node->right, node->data, max, size, bst, child);
		Node *right = (r == 0) ? NULL : child;
		// create a copy of the current node and assign its left and right child.
		Node *cur = new Node(node->data, left, right);
		// pass the cur as the child to the above tree.
		child = cur;
		int all = l + r + 1;
		if (all > size)
		{
			size = all;
			bst = cur;
		}
		return all;
	}
	else
	{
		// include this node breaks the BST constraint, so treat this node as an entirely new tree and check if a larger BST exist in this tree
		findBST(node, INT_MIN, INT_MAX, size, bst, child);
		return 0;// must return 0 to exclude this node
	}
}
Node* largestBST(Node *root)
{
	Node *bst = NULL, *child = NULL;
	int maxSize = INT_MIN;
	findBST(root, INT_MIN, INT_MAX, maxSize, bst, child);
	return bst;
}

//4. RBT (red black tree)

//4.21 Pretty formatting of a binary tree to the output stream
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printBranch(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BTNode*>& nodesQueue, ostream& out) {
	deque<BTNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		out << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
		out << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
	}
	out << endl;
}
// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BTNode*>& nodesQueue, ostream& out) {
	deque<BTNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
		out << setw(branchLen + 2) << ((*iter) ? intToString((*iter)->data) : "");
		out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
	}
	out << endl;
}
// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BTNode*>& nodesQueue, ostream& out) {
	deque<BTNode*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->data) : "");
	}
	out << endl;
}
void printPretty(BTNode *root, int level, int indentSpace, ostream &out)
{
	int h = maxHeight(root);
	int nodeInCurLvl = 1;
	int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level)*(int)pow(2.0, h - 1);  // eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level + 1)*(int)pow(2.0, h);  // distance between left neighbor node's right arm and right neighbor node's left arm
	int startLen = branchLen + (3 - level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
	deque<BTNode*> dq;
	dq.push_back(root);
	for (int r = 1; r < h; ++r)
	{
		printBranch(branchLen, nodeSpaceLen, startLen, nodeInCurLvl, dq, out);
		branchLen = branchLen / 2 - 1;
		nodeSpaceLen = nodeSpaceLen / 2 + 1;
		startLen = branchLen + (3 - level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodeInCurLvl, dq, out);
		for (int i = 0; i < nodeInCurLvl; ++i)
		{
			BTNode *cur = dq.front();
			dq.pop_front();
			if (cur != NULL)
			{
				dq.push_back(cur->left);
				dq.push_back(cur->right);
			}
			else
			{
				dq.push_back(NULL);
				dq.push_back(NULL);
			}
		}
		nodeInCurLvl *= 2;
	}
	printBranch(branchLen, nodeSpaceLen, startLen, nodeInCurLvl, dq, out);
	printLeaves(indentSpace, level, nodeInCurLvl, dq, out);
}

//4.22 Given two binary trees, write a function to check if they are equal or not. 
// 递归版，时间复杂度O(n)，空间复杂度O(logn)
bool isSameBT(BTNode *p, BTNode *q)
{
	if (p == nullptr && q == nullptr)
		return true;
	else if (p == nullptr || q == nullptr)
		return false;
	else
		return p->data == q->data && isSameBT(p->left, q->left) && isSameBT(p->right, q->right);
}
// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
bool isSameBT(BTNode *p, BTNode *q)
{
	stack<BTNode *> s;
	s.push(q);
	s.push(p);
	while (!s.empty())
	{
		p = s.top(); s.pop();
		q = s.top(); s.pop();
		if (p == nullptr && q == nullptr)
			continue;
		else if (p == nullptr || q == nullptr)
			return false;
		else if (p->data != q->data)
			return false;
		s.push(p->left);
		s.push(q->left);
		s.push(p->right);
		s.push(q->right);
	}
	return true;
}
//b. Check if a binary tree is Symmetric, 递归版，时间复杂度O(n)，空间复杂度O(logn)
bool isSymmetric(BTNode* root)
{
	if (root == nullptr)
		return true;
	else
		return isSameBT(root->left, root->right);
}

//4.23 Given n, how many structurally unique BST’s (binary search trees) that store values 1~n?
//当数组为1~n时，基于以下原则的构建的BST树具有唯一性：以i为根节点的树，其左子树由[1, i-1] 构成，其右子树由[i+1, n]构成。
//定义f(i) 为以[1,i] 能产生的Unique Binary Search Tree 的数目，则空树f(0) = 1, 单个节点f(1) = 1。f(i) = Sum{f(k-1)*f(i-k)}(k=1~i)
//DP, 时间复杂度O(n)，空间复杂度O(n)
int uniqBTNum(int n)
{
	vector<int> f(n + 1, 0);
	f[0] = 1; f[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		for (int k = 1; k <= i; ++k)
			f[i] += f[k - 1] * f[i - k];
	}
	return f[n];
}

//b. Given n, generate all structurally unique BST’s (binary search trees) that store values 1...n.
vector<BTNode*> generate(int start, int end)
{
	vector<BTNode*> subtree;
	if (start > end)
	{
		subtree.push_back(NULL);
		return subtree;
	}
	for (int k = start; k <= end; ++k)
	{
		vector<BTNode*> leftsub = generate(start, k - 1);
		vector<BTNode*> rightsub = generate(k + 1, end);
		for (auto i : leftsub)
		{
			for (auto j : rightsub)
			{
				BTNode *node = new BTNode(k, i, j, NULL);
				subtree.push_back(node);
			}
		}
	}
	return subtree;
}
vector<BTNode *> generateBT(int n)
{
	if (n == 0)
		return generate(1, 0);
	return generate(1, n);
}

//4.24 a. Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
bool pathSum(BTNode *root, int sum)
{
	if (root == NULL)
		return false;
	if (root->left == nullptr && root->right == nullptr)
		return sum == root->data;
	return pathSum(root->left, sum - root->data) || pathSum(root->right, sum - root->data);
}

//b. Given a binary tree and a sum, find all root-to-leaf paths where each path’s sum equals the given sum.
//时间复杂度O(n)，空间复杂度O(logn)
void pathSumBT(BTNode *root, int gap, vector<int> &path, vector<vector<int>> &result)
{
	if (root == NULL)
		return;
	path.push_back(root->data);
	if (root->left == NULL && root->right == NULL)
	{
		if (gap == root->data)
			result.push_back(path);
	}
	pathSumBT(root->left, gap - root->data, path, result);
	pathSumBT(root->right, gap - root->data, path, result);
	path.pop_back();
}
vector<vector<int>> pathSum(BTNode *root, int sum)
{
	vector<vector<int>> result;
	vector<int> path;
	pathSumBT(root, sum, path, result);
	return result;
}

//c. Given a binary tree, find the maximum path sum. The path may start and end at any node in the tree.
//用“最大连续子序列和”的思路，如果说Array 只有一个方向的话，那么Binary Tree 其实只是左、右两个方向而已，我们需要比较两个方向上的值。
//用的dfs 来进行遍历。先算出左右子树的结果L 和R，如果L 大于0，那么对后续结果是有利的，我们加上L，如果R 大于0，对后续结果也是有利的，继续加上R。
int maxPathSum(BTNode* root, int &maxsum)// 时间复杂度O(n)，空间复杂度O(logn), maxsum = INT_MIN;
{
	if (root == NULL)
		return 0;
	int l = maxPathSum(root->left, maxsum);
	int r = maxPathSum(root->right, maxsum);
	int sum = root->data;
	if (l > 0)
		sum += l;
	if (r > 0)
		sum += r;
	maxsum = max(maxsum, sum);
	return max(l, r) > 0 ? max(l, r) + root->data : root->data;
}

//d. Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
//An example is the root-to-leaf path 1->2->3 which represents the number 123.Find the total sum of all root-to-leaf numbers.
int sumPathNum(BTNode *root, int sum)//时间复杂度O(n)，空间复杂度O(logn), sumPathNum(root, 0);
{
	if (root == nullptr)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return sum * 10 + root->data;
	return sumPathNum(root->left, sum * 10 + root->data) + sumPathNum(root->right, sum * 10 + root->data);
}


//Graph
//G.1 Breadth First Traversal(BFS) + Depth First Traversal for a Graph(DFS), use boolean visited array to avoid cycle
// This class represents a directed graph using adjacency list representation
class Graph
{
private:
	int vtcs; // No. of vertices
	list<int> *adj;
	bool *visited;
public:
	Graph(int vtcs)
	{
		this->vtcs = vtcs;
		adj = new list<int>[vtcs];
		visited = new bool[vtcs];
		memset(visited, false, vtcs);
	}
	~Graph()
	{
		delete[] adj;
		delete[] visited;
	}
	void addEdge(int vtc, int wei)
	{
		adj[vtc].push_back(wei);
	}
	//Time: O(V+E) V is number of vertices and E is number of edges in the graph.
	void BFS(int root)
	{
		list<int> que;//queue for BFS
		que.push_back(root);
		visited[root] = true;
		// 'i' will be used to get all adjacent vertices of a vertex
		list<int>::iterator li;
		while(!que.empty())
		{
			root = que.front();
			cout<<root<<" ";
			que.pop_front();
			for(li=adj[root].begin(); li!=adj[root].end(); ++li)
			{
				if(!visited[*li])
				{
					visited[*li] = true;
					que.push_back(*li);
				}
			}
		}		
	}

	//Depth First Traversal for a Graph, DFS of the vertices reachable from vtc. It uses recursive DFSUtil()
	//Time: O(V+E) where V is number of vertices in the graph and E is number of edges in the graph.
	void DFS(int vtc)
	{
		visited[vtc] = true;
		cout<<vtc<<" ";
		list<int>::iterator il;
		for(il= adj[vtc].begin(); il!=adj[vtc].end(); ++il)
		{
			if(!visited[*il])
				DFS(*il);
		}
	}	
	
	//DFS stack<int> method
	void DFS_Stack(int vtc)
	{		
		stack<int> si;
		visited[vtc] = true;
		cout<<vtc<<" ";
		si.push(vtc);
		list<int>::iterator il;
		while(!si.empty())
		{
			vtc = si.top();							
			for(il= adj[vtc].begin(); il!=adj[vtc].end(); ++il)
			{
				if(!visited[*il])
				{
					visited[*il] = true;
					cout<<*il<<" ";	
					si.push(*il);
					break;
				}
			}
			si.pop();	
		}				
	}
};

//a. Given a directed graph, design an algorithm to find out whether there is a route between two nodes.
//like BFS (breadth-first search)
bool route(int src, int dst)
{
	queue<int> que;
	que.push(src);
	visited[src] = true;
	while(!que.empty())
	{
		int top = que.front();
		que.pop();
		if(top == dst)
			return true;
		for(int i=0; i<n; ++i)
		{
			if(g[top][i] && !visited[i])
			{
				que.push(i);
				visited[i] = true;
			}
		}
	}
	return false;
}

//G.2 a. Clone Graph, Input is a Node pointer. Return the Node pointer of the cloned graph.
struct Node
{
	vector<Node *> neighbors;
};
Node *cloneGraph(Node *graph)
{
	if (graph == NULL)
		return NULL;
	unordered_map<Node *, Node *> map;
	queue<Node *> q;
	q.push(graph);
	Node *graphCopy = new Node();
	map[graph] = graphCopy;
	while (!q.empty())
	{
		Node *node = q.front();
		q.pop();
		int n = node->neighbors.size();
		for (int i = 0; i < n; ++i)
		{
			Node *neighbor = node->neighbors[i];
			//no copy exists
			if (map.find(neighbor) == map.end())
			{
				Node *p = new Node();
				map[node]->neighbors.push_back(p);
				map[neighbor] = p;
				q.push(neighbor);
			}
			else// copy already exist
				map[node]->neighbors.push_back(map[neighbor]);
		}
	}
	return graphCopy;
}

/*b. Clone an undirected graph. Each node in the graph contains a label and a list of its neighbours. OJ’s undirected graph serialization : Nodes are labeled uniquely.
We use # as a separator for each node, and, as a separator for node label and each neighbour of the node.As an example, consider the serialized graph{ 0, 1, 2#1, 2#2, 2 }.
The graph has a total of three nodes, and therefore contains three parts as separated by #. 1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
2. Second node is labeled as 1. Connect node 1 to node 2. 3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self - cycle.*/
struct UndirectedGraphNode
{
	int label;
	vector<UndirectedGraphNode*> neighbors;
	UndirectedGraphNode(int x) : label(x) {}
};
// DFS，时间复杂度O(n)，空间复杂度O(n)
class Solution
{
public:
	UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node)
	{
		if (node == NULL)
			return NULL;
		unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> copy;
		clone(node, copy);
		return copy[node];
	}
private:
	static UndirectedGraphNode *clone(const UndirectedGraphNode *node, unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> &copy)
	{
		if (copy.find(node) != copy.end())
			return copy[node];
		UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
		copy[node] = newNode;
		for (auto nbr : node->neighbors)
			newNode->neighbors.push_back(clone(nbr, copy));
		return newNode;
	}
};
// BFS，时间复杂度O(n)，空间复杂度O(n)
UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node)
{
	if (node == nullptr)
		return nullptr;
	unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> copy;// key is original node，value is copied node
	// each node in queue is already copied itself but neighbors are not copied yet
	queue<const UndirectedGraphNode*> q;
	q.push(node);
	copy[node] = new UndirectedGraphNode(node->label);
	while (!q.empty())
	{
		const UndirectedGraphNode* cur = q.front();
		q.pop();
		for (auto nbr : cur->neighbors)
		{
			if (copy.find(nbr) != copy.end())
				copy[cur]->neighbors.push_back(copy[nbr]);
			else
			{
				UndirectedGraphNode *newNode = new UndirectedGraphNode(nbr->label);
				copy[nbr] = newNode;
				copy[cur]->neighbors.push_back(newNode);
				q.push(nbr);
			}
		}
	}
	return copy[node];
}

/*G.3 Union-Find Algorithm | Set 1 (Detect Cycle in a an Undirected Graph)
A disjoint-set data structure is a data structure that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets. 
A union-find algorithm is an algorithm that performs two useful operations on such a data structure:
Find: Determine which subset a particular element is in.This can be used for determining if two elements are in the same subset.
Union : Join two subsets into a single subset.*/
//a. Naive method, time O(n)
struct Edge
{
	int src;
	int dest;
};
struct Graph
{
	int v;//Number of vertice
	int e; // Number of edges
	struct Edge* edge;// graph is represented as an array of edges
	Graph(int v, int e)
	{
		this->v = v;
		this->e = e;
		edge = new Edge[e];
	}
	~Graph()
	{
		delete[] edge;
	}
};
Graph* creatGraph(int v, int e)
{
	Graph* graph = new Graph(v, e);
	return graph;
}
void deleteGraph(Graph* graph)
{
	delete graph;
}
int find(int parent[], int i)//find the subset of an element i
{
	if (parent[i] == -1)
		return i;
	return find(parent, parent[i]);
}
void Union(int parent[], int x, int y)//to do union of two subsets
{
	int xset = find(parent, x);
	int yset = find(parent, y);
	parent[xset] = yset;
}
bool isCycle(Graph *graph)
{
	int *parent = new int[graph->v];
	memset(parent, -1, sizeof(int)*graph->v);
	// Iterate through all edges of graph, find subset of both vertices of every edge, if both subsets are same, then there is cycle in graph.
	for (int i = 0; i < graph->e; ++i)
	{
		int x = find(parent, graph->edge[i].src);
		int y = find(parent, graph->edge[i].dest);
		if (x == y)
			return true;
		Union(parent, x, y);
	}
	delete[] parent;
	return false;
}
//b. Union-Find Algorithm | Set 2 (Union By Rank and Path Compression), time O(logn)
struct Subset
{
	int parent;
	int rank;
};
int find(Subset subsets[], int i)//find the subset of an element i by using path compression technique
{
	// find root and make root as parent of i (path compression)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}
void Union(Subset subsets[], int x, int y)//to do union of two subsets by uses union by rank
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);
	// Attach smaller rank tree under root of high rank tree (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else // If ranks are same, then make one as root and increment its rank by one
	{
		subsets[yroot].parent = xroot;
		++subsets[xroot].rank;
	}
}
bool isCycle(Graph *graph)
{
	Subset *subsets = new Subset[graph->v];
	for (int i = 0; i < graph->v; ++i)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	for (int i = 0; i < graph->e; ++i)
	{
		int x = find(subsets, graph->edge[i].src);
		int y = find(subsets, graph->edge[i].dest);
		if (x == y)
			return true;
		Union(subsets, x, y);
	}
	return false;
}
//c. Detect Cycle in a Directed Graph -- DFS
class Graph//time O(V+E)
{
private:
	int v;//No. of vertices
	list<int> *adj;//Pointer to an array containing adjacency lists
	bool isCyclicUtil(int v, bool visited[], bool *recStack)// used by isCyclic()
	{
		if (visited[v] == false)
		{
			// Mark the current node as visited and part of recursion stack
			visited[v] = true;
			recStack[v] = true;
			// Recursion for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
			{
				if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
					return true;
				if (recStack[*i])
					return true;
			}
		}
		recStack[v] = false;// remove the vertex from recursion stack
		return false;
	}
public:
	Graph(int v)
	{
		this->v = v;
		adj = new list<int>[v];
	}
	void addEdge(int v, int w)//add an edge to graph
	{
		adj[v].push_back(w); //add w to v's list
	}
	bool isCyclic()// return true if there is a cycle in graph
	{
		bool *visited = new bool[v];
		bool *recStack = new bool[v];
		memset(visited, false, v);
		memset(recStack, false, v);
		for (int i = 0; i < v; ++i)
		{
			if (isCyclicUtil(i, visited, recStack))
				return true;
		}
		delete[] visited;
		delete[] recStack;
		return false;
	}
};

//Heap
//H.1 Big heap
void ShiftUp(int a[], int i)// 把第i个元素向上移动
{
	while(i > 1 && a[i] > a[i/2])
	{
		swap(a[i], a[i/2]);
		i >>= 1;
	}
}
void ShiftDown(int a[], int n, int i)// 把第i个元素向下移动
{
	while((i=2*i) <= n)
	{
		if(i+1 <= n && a[i+1] > a[i])
			++i;
		if(a[i] > a[i/2])
			swap(a[i],a[i/2]);
		else
			break;
	}
}
void MakeHeap(int a[], int n)//把数组a变成具备最大堆性质的数组
{
	for(int i=n/2; i>0; --i)
		ShiftDown(a, n, i);
}
void Insert(int a[], int &n, int x)
{
	a[++n] = x;
	ShiftUp(a,n);
}
void Del(int a[], int &n, int i)
{
	a[i] = a[n--];
	if(i>1 && a[i]>a[i/2])
		ShiftUp(a,i);
	else
		ShiftDown(a,n,i);
}
void HeapSort(int a[], int n)// 堆排序，时间复杂度O(nlogn)
{
	MakeHeap(a,n);
	for(int i=n;i>1;--i)
	{
		swap(a[i],a[1]);
		ShiftDown(a, i-1, 1);
	}
}

//H.2 Numbers are randomly generated and passed to a method. Write a program to find and maintain the median value as new values are generated.
//如果我用一个最大堆维护中位数左边的数(包含它)， 用一个最小堆维护中位数右边的数。当n为偶数时，我只需要把左边的数最大那个， 和右边的数最小那个相加除以2即可。左边的最大数即最大堆的堆顶元素， 右边最小数即最小堆的堆顶元素。当n为奇数时，如果最大堆的元素比最小堆的元素多1， 则最大堆的堆顶元素是中位数；如果最小堆的元素比最大堆的元素多1， 则最小堆的堆顶元素是中位数。
//插入新元素还是O(logn)的时间，而取中位数只需要O(1)的时间， 要优于方法一和方法二
//Max heap & min Heap get the median value of array
class Median
{
private:
	priority_queue<int,deque<int>,less<int>> max_heap;//left number <= median
	priority_queue<int,deque<int>,greater<int>> min_heap;//right number > median
public:
	void Insert(int val)
	{
		if(max_heap.empty() && min_heap.empty())
			max_heap.push(val);
		else if(!max_heap.empty() && min_heap.empty())
			max_heap.push(val);
		else if(max_heap.empty() && !min_heap.empty())
			min_heap.push(val);
		else
		{
			if(val > max_heap.top())
				min_heap.push(val);
			else
				max_heap.push(val);
		}
		//调整，保证两个堆的元素数量差别不大于1, 不要用max_heap.size()-min_heap.size()>1, 因为size返回的是unsigned类型，当左边相减得到一个负数时，本来为false, 但会被转为一个大的正数，结果为true，出问题
		while(max_heap.size() > min_heap.size() + 1)
		{
			int temp = max_heap.top();
			max_heap.pop();
			min_heap.push(temp);
		}
		while(min_heap.size() > max_heap.size() + 1)
		{
			int temp = min_heap.top();
			min_heap.pop();
			max_heap.push(temp);
		}
	}
	int GetValue()
	{
		if(max_heap.empty() && min_heap.empty())
			return 0;
		if(max_heap.size() == min_heap.size())
			return (max_heap.top() + min_heap.top())/2;
		else if(max_heap.size() < min_heap.size())
			return min_heap.top();
		else
			return max_heap.top();
	}
};