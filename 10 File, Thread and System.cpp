//10.1 Write a method to print the last K lines of an input file using C++.
void printLastKLines(ifstream &fin, int k)
{
	string *line = new string[k];
	int lines = 0;
	string tmp;
	while(getline(fin, tmp))
	{
		line[lines%k] = tmp;
		++lines;
	}
	int start = 0, cnt = 0;
	if(lines < k)
	{
		start = 0;
		cnt = lines;
	}
	else
	{
		start = lines%k;
		cnt = k;
	}
	for(int i=0; i<cnt; ++i)
		cout<<line[(start+i)%k]<<endl;
	delete[] line;
	return;
}

//10.2 Write a method that takes a pointer to a Node structure as a parameter and returns a complete copy of the passed-in data structure. The Node structure contains two pointers to other Node structures.
struct Node
{
	Node *pre, *next;
};
typedef map<Node*, Node*> NodeMap;
Node * copy_recursive(Node *cur, NodeMap &nodeMap)
{
	if(cur == NULL)
		return NULL;
	NodeMap::iterator inm = nodeMap.find(cur);
	if(inm != nodeMap.end())
		return inm->second;
	Node *node = new Node;
	nodeMap[cur] = node;
	node->pre = copy_recursive(cur->pre, nodeMap);
	node->next = copy_recursive(cur->next, nodeMap);
	return node;
}
Node* copy_structure(Node *root)
{
	NodeMap nodeMap;
	return copy_recursive(root, nodeMap);
}

//10.3 Write a smart pointer (smart_ptr) class.
template<typename T> class SmartPointer
{
	//The smart pointer class needs pointers to both the object itself and to the ref count.
	//These must be pointers, rather than the actual object or ref count value, since the goal 
	//of a smart pointer is that the reference count is tracked across mutiple smart pointers to one object.
protected:
	T *ref;
	unsigned int *ref_count;
	void remove()
	{
		--(*ref_count);
		if(*ref_count == 0)
		{
			delete ref;
			ref = NULL;
			free(ref_count);
			ref_count = NULL;
		}
		cout<<"remove()"<<endl;
	}
public:
	SmartPointer(T *obj)
	{
		//Set the value of T *obj and ref counter to 1
		ref = obj;
		ref_count = (unsigned int*)malloc(sizeof(unsigned int));
		*ref_count = 1;
		cout<<"SmartPointer(T *obj)"<<endl;
	}
	SmartPointer(SmartPointer<T> &sptr)
	{
		//Creat a new smart pointer that points to an existing boject. We need to first set obj and ref_count 
		//to pointer to sptr's obj and ref_count. Then, because we created a new reference to obj, we need to increment ref_count.
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
		cout<<"SmartPointer(SmartPointer<T> &sptr)"<<endl;
	}
	~SmartPointer()
	{
		//Destroying a reference to the object. Decrement ref_count. If ref_count is 0, then free the memory created by the interger and destroy the object.
		remove();//remove one reference to object.
		cout<<"~SmartPointer(SmartPointer<T> sptr)"<<endl;
		getchar();
	}
	SmartPointer<T> &operator=(SmartPointer<T> &sptr)
	{
		cout<<"operator="<<endl;
		// Override the =, If sptr has an existing value, decrement its reference count. Then, copy the pointers to obj and ref_count over.
		// Finally, since we created a new reference, we need to increment ref_count.
		if(this == &sptr)
			return *this;
		//if already assigned to an object, remove one reference.
		if(*ref_count > 0)
			remove();
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
		return *this;
	}
	T getValue()
	{
		return *ref;
	}	
};

//10.4 Find OS is big and small endian storage
void showMemRep()
{
	unsigned int i =1;
	char *c = (char*)&i;
	if(*c)
		printf("little endian");
	else
		printf("big endian");
	getchar();
}

//10.5 Write a function called my2DAlloc which allocates a two dimensional array. Minimize the number of calls to malloc and make sure that the memory is accessible by the notation arr[i][j].
int **my2DAlloc(int row, int col)
{
	int **arr = new int*[row];
	for(int i=0; i<row; ++i)
	{
		arr[i] = new int[col];
		memset(arr[i], 0, sizeof(int)*col);
	}
	return arr;
}
int **my2DAlloc1(int row, int col)
{	
	int **arr = (int **)malloc(sizeof(int*)*row+sizeof(int)*row*col);
	for(int i=0; i<row; ++i)
	{
		arr[i] = (int*)(arr+row+i*col);
	}
	return arr;
}

//10.6 Write an aligned molloc and free fnction that supports allocating memory such that the memory address returned is divisible by a specific power of two.
void *aligned_malloc(size_t required_bytes, size_t alignment)
{
	void *po;//original block
	void **pa;//aligned block
	int offset = alignment - 1 + sizeof(void*);//alignment-1 for divid by power 2, sizeof(void*) for save po.
	if((po = (void*)malloc(required_bytes + offset)) == NULL)
		return NULL;
	pa = (void**)(((size_t)(po) + offset) & ~(alignment-1));
	pa[-2] = po;
	return pa;
}
void aligned_free(void *pa)
{
	void *po = ((void**)pa)[-2];
	free(po);
}

//10.7 Diamond problem
class Animal
{
	friend class Mule;
public:
	Animal()
	{
		cout<<"Animal constructor"<<endl;
	}
	~Animal(){}
	virtual void eat()
	{
		cout<<"animal eat()"<<endl;
	}
private:
	void drink()
	{cout<<"animal all drink water."<<endl;}
};
class Horse : virtual public Animal
{
public:
	Horse(){
	cout<<"Horse constructor"<<endl;}
	~Horse(){}
	virtual void eat()
	{
		cout<<"Horse eat grass."<<endl;
	}
};
class Donkey : virtual public Animal
{
public:
	Donkey(){
		cout<<"Donkey constructor"<<endl;}
	~Donkey(){}
	virtual void eat()
	{cout<<"Donkey eat grass too."<<endl;}
};
class Mule
{
	
public:
	Mule(){
		cout<<"Mule constructor"<<endl;}
	~Mule(){}
	virtual void eat()
	{cout<<"Mule eat grass 2 2."<<endl;}
	void muleEat()
	{Animal a;
	a.drink();
		cout<<"Mule eat milk."<<endl;}
};

//10.8 Elevator Simulator Design
http://www.angelfire.com/trek/software/elevator.html

//10.9 Give student result structure: 给一个result的vector，返回一个map<ID, 最高5次平均分>
struct Result
{
	int studentID;
	string data;
	int testScore;
};
typedef vector<Result> vecStudentResult;
typedef map<int,double> mapStudentAverage;
bool comapreIDScore(Result a, Result b)
{
	if(a.studentID == b.studentID)
		return a.testScore > b.testScore;
	else
		return a.studentID < b.studentID;
}
mapStudentAverage getAverageScore(vecStudentResult &vsr,mapStudentAverage &msa)
{
	static int testTime = 0;
	sort(vsr.begin(),vsr.end(),comapreIDScore);
	mapStudentAverage::iterator imsa;
	for(unsigned int i=0; i<vsr.size(); ++i)
	{
		imsa = msa.find(vsr[i].studentID);
		if(imsa == msa.end())
		{
			msa[vsr[i].studentID] = vsr[i].testScore;
			testTime = 1;
		}
		else
		{
			++testTime;
			if(testTime <= 2)
			{
				msa[vsr[i].studentID] = (msa[vsr[i].studentID]*(testTime-1) + vsr[i].testScore)/testTime;				
			}			
		}			
	}
	return msa;
}
int main()
{
	const int num = 2;
	int duplitime = 3;

	vecStudentResult vsr;
	mapStudentAverage msa, msa2;
	Result res;
	while(duplitime--)
	{
		for(int i=1; i<=num; ++i)
		{		
			res.studentID = i;
			res.data = "C++ Program Class";
			res.testScore = rand()%100;
			vsr.push_back(res);
		}
	}
	res.studentID = 3;
	res.data = "C++ Program Class";
	res.testScore = rand()%100;
	vsr.push_back(res);
	res.studentID = 4;
	res.data = "C++ Program Class";
	res.testScore = rand()%100;
	vsr.push_back(res);
	res.studentID = 4;
	res.data = "C++ Program Class";
	res.testScore = rand()%100;
	vsr.push_back(res);

	msa2 = getAverageScore(vsr, msa);
	
	return 0;
}

//10.10 Singleton OOD --http://www.yolinux.com/TUTORIALS/C++Singleton.html
/*a. This design pattern and methodology ensures that only one instance of the C++ class is instantiated. It assures that only one object is created and no more. 
It is often used for a logging class so only one object has access to log files, or when there is a single resource, where there should only be a single object in charge of accessing the single resource.
1. That the instance function returns a pointer to a static variable and thus is declared static.
2. Only the class function Instance can call the constructor. Public access to the constructor is denied.
3. The constructor, copy constructor and assignment operator are all private to ensure that the programmer using the singleton class can only create a single instance of the class using only the Instance() function.
4. The life of the singleton instantiation is for the duration of the application.*/
class Logger//logger.h, Logger is Singleton
{
public:
	static Logger* Instance();
	bool openLogFile(string logFile);
	void writeToLogFile();
	bool closeLogFile();
	int data;
private:
	Logger(){}// Private so that it can  not be called
	Logger(Logger const&){}// copy constructor is private
	Logger& operator=(Logger const&){}// assignment operator is private
	static Logger* m_pInstance;
};
//logger.cpp, Global static pointer used to ensure a single instance of the class.
Logger* Logger::m_pInstance = NULL;
// This function is called to create an instance of the class. Calling the constructor publicly is not allowed. The constructor is private and is only called by this Instance function.
Logger* Logger::Instance()
{
	if(m_pInstance == NULL)// Only allow one instance of class to be generated.
		m_pInstance = new Logger;
	return m_pInstance;
}
//usage
Logger* pl = Logger::Instance(); pl->data = 10;//	Logger* p2 = Logger::Instance();	p2->data = 20;

//b. C++ Singleton class using inheritance:
//Singleton base class, base.h
class sBase
{
public:
	static sBase* instance();
	static bool exists();
	inline int getDataX(){return mDataX;}
	inline void setDataX(int a){	mDataX = a;}
	virtual int getDataY() = 0;
	virtual void setDataY(int a) = 0;
protected:
	sBase(int a);
	virtual ~sBase(){}
	static sBase* mBaseInstance;
private:
	int mDataX;
};
//base.cpp, Global initialization to facilitate singleton design pattern
sBase* sBase::mBaseInstance = NULL;
sBase::sBase(int init)
{
	mDataX= init;
}
bool sBase::exists()
{
	return (mBaseInstance != NULL);
}
sBase* sBase::instance()
{
	if(mBaseInstance == NULL)
		cout<<"Class has not been created." <<endl;
	return mBaseInstance;
}
//derived.h
class sDerived : public sBase
{
public:
	static void create(int, int);
	virtual inline int getDataY(){return mDataY;}
	virtual inline void setDataY(int a){mDataY = a;}
protected:
	sDerived(int, int);// Can't be called by non-member functions
	virtual ~sDerived(){}// Can't be called by non-member functions
private:
	int mDataY;
};
//derived.cpp
sDerived::sDerived(int initX, int initY) : sBase(initX)
{
	mDataY = initY;
}
void sDerived::create(int initX, int initY)
{
	if(mBaseInstance != NULL)
		cout<<"Singleton has already been created"<<endl;
	else
		mBaseInstance = new sDerived(initX, initY);
}
//usage,The functions create() and instance() are defined as static functions in the class definitions. 
//Note that static member functions do not have a this pointer as they exist independent of any objects of a class.
sDerived::create(1,2); 	sBase *psd = sDerived::instance();	psd->setDataX(30);

//c. The Template Singleton class:
template<class T> class Singleton
{
public:
	static T* instance()
	{
		if(pInstance == NULL)
			pInstance = new T;
		assert(pInstance != NULL);
		return pInstance;
	}
protected:
	Singleton();
	~Singleton();
private:
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
	static T* pInstance;
};
template<class T> T* Singleton<T>::pInstance = NULL;

//d. Implement a singleton design pattern as a template such that, for any given class Foo, you can call Singleton::instance() and get a pointer to an instance of a singleton of type Foo. Assume the existence of a class Lock which has acquire() and release() methods. How could you make your implementation thread safe and exception safe?
class Lock//lock of thread
{
public:
	Lock(){}
	~Lock(){}
	void acquire(){}
	void release(){}
};
template<typename T> class Singleton
{
private:
	static Lock lock;
	static T *obj;
protected:
	Singleton(): obj(NULL){}
public:
	static T* instance()
	{
		if(obj == NULL)
		{
			//initial and lock
			lock.acquire();
			//这里再判断一次，因为多个线程可能同时通过第一个if, 只有第一个线程去实例化object，之后object非NULL, 后面的线程不再实例化它
			if(obj == NULL)
			{
				obj = new T;
			}
			lock.release();
		}
		return obj;
	}
};
class Foo{};
Foo *singleton_foo = Singleton<Foo>::instance();

//10.11 Peterson’s Algorithm, Guarantees mutual exclusion and protects against Deadlock and Livelock. 
//The algorithm uses two variables, flag and turn. A flag[n] value of true indicates that the process n wants to enter the critical section. Entrance to the critical section is granted for process P0 if P1 does not want to enter its critical section or if P1 has given priority to P0 by setting turn to 0.
void Peterson2Process()
{
	bool flag[2] = {false};
	int turn = 0;
	//Process 0
	flag[0] = true;
	turn = 1;
	while(flag[1] == true && turn == 1)
	{
		//busy wait
	}
	//execute critical section
	//end critical section
	flag[0] = false;
	//process 1
	flag[1] = true;
	turn = 0;
	while(flag[0] == true && turn == 0)
	{	
		//busy wait
	}
	//execute critical section
	//end critical section
	flag[1] = false;
}
void Peterson()
{
	// initialization
	level[N] = { -1 };     // current level of processes 0...N-1
	waiting[N-1] = { -1 }; // the waiting process of each level 0...N-2
	// code for process #i
	for(l = 0; l < N-1; ++l)
	{
		level[i] = l;
		waiting[l] = i;
		while(waiting[l] == i && (there exists k ≠ i, such that level[k] ≥ l)) 
		{
			// busy wait
		}
	}
	// critical section
	level[i] = -1; // exit section
}

//10.12 Operator Overloading
//a. less than < ,Comparison operator for table sorting.(as a member function)
bool Complex::operator<(const Complex& param) const
{
	if (keyA < param.keyA) return true;
	if (keyA > param.keyA) return false;
	if (keyB < param.keyB) return true;
	if (keyB > param.keyB) return false;
	if (keyC < param.keyC) return true;
	if (keyC > param.keyC) return false;
	return false;
}

//10.13 Concurrency -- Threads
http://baptiste-wicht.com/posts/2012/03/cpp11-concurrency-part1-start-threads.html

//Semaphore
struct semaphore
{
	int value;
	queue L;// list of processes
};
wait(s)
{
	if (s.value > 0)
		--s.value;
	else
	{
		add this process to s.L;
		block;
	}		
}
signal(s)
{
	if (s.L != empty())
	{
		remove a process P from s.L;
		wakeup(P)
	}
	else
		++s.value;
}