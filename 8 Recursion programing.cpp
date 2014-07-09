//8.1 Write a method to generate the nth Fibonacci number.
//recursion method
int fibonacci(int n)
{
	if(n < 0)
	{
		cout<<"Please input a positive number between 0 ~ n"<<endl;
		return -1;
	}
	else if(n == 0)
		return 0;
	else if(n == 1 || n == 2)
		return 1;
	else
	{
		return fibonacci(n-1) + fibonacci(n-2);
	}
}
//iterative method
int fibonacciI(int n)
{
	if(n < 0)
	{
		cout<<"Please input a positive number between 0 ~ n"<<endl;
		return -1;
	}
	else if(n == 0)
		return 0;
	else if(n == 1 || n == 2)
		return 1;
	else
	{
		int fn_1 = 1, fn_2 = 1, fn = 0;
		for(int i=3; i<=n; ++i)
		{
			fn = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = fn;
		}
		return fn;
	}
}
// 求数的n次方，O(logN) method
int pow_logN(int m, int n)
{
	int res = 1;
	while(n > 0)
	{
		//二进制形式11..01中的某一位为1，那么， res就去乘以那一位对应的一个数
		if(n&1)
			res *= m;
		m *= m;//每次res去乘以的数(如果该位为0则不乘)都是上一次那个数的平方
		n >>= 1;
	}
	return res;
}

//8.2 a. Given a collection of numbers, return all possible permutations. For example, [1, 2, 3] have the following permutations : [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], and[3, 2, 1]
//STL, 时间复杂度O(n!)，空间复杂度O(1)
vector<vector<int>> permute(vector<int> &num)
{
	vector<vector<int>> result;
	sort(num.begin(), num.end());
	do{
		result.push_back(num);
	} while (next_permutation(num.begin(), num.end()));
	return result;
}
// 递归，深搜，增量构造法， 时间复杂度O(n!)，空间复杂度O(n)
void dfs(const vector<int> &num, vector<int> &sub, vector<vector<int>> &result)
{
	if (sub.size() == num.size())
	{
		result.push_back(sub);
		return;
	}
	for (auto i : num)
	{
		// 查找i 是否在path 中出现过
		auto pos = find(sub.begin(), sub.end(), i);
		if (pos == sub.end())
		{
			sub.push_back(i);
			dfs(num, sub, result);
			sub.pop_back();
		}
	}
}
vector<vector<int>> permute(vector<int> &num)
{
	sort(num.begin(), num.end());
	vector<vector<int>> result;
	vector<int> sub;
	dfs(num, sub, result);
	return result;
}

//b. Given a collection of numbers that might contain duplicates, return all possible unique permutations. For example, [1, 1, 2] have the following unique permutations : [1, 1, 2], [1, 2, 1], and[2, 1, 1].
void dfs(const vector<int> &num, vector<int> &sub, vector<int> &pos, set<vector<int>> &result, unordered_map<int, int> &mii)
{
	if (sub.size() == num.size())
	{
		result.insert(sub);
		return;
	}
	for (auto i : mii)
	{

		// 查找i是否在map中出现过
		auto p = find(pos.begin(), pos.end(), i.first);
		if (p == pos.end())
		{
			sub.push_back(i.second);
			pos.push_back(i.first);
			dfs(num, sub, pos, result, mii);
			sub.pop_back();
			pos.pop_back();
		}
	}
}
set<vector<int>> permute(vector<int> &num)
{
	sort(num.begin(), num.end());
	set<vector<int>> result;
	unordered_map<int, int> mii;
	for (int i = 0; i < num.size(); ++i)
	{
		mii[i] = num[i];
	}
	vector<int> sub, pos;
	dfs(num, sub, pos, result, mii);
	return result;
}

//8.3 Write a method that returns all subsets of a set.
//对于一个集合，它的子集一共有2^n 个(包括空集和它本身),如果一个集合有n个元素，那么它可以用0到2^n -1 总共2^n 个数的二进制形式来指示。每次我们只需要检查某个二进制数的哪一位为1， 就把对应的元素加入到这个子集就OK
vector<vector<int>> getSubSets(int a[], int n)//二进制法，时间复杂度O(2^n)，空间复杂度O(1)
{
	vector<vector<int>> subsets;
	int max = 1<<n;//set elements less than 32
	for(int i=0; i<max; ++i)
	{
		vector<int> subset;
		int index = 0;
		int j = i;
		while(j > 0)
		{
			if((j&1)==1)
			{
				subset.push_back(a[index]);
			}
			j >>= 1;
			++index;
		}
		subsets.push_back(subset);
	}
	return subsets;
}
//recursion
vector<vector<int>> recuSubSets(int a[], int index, int n)
{
	vector<vector<int>> subsets;
	if(index == n)
	{
		vector<int> subset;
		subsets.push_back(subset);//empty set
	}
	else
	{
		vector<vector<int>> rsubsets = recuSubSets(a, index + 1, n);
		int v = a[index];
		for(int i=0; i< rsubsets.size(); ++i)
		{
			vector<int> subset = rsubsets[i];
			subsets.push_back(subset);
			subset.push_back(v);
			subsets.push_back(subset);
		}
	}
	return subsets;
}
//增量构造法，深搜，时间复杂度O(2^n)，空间复杂度O(n)
static void subset(vector<int> &s, vector<int> &sub, int step, vector<vector<int>> &result)
{
	if (step == s.size())
	{
		result.push_back(sub);
		return;
	}
	// 不选s[step]
	subset(s, sub, step + 1, result);
	// 选s[step]
	sub.push_back(s[step]);
	subset(s, sub, step + 1, result);
	sub.pop_back();
}
vector<vector<int>> subsets(vector<int> &s)
{
	sort(s.begin(), s.end());//output is ascending order
	vector<vector<int>> result;
	vector<int> sub;
	subset(s, sub, 0, result);
	return result;
}
//增量构造法, 迭代版，时间复杂度O(2^n)，空间复杂度O(1)
vector<vector<int>> subsets(vector<int> &vi)
{
	sort(vi.begin(), vi.end());
	vector<vector<int>> result(1);
	for (auto e : vi)
	{
		result.reserve(result.size() * 2);
		auto half = result.begin() + result.size();
		copy(result.begin(), half, back_inserter(result));
		for_each(half, result.end(), [&e](decltype(result[0]) &elem){elem.push_back(e); });
	}
	return result;
}

//b. Given a collection of integers that might contain duplicates, S, return all possible subsets. Note: Elements in a subset must be in non - descending order.The solution set must not contain duplicate subsets.
//recursion，增量构造法，时间复杂度O(2^n)，空间复杂度O(n)
void dfs(vector<int> &s, vector<int>::iterator start, vector<int> &sub, vector<vector<int>> &result)
{
	for (auto i = start; i < s.end(); ++i)
	{
		if (i != start && *i == *(i - 1))
			continue;
		sub.push_back(*i);
		dfs(s, i + 1, sub, result);
		sub.pop_back();
	}
}
vector<vector<int>> subsetDup(vector<int> &s)
{
	sort(s.begin(), s.end());
	vector<vector<int>> result;
	vector<int> sub;
	dfs(s, s.begin(), sub, result);
	return result;
}
// iterator, 增量构造法, 时间复杂度O(2^n)，空间复杂度O(1)
vector<vector<int>> subsetsDup(vector<int> &s)
{
	sort(s.begin(), s.end());
	vector<vector<int>> result(1);
	size_t pre_size = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		int size = result.size();
		for (int j = 0; j < size; ++j)
		{
			if (i == 0 || s[i] != s[i - 1] || j >= pre_size)
			{
				result.push_back(result[j]);
				result.back().push_back(s[i]);
			}
		}
		pre_size = size;
	}
	return result;
}
// 二进制法，时间复杂度O(2^n)，空间复杂度O(1)
vector<vector<int>> subsetDup(vector<int> &s)
{
	sort(s.begin(), s.end());
	// 用set 去重，不能用unordered_set，因为输出要求有序
	set<vector<int>> subset;
	int n = s.size();//size <= 32
	vector<int> sub;
	int max = 1 << n;
	for (int i = 0; i < max; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i & 1 << j)
				sub.push_back(s[j]);
		}
		subset.insert(sub);
		sub.clear();
	}
	vector<vector<int>> result;
	copy(subset.begin(), subset.end(), back_inserter(result));
	return result;
}

//8.4 a. Write a method to compute all permutations of a string
//我们可以把串“abc”中的第0个字符a取出来，然后递归调用permu计算剩余的串“bc” 的排列，得到{bc, cb}。然后再将字符a插入这两个串中的任何一个空位(插空法)， 得到最终所有的排列
vector<string> permu(string s)
{
	vector<string> result;
	if(s == "")
	{
		result.push_back("");
		return result;
	}
	string c = s.substr(0,1);
	vector<string> res = permu(s.substr(1));
	for(int i=0; i<res.size(); ++i)
	{
		string t = res[i];
		for(int j=0; j<=t.length(); ++j)
		{
			string u = t;
			u.insert(j,c);
			result.push_back(u);
		}
	}
	return result;
}
// 然后只需要把取出的字符加到剩余串排列的每个字符前即可
vector<string> permu1(string s)
{
	vector<string> result;
	if(s == "")
	{
		result.push_back("");
		return result;
	}
	for(int i=0; i<s.length(); ++i)
	{
		string c = s.substr(i,1);
		string t = s;
		vector<string> res = permu1(t.erase(i, 1));
		for(int j=0; j<res.size(); ++j)
			result.push_back(c + res[j]);
	}
	return result;
}
// C code without use extra space
void permute(char *str, int begin, int end)
{
	if(begin > end)
		return;
	else if(begin == end)
		printf("%s\n",str);
	else
	{
		for(int i=begin; i<=end; ++i)
		{
			swap(*(str+begin),*(str+i));
			permute(str, begin+1, end);
			swap(*(str+begin), *(str+i));
		}
	}
}

//b. Print all permutations with repetition of characters, Repetition of characters is allowed. Print these permutations in lexicographically sorted order 
//Input: AB Ouput: AA  AB   BA  BB
void permuteSortRecur(char *str, char *data, int last, int index)
{
	for(int i=0; i<=last; ++i)
	{
		data[index] = str[i];
		if(index == last)
			printf("%s\n", data);
		else
			permuteSortRecur(str, data, last, index+1);
	}
}
void permuteSort(char *str)
{
	int len = strlen(str);
	char *data = (char*)malloc(sizeof(char)*(len+1));
	data[len] = '\0';
	sort(str, str+len);
	permuteSortRecur(str, data, len-1, 0);
	free(data);
	data = NULL;
}

//c. Print all possible strings of length k that can be formed from a set of n characters
//Input: set[] = {'a', 'b'}, k = 3, Output: aaa aab aba abb baa bab bba bbb
//kPermute(ca, "", 2,3); prefix = "";
void kPermute(char *str, string prefix, int strlen, int k)
{
	if(k == 0 || str == NULL)
	{
		cout<<prefix<<endl;
		return;
	}
	for(int i=0; i<strlen; ++i)
	{
		string sall = prefix + str[i];
		kPermute(str, sall, strlen, k-1);
	}
}

//d. Given an array of size n, generate and print all possible combinations of r elements in array.
//For example, if input array is {1, 2, 3, 4} and r is 2, then output should be {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4} and {3, 4}.
/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed 
   combinationUtil(arr, data, 0, 3, 0, r);*/
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
	// Current combination is ready to be printed, print it
	if (index == r)
	{
		for (int j=0; j<r; j++)
			printf("%d ", data[j]);
		printf("\n");
		return;
	}
	// replace index with all possible elements. The condition
	// "end-i+1 >= r-index" makes sure that including one element
	// at index will make a combination with remaining elements
	// at remaining positions
	for (int i=start; i<=end && end-i+1 >= r-index; ++i)
	{
		data[index] = arr[i];
		combinationUtil(arr, data, i+1, end, index+1, r);
	}
}

//e. Given two integers n and k, return all possible combinations of k numbers out of 1...n.
// 深搜，递归, 时间复杂度O(n!)，空间复杂度O(n)
void dfs(int n, int k, int start, int cur, vector<int> &sub, vector<vector<int>> &result)// start，开始的数, cur，已经选择的数目
{
	if (cur == k)
	{
		result.push_back(sub);
	}
	for (int i = start; i <= n; ++i)
	{
		sub.push_back(i);
		dfs(n, k, i + 1, cur + 1, sub, result);
		sub.pop_back();
	}
}
vector<vector<int>> combine(int n, int k)
{
	vector<vector<int>> result;
	vector<int> sub;
	dfs(n, k, 1, 0, sub, result);
	return result;
}
//迭代，use prev_permutation(), 时间复杂度O((n-k)!)，空间复杂度O(n)
vector<vector<int>> combine(int n, int k)
{
	vector<int> val(n);
	iota(val.begin(), val.end(), 1);
	vector<bool> select(n, false);
	fill_n(select.begin(), k, true);
	vector<vector<int>> result;
	do{
		vector<int> sub(k);
		for (int i = 0, index = 0; i < n; ++i)
		{
			if (select[i])
				sub[index++] = val[i];
		}
		result.push_back(sub);
	} while (prev_permutation(select.begin(), select.end()));
	return result;
}

//8.5 Implement an algorithm to print all valid combinations of n-pairs of parentheses.
void printPare(char str[], int n, int open, int close)
{
	if(open < 0 || open > close)
		return;
	if(open == 0 && close == 0)
	{
		for(int i=0;i<n;++i)
			cout<<str[i];
		cout<<endl;
	}
	else
	{
		if(open > 0)
		{
			str[n] = '(';
			printPare(str, n+1, open-1, close); 
		}
		if(close > open)
		{
			str[n] = ')';
			printPare(str, n+1, open, close-1);
		}
	}
}
//时间复杂度O(n)，空间复杂度O(n)
class Solution
{
	vector<string> parenthes(int n)
	{
		vector<string> result;
		if (n > 0)
			generate(n, "", 0, 0, result);
		return result;
	}
	void generate(int n, string s, int l, int r, vector<string> &result)
	{
		// l 表示( 出现的次数, r 表示) 出现的次数
		if (l == n)
		{
			result.push_back(s.append(n - r, ')'));
			return;
		}
		generate(n, s + '(', l + 1, r, result);
		if (l > r)
			generate(n, s + ')', l, r + 1, result);
	}
};
//better
vector<string> generateParenthese(int n)
{
	if (n == 0)
		return vector<string>(1, "");
	if (n == 1)
		return vector<string>(1, "()");
	vector<string> result;
	for (int i = 0; i < n; ++i)
	{
		for (auto in : generateParenthese(i))
		{
			for (auto out : generateParenthese(n - i - 1))
				result.push_back("(" + in + ")" + out);
		}
	}
	return result;
}

//b. Check for balanced parentheses in an expression
bool compareBracket(char c1, char c2)
{
	if(c1 == '(' && c2 == ')')
		return true;
	else if(c1 == '[' && c2 == ']')
		return true;
	else if(c1 == '{' && c2 == '}')
		return true;
	else
		return false;
}
bool isBlancedBracket(char ch[])
{
	if(ch == NULL)
		return true;
	stack<char> sc;
	int i = 0;
	while(ch[i] != '\0')
	{
		if(ch[i] == '(' || ch[i] == '[' || ch[i] == '{')
		{
			sc.push(ch[i]);
		}
		else if(ch[i] == ')' || ch[i] == ']' || ch[i] == '}')
		{
			if(sc.empty())
				return false;
			char temp = sc.top();
			sc.pop();
			if(!compareBracket(temp,ch[i]))
				return false;
		}
		++i;
	}
	if(sc.empty())
		return true;
	else
		return false;
}
//recursion for ()
bool isBracketsPare(char str[])
{
	static int open = 0;
	static int close = 0;
	if(str == NULL || *str == '\0')
	{
		if(open == close)
			return true;
		else
			return false;
	}
	if(*str == '(' && ++open <= close)
		return false;
	else if(*str == ')' && ++close > open)
		return false;
	else
		return isBracketsPare(++str);
}

//c. Given a string containing just the characters ’(’ and ’)’, find the length of the longest valid (wellformed) parentheses substring.
// 使用栈，时间复杂度O(n)，空间复杂度O(n). For ”(()”, the longest valid parentheses substring is ”()”, which has length = 2.
int longestParenth(string s)
{
	int maxlen = 0, last = -1;// the position of the last ')'
	stack<int> left; // keep track of the positions of non-matching '('s
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '(')
			left.push(i);
		else
		{
			if (left.empty())
				last = i;
			else
			{
				left.pop();// find a matching pair
				if (left.empty())
					maxlen = max(maxlen, i - last);
				else
					maxlen = max(maxlen, i - left.top());
			}
		}
	}
	return maxlen;
}
// DP, 时间复杂度O(n)，空间复杂度O(n)
int lvp(string s)
{
	vector<int> vi(s.size(), 0);
	int maxlen = 0, match = 0;
	for (int i = s.size() - 2; i >= 0; --i)
	{
		match = i + vi[i + 1] + 1;
		// case: "((...))"
		if (s[i] == '(' && match < s.size() && s[match] == ')')
		{
			vi[i] = vi[i + 1] + 2;
			// if a valid sequence exist afterwards "((...))()"
			if (match + 1 < s.size())
				vi[i] += vi[match + 1];
		}
		maxlen = max(maxlen, vi[i]);
	}
	return maxlen;
}
// 两遍扫描，时间复杂度O(n)，空间复杂度O(1)
int lvp(string s)
{
	int maxlen = 0, len = 0, start = -1;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '(')
			++len;
		else
		{
			--len;
			if (len < 0)
			{
				start = i;
				len = 0;
			}
			else if (len == 0)
				maxlen = max(maxlen, i - start);
		}
	}
	len = 0;
	start = s.size();
	for (int i = s.size() - 1; i >= 0; --i)
	{
		if (s[i] == ')')
			++len;
		else
		{
			--len;
			if (len < 0)
			{
				start = i;
				len = 0;
			}
			else if (len == 0)
				maxlen = max(maxlen, start - i);
		}
	}
	return maxlen;
}

//8.6 Implement the “paint fill” function that one might see on many image editing programs. That is, given a screen (represented by a 2-dimensional array of Colors), a point, and a new color, fill in the surrounding area until you hit a border of that color.
enum color
{
	red, yellow, blue, green, black
};
void paintFill(color **screen, int m, int n, int x, int y, color cr)
{
	if(x >= m || x < 0 || y < 0 || y >= n || screen == NULL || m < 1 || n < 1)
		return;
	if(screen[x][y] == cr)
		return;
	screen[x][y] = cr;
	paintFill(screen, m, n, x-1, y, cr);
	paintFill(screen, m, n, x, y-1, cr);
	paintFill(screen, m, n, x+1, y, cr);
	paintFill(screen, m, n, x, y+1, cr);
}
//迭代版本也不难，用BFS即可。每次给一个点着色后，就把它周围四个点放入队列， 只要队列不为空，就一直处理。这里需要注意一点的是，如果遇到一个点已经是新颜色， (比如上面说的绿色)，那么我就不用处理它而且不需要把它周围四个点入队。 如果不注意这点，那么填充色就会不顾边界直接把整张图片都填充成同一种颜色。 

//8.7 Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent), write code to calculate the number of ways of representing n cents.
//changes(0, 25, 50) or change(50, 25)
int changes(int sum, int cur, int val)
{
	if(sum < 0 || cur < 0 || val < 1)
		return 0;
	int ways = 0;
	if(sum <= val)
	{
		if(sum == val)
			return 1;
		if(cur >= 25)
			ways += changes(sum+25, 25, val);
		if(cur >= 10)
			ways += changes(sum+10, 10, val);
		if(cur >= 5)
			ways += changes(sum+5, 5, val);
		if(cur >= 1)
			ways += changes(sum+1, 1, val);
	}
	return ways;
}
int change(int n, int de)
{
	int nextde = 0;
	switch(de)
	{
	case 25:
		nextde = 10;
		break;
	case 10:
		nextde = 5;
		break;
	case 5:
		nextde = 1;
		break;
	case 1:
		return 1;
	}
	int ways = 0;
	for(int i=0; i*de<=n; ++i)
		ways += change(n-i*de, nextde);
	return ways;
}

//8.8 

//8.9 Given a target number, and a series of candidate numbers, print out all combinations, so that the sum of candidate numbers equals to the target.
//e.g.target is 7, candidate is 2, 3, 6, 7, output should be 7 and 3 + 2 + 2 (but not print 2 + 3 + 2, 2 + 2 + 3)
void printSum(int candidate[], int index[], int n)
{
	for (int i = 1; i <= n; ++i)
		cout << candidate[index[i]] << ((i == n) ? "" : " + ");
	cout << endl;
}
void solve(int target, int sum, int candidate[], int size, int index[], int n)
{
	if (sum > target)
		return;
	if (sum == target)
		printSum(candidate, index, n);
	for (int i = index[n]; i < size; ++i)
	{
		index[n + 1] = i;
		solve(target, sum + candidate[i], candidate, size, index, n + 1);
	}
}
void combin2sum(int target, int candidate[], int size)
{
	int index[100] = { 0 };
	solve(target, 0, candidate, size, index, 0);
	return;
}

//8.10 Given a digit string, return all possible letter combinations that the number could represent. A mapping of digit to letters like on the telephone buttons.
//递归，时间复杂度O(3^n)，空间复杂度O(n)
class Solution
{
public:
	vector<string> keyboard;
	Solution()
	{
		string s[10] = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };//0,1,2...
		for (int i = 0; i < 10; ++i)
			keyboard.push_back(s[i]);
	}
	vector<string> letterCombin(const string &digits)
	{
		vector<string> result;
		dfs(digits, 0, "", result);
		return result;
	}
	void dfs(const string &digits, size_t cur, string path, vector<string> &result)
	{
		if (cur == digits.size())
		{
			result.push_back(path);
			return;
		}
		for (auto c : keyboard[digits[cur] - '0'])
			dfs(digits, cur + 1, path + c, result);
	}
};
//迭代，时间复杂度O(3^n)，空间复杂度O(1)
class Solution
{
public:
	vector<string> keyboard;
	Solution()
	{
		string s[10] = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };//0,1,2...
		for (int i = 0; i < 10; ++i)
			keyboard.push_back(s[i]);
	}
	vector<string> letterCombin(const string &digits)
	{
		vector<string> result(1, "");
		for (auto d : digits)
		{
			int n = result.size();
			int m = keyboard[d - '0'].size();
			result.resize(n * m);
			for (int i = 0; i < m; ++i)
				copy(result.begin(), result.begin() + n, result.begin() + n*i);
			for (int i = 0; i < m; ++i)
			{
				auto begin = result.begin();
				for_each(begin + n*i, begin + n*(i + 1), [&](string &s){s += keyboard[d - '0'][i]; });
			}
		}
		return result;
	}
};

//Backtracking method template.
void backtracking(P point, vector<P> &path, vector<vector<p> &paths)
{
	if(!point)//invalid point
		return;
	path.push_back(point);
	bool success = ;//condition for success
	if(success)
		paths.push_back(vector<P>(path.begin(), path.end()));//don't return here
	for(P next: all directions)
		backtracking(next, path, paths);
	path.pop_back();
	return;
}