//6.1 Knapsack Problem: Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack
//recursion method, return the max value, time O(2^n)
int knapsack(int w, int wt[], int val[], int n)
{
	if(n == 0 || w == 0)
		return 0;
	if(wt[n-1] > w)
		return knapsack(w, wt, val, n-1);
	else
		return  max(val[n-1] + knapsack(w-wt[n-1], wt, val, n-1), 
		knapsack(w, wt, val, n-1));
}
//DP method， return the max value， num[] is which item be selected. time O(n*w)
int Knapsack(int w, int wt[], int val[], int n)
{
	int i = 0, j = 0;
	int **M = new int*[n+1];
	for(i=0; i<=n; ++i)
	{
		M[i] = new int[w+1];
		memset(M[i], 0, sizeof(int)*(w+1));
	}

	for(i=0; i<=n; ++i)
	{
		for(j=0; j<=w; ++j)
		{
			if(i == 0 || j == 0)
				M[i][j] = 0;
			else if(wt[i-1] <= j)
				M[i][j] = max(val[i-1]+M[i-1][j-wt[i-1]], M[i-1][j]);
			else
				M[i][j] = M[i-1][j];
			/* Space optimize to O(W)
			if(i > 0 && j >= wt[i-1])
				M[j] = max(val[i-1]+M[j-wt[i-1]], M[j]);
			*/
		}
	}
	int res = M[n][w];
	j = w;
	int *num = new int[n];
	for(i=0; i<n; ++i)
		num[i] = 0;
	for(i=n; i>0; --i)
	{
		if(M[i][j] > M[i-1][j])
		{
			num[i-1] = 1;
			j -= wt[i-1];//装入第i-1个宝石后背包能装入的重量就只剩下j - wt[i-1]
		}
	}
	for(i=0; i<n; ++i)
		cout<<num[i]<<", ";
	for(i=0; i<=n; ++i)
	{
		delete[] M[i];
		M[i] = NULL;
	}
	delete[] M;
	M = NULL;
	return res;
}

//6.2 有面值为1元、3元和5元的硬币若干枚，如何用最少的硬币凑够11元？
//DP equation d(i)=min{d[i-Vj]+1} 其中i-vj >=0，vj表示第j个硬币的面值; 
int coin2Value(int coin[], int num, int value)
{
	if(coin == NULL || num < 1 || value < 1)
		return 0;
	int *minCoin = new int[value+1];
	memset(minCoin, 0, sizeof(int)*(value+1));
	for(int i=1; i<=value; ++i)
	{
		minCoin[i] = i;
		for(int j=0; j<num; ++j)
		{
			if(i >= coin[j])
				minCoin[i] = min(minCoin[i],minCoin[i-coin[j]]+1);
		}
	}
	for(int i=0; i<=value; ++i)
		cout<<minCoin[i]<<", ";
	int coinNum = minCoin[value];
	delete[] minCoin;
	minCoin = NULL;
	return coinNum;
}

//6.3 longest increasing subsequence 一个序列有N个数：A[1],A[2],…,A[N]，求出最长非降子序列的长度
//DP time O(n*n),Space O(n), equation: d(i) = max{1, d(j)+1}, j<i, a[j]<=a[i]
int lisDP(int arr[], int n)
{
	if(arr == NULL || n < 1)
		return 0;
	int *d = new int[n];
	int len = 1;
	for(int i=0; i<n; ++i)
	{
		d[i] = 1;
		for(int j=0; j<i; ++j)
		{
			if(arr[j] <= arr[i] && d[j] +1 > d[i])
				d[i] = d[j]+1;
			if(len<d[i])
				len = d[i];
		}
	}
	for(int i=0; i<n; ++i)
		cout<<d[i]<<", ";
	delete[] d;
	return len;
}
//time O(nlogn), space O(n) algorithem
int binarySearch(int arr[], int n, int key)
{
	assert(arr != NULL && n > 0);
	int left = 0, right = n-1;
	while(left < right)
	{
		int mid = left + ((right-left)>>1);
		if(arr[mid] < key)
			left = mid+1;
		else if(arr[mid] > key)
			right = mid;
		else
			return mid;
	}
	return right;
}
int LIS(int arr[], int n)
{
	if(arr == NULL || n < 1)
		return 0;
	int *mintail = new int[n];//save end element of smaller list is smaller than end elements of larger lists
	memset(mintail,0,sizeof(int)*n);
	int len = 1;// max value of LIS
	mintail[0] = arr[0];
	for(int i=1; i<n; ++i)
	{
		//new smallest value
		if(arr[i] < mintail[0])
			mintail[0] = arr[i];
		//extend largest subsequence by A[i]
		else if(arr[i] > mintail[len-1])
			mintail[len++] = arr[i];
		//If A[i] is in between, we will find a list with largest end element that is bigger than A[i]. Clone and extend this list by A[i]. We will discard all other lists of same length as that of this modified list
		else
		{
			mintail[binarySearch(mintail,len,arr[i])] = arr[i];
		}		
	}
	for(int i=0; i<n; ++i)
		cout<<mintail[i]<<", ";
	delete[] mintail;
	return len;
}
//construct LIS
int getCeilIndex(int A[], int T[], int l, int r, int key)
{
	while(r-l > 1)
	{
		int m = l + (r-l)/2;
		if(A[T[m]] >= key)
			r = m;
		else
			l = m;
	}
	return r;
}
int constructLIS(int arr[], int size)
{
	int *tailindex = new int[size];
	int *previndex = new int[size];
	memset(tailindex, 0, sizeof(int)*size);
	memset(previndex, 0xFF, sizeof(int)*size);
	int len = 1;
	tailindex[0] = 0;
	previndex[0] = -1;
	for(int i=1; i<size; ++i)
	{
		//new smallest value
		if(arr[i]<arr[tailindex[0]])
			tailindex[0] = i;
		//extend largest subsequence by arr[i]
		else if(arr[i] > arr[tailindex[len-1]])
		{
			previndex[i] = tailindex[len-1];
			tailindex[len++] = i;
		}
		// A[i] wants to be a potential condidate of future subsequence. It will replace ceil value in tailIndices
		else
		{
			int pos = getCeilIndex(arr, tailindex, -1, len-1, arr[i]);
			previndex[i] = tailindex[pos-1];
			tailindex[pos] = i;
		}
	}
	for(int i=tailindex[len-1]; i>=0; i=previndex[i])
		cout<<"LIS:"<<arr[i]<<", ";
	cout<<endl;
	for(int i=0; i<size; ++i)
		cout<<"tailindex:"<<tailindex[i]<<", ";
	cout<<endl;
	for(int i=0; i<size; ++i)
		cout<<"previndex:"<<previndex[i]<<", ";
	cout<<endl;
	delete[] previndex;
	delete[] tailindex;
	return len;
}

//b. A circus is designing a tower routine consisting of people standing atop one another’s shoulders. For practical and aesthetic reasons, each person must be both shorter and lighter than the person below him or her. Given the heights and weights of each person in the circus, write a method to compute the largest possible number of people in such a tower.
//EXAMPLE: Input (ht, wt): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110) Output: The longest tower is length 6 and includes from top to bottom: (56, 90) (60,95) (65,100) (68,110) (70,150) (75,190)
//给定了(身高 体重)序列，要求我们排序。不过由于要排序的对象是一个结构， 我们可以先按其中的一个指标进行排序，比如说身高。身高排好序后， 身高这个指标就都是满足叠罗汉的要求了，剩下的就看体重。 我们就只要在体重那个维度找到最长的递增子序列就可以了。
struct Person
{
	int height;
	int weight;
	Person(int h, int w)
	{
		height = h;
		weight = w;
	}
};
bool cmpPerson(Person p1, Person p2)
{
	if(p1.height == p2.height)
		return p1.weight < p2.weight;
	else
		return p1.height < p2.height;
}
int personTower(Person pe[], int n)//LIS 单调连续递增子序列
{
	if(pe == NULL || n < 1)
		return -1;
	sort(pe, pe+n, cmpPerson);
	int *idp = new int[n];
	memset(idp, 0, sizeof(int)*n);	
	int len = 0;
	for(int i=0; i<n; ++i)
	{
		ipd[i] = 1;
		for(int j=0; j<i; ++j)
		{			
			if(pe[j].weight <= pe[i].weight && idp[j]+1 > idp[i])
				idp[i] = idp[j]+1;
			if(len < ipd[i])
				len = ipd[i];
		}
	}
	delete[] ipd;
	return len;
}

//6.4 Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.
//Examples: set[] = {3, 34, 4, 12, 5, 2}, sum = 9, Output:  True  //There is a subset (4, 5) with sum 9. Returns true if there is a subset of set[] with sun equal to given sum
//recursion method time O(2^n)
bool isSubsetSum(int set[], int n, int sum)
{
	// Base Cases
	if (sum == 0)
		return true;
	if (n == 0 && sum != 0)
		return false;

	// If last element is greater than sum, then ignore it
	if (set[n-1] > sum)
		return isSubsetSum(set, n-1, sum);

	/* else, check if sum can be obtained by any of the following
	(a) including the last element
	(b) excluding the last element   */
	return isSubsetSum(set, n-1, sum) || isSubsetSum(set, n-1, sum-set[n-1]);
}
//DP method, fill it in bottom up manner, time O(n*sum)
bool subSumDP(int arr[], int n, int sum)
{
	// The value of subset[sum+1][n+1] will be true if there is a subset of set[0..j-1] with sum equal to i
	bool **subset = new bool*[sum+1];
	for(int i=0; i<=sum; ++i)
		subset[i] = new bool[n+1];
	// If sum is 0, then answer is true
	for (int i = 0; i <= n; i++)
		subset[0][i] = true;

	// If sum is not 0 and set is empty, then answer is false
	for (int i = 1; i <= sum; i++)
		subset[i][0] = false;

	// Fill the subset table in botton up manner
	for (int i = 1; i <= sum; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			subset[i][j] = subset[i][j-1];
			if (i >= arr[j-1])
				subset[i][j] = subset[i][j] || subset[i - arr[j-1]][j-1];
		}
	}

	 // uncomment this code to print table
	for (int i = 0; i <= sum; i++)
	{
	for (int j = 0; j <= n; j++)
	printf ("%4d", subset[i][j]);
	printf("\n");
	} 
	bool result = subset[sum][n];
	for(int i=0; i<=sum; ++i)
	{
		delete[] subset[i];
		subset[i] = NULL;
	}
	delete[] subset;
	subset = NULL;
	return result;
}

//6.5 Palindrome problem
//a. Check if a number is Palindrome, recursion
bool oneDigit(int num)// single number is palindrome
{
	if(num >= 0 && num < 10)
		return true;
	else
		return false;
}
bool isPalUtil(int num, int *dupNum)
{
	if(oneDigit(num))
		return (num == (*dupNum) % 10);
	if(!isPalUtil(num/10, dupNum))
		return false;
	*dupNum /= 10;
	return (num%10 == (*dupNum)%10);
}
bool isPal(int num)
{
	if(num < 0)
		num = -num;
	int dupNum = num;
	return isPalUtil(num, &dupNum);
}
//iterative + reverse num
int reverseNum(int num)
{
	if(num >=0 && num < 10)
		return num;
	int count = 1, temp = num;
	while(temp/=10)
		++count;
	while(count--)
	{
		temp += (num%10) * (int)pow(10, (double)count);
		num /= 10;
	}
	return temp;
}
bool isPal2(int num)
{
	if(num < 0)
		num = -num;
	return (num == reverseNum(num));
}
//better iterative
bool palNum(int num)
{
	if (num < 0)
		num = -num;
	int div = 1;
	while (num / div >= 10)
		div *= 10;
	while (num > 0)
	{
		int l = num / div;
		int r = num % 10;
		if (l != r)
			return false;
		num %= div;
		num /= 10;
		div /= 100;
	}
	return true;
}

//b. Given a number, find the next smallest palindrome
bool areAll9s(int a[], int n)
{
	if(a == NULL || n < 0)
		return false;
	for(int i=0; i<n; ++i)
	{
		if(a[i] != 9)
			return true;
	}
	return false;
}
void printArray(int a[], int n)
{
	for(int i=0; i<n; ++i)
		cout<<a[i];
	cout<<endl;
}
void getNextPalindromeNum(int num[], int n)
{
	int mid = n/2;
	int i = mid -1;// left part end
	int j = (n % 2) ? mid + 1 : mid;//right part begin
	bool leftsmaller = false;// compare left to right
	while(i >=0 && num[i] == num[j])
	{
		--i;
		++j;
	}
	if(i < 0 || num[i] < num[j])
		leftsmaller = true;
	while(i >= 0)
	{
		num[j] = num[i];
		++j;
		--i;
	}
	if(leftsmaller == true)
	{
		int carry = 1;
		i = mid-1;
		if(n%2 == 1)
		{
			num[mid] += carry;
			if(num[mid] == 10)
			{
				num[mid] = 0;				
			}
			else
				carry = 0;
			j = mid + 1;
		}
		else
			j = mid;
		while(i >= 0)
		{
			num[i] += carry;
			carry = num[i] / 10;
			num[i] %= 10;
			num[j++] = num[i--];
		}
	}
	return;
}
void getNextPalindrome(int num[], int n)
{
	int i = 0;
	printf("\n Next Palindrome is: ");
	if(areAll9s(num, n))
	{
		cout<<"1";
		for(i=1; i<n; ++i)
			cout<<"0";
		cout<<"1"<<endl;
	}
	else
	{
		getNextPalindromeNum(num, n);
		printArray(num, n);
	}
}

//c. check if a singly linked list is palindrome
//By reversing the last half list, O(n) time and O(1) space.
struct Node
{
	char data;
	Node *next;
};
void Reverse(Node **head)
{
	Node *pre = NULL;
	Node *cur = *head;
	Node *next = NULL;
	while(cur != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	*head = pre;
}
bool compareLists(Node *head1, Node *head2)
{
	while(head1 && head2)
	{
		if(head1->data != head2->data)
			return false;
		head1 = head1->next;
		head2 = head2->next;
	}
	if(head1 || head2)
		return false;
	return true;
}
bool isPalindrome(Node *head)
{
	if(head == NULL)
		return false;
	Node *slow = head, *fast = head;
	Node *half = NULL, *pre_slow = head;
	Node *midnode = NULL;
	bool res = true;
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		pre_slow = slow;
		slow = slow->next;
	}
	if(fast != NULL)
	{
		midnode = slow;
		slow = slow->next;
	}
	half = slow;
	pre_slow->next = NULL;
	Reverse(&half);
	res = compareLists(head, half);
	Reverse(&half);
	if(midnode != NULL)
	{
		pre_slow->next = midnode;
		midnode->next = half;
	}
	else
		pre_slow->next = half;
	return res;
}
//Using Recursion,O(n) time and O(1) space.
bool isPalindrome(Node **left, Node *right)
{
	if(right == NULL)
		return true;
	if(!isPalindrome(left, right->next))
		return false;
	bool isp = (right->data == (*left)->data);
	*left = (*left)->next;
	return isp;
}

//d. Determine if string a palindrome, considering only alphanumeric characters and ignoring cases. For example, "A man, a plan, a canal : Panama" is a palindrome.
//”race a car” is not a palindrome. We define empty string as valid palindrome,时间复杂度O(n)，空间复杂度O(1)
bool isPalindrome(string src)
{
	transform(src.begin(), src.end(), src.begin(), tolower);
	auto left = src.begin(), right = prev(src.end());
	while (left < right)
	{
		if (!isalnum(*left))
			++left;
		else if (!isalnum(*right))
			--right;
		else if (*left != *right)
			return false;
	}
	return true;
}

//e. Longest Palindromic Subsequence input:“forgeeksskeegfor”, output:“geeksskeeg”.
//recursion, output:“ogeeksskeego”
int lps(char *str, int i, int j)
{
	if(i == j)// Base Case 1: If there is only 1 character
		return 1;
	else if(str[i] == str[j] && i+1 == j)// Base Case 2: If there are only 2 characters and both are same
		return 2;
	else if(str[i] == str[j]) // If the first and last characters match
		return lps(str, i+1, j-1)+2;
	else// If the first and last characters do not match
		return max(lps(str, i+1, j), lps(str, i, j-1));
}
//Dynamic Programming solution 1, Time O(n^2), Space O(n^2)
int lps(char *str)
{
	int n = strlen(str);
	int i = 0, j = 0, cl = 0;
	int start = 0, maxlen = 1;// All substrings of length 1 are palindromes
	int **L = new int*[n];
	for(i=0; i<n; ++i)
	{
		L[i] = new int[n];
		memset(L[i], 0, n*sizeof(int));
	}
	for(i=0; i<n; ++i)
		L[i][i] = 1;//L[i][j] will be false if substring str[i..j] is not palindrome. Else table[i][j] will be true
	for(cl=2; cl<=n; ++cl)
	{
		for(i=0; i<n-cl+1; ++i)
		{
			j = i + cl - 1;
			if(str[i] == str[j] && cl == 2)
			{
				L[i][j] = 2;
				if(maxlen < 2)
				{
					start = i;
					maxlen = 2;
				}
			}
			else if(str[i] == str[j] && L[i+1][j-1])
			{
				L[i][j] = L[i+1][j-1] + 2;
				if(maxlen < cl)
				{
					start = i;
					maxlen = cl;
				}
			}
		}
	}
	int len = L[0][n-1];
	for(i=0; i<n; ++i)
	{
		for(j=0; j<n; ++j)
		{
			cout<<L[i][j]<<" ";
		}
		cout<<endl;
	}
	for(i=start; i<start+maxlen; ++i)
		cout<<str[i];
	cout<<"; "<<maxlen<<endl;
	for(i=0; i<n; ++i)
	{
		delete[] L[i];
	}
	delete[] L;
	return len;
}
//Dynamic Programming solution 2, Time O(n^2), Space O(n^2)
int lps(char *str)
{
	int n = strlen(str);
	int **L = new int*[n];
	int i=0, j=0, k=0;
	for(i=0; i<n; ++i)
	{
		L[i] = new int[n];
		memset(L[i], 0, sizeof(int)*n);
	}
	int start = 0, maxlen = 1;
	for(i=0; i<n; ++i)
		L[i][i] = 1;
	for(i=0; i<n-1; ++i)
	{
		if(str[i] == str[i+1])
		{
			L[i][i+1] = 1;
			if(maxlen < 2)//check for sub-string of length 2.
			{
				start = i;
				maxlen = 2;
			}
		}
	}
	for(k=3; k<=n; ++k)// Check for lengths greater than 2. k is length of substring
	{
		for(i=0; i<n-k+1; ++i)
		{
			j = i + k - 1;// Get the ending index of substring from starting index i and length k
			if(L[i+1][j-1] && str[i] == str[j])
			{// checking for sub-string from ith index to jth index iff str[i+1] to str[j-1] is a palindrome
				L[i][j] = 1;
				if(k > maxlen)
				{
					start = i;
					maxlen = k;
				}
			}
		}
	}
	for(i=start; i<start+maxlen; ++i)
		cout<<str[i];
	cout<<";"<< maxlen<<endl;
	for(i=0; i<n; ++i)
	{
		delete[] L[i];
		L[i] = NULL;
	}
	delete[] L;
	L = NULL;
	return maxlen;
}
//Time O(n^2), Space O(1)
int LPS(char *str)
{
	int maxlen = 1, start = 0, i = 0;
	int low = 0, high = 0;
	int n = strlen(str);
	// One by one consider every character as center point of even and length palindromes
	for(i=1; i<n; ++i)
	{
		low = i-1;// Find the longest even length palindrome with center points as i-1 and i.  
		high = i;
		while(low >= 0 && high < n && str[low] == str[high])
		{
			if(high - low + 1 > maxlen)
			{
				start = low;
				maxlen = high - low + 1;
			}
			--low;
			++high;
		}
		low = i-1;// Find the longest odd length palindrome with center point as i
		high = i+1;
		while(low >= 0 && high < n && str[low] == str[high])
		{
			if(high - low +1 > maxlen)
			{
				start = low;
				maxlen = high -low +1;
			}
			--low;
			++high;
		}
	}
	for(i=start; i<start+maxlen; ++i)
	{
		cout<<str[i];
	}
	cout<<"; "<<maxlen<<endl;
	return maxlen;
}

// Manacher's Algorithm, time O(n), space O(n)
// Transform S into T. For example, S = "abba", T = "^#a#b#b#a#$". ^ and $ signs are sentinels appended to each end to avoid bounds checking
string expendStr(string s)
{
	int n = s.length();
	if (n == 0)
		return "^$";
	string res = "^";
	for (int i = 0; i < n; ++i)
		res += "#" + s.substr(i, 1);
	res += "#$";
	return res;
}
string lps(string s)
{
	string t = expendStr(s);
	int n = t.length();
	int *p = new int[n];
	int cen = 0, rt = 0;
	for (int i = 1; i < n - 1; ++i)
	{
		int i_mirror = 2 * cen - i;
		p[i] = (rt > i) ? min(rt - i, p[i_mirror]) : 0;
		// expand palindrome centered at i
		while (t[i + 1 + p[i]] == t[i - 1 - p[i]])
			++p[i];
		// If palindrome centered at i expand past R, adjust center based on expanded palindrome.
		if (i + p[i] > rt)
		{
			cen = i;
			rt = i + p[i];
		}
	}
	// Find the maximum element in P
	int maxlen = 0, centerIndex = 0;
	for (int i = 1; i < n - 1; ++i)
	{
		if (p[i] > maxlen)
		{
			maxlen = p[i];
			centerIndex = i;
		}
	}
	delete[] p;
	return s.substr((centerIndex - 1 - maxlen) / 2, maxlen);
}

//f. Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
//For example, given s = ”aab”, Return ["aa", "b"], ["a", "a", "b"]， 在每一步都可以判断中间结果是否为合法结果，用回溯法。
// 一个长度为n的字符串，有n-1个地方可以砍断，每个地方可断可不断，因此复杂度为O(2^(n-1)), 时间复杂度O(2^n)，空间复杂度O(n)
class Solution
{
public:
	vector<vector<string>> partition(string str)
	{
		vector<vector<string>> result;
		vector<string> path; // one partition plan
		dfs(str, path, result, 0, 1);
		return result;
	}
	// s[0, prev-1] 之间已经处理，保证是回文串, prev 表示s[prev-1] 与s[prev] 之间的空隙位置，start 同理
	void dfs(string &s, vector<string> &path, vector<vector<string>> &result, size_t pre, size_t start)
	{
		if (start == s.size())
		{
			// 最后一个隔板
			if (isPalindrom(s, pre, start - 1))
			{
				path.push_back(s.substr(pre, start - pre));
				result.push_back(path);
				path.pop_back();
			}
			return;
		}
		dfs(s, path, result, pre, start + 1);//no cut
		// 如果[prev, start-1] 是回文，则可以断开，也可以不断开（上一行已经做了）
		if (isPalindrom(s, pre, start - 1))
		{
			//cut
			path.push_back(s.substr(pre, start - pre));
			dfs(s, path, result, start, start + 1);
			path.pop_back();
		}
	}
	bool isPalindrom(const string &s, int start, int end)
	{
		if (start == end)
			return true;
		while (s[start] == s[end] && start < end)
		{
			++start;
			--end;
		}
		return start >= end;
	}
};
//improved 时间复杂度O(2^n)，空间复杂度O(n)
class Solution
{
public:
	vector<vector<string>> partition(string s)
	{
		vector<vector<string>> result;
		vector<string> path;
		dfs(s, path, result, 0);
		return result;
	}
	// 搜索必须以s[start] 开头的partition 方案
	void dfs(string &s, vector<string> &path, vector<vector<string>> &result, int start)
	{
		if (start == s.size())
		{
			result.push_back(path);
			return;
		}
		for (int i = start; i < s.size(); ++i)
		{
			if (isPalindrom(s, start, i))
			{
				//cut from position i
				path.push_back(s.substr(start, i - start + 1));
				dfs(s, path, result, i + 1);// go on cut
				path.pop_back();
			}
		}
	}
	bool isPalindrom(const string &s, int start, int end)
	{
		if (start == end)
			return true;
		while (s[start] == s[end] && start < end)
		{
			++start;
			--end;
		}
		return start >= end;
	}
};
// 动规，时间复杂度O(n^2)，空间复杂度O(1)
vector<vector<string>> partition(string s)
{
	const int n = s.size();
	bool **p = new bool*[n];// whether s[i,j] is palindrome
	for (int i = 0; i < n; ++i)
	{
		p[i] = new bool[n];
		fill_n(p[i], n, false);
	}
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = i; j < n; ++j)
			p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);
	}
	vector<vector<vector<string>>> result(n);// sub palindromes of s[0,i]
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = i; j < n; ++j)
		{
			if (p[i][j])
			{
				string palin = s.substr(i, j - i + 1);
				if (j + 1 < n)
				{
					for (auto e : result[j + 1])
					{
						e.insert(e.begin(), palin);
						result[i].push_back(e);
					}
				}
				else
					result[i].push_back(vector<string> {palin});
			}
		}
	}
	for (int i = 0; i < n; ++i)
		delete[] p[i];
	delete[] p;
	return result[0];
}

//g. Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.
// 时间复杂度O(n^2)，空间复杂度O(n^2)
int minCut(string s)
{
	const int n = s.size();
	vector<int> f(n + 1, 0);
	vector<vector<bool>> p(n, vector<bool>(n, false));
	//the worst case is cutting by each char
	for (int i = 0; i <= n; ++i)
		f[i] = n - 1 - i;//f[n] = -1;
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = i; j < n; ++j)
		{
			if (s[i] == s[j] && (j - i < 2 || p[i + 1][j - 1]))
			{
				p[i][j] = true;
				f[i] = min(f[i], f[j + 1] + 1);
			}
		}
	}
	return f[0];
}

//6.6 There are n coins in a line. (Assume n is even). Two players take turns to take a coin from one of the ends of the line until there are no more coins left. The player with the larger amount of money wins.
//Would you rather go first or second? Does it matter? Assume that you go first, describe an algorithm to compute the maximum amount of money you can win.
// DP: O(n^2) time and O(n^2) space
const int MAX = 20;
void printMoves(int p[][MAX], int A[], int N)
{
	int sum1 = 0, sum2 = 0;
	int m = 0, n = N-1;
	bool myTurn = true;
	while(m <= n)
	{
		int p1 = p[m+1][n];// If take A[m], opponent can get
		int p2 = p[m][n-1];// If take A[n]
		cout<<(myTurn? "I" : "U") << " take coin No. ";
		if(p1 <= p2)
		{
			cout<<m+1<<"("<< A[m] <<")";
			++m;
		}
		else
		{
			cout<<n+1<<"("<<A[n]<<")";
			--n;
		}
		cout<<(myTurn? "," : ".\n");
		myTurn = !myTurn;
	}
	cout << "\nThe total amount of money (maximum) I get is " << p[0][N-1] << ".\n";
}
int maxMoney(int A[], int n)
{
	int p[MAX][MAX] = {0};//P(i, j) denotes the maximum amount of money you can win when the remaining coins are { Ai, …, Aj }
	int a, b, c, i, j, k;
	for(i=0; i<n; ++i)//it is your turn now. You have two choices, either take Ai or Aj.
	{
		for(j=0, k=i; k<n; ++j, ++k)
		{
			a = ((j+2 <= n-1) ? p[j+2][k] : 0);
			b = ((j+1 <= n-1 && k-1 >= 0) ? p[j+1][k-1] : 0);
			c = ((k-2 >= 0) ? p[j][k-2] : 0);
			p[j][k] = max(A[j] + min(a, b), A[k] + min(b, c));//P(i, j) = max { Ai + min { P(i+2, j),   P(i+1, j-1) }, Aj + min { P(i+1, j-1), P(i,   j-2) } }
		}
	}
	printMoves(p, A, n);
	return p[0][n-1];
}

//6.7 You have to paint N boards of length {A0, A1, A2 … AN-1}. There are K painters available and you are also given how much time a painter takes to paint 1 unit of board. 
//You have to get this job done as soon as possible under the constraints that any painter will only paint continuous sections of board, say board {2, 3, 4} or only board {1} or nothing but not board {2, 4, 5}.
//recusion method
int sum(int a[], int b, int e)
{
	int sum = 0;
	for(int i=b, i<=e; ++i)
		sum += a[i];
	return sum;
}
int partition(int a[], int n, int k)
{
	if(k == 1)
		return sum(a, 0, n-1);
	if(n == 1)
		return a[0];
	int best = INT_MAX;
	for(int j=1; j<=n; ++j)
		best = min(best, max(partition(a, j, k-1), sum(a, j, n-1)));
	return best;
}
//DP solution with O(kN^2) run time and using O(kN) space complexity.
const int MAX = 10+1;
int findMax(int a[], int n, int k)
{
	int M[MAX][MAX] = {0};
	int cum[MAX] = {0};
	for(int i=1; i<=n; ++i)
		cum[i] = cum[i-1] + a[i-1];
	for(int i=1; i<=n; ++i)
		M[i][1] = cum[i];
	for(int i=1; i<=k; ++i)
		M[1][i] = a[0];
	for(int i=2; i<=k; ++i)
	{
		for(int j=2; j<=n; ++j)
		{
			int best = INT_MAX;
			for(int p=1; p<=j; ++p)
				best = min(best, max(M[p][i-1], cum[j]-cum[p]));
			M[j][i] = best;
		}
	}
	return M[n][k];
}
//Binary search, time O(N log c)/ O(N log ( ∑ Ai )) ，where c is the sum of all elements in A.
int getMax(int a[], int n)
{
	int max = a[0];
	for(int i=0; i<n; ++i)//n==1
	{
		if(a[i] > max)
			max = a[i];
	}
	return max;
}
int getSum(int a[], int n)
{
	int sum = 0;
	for(int i=0; i<n; ++i)
		sum += a[i];
	return sum;
}
int getNum(int a[], int n, int maxLength)
{
	int sum = 0, num = 1;//num of painters
	for(int i=0; i<n; ++i)
	{
		sum += a[i];
		if(sum > maxLength)
		{
			sum = a[i];
			++num;
		}
	}
	return num;
}
int partition(int a[], int n, int k)
{
	int lo = getMax(a, n);
	int hi = getSum(a, n);
	while(lo < hi)
	{
		int mid = lo + (hi-lo)/2;
		int num = getNum(a, n, mid);
		if(num <= k)
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}

//6.8 Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below. Only use O(r) extra space, r = row.
//设状态为f(i,j)，表示从从位置(i,j) 出发，路径的最小和，则状态转移方程为f(i,j) = min{f(i+1,j), f(i+1,j+1)} + (i,j),时间复杂度O(n^2)，空间复杂度O(1)
int minPath(vector<vector<int>> &triangle)
{
	for (int i = triangle.size() - 2; i >= 0; --i)
	{
		for (int j = 0; j < i + 1; ++j)
			triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
	}
	return triangle[0][0];
}

//6.9 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2. Given: s1 = ”aabcc”, s2 = ”dbbca”, When s3 = ”aadbbcbcac”, return true. When s3 = ”aadbbbaccc”, return false.
// 递归，会超时，仅用来帮助理解
class Solution
{
public:
	bool interleave(string s1, string s2, string s3)
	{
		if (s3.size() != s1.size() + s2.size())
			return false;
		return isInterleave(begin(s1), end(s1), begin(s2), end(s2), begin(s3), end(s3));
	}
	template<typename T> bool isInterleave(T first1, T last1, T first2, T last2, T first3, T last3)
	{
		if (first3 == last3)
			return first1 == last1 && first2 == last2;
		return (*first1 == *first3 && isInterleave(next(first1), last1, first2, last2, next(first3), last3))
			|| (*first2 == *first3 && isInterleave(first1, last1, next(first2), last2, next(first3), last3));
	}
};
// 二维动规，时间复杂度O(n^2)，空间复杂度O(n^2)
bool interleave(string s1, string s2, string s3)
{
	if (s3.length() != s1.length() + s2.length())
		return false;
	vector<vector<bool>> f(s1.length() + 1, vector<bool>(s2.length() + 1, true));
	for (int i = 1; i <= s1.length(); ++i)
		f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
	for (int i = 1; i <= s2.length(); ++i)
		f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
	for (int i = 1; i <= s1.length(); ++i)
	{
		for (int j = 1; j <= s2.length(); ++j)
			f[i][j] = (s1[i - 1] == s3[i + j - 1] && f[i - 1][j])
			|| (s2[j - 1] == s3[i + j - 1] && f[i][j - 1]);
	}
	return f[s1.length()][s2.length()];
}
// 二维动规+ 滚动数组，时间复杂度O(n^2)，空间复杂度O(n)
bool interleave(string s1, string s2, string s3)
{
	if (s3.length() != s1.length() + s2.length())
		return false;
	if (s1.length() < s2.length())
		swap(s1, s2);
	vector<bool> f(s2.length() + 1, true);
	for (int i = 1; i <= s2.length(); ++i)
		f[i] = s2[i - 1] == s3[i - 1] && f[i - 1];
	for (int i = 1; i <= s1.length(); ++i)
	{
		f[0] = s1[i - 1] == s3[i - 1] && f[0];
		for (int j = 1; j <= s2.length(); ++j)
			f[j] = (s1[i - 1] == s3[i + j - 1] && f[j]) || (s2[j - 1] == s3[i + j - 1] && f[j - 1]);
	}
	return f[s2.length()];
}

//6.10 Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
//To scramble the string, we may choose any non-leaf node and swap its two children，Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
//递归 + 剪枝，时间复杂度O(n^6)，空间复杂度O(1)
class Solution
{
public:
	bool isScramble(string s1, string s2)
	{
		return scramble(s1.begin(), s1.end(), s2.begin());
	}
private:
	typedef string::iterator IT;
	bool scramble(IT f1, IT l1, IT f2)
	{
		auto length = distance(f1, l1);
		auto l2 = next(f2, length);
		if (length == 1)
			return *f1 == *f2;
		// 剪枝，提前返回
		int a[26] = { 0 };//字符计数器
		for (int i = 0; i < length; ++i)
		{
			++a[*(f1 + i) - 'a'];
			--a[*(f2 + i) - 'a'];
		}
		for (int i = 0; i < 26; ++i)
		{
			if (a[i] != 0)
				return false;
		}
		
		for (int i = 1; i < length; ++i)
		{
			if ((scramble(f1, f1 + i, f2) && scramble(f1 + i, l1, f2 + i))
				|| (scramble(f1, f1 + i, l2 - i) && scramble(f1 + i, l1, f2)))
				return true;
		}
		return false;
	}
};
// 动规，时间复杂度O(n^3)，空间复杂度O(n^3),有错
bool scramble(string s1, string s2)
{
	const int n = s1.size();
	if (n != s2.size())
		return false;
	// f[n][i][j]，表示长度为n，起点为s1[i]和起点为s2[j]两个字符串是否互为scramble
	bool ***f = new bool **[n + 1];
	for (int i = 0; i <= n; ++i)
	{
		f[i] = new bool*[n];
		for (int j = 0; j < n; ++j)
			f[i][j] = new bool[n];
	}
	fill_n(&f[0][0][0], (n + 1)*n*n, false);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			f[1][i][j] = s1[i] == s2[j];
	}
	for (int m = 1; m <= n; ++m)
	{
		for (int i = 0; i + m < n; ++i)
		{
			for (int j = 0; j + m < n; ++j)
			{
				for (int k = 1; k < n; ++k)
				{
					if (((f[k][i][j] && f[m - k][i + k][j + k]) || (f[k][i][j + m - k] && f[m - k][i + k][j])))
					{
						f[m][i][j] = true;
						break;
					}
				}
			}
		}
	}
	bool res = f[n][0][0];
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			delete[] f[i][j];
		}
		delete[] f[i];
	}
	delete[] f;
	return res;
}
//better 递归+map做cache, 时间复杂度O(n^3)，空间复杂度O(n^3)
class Solution
{
public:
	bool isScramble(string s1, string s2)
	{
		cache.clear();
		return scramble(s1.begin(), s1.end(), s2.begin());
	}
private:
	typedef string::const_iterator IT;
	map<tuple<IT, IT, IT>, bool> cache;
	bool scramble(IT f1, IT l1, IT f2)
	{
		auto len = distance(f1, l1);
		if (len == 1)
			return *f1 == *f2;
		auto l2 = next(f2, len);
		for (int i = 1; i < len; ++i)
		{
			if ((getOrUpdate(f1, f1 + i, f2) && getOrUpdate(f1 + i, l1, f2 + i))
				|| (getOrUpdate(f1, f1 + i, l2 - i) && getOrUpdate(f1 + i, l1, f2)))
				return true;
		}
		return false;
	}
	bool getOrUpdate(IT f1, IT l1, IT f2)
	{
		auto key = make_tuple(f1, l1, f2);
		auto pos = cache.find(key);
		return (pos != cache.end()) ? pos->second : (scramble(f1, l1, f2));
	}
};

//6.11 Gven a m*n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
//Note: You can only move either down or right at any point in time, f[i][j]=min(f[i-1][j], f[i][j-1])+grid[i][j]
// 备忘录法
class Solution
{
public:
	int minPathSum(vector<vector<int>> &grid)
	{
		int m = grid.size();
		int n = grid[0].size();
		f = vector<vector<int>>(m, vector<int>(n, -1));
		return dfs(grid, m - 1, n - 1);
	}
private:
	vector<vector<int>> f;
	int dfs(vector<vector<int>> &grid, int x, int y)if
	{
		if (x < 0 || y < 0)
			return INT_MAX;
		if (x == 0 && y == 0)
			return grid[0][0];
		return min(update(grid, x - 1, y), update(grid, x, y - 1)) + grid[x][y];
	}
	int update(const vector<vector<int>> &grid, int x, int y)
	{
		if (x < 0 || y < 0)
			return INT_MAX;
		if (f[x][y] >= 0)
			return f[x][y];
		else return f[x][y] = dfs(grid, x, y);
	}
};
// 二维动规
int minPathSum(vector<vector<int>> &grid)
{
	if (grid.size() == 0)
		return 0;
	const int m = grid.size();
	const int n = grid[0].size();
	vector<vector<int>> f(m, vector<int>(n, 0));
	f[0][0] = grid[0][0];
	for (int i = 1; i < m; ++i)
		f[i][0] = f[i - 1][0] + grid[i][0];
	for (int i = 1; i < n; ++i)
		f[0][i] = f[0][i - 1] + grid[0][i];
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
			f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j];
	}
	return f[m - 1][n - 1];
}
//better 二维动规+ 滚动数组
int minPathSum(vector<vector<int>> &grid)
{
	if (grid.size() == 0)
		return 0;
	const int m = grid.size();
	const int n = grid[0].size();
	vector<int> f(n, INT_MAX);// use min() to compare
	f[0] = 0;
	for (int i = 0; i < m; ++i)
	{
		f[0] += grid[i][0];
		for (int j = 1; j < n; ++j)
			f[j] = min(f[j - 1], f[j]) + grid[i][j];
	}
	return f[n - 1];
}

//6.12 Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
//You have the following 3 operations permitted on a word : Insert a character; Delete a character; Replace a character
//设状态为f[i][j]，表示A[0, i] 和B[0, j] 之间的最小编辑距离。设A[0, i] 的形式是str1c，B[0, j] 的形式是str2d，1. 如果c == d，则f[i][j] = f[i - 1][j - 1]；2. 如果c != d，
//(a) 如果将c 替换成d，则f[i][j] = f[i - 1][j - 1] + 1；(b) 如果在c 后面添加一个d，则f[i][j] = f[i][j - 1] + 1；(c) 如果将c 删除，则f[i][j] = f[i - 1][j] + 1；
// 二维动规，时间复杂度O(n*m)，空间复杂度O(n*m)
int minStep(const string &s1, const string &s2)
{
	const int n = s1.size();
	const int m = s2.size();
	vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
	for (int i = 0; i <= n; ++i)
		f[i][0] = i;
	for (int j = 0; j <= m; ++j)
		f[0][j] = j;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
				f[i][j] = f[i - 1][j - 1];
			else
				f[i][j] = 1 + min(f[i - 1][j - 1], min(f[i - 1][j], f[i][j - 1]));
		}
	}
	return f[n][m];
}
// 二维动规+ 滚动数组，时间复杂度O(n*m)，空间复杂度O(n)
int minStep(const string &s1, const string &s2)
{
	if (s1.length() < s2.length())
		swap(s1, s2);
	vector<int> f(s2.length() + 1, 0);
	int pre = 0;// record f[i-1][j-1]
	for (int i = 0; i <= s2.length(); ++i)
		f[i] = i;
	for (int i = 1; i <= s1.length(); ++i)
	{
		pre = f[0];
		f[0] = i;
		for (int j = 1; j <= s2.length(); ++j)
		{
			int cur = f[j];
			if (s1[i - 1] == s2[j - 1])
				f[j] = pre;
			else
				f[j] = 1 + min(pre, min(f[j], f[j - 1]));
			pre = cur;
		}
	}
	return f[s2.length()];
}

//6.13 A message containing letters from A-Z is being encoded to numbers using the following mapping: 'A' -> 1,'B' -> 2,...,'Z' -> 26
//Given an encoded message containing digits, determine the total number of ways to decode it. For example, Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12). The number of ways decoding "12" is 2.
// 动规，时间复杂度O(n)，空间复杂度O(1)
int decoding(const string &s)
{
	if (s.empty() || s[0] == '0')
		return 0;
	int pre = 0, cur = 1, tmp = 0;
	for (int i = 1; i <= s.size(); ++i)//长度为n的字符串，有n+1个阶梯
	{
		if (s[i - 1] == '0')
			cur = 0;
		if (i < 2 || !(s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')))
			pre = 0;
		tmp = cur;
		cur += pre;
		pre = tmp;
	}
	return cur;
}

//6.14 Given a string S and a string T, count the number of distinct subsequences of T in S. A subsequence of a string is a new string which is formed from the original string by deleting some(can be none)
//of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not). Example: S = "rabbbit", T = "rabbit", Return 3.
//设状态为f(i,j)，表示T[0,j]在S[0,i]里出现的次数。首先,无论S[i]和T[j]是否相等，若不使用S[i]，则f(i,j) = f(i-1,j); 若S[i] == T[j]，则可以使用S[i]，此时f(i,j) = f(i-1,j) + f(i-1,j-1)
// 二维动规+ 滚动数组, 时间复杂度O(m*n)，空间复杂度O(n)
int distinct(const string &s, const string &t)
{
	vector<int> f(t.size() + 1);
	f[0] = 1;
	for (int i = 0; i < s.size(); ++i)
	{
		for (int j = t.size() - 1; j >= 0; --j)
			f[j + 1] += s[i] == t[j] ? f[j] : 0;
	}
	return f[t.size()];
}
// 二维动规, 时间复杂度O(m*n)，空间复杂度O(m*n)
int distinct(const string &s, const string &t)
{
	const int m = s.size();
	const int n = t.size();
	if (s == t)
		return 1;
	else if (m < n)
		return 0;
	vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
	for (int i = 0; i <= m; ++i)
		f[i][0] = 1;
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (s[i - 1] == t[j - 1])
				f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
			else
				f[i][j] = f[i - 1][j];
		}
	}
	return f[m][n];
}

//6.15 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
//For example, given s = "leetcode", dict = ["leet", "code"]. Return true. 设状态为f(i)，表示s[0,i]是否可以分词，则状态转移方程为f(i) = anyof(f(j) && s[j + 1, i] in dict), 0 < j < i
// 动规，时间复杂度O(n^2)，空间复杂度O(n)
bool wordBreak(string s, unordered_set<string> &dict)
{
	vector<bool> f(s.size() + 1, false);//长度为n的字符串有n+1个隔板
	f[0] = true;// empty string
	for (int i = 1; i <= s.size(); ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (f[j] && dict.find(s.substr(j, i - j)) != dict.end())
			{
				f[i] = true;
				break;
			}
		}
	}
	return f[s.size()];
}
// 深搜，超时,时间复杂度O(2^n)，空间复杂度O(n)
class Solution
{
public:
	bool wordBreak(string s, unordered_set<string> &dict)
	{
		return dfs(s, dict, 0, 0);
	}
private:
	static bool dfs(const string &s, unordered_set<string> &dict, int start, int cur)
	{
		if (cur == s.size())
			return dict.find(s.substr(start, cur - start + 1)) != dict.end();
		if (dfs(s, dict, start, cur + 1))
			return true;
		if (dict.find(s.substr(start, cur - start + 1)) != dict.end())
		{
			if (dfs(s, dict, cur + 1, cur + 1))
				return true;
		}
		return false;
	}
};

//b. Return all such possible sentences. 动规，时间复杂度O(n^2)，空间复杂度O(n^2)
class Solution
{
public:
	vector<string> wordBreak(string s, unordered_set<string> &dict)
	{
		vector<bool> f(s.length() + 1, false);//长度为n 的字符串有n+1 个隔板
		//prev[i][j] 为true，表示s[j, i) 是一个合法单词，可以从j 处切开
		vector<vector<bool>> pre(s.length() + 1, vector<bool>(s.length(), false));
		f[0] = true;
		for (int i = 1; i <= s.length(); ++i)
		{
			for (int j = i - 1; j >= 0; --j)
			{
				if (f[j] && dict.find(s.substr(j, i - j)) != dict.end())
				{
					f[i] = true;
					pre[i][j] = true;
				}
			}
		}
		vector<string> result, path;
		getPath(s, pre, s.length(), path, result);
		return result;
	}
private:
	// DFS 遍历树，生成路径
	void getPath(const string &s, const vector<vector<bool>> &pre, int cur, vector<string> &path, vector<string> &result)
	{
		if (cur == 0)
		{
			string tmp;
			for (auto i = path.crbegin(); i != path.crend(); ++i)
				tmp += *i + " ";
			tmp.erase(tmp.end() - 1);
			result.push_back(tmp);
		}
		for (int i = 0; i < s.size(); ++i)
		{
			if (pre[cur][i])
			{
				path.push_back(s.substr(i, cur - i));
				getPath(s, pre, i, path, result);
				path.pop_back();
			}
		}
	}
};