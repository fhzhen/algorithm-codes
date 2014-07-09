//Stack and Queue
//3.1 Describe how you could use a single array to implement three stacks.
//直接将这个数组平均分为3个部分
class stack3
{
public:
	stack3(int size = 300)
	{
		buf = new int[size*3];
		ptop[0] = ptop[1] = ptop[2] = -1;
		this->size = size;
	}
	~stack3()
	{
		delete[] buf;
	}
	void push(int stackNum, int val)
	{
		int index = stackNum*size + ptop[stackNum] + 1;
		buf[index] = val;
		++ptop[stackNum];
	}
	void pop(int stackNum)
	{
		--ptop[stackNum];
	}
	int top(int stackNum)
	{
		int index = stackNum*size + ptop[stackNum];
		if(index < 0)
		{
			printf("Error to get top value, The stack is empty!");
			exit(1);
		}
		return buf[index];
	}
	bool empty(int stackNum)
	{
		return ptop[stackNum] == -1;
	}
private:
	int *buf;
	int ptop[3];
	int size;
};

//3.2 How would you design a stack which, in addition to push and pop, also has a function min which returns the minimum element? Push, pop and min should all operate in O(1) time.
// use 2 stack to save data and min, save space.
class Stack
{
public:
	Stack(int size = 1000)
	{
		buf = new int[size];
		cur = -1;
	}
	~Stack()
	{
		delete[] buf;
	}
	void push(int val)
	{
		buf[++cur] = val;
	}
	void pop()
	{
		--cur;
	}
	int top()
	{
		return buf[cur];
	}
	bool empty()
	{
		return cur == -1;
	}
private:
	int *buf;
	int cur;
};
class stackWithMin
{
public:
	stackWithMin(){};
	~stackWithMin(){};
	void push(int val)
	{
		sdata.push(val);
		if(val <= min())
			smin.push(val);
	}
	void pop()
	{
		if(sdata.top() == min())
			smin.pop();
		sdata.pop();
	}
	int top()
	{
		return sdata.top();
	}
	bool empty()
	{
		return sdata.empty();
	}
	int min()
	{
		if(smin.empty() == true)
			return INT_MAX;
		else
			return smin.top();
	}
private:
	Stack sdata, smin;
};

//3.3 SetOfStacks should be composed of several stacks, and should create a new stack once the previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single stack (that is, pop() should return the same values as it would if there were just a single stack).
// Implement a function popAt(int index) which performs a pop operation on a specific sub-stack.
const int STACK_SIZE = 100;
const int STACK_NUM = 10;
class Stack
{
private:
	int *buf;
	int cur;
	int capacity;
public:
	Stack(int cap = STACK_SIZE)
	{
		buf = new int[cap];
		cur = -1;
		capacity = cap;
	}
	~Stack()
	{
		delete[] buf;
	}
	void push(int val)
	{
		buf[++cur] = val;
	}
	void pop()
	{
		--cur;
	}
	int top()
	{
		return buf[cur];
	}
	bool empty()
	{
		return cur == -1;
	}
	bool full()
	{
		return cur == capacity - 1;
	}
};
class SetofStacks
{
private:
	Stack *st;
	int cur;
	int capacity;
public:
	SetofStacks(int cap = STACK_NUM)
	{
		st = new Stack[cap];
		cur = 0;
		capacity = cap;
	}
	~SetofStacks()
	{
		delete[] st;
	}
	void push(int val)
	{
		if(st[cur].full())
			++cur;
		st[cur].push(val);
	}
	void pop()
	{
		if(st[cur].empty())
			--cur;
		st[cur].pop();
	}
	void popAt(int index)
	{
		if(st[index].empty())
			return;
		st[index].pop();
	}
	int top()
	{
		while(st[cur].empty())
			--cur;
		return st[cur].top();
	}
	bool empty()
	{
		while(cur != -1 && st[cur].empty())
			--cur;
		return cur == -1;
	}
	bool full()
	{
		if(cur == capacity - 1)
			return st[cur].full();
		else
			return false;
	}
};

//3.4 Towers of Hanoi, you have 3 rods and N disks of different sizes
//recursion method (source, bridge, destination)(1~n,0,0)->(n,1~n-1,0)->(0,1~n-1,n)->(0,0,1~n)
void hanoi(int n, char src, char bri, char dst)
{
	if(n < 1)
		return;
	else if(n == 1)
		cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
	else
	{
		hanoi(n-1, src, dst, bri);
		cout<<"Move disk "<<n<<" from "<<src<<" to "<<dst<<endl;
		hanoi(n-1, bri, src, dst);
	}
}
//stack method
struct Hanoi
{
	int begin, end;
	char src, bri, dst;
	Hanoi(){};
	Hanoi(int ibegin, int iend, char csrc, char cbri, char cdst):
	begin(ibegin),end(iend),src(csrc),bri(cbri),dst(cdst){}
};
void hanoi(int n, char src, char bri, char dst)
{
	stack<Hanoi> sh;
	Hanoi htmp;
	sh.push(Hanoi(1, n, src, bri, dst));
	while(!sh.empty())
	{
		htmp = sh.top();
		sh.pop();
		if(htmp.begin != htmp.end)
		{
			sh.push(Hanoi(htmp.begin,htmp.end-1,htmp.bri,htmp.src, htmp.dst));
			sh.push(Hanoi(htmp.end,htmp.end, htmp.src, htmp.bri, htmp.dst));
			sh.push(Hanoi(htmp.begin, htmp.end-1, htmp.src, htmp.dst, htmp.bri));
		}
		else
			cout<<"Move disk "<<htmp.begin<<" from "<<htmp.src<<" to "<<htmp.dst<<endl;
	}
}

//3.5 Implement a MyQueue class which implements a queue using two stacks.
//by template
template<typename T> class MyQueue
{
public:
	MyQueue(){}
	~MyQueue(){}
	void push(T val)
	{
		sin.push(val);
	}
	void pop()
	{
		move(sin, sout);
		sout.pop();
	}
	T front()
	{
		move(sin, sout);
		return sout.top();
	}
	T back()
	{
		move(sout, sin);
		return sin.top;
	}
	int size()
	{
		return sin.size() + sout.size();
	}
	bool empty()
	{
		return sin.empty() &&  sout.empty();
	}
	void move(stack<T> &src, stack<T> &dst)
	{
		if(dst.empty())
		{
			while(!src.empty())
			{
				dst.push(src.top());
				src.pop();
			}
		}
	}
private:
	stack<T> sin, sout;
};
//Implement Queue using 2 stacks. by sigle linked list
struct Node
{
	int data;
	Node *next;
};
struct Queue
{
	Node *stack1;
	Node *stack2;
};
void push(Node **head, int val)
{
	Node *newNode = new Node;
	if(newNode == NULL)
	{
		printf("Stack overflow! \n");
		getchar();
		exit(0);
	}
	newNode->data = val;
	newNode->next = *head;
	*head = newNode;
}
int pop(Node **head)
{
	if(*head == NULL)
	{
		printf("Queue is empty.\n");
		getchar();
		exit(0);
	}
	else
	{
		Node *top = *head;
		int val = top->data;
		*head = (*head)->next;
		delete top;
		top = NULL;
		return val;
	}
}
void enQueue(Queue *que, int val)
{
	push(&que->stack1, val);
}
int deQueue(Queue *que)
{
	if(que->stack1 == NULL && que->stack2 == NULL)
	{
		cout<<"Queue is empty."<<endl;
		getchar();
		exit(0);
	}
	int val = 0;
	if(que->stack2 == NULL)
	{
		while(que->stack1 != NULL)
		{
			val = pop(&(que->stack1));
			push(&(que->stack2), val);
		}
	}
	val = pop(&que->stack2);
	return val;
}

//use template to implemte stack by 2 queue
template<typename T> class Stack
{
public:
	Stack():ptemp(NULL), pEQ(&mq1), pDQ(&mq2){}
	~Stack(){}
	void push(const T &val);
	T pop();
	bool empty();
	void swap2Q();
private:
	queue<T> mq1;
	queue<T> mq2;
	queue<T> *pEQ, *pDQ, *ptemp;
	
};
template<class T> void Stack<T>::swap2Q()
{
	ptemp = pEQ;
	pEQ = pDQ;
	pDQ = ptemp;
}
template<class T> void Stack<T>::push(const T &val)
{
	pEQ->push(val);

	while(!pDQ->empty())
	{
		pEQ->push(pDQ->front());
		pDQ->pop();
	}
	swap2Q();
}
template<class T> T Stack<T>::pop()
{
	assert(!pDQ->empty());	
	T temp = pDQ->front();
	pDQ->pop();
	return temp;
}
template<typename T> bool Stack<T>::empty()
{
	return pDQ->empty();
}

//3.6 Write a program to sort a stack in ascending order.by push | pop | peek | isEmpty.
//use priority queue
void stackSort(stack<int> &si)
{
	priority_queue<int, vector<int>, greater<int>> pque;
	while(!si.empty())
	{
		pque.push(si.top());
		si.pop();
	}
	while(!pque.empty())
	{
		si.push(pque.top());
		pque.pop();
	}
}
//use additional stack
void stackSort(stack<int> src, stack<int> &sdst)
{
	while(!src.empty())
	{
		int data = src.top();
		src.pop();
		while(!sdst.empty() && sdst.top() < data)
		{
			src.push(sdst.top());
			sdst.pop();
		}
		sdst.push(data);
	}
}

//3.7 Evaluate the value of an arithmetic expression in Reverse Polish Notation. Valid operators are + , -, *, / .Each operand may be an integer or another expression.
//examples : ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9 ; ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
// 递归，时间复杂度O(n)，空间复杂度O(logn)
int rpn(vector<string> &vs)
{
	int x = 0, y = 0;
	auto s = vs.back();
	vs.pop_back();
	if (s.size() == 1 && string("+-*/").find(s) != string::npos)
	{
		y = rpn(vs);
		x = rpn(vs);
		if (s[0] == '+')
			x += y;
		else if (s[0] == '-')
			x -= y;
		else if (s[0] == '*')
			x *= y;
		else
			x /= y;
	}
	else
	{
		size_t i;
		x = stoi(s, &i);
	}
	return x;
}
// 迭代，时间复杂度O(n)，空间复杂度O(logn)
int rpn(vector<string> &vs)
{
	stack<string> ss;
	for (auto i : vs)
	{
		if (string("+-*/").find(i) == string::npos)
			ss.push(i);
		else
		{
			int y = stoi(ss.top(), nullptr, 10);
			ss.pop();
			int x = stoi(ss.top(), nullptr, 10);
			ss.pop();
			if (i[0] == '+')
				x += y;
			else if (i[0] == '-')
				x -= y;
			else if (i[0] == '*')
				x *= y;
			else
				x /= y;
			ss.push(to_string(x));
		}
	}
	return stoi(ss.top());
}