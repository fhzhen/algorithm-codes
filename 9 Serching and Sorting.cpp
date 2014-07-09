//9.1 a. Binary search algorithm, return key index in array[]
//iteration time O(logN)
int binarySearch(int arr[], int n, int key)
{
	if(arr == NULL || n < 1)
		return -1;
	int left = 0, right = n-1;
	while(left <= right)
	{
		int mid = left + ((right-left)>>1);
		if(arr[mid] < key)
			left = mid + 1;
		else if(arr[mid] > key)
			right = mid -1;
		else
			return mid;
	}
	return -1;
}
//recursion, right = n-1
int binarySearchRecur(int arr[], int left, int right, int key)
{
	if(arr == NULL || left > right)
		return -1;
	int mid = left + ((right-left)>>1);
	if(arr[mid] > key)
		return binarySearchRecur(arr, left, mid-1, key);
	else if(arr[mid] < key)
		return binarySearchRecur(arr, mid+1, right, key);
	else
		return mid;
}

//b. Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array. You may assume that the array was originally sorted in increasing order.
//EXAMPLE: Input: find 5 in array {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};  Output: 8 (the index of 5 in the array)
int binarySearch(int a[], int n, int val)
{
	int left = 0, right = n-1;
	while(left <= right)
	{
		int mid = left + (right-left)/2;
		if(a[mid] == val)
			return mid;
		else if(a[mid] >= a[left])
		{
			if(val < a[mid] && val >= a[left])
				right = mid - 1;
			else
				left = mid + 1;
		}
		else
		{
			if(val > a[mid] && val < a[left])
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	return -1;
}
//What if duplicates are allowed? Would this affect the run time complexity ? How and why ?
int bs(int a[], int n, int val)
{
	int l = 0, r = n - 1;
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		if (a[m] == val)
			return m;
		else if (a[m] > a[l])
		{
			if (a[l] <= val && val < a[m])
				r = m - 1;
			else
				l = m + 1;
		}
		else if (a[m] < a[l])
		{
			if (a[m] < val && val <= a[r])
				l = m + 1;
			else
				r = m - 1;
		}
		else//a[m] == a[l], exist duplicate
		{
			++l;
		}
	}
	return -1;
}

//c. Given a sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string.
//Example: find “ball” in [“at”, “”, “”, “”, “ball”, “”, “”, “car”, “”,“”, “dad”, “”, “”] will return 4
int Bsearch(string str[], int n, string des)
{
	if(str == "")
		return -1;
	int left = 0, right = n-1;
	while(left <= right)
	{
		int mid = left + (right-left)/2;
		int temp = mid;
		while(str[temp] == "" && temp <= right)
			++temp;
		if(temp > right)
			right = mid - 1;
		else
		{
			if(str[temp] == des)
				return temp;
			else if(str[temp] < des)
				left = temp + 1;
			else
				right = mid -1;
		}
	}
	return -1;
}

//d. Implement a function which takes as input a float varaible x and return its square root.
int compare(double a, double b)// 0 means equal, -1 means smaller, and 1 means larger.
{
	double dif = a - b;
	if(dif < -0.000001)
		return -1;
	else if(dif > 0.000001)
		return 1;
	else 
		return 0;
}
double squareRoot(double x)
{
	assert(x > 0);
	double l, r;
	if(compare(x, 1.0) < 0)// Decide the search range according to x.
	{
		l = x;
		r = 1.0;
	}
	else
	{
		l = 1.0;
		r = x;
	}
	while(compare(l, r) == -1)// Keep searching if l < r
	{
		double m = l + 0.5*(r-l);
		double square_m = m * m;
		if(compare(square_m, x) == 0)
			return m;
		else if(compare(square_m, x) == 1)
			r = m;
		else
			l = m;
	}
	return l;
}

/*e. N nodes, each node consists of a couple fields and methods. These are:
int id; //every node has an ID. All of these IDs are sequential, and begin with 0. 
int val; //every node has a value  
int max; //max = N. Every node knows how many nodes are in the system.  
void send(int idTo, int payload);  
int recv(int idFrom); 
Write a single piece of code which runs on every node simultaneously, such that when it is finished running every node in the system knows the sum of the values of all the nodes in the system.*/
int getsum() //as member function of the node
{
	int parent = (id-1)/2;// index from 0
	int left = 2 * id + 1;
	int right = 2 * id + 2;
	int subsum = val;
	if(right < max)
		subsum += recv(right);
	if(left < max)
		subsum += recv(left);
	int sum = 0;
	if(parent >= 0)
	{
		send(parent, subsum);
		sum = recv(parent);
	}	
	else 
		sum = subsum;
	send(left, sum);
	send(right, sum);
	return sum;
}

//f.Given a sorted array of integers, find the starting and ending position of a given target value. Your algorithm’s runtime complexity must be in the order of O(log n).
//f the target is not found in the array, return[-1, -1]. For example, Given[5, 7, 7, 8, 8, 10] and target value 8, return[3, 4].
//偷懒的做法，使用STL, 时间复杂度O(logn)，空间复杂度O(1)
vector<int> searchRange(int a[], int n, int target)
{
	int b = distance(a, lower_bound(a, a + n, target));
	int e = distance(a, prev(upper_bound(a, a + n, target)));
	if (a[b] != target)
		return vector<int> {-1, -1};
	else
		return vector<int> {b, e};
}
// 重新实现lower_bound 和upper_bound, 时间复杂度O(logn)，空间复杂度O(1)
vector<int> searchRange(int a[], int n, int target)
{
	auto lower = lower_bound(a, a + n, target);
	auto upper = upper_bound(lower, a + n, target);
	if (lower == a + n || *lower != target)
		return vector<int> {-1, -1};
	else
		return vector<int> {distance(a, lower), distance(a, prev(upper))};
}
template<typename ForwardIterator, typename T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T value)
{
	while (first != last)
	{
		auto mid = next(first, distance(first, last) / 2);
		if (value > *mid)
			first = ++mid;
		else
			last = mid;
	}
	return first;
}
template<typename ForwardIterator, typename T>
ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T value)
{
	while (first != last)
	{
		auto mid = next(first, distance(first, last) / 2);
		if (value >= *mid)
			first = ++mid;// 与lower_bound 仅此不同
		else
			last = mid;
	}
	return first;
}

//g. Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
//You may assume no duplicates in the array. 即std::lower_bound(), 时间复杂度O(logn)，空间复杂度O(1), example: [1,3,5,6], 2 → 1
template<typename ForwardIterator, typename T>
ForwardIterator lower_bounds(ForwardIterator first, ForwardIterator last, T value)
{
	while (first != last)
	{
		auto mid = next(first + distance(first, last) / 2);
		if (*mid < value)
			first = mid + 1;
		else
			last = mid;
	}
	return first;
}
int searchInsert(int a[], int n, int target)
{
	return lower_bounds(a, a + n, target) - a;
}

//9.2 //Given a matrix in which each row and each column is sorted, write a method to find an element in it.
//让我们来看看右上角， 设要查找的元素为x，比如x比右上角元素5大，那么它也会比第一行的其它元素都大。 因此可以去掉第一行；如果它比右上角元素小，那么它也会比最后一列的元素都小， 因此可以去掉最后一列；然后这样不断地比下去，只需要O(m+n)的时间就查找完。 对于左下角的元素，也有一样的特点。
int matrixSearch(int **arr, int m, int n, int val)
{
	int row = 0, cln = n-1;
	while(row < m && cln >= 0)
	{
		if(arr[row][cln] == val)
			return row*n + cln;
		else if(arr[row][cln] < val)
			++row;
		else
			--cln;
	}
	return -1;
}

//b. Searches a value in an mn matrix. Integers in each row are sorted from left to right. The first integer of each row is greater than the last integer of the previous row.
//binary search, 时间复杂度O(logn)，空间复杂度O(1)
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
	if (matrix.empty())
		return false;
	int m = matrix.size();
	int n = matrix[0].size();
	int first = 0, last = m*n;
	while (first < last)
	{
		int mid = first + (last - first) / 2;
		int val = matrix[mid / n][mid % n];
		if (val == target)
			return true;
		else if (val < target)
			first = mid + 1;
		else
			last = mid - 1;
	}
	return false;
}

//9.3 Given a string containing only digits, restore it by returning all possible valid IP address combinations. For example: Given ”25525511135”, return[”255.255.11.135”, ”255.255.111.35”].
//必须要走到底部才能判断解是否合法，深搜,时间复杂度O(n^4)，空间复杂度O(n)
class Solution
{
public:
	vector<string> ipAddress(string s)
	{
		vector<string> result;
		string ip;// save middle result
		dfs(s, 0, 0, ip, result);
		return result;
	}
	/*@param[in] startIndex 从s 的哪里开始
	* @param[in] step 当前步骤编号，从0 开始编号，取值为0,1,2,3,4 表示结束了
	* @param[out] intermediate 当前解析出来的中间结果*/
	void dfs(string s, int start, int step, string ip, vector<string> &result)
	{
		if (start == s.size() && step == 4)//find a result
		{
			ip.resize(ip.size() - 1);
			result.push_back(ip);
			return;
		}
		if (s.size() - start > (4 - step) * 3)
			return;
		if (s.size() - start < 4 - step)
			return;
		int num = 0;
		for (int i = start; i < start + 3; ++i)
		{
			num = num * 10 + (s[i] - '0');
			if (num <= 255)
			{
				ip += s[i];
				dfs(s, i + 1, step + 1, ip + '.', result);
			}
			if (num == 0)// 不允许前缀0，但允许单个0
				break;
		}
	}
};

//9.4 a. Given a set of candidate numbers (C) and a target number (T) all positive, find all unique combinations in C where the candidate numbers sums to T.
//The same repeated number may be chosen from C unlimited number of times. Output should be unique in ascending order. 时间复杂度O(n!)，空间复杂度O(n)
class Solution
{
public:
	vector<vector<int>> combinSum(vector<int> &num, int target)
	{
		sort(num.begin(), num.end());
		vector<vector<int>> result;
		vector<int> sub;
		dfs(num, target, 0, sub, result);
		return result;
	}
private:
	void dfs(vector<int> &num, int gap, int start, vector<int> &sub, vector<vector<int>> &result)
	{
		if (gap == 0)
		{
			result.push_back(sub);
			return;
		}
		for (int i = start; i < num.size(); ++i)//expand state
		{
			if (gap < num[i])//cut
				return;
			sub.push_back(num[i]);// execute expand active
			dfs(num, gap - num[i], i, sub, result);
			sub.pop_back();// withdraw
		}
	}
};

//b. The same repeated number may be chosen from C ONCE number of times. 时间复杂度O(n!)，空间复杂度O(n)
class Solution
{
public:
	vector<vector<int>> combinSum(vector<int> &num, int target)
	{
		sort(num.begin(), num.end());
		vector<vector<int>> result;
		vector<int> sub;
		dfs(num, target, 0, sub, result);
		return result;
	}
	void dfs(vector<int> &num, int gap, int start, vector<int> &sub, vector<vector<int>> &result)
	{
		if (gap == 0)
		{
			result.push_back(sub);
			return;
		}
		int pre = -1;
		for (int i = start; i < num.size(); ++i)
		{
			if (pre == num[i])//如果上一轮循环选了nums[i]，则本次循环就不能再选nums[i]，确保nums[i] 最多只用一次
				continue;
			if (num[i] > gap)
				return;
			pre = num[i];
			sub.push_back(num[i]);
			dfs(num, gap - num[i], i + 1, sub, result);
			sub.pop_back();
		}
	}
};

//9.5 Given a 2D board and a word, find if the word exists in the grid. The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighbouring.The same letter cell may not be used more than once
//深搜，递归, 时间复杂度O(n^2*m^2)，空间复杂度O(n^2)
class Solution
{
public:
	bool exist(vector<vector<char>> &board, string word)
	{
		int m = board.size();
		int n = board[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (dfs(board, word, 0, i, j, visited))
					return true;
			}
		}
		return false;
	}
private:
	static bool dfs(const vector<vector<char>> &board, const string &word, int index, int x, int y, vector<vector<bool>> &visited)
	{
		if (index == word.size())
			return true;
		if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
			return false;
		if (visited[x][y])
			return false;
		if (board[x][y] != word[index])
			return false;
		visited[x][y] = true;
		bool res = dfs(board, word, index + 1, x - 1, y, visited) || dfs(board, word, index + 1, x + 1, y, visited)
			|| dfs(board, word, index + 1, x, y - 1, visited) || dfs(board, word, index + 1, x, y + 1, visited);
		visited[x][y] = false;
		return res;
	}
};

//BFS-广度优先搜索:
//9.11 Word Ladder: Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that :
//• Only one letter can be changed at a time; • Each intermediate word must exist in the dictionary; • Return 0 if there is no such transformation sequence.
//Note: • All words have the same length. • All words contain only lowercase alphabetic characters.
//For example, Given : start = "hit"; end = "cog"； dict = ["hot", "dot", "dog", "lot", "log"]. As one shortest transformation is ”hit” -> ”hot” -> ”dot” -> ”dog” -> ”cog”, return its length 5.
class Solution
{
public:
	int wordLadder(const string &start, const string &end, const unordered_set<string> &dict)
	{
		queue<string> current, next;// 当前层，下一层
		unordered_set<string> visited;//unique
		int level = 0;
		bool found = false;
		auto target = [&](const string &s){return s == end; };
		auto extend = [&](const string &s)
		{
			vector<string> result;
			for (int i = 0; i < s.size(); ++i)
			{
				string new_word(s);
				for (char c = 'a'; c <= 'z'; ++c)
				{
					if (c == new_word[i])
						continue;
					swap(c, new_word[i]);
					if ((dict.count(word) > 0 || word == end) && !visited.count(new_word))
					{
						result.push_back(new_word);
						visited.insert(new_word);
					}
					swap(c, new_word[i]);// restore back
				}
			}
			return result;
		};
		current.push(start);
		while (!current.empty() && !found)
		{
			++level;
			while (!current.empty() && !found)
			{
				const string str = current.front();
				current.pop();
				const auto &state = extend(str);
				for (const auto &st : state)
				{
					next.push(st);
					if (target(st))
					{
						found = true;//done
						break;
					}
				}
			}
			swap(next, current);
		}
		if (found)
			return level + 1;
		else
			return 0;
	}
};
//b. find all shortest transformation sequence(s) from start to end, 时间复杂度O(n)，空间复杂度O(n)
void gen_path(unordered_map<string, vector<string>> &father, vector<string> &path, string &start, string &word, vector<vector<string>> &result)
{
	path.push_back(word);
	if (word == start)
	{
		result.push_back(path);
		reverse(result.back().begin(), result.back().end());
	}
	else
	{
		for (auto &s : father[word])
			gen_path(father, path, start, s, result);
	}
	path.pop_back();
}
vector<vector<string>> ladderPath(string start, string end, const unordered_set<string> &dict)
{
	unordered_set<string> cur, next; // 当前层，下一层，用集合是为了去重
	unordered_set<string> visited; // avoid duplicate
	unordered_map<string, vector<string>> father; // tree
	bool found = false;
	auto target = [&](const string &s){return s == end; };
	auto extend = [&](const string &s){
		unordered_set<string> result;
		for (int i = 0; i < s.size(); ++i)
		{
			string word(s);
			for (char c = 'a'; c <= 'z'; ++c)
			{
				if (c == word[i])
					continue;
				swap(c, word[i]);
				if ((dict.count(word) > 0 || word == end) && !visited.count(word))
					result.insert(word);
				swap(c, word[i]); //restore
			}
		}
		return result;
	};
	cur.insert(start);
	while (!cur.empty() && !found)
	{
		// 先将本层全部置为已访问，防止同层之间互相指向
		for (const auto &word : cur)
			visited.insert(word);
		for (const auto &word : cur)
		{
			const auto state = extend(word);
			for (auto &st : state)
			{
				if (target(st))
					found = true;
				next.insert(st);
				father[st].push_back(word);
			}
		}
		cur.clear();
		swap(cur, next);
	}
	vector<vector<string>> result;
	if (found)
	{
		vector<string> path;
		gen_path(father, path, start, end, result);
	}
	return result;
}

//9.12 Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region .
//广搜。从上下左右四个边界往里走，凡是能碰到的'O'，都是跟边界接壤的，应该保留, 时间复杂度O(n)，空间复杂度O(n)
class Solution
{
public:
	void fillBoard(vector<vector<char>> &board)
	{
		if (board.empty())
			return;
		int m = board.size();
		int n = board[0].size();
		for (int i = 0; i < n; ++i)
		{
			bfs(board, 0, i);
			bfs(board, m - 1, i);
		}
		for (int j = 1; j < m - 1; j++)
		{
			bfs(board, j, 0);
			bfs(board, j, n - 1);
		}
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == '+')
					board[i][j] = 'O';
			}
		}
	}
private:
	void bfs(vector<vector<char>> &board, int i, int j)
	{
		queue<pair<int, int>> q;
		int m = board.size();
		int n = board[0].size();
		auto valid = [&](pair<int, int> &s)
		{
			int x = s.first;
			int y = s.second;
			if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O')
				return false;
			return true;
		};
		auto extend = [&](pair<int, int> &s)
		{
			vector<pair<int, int>> result;
			int x = s.first;
			int y = s.second;
			pair<int, int> state[4] = { { x - 1, y }, { x + 1, y }, { x, y - 1 }, { x, y + 1 } };// up, down, left, right
			for (int k = 0; k < 4; ++k)
			{
				if (valid(state[k]))
				{
					// 既有标记功能又有去重功能
					board[state[k].first][state[k].second] = '+';
					result.push_back(state[k]);
				}
			}
			return result;
		};
		pair<int, int> start = { i, j };
		if (valid(start))
		{
			board[i][j] = '+';
			q.push(start);
		}
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			auto state = extend(cur);
			for (auto s : state)
				q.push(s);
		}
	}
};


//Sort.1 quick sort Time average O(nlogn) normally is faster than O(nlogn), worst case O(n^2)
//a. 设置一快一慢两个指针，慢指针左侧都是小于等于pivot(包含慢指针所在位置)， 慢指针到快指针之间的值是大于pivot，快指针右侧的值是还未比较过的
void qsort(int a[], int head, int end)//qsort（a, 0, n);
{
	if(a == NULL || head == end)
		return;
	int slow = head, fast = head + 1;
	int pivot = a[head];
	while(fast < end)
	{
		if(a[fast] <= pivot)
		{
			int t = a[++slow];
			a[slow] = a[fast];
			a[fast] = t;
		}
		++fast;
	}
	int t = a[head]; a[head] = a[slow]; a[slow] = t;
	qsort(a, head, slow);
	qsort(a, slow+1, end);
}
//b. better, 双向移动版本的快排，一个是从左向右移动，一个是从右向左移动, 小于等于pivot    ｜i    ？    |j    大于pivot
//指针j不断向左移动，直到遇到小于等于pivot，就交换指针i和j所指元素 (指针i一开始指向pivot)；指针i不断向右移动，直到遇到大于pivot的， 就交换指针i和j所指元素。pivot在这个过程中，不断地换来换去， 最终会停在分界线上，分界线左边都是小于等于它的元素，右边都是大于它的元素。 这样就避免了最后还要交换一次pivot的操作
int partition(int a[], int low, int high)
{
	int pivot = a[low], i = low, j = high;
	while(i < j)
	{
		while(i < j && a[j] > pivot)
			--j;
		if(i < j)
			a[i++] = a[j];
		while(i < j && a[i] <= pivot)
			++i;
		if(i < j)
			a[j--] = a[i];
	}
	a[i] = pivot;
	return i;
}
void quicksort(int a[], int first, int last)
{
	if(first < last)
	{
		int k = partition(a,first,last);
		quicksort(a,first,k-1);
		quicksort(a,k+1, last);
	}
}
//iterator qsort ,IterQSort(arr, 0,n-1)
struct QS
{
	int begin, end;
};
void IterQSort(int arr[], int begin, int end)
{
	if(arr == NULL || begin >= end)
		return;
	QS qs;
	stack<QS> sqs;
	qs.begin = begin;
	qs.end = end;
	sqs.push(qs);
	while(!sqs.empty())
	{
		qs = sqs.top();
		sqs.pop();
		if(qs.begin < qs.end)
		{
			int n = partition(arr,qs.begin,qs.end);
			QS tmp;
			tmp.begin = qs.begin;
			tmp.end = n-1;
			sqs.push(tmp);
			tmp.begin = n+1;
			tmp.end = qs.end;
			sqs.push(tmp);
		}
	}
}

//Sort.2 Merge sort Time O(nlogn) Space O(n)
// Recursion method
void merge(int *a, int l, int r)
{
	if(a == NULL || l >= r)
		return;
	int m = (l+r)/2;
	int k = l, i = l, j = m+1;
	int *t = new int[r+1];
	if(t == NULL)
		return;
	memset(t,0,sizeof(int)*(r+1));
	while(k<=r)
	{
		if(j>r)// descending sort
			t[k++] = a[i++];
		else if(i>m)
			t[k++] = a[j++];
		else
		{
			if(a[i] > a[j])
				t[k++] = a[i++];
			else
				t[k++] = a[j++];
		}
	}
	delete[] t;
	t = NULL;
	return;
}
void mergesort(int *a, int l, int r)
{
	if(l < r)
	{
		int m = (l + r)/2;
		mergesort(a, l,m);
		mergesort(a,m+1,r);
		merge(a,l,r);
	}
}
//merge sort iteration
void merge_sort(int *a, int len)
{
	int left_min=0, left_max=0, right_min=0, right_max=0;
	int *tmp = (int*)malloc(sizeof(int) * len);
	if (tmp == NULL) 
		return;
	memset(tmp,0,sizeof(int)*len);
	for (int i = 1; i < len; i *= 2)
	{
		for (left_min = 0; left_min < len - i; left_min = right_max)
		{ 			
			right_min = left_max = left_min + i;
			right_max = right_min + i;
			if (right_max > len)
				right_max = len;
			int	next = 0;
			while (left_min < left_max && right_min < right_max)
				tmp[next++] = a[left_min] > a[right_min] ? a[right_min++] : a[left_min++];
			while (left_min < left_max)
				a[--right_min] = a[--left_max];
			while (next > 0)
				a[--right_min] = tmp[--next];
		}
	}
	free(tmp);
	tmp = NULL;
	return;
}

// b. Sort a linked list in O(nlogn) time using constant space complexity
//常数空间且O(nlogn)，单链表适合用归并排序，双向链表适合用快速排序
SLL *sortList(SLL *head)
{
	SLL *fast = head, *slow = head;// 快慢指针找到中间节点
	while (fast->next != nullptr && fast->next->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	fast = slow;//断开
	slow = slow->next;
	fast->next = NULL;
	SLL *l1 = sortList(head);// 前半段排序
	SLL *l2 = sortList(slow);// 后半段排序
	return merge2list(l1, l2);
}

//Sort.3 shell sort
void shellsort(int *a, int n)
{
	for(int gap=n/2;gap>0;gap/=2)
	{
		cout<<"gap = "<<gap<<endl;
		for(int i = 0;i<gap;i++)
		{
			cout<<"i = "<<i<<endl;
			for(int j=i+gap;j<n;j+=gap)
			{
				cout<<"j = "<<j<<endl;
				for(int k=j;k>0;k-=gap)
				{
					cout<<"k = "<<k<<endl;
					if(a[k]<a[k-1])
					{
						a[k]=a[k]^a[k-1];
						a[k-1]=a[k]^a[k-1];
						a[k]=a[k]^a[k-1];
					}
				}
				for(int c=0;c<n;c++)
				{
					cout<<a[c]<<", ";
				}
			}
		}
	}
	return;
}

//Sort.4 Bubble Sort O(n^2)
void BubbleSort(int a[],int n)
{
	if(a == NULL || n < 2 )
		return;
	int i = 0, j = 0;
	int big = 0;
	for(i = 0;i < n;i++)
	{
		for(j=0;j<n-i-1;j++)//no need to compare sorted array
		{
			if(a[j] > a[j+1])
			{
				big = a[j];
				a[j] = a[j+1];
				a[j+1] = big;
			}
		}
	}
}

//Sort.5 Insert sort
void insertSort(int arr[], int n)
{
	if(arr == NULL || n < 1)
		return;
	for(int i=0; i<n; ++i)
	{
		int min = arr[i], m = i; 
		for(int j=i; j<n; ++j)
		{
			if(arr[j] < min)
			{
				min = arr[j];
				m = j;
			}
		}
		swap(arr[m], arr[i]);
	}
}

//b. Sort a linked list using insertion sort.
SLL *findInsertPos(SLL *head, int x)
{
	SLL *pre = NULL;
	for (SLL *cur = head; cur != nullptr && cur->data <= x; pre = cur, cur = cur->next);
	return pre;// less than x
}
SLL *insertSortList(SLL *head)
{
	SLL dummy(INT_MIN);
	for (SLL *cur = head; cur != nullptr;)
	{
		SLL *pos = findInsertPos(&dummy, cur->data);
		SLL *tmp = cur->next;
		cur->next = pos->next;
		pos->next = cur;
		cur = tmp;
	}
	return dummy.next;
}
//myself write
SLL *insertSort(SLL *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	SLL *cur = head, *newhead = NULL, *node = NULL;
	while (cur != nullptr)
	{
		SLL *next = cur->next, *pre = cur, *premin = cur, *min = cur;
		while (next != nullptr)
		{
			if (min->data > next->data)
			{
				premin = pre;
				min = next;
			}
			pre = next;
			next = next->next;
		}
		if (min != cur)
		{
			premin->next = min->next;
		}
		else
		{
			cur = cur->next;
		}
		if (newhead == NULL)
		{
			newhead = min;
			node = newhead;
		}
		else
		{
			node->next = min;
			node = node->next;
		}
	}
	return newhead;
}

//Sort.6 a.You are given two sorted arrays, A and B, and A has a large enough buffer at the end to hold B. Write a method to merge B into A in sorted order.
//from A和B的尾部元素开始对比，每次取大的元素放在数组A的尾部 Time O(n+m)
void merge2Array(int a[], int n, int b[], int m)
{
	int k = n + m -1;
	int i = n-1, j = m-1;
	while(i >= 0 && j >= 0)
	{
		if(a[i] > b[j])
			a[k--] = a[i--];
		else
			a[k--] = b[j--];
	}
	while(j >= 0)
		a[k--] = b[j--];
}

//b. 数组A，它的前半段和后半段分别有序，不使用额外的空间怎么使A整体有序
void mergeArray(int a[], int n)
{
	int mid = (n-1)/2;// n-1 for n is even.
	for(int i=0; i<=mid; ++i)
	{
		if(a[i] > a[mid+1])
		{
			swap(a[i], a[mid+1]);
			for(int j=mid+1; j<n-1; ++j)
			{
				if(a[j] < a[j+1])
					break;
				swap(a[j], a[j+1]);
			}
		}
	}
}

//c. Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
SLL *merge2list(SLL *l1, SLL *l2)//时间复杂度O(min(m, n))，空间复杂度O(1)
{
	if (l1 == nullptr)
		return l2;
	else if (l2 == nullptr)
		return l1;
	SLL dummy(-1);
	SLL *p = &dummy;
	for (; l1 != nullptr && l2 != nullptr; p = p->next)
	{
		if (l1->data > l2->data)
		{
			p->next = l2;
			l2 = l2->next;
		}
		else
		{
			p->next = l1;
			l1 = l1->next;
		}
	}
	p->next = l1 != nullptr ? l1 : l2;
	return dummy.next;
}

//d. Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
// 时间复杂度O(n1+n2+...)，空间复杂度O(1)
SLL* mergeKlists(vector<SLL*> &lists)
{
	if (lists.size() == 0)
		return NULL;
	SLL *p = lists[0];
	for (int i = 1; i < lists.size(); ++i)
		p = merge2list(p, list[i]);
	return p;
}

//Sort.7 Write a method to sort an array of strings so that all the anagrams are next to each other.
bool cmp(string s1, string s2)//sort(s, s+s.length(), cmp);
{
	sort(&s1[0], &s1[0]+s1.length());
	sort(&s2[0], &s2[0]+s2.length());
	return s1 < s2;
}

//Sort.8 Find the K closest points to the origin in 2D plane, given an array containing N points. You can assume K is much smaller than N and N is very large. 
//You need only use standard math operators (addition, subtraction, multiplication, and division).
//m1. use int + vector<> + make_heap
typedef struct point
{
	int x, y;
}Point;
void topkmin(Point a[], int dis[], int r[], int n, int k)
{	
	for(int i=0;i<n;++i)//pre calculate the distance
	{
		dis[i] = a[i].x*a[i].x + a[i].y*a[i].y;
	}
	vector<int> vi(dis,dis+k);

	make_heap(vi.begin(), vi.end());

	for(int i=k; i<n; ++i)
	{
		if(dis[i] < vi[0])
		{
			vi[0] = dis[i];
			make_heap(vi.begin(),vi.end());
		}
	}
	for(int i=0;i<k;++i)
		r[i] = vi[i];
	return;
}
//use double + priority_queue<double, deque<double>, less<double>>
struct Point
{
	double x, y;
/*	srand((unsigned)time(NULL));
	Point p[10];
	for(int i=0; i<10; ++i)
	{
		p[i].x = rand()/(double)(RAND_MAX/100);
		p[i].y = rand()/(double)(RAND_MAX/100);
	}
	double *dp = kPoint2Ori(p, 10, 5);
	delete[] dp;*/
};
double *kPoint2Ori(Point p[], int n, int k)
{
	if(p == NULL || n < 1 || k < 1 || k > n)
		return NULL;
	double *dist = new double[n];
	for(int i=0; i<n; ++i)
		dist[i] = p[i].x * p[i].x + p[i].y * p[i].y;
	priority_queue<double, deque<double>, less<double>> pq;
	for(int i=0; i<k; ++i)
		pq.push(dist[i]);
	for(int i=k; i<n; ++i)
	{
		if(pq.top() > dist[i])
		{
			pq.pop();
			pq.push(dist[i]);
		}
	}
	double *dp = new double[k];
	for(int i=0; i<k; ++i)
	{
		dp[i] = pq.top();
		pq.pop();
	}
	delete[] dist;
	dist = NULL;
	return dp;
}
//m2 use partition find k small one.
int partition(int a[], int b, int e)
{
	if(!a || b >= e)
		return -1;
	int t = -1;
	while(t<b)
		t = rand()%e;
	swap(a[b],a[t]);
	int l = b, r = e, pivot = a[l];
	while(l<r)
	{
		while(l<r && a[r] >= pivot)
			--r;
		if(l<r)
			a[l++] = a[r];
		while(l<r && a[l] < pivot)
			++l;
		if(l<r)
			a[r--] = a[l];
	}
	a[l] = pivot;
	return l;
}
int findKCloseP(int a[], int n, int k)
{
	if(!a)
		return -1;
	int m = partition(a, 0, n-1);
	while(m != k-1)
	{
		if(m < k-1)
			m += partition(a, m+1, n-1);
		else
			m = partition(a, 0, m-1);
	}
	return m;
}

//Sort.9 求数组中出现频率最高的数, O(nlogn)
int FindNumMostTime(int a[], int n)
{
	if(a == NULL)
		return -1;
	sort(a, a+n);
	int value = a[0], time = 1, maxNum = 1, maxValue = a[0];
	for(int i=1; i<n; ++i)
	{
		if(value == a[i])
		{
			++time;
			if(time >= maxNum)
			{
				maxNum = time;
				maxValue = a[i];
			}
		}
		else
		{
			value = a[i];
			time = 1;
		}
	}
	return maxValue;
}

//Sort.10. Given an unsorted integer array, find the first missing positive integer. For example, Given[1, 2, 0] return 3, and[3, 4, -1, 1] return 2.
//本质上是桶排序(bucket sort)，每当A[i]!= i+1 的时候，将A[i] 与A[A[i]-1] 交换，直到无法交换为止，终止条件是A[i] == A[A[i] - 1], 时间复杂度O(n)，空间复杂度O(1)
void bucketSort(int a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		while (a[i] != i + 1)
		{
			if (a[i] <= 0 || a[i] > n || a[i] == a[a[i] - 1])
				break;
			swap(a[i], a[a[i] - 1]);
		}
	}
}
int missNum(int a[], int n)
{
	bucketSort(a, n);
	for (int i = 0; i < n; ++i)
	if (a[i] != i + 1)
		return i + 1;
	return n + 1;
}

//Sort.11 counting sort, Time O(n+k), Space O(n + k) where n is the number of elements in input array and k is the range of input. 
void countSort(char *str)//sort the given string str in alphabatical order
{
	const int SIZE = 255;
	if (str == NULL) return;
	int n = strlen(str);
	char *output = new char[n];
	// Create a count array to store count of inidividul characters and initialize count array as 0
	int count[SIZE + 1] = { 0 }, i = 0;
	for (i = 0; i < n; ++i)// Store count of each character
		++count[str[i]];
	// Change count[i] so that count[i] now contains actual position of this character in output array
	for (i = 1; i <= SIZE; ++i)
		count[i] += count[i - 1];
	// Build the output character array
	for (i = 0; i < n; ++i)
	{
		output[count[str[i]] - 1] = str[i];
		--count[str[i]];
	}
	for (i = 0; i < n; ++i)
		str[i] = output[i];
	delete[] output;
}
//sort the given array in accsending order
void countSort(int a[], int n)
{
	const int SIZE = 10;
	int *output = new int[n];
	memset(output, 0, sizeof(int)*n);
	// Create a count array to store count of inidividul characters and initialize count array as 0
	int count[SIZE + 1] = { 0 }, i = 0;
	for (i = 0; i < n; ++i)// Store count of each character
		++count[a[i]];
	// Change count[i] so that count[i] now contains actual position of this character in output array
	for (i = 1; i <= SIZE; ++i)
		count[i] += count[i - 1];
	// Build the output character array
	for (i = 0; i < n; ++i)
	{
		output[count[a[i]] - 1] = a[i];
		--count[a[i]];
	}
	for (i = 0; i < n; ++i)
		a[i] = output[i];
	delete[] output;
}

//Sort.12 Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
//Counting Sort, 时间复杂度O(n)，空间复杂度O(1), Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively,
void sortColors(int a[], int n)
{
	int count[3] = { 0 };//记录每个颜色出现的次数
	for (int i = 0; i < n; ++i)
		++count[a[i]];
	for (int i = 0, index = 0; i < 3; ++i)
	{
		for (int j = 0; j < count[i]; ++j)
			a[index++] = i;
	}
}
// 双指针，时间复杂度O(n)，空间复杂度O(1)
void sortColor(int a[], int n)
{
	// 一个是red 的index，一个是blue 的index，两边往中间走
	int red = 0, blue = n - 1;
	for (int i = 0; i < blue + 1;)
	{
		if (a[i] == 0)
			swap(a[i++], a[red++]);
		else if (a[i] == 2)
			swap(a[i], a[blue--]);
		else
			++i;
	}
}
// use partition(), 时间复杂度O(n)，空间复杂度O(1)
void sortColor(int a[], int n)
{
	partition(partition(a, a + n, bind1st(equal_to<int>(), 0)), a + n, bind1st(equal_to<int>(), 1));
}
//重新实现partition(), 时间复杂度O(n)，空间复杂度O(1)
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
	auto pos = first;
	for (; first != last; ++first)
	{
		if (pred(*first))
			swap(*first, *post++);
	}
	return pos;
}