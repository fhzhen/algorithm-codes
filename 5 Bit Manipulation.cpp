//5.1 You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method to set all bits between i and j in N equal to M (e.g., M becomes a substring of N located at i and starting at j).
//Input: N = 10000000000, M = 10101, i = 2, j = 6. Output: N = 10001010100
int setNbyM(int n, int m, int i, int j)
{
	if(i > j)
	{
		cout<<"i should be minor than j."<<endl;
		return 0;
	}
	for(int a=i; a<=j; ++a)
	{
		if((m & 1) == 1)
			n |= 1<<a;
		else
			n &= ~(1<<a);
		m >>= 1;
	}
	return n;
}

//5.2 Given a (decimal - e.g. 3.72) number that is passed in as a string, print the binary representation.If the number can not be represented accurately in binary, print “ERROR”.
string getBinary(string str)
{
	int neg = 0;
	if(str.front() == '-')
	{
		str.erase(0,1);
		neg = 1;
	}
	else if(str.front() == '+')
		str.erase(0,1);
	int pos = str.find('.');
	int intpart = atoi(str.substr(0, pos).c_str());
	double decpart = atof(str.substr(pos).c_str());
	string intstr = "", decstr = "";
	while(intpart > 0)
	{
		if(intpart & 1 == 1)
			intstr = "1" + intstr;
		else
			intstr = "0" + intstr;
		intpart >>= 1;
	}
	while(decpart > 0)
	{
		if(decstr.length() > 32)
			return "ERROR";
		decpart *= 2;
		if(decpart >= 1)
		{
			decstr += "1";
			decpart -= 1;
		}
		else
			decstr += "0";
	}
	return intstr + "." + decstr;
}

//5.3 Given an integer, print the next smallest and next largest number that have the same number of 1 bits in their binary representation.
// 给定一个整数x，找出另外两个整数，这两个整数的二进制表示中1的个数和x相同， 其中一个是比x大的数中最小的，另一个是比x小的数中最大的
int countOne(int num)
{
	int cnt = 0;
	for(int i=0; i<32; ++i)
	{
		if((num & 1) == 1)
			++cnt;
		num >>= 1;
	}
/*	while(num != 0)
	{
		num &= (num-1);
		++cnt;
	}*/
	return cnt;
}
int bigger(int num)
{
	int pre = num;
	int bit = 0;
	while((num & 1) != 1 && bit < 32)
	{
		++bit;
		num >>= 1;
	}
	while((num & 1) != 0 && bit < 32)
	{
		++bit;
		num >>= 1;
	}
	if(bit == 31)//011... return -1
		return -1;
	else if(bit == 32) // for 11000...
		num = 0;
	else
	{
		num |= 1;
		num <<= bit;
	}
	int res = countOne(pre) - countOne(num);
	int cur = 1;
	while(res > 0)
	{
		num |= cur;
		cur <<= 1;
		--res;
	}
	return num;
}
int smaller(int num)
{
	int pre = num, bit = 0;
	while((num & 1) != 0 && bit < 32)
	{
		num >>= 1;
		++bit;
	}
	while((num & 1) != 1 && bit < 32)
	{
		num >>= 1;
		++bit;
	}
	if(bit == 31)// 100...11
		return -1;
	else if(bit == 32)
		num = 0;
	else
	{
		num -= 1;
		num <<= bit;
	}
	int res = countOne(pre) - countOne(num);//get gap No. of 1
	num >>= bit;
	while(res > 0)
	{
		num = (num<<1) | 1;
		--res;
		--bit;
	}
	while(bit > 0)
	{
		num <<= 1;
		--bit;
	}
	return num;
}
int smaller2(int num)
{
	int cnt = countOne(num);
	if(cnt == 0 || num == -1)
		return -1;
	int cur = num - 1;
	while(countOne(cur) != cnt && cur > INT_MIN)
		--cur;
	if(countOne(cur) == cnt)
		return cur;
	return -1;
}

//5.4 a. Write a function to determine the number of bits required to convert integer A to integer B.
//从整数A变到整数B，所需要修改的就只是A和B二进制表示中不同的位， 先将A和B做异或，然后再统计结果的二进制表示中1的个数即可
int needBit(int a, int b)
{
	int xor = a^b;
	int cnt = 0;
	while(xor != 0)
	{
		xor &= (xor-1);
		++cnt;
	}
	return cnt;
}

//b. Count the ones in a integer. Determine within constant time.
int onesnum(int val)//only for 32 bit
{
	int bitset[256] = {0};//bitset[val] = cnt, cnt is 1's count in val
	int cnt = 0;
	for(int i=1; i<256; ++i)
		bitset[i] = (i&1)+bitset[i/2];
	cnt = bitset[val&0xFF] + bitset[(val>>8)&0xFF] + bitset[(val>>16)&0xFF] + bitset[val>>24];
	return cnt;
}

//5.5 a.Write a program to swap odd and even bits in an integer with as few instructions as possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, etc).
int swapBit(int num)
{
	return ((num & 0x55555555) << 1) | ((num >> 1) & 0x55555555);
}

//b. swap the ith bit with the jth bit of an unsigned integer.
typedef unsigned int  uint;
uint swapBits(uint x, uint i, uint j)
{
	uint lo = ((x >> i) & 1);
	uint hi = ((x >> j) & 1);
	if(lo ^ hi == 1)
		x ^= (1 << i || 1 << j);
	return x;
}
//c. Reverse bits of an unsigned integer, time O(n)
uint reverseXor(uint x)
{
	uint n = sizeof(x)*8;
	for(uint i=0; i<n/2; ++i)
		x = swapBits(x, i, n-i-1);
	return x;
}
//like mearge sort, time O(log(n))
uint reverseMask(uint x)
{
	assert(sizeof(x) == 4);// only for 4 bytes
	x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
	x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
	x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
	x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
	x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
	return x;
}

//5.6 An array A[1…n] contains all the integers from 0 to n except for one number which is missing. In this problem, we cannot access an entire integer in A with a single operation. The elements of A are represented in binary, and the only operation we can use to access them is “fetch the jth bit of A[i]”, which takes constant time. Write code to find the missing integer. Can you do it in O(n) time?
int fetch(int a[], int i, int j)
{
	return (a[i]>>j)&1;
}
int getai(int a[], int i)
{
	int val = 0;
	for(int j=31; j>=0; --j)
	{
		val <<= 1;
		val |= fetch(a, i, j);		
	}
	return val;
}
int findMiss(int a[], int n)
{
	bool *exist = new bool[n+1];
	memset(exist, false, sizeof(bool)*(n+1));
	int i = 0;
	for(i=0; i<n; ++i)
		exist[getai(a, i)] = true;
	for(i=0; i<n+1; ++i)
	{
		if(!exist[i])
		{
			break;
		}
	}
	delete[] exist;
	return i;
}

//5.7 http://www.catonmat.net/blog/low-level-bit-hacks-you-absolutely-must-know/
//http://graphics.stanford.edu/~seander/bithacks.html
// 判断一个数是否是2的方幂: n > 0 && ((n & (n - 1)) == 0 )
// 判断一个数奇偶: if(x&1 == 0) x is even, else x is odd
// Isolate the rightmost 1-bit: y = x & (-x)
// Right propagate the rightmost 1-bit: x | (x-1)
// Isolate the rightmost 0-bit: y = ~x & (x+1)
// Turn on the rightmost 0-bit: y = x | (x+1)

//5.8 The gray code is a binary numeral system where two successive values differ in only one bit.Given a non - negative integer n representing the total number of bits in the code,
//print the sequence of gray code.A gray code sequence must begin with 0. For example, given n = 2, return[0, 1, 3, 2]. 
//数学公式，时间复杂度O(2^n)，空间复杂度O(1)
vector<int> grayCode(int n)
{
	vector<int> res;
	const size_t size = 1 << n;//2^n
	res.reserve(size);
	for (size_t i = 0; i < size; ++i)
		res.push_back(i ^ (i >> 1));
	return res;
}

//5.9 