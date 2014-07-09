//Array and String
//1.1 Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?
bool isUnique(char *str)
{
	if(str == NULL)
		return true;
	int a[8] = {0};// ASCII only 256 = 8*4*8 = 8*int;
	int len = strlen(str);
	for(int i=0; i<len; ++i)
	{
		if((a[str[i]/32] >> (str[i]%32)) & 1 == 0)
			a[str[i]/32] |= (1 << (str[i]%32));
		else
			return false;
	}
	return true;
}

//1.2 Reverse String
//a. Write code to reverse a C-Style String
//without last null character
void reverseStr(char *str)
{
	if(str == NULL)
		return;
	int len = strlen(str);
	for(int i=0, j=len-1; i<j; ++i,--j)
	{
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
//with last null character 
void reverseStr(char *str)
{
	if(!str)
		return;
	char *p = str, *q = str;
	while(*p)
		++p;
	while(q < p)
	{
		char tmp = *p;
		*p = *q;
		*q = tmp;
		--p;
		++q;
	}
}
//recursion
void reverseStr(const char *str)
{
	if (*str == '\0')
		return;
	reverseStr(str + 1);
	putchar(*str);
}

//b. reverse individual subsections of a list that were separated by punctuation or whitespace. 
//method 1, space O(n), time O(n)
char *reverseList(char ch[])
{
	if(ch == NULL)
		return NULL;	
	int num = 0, nch = 0, n2s = 0;
	num = strlen(ch);	
	char *ach = new char[num+1];
	ach[num] = '\0';
	for(int i=num-1; i>=0; --i)
	{
		if((ch[i] >='a' && ch[i] <= 'z') || 
			(ch[i] >='A' && ch[i] <= 'Z'))
		{
			++n2s;
		}
		else
		{
			if(i==num-1)
				ach[i] = ch[i];
			else
			{
				for(int j=1; j<=n2s; ++j)
					ach[nch++] = ch[i+j];
				ach[nch++] = ch[i];
				n2s = 0;
			}
		}
	}
	for(int j=0; j<n2s; ++j)
		ach[nch++] = ch[j];
	memcpy(ch,ach,num);
	delete[] ach;
	return ch;
}
//method 2
void reverse(char *begin, char * end)
{
	char temp;
	while(begin<end)
	{
		temp = *begin;
		*begin++ = *end;
		*end-- = temp;
	}
}
char *reverseWords(char *ch)
{
	char *wordBegin = NULL;
	char *temp = ch;
	while(*temp)
	{
		if((wordBegin == NULL) && ((*temp >= 'a' && *temp <= 'z') || (*temp >= 'A' && *temp <= 'Z')))
			wordBegin = temp;
		if(wordBegin && ((*(temp+1)> 'z' || *(temp+1) <'A' || (*(temp+1) < 'a' && *(temp+1) > 'Z')) || (*(temp+1) == '\0')))
		{
			reverse(wordBegin, temp);
			wordBegin = NULL;
		}
		++temp;
	}
	reverse(ch, temp-1);
	return ch;
}

//c. Rotate a one-dimensional array of n elements to the right by k steps. For instance, with n = 7 and k = 3, the array {a, b, c, d, e, f, g} is rotated to{ e, f, g, a, b, c, d }.
void revstr(char *str, int left, int right)
{
	char *p1 = str + left;
	char *p2 = str + right;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		++p1;
		--p2;
	}
}
void rotate(char *str, int k)
{
	int n = strlen(str);
	revstr(str, 0, n - 1);//strrev(str); 
	revstr(str, 0, k - 1);
	revstr(str, k, n - 1);
}

//d. Given only putchar (no sprintf, itoa, etc.) write a routine putlong that prints out an unsigned long in decimal.
void putlong(unsigned long n)
{
	if (n < 10)
	{
		putchar(n + '0');
		return;
	}
	putlong(n / 10);
	putchar(n % 10 + '0');
}

//e. Reverse digits of an integer.x = -123, return -321, cases such as 10, 100. reverse of 1000000003 overflows
// 时间复杂度O(logn)，空间复杂度O(1)
int reverse(int x)
{
	int r = 0;
	for (; x; x /= 10)
		r = r * 10 + x % 10;
	return r;
}

//1.3 duplicate characters or numbers
//a. Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. NOTE: One or two additional variables are fine. An extra copy of the array is not. 
void DelDuplicate(char s[])// Time O(n^2)
{
	int len = strlen(s);
	if(len < 2)
		return;
	int p = 0;
	for(int i=0; i< len; ++i)
	{
		if(s[i] != '\0')
		{
			s[p++] = s[i];
			for(int j=i+1; j<len; ++j)
			{
				if(s[j] == s[i])
					s[j] = '\0';
			}
		}
	}
	s[p] = '\0';
}
//if string between a-z, time O(n)
void DelDuplicate(char s[])
{
	int len = strlen(s);
	if(len < 2)
		return;
	int p = 0, check = 0;
	for(int i=0; i<len; ++i)
	{
		int v = (int)(s[i] - 'a');
		if(check & (1 << v) == 0)
		{
			s[p++] = s[i];
			check |= 1 << v;
		}
	}
	s[p] = '\0';
}

// XOR,只要出现偶数次，都可以清零. 时间复杂度O(n)，空间复杂度O(1)
int singleNumber(int a[], int n)
{
	int res = 0;
	for (int i = 0; i < n; ++i)
		res ^= a[i];
	return res;
}

//b. Given an array of n elements which contains elements from 1 to n-1, with any of these numbers appearing no more than 2 times. Find these repeating (duplicate) numbers in O(n) and using only constant memory space.
//O(n) time and O(1) extra space, For example, let n be 7 and array be {1, 2, 3, 1, 3, 6, 6}, the answer should be 1, 3 and 6.
void findRepeat(int a[], int n)
{
	for(int i=0; i<n; ++i)
	{
		if(a[abs(a[i])] >= 0)
			a[abs(a[i])] *= -1;		
		else
			cout<<abs(a[i])<<endl;
	}	
}

//c. You are given an array of n+2 elements. All elements of the array are in range 1 to n. And all elements occur once except two numbers which occur twice. Find the two repeating numbers.
//Find the two repeating elements in a given arrayFor example, array = {4, 2, 4, 5, 2, 3, 1} and n = 5
double factorial(int n)
{
	if(n == 0 || n == 1)
		return 1;
	int product = 1;
	for(int i=2; i<=n; ++i)
	{
		product *= i;
	}
	return product;
}
void printRepeating(int arr[], int size)
{
  int S = 0;  /* S is for sum of elements in arr[] */
  int P = 1;  /* P is for product of elements in arr[] */ 
  int x,  y;   /* x and y are two repeating elements */
  int D;      /* D is for difference of x and y, i.e., x-y*/
  int n = size - 2,  i;
 
  /* Calculate Sum and Product of all elements in arr[] */
  for(i = 0; i < size; i++)
  {
    S = S + arr[i];
    P = P*arr[i];
  }        
   
  S = S - n*(n+1)/2;  /* S is x + y now */
  P = P/fact(n);         /* P is x*y now */
   
  D = sqrt(S*S - 4*P); /* D is x - y now */
   
  x = (D + S)/2;
  y = (S - D)/2;
   
  printf("The two Repeating elements are %d & %d", x, y);
}    

//d. Given two lists of integers, write a function that returns a list that contains only the intersection (elements that occur in both lists) of the two lists. The returned list should only contain unique integers, no duplicates.
// Example, {4,2,9,73,9,11,-5} and {-5,73,4,-1,9,9,9,4,7} would return the list [-5, 4, 73] in no particular order. 
int *FindIntersection(int a[], int m, int b[], int n, int c[], int l)//FindIntersection(a1,7,a2,8,c,10);
{
	if(a == NULL || b == NULL || c == NULL)
		return NULL;
	if(max(m, n) > l)
		return NULL;
	sort(a, a+m);
	sort(b, b+n);
	int i = 0, j = 0, k = 0;
	while(m > i && n > j)
	{
		if(a[i] == b[j])
		{
			if(k == 0)
				c[k++] = a[i];
			else
			{
				if(a[i] != c[k-1])
					c[k++] = a[i];
			}
			++i;
			++j;
		}
		else if(a[i] < b[j])
			++i;
		else
			++j;
	}
	return c;
}

//e. Find the intersection of two sorted arrays.
vector<int> getIntersection(int a[], int n, int b[], int m)
{
	vector<int> vi;
	int i = 0, j = 0;
	while (i < n && j < m)
	{
		if (a[i] > b[j])
			++j;
		else if (a[i] < b[j])
			++i;
		else
		{
			if (vi.empty())
				vi.push_back(a[i]);
			else if (a[i] != vi.back())
				vi.push_back(a[i]);
			++i;
			++j;
		}
	}
	return vi;
}

//f. Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
//Do not allocate extra space for another array, you must do this in place with constant memory.
int removeDuplicate(int a[], int n)
{
	if (n == 0)
		return 0;
	int index = 0;
	for (int i = 1; i < n; ++i)
	{
		if (a[index] != a[i])
		{
			a[++index] = a[i];
		}
	}
	return index + 1;
}
//What if duplicates are allowed at most twice? For example, Given sorted array A = [1, 1, 1, 2, 2, 3], Your function should return length = 5, and A is now[1, 1, 2, 2, 3]
int rmvDup(int a[], int n)
{
	assert(n >= 0);
	if (n <= 2)
		return n;
	int index = 2;
	for (int i = 2; i < n; ++i)
	{
		if (a[index - 2] != a[i])
			a[index++] = a[i];
	}
	return index;
}

//g. Given an array of integers, every element appears three times except for one.Find that single one. 时间复杂度O(n)，空间复杂度O(1)
int single(int a[], int n)
{
	const int len = sizeof(int)* 8;
	int count[len] = { 0 };
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			count[j] += (a[i] >> j) & 1;
			count[j] %= 3;
		}
	}
	int res = 0;
	for (int i = 0; i < len; ++i)
	{
		res += (count[i] << i);
	}
	return res;
}
int single(int a[], int n)
{
	int one = 0, two = 0, three = 0;
	for (int i = 0; i < n; ++i)
	{
		two |= (one & a[i]);
		one ^= a[i];
		three = ~(one & two);
		one &= three;
		two &= three;
	}
	return one;
}

//1.4 Write a method to decide if two strings are anagrams or not.
bool IsAnagram(char s1[], char s2[])
{
	if(s1 == NULL || s2 == NULL)
		return false;
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	if(l1 != l2)
		return false;
	int all[256] = {0};
	for(int i=0; i<l1; ++i)
	{
		++all[(int)s1[i]];
		--all[(int)s2[i]];
	}
	for(int i=0; i<256; ++i)
		if(all[i] != 0)
			return false;
	return true;
}

//b. Given an array of strings, return all groups of strings that are anagrams.lower - case.
//单词按照字母顺序排序后，若它们相等，则它们属于同一组anagrams,时间复杂度O(n)，空间复杂度O(n)
vector<string> anagrams(vector<string> &vs)
{
	unordered_map<string, vector<string>> group;
	for (auto s : vs)
	{
		string key = s;
		sort(key.begin(), key.end());
		group[key].push_back(s);
	}
	vector<string> res;
	for (auto i = group.cbegin(); i != group.cend(); ++i)
	{
		if (i->second.size() > 1)
			res.insert(res.end(), i->second.begin(), i->second.end());
	}
	return res;
}

//1.5 a. Write a method to replace all spaces in a string with ‘%20’.
char *replace(char *str, int n)
{
	if(str == NULL || n < 1)
		return NULL;
	int len =  strlen(str);	
	int num = 0, i = 0;
	for(i=0; i<len; ++i)	
	{
		if(str[i] == ' ')
			++num;		
	}
	
	int newlen = len + 2 * num + 1;
	if(newlen <= n)
	{
		int j = len-1;
		str[--newlen] = '\0';
		i = -- newlen;
		while(i >= 0)
		{
			if(str[j] == ' ')
			{
				str[i] = '0';
				str[--i] = '2';
				str[--i] = '%';
			}
			else
				str[i] = str[j];
			--i;
			--j;
		}
		return str;
	}
	else
	{
		char *newstr = new char[newlen];		
		newstr[--newlen] = '\0';
		int j = len-1;
		i = --newlen;
		while(i >= 0)
		{
			if(str[j] == ' ')
			{
				newstr[i] = '0';
				newstr[--i] = '2';
				newstr[--i] = '%';
			}
			else
				newstr[i] = str[j];
			--i;
			--j;
		}
		return newstr;
	}
}

//b. A String Replacement Problem -- in-place ,Replace all occurrence of the given pattern to ‘X’.
//For example, given that the pattern = ”abc”, replace “abcdeffdfegabcabc” with “XdeffdfegX”.Note that multiple occurrences of abc’s that are contiguous will be replaced with only one ‘X’.
void replace(char str[], char *pat)
{
	if (str == NULL || pat == NULL)
		return;
	int n = strlen(str);
	int m = strlen(pat);
	int index = 0, i = 0, j = 0;
	while (i < n)
	{
		for (j = 0; j < m; ++j)
		{
			if (str[i + j] != pat[j])
				break;
		}
		if (j == m)
		{
			if (str[index] != 'X')
				str[index++] = 'X';
			i += m;
		}
		else if (i < n)
		{
			str[index++] = str[i++];
		}
	}
	str[index] = '\0';
}

//c. remove spaces from a string
void removeSpace(char *str)
{
	char *p1 = str, *p2 = str;
	while (*p2 != '\0')
	{
		while (*p2 == ' ')
			++p2;
		*p1++ = *p2++;
	}
}

//d. C code to count the number of words in a string
int wordnum(const char *str)
{
	int cnt = 0;
	bool inword = false;
	while (*str != '\0')
	{
		if (isalpha(*str) != 0 && !inword)
		{
			++cnt;
			inword = true;
		}
		else if (inword && isalpha(*str) == 0)
			inword = false;
		++str;
	}
	return cnt;
}

//e. Given an absolute path for a file (Unix-style), simplify it. path = "/home/", = > "/home"; path = "/a/./b/../../c/", = > "/c"
//path = "/../" -> "/". path = "/home//foo/"->"/home/foo". 时间复杂度O(n)，空间复杂度O(n)
string simplifyPath(const string &path)
{
	vector<string> dirs;// as stack
	for (auto i = path.begin(); i != path.end();)
	{
		++i;
		auto j = find(i, path.end(), '/');
		auto dir = string(i, j);
		if (!dir.empty() && dir != ".")//当有连续'///' 时，dir 为空
		{
			if (dir == "..")
			{
				if (!dirs.empty())
					dirs.pop_back();
			}
			else
				dirs.push_back(dir);
		}
		i = j;
	}
	stringstream out;
	if (dirs.empty())
		out << "/";
	else
	{
		for (auto dir : dirs)
			out << '/' << dir;
	}
	return out.str();
}

//1.6 Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?
//counterclockwise 90
void ccwm90(int *a, int n)
{
	if(a == NULL || n < 2)
		return;
	for(int i=0; i<n-1; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			swap(*(a+n*i+j), *(a+n*j+i));
		}
	}
	for(int i=0; i<n/2; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			swap(*(a+n*i+j), *(a+n*(n-1-i)+j));
		}
	}
}
//clockwise 90
void cwm90(int a[][4], int n)
{
	if(a == NULL || n < 2)
		return;
	for(int i=0; i<n-1; ++i)
	{
		for(int j=i+1; j<n; ++j)
		{
			swap(a[i][j], a[j][i]);
		}
	}
	for(int j=0; j<n/2; ++j)
		for(int i=0; i<n; ++i)
			swap(a[i][j], a[i][n-j-1]);
}
//clockwise 180
void m180(int a[][4], int n)
{
	if(a == NULL || n < 2)
		return;
	for(int i=0; i<n/2; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			swap(a[i][j], a[n-1-i][j]);
		}
	}
	for(int j=0; j<n/2; ++j)
		for(int i=0; i<n; ++i)
			swap(a[i][j], a[i][n-j-1]);
}

//1.7 Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0.
//时间复杂度O(m*n)，空间复杂度O(m+n)
void zeroMN(int **a, int m, int n)
{
	bool *row = new bool[m];
	if(row == NULL)
		return;
	memset(row, false, sizeof(bool)*m);
	bool *col = new bool[n];
	if(col == NULL)
		return;
	memset(col, false, sizeof(bool)*n);
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(a[i][j] == 0)
			{
				row[i] = true;
				col[j] = true;
			}
		}
	}
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j)
		{ 
			if(row[i] == true || col[j] == true) 
				a[i][j] = 0;
		}
	}
}
// 时间复杂度O(m*n)，空间复杂度O(1)
void set0(vector<vector<int>> &matrix)
{
	const int m = matrix.size();
	const int n = matrix[0].size();
	bool row0 = false, col0 = false;//// 第一行/列是否存在0
	for (int i = 0; i < n; ++i)
	{
		if (matrix[0][i] == 0)
		{
			row0 = true;
			break;
		}
	}
	for (int j = 0; j < m; ++j)
	{
		if (matrix[j][0] == 0)
		{
			col0 = true;
			break;
		}
	}
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (matrix[i][j] == 0)
			{
				matrix[0][j] = 0;
				matrix[i][0] = 0;
			}
		}
	}
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (matrix[0][j] == 0 || matrix[i][0] == 0)
				matrix[i][j] = 0;
		}
	}
	if (row0)
	{
		for (int i = 0; i < n; ++i)
			matrix[0][i] = 0;
	}
	if (col0)
	{
		for (int i = 0; i < m; ++i)
			matrix[i][0] = 0;
	}
}

//1.8 Assume you have a method isSubstring which checks if one word is a substring of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring ( i.e., “waterbottle” is a rotation of “erbottlewat”).
//s1+s1将包含s1的所有旋转字符串，如果s2是s1+s1的子串，自然也就是s1 的旋转字符串了
bool isSubString(string s1, string s2)
{
	if(s1.find(s2) != string::npos)
		return true;
	else
		return false;
}
bool isRotation(string s1, string s2)
{
	if(s1.length() != s2.length() || s1.length() <= 0)
		return false;
	return isSubString(s1+s1, s2);
}

//1.9 a. Largest Sum Contiguous Subarray
int maxSumSubAry(int a[], int n)
{
	if(a == NULL || n < 1)
		return 0;
	int negNo = 0, bigele = a[0], sum = 0, maxsum = 0;
	for(int i=0; i<n; ++i)
	{
		sum += a[i];
		//if all element is negative
		if(sum < 0)
		{
			if(a[i] < 0)
			{
				++negNo;
				if(bigele < a[i])
					bigele = a[i];
			}
			sum = 0;
		}
		else if(sum > maxsum)
			maxsum = sum;
	}
	if(negNo == n)
		return bigele;
	else
		return maxsum;
}
//DP: better.时间复杂度O(n)，空间复杂度O(1)
int maxSumSubAry(int a[], int n)
{
	int maxsum = a[0], sum = a[0];
	for(int i=1; i<n; ++i)
	{
		sum = max(a[i], sum+a[i]);
		maxsum = max(sum, maxsum);
	}
	return maxsum;
}

//b. find how many 2 positive elements sum is a value in an unsorted array, time O(nlogn)+ O(n)
int elem2sum(int a[], int n, int sum)
{
	if(a == NULL || n < 2)
		return 0;
	sort(a,a+n-1);
	int count = 0, l = 0, r = n-1;
	while(l < r)
	{
		if(a[l] + a[r] < sum)
			++l;
		else if(a[l] + a[r] > sum)
			--r;
		else
		{
			cout<<a[l++]<<" + "<<a[r--]<<" = "<<sum<<endl;
			++count;
		}
	}
	return count;
}
//output index, hash table, time O(n)
int sum2(vector<int> &vi, int val)
{
	int cnt = 0;
	unordered_map<int, int> mii;
	unordered_set<int> si;
	for (int i = 0; i < vi.size(); ++i)
		mii[vi[i]] = i;
	for (int i = 0; i < vi.size(); ++i)
	{
		if (si.find(vi[i]) != si.end())
			continue;
		si.insert(vi[i]);
		int gap = val - vi[i];
		if (mii.find(gap) != mii.end())
		{
			si.insert(gap);
			cout << " index1 = " << min(i, mii[gap]) + 1 << ", index2 = " << max(i, mii[gap]) + 1 << endl;
			++cnt;
		}
	}
	return cnt;
}

//c. Given an unsorted array of nonnegative integers, find a continous subarray which adds to a given number.
//time O(n), Input: arr[] = {1, 4, 0, 0, 3, 10, 5}, sum = 7 , Ouptut: Sum found between indexes 1 and 4
bool subArraySum(int arr[], int n, int sum)
{
	if(arr == NULL || n < 1 || sum < 1)
		return false;
	int cursum = 0;
	bool find = false;
	int start = 0;
	for(int i=0; i<n; ++i)
	{
		cursum += arr[i];
		while(cursum > sum && start < i)
			cursum -= arr[start++];
		if(cursum == sum)
		{
			printf("Find continue subarray from %d to %d equal to sum %d.\n", start, i, sum);
			find = true;
		}		
	}
	return find;
}

/*d. Given a set S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the set which gives the sum of zero.
For example, given set S = { -1 0 1 2 - 1 - 4 }, One possible solution set is : (-1, 0, 1), (-1, 2, -1) */
set<vector<int>> tripleSum(vector<int> &arr)// time O(n^2)
{
	sort(arr.begin(), arr.end());
	set<vector<int>> triple;
	vector<int> vi(3);
	int n = arr.size();
	for (int i = 0; i < n - 2; ++i)
	{
		int j = i + 1;
		int k = n - 1;
		while (j < k)
		{
			int  sum2 = arr[i] + arr[j];
			if (sum2 + arr[k] < 0)
				++j;
			else if (sum2 + arr[k] > 0)
				--k;
			else
			{
				vi[0] = arr[i];
				vi[1] = arr[j];
				vi[2] = arr[k];
				triple.insert(vi);
				++j;
				--k;
			}
		}
	}
	return triple;
}

//e. Given an array S of n integers, find three integers in S such that the sum is closest to a given number target. Return the sum of the three integers.You may assume that each input would have exactly one solution.
//For example, given array S = { -1 2 1 - 4 }, and target = 1. The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
int sum3close(vector<int> &arr, int val)
{
	int res = 0;
	int min_gap = INT_MAX;
	sort(arr.begin(), arr.end());
	for (int i = 0; i < arr.size() - 2; ++i)
	{
		int j = i + 1;
		int k = arr.size() - 1;
		while (j < k)
		{
			int sum = arr[i] + arr[j] + arr[k];
			int gap = abs(sum - val);
			if (gap < min_gap)
			{
				res = sum;
				min_gap = gap;
			}
			if (sum < val)
				++j;
			else
				--k;
		}
	}
	return res;
}

//f. Given an array S of n integers, are there elements a; b; c, and d in S such that a+b+c+d = target?
// Note: Elements in a quadruplet(a; b; c; d) must be in non - descending order. The solution set must not contain duplicate quadruplets.
set<vector<int>> sum4(vector<int> &arr, int val)//time O(n^2), space O(n^2)
{
	set<vector<int>> svi;
	vector<int> quad(4);
	int n = arr.size();
	if (n < 4)
		return svi;
	sort(arr.begin(), arr.end());
	unordered_multimap<int, pair<int, int>> cache;
	for (int i = 0; i < n - 1; ++i)//save all 2 elem sum
	{
		for (int j = i + 1; j < n; ++j)
			cache.insert(make_pair(arr[i] + arr[j], make_pair(i, j)));
	}
	for (auto i = cache.begin(); i != cache.end(); ++i)
	{
		int sub = val - i->first;
		auto range = cache.equal_range(sub);
		for (auto j = range.first; j != range.second; ++j)
		{
			auto a = i->second.first;
			auto b = i->second.second;
			auto c = j->second.first;
			auto d = j->second.second;
			if (a != c && b != c && a != d && b != d)
			{
				quad[0] = arr[a];
				quad[1] = arr[b];
				quad[2] = arr[c];
				quad[3] = arr[d];
				sort(quad.begin(), quad.end());
				svi.insert(quad);
			}
		}
	}
	return svi;
}

//g. There is an array A[N] of N numbers. You have to compose an array Output[N] such that Output[i] will be equal to multiplication of all the elements of A[N] except A[i]. Solve it without division operator and in O(n).
void multip(int a[], int out[], int n)// time O(n)
{
	int left = 1, right = 1;
	for (int i = 0; i < n; ++i)
		out[i] = 1;
	for (int i = 0; i < n; ++i)
	{
		out[i] *= left;
		out[n - 1 - i] *= right;
		left *= a[i];
		right *= a[n - 1 - i];
	}
}

//1.10 find the longest word made of other words.EXAMPLE Input: test, tester, testertest, testing, testingtester Output: testingtester
unordered_set<string> hs;
inline bool cmp(string s1, string s2)
{
	return s2.length() < s1.length();
}
bool makeofword(string word, int len)
{
	int l = word.length();
	if(l == 0)
		return true;
	for(int i=1;i<=l;++i)
	{
		if(i == len)
			return false;
		string str = word.substr(0,i);
		if(hs.find((char*)&str[0]) != hs.end())
		{
			if(makeofword(word.substr(i),len))
				return true;
		}
	}
	return false;
}
bool printlongestword(string word[], int n)
{
	for(int i=0;i<n;i++)
		hs.insert((char*)&word[i][0]);
	sort(word, word+n,cmp);
	for(int i=0;i<n;i++)
	{
		if(makeofword(word[i],word[i].length()))
		{
			cout<<"longest word: "<<word[i]<<endl;
			return true;
		}
	}
	return false;
}
//read from file, big data
struct ConstructWords// output struct
{
	unsigned int count;// the count of words that can be constructed by other word
	string longestWord;
	string secondLongestWord;
};
inline bool cmp(string s1, string s2)// compare function used by sort
{
	return s2.length() < s1.length();
}
bool construtWord(string word, int length, unordered_set<string> &hs)// check if a word can be consisted by other shorter word, not count itself, if find return true 
{
	if (word.length() == 0)// finished whole word match
		return true;
	for (int i = 1; i <= word.length(); ++i)
	{
		if (i == length)//not count itself 
			return false;
		string str = word.substr(0, i);//get the sub word
		if (hs.find(str) != hs.end())// find sub word in hash table
		{
			if (construtWord(word.substr(i), length, hs))
				return true;
		}
	}
	return false;
}
// get and return the longest and second logest word and the number of words which can be consised by other shorter words.
// Time O(n*log(n) +n*d) n is words number, d is word average length， when n is very large, time is O(n*log(n)), space is O(n)
ConstructWords getConstructWords(string input)
{
	ConstructWords cw;
	cw.count = 0;
	ifstream fin(input, ios::in, _SH_DENYWR);
	if (fin.bad())// Check whether input file is corrupted.
	{
		cerr << "Data File \"" << input << " \"Corrupted! Pelase check it." << endl;
	}
	else if (fin.fail())// Check whether file can be opened.
	{
		cerr << "Failing to open the \"" << input << "\" File!" << endl;
	}
	else
	{
		vector<string> vs;// save all words
		unordered_set<string> hs;// hash table
		string str = "";
		while (!fin.eof())
		{
			fin >> str;
			vs.push_back(str);
			hs.insert(str);
		}
		sort(vs.begin(), vs.end(), cmp);// sort the words by descending order according to word length (first) and dictionary (if word length equal)
		for (unsigned int i = 0; i < vs.size(); ++i)
		{
			if (construtWord(vs[i], vs[i].length(), hs))
			{
				if (cw.count == 0)
				{
					cout << "The longest word that can be constructed by other words is: " << vs[i] << ", the length is " << vs[i].length() << endl;
					cw.longestWord = vs[i];
					++cw.count;
				}
				else if (cw.count == 1)
				{
					cout << "Second longest word that can be constructed by other words is: " << vs[i] << ", the length is " << vs[i].length() << endl;
					++cw.count;
					cw.secondLongestWord = vs[i];
				}
				else
					++cw.count;
			}
		}
		cout << "The total count of word that can be constructed by other shorter words are " << cw.count << endl;
	}
	fin.close();
	return cw;
}

//1.11 a. Imagine you have a square matrix, where each cell is filled with either black or white. Design an algorithm to find the maximum subsquare such that all four borders are filled with black pixels.
// Brute force time O(n^2)//const int MAX_N = 10; //int matrix[MAX_N][MAX_N] = {0};
struct SubSquare
{
	int row, col, size;
};
bool IsSquare(int row, int col, int size)
{
	for(int i=0; i<size; ++i)
	{
		if(matrix[row][col+i] == 1)// 0 = black, 1 = white
			return false;
		if(matrix[row+size-1][col+i] == 1)
			return false;
		if(matrix[row+i][col] == 1)
			return false;
		if(matrix[row+i][col+size-1] == 1)
			return false;
	}
	return true;
}
SubSquare FindSubSquare(int n)
{
	int max_size = 0;// 最大边长
	int col = 0;
	int row = 0, size = 0;
	SubSquare sq;
	while(n-col > max_size)
	{
		for(row=0; row<n; ++row)
		{
			size = n - max(row, col);
			while(size > max_size)
			{
				if(IsSquare(row,col,size))
				{
					max_size = size;
					sq.row = row;
					sq.col = col;
					sq.size = size;
					break;
				}
				--size;
			}
		}
		++col;
	}
	return sq;
}

//b. Given a 2D binary matrix filled with 0’s and 1’s, find the largest rectangle containing all ones and return its area.
//DP: 时间复杂度O(n^2)，空间复杂度O(n)
int maxRectangle(vector<vector<char>> &matrix)
{
	if (matrix.empty())
		return 0;
	const int m = matrix.size();
	const int n = matrix[0].size();
	vector<int> H(n, 0), L(n, 0), R(n, n);
	int res = 0;
	for (int i = 0; i < m; ++i)
	{
		int left = 0, right = n;
		// calculate L(i, j) from left to right
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == '1')
			{
				++H[j];
				L[j] = max(L[j], left);
			}
			else
			{
				left = j + 1;
				H[j] = 0; L[j] = 0; R[j] = n;
			}
		}
		// calculate R(i, j) from right to left
		for (int j = n - 1; j >= 0; --j)
		{
			if (matrix[i][j] == '1')
			{
				R[j] = min(R[j], right);
				res = max(res, H[j] * (R[j] - L[j]));
			}
			else
				right = j;
		}
	}
	return res;
}

//1.12 Given an NxN matrix of positive and negative integers, write code to find the submatrix with the largest possible sum.
//a. 暴力法，时间复杂度O(n^6 )枚举子矩阵一共有C(n, 2)*C(n, 2)个(水平方向选两条边，垂直方向选两条边)， 时间复杂度O(n^4)，求子矩阵中元素的和需要O(n^2)的时间。 
//b. 部分和预处理，时间复杂度降到O(n^4),上面的方法需要O(n2 )去计算子矩阵中元素的和。 这一部分我们可以在预处理的时候求出部分和，在使用的时候就只需要O(1) 的时间来得到子矩阵中元素的和
//我们用一个二维数组p来保存矩阵的部分和，p[i][j]表示左上角是(1, 1)，(下标从1开始)， 右下角是(i, j)的矩阵中元素的和。这样一来，如果我们要求矩阵(x1, x2, y1, y2) 中元素的和(即上图矩阵D)
//sum(D) = p[y2][x2] - p[y2][x1-1] - p[y1-1][x2] + p[y1-1][x1-1], p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + A[i][j]
//c. 降维，O(n^3)的解法,枚举i，j行需要O(n2 )的时间，求一维情况的子数组最大和需要O(n)的时间， 所以总的时间复杂度为O(n3 )。其中求第k列元素中， 第i行到第j行的元素和可以用部分和求解，仅需要O(1)的时间
//sum(i,j,k) = p[j][k] - p[j][k-1] - p[i-1][k] + p[i-1][k-1]
const int MAX_N = 5; int A[MAX_N][MAX_N] = {{0},{0,1,52,3,-4},{0,5,66,-7,-8},{0,9,-910,11,-12},{0,13,-14,-15,16}};//元素值
int p[MAX_N][MAX_N] = {0};//p[i][j]表示左上角是(1, 1)，(下标从1开始)， 右下角是(i, j)的矩阵中元素的和
struct Matrix
{
	int rowb, rowe, col, size, maxsum;
};
void precompute(int n)
{
	int j = 0;
	for(int i=1;i<=n;++i)
	{
		for(j=1; j<=n; ++j)
		{
			p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + A[i][j];
		}
	}
}
Matrix maxSubMatrixSum(int n)
{	
	Matrix mx;
	if(n<1)
		return mx;
	precompute(n);
	int max_sum = INT_MAX;
	int j = 0, k = 0;
	int cur_sum = 0, val = 0;
	for(int i=1; i<=n; ++i)
	{
		for(j=i; j<=n; ++j)// i到j行
		{
			cur_sum = 0;
			for(k=1; k<=n; ++k)
			{
				val = p[j][k] - p[j][k-1] - p[i-1][k] + p[i-1][k-1];
				if(cur_sum <= 0)
					cur_sum = val;
				else
					cur_sum += val;
				if(cur_sum > max_sum)
				{
					mx.col = k;
					mx.rowb = i;
					mx.rowe = j;
					mx.size = max(j-i+1, k);
					mx.maxsum = cur_sum;
					max_sum = cur_sum;
				}
			}
		}
	}
	return mx;
}

//1.13 Pattern Searching 
//Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[]. You may assume that n > m.
//a. Brute force method O((n-m+1)*m)
bool bfSearch(const char *src, const char *pat)
{
	int n = strlen(src);
	int m = strlen(pat);
	bool find = false;
	for(int i=0; i<=n-m; ++i)// slide src one by one, find all match pattern
	{
		int j = 0;
		for(j=0; j<m; ++j)//For current index i, check for pattern match 
		{
			if(src[i+j] != pat[j])
				break
		}
		if(j == m)// find it
		{
			cout<<"Pattern found at index "<<i<<"."<<endl;
			find = true;
		}
	}
}
//Implement strstr() to Find a Substring in a String, can't invoke library functions
char* StrStr(const char *str, const char *pat)
{
	if (!*pat)
		return (char*)str;
	char *p1 = (char*)str, *p2 = (char*)pat;
	char *p1adv = (char*)str;
	while (*(++p2))
		++p1adv;
	while (*p1adv != '\0')
	{
		char *p1b = p1;
		p2 = (char*)pat;
		while (*p1 && *p2 && *p1 == *p2)
		{
			++p1;
			++p2;
		}
		if (*p2 == '\0')
			return p1b;
		p1 = p1b + 1;
		++p1adv;
	}
	return NULL;
}

//b. KMP, time O(n), n是目标串长度, find longest proper prefix which is also suffix
void matchTable(const char arr[],int mt[], int n)// longest prefix suffix value
{
	if(arr == NULL || mt == NULL || n < 1)
		return;
	int i = 1;//index of travse arr
	int j = 0;//longest prefix suffix value
	mt[0]= 0;
	while(i < n)
	{		
		while(arr[i] == arr[j])
		{
			mt[i++] = ++j;
		}
		if(arr[i] != arr[j])
		{			
			if(j == 0)
			{
				mt[i++] = 0;				
			}
			else
				j = mt[j-1];//fast compare
		}
	}
}
void KMPSearch(const char *str, const char *pat)
{
	if(str == NULL || pat == NULL)
		return;
	int n = strlen(str);
	int m = strlen(pat);
	int *mt = new int[m];
	memset(mt, 0, sizeof(int)*m);
	matchTable(pat, mt, m);
	int i = 0, j = 0;
	while(i < n-m+1)
	{
		while(str[i] == pat[j] && j < m)
		{
			++i;
			++j;
		}
		if(j == m)
		{
			cout<<"Found pattern at index : "<<i - m<<endl;
			j = mt[j-1];
		}
		else//str[i] != pat[j]
		{
			if(j == 0)
				++i;
			else
				j = mt[j-1];
		}			
	}
	delete[] mt;
	mt = NULL;
}

//c. BM：Boyer-Moore, 字符串"与"搜索词"头部对齐，从尾部开始比较.Boyer-Moore算法的基本思想是，每次后移下面两个规则之中的较大值。各种文本编辑器的"查找"功能（Ctrl+F），大多采用Boyer-Moore算法
//坏字符规则：后移位数 = 坏字符的位置 - 搜索词中的上一次出现位置, 如果"坏字符"不包含在搜索词之中，则上一次出现位置为 -1
//好后缀规则: 后移位数 = 好后缀的位置 - 搜索词中的上一次出现位置,（1）"好后缀"的位置以最后一个字符为准。假定"ABCDEF"的"EF"是好后缀，则它的位置以"F"为准，即5（从0开始计算）。
//（2）如果"好后缀"在搜索词中只出现一次，则它的上一次出现位置为 -1。比如，"EF"在"ABCDEF"之中只出现一次，则它的上一次出现位置为-1（即未出现）。
//（3）如果"好后缀"有多个，则除了最长的那个"好后缀"，其他"好后缀"的上一次出现位置必须在头部。比如，假定"BABCDAB"的"好后缀"是"DAB"、"AB"、"B"，请问这时"好后缀"的上一次出现位置是什么？回答是，
//此时采用的好后缀是"B"，它的上一次出现位置是头部，即第0位。这个规则也可以这样表达：如果最长的那个"好后缀"只出现一次，则可以把搜索词改写成如下形式进行位置计算"(DA)BABCDAB"，即虚拟加入最前面的"DA"。
//only use bad rule
void BMBadTable(char *str, int len, int bad[], int n)
{
	if(str == NULL || bad == NULL || len < 1 || n != 256)//255 characters hash
		return;	
	memset(bad, -1, sizeof(int)*n);// Initialize all occurrences as -1
	for(int i=0; i<len; ++i)
	{
		bad[(int)str[i]] = i;//坏字符在搜索词中上一次出现位置
	}
}
void BMsearchBad(char *str, char *pat)
{
	if(str == NULL || pat == NULL)
		return;
	int n = strlen(str);
	int m = strlen(pat);
	const int iASCII = 256;
	int bad[iASCII];
	BMBadTable(pat, m, bad, iASCII);
	int i = 0;
	while(i <= n-m)
	{
		int j = m - 1;
		while(j >= 0 && pat[j] == str[i+j])
		{
			--j;
		}
		if(j < 0)//j == -1
		{
			cout<<"Found the pattern at index : "<<i<<endl;
			i += (i + m < n)? m - bad[(int)str[i+m]]:1;
		}
		else
			i += max(1, j - bad[(int)str[i+j]]);
	}
}
//both bad and good rule
void BMMatchTable(char *str, int good[], int len, int bad[], int n)
{
	if(str == NULL || bad == NULL || good == NULL || n != 256)//255 characters hash
		return;	
	for(int i=0; i<n; ++i)// Initialize all occurrences as len
		bad[i] = len;
	for(int i=0; i<len; ++i)
	{
		bad[(int)str[i]] = len - 1 - i;//len - 1 - 坏字符在搜索词中上一次出现位置
		good[i] = len;
	}
	int *suffix = new int[len];
	suffix[len-1] = len;//其中suffix[i] = s 表示以i为边界，与模式串后缀匹配的最大长度
	for(int i=len-2; i>=0; --i)
	{
		int j = i;
		while(j >= 0 && str[j] == str[len-1-i+j])
			--j;
		suffix[i] = i - j;//aaaa=1234,abcd=0004,abab=0204
	}
	int j = 0;
	for(int i=len-1; i>=0; --i)
	{
		if(suffix[i] == i + 1)//最大前缀
		{
			while(j < len-1-i)
			{
				if(good[j] == len)
					good[j] = len-1-i;
				++j;
			}
		}
	}
	for(int i=0; i<=len-2; ++i)
		good[len-1-suffix[i]] = len-1-i;//表示遇到好后缀时，模式串应该移动的距离，其中i表示好后缀前面一个字符的位置（也就是坏字符的位置）
	delete[] suffix;
	return;
}
void BMsearch(char *str, char *pat)
{
	if(str == NULL || pat == NULL)
		return;
	int n = strlen(str);
	int m = strlen(pat);
	const int ichar = 256;//256个字母hash
	int bad[ichar];
	int *good = new int[m];
	BMMatchTable(pat, good, m, bad, ichar);
	int i = 0;//shift of str
	while(i <= n-m)
	{
		int j = m-1;//compare from end to begin
		while(j >= 0 && str[i+j] == pat[j])
			--j;
		if(j < 0)//j == -1
		{
			cout<<"Found the pattern at index : "<<i<<endl;
			i += (i+m < n)? m - bad[(int)str[i+m]]:1;			
		}
		else//We may get a negative shift if the last occurrence of bad character in pattern is on the right side of the current character. 
			i += max(good[j], bad[(int)str[i+j]]-(m-1-j));
	}
	delete[] good;
	good = NULL;
}

//d. Rabin-Karp Algorithm, hash( txt[s+1 .. s+m] ) = d ( hash( txt[s .. s+m-1]) – txt[s]*h ) + txt[s + m] ) mod q
//The average and best case running time is O(n+m), worst-case time is O(nm), O(m)的预处理时间. Worst case occurs when all characters of pattern and text are same as the hash values of all the substrings of txt[] match with hash value of pat[]. For example pat[] = “AAA” and txt[] = “AAAAAAA”.
void RKsearch(char *str, char *pat)
{
	if(str == NULL || pat == NULL)
		return;
	const int iASCII = 256;//the number of characters in input alphabet
	const int imod = 101; // A prime number for mod
	int n = strlen(str);
	int m = strlen(pat);
	int i = 0, j = 0;
	int hashPat = 0;// hash value for pat
	int hashStr = 0;// hash value for str
	int hash = 1;
	for(i=0; i<m-1; ++i)
		hash = (hash * iASCII) % imod;// The value of hash would be pow(iASCII, m-1)%imod
	for(i=0; i<m; ++i)// Calculate the hash value of pattern and first window of text
	{
		hashPat = (iASCII * hashPat + pat[i]) % imod;
		hashStr = (iASCII * hashStr + str[i]) % imod;
	}
	for(i=0; i<=n-m; ++i)// Slide the pattern over text one by one
	{
		// Chaeck the hash values of current window of text and pattern
        // If the hash values match then only check for characters on by one
		if(hashPat == hashStr)
		{
			for(j=0; j<m; ++j)
			{
				if(str[i+j] != pat[j])
					break;
			}
			if(j == m)
				printf("Pattern found at index %d \n", i);
		}
		// Calulate hash value for next window of text: Remove leading digit, add trailing digit  
		if(i < n-m)
		{
			hashStr = (iASCII * (hashStr - str[i] * hash) + str[i+m]) % imod;
			if(hashStr < 0)// if hashStr is negative, converting it to positive
				hashStr += imod; 
		}
	}
}

//e. sunday 最坏时间复杂性为O(N*M),平均快于BM,Sunday算法的思想和BM算法中的坏字符思想非常类似。
//差别只是在于Sunday算法在失配之后，是取目标串中当前和模式串对应的部分后面一个位置的字符来做坏字符匹配。
bool maxShift(char const *ptr, int *nextval)
{
	if(ptr == NULL || nextval == NULL)
		return false;
	int plen = strlen(ptr);
	for(int i=0; i<256; ++i)//256 ASCII 
		nextval[i] = plen + 1;
	for(int i=0; i<plen; ++i)
		nextval[(int)ptr[i]] = plen - i;
	return true;
}
bool sunday(char const *str, char const *ptr)//return find or not
{
	if(str == NULL || ptr == NULL)
		return false;
	int slen = strlen(str);
	int plen = strlen(ptr);
	if(plen > slen || plen < 1 || slen < 1)
		return false;
	int *nextval = new int[256];
	if(!maxShift(ptr, nextval))
		return false;
	int i = 0;
	bool find = false;
	while(i < slen-plen+1)
	{
		int j = 0;
		while(j < plen && str[i+j] == ptr[j])
			++j;
		if(j == plen)
		{
			cout<<"Find pattern at position "<<i<<endl;
			find = true;
		}
		if(i < slen - plen)
			i += nextval[str[i+plen]];
		else
			break;
	}
	delete[] nextval;
	nextval = NULL;
	return find;
}

//f. Finite Automata, time O(n)
int getState(char *pat, int m, int state, int i)
{
	//If the character is same as next character in pattern, just increment state
	if(state < m && i == pat[state])
		return state+1;
	for(int ns=state; ns>0; --ns) // ns stores the result which is next state
	{
		// ns finally contains the longest prefix which is also suffix in "pat[0..state-1]c"
		// Start from the largest possible value and stop when you find a prefix which is also suffix
		if(pat[ns-1] == i)
		{
			int j = 0;
			for(j=0; j<ns-1; ++j)
			{
				if(pat[j] != pat[state-ns+1+j])
					break;
			}
			if(j == ns-1)//j is the 
				return ns;
		}
	}
	return 0;// i is not the character in pattern, then 0
}
void getTF(char *pat, int m, int **TF)//time O((m^3)*NO_OF_CHARS)
{
	for(int state=0; state<m+1; ++state)
	{
		for(int i=0; i<256; ++i)
		{
			TF[state][i] = getState(pat, m, state, i);
		}
	}
}
bool FASearch(char *src, char *pat)
{
	if(src == NULL || pat == NULL)
		return false;
	int n = strlen(src);
	int m = strlen(pat);
	int **TF = new int*[m+1];//FA status
	for(int i=0; i<m+1; ++i)
	{
		TF[i] = new int[256];
		memset(TF[i], 0, sizeof(int)*256);
	}
	getTF(pat, m, TF);
	int state = 0;
	bool find = false;
	for(int i=0; i<n; ++i)//FA search
	{
		state = TF[state][src[i]];
		if(state == m)
		{
			cout<<"Find pattern at position "<<i-m+1<<endl;
			find = true;
		}
	}
	return find;
}
//like lps for time O(M*NO_OF_CHARS) to compute transition function
void computeTF(char *pat, int m, int **TF)
{
	for(int i=0; i<256; ++i)
		TF[0][i] = 0;// first row is 0
	TF[0][pat[0]] = 1;
	int lps = 0;
	for(int i=1; i<=m; ++i)
	{
		for(int j=0; j<256; ++j)
			TF[i][j] = TF[lps][j];
		TF[i][pat[i]] = i+1;
		if(i < m)
			lps = TF[lps][pat[i]];
	}
}

//g. Given two strings where first string may contain wild card characters and second string is a normal string. Write a function that returns true if the two strings match. 
//* --> Matches with 0 or more instances of any character or set of characters. ? --> Matches with any one character.
bool match(char *src, char *pat)//时间复杂度O(n!*m!)，空间复杂度O(n)
{
	if(src == NULL || pat == NULL)
		return false;
	else if(*src == '\0' && *pat == '\0')// If we reach at the end of both strings, we are done
		return true;
	// Make sure that the characters after '*' are present in second string.
    // This function assumes that the first string will not contain two consecutive '*' 
	else if(*src == '*' && *(src+1) != '\0' && *pat == '\0')
		return false;
	//If the first string contains '?', or current characters of both strings match
	else if(*src == '?' || *src == *pat)
		return match(src+1, pat+1);
	// If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
	else if(*src == '*')
		return match(src+1,pat) || match(src, pat+1);
	else
		return false;
}
// 迭代版，时间复杂度O(n*m)，空间复杂度O(1)
bool isMatch(const char *s, const char *p)
{
	bool star = false;
	const char *src = s, *pat = p;
	for (src = s, pat = p; *src != '\0'; ++src, ++pat)
	{
		switch (*pat)
		{
		case '?':
			break;
		case '*':
			star = true;
			s = src, p = pat;
			while (*p == '*')
				++p;//skip continuous '*'
			if (*p == '\0')
				return true;
			src = s - 1;
			pat = p - 1;
			break;
		default:
			if (*src != *pat)
			{
				if (!star)
					return false;
				++s;
				src = s - 1;
				pat = p - 1;
			}
		}
	}
	while (*pat == '*')
		++pat;
	return (*pat == '\0');
}

//‘.’ Matches any single character. ‘*’ Matches zero or more of the preceding element. isMatch(“aab”, “c*a*b”) → true
bool isMatch(const char *s, const char *p)
{
	assert(s && p);
	if (*p == '\0')
		return *s == '\0';
	//next char is not '*'
	if (*(p + 1) != '*')
	{
		assert(*p != '*');
		return((*s == *p) || (*p == '.' && *s != '\0')) && isMatch(s + 1, p + 1);
	}
	//next char is '*'
	while ((*s == *p) || (*p == '.' && *s != '\0'))
	{
		if (isMatch(s, p + 2))
			return true;
		++s;
	}
	return isMatch(s, p + 2);
}

//h. Suffix array is a sorted array of all suffixes of a given string. In fact Suffix array and suffix tree both can be constructed from each other in linear time.
//Advantages of suffix arrays over suffix trees include improved space requirements, simpler linear time construction algorithms (e.g., compared to Ukkonen’s algorithm) and improved cache locality
//Naive method time O(n2Logn), the suffix array for "banana" is {5, 3, 1, 0, 4, 2}：0 banana - 1 anana - 5 a
struct Suffix
{
	int index;
	char *sfx;
};
bool cmpSuffix(Suffix a, Suffix b)
{
	if(strcmp(a.sfx, b.sfx) < 0)
		return true;
	else 
		return false;
}
int *buildSuffixArray(char *src, int n)// 
{
	if(src == NULL || n < 1)
		return NULL;
	Suffix *suffix = new Suffix[n];
	if(suffix == NULL)
	{
		cout<<"there are no more memory"<<endl;
		return NULL;
	}
	for(int i=0; i<n; ++i)
	{// Store suffixes and their indexes in an array of structures.
		suffix[i].index = i;
		suffix[i].sfx = src + i;
	}
	sort(suffix, suffix+n, cmpSuffix);// Sort the suffixes using the comparison function
	int *suffixArr = new int[n];
	for(int i=0; i<n; ++i)// Store indexes of all sorted suffixes in the suffix array
		suffixArr[i] = suffix[i].index;
	delete[] suffix;
	suffix = NULL;
	return suffixArr;// Return the suffix array
}
//Suffix array based search function, time O(mLogn)
bool suffixArraySearch(char *src, char *pat, int *suffixArr, int n)
{
	int m = strlen(pat);
	// Do binary search for the pat in src using the suffix array
	int l = 0, r = n-1;
	while(l <= r)
	{
		int mid = l + (r-l)/2;
		int res = strncmp(pat, src+suffixArr[mid], m);
		if(res == 0)
		{
			cout<<"pattern found at index "<<suffixArr[mid]<<endl;
			return true;
		}
		else if(res < 0)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return false;
}

//1.14 Given a string s and an array of smaller strings T, design a method to search s for each small string in T.//字符串的多模式匹配问题.我们把S称为目标串，T中的字符串称为模式串。设目标串S的长度为m，模式串的平均长度为 n，共有k个模式串。
//如果我们用KMP算法(或BM算法)去处理每个模式串， 判断模式串是否在目标串中出现， 匹配一个模式串和目标串的时间为O(m+n)，所以总时间复杂度为：O(k(m+n))。
//一般实际应用中，目标串往往是一段文本，一篇文章，甚至是一个基因库， 而模式串则是一些较短的字符串，也就是m一般要远大于n。 这时候如果我们要匹配的模式串非常多(即k非常大)，那么我们使用上述算法就会非常慢。
//这也是为什么KMP或BM一般只用于单模式匹配，而不用于多模式匹配。 Trie树，AC自动机，WM算法，后缀树等算法可以解决多模式匹配问题。
//a. Trie树--处理目标串，又称为字典树，单词查找树或前缀树，是一种用于快速检索的多叉树结构。 比如英文字母的字典树是一个26叉树，数字的字典树是一个10叉树。
//Trie树可以利用字符串的公共前缀来节约存储空间，这也是为什么它被叫前缀树.构造字符串S的后缀Trie却需要O(m^2)的时间， (m为S的长度)，及O(m^2)的空间
//将字符串S的所有后缀构成一棵Trie树(后缀Trie)， 然后查询模式串是否在该Trie树中出现即可。如果模式串t的长度为n， 那么我们从根结点向下匹配，可以用O(n)的时间得出t是否为S的子串。
class Trie//array version, 总的时间复杂度O(m^2 + kn)
{
public:
	static const int MAX_N = 20*20;//20为主串长度
	static const int CLD_NUM = 26; //每个节点的子节点数量=26个字母
	int index;//current node ID
	int trie[MAX_N][CLD_NUM];
	Trie(const char* str)
	{
		memset(trie[0], -1, sizeof(trie[0]));
		index = 1;
		while(*str != '\0')
		{
			insert(str);
			++str;
		}
	}
	void insert(const char *str)
	{
		int i = 0;
		while(*str != '\0')
		{
			int j = *str - 'a';//str are all lower case letter
			if(trie[i][j] == -1)
			{
				memset(trie[index], -1, sizeof(trie[index]));
				trie[i][j] = index++;
			}
			i = trie[i][j];
			++str;
		}
	}
	bool find(const char *str)
	{
		int i = 0;
		while(*str != '\0')
		{
			int j = *str - 'a';// str are all lower case letters
			if(trie[i][j] == -1)
				return false;
			i = trie[i][j];
			++str;
		}
		return true;
	}
};
class trie//pointer version
{
public:
	static const int ALPHABET_SIZE = 26;
	struct TrieNode
	{
		int value;
		TrieNode *child[ALPHABET_SIZE];
	};
	struct Trie
	{
		int count;
		TrieNode *root;
	};
	trie(Trie *ptrie)
	{
		ptrie->count = 0;
		ptrie->root = getNode();
	}
	TrieNode *getNode()//return new trie node
	{
		TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
		if(node != NULL)
		{
			node->value = 0;
			for(int i=0; i<ALPHABET_SIZE; ++i)
				node->child[i] = NULL;
		}		
		return node;
	}
	void insert(Trie *ptrie, char key[])
	{
		int len = strlen(key);
		++ptrie->count;
		TrieNode *pcrawl = ptrie->root;
		for(int i=0; i<len; ++i)
		{
			int index = (int)(key[i] - 'a');// all lower case letter
			if(pcrawl->child[index] == NULL)
				pcrawl->child[index] = getNode();
			pcrawl = pcrawl->child[index];
		}
		pcrawl->value = ptrie->count;//mark last node as leaf
	}
	bool search(Trie *ptrie, char key[])//return non 0 if key is in trie
	{
		int len = strlen(key);
		TrieNode *pcrawl = ptrie->root;
		for(int i=0; i<len; ++i)
		{
			int index = int(key[i] - 'a');
			if(pcrawl->child[index] == NULL)
				return false;
			pcrawl = pcrawl->child[index];
		}
		return (pcrawl !=0 && pcrawl->value);
	}
};

//b.Aho–Corasick string matching algorithm- AC自动机--处理模式串,时间复杂度为：O(m+kn+z)， 其中：m是目标串S的长度，k是模式串个数，n是模式串平均长度，z是S 中出现的模式串数量。从时间复杂度上可以看出，AC自动机比后缀Trie方法要快， m从2次方降到了1次方
// AC算法的时间复杂度是O(n)，与patterns的个数及长度都没有关系。因为Text中的每个字符都必须输入自动机，所以最好最坏情况下都是O(n)，加上预处理时间，那就是O(M+n)，M是patterns长度总和
//array method
class ACAutomation
{
public:
	static const int MAX_N = 20*20;// all patterns length
	static const int CLD_NUM = 26;// 26 alphabet
	int index;
	int fail[MAX_N];// failure function
	int tag[MAX_N];// output function
	int trie[MAX_N][CLD_NUM];//trie tree function
	void reset()
	{
		memset(trie[0], -1, sizeof(trie[0]));
		tag[0] = 0;
		index = 1;
	}
	void insert(const char *str)
	{
		int i = 0;
		while(*str != '\0')
		{
			int j = *str - 'a';
			if(trie[i][j] == -1)
			{
				memset(trie[index], -1, sizeof(trie[index]));
				tag[index] = 0;
				trie[i][j] = index++;
			}
			i = trie[i][j];
			++str;
		}
		++tag[i];
	}
	void construct()
	{
		queue<int> qi;
		fail[0] = 0;
		for(int i=0; i<CLD_NUM; ++i)
		{
			if(trie[0][i] != -1)
			{
				fail[trie[0][i]] = 0;
				qi.push(trie[0][i]);
			}
			else
				trie[0][i] = 0;
		}
		while(!qi.empty())
		{
			int it = qi.front();
			qi.pop();
			for(int i=0; i<CLD_NUM; ++i)
			{
				int &val = trie[it][i];
				if(val != -1)
				{
					qi.push(val);
					fail[val] = trie[fail[it]][i];
				}
				else
					val = trie[fail[it]][i];
			}
		}
	}
	int query(const char *str)//返回匹配的模式串个数
	{
		int i = 0, cnt = 0;
		while(*str != '\0')
		{
			int j = *str - 'a';
			while(trie[i][j] == -1 && i != 0)//无法匹配当前字符，回退到其fail指针
				i = fail[i];
			i = trie[i][j];
			i = (i==-1?0:i);
			int temp = i;
			while(temp != 0 && tag[temp] != -1)
			{
				cnt += tag[temp];
				tag[temp] = -1;
				temp = fail[temp];//跳到当前字符的最大后缀，统计模式串出现个数
			}
			++str;
		}
		return cnt;
	}
};
//point method
class ACAuto{
const int ALPHA = 26;//字符数 
struct Node
{
	Node *fail;
	Node *trie[ALPHA];
	int index;// count the words
	Node()
	{
		fail = NULL;
		memset(trie, NULL, sizeof(trie));
		index = 0;
	}
};
void insert(const char *str, Node *root)
{
	if(str == NULL || root == NULL)
		return;	
	while(*str != '\0')
	{
		int i = *str - 'a';
		if(root->trie[i] == NULL)
			root->trie[i] = new Node();
		root = root->trie[i];
		++str;
	}
	++root->index;
}
void construct(Node *root)
{
	if(root == NULL)
		return;
	queue<Node *> qn;
	root->fail = root;
	for(int i=0; i<ALPHA; ++i)
	{
		if(root->trie[i] != NULL)
		{
			qn.push(root->trie[i]);
			root->trie[i]->fail = root;
		}		
	}
	while(!qn.empty())
	{
		Node *cur = qn.front();
		qn.pop();
		for(int i=0; i<ALPHA; ++i)
		{
			if(cur->trie[i] != NULL)
			{
				qn.push(cur->trie[i]);				
				if(cur->fail == NULL)
					cur->fail = root;
				Node *f = cur->fail;
				while(f != NULL)
				{
					if(f->trie[i] != NULL)
					{
						cur->trie[i]->fail = f->trie[i];
						break;
					}
					else
					{
						if(f == root)
							break;
						else
							f = f->fail;						
					}
				}				
			}			
		}
	}
}
int query(const char *str, Node *root)
{
	if(str == NULL || root == NULL)
		return 0;
	int cnt = 0;
	Node *cur = root;
	while(*str != '\0')
	{
		int i = *str - 'a';		
		while(cur->trie[i] == NULL && cur != root)
			cur = cur->fail;
		cur = (cur->trie[i] == NULL) ? root : cur->trie[i];
		Node *tmp = cur;
		while(tmp != root && tmp->index > 0)
		{
			cnt += tmp->index;
			tmp->index = 0;
			tmp = tmp->fail;
		}
		++str;
	}
	return cnt;
}
void deleteNode(Node *root)
{
	queue<Node *> qn;
	for(int i=0; i<ALPHA; ++i)
	{
		if(root->trie[i] != NULL)
			qn.push(root->trie[i]);
	}
	delete root;
	while(!qn.empty())
	{
		Node *cur = qn.front();
		qn.pop();
		for(int i=0; i<ALPHA; ++i)
		{
			if(cur->trie[i] != NULL)
				qn.push(cur->trie[i]);
		}
		delete cur;
	}
}
};

//1.15 string or array + - * /
//a. an arrary is a number, add 1
int add1(int a[], int n)
{
	if(a == NULL || n < 1)
		return 1<<31;
	int i = 0, count = 0;
	for(i=0; i<n; ++i)
	{
		if(a[i] > 9 || a[i] < 0)
			return 1<<31;
		if(a[i] == 9)
			++count;
	}
	if(count == n)
		return 1<<31;
	if(a[n-1] < 9)
		a[n-1] += 1;
	else
	{
		for(i=n-1; i>=0; --i)
		{
			if(a[i] < 9)
			{
				a[i] += 1;
				break;
			}
			else
				a[i] = 0;
		}
	}
	return 1;
}
//vector, 时间复杂度O(n)，空间复杂度O(1)
void plus1(vector<int> &arr)
{
	int c = 1;//carry
	for_each(arr.rbegin(), arr.rend(), [&c](int &d){
		d += c;
		c = d / 10;
		d %= 10; });
		if (c > 0)
			arr.insert(arr.begin(), 1);
}
void plus1(vector<int> &arr)
{
	int c = 1;//carry
	for (auto i = arr.rbegin(); i != arr.rend(); ++i)
	{
		*i += c;
		c = *i / 10;
		*i %= 10;
	}
	if (c > 0)
		arr.insert(arr.begin(), 1);
}

//b. Given two binary strings, return their sum(also a binary string).
string binarySum(string s1, string s2)
{
	int n = s1.length() > s2.length() ? s1.length() : s2.length();
	string sum;
	int carry = 0;
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	for (int i = 0; i < n; ++i)
	{
		int a = i < s1.size() ? s1[i] - '0' : 0;
		int b = i < s2.size() ? s2[i] - '0' : 0;
		int val = (a + b + carry) % 2;
		carry = (a + b + carry) / 2;
		sum.insert(sum.begin(), val + '0');
	}
	if (carry == 1)
		sum.insert(sum.begin(), '1');
	return sum;
}

//c. Given two numbers represented as strings, return multiplication of the numbers as a string. Note: The numbers can be arbitrarily large and are non - negative.
// 一个字符对应一个int,时间复杂度O(n*m)，空间复杂度O(n+m)
vector<int> operator*(const vector<int> &x, const vector<int> &y)
{
	vector<int> z(x.size() + y.size());
	for (int i = 0; i < x.size(); ++i)
	{
		for (int j = 0; j < y.size(); ++j)
		{
			z[i + j] += x[i] * y[j];
			z[i + j + 1] += z[i + j] / 10;
			z[i + j] %= 10;
		}
	}
	return z;
}
class Solution
{
public:
	vector<int> bigInt(const string &s)
	{
		vector<int> n;
		transform(s.rbegin(), s.rend(), back_inserter(n), [](char c){return c - '0'; });
		return n;
	}
	string num2str(const vector<int> &n)
	{
		string str;
		transform(find_if(n.rbegin(), prev(n.rend()), [](char c){return c > '\0'; }), n.rend(), back_inserter(str),
			[](char c){return c + '0'; });
		return str;
	}
	string multiply(string n1, string n2)
	{
		return num2str(bigInt(n1) * bigInt(n2));
	}
};
// 9 个字符对应一个int64,时间复杂度O(n*m/81)，空间复杂度O((n+m)/9)
class BigInt
{
private:
	typedef long long int64;
	//一个数组元素对应9 个十进制位，即数组是亿进制的,因为1000000000 * 1000000000 没有超过2 ^ 63 - 1
	const static int BIGINT_RADIX = 1000000000;//10
	const static int RADIX_LEN = 9;
	vector<int64> elems;//万进制整数
	BigInt(const vector<int64> num) : elems(num){}
public:
	BigInt(string s)//构造函数，将字符串转化为大整数.
	{
		elems.reserve(s.size() / RADIX_LEN + 1);
		for (int i = s.size(); i > 0; i -= RADIX_LEN)// [i-RADIX_LEN, i)
		{
			int temp = 0;
			const int low = max(i - RADIX_LEN, 0);
			for (int j = low; j < i; ++j)
				temp = temp * 10 + s[j] - '0';
			elems.push_back(temp);
		}
	}
	BigInt(){}
	string num2str()
	{
		stringstream result;
		bool start = false;//用于跳过前导0
		for (auto i = elems.rbegin(); i != elems.rend(); ++i)
		{
			if (start)// 如果多余的0 已经都跳过，则输出
				result << setw(RADIX_LEN) << setfill('0') << *i;
			else
			{
				result << *i;
				start = true;//碰到第一个非0 的值，就说明多余的0 已经都跳过
			}
		}
		if (!start)
			return "0";// when x  = 0
		else
			return result.str();
	}
	static BigInt multiply(const BigInt &x, const BigInt &y)
	{
		const int m = x.elems.size();
		const int n = y.elems.size();
		vector<int64> z(m + n, 0);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				z[i + j] += x.elems[j] * y.elems[i];
				if (z[i + j] >= BIGINT_RADIX)//要进位
				{
					z[i + j + 1] += z[i + j] / BIGINT_RADIX;
					z[i + j] %= BIGINT_RADIX;
				}
			}
		}
		while (z.back() == 0)
			z.pop_back();//没有进位，去掉最高位的0
		return BigInt(z);
	}
	string multi(string n1, string n2)
	{
		BigInt x(n1);
		BigInt y(n2);
		return multiply(x, y).num2str();
	}
};

//1.16 integer, char or string transformation
//a. change upper case to lower case letters
char* u2l(char *str)
{
	if (str == NULL)
		return NULL;	
	int len = strlen(str);
	for(int i=0; str[i] != '\0'; ++i)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	FILE *fp;
	if((fp=fopen("test.txt","a+")) == NULL)
	{
		cout<<"open file error"<<endl;
		exit(0);
	}
	fwrite(str,sizeof(char),sizeof(char)*len,fp);
	fclose(fp);
	return str;
}
//b. decimal to hex or octal
char *d2h(unsigned int val, int format)//format  = 16 hex, = 8 octal
{
	if(val < 0 || (format != 16 && format != 8))
		return NULL;
	char chex[] = "0123456789ABCDEF";
	int len = 0, cur = val;
	while(cur > 0)
	{
		cur /= 10;
		++len;//get val bit
	}
	char *str = new char[len*2];
	memset(str, 0, sizeof(char)*(len*2));
	int i = 0;
	while(val > 0)
	{
		str[i++] = chex[val%format];
		val /= format;
	}
	int j = 0;
	--i;
	while(j < i)
	{
		swap(str[i--], str[j++]);
	}
	return str;
}

//c. Print number 0~999,999 to word mode
string GetWords(int num)
{
	string s = "";
	if(num < 0 || num > 1000)
	{
		cout<<"Please input the number between 0~1,000."<<endl;
		return s;
	}
	char *c1[10] = {"","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
	char *c11[10] = {"Ten","Eleven ","Twelve ","Thirteen ","Fourteen ","Fifteen ","Sixteen ","Seventeen "," Eighteen ","Nineteen "};
	char *c20[8] = {"Twenty ","Thirty ","Forty ","Fifty ","Sixty ","Seventy ","Eighty ","Ninety "};
	int hun = num/100;//hundred
	int tens = num%100;
	int single = num%10;
	bool flag = false;
	if(hun > 0)
	{
		s = (string)c1[hun];
		s += " Hundred ";
		flag = true;
	}
	if(tens > 0)
	{
		if(flag)
			s += "and ";
		if(tens < 10)
			s += c1[tens];
		else if(tens >= 10 && tens <20)
			s += c11[tens - 10];
		else
		{
			s += c20[tens/10 - 2];
			s += c1[single];
		}
	}
	return s;
}
string Num2Str(int num)
{
	string s = "";
	if(num < 0 || num > 999999)
	{
		cout<<"Please input the number between 0~999,999."<<endl;
		return s;
	}
	else if(num == 0)
	{
		s = "Zero";
		return s;
	}	
	else if(num < 1000)
		s = GetWords(num);
	else
	{
		s = GetWords(num/1000);
		s += " Thousand, ";
		s += GetWords(num%1000);
	}
	return s;
}

//d. Given the sequence S1 = {a,b,c,d,…,x,y,z,aa,ab,ac…. } and given that this sequence corresponds (term for term) to the sequence S2 = {0,1,2,3,….}. 
//Write code to convert an element of S2 to the corresponding element of S1.
string num2str(int n)
{
	string str(1, 'a' + n % 26);
	n /= 26;
	while (n > 0)
	{
		str = (char)('a' + (n - 1) % 26) + str;
		n = (n - 1) / 26;
	}
	return str;
}
//recursion
void num2strHelp(int n)
{
	if (n == 0)
		return;
	num2strHelp((n - 1) / 26);
	cout << (char)('a' + (n - 1) % 26);
}
void num2strRec(int n)
{
	num2strHelp(n / 26);
	cout << (char)('a' + n % 26);
}

//e. Validate if a given string is numeric. as 标准库中的strtod()
bool isNumber(char *s)
{
	char *endptr;
	strtod(s, &endptr);
	if (endptr == s)
		return false;
	while (*endptr)
	{
		if (!isspace(*endptr))
			return false;
		++endptr;
	}
	return true;
}

//f. Convert an integer to a roman numeral. 1 <= n <= 3999.
string int2roman(int num)//时间复杂度O(num)，空间复杂度O(1)
{
	const int radix[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	const string symbol[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	string roman;
	for (int i = 0; num > 0; ++i)
	{
		int count = num / radix[i];
		num %= radix[i];
		while (count > 0)
		{
			roman += symbol[i];
			--count;
		}
	}
	return roman;
}

//g. Convert a roman numeral to an integer. 1 <= n <= 3999, 时间复杂度O(n)，空间复杂度O(1)
inline int mapc(const char c)
{
	switch (c)
	{
	case 'I': return 1;
	case 'V': return 5;
	case 'X': return 10;
	case 'L': return 50;
	case 'C': return 100;
	case 'D': return 500;
	case 'M': return 1000;
	default: return 0;
	}
}
int roman2int(string s)
{
	int res = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (i > 0 && mapc(s[i]) > mapc(s[i - 1]))
			res += mapc(s[i]) - 2 * mapc(s[i - 1]);
		else
			res += mapc(s[i]);
	}
	return res;
}

//h. Implement atoi to convert a string to an integer.时间复杂度O(n)，空间复杂度O(1)
int atoi(const char *str)
{
	int num = 0, sign = 1, i = 0;
	int n = strlen(str);
	while (str[i] == ' ' && i < n)
		++i;
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		++i;
		sign = -1;
	}
	for (; i < n; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
			return sign == -1 ? INT_MIN : INT_MAX;
		num = num * 10 + str[i] - '0';
	}
	return num * sign;
}

//1.17 Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
//If the last word does not exist, return 0. Note: A word is defined as a character sequence consists of non - space characters only.
//STL, 时间复杂度O(n)，空间复杂度O(1), Given s = "Hello World", return 5.
int lengthOfLastWord(const char *s)
{
	const string str(s);
	auto first = find_if(str.rbegin(), str.rend(), isalpha);
	auto last = find_if_not(first, str.rend(), isalpha);
	return distance(first, last);
}
//顺序扫描，记录每个word 的长度, 时间复杂度O(n)，空间复杂度O(1)
int lenLastWord(const char *s)
{
	int len = 0;
	while (*s)
	{
		if (*s++ != ' ')
			++len;
		else if (*s && *s != ' ')
			len = 0;
	}
	return len;
}

/*1.18 Rearrange an array using swap with 0. You have two arrays src, tgt, containing two permutations of the numbers 0..n-1. You would like to rearrange src so that it equals tgt. The only allowed operations is “swap a number with 0”, e.g. {1,0,2,3} -> {1,3,2,0} 
You can use an extra O(n) space to get a solution with O(n) time complexity. shortest path algorithm will resolve it.
1. In a pre-processing step, go through the "source" array, compute the position of each of the 0 to n elements and store in the auxiliary 'position' array. 
2. Start at the heads of both source and target array and compare the elements
3. If the elements are the same or the value of the target array ==0 proceed to the next elements. Otherwise go to step 4
4. Find position of 0 using the 'position' array and swap it with the current element 'e' in the source array and update the positions of 0 and 'e' in the position array.
Now swap 0 with the target element(found again using the position array) and after the swap, update their positions in the position array. Advance the pointers of both source and target arrays.
5. Repeat steps 3 & 4 until all the elements are processed.*/
int rearrangeBySwap0(int src[], int tar[], int num)//return swap times
{
	if(src == NULL || tar == NULL || num < 2)
		return 0;
	int swapTimes = 0;// record swap times
	int tempPos = 0;// save 0 position
	int *pos = new int[num];//record element position in src array
	memset(pos, 0, sizeof(int)*num);
	for(int i=0; i<num; ++i)
	{
		pos[src[i]] = i;
	}
	for(int i=0; i<num; ++i)
	{
		if(src[i] == tar[i] || tar[i] == 0)//only can swap with 0, so pass 0
			continue;
		else
		{
			if(src[i] == 0)
			{
				swap(src[i], src[pos[tar[i]]]);
				++swapTimes;
				pos[0] = pos[tar[i]];
				pos[tar[i]] = i;
			}
			else
			{
				swap(src[i], src[pos[0]]);
				pos[src[pos[0]]] = pos[0];
				swap(src[i], src[pos[tar[i]]]);
				pos[0] = pos[tar[i]];
				pos[tar[i]] = i;
				swapTimes += 2;
			}
		}
	}
	delete[] pos;
	pos = NULL;
	return swapTimes;
}

//1.19 Input: A long array A[], and a window width w, Output: An array B[], B[i] is the maximum value of from A[i] to A[i+w-1]
//use deque time O(n), use heap time is O(nlogn)
void maxSlidingWindow(int a[], int n, int w, int b[])
{
	deque<int> dq;
	for(int i=0; i<w; ++i)
	{
		while(!dq.empty() && a[i] >= a[dq.back()])
			dq.pop_back();
		dq.push_back(i);
	}
	for(int i=w; i<n; ++i)
	{
		b[i-w] = a[dq.front()];
		while(!dq.empty() && a[i] >= a[dq.back()])
			dq.pop_back();
		while(!dq.empty() && dq.front() <= i-w)
			dq.pop_front();
		dq.push_back(i);
	}
	b[n-w] = a[dq.front()];
}

//1.20 Find the k-th Smallest Element in the Union of Two Sorted Arrays, time O(lg m + lg n) method faster than O(k)
int findKthSmall(int a[], int m, int b[], int n, int k)
{
	assert(m >= 0); assert(n >= 0); assert (k > 0); assert(k <= m+n);
	int i = (int)((double)m/(m+n)*(k-1));
	int j = (k-1) - i;// invariant: i + j = k-1
	assert(i>=0); assert(j>=0); assert(i<=m); assert(j<=n);
	//Note: A[-1] = -INF and A[m] = +INF to maintain invariant
	int ai_1 = ((i == 0) ? INT_MIN : a[i-1]);
	int bj_1 = ((j == 0) ? INT_MIN : b[j-1]);
	int ai = ((i == m) ? INT_MAX : a[i]);
	int bj = ((j == n) ? INT_MAX : b[j]);

	if(bj_1 < ai && ai < bj)
		return ai;
	else if(ai_1 < bj && bj < ai)
		return bj;
	assert((ai > bj && ai_1 > bj) || (ai < bj && ai < bj_1));
	// if none of the cases above, then it is either:
	if(ai < bj)// exclude Ai and below portion, Bj and above portion
		return findKthSmall(a+i+1, m-i-1, b, j, k-i-1);
	else// exclude bj and below portion, ai and above portion
		return findKthSmall(a, i, b+j+1, n-j-1, k-j-1);
}

//1.21 There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. Time O(log(m+n)).
double getMedianBase(int med, int a[], int n)
{
	if(n == 1)
		return (med+a[0])/2.0;
	if(n%2 == 0)
	{
		int i = a[n/2-1], j = a[n/2];
		if(med <= i)
			return i;
		else if(med <= j)
			return med;
		else
			return j;
	}
	else
	{
		int i = a[n/2-1], j = a[n/2]; k = a[n/2+1];
		if(med <= i)
			return (i+j)/2.0;
		else if(med <= k)
			return (med+j)/2.0;
		else
			return (j+k)/2.0;
	}
}
double getMedianBase2(int med1, int med2, int a[], int n)
{
	if(n%2 == 0)
	{
		int i = (((n/2-2) >= 0) ? a[n/2-2] : INT_MIN);
		int j = a[n/2-1], k = a[n/2];
		int l = (((n/2+1) <= n-1) ? a[n/2+1] : INT_MAX);
		if(med2 <= j)
			return (j+max(med2,i))/2.0;
		else if(med1 <= j)
			return (j+min(med2,k))/2.0;
		else if(med1 >= k)
			return (k+min(med1,l))/2.0;
		else if(med2 >= k)
			return (k+max(med1,j))/2.0;
		else//i<med1<=med2<j
			return (med1+med2)/2.0;
	}
	else
	{
		int i = a[n/2-1], j = a[n/2]; k = a[n/2+1];
		if(med1 >= j)
			return min(med1, k);
		else if(med2 <= j)
			return max(i, med2);
		else//med1 < j < med2
			return j;
	}
}
double getMedianSingleArray(int a[], int n)
{
	assert(n>0);
	return ((n%2 == 1) ? a[n/2] : (a[n/2-1]+a[n/2])/2.0);
}
double getMedianSortedArray(int a[], int m, int b[], int n)
{
	assert(m + n >= 1);
	if(m == 0)
		return getMedianSingleArray(b, n);
	else if(n == 0)
		return getMedianSingleArray(a, m);
	else if(m == 1)
		return getMedianBase(a[0], b, n);
	else if(n == 1)
		return getMedianBase(b[0], a, m);
	else if(m == 2)
		return getMedianBase2(a[0], a[1], b, n);
	else if(n == 2)
		return getMedianBase2(b[0], b[1], a, m);
	int i = m/2, j = n/2, k = 0;
	if(a[i] <= b[j])
	{
		k = ((m%2 == 0)? min(i-1, n-j-1) : min(i, n-j-1));
		return getMedianSortedArray(a+k, m-k, b, n-k);
	}
	else
	{
		k = ((n%2 == 0) ? min(m-i-1, j-1) : min(m-i-1, j));
		return getMedianSortedArray(a, m-k, b+k, n-k);
	}
}
//better, time O(log(m+n))，space O(log(m+n))
int findkth(int a[], int m, int b[], int n, int k)
{
	//always assume that m is equal or smaller than n
	if (m > n)
		return findkth(b, n, a, m, k);
	if (m == 0)
		return b[k - 1];
	if (k == 1)
		return min(a[0], b[0]);
	//divide k into two parts
	int ia = min(k / 2, m), ib = k - ia;
	if (a[ia - 1] < b[ib - 1])
		return findkth(a + ia, m - ia, b, n, k - ia);
	else if (a[ia - 1] > b[ib - 1])
		return findkth(a, m, b + ib, n - ib, k - ib);
	else
		return a[ia - 1];
}
double getMedian(int a[], int m, int b[], int n)
{
	int all = m + n;
	if (all & 0x1)
		return findkth(a, m, b, n, all / 2 + 1);
	else
		return (findkth(a, m, b, n, all / 2) + findkth(a, m, b, n, all / 2 + 1)) / 2.0;
}

//1.22 Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for “abcabcbb” is “abc”, which the length is 3. For “bbbbb” the longest substring is “b”, with the length of 1.
int maxUniqueSubstr(string s)
{
	int n = s.length();
	int i=0, j=0, maxlen = 0;
	bool exist[256] = {false};
	while(i < n)
	{
		if(exist[s[i]])
		{
			maxlen = max(maxlen, i-j);
			while(s[i] != s[j])
			{
				exist[s[j]] = false;
				++j;
			}
			++i;
			++j;
		}
		else
		{
			exist[s[i]] = true;
			++i;
		}
	}
	maxlen = max(maxlen, n-j);
	return maxlen;
}
//从左往右扫描，当遇到重复字母时，以上一个重复字母的index+1，作为新的搜索起始位置，直到最后一个字母，time O(n), space O(1)
int uniqueSubStringLen(string str)
{
	const int CHAR = 26;
	int last[CHAR] = { 0 };// // 记录字符上次出现过的位置
	memset(last, -1, sizeof(last));
	int start = 0;// 记录当前子串的起始位置
	int maxLen = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (last[str[i] - 'a'] >= start)
		{
			maxLen = max(i - start, maxLen);
			start = last[str[i] - 'a'] + 1;
		}
		last[str[i] - 'a'] = i;
	}
	return max((int)str.size() - start, maxLen);
}

/*1.23 Given a set T of characters and a string S, find the minimum window in S which will contain all the characters in T in complexity O(n).
eg, S = “ADOBECODEBANC”, T = “ABC”, Minimum window is “BANC”. Returns true if find window, and starting and ending position of the minimum window.*/
bool minwin(char *str, char *pat, int &begin, int &end)// time O(n)
{
	if (str == NULL || pat == NULL)
		return false;
	int n = strlen(str);
	int m = strlen(pat);
	const int ASCII = 256;
	int need2find[ASCII] = { 0 };// needToFind stores the total count of a character in T
	for (int i = 0; i < m; ++i)
		++need2find[pat[i]];
	int found[ASCII] = { 0 };//found stores the total count of a character met so far
	int minlen = INT_MAX, cnt = 0;
	for (int b = 0, e = 0; e < n; ++e)
	{
		if (need2find[str[e]] == 0)
			continue;// skip characters not in T
		++found[str[e]];
		if (found[str[e]] <= need2find[str[e]])
			++cnt;// store the total characters in T that’s met so far
		// if window constraint is satisfied
		if (cnt == m)
		{
			// advance begin index as far right as possible, stop when advancing breaks window constraint.
			while (need2find[str[b]] == 0 || found[str[b]] > need2find[str[b]])
			{
				if (found[str[b]] > need2find[str[b]])
					--found[str[b]];
				++b;
			}
			// update minWindow if a minimum length is met
			if (e - b + 1 < minlen)
			{
				begin = b;
				end = e;
				minlen = e - b + 1;
			}
		}
	}
	return cnt == m ? true : false;
}
string minWin(string s, string t)
{
	if (s.empty() || s.size() < t.size())
		return "";
	const int ASCII = 256;
	int need2find[ASCII] = { 0 };
	int found[ASCII] = { 0 };
	for (int i = 0; i < t.size(); ++i)
		++need2find[t[i]];
	int minWidth = INT_MAX, minStart = 0;
	int winStart = 0, count = 0;
	for (int winEnd = 0; winEnd < s.size(); ++winEnd)
	{
		if (need2find[s[winEnd]] > 0)
		{
			++found[s[winEnd]];
			if (found[s[winEnd]] <= need2find[s[winEnd]])
				++count;
		}
		if (count == t.size())
		{
			while (need2find[s[winStart]] == 0 || found[s[winStart]] > need2find[s[winStart]])
			{
				--found[s[winStart]];
				++winStart;
			}
			if (minWidth > winEnd - winStart + 1)
			{
				minStart = winStart;
				minWidth = winEnd - winStart + 1;
			}
		}
	}
	if (minWidth == INT_MAX)
		return "";
	else
		return s.substr(minStart, minWidth);
}

//1.24 Searches a value in an sorted array[n][m] as Table[i][j] ≤ Table[i][j + 1], Table[i][j] ≤ Table[i + 1][j]*/
// step-wise linear search, time O(n)
bool findNumInMatrix(int **a, int n, int m, int val)
{
	bool find = false;
	int r = 0, c = m - 1;
	while (c >= 0 && r < n)
	{
		if (a[r][c] > val)
			--c;
		else if (a[r][c] < val)
			++r;
		else
		{
			find = true;
			cout << "Find " << val << " at a[" << r << "][" << c << "]" << endl;
			break;
		}
	}
	return find;
}

//1.25 a. Given a matrix of m * n elements, write a function that prints the elements in the array in a spiral manner.
void spiral(int **a, int m, int n, int k)//k=0;
{
	if (m < 1 || n < 1)
		return;
	if (m == 1)
	{
		for (int j = 0; j < n; ++j)
			cout << a[k][k + j] << " ";
		return;
	}
	if (n == 1)
	{
		for (int i = 0; i < m; ++i)
			cout << a[k + i][k] << " ";
		return;
	}
	// print from top left
	for (int j = 0; j < n - 1; ++j)
		cout << a[k][k + j] << " ";
	// print from top right
	for (int i = 0; i < m - 1; ++i)
		cout << a[k + i][n - 1 + k];
	// print from bottom right
	for (int j = 0; j < n - 1; ++j)
		cout << a[k + m - 1][k + n - 1 - j];
	//print from bottom left
	for (int i = 0; i < m - 1; ++i)
		cout << [k + m - 1 - i][k] << " ";

	spiral(a, m - 2, n - 2, k + 1);
}
//better 时间复杂度O(n^2)，空间复杂度O(1)
vector<int> spiral(vector<vector<int>> &matrix)
{
	vector<int> result;
	if (matrix.empty())
		return result;
	int bx = 0, ex = matrix[0].size() - 1;
	int by = 0, ey = matrix.size() - 1;
	while (true)
	{
		// From top left to right
		for (int j = bx; j <= ex; ++j)
			result.push_back(matrix[by][j]);
		if (++by > ey) break;
		// From right top to bottom
		for (int i = by; i <= ey; ++i)
			result.push_back(matrix[i][ex]);
		if (bx > --ex) break;
		// From bottom right to left
		for (int j = ex; j >= bx; --j)
			result.push_back(matrix[ey][j]);
		if (by > --ey) break;
		//left From bottom to top
		for (int i = ey; i >= by; --i)
			result.push_back(matrix[i][bx]);
		if (++bx > ex) break;
	}
	return result;
}

//b. Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order. 时间复杂度O(n^2)，空间复杂度O(n^2)
vector<vector<int>> spiralMatrix(int n)
{
	vector<vector<int>> matrix(n, vector<int>(n));
	int b = 0, e = n - 1, num = 1;
	while (b < e)
	{
		for (int j = b; j < e; ++j)
			matrix[b][j] = num++;
		for (int i = b; i < e; ++i)
			matrix[i][e] = num++;
		for (int j = e; j > b; --j)
			matrix[e][j] = num++;
		for (int i = e; i > b; --i)
			matrix[i][b] = num++;
		++b; --e;
	}
	if (b == e)
		matrix[b][e] = num;
	return matrix;
}

//1.26 a. Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
//If such arrangement is not possible, it must rearrange it as the lowest possible order(ie, sorted in ascending order).
//The replacement must be in - place, do not allocate extra memory. 1, 2, 3 → 1, 3, 2;  3, 2, 1 → 1, 2, 3
template<typename T> bool next_permutation(T b, T e)
{
	// Get a reversed range to simplify reversed traversal.
	auto rb = reverse_iterator<T>(e);
	auto re = reverse_iterator<T>(b);
	// Begin from the second last element to the first element.
	auto pivot = next(rb);
	// Find pivot, which is the first element that is no less than its successor. Prev is used since`pivort is a `reversed_iterator`.
	while (pivot != re && *pivot >= *prev(pivot))
		++pivot;
	// No such elemenet found, current sequence is already the largest permutation, then rearrange to the first permutation and return false.
	if (pivot == re)
	{
		reverse(rb, re);
		return false;
	}
	// Scan from right to left, find the first element that is greater than pivot
	auto change = find_if(rb, pivot, bind1st(less<int>(), *pivot));
	swap(*change, *pivot);
	reverse(rb, pivot);
	return true;
}

//b. The set [1,2,3,⋯,n] contains a total of n! unique permutations. Given n and k, return the kth permutation sequence. 1<n<9
//康托编码，时间复杂度O(n)，空间复杂度O(1)
int factorial(int n)
{
	int result = 1;
	for (int i = 1; i <= n; ++i)
		result *= i;
	return result;
}
template<typename S> S kth_permutation(const S &seq, int k)
{
	int n = seq.size();
	S s(seq);
	S res;
	int base = factorial(n - 1);
	--k;//康托编码从0 开始
	for (int i = n - 1; i > 0; k %= base, base /= i, --i)
	{
		auto a = next(s.begin(), k / base);
		res += *a;//res.push_back(*a);
		s.erase(a);
	}
	res.push_back(s[0]);
	return res;
}
string getPermutation(int n, int k)
{
	string s(n, '0');
	for (int i = 0; i < n; ++i)
		s[i] += i + 1;
	return kth_permutation(s, k);
}

//1.27 find the longest common prefix string amongst an array of strings.
// 纵向扫描，从位置0 开始，对每一个位置比较所有字符串，直到遇到一个不匹配,时间复杂度O(n1+n2+...)
string lcp(vector<string> &vs)
{
	if (vs.empty())
		return "";
	for (int i = 0; i < vs[0].size(); ++i)
	{
		for (int j = 1; j < vs.size(); ++j)
		{
			if (vs[j][i] != vs[0][i])
				return vs[0].substr(0, i);
		}
	}
	return vs[0];
}
// 横向扫描，每个字符串与第0 个字符串，从左到右比较，直到遇到一个不匹配，然后继续下一个字符串, 时间复杂度O(n1+n2+...)
string lcp2(vector<string> &vs)
{
	if (vs.empty())
		return "";
	int len = vs[0].size() - 1;
	for (int i = 1; i < vs.size(); ++i)
	{
		for (int j = 0; j <= len; ++j)
		{
			if (vs[0][j] != vs[i][j])
			{
				len = j - 1;
			}
		}
	}
	return vs[0].substr(0, len + 1);
}

//1.28 The count-and-say sequence is the sequence of integers beginning as follows: 1, 11, 21, 1211, 111221, ... 1 is read off as "one 1" or 11.
// 11 is read off as "two 1s" or 21. 21 is read off as "one 2", then "one 1" or 1211. Given an integer n, generate the nth sequence (string).
string getNext(const string &s)
{
	stringstream ss;
	for (auto i = s.begin(); i != s.end();)
	{
		auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
		ss << distance(i, j) << *i;
		i = j;
	}
	return ss.str();
}
string count2say(int n)//时间复杂度O(n^2)，空间复杂度O(n)
{
	string s("1");
	while (--n)
		s = getNext(s);
	return s;
}

//1.29 Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary). You may assume that the intervals were initially sorted according to their start times.
//Example 1: Given intervals[1, 3], [6, 9], insert and merge[2, 5] in as[1, 5], [6, 9]. Example 2 : Given[1, 2], [3, 5], [6, 7], [8, 10], [12, 16], insert and merge[4, 9] in as[1, 2], [3, 10], [12, 16].
// 时间复杂度O(n)，空间复杂度O(1)
struct Interval
{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
vector<Interval> insert(vector<Interval> &vi, Interval in)
{
	vector<Interval>::iterator it = vi.begin();
	while (it != vi.end())
	{
		if (in.end < it->start)
		{
			vi.insert(it, in);
			return vi;
		}
		else if (in.start > it->end)
			++it;
		else
		{
			in.start = min(in.start, it->start);
			in.end = max(in.end, it->end);
			it = vi.erase(it);
		}
	}
	vi.insert(vi.end(), in);
	return vi;
}

//b. Given a collection of intervals, merge all overlapping intervals.
vector<Interval> mergeInterval(vector<Interval> &in)
{
	vector<Interval> result;
	for (int i = 0; i < in.size(); ++i)
		insert(result, in[i]);
	return result;
}

//1.30 You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.
//For example, given: S : "barfoothefoobarman" L : ["foo", "bar"]	You should return the indices : [0, 9].(order does not matter).
// 时间复杂度O(n*m)，空间复杂度O(m)
vector<int> findSubStr(string s, vector<string> &dict)
{
	vector<int> result;
	if (s.size() < 1 || dict.size() < 1)
		return result;
	int len = dict[0].length();
	int allLen = len * dict.size();
	if (s.length() < allLen)
		return result;
	unordered_map<string, int> count, cur;
	for (auto word : dict)
		++count[word];
	for (auto i = begin(s); i <= prev(end(s), allLen); ++i)
	{
		cur = count;
		for (auto j = i; j != next(i, allLen); j += len)
		{
			auto pos = cur.find(string(j, next(j, len)));
			if (pos == cur.end() || pos->second == 0)
				break;
			if (--pos->second == 0)
				cur.erase(pos);
		}
		if (cur.size() == 0)
			result.push_back(distance(begin(s), i));
	}
	return result;
}

//1.31 a. Given numRows, generate the first numRows of Pascal’s triangle. For example, given numRows = 5, Return [1],[1, 1], [1, 2, 1],	[1, 3, 3, 1],[1, 4, 6, 4, 1]
//用队列，计算下一行时，给上一行左右各加一个0，然后下一行的每个元素，就等于左上角和右上角之和. 另一种思路，下一行第一个元素和最后一个元素赋值为1，中间的每个元素，等于上一行的左上角和右上角元素之和。
//从左到右,时间复杂度O(n^2)，空间复杂度O(n) 
vector<vector<int>> pascal(int row)
{
	vector<vector<int>> result;
	if (row < 1)
		return result;
	result.push_back(vector<int>(1, 1));//first row
	for (int i = 2; i <= row; ++i)
	{
		vector<int> cur(i, 1);
		vector<int> &pre = result[i - 2];//up row
		for (int j = 1; j < i - 1; ++j)
			cur[j] = pre[j - 1] + pre[j];//左上角和右上角之和
		result.push_back(cur);
	}
	return result;
}
//Given an index k, return the kth row of the Pascal’s triangle. 从右到左, 滚动数组，时间复杂度O(n^2)，空间复杂度O(n)
vector<vector<int>> pascaltri(int r)
{
	vector<vector<int>> result;
	vector<int> row;
	for (int i = 1; i <= r; ++i)
	{
		for (int j = i - 2; j > 0; --j)
			row[j] = row[j - 1] + row[j];
		row.push_back(1);//this is the kth row
		result.push_back(row);
	}
	return result;
}

//1.32 zigzag pattern: write function "string convert(string text, int nRows)", Example: convert(”PAYPALISHIRING”, 3) return ”PAHNAPLSIIGYIR”.
//要找到数学规律, 对于每一层垂直元素的坐标(i,j) = (j + 1)*n + i；对于每两层垂直元素之间的插入元素斜对角元素(i,j) = (j + 1)*n-i, 时间复杂度O(n)，空间复杂度O(1)
string convert(string s, int row)
{
	if (row <= 1 || s.size() <= 1)
		return s;
	string res;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0, index = i; index < s.size(); ++j, index = (2 * row - 2) *j + i)
		{
			res.append(1, s[index]);//垂直元素 
			if (i == 0 || i == row - 1)
				continue;//斜对角元素
			if (index + (row - i - 1) * 2 < s.size())
				res.append(1, s[index + (row - i - 1) * 2]);
		}
	}
	return res;
}

/*1.33 Given an array of words and a length L, format the text such that each line has exactly L characters and is fully(left and right) justified.
You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.
Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the
slots on the right. For the last line of text, it should be left justified and no extra space is inserted between words. Note: Each word is guaranteed not to exceed L in length.
Corner Cases: • A line other than the last line might contain only one word. What should you do in this case? In this case, that line should be left*/
// 时间复杂度O(n)，空间复杂度O(1)
class Solution
{
	vector<string> justify(vector<string> &words, int L)
	{
		vector<string> result;
		int n = words.size();
		if (n == 0 || L < 1)
			return result;
		int begin = 0, len = 0;//beginning of current row, current length
		for (int i = 0; i < n; ++i)
		{
			if (len + words[i].size() + (i - begin) > L)
			{
				result.push_back(connect(words, begin, i - 1, len, L, false));
				begin = i;
				len = 0;
			}
			len += words[i].size();
		}
		result.push_back(connect(words, begin, n - 1, len, L, true));//last row less than L
		return result;
	}
	/*@brief 将words[begin, end] 连成一行
	* @param[in] words 单词列表
	* @param[in] begin 开始
	* @param[in] end 结束
	* @param[in] len words[begin, end] 所有单词加起来的长度
	* @param[in] L 题目规定的一行长度
	* @param[in] is_last 是否是最后一行
	* @return 对齐后的当前行	*/
	string connect(vector<string> &word, int begin, int end, int len, int L, bool isLast)
	{
		string s;
		int n = end - begin + 1;
		for (int i = 0; i < n; ++i)
		{
			s += word[begin + i];
			addSpaces(s, i, n - 1, L - len, isLast);
		}
		if (s.size() < L)
			s.append(L - s.size(), ' ');
		return s;
	}
	/*@brief 添加空格.
	* @param[inout]s 一行
	* @param[in] i 当前空隙的序号
	* @param[in] n 空隙总数
	* @param[in] L 总共需要添加的空额数
	* @param[in] is_last 是否是最后一行*/
	void addSpaces(string &s, int i, int n, int L, bool isLast)
	{
		if (n < 1 || i > n - 1)
			return;
		int space = isLast ? 1 : (L / n + (i < (L%n) ? 1 : 0));
		s.append(space, ' ');
	}
};