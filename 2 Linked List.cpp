//bassic functions
//Struct of Single linked list
typedef struct _slinklist 
{
	struct _slinklist *next;
	int e;
}SLL;
//Creat Single linked list with N node, data value 0~n-1,
SLL *fCreatSLL(SLL **phead, int n)
{
	SLL *pn = NULL;
	SLL *psll = (SLL *)malloc(sizeof(SLL));
	if(!psll)
		return NULL;
	psll->e = 0;
	psll->next = NULL;
	pn = psll;
	*phead = psll;
	
	for(int i=1;i<n;i++)
	{
		pn = (SLL *)malloc(sizeof(SLL));
		if(pn == NULL)
			return NULL;
		pn->e = i;
		pn->next = NULL;
		psll->next = pn;
		psll = pn;
	}
	return *phead;
}
//Free Single linked list 
bool fFreeSLL(SLL *phead)
{
	if(!phead)
		return false;

	SLL *psll = phead;
	while(phead != NULL)
	{
		psll = phead->next;
		free(phead);
		phead = psll;
	}
	return true;
}
//Print Single linked list 
bool fPrintSLL(SLL *phead)
{
	if(!phead)
		return false;

	while(phead != NULL)
	{
		printf("phead->e is %d\n", phead->e);
		phead = phead->next;
	}
	return true;
}
//Get Single linked list length
int GetLen(SLL *ph)
{
	if(!ph)
		return 0;
	int len = 0;
	while(ph)
	{
		ph = ph->next;
		len++;
	}
	return len;
}

//2.1 Write code to remove duplicates from an unsorted linked list.
//use map<int, bool> or hash[data] = true; O(n)space, O(n) time.
void removeDuplicate(SLL *phead)
{
	if(phead == NULL)
		return;
	map<int, bool> msll;
	SLL *temp = NULL, *head = phead, *prev = NULL;
	while(head != NULL)
	{
		if(msll[head->data] == true)
		{
			temp = head->next;
			delete head;
			head = temp;
			prev->next = head;
		}
		else
		{
			msll[head->data] = true;
			prev = head;
			head = head->next;
		}
	}
}
//can't use extra space, 那需要两个指针， 当第一个指针指向某个元素时，第二个指针把该元素后面与它相同的元素删除， 时间复杂度O(n^2)
void removeDuplicate(SLL *head)
{
	if(head == NULL)
		return;
	SLL *cur = head, *prev = NULL, *trave = NULL;
	while(cur != NULL)
	{
		prev = cur;
		trave = cur->next;
		while(trave != NULL)
		{
			if(cur->data == trave->data)
			{
				prev->next = trave->next;
				free(trave);
				trave = prev->next;				
			}
			else
			{
				prev = trave;
				trave = trave->next;
			}
		}
		cur = cur->next;
	}
}

//b. Remove Duplicates from Sorted List. 迭代版，时间复杂度O(n)，空间复杂度O(1)
SLL *deletDuplicate(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	for (SLL *pre = head, *cur = head->next; cur != NULL; cur = cur->next)
	{
		if (pre->data == cur->data)
		{
			pre->next = cur->next;
			delete cur;
		}
		else
			pre = cur;
	}
	return head;
}

//c. Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
// For example, Given 1->2->3->3->4->4->5, return 1->2->5. 递归版，时间复杂度O(n)，空间复杂度O(1)
SLL *delDup(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	SLL *cur = head->next;
	if (head->data == cur->data)
	{
		while (cur != NULL && head->data == cur->data)
		{
			SLL *tmp = cur;
			cur = cur->next;
			delete tmp;
		}
		delete head;
		return delDup(cur);
	}
	else
	{
		head->next = delDup(head->next);
		return head;
	}
}
SLL *delDup(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	SLL newhead(-1);
	newhead.next = head;
	SLL *pre = &newhead, *cur = head;
	while (cur != NULL)
	{
		bool dup = false;
		while (cur->next != NULL && cur->data == cur->next->data)
		{
			SLL *tmp = cur;
			cur = cur->next;
			delete tmp;
			dup = true;
		}
		if (dup)
		{
			SLL *tmp = cur;
			cur = cur->next;
			delete tmp;
			continue;
		}
		pre->next = cur;
		pre = pre->next;
		cur = cur->next;
	}
	pre->next = cur;
	return newhead.next;
}

//2.2 Implement an algorithm to find the nth to last element of a singly linked list.
SLL *getKth2Last(SLL *phead, int k)
{
	if(k <= 0 || phead == NULL)
		return NULL;
	SLL *pa = phead;
	SLL *pb = phead;

	while(k > 0 && pa != NULL)
	{
		pa = pa->next;
		--k;
	}
	if(k > 0 && pa == NULL)
		return NULL;
	while(pa->next != NULL)
	{
		pb=pb->next;
		pa=pa->next;
	}
	return pb;
}
//Get mid node of Link
SLL *GetMid(SLL *phead)
{
	if(!phead || !phead->next)
		return phead;
	SLL *pa = phead;
	SLL *pb = phead;
	while(pa->next)
	{
		pa =pa->next;
		pb=pb->next;
		if(pa->next)
			pa=pa->next;
	}
	return pb;
}

/*Split a list into two sublists — one for the front half, and one for the back half. If the number of elements is odd, the extra element should go in the front list.
So FrontBackSplit() on the list {2, 3, 5, 7, 11} should yield the two lists {2, 3, 5} and {7, 11}.*/
Node *split2list(Node *head)// return second list head
{
	if (head == NULL || head->next == NULL)// only 1 element
		return NULL;
	Node *s = head, *f = head->next->next;
	while (f != NULL)
	{
		s = s->next;
		if (f->next == NULL)
			break;
		else
			f = f->next->next;
	}
	return s->next;
}

//2.3 Implement an algorithm to delete a node in the middle of a single linked list, given only access to that node.
void delMidNode(SLL *pNode)
{
	if(pNode == NULL)
		return;
	SLL *pNext = pNode->next;
	if(pNext == NULL)
		pNode->data = 0xFFFFFFFF;
	else
	{
		pNode->data = pNext->data;
		pNode->next = pNext->next;
		free(pNext);
		pNext = NULL;
	}
	return;
}

//2.4 You have two numbers represented by a linked list, where each node contains a single digit. The digits are stored in reverse order, such that the 1’s digit is at the head of the list. Write a function that adds the two numbers and returns the sum as a linked list.
// Input: (3 -> 1 -> 5), (5 -> 9 -> 2)  Output: 8 -> 0 -> 8
SLL *sum2SLL(SLL *phead1, SLL *phead2)
{
	if(phead1 == NULL && phead2 != NULL)
		return phead2;
	else if(phead1 != NULL && phead2 == NULL)
		return phead1;
	else if(phead1 == NULL && phead2 == NULL)
		return NULL;
	else
	{		
		int carry = 0;		
		SLL *pnewhead = NULL, *psumhead = NULL;		
		while(phead1 != NULL && phead2 != NULL)
		{
			SLL *pnew = new SLL;
			if(pnew == NULL)
				return NULL;			
			pnew->data = phead1->data + phead2->data + carry;			
			pnew->next = NULL;
			if(pnewhead == NULL)
			{
				pnewhead = psumhead = pnew;
			}
			else
			{
				psumhead->next = pnew;
				psumhead = pnew;
			}
			if(pnew->data > 9)
			{
				carry = 1;
				pnew->data %= 10;
			}
			else
				carry = 0;
			phead1=phead1->next;
			phead2=phead2->next;
		}
		while(phead1 != NULL)
		{
			SLL *pnew = new SLL;
			if(pnew == NULL)
				return NULL;			
			pnew->data = phead1->data + carry;
			carry = pnew->data/10;
			pnew->data %= 10;	
			pnew->next = NULL;
			psumhead->next = pnew;
			psumhead = pnew;
			phead1 = phead1->next;
		}
		while(phead2 != NULL)
		{
			SLL *pnew = new SLL;
			if(pnew == NULL)
				return NULL;			
			pnew->data = phead2->data + carry;
			carry = pnew->data/10;
			pnew->data %= 10;
			pnew->next = NULL;
			psumhead->next = pnew;
			psumhead = pnew;
			phead2 = phead2->next;
		}
		if(phead1 == NULL && phead2 == NULL && carry == 1)
		{
			SLL *pnew = new SLL;
			if(pnew == NULL)
				return NULL;			
			pnew->data = 1;
			carry = 0;
			pnew->next = NULL;
			psumhead->next = pnew;
			psumhead = pnew;
		}
		return pnewhead;
	}
}
SLL *add2num(SLL *l1, SLL *l2)
{
	SLL sum(-1);
	int carry = 0, a = 0, b = 0, val = 0;
	SLL *pre = &sum;
	for (SLL *p1 = l1, *p2 = l2; p1 != NULL || p2 != NULL;
		p1 = p1 == NULL ? NULL : p1->next, p2 = p2 == NULL ? NULL : p2->next, pre = pre->next)
	{
		a = p1 == NULL ? 0 : p1->data;
		b = p2 == NULL ? 0 : p2->data;
		val = (a + b + carry) % 10;
		carry = (a + b + carry) / 10;
		pre->next = new SLL(val);
	}
	if (carry > 0)
		pre->next = new SLL(carry);
	return sum.next;
}

//两个单链表（singly linked list），每一个节点里面一个0-9的数字， 输入就相当于两个大数了。然后返回这两个数的和（一个新list）。这两个输入的list 长度相等。 要求是：1. 不用递归。2. 要求算法在最好的情况下，只遍历两个list一次， 最差的情况下两遍。
struct Node
{
	int data;
	Node *next;
};
Node *makeSLL(int a[], int n)
{
	if(a == NULL || n < 1)
		return NULL;
	Node *head = new Node;
	head->data = a[0];
	head->next = NULL;
	Node *pre = head;
	for(int i=1; i<n; ++i)
	{
		Node *cur = new Node;
		cur->data = a[i];
		cur->next = NULL;
		pre->next = cur;
		pre = cur;
	}
	return head;
}
void delSLL(Node **head)
{
	if(*head == NULL)
		return;
	while(*head)
	{
		Node *cur = *head;
		*head = (*head)->next;
		delete cur;
		cur = NULL;
	}
}
Node *add2SLL(Node *list1, Node *list2)
{
	if(list1 == NULL || list2 == NULL)
		return NULL;
	Node *head3 = new Node;
	head3->data = list1->data + list2->data;
	head3->next = NULL;
	Node *pre = head3, *cur = head3;

	while((list1 = list1->next) && (list2 = list2->next))
	{
		Node *list3 = new Node;
		list3->data = list1->data + list2->data;
		list3->next = NULL;
		cur->next = list3;
		cur = list3;
		if(cur->data < 9)
			pre = cur;
		else if(cur->data > 9)
		{
			cur->data -= 10;
			pre->data += 1;
			while(++pre != cur)
				pre->data = 0;
		}
	}
	if(head3->data > 9)
	{	
		Node *list3 = new Node;
		list3->data = 1;
		list3->next = head3;
		head3->data -= 10;
		head3 = list3;
	}
	return head3;
}

//2.5 Check if the Single linked list has a loop if yes, return the head of the loop
SLL *hascircle(SLL *phead)
{
	SLL *pf = phead;
	SLL *ps = phead;
	while(pf!=NULL&&pf->next!=NULL)
	{
		pf=pf->next->next;
		ps=ps->next;
		if(ps==pf)
			break;
	}
	if(!pf||!pf->next)
		return NULL;
	ps=phead;
	while(pf!=ps)
	{
		pf=pf->next;
		ps=ps->next;
	}
	return pf;
}
//use map<>
map<SLL*, bool> mapSLL;
SLL *mapfindcirclehead(SLL *phead)
{
	while(phead != NULL)
	{
		if(mapSLL[phead] == true)
			return phead;
		else
		{
			mapSLL[phead] = true;
			phead = phead->next;
		}
	}
	return phead;
}

//2.6 Reverse Single linked list 
SLL *fRevList(SLL *phead)
{
	if(!phead || !phead->next)
		return phead;	
	SLL *prev = NULL, *pnew = NULL;
	while(phead)
	{
		pnew = phead;
		phead = phead->next;
		pnew->next = prev;
		prev = pnew;
	}
	return prev;
}
//recursion method
void recursiveReverse(Node **head)
{
	if(*head == NULL || (*head)->next == NULL)
		return;
	Node *first = *head;
	Node *rest = first->next;
	recursiveReverse(&rest);
	first->next->next = first;
	first->next = NULL;
	*head = rest;
}

//b. Reverse a linked list from position m to n. Do it in-place and in one-pass. For example: Given 1->2->3->4->5->null, m=2 and n=4, return 1->4->3->2->5->null.1<=m<=n<=length
SLL *reverseBetween(SLL *head, int m, int n)
{
	assert(m >= 1 && n >= m);
	if (head == NULL || head->next == NULL || m == n)
		return head;
	SLL *pm = head, *pre = head;
	int cnt = m;
	while (cnt > 1 && pm != NULL)
	{
		pre = pm;
		pm = pm->next;
		--cnt;
	}
	if (pm == NULL)
		return head;
	cnt = m;
	SLL *pn = pm->next;
	while (n - cnt > 0 && pn != NULL)
	{
		pm->next = pn->next;
		pn->next = pre->next;
		pre->next = pn;
		pn = pm->next;
		++cnt;
	}
	if (n - cnt > 0 && pn == NULL)
		cout << "Error n is bigger than list length" << endl;
	return head;
}

//2.7 Print list from back end, itration(i=0), recursion(i=1)
void RPrintList(SLL *phead, int i)
{
	if(i == 0)
	{
		stack<SLL *> sl;
		while(phead)
		{
			sl.push(phead);
			phead = phead->next;
		}
		SLL *p = NULL;
		while(!sl.empty())
		{
			p=sl.top();
			cout<<p->e<<endl;
			sl.pop();
		}
	}
	else if(i == 1)
	{
		if(!phead)
			return;
		else
		{
			RPrintList(phead->next,1);
			cout<<"recursion: "<<phead->e<<endl;
		}
	}
	else
		return;
}

//2.8 Merge sorted 2 lists iteration
SLL *fMergeSortList(SLL *p1, SLL *p2)
{
	if(p1 == NULL && p2 != NULL)
		return p2;
	else if(p1 != NULL && p2 == NULL)
		return p1;
	else if(p1 == NULL && p2 == NULL)
		return NULL;
	else
	{
		SLL *phm = NULL;
		if(p1->e<p2->e)
		{
			phm = p1;
			p1=p1->next;
			phm->next=NULL;
		}
		else
		{
			phm=p2;
			p2=p2->next;
			phm->next=NULL;
		}

		SLL *ptmp=phm;
		while(p1!=NULL && p2!=NULL)
		{
			if(p1->e<p2->e)
			{
				ptmp->next=p1;
				p1=p1->next;
				ptmp=ptmp->next;
				ptmp->next=NULL;
			}
			else
			{
				ptmp->next=p2;
				p2=p2->next;
				ptmp=ptmp->next;
				ptmp->next=NULL;
			}
		}
		if(p1)
			ptmp->next=p1;
		if(p2)
			ptmp->next=p2;
		return phm;
	}
}
//Merge sorted 2 lists recursion
SLL *MergeSortListRecu(SLL *p1, SLL *p2)
{
	if(p1 == NULL && p2 != NULL)
		return p2;
	else if(p1 != NULL && p2 == NULL)
		return p1;
	else if(p1 == NULL && p2 == NULL)
		return NULL;
	else
	{
		SLL *phm=NULL;
		if(p1->e<p2->e)
		{
			phm=p1;
			phm->next=MergeSortListRecu(p1->next,p2);
		}
		else
		{
			phm=p2;
			phm->next=MergeSortListRecu(p1,p2->next);
		}
		return phm;
	}
}

//2.9 check if 2 SLL like Y, has intersection.
bool isIntersect(SLL *p1, SLL *p2)
{
	if(!p1||!p2)
		return false;
	SLL *ptail=p1;
	while(ptail->next)
		ptail=ptail->next;

	while(p2->next)
		p2=p2->next;
	return p1==p2;
}

//2.10 Given a node from a cyclic linked list which has been sorted, write a function to insert a value into the list such that it remains a cyclic sorted list. The given node can be any single node in the list.
Node* insert(Node *node, int x)
{
	if(node == NULL)
	{
		node = new Node(x);
		node->next = node;
		return node;
	}
	Node *cur = node, *pre = NULL;
	do{
		pre = cur;
		cur = cur->next;
		if(x <= cur->data && x >= pre->data)
			break;//prev→val ≤ x ≤ current→val:
		else if((x >= pre->data || x <= cur->data) && (pre->data >= cur->data))
			break;//x is the maximum or minimum value in the list
	}while(cur != node);//Traverses back to the starting point:the list has only one value or all duplicates
	Node *newNode = new Node(x);
	pre->next = newNode;
	newNode->next = cur;
	return newNode;
}

//2.11 Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
// 时间复杂度O(n)，空间复杂度O(1), preserve the original relative order of the nodes in each of the two partitions. Given 1->4->3->2->5->2 and x = 3, return 1->2->2->4->3->5.
SLL *partition(SLL* head, int x)
{
	SLL left(-1), right(-1);
	SLL *l = &left, *r = &right;
	for (SLL *cur = head; cur != NULL; cur = cur->next)
	{
		if (cur->data < x)
		{
			l->next = cur;
			l = cur;
		}
		else
		{
			r->next = cur;
			r = cur;
		}
	}
	l->next = right.next;
	r->next = NULL;
	return left.next;
}

//2.12 Given a list, rotate the list to the right by k places, where k is non-negative. Given 1->2->3->4->5->nullptr and k = 2, return 4->5->1->2->3->nullptr.
// 时间复杂度O(n)，空间复杂度O(1)
SLL *rotateRight(SLL *head, int k)
{
	if (head == NULL || k == 0)
		return head;
	int len = 1;
	SLL *cur = head->next;
	while (cur != NULL)
	{
		++len;
		cur = cur->next;
	}
	int m = len - k % len;
	cur = head;//首尾相连
	while (m > 1)
	{
		cur = cur->next;
		--m;
	}
	head = cur->next;
	cur->next = NULL;
	return head;
}

//2.13 Given a linked list, swap every two adjacent nodes and return its head. For example, Given 1->2->3->4, you should return the list as 2->1->4->3.
//swap the whole node. 时间复杂度O(n)，空间复杂度O(1)
SLL *swapPair(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	SLL pn(-1);
	pn.next = head;
	for (SLL *pre = &pn, *cur = head, *next = head->next; next != NULL; pre = cur, cur = cur->next, next = cur ? cur->next : NULL)
	{
		pre->next = next;
		cur->next = next->next;
		next->next = cur;
	}
	return pn.next;
}
//swap the node value. 时间复杂度O(n)，空间复杂度O(1)
SLL *swapPairValue(SLL *head)
{
	SLL *cur = head;
	while (cur && cur->next)
	{
		swap(cur->data, cur->next->data);
		cur = cur->next->next;
	}
	return head;
}

//2.14 Reverse the nodes of a linked list k at a time and return its modified list. If the number of nodes is not a multiple of k then left - out nodes in the end should remain as it is.
// Given this linked list : 1->2->3->4->5, For k = 2, you should return : 2->1->4->3->5, For k = 3, you should return : 3->2->1->4->5
// 递归版，时间复杂度O(n)，空间复杂度O(1)
SLL *reverseKGroup(SLL *head, int k)
{
	if (head == nullptr || head->next == nullptr || k < 2)
		return head;
	SLL *next_group = head;//the head of next group
	for (int i = 0; i < k; ++i)
	{
		if (next_group)
			next_group = next_group->next;
		else
			return head;
	}
	SLL *newNext = reverseKGroup(next_group, k);//the new head of next group after reversion
	SLL *pre = NULL, *cur = head;
	while (cur != next_group)
	{
		SLL *next = cur->next;
		cur->next = pre ? pre : newNext;
		pre = cur;
		cur = next;
	}
	return pre;//the new head of this group
}
// 迭代版，时间复杂度O(n)，空间复杂度O(1)
SLL *reverse(SLL *pre, SLL *end)
{
	// prev 是first 前一个元素, [begin, end] 闭区间，保证三者都不为null, 返回反转后的倒数第1个元素
	SLL *begin = pre->next, *endNext = end->next;
	for (SLL *p = begin, *cur = p->next, *next = cur->next; cur != endNext; p = cur, cur = next, next = next ? next->next : NULL)
	{
		cur->next = p;
	}
	begin->next = endNext;
	pre->next = end;
	return begin;
}
SLL *reverseKth(SLL *head, int k)
{
	if (head == nullptr || head->next == nullptr || k < 2)
		return head;
	SLL pn(-1);
	pn.next = head;
	for (SLL *pre = &pn, *cur = head; cur != NULL; cur = pre->next)
	{
		for (int i = 1; i < k && cur != NULL; ++i)
			cur = cur->next;
		if (cur == NULL)
			break;// less than k
		pre = reverse(pre, cur);
	}
	return pn.next;
}

//2.15 Return a deep copy of the list that each node contains an additional random pointer which could point to any node in the list or null.
// 两遍扫描，时间复杂度O(n)，空间复杂度O(1)
RSLL *copyRSLL(RSLL *head)
{
	RSLL *cur = head, *pre = NULL;
	for (cur = head; cur != NULL;)
	{
		RSLL *node = new RSLL(cur->data);
		node->next = cur->next;
		cur->next = node;
		cur = node->next;
	}
	for (cur = head; cur != NULL;)
	{
		if (cur->random != NULL)
			cur->next->random = cur->random->next;//point new linked list point
		cur = cur->next->next;
	}
	RSLL newhead(-1);
	for (cur = head, pre = &newhead; cur != nullptr;)
	{
		pre->next = cur->next;
		pre = pre->next;
		if (cur->next != NULL)
			cur->next = cur->next->next;
		cur = cur->next;
	}
	return newhead.next;
}

//2.16 Given a singly linked list L : L0->L1->...->Ln-1->Ln, reorder it to: L0->Ln->L1->Ln-1->... , in-place without altering the nodes’ values.
//找到中间节点，断开，把后半截单链表reverse 一下，再合并两个单链表, 时间复杂度O(n)，空间复杂度O(1)
SLL * reverse(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	SLL *pre = head;
	for (SLL *cur = head->next, *next = cur->next; cur; pre = cur, cur = next, next = next ? next->next : NULL)
		cur->next = pre;
	head->next = nullptr;
	return pre;
}
void reorderSLL(SLL *head)
{
	if (head == nullptr || head->next == nullptr)
		return;
	SLL *slow = head, *fast = head, *pre = NULL;
	while (fast && fast->next)
	{
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	pre->next = nullptr;//cut at middle
	slow = reverse(slow);
	//merge 2 list
	SLL *cur = head;
	while (cur->next)
	{
		SLL *tmp = cur->next;
		cur->next = slow;
		slow = slow->next;
		cur->next->next = tmp;
		cur = tmp;
	}
	cur->next = slow;
}

/*2.17 Design and implement a data structure for Least Recently Used(LRU) cache. It should support the following operations : get and set.
get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present.
双向链表插入和删除效率高, 哈希表保存每个节点的地址，可以基本保证在O(1) 时间内查找节点, 时间复杂度O(logn)，空间复杂度O(n)
越靠近链表头部，表示节点上次访问距离现在时间最短，尾部的节点表示最近访问最少. 访问节点时，如果节点存在，把该节点交换到链表头部，同时更新hash 表中该节点的地址
插入节点时，如果cache 的size 达到了上限capacity，则删除尾部节点，同时要在hash 表中删除对应的项；新节点插入链表头部*/
class LRUCache
{
private:
	struct CacheNode
	{
		int key;
		int value;
		CacheNode(int k, int v) :key(k), value(v){}
	};
	list<CacheNode> cacheList;
	unordered_map<int, list<CacheNode>::iterator> cacheMap;
	int capacity;
public:
	LRUCache(int size)
	{
		capacity = size;
	}
	int get(int key)
	{
		if (cacheMap.find(key) == cacheMap.end())
			return -1;
		// 把当前访问的节点移到链表头部，并且更新map 中该节点的地址
		cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
		cacheMap[key] = cacheList.begin();
		return cacheMap[key]->value;
	}
	void set(int key, int value)
	{
		if (cacheMap.find(key) == cacheMap.end())
		{
			if (cacheList.size() == capacity)
			{
				//删除链表尾部节点（最少访问的节点）
				cacheMap.erase(cacheList.back().key);
				cacheList.pop_back();
			}
			// 插入新节点到链表头部, 并且在map 中增加该节点
			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();
		}
		else
		{
			//更新节点的值，把当前访问的节点移到链表头部, 并且更新map 中该节点的地址
			cacheMap[key]->value = value;
			cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
			cacheMap[key] = cacheList.begin();
		}
	}
};