//7.1 Random algorithm 对于整数m和n，其中m<n，输出0~n-1范围内m个随机整数的有序列表，不允许重复
//a. Knuth的TAOCP，time O(n)
void GenKnuth(int m, int n)
{
	for(int i=0; i<n; ++i)
	{
		int r = rand();
		if((r%(n-i)) < m)
		{
			cout<<i<<endl;
			--m;
		}
	}
}
//b. 在一个初始为空的集合里面插入随机整数，直到个数足够
void insertRandom(int m, int n)
{
	set<int,greater<int>> si;
	while(si.size() < m)
		si.insert(rand()%n);
	set<int,less<int>>::iterator i;
	for(i = si.begin(); i!=si.end(); ++i)
		cout<<*i<<" ";
}

//7.2 Shuffle a given array or random poke shuffle
//我们先假设一个5维数组：1，2，3，4，5。如果第1次随机取到的数是4， 那么我们希望参与第2次随机选取的只有1，2，3，5。既然4已经不用， 我们可以把它和1交换，第2次就只需要从后面4位(2,3,1,5)中随机选取即可。同理， 第2次随机选取的元素和数组中第2个元素交换，然后再从后面3个元素中随机选取元素， 依次类推
void randomshuffle(int a[],int n)
{	
	for(int i=0; i<n; ++i)
	{
		int j = rand()%(n-i)+i;// +i = 确保前面洗好的数据不变
		swap(a[i], a[j]);
	}
}
// random pick up M item from N from an array. 选出的m个数放到数组前m个位置
void pickMRandomN(int a[], int n, int m)
{
	for(int i=0;i<m;++i)
	{
		int j = rand()%(n-i) + i;
		swap(a[i], a[j]);
	}
}
//b. Fisher Yates算法
void FisherYate(int a[], int n)
{
	srand(time(null));// Use a time seed value
	// Start from the last element and swap one by one. We don't need to run for the first element that's why i > 0
	for(int i=n-1; i>0; --i)
	{
		int j = rand()%(i+1);
		swap(a[i], a[j]);
	}
}

//7.3 Write a method to generate a random number between 1 and 7, given a method that generates a random number between 1 and 5 (i.e., implement rand7() using rand5())
int random7()
{
	int x = INT_MAX;
	while(x>21)
		x = 5*(random5()-1)+random5();
	return x%7+1;
}
//less invoke rand()
int rand10()//less call rand7()
{
	int a, b, idx;
	while (true)
	{
		a = rand7();
		b = rand7();
		idx = b + (a - 1) * 7;//1-49
		if (idx <= 40)
			return 1 + idx % 10;
		a = idx - 40;
		b = rand7();
		idx = b + (a - 1) * 7;//1-63
		if (idx <= 60)
			return 1 + idx % 10;		
	}
}

//General swap replacement good for all conditions
void pswap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
	cout<<"a = "<<*a<<", b = "<<*b<<endl;
}
//not use 3rd variable, only + -
void dswap(int &a, int &b)
{
	a = a + b;
	b = a - b;
	a = a - b;
	cout<<"a = "<<a<<", b = "<<b<<endl;
}
//use ^ xor， a and b can't be same variable
void aswap(int &a, int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
	cout<<"a = "<<a<<", b = "<<b<<endl;
}

//Math.1 a. only use + to do the -,*, / functions
int flipsign(int a)
{
	int d = (a<0?1:-1);
	int opa = 0;
	while(a!=0)
	{
		a+=d;
		opa+=d;
	}
	return opa;
}
int abs(int a)
{
	if(a<0)
		a = flipsign(a);
	return a;
}
bool opsign(int a, int b)
{
	return (a>0 && b<0) || (a<0 && b>0);
}
int times(int a, int b)
{
	int aa = abs(a), bb = abs(b);
	int res = 0;
	if(aa<bb)
		swap(aa,bb);
	for(int i=0;i<bb;++i)
		res+=aa;
	if(opsign(a,b))
		res = flipsign(res);
	return res;
}
int minus(int a, int b)
{
	return a + flipsign(b);
}
int divide(int a, int b)
{
	if(b==0)
		return 0;
	int aa=abs(a), bb=b;
	if(b>0)
		bb=flipsign(b);
	int res=0;
	while((aa+=bb)>=0)
		res++;
	if(opsign(a,b))
		res = flipsign(res);
	return res;
}

//Divide two integers without using multiplication, division and mod operator, 时间复杂度O(logn)，空间复杂度O(1)
int divide(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	// 当a = INT_MIN 时，-a 会溢出，所以用long long
	long long x = a > 0 ? a : -a;
	long long y = b > 0 ? b : -b;
	long long res = 0;//当dividend = INT_MIN 时，divisor = -1 时，结果会溢出, so use long long
	while (x >= y)
	{
		long long c = y;
		for (int i = 0; x >= c; ++i, c <<= 1)
		{
			x -= c;
			res += 1 << i;
		}
	}
	return (a^b >> 31) ? (-res) : res;
}

//b. no + signal sum
int recuaddXOR(int a, int b)//recursion
{
	if(b == 0)
		return a;
	int sum = a ^ b;
	int carry = (a&b)<<1;
	int mask = 0x40000000;
	cout<<"binary = ";
	int flag = 0;
	while(mask)
	{
		if(mask&sum)
		{
			cout<<"1";
			flag = 1;
		}
		else
		{
			if(flag)
				cout<<"0";
		}
		mask>>=1;
	}
	cout<<endl;
	cout<<"carry = ";
	mask = 0x40000000;
	flag=0;
	while(mask)
	{

		if(mask&carry)
		{
			cout<<"1";
			flag = 1;
		}
		else
		{
			if(flag)
				cout<<"0";
			if(carry == 0)
			{
				cout<<"0";
				break;
			}
		}
		mask>>=1;
	}
	cout<<endl;
	cout<<"sum = "<<sum<<", carry = "<<carry<<endl;
	return add(sum,carry);
}
int addXOR(int a, int b)
{
	int sum = 0, carry = 0;
	while(b != 0)
	{
		sum = a ^ b;
		carry = (a&b)<<1;
		a = sum;
		b = carry;
	}
	return a;
}
int addChar(int a, int b)
{
	char *c = (char*)a;
	int s = (int)&c[b];
	return s;
}

//c. Write a method which finds the maximum of two numbers. You should not use if-else or any other comparison operator.
int maximum(int a, int b)
{
	return (a == b+abs(a-b))? a:b;
}
int maximum2(int a, int b)
{
	int k = a - b;
	return a - k*((k>>31)&1);
}

//Math.2 Given a two dimensional graph with points on it, find a line which passes the most number of points.
struct Point
{
	double x, y;
};
class line
{
public:
	double epsilon, slope, intercept;
	bool bslope;
	line(){}
	line(Point p, Point q)
	{
		epsilon = 0.0001;
		if(abs(p.x-q.x) > epsilon)
		{
			slope = (p.y-q.y)/(p.x-q.x);
			intercept = p.y - slop* p.x;
			bslope = true;
		}
		else
		{
			bslope = false;
			intercept = p.x;
		}
	}
	~line(){}
	int hashcode()
	{
		int sl = (int)(slope * 1000);
		int in = (int)(intercept * 1000);
		return sl*1000+in;
	}
	void print()
	{
		cout<<"y = "<<slope<<"x + "<<intercept<<endl;
	}
};
//line l = find_best_line(p, point_num);  l.print();
line findBaseLine(Point *p, int n)
{
	line baseline;
	bool first = true;
	map<int, int> mii;
	for(int i=0; i<n; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			line l(p[i],p[j]);
			if(mii.find(l.hashcode()) == mii.end())
				mii[l.hashcode()] = 0;
			else
				mii[l.hashcode()] += 1;
			if(first)
			{
				baseline = l;
				first = false;
			}
			else
			{
				if(mii[l.hashcode()] > mii[baseline.hashcode()])
					baseline = l;
			}
		}
	}
	return baseline;
}

// 暴力枚举法，以边为中心，时间复杂度O(n^3)，空间复杂度O(1),两点决定一条直线，n 个点两两组合，可以得到n*(n-1)/2条直线，对每一条直线，判断n 个点是否在该直线上，从而可以得到这条直线上的点的个数，选择最大的那条直线返回。
int maxPoints(vector<Point> &points)
{
	const int n = points.size();
	if (n < 3)
		return n;
	int result = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			int sign = 0, a = 0, b = 0, c = 0;
			if (points[i].x == points[j].x)
				sign = 1;
			else
			{
				a = points[j].x - points[i].x;
				b = points[j].y - points[i].y;
				c = a*points[i].y - b*points[i].x;
			}
			int count = 0;
			for (int k = 0; k < n; ++k)
			{
				if ((sign == 0 && a * points[k].y == b * points[k].x + c) || (1 == sign && points[k].x == points[j].x))
					++count;
			}
			if (count > result)
				result = count;
		}
	}
	return result;
}
// 暴力枚举，以点为中心，时间复杂度O(n^2)，空间复杂度O(n)
int maxPoints(vector<Point> &points)
{
	const int n = points.size();
	if (n < 3)
		return n;
	int result = 0;
	unordered_map<double, int> slope;
	for (int i = 0; i < n - 1; ++i)
	{
		slope.clear();
		int samePoint = 0, maxPoint = 0;//
		for (int j = i + 1; j < n; ++j)
		{
			double k;//slope
			if (points[i].x == points[j].x)
			{
				k = numeric_limits<double>::infinity();
				if (points[i].y == points[j].y)
				{
					++samePoint;
					continue;
				}
			}
			else
				k = 1.0*(points[i].y - points[j].y) / (points[i].x - points[j].x);
			int cnt = 0;
			if (slope.find(k) != slope.end())
				cnt = ++slope[k];
			else
			{
				cnt = 2;
				slope[k] = 2;
			}
			if (maxPoint < cnt)
				maxPoint = cnt;
		}
		result = max(result, samePoint + maxPoint);
	}
	return result;
}

//Math.3 Design an algorithm to find the kth number such that the only prime factors are 3, 5, and 7.
//1. 初始化结果res=1和队列q3,q5,q7 2. 分别往q3,q5,q7插入1*3,1*5,1*7 3. 求出三个队列的队头元素中最小的那个x，更新结果res=x
//4. 如果x在：    q3中，那么从q3中移除x，并向q3，q5，q7插入3*x,5*x,7*x     q5中，那么从q5中移除x，并向q5，q7插入5*x,7*x     q7中，那么从q7中移除x，并向q7插入7*x 5. 重复步骤3－5，直到找到第k个满足条件的数.当x出现在q5中，我们没往q3中插入3*x，那是因为这个数在q5中已经插入过了
int get357KthNum(int k)
{
	if(k <= 0)
		return 0;
	int res = 1, cnt = 1;
	queue<int> q3, q5, q7;
	q3.push(3);
	q5.push(5);
	q7.push(7);
	for(cnt=1; cnt<k; ++cnt)
	{
		int v3 = q3.front();
		int v5 = q5.front();
		int v7 = q7.front();
		res = min(min(v3, v5), v7);
		if(res == v7)
			q7.pop();
		else
		{
			if(res == v5)
				q5.pop();
			else
			{
				if(res == v3)
				{
					q3.pop();
					q3.push(3*res);
				}
			}
			q5.push(5*res);
		}
		q7.push(7*res);
	}
	return res;
}

//Math.4 the number of trailing zeros in n factorial.
int numZeroInFactorial(int n)
{
	if(n < 0)
		return -1;
	int num = 0;
	while((n /= 5) > 0)
		num += n;
	return num;
}

//Math.5 count how many i in a number
//brute force time O(nlogn)
int count2(int n)//time O(logn)
{
	int cnt = 0;
	while(n > 0)
	{
		if(n%10 == 2)
			++cnt;
		n /= 10;
	}
	return cnt;
}
int count2sFN(int n)
{
	int cnt = 0;
	for(int i=0;i<=n;++i)
		cnt += count2(i);
	return cnt;
}

// b. 当某一位的数字小于2时，那么该位出现2的次数为：更高位数字*当前位数, 
// 当某一位的数字等于2时，那么该位出现2的次数为：更高位数字x当前位数+低位数字+1, 
// 当某一位的数字大于2时，那么该位出现2的次数为：(更高位数字+1)x当前位数
int count2s(int n)
{
	int con = 0, fac = 1;
	int low = 0, cur = 0, high = 0;
	while(n/fac)
	{
		low = n - (n/fac)*fac;//low number
		cur = (n/fac)%10;
		high = n/(fac*10);
		switch(cur)
		{
		case 0:
		case 1:
			con += high*fac;
			break;
		case 2:
			con += high*fac + low +1;
			break;
		default:
			con +=(high +1)*fac;
			break;
		}
		fac *= 10;
	}
	return con;
}
int countKinN(int n, int k)// 1<=k<=9
{
	if(k < 1 || k > 9 || n < 1)
		return 0;
	int countK = 0, i = 0, cur = n, time = 1;
	while(cur > 0)
	{
		i = cur%10;
		cur /= 10;		
		if(i < k)
			countK += cur*time;
		else if(i == k)
		{
			countK += cur*time + n%time + 1;
		}
		else
		{
			countK += (cur+1)*time;
		}
		time *= 10;
	}
	return countK;
}

//Math.6 find primes in val, 最小的素数是2，也是素数中唯一的偶数；其他素数都是奇数
void prime(int val)
{
	if(val < 2)//最小的素数是2，也是素数中唯一的偶数；其他素数都是奇数
		return;
	else if(val == 2)
	{
		cout<<" 2 "<<endl;
		return;
	}
	else//val > 2
	{
		int divd = 0;
		for(int i=2; i<=val; ++i)
		{
			divd = 0;
			for(int j=2; j<i; ++j)
			{
				divd += !(i%j);
				if(divd > 0)
					break;				
			}
			if(divd == 0)
				cout<<i<<" ";					
		}
	}
}
// Generate a prime list from 0 up to n, using The Sieve of Erantosthenes param, n The upper bound of the prime list (including n) param prime[] An array of truth value whether a number is prime
void prime2n(int n, bool prime[])
{
	prime[0] = false;
	prime[1] = false;
	for (int i = 2; i <= n; ++i)
		prime[i] = true;
	int limit = sqrt(n);
	for (int i = 2; i <= limit; ++i)
	{
		if (prime[i])
		{
			for (int j = i*i; j <= n; j += i)
				prime[j] = false;
		}
	}
	for (int i = 2; i <= n; ++i)
	{
		if (prime[i])
			cout << i << ", ";
	}

}

//Math.7 Greatest Common Divisor最大公约数, Lowest Common Multiple最小公倍数
int GCD(int a, int b)//Greatest Common Divisor最大公约数
{
	int r = 0;//remainder余数,quotient商
	if(a < b)
		swap(a, b);
	while((r = a%b) > 0)
	{
		a = b;
		b = r;
	}
	return b;
}
int LCM(int a, int b)//LCM * GCD = a * b
{
	if(a < 1 || b < 1)
		return 0;
	return a*b/GCD(a, b);
}

/*Math.8 Imagine you have a special keyboard with the following keys:A, CTRL+A, CTRL+C, CTRL+V and last 3 each acts as one function key for “Select All”, “Copy”, and “Paste” operations respectively.
If you can only press the keyboard for N times (with the above four keys), please write a program to produce maximum numbers of A. If possible, please also print out the sequence of keys.
That is to say, the input parameter is N (No. of keys that you can press), the output is M (No. of As that you can produce).
1.  N <= 7, M = N. 2. For N = 8 the answer is M = 9, where S = { A, A, A, CTRL+A, CTRL+C, CTRL+V, CTRL+V, CTRL+V }.
For N = 9 the answer is M = 12, where S = { A, A, A, CTRL+A, CTRL+C, CTRL+V, CTRL+V, CTRL+V, CTRL+V }.
Define 4A as a sequence of { A, A, A, A }. Therefore, 5A would then mean { A, A, A, A, A }.
Define 2D as a sequence of CTRL+A, CTRL+C, CTRL+V, CTRL+V, which simply means double the previous text. Note that 3D does not double the previous text, it actually triples the previous text.
The solution so far for N > 7 is to find integers a and b such that ab yields the largest product, subjected to the condition where a+b = N-2.
Both a and b are easy to find, as the largest product is found when the difference of a and b is less than or equal to one.
M = MAX (a1*a2*…*ak), where a1 + a2 + … + ak = n – 2(k-1), To obtain M = MAX (a1*a2*…*ak), it is necessary that the condition "∀ i, j ∈{ 1, 2, … , k } : MAX ( | ai – aj | ) = 1." must be met*/
//brute force
int maxK(int n)
{
	int k = 0, power = 2;
	double max = 0.0;
	while (n > 0)
	{
		n -= 2;
		double t = (double)n / power;
		double r = pow(t, (double)power);
		if (r > max)
		{
			k = power;
			max = r;
		}
		++power;
	}
	return k;
}
unsigned int maxA(int n)
{
	assert(n >= 0);
	if (n <= 7)
		return n;
	int k = maxK(n);
	int sum = n - 2 * (k - 1);
	unsigned int m = 1;
	while (k > 0)
	{
		int avg = sum / k;
		m *= avg;
		--k;
		sum -= avg;
	}
	assert(sum == 0);
	return m;
}

/*Math.9 A double-square number is an integer X which can be expressed as the sum of two perfect squares. For example, 10 is a double-square because 10 = 32 + 12.
Your task in this problem is, given X, determine the number of ways in which it can be written as the sum of two squares. For example, 10 can only be written
as 32 + 12 (we don’t count 12 + 32 as being different). On the other hand, 25 can be written as 52 + 02 or as 42 + 32.*/
int doubleSquare(unsigned int x)//int range is -2147483648 - 2147483647
{
	int total = 0;
	int iUp2 = (int)sqrt((double)x / 2.0);
	for (int i = 0; i <= iUp2; ++i)
	{
		unsigned int i2 = i * i;
		for (int j = i;; ++j)
		{
			unsigned int sum = i2 + j * j;
			if (sum == x)
			{
				++total;
				cout << i << "^2 + " << j << "^2 = " << x << endl;
			}
			else if (sum > x)
				break;
		}
	}
	return total;
}
int square2(int x)//
{
	int n = 0;
	int imax = sqrt((double)x / 2.0);
	for (int i = 0; i <= imax; ++i)
	{
		double j = sqrt((double)x - i*i);
		if (j - (int)j == 0.0)
		{
			++n;
			cout << i << "^2 + " << j << "^2 = " << x << endl;
		}
	}
	return n;
}

//Math.10 任何整数必定能分解成2的幂之和，给定整数n，求n的此类分解方法的数量, DP f(1) = 1, f(2m+1) = f(2m), f(2m) = f(2m-1) + f(m)
int powerNumBy2(int n)
{

	int *a = new int[n + 1];
	memset(a, 0, sizeof(int)*(n + 1));
	a[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (i % 2)
			a[i] = a[i - 1];
		else
			a[i] = a[i - 1] + a[i / 2];
	}
	int max = a[n];
	delete[] a;
	return max;
}

//Math.11 Given a list of positive integers: t1, t2, …, tn, and ti != tj for some i, j. Find the smallest integer y >= 0 such that each ti + y is divisible by an integer T. T must be the largest of all possible divisors.
long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);//a > b
}
long long gcdarr(long long arr[], int n)
{
	long long temp = arr[0];
	for (int i = 1; i < n; ++i)
		temp = gcd(temp, arr[i]);
	return temp;
}
long long getY(long long arr[], int n)
{
	sort(arr, arr + n);
	int index = 0;
	long long *minus = new long long[n*n];
	memset(minus, 0, sizeof(long long)*(n*n));
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
			minus[index++] = arr[i] - arr[j];
	}
	long long T = gcdarr(minus, index);
	long long y = (ceil((double)arr[0] / T)) * T - arr[0];
	return y;
}

//Math.12 Given a 2D point and a rectangle, determine if the point is inside the rectangle.
// 功能：判断点是否在多边形内, 方法：求解通过该点的水平线与多边形各边的交点, 结论：单边交点为奇数，成立! 
bool inRec(Point p, Point rec[], int n)// POINT p 指定的某个点 , LPPOINT ptPolygon 多边形的各个顶点坐标（首末点可以不一致）, int nCount 多边形定点的个数 
{
	int cross = 0;
	for (int i = 0; i < n; ++i)
	{
		Point p1 = rec[i];
		Point p2 = rec[(i + 1) % n];
		// find y = p.y 与p1p2的交点
		if (p1.y == p2.y)//y = p.y 与 p1p2 平行
			continue;
		if (p.y < min(p1.y, p2.y))// 交点在p1p2延长线上 
			continue;
		if (p.y > max(p1.y, p2.y))// 交点在p1p2延长线上 
			continue;
		// 求交点的 X 坐标
		double x = (p.y - p1.y)*(p2.x - p1.x) / (p2.y - p1.y) + p1.x;
		if (x > p.x)
			++cross;
	}
	return (cross % 2 == 1);// 单边交点为偶数，点在多边形之外
}

//Math.13 a. Implement pow(x, n). 二分法，x^n = x^{n/2} * x^{n/2} * x^{n\%2}, 时间复杂度O(logn)，空间复杂度O(1)
class Solution
{
public:
	double pow(double x, int n)
	{
		if (n < 0)
			return 1.0 / power(x, -n);
		else
			return power(x, n);
	}
private:
	double power(double x, int n)
	{
		if (n == 0)
			return 1;
		double v = power(x, n / 2);
		if (n % 2 == 0)
			return v * v;
		else
			return v * v * x;
	}
};

//b. Implement int sqrt(int x).二分查找, 时间复杂度O(logn)，空间复杂度O(1)
int sqrt(int x)
{
	assert(x >= 0);
	int left = 1, right = x / 2;
	int lastMid = 0; //record last mid
	if (x < 2)
		return x;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (x / mid > mid)
		{
			left = mid + 1;
			lastMid = mid;
		}
		else if (x / mid < mid)
			right = mid - 1;
		else
			return mid;
	}
	return lastMid;
}
