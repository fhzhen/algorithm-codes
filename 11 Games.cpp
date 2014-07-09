//11.1 Design an algorithm to figure out if someone has won in a game of tic-tac-toe.
//1. 如果HasWon函数需要被频繁调用. 对于井字游戏，每个格子可以是空，我的棋子和对方的棋子3种可能，总共有39 = 19683 种可能状态。我们可以把每一种状态转换成一个整数， 预处理时把这个状态下是否有人赢得了井字游戏保存起来，每次检索时就只需要O(1)时间。 比如每个格子上的3种状态为0(空)，1(我方棋子)，2(对方棋子)，棋盘从左到右， 从上到下依次记为0到8，那么任何一个状态都可以写成一个3进制的数，再转成10进制即可。122211201=1*3^8 + 2*3^7 +...+ 0*3^1 + 1*3^0
//2. 如果HasWon函数只被调用一次或很少次.判断n*n的棋盘是否有人赢，即同一棋子连成一线
enum Check
{
	ROW, COLUMN, DIAGONAL, REDIAGONAL
};
int checkRowColumn(int board[], int n, Check check)//return 0,1,2
{
	int type = 0;
	for(int i=0; i<n; ++i)
	{
		bool found = true;
		for(int j=0; j<n; ++j)
		{
			int k = 0;//棋子位置
			if(check == ROW)
				k = i * n + j;
			else
				k = i + j * n;//列
			if(j == 0)
			{
				type = board[k];
			}
			else if(board[k] != type)
			{
				found = false;
				break;
			}
		}
		if(found)
			return type;
	}
	return 0;// no one win
}
int checkDiagonal(int board[], int n, Check check)
{
	int type = 0;
	bool found = true;
	for(int i=0; i<n; ++i)
	{
		int k = 0;
		if(check == DIAGONAL)
			k = i + i * n;
		else
			k = i + (n-i-1)*n;
		if(i == 0)
			type = board[k];
		else if(board[k] != type)
		{
			found = false;
			break;
		}
	}
	if(found)
		return type;
	else
		return 0;
}
int ticTacToe(int board[], int n)
{
	int type = 0;
	type = checkRowColumn(board, n, ROW);
	if(type != 0)
		return type;
	type = checkRowColumn(board, n, COLUMN);
	if(type != 0)
		return type;
	type = checkDiagonal(board, n, DIAGONAL);
	if(type != 0)
		return type;
	type = checkDiagonal(board, n, REDIAGONAL);
	if(type != 0)
		return type;
	return 0;
}

//11.2 The Game of Master Mind is played as follows: The computer has four slots containing balls that are red (R ), yellow (Y), green (G) or blue (B). For example, the computer might have RGGB (e.g., Slot #1 is red, Slots #2 and #3 are green, Slot #4 is blue).
//The user are trying to guess the solution. You might, for example, guess YRGB.When you guess the correct color for the correct slot, you get a “hit”. If you guess a color that exists but is in the wrong slot, you get a “pseudo-hit”. For example, the guess YRGB has 2 hits and one pseudo hit.
//For each guess, you are told the number of hits and pseudo-hits. Write a method that, given a guess and a solution, returns the number of hits and pseudo hits.
struct Result
{
	int hits;
	int pseudo_hits;
};
Result masterMind(const char* result, const char* guess)
{
	Result res;
	res.hits = 0;
	res.pseudo_hits = 0;
	int mask = 0;
	for(int i=0; i<4; ++i)
		mask |= 1<<(result[i] - 'A');
	for(int i=0; i<4; ++i)
	{
		if(guess[i] == result[i])
			++res.hits;
		else if(mask & (1<<(guess[i]-'A')))
		{
			++res.pseudo_hits;
		}
	}
	return res;
}

//11.3 约瑟夫问题 josephus problem. Given the total number of persons n and a number k which indicates that k-1 persons are skipped and kth person is killed in circle. 
//The task is to choose the place in the initial circle so that you are the last one remaining and so survive.
//brute force, time O(n^2)
int jsf(int a[], int n, int m)
{
	int i = 0, count = 1, last = 0, outnum = 0;
	while(outnum < (n-1))
	{		
		for(i=0; i<n; ++i)
		{
			if(a[i] == 0)// survive
			{
				if(count < m)
				{
					++count;
				}
				else// count m
				{
					a[i] = 1;//killed
					count = 1;
					++outnum;
				}
			}
		}		
	}
	for(i=0;i<n;++i)
	{
		if(a[i] == 0)
			return i+1;
	}
	return 0;
}
//DP1: recursion time O(n): f(n,k)=(f(n-1,k)+k)%n，f(1,k)=0; josephus(1, k) = 1, josephus(n, k) = (josephus(n - 1, k) + k-1) % n + 1,
// When the index starts from one, then the person at s shifts from the first person is in position ((s-1)mod n)+1, where n is the total number of persons.
//Let f(n,k) denote the position of the survivor. After the k-th person is killed, we're left with a circle of n-1, and we start the next count with the person 
//whose number in the original problem was (k\bmod n)+1. The position of the survivor in the remaining circle would be f(n-1,k) if we start counting at 1; shifting this to account for the fact that we're starting at (k\bmod n)+1 yields the recurrence
int josephus(int n, int k)
{
	if(n == 1)
		return 1;
	else
		return(josephus(n-1,k) + k -1)%n + 1;
}
//iterative method
int jsp(int n, int m)
{
	int s = 0;
	for(int i=2;i<=n;++i)
		s = (s + m) % i;//从最后一个人往n个人推导
	return s + 1;
}
//DP2: small k and large n time O(klogn).based on considering killing k-th, 2k-th, ..., (k)-th people as one step, then changing the numbering.

//11.4 下排数是上排对应数字在下排出现的次数 input: 0,1,2,3,4,5,6,7,8,9 ; output: 6,2,1,0,0,0,1,0,0,0
void rowRiddle()
{
	/*
1）下排n个数的累加和为n，即b[0]+b[1]+...+b[n-1] = n
2）ai*bi的累加和也为n，即a[0]*b[0]+a[1]*b[1]+...+a[n-1]*b[n-1] = n
3）对于b中任意一个元素b[j], 都存在i，a[i] = b[j].
4）对于b中任意一个元素b[j],都有b[j] >= 0
5）如果a中存在负数。其在b中出现的次数一定为0. 如果a中数值大于n，则其出现次数也为0.
6）a中至少有两个非0数值在b中出现的次数非0
结论：
1）如果上排数列中有0，此时如果上排数列中无0,1,2,n-4这四个数，则下排数列无解；否则下排数列中0出现的次数为n-4；1出现的次数为2；2出现的次数为1；n-4出现的次数为1；其余为0。
2）如果上排数列中无0，则下排数列全0，是其唯一解。
	*/
	int r1[10] = {6,1,2,3,4,5,0,7,8,19};
	int r2[10] = {0};
	int count = 0;
	bool changed = true;
	while(changed)
	{
		changed = false;
		for(int i=0; i<10; ++i)
		{
			count = 0;
			for(int j=0; j<10; ++j)
			{
				if(r2[j] == r1[i])
					++count;
			}
			if(r2[i] != count)
			{
				changed = true;
				r2[i] = count;
			}
		}
	}
	for(int i=0; i<10; ++i)
		cout<<r2[i]<<" ";
	cout<<endl;
}

//11.5 字母算式 WWWDOT - GOOGLE = DOTCOM，求每个字母代表数字 ,int arr[10] = {0,1,2,3,4,5,6,7,8,9};
void SolveCRM(int *a, int n)
{
	int tmp, i;
	int w,d,o,t,g,l,e,c,m,wwwdot,google,dotcom;
	if(n == 1)
	{
		w = a[0];
		d = a[1];
		o = a[2];
		t = a[3];
		g = a[4];
		l = a[5];
		e = a[6];
		c = a[7];
		m = a[8];
		if(w != 0 && g != 0 && d != 0)
		{
			wwwdot = w*111000 + d*100 + o*10 + t;
			google = g*100100 + o*11000 + l*10 + e;
			dotcom = d*100000 + o*10010 + t*1000 + c*100 + m;
			if((wwwdot - google == dotcom) || (wwwdot - (google -e + m) == (dotcom - m + e)))
				printf("%d - %d = %d\n",wwwdot,google,dotcom);
		}
		return;
	}
	else
	{
		for(i=0; i<n; ++i)
		{
			tmp = a[i]; a[i] = a[n-1]; a[n-1] = tmp;
			SolveCRM(a,n-1);
			tmp = a[i]; a[i] = a[n-1]; a[n-1] = tmp;
		}
	}
}
//iterative
void SolveCRM(int *a, int n)
{
	int tmp, i1,i2,i3,i4,i5,i6,i7,i8,i9;
	int w,d,o,t,g,l,e,c,m,wwwdot,google,dotcom;
	for(i1=0; i1<n; ++i1)
	{		
		if(a[i1] == 0)
			continue;
		w = a[i1];
		tmp = a[i1]; a[i1] = a[0]; a[0] = tmp;
		for(i2 = 1;i2<n;++i2)
		{
			if(a[i2] == 0)
				continue;
			d=a[i2];
			tmp = a[i2]; a[i2] = a[1]; a[1] = tmp;
			for(i3=2;i3<n;++i3)
			{
				if(a[i3] == 0)
					continue;
				o=a[i3];
				tmp = a[i3]; a[i3] = a[2]; a[2] = tmp;
				for(i4=3;i4<n;++i4)
				{				
					t=a[i4];
					tmp = a[i4]; a[i4] = a[3]; a[3] = tmp;
					for(i5=4;i5<n;++i5)
					{
						g=a[i5];
						tmp = a[i5]; a[i5] = a[4]; a[4] = tmp;
						for(i6=5;i6<n;++i6)
						{
							l=a[i6];
							tmp = a[i6]; a[i6] = a[5]; a[5] = tmp;
							for(i7=6;i7<n;++i7)
							{
								e=a[i7];
								tmp = a[i7]; a[i7] = a[6]; a[6] = tmp;
								for(i8=7;i8<n;++i8)
								{
									c=a[i8];
									tmp = a[i8]; a[i8] = a[7]; a[7] = tmp;
									for(i9=8;i9<n;++i9)
									{
										m=a[i9];
										tmp = a[i9]; a[i9] = a[8]; a[8] = tmp;
										++count1;
										wwwdot = w*111000 + d*100 + o*10 + t;
										google = g*100100 + o*11000 + l*10 + e;
										dotcom = d*100000 + o*10010 + t*1000 + c*100 + m;
										if((wwwdot - google == dotcom) || (wwwdot - (google -e + m) == (dotcom - m + e)))
											printf("%d - %d = %d\n",wwwdot,google,dotcom);
									}
								}							
							}
						}
					}
				}
			}
		}		
	}	
}

//11.6 a. Imagine a robot sitting on the upper left hand corner of an MxN grid. The robot can only move in two directions: right and down. How many possible paths are there for the robot?
//Backtracking - recursion, 对于矩阵中的格子(i, j)，假设从(1, 1)到它的路径数量为path(i, j) = path(i-1, j) + path(i, j-1). 深搜，小集合可以过，大集合会超时, 时间复杂度O(n^4)，空间复杂度O(n)
int recuPath(int m, int n)
{
	if (m < 1 || n < 1)
		return 0;
	if (m == 1 || n == 1)
		return 1;
	return recuPath(m - 1, n) + recuPath(m, n - 1);
}
// 深搜+缓存，即备忘录法, 时间复杂度O(n^2)，空间复杂度O(n^2)
class Solution
{
public:
	int uniquePaths(int m, int n)
	{
		//doesn't use row 0 and column 0 
		vvi = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
		return dfs(m, n);
	}
private:
	vector<vector<int>> vvi;//cache
	int dfs(int m, int n)
	{
		if (m < 1 || n < 1)
			return 0;
		else if (m == 1 || n == 1)
			return 1;
		else
			return update(m - 1, n) + update(m, n - 1);
	}
	int update(int m, int n)
	{
		if (vvi[m][n] > 0)
			return vvi[m][n];
		else
			return vvi[m][n] = dfs(m, n);
	}
};
// Mathematic,  机器人从(1, 1)走到(m, n)一定要向下走m-1次，向右走n-1次，不管这过程中是怎么走的。 因此，一共可能的路径数量就是从总的步数(m-1+n-1)里取出(m-1)步，作为向下走的步子， 剩余的(n-1)步作为向右走的步子。
int factorial(int n)
{
	if (n<0)
		return -1;
	else if (n == 0 || n == 1)
		return 1;
	else
		return n*factorial(n - 1);
}
int mathPath(int m, int n)
{
	if (m < 1 || n < 1)
		return 0;
	else if (m == 1 || n == 1)
		return 1;
	else
		return factorial(m - 1 + n - 1) / (factorial(m - 1)*factorial(n - 1));
}
//DP 1
int backtrack(int r, int c, int m, int n, int p[][10 + 2])
{
	if (r == m && c == n)
		return 1;
	if (r > m || c > n)
		return 0;
	if (p[r + 1][c] == -1)
		p[r + 1][c] = backtrack(r + 1, c, m, n, p);
	if (p[r][c + 1] == -1)
		p[r][c + 1] = backtrack(r, c + 1, m, n, p);
	return p[r + 1][c] + p[r][c + 1];
}
int pathDP(int m, int n)
{
	int p[10 + 2][10 + 2];
	for (int i = 0; i < 10 + 2; ++i)
	{
		for (int j = 0; j < 10 + 2; ++j)
			p[i][j] = -1;
	}
	return backtrack(1, 1, m, n, p);
}
//better DP2
int dpPath(int m, int n)
{
	int **p = new int*[m + 2];
	for (int i = 0; i < m + 2; ++i)
	{
		p[i] = new int[n + 2];
		memset(p[i], 0, sizeof(int)*(n + 2));
	}
	p[m][n + 1] = 1;
	for (int r = m; r >= 1; --r)
	{
		for (int c = n; c >= 1; --c)
			p[r][c] = p[r + 1][c] + p[r][c + 1];
	}
	int res = p[1][1];
	for (int i = 0; i < m + 2; ++i)
		delete[] p[i];
	delete[] p;
	return res;
}
//better DP, 时间复杂度O(n^2)，空间复杂度O(n)
int uniquePath(int m, int n)
{
	vector<int> f(n, 0);
	f[0] = 1;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
			// 左边的f[j]，表示更新后的f[j]，与公式中的f[i][j] 对应
			// 右边的f[j]，表示老的f[j]，与公式中的f[i-1][j] 对应
			f[j] = f[j - 1] + f[j];
	}
	return f[n - 1];
}

//b. Imagine certain squares are “off limits”, such that the robot can not step on them. Design an algorithm to get all possible paths for the robot.
class Solution
{
	struct Point
	{
		int x;
		int y;
	};
	const int NUM = 10;
	int go[3][3] = { { 1, 1, 1 }, { 1, 1, 1, }, { 0, 1, 1 } };//M*N的矩阵，元素为1表示该位置可以走，为0表示该位置不可走
	Point ap[NUM * 2];
	stack<Point> sp;
	//get 1 path
	bool getPath(int m, int n)
	{
		if (n == 1 || m == 1)
			return true;
		Point p;
		p.x = m;
		p.y = n;
		sp.push(p);
		bool suc = false;
		if (m>1 && go[m - 1][n])
			suc = getPath(m - 1, n);
		if (!suc && n>1 && go[m][n - 1])
			suc = getPath(m, n - 1);
		if (!suc)
			sp.pop();
		return suc;
	}
	void allPath(int m, int n, int M, int N, int len)//allPath(0,0,2,2,0);
	{
		if (go[m][n] == 0 || n > N || m > M)
			return;
		Point p;
		p.x = m;
		p.y = n;
		ap[len++] = p;
		if (m == M && n == N)
		{
			for (int i = 0; i<len; ++i)
				cout << "(" << ap[i].x << ", " << ap[i].y << ")" << " ";
			cout << endl;
		}
		else
		{
			allPath(m, n + 1, M, N, len);
			allPath(m + 1, n, M, N, len);
		}
	}
};
// 动规，滚动数组, 时间复杂度O(n^2)，空间复杂度O(n)
int pathWithBlock(vector<vector<int>> &grid)
{
	int m = grid.size();
	int n = grid[0].size();
	if (grid[0][0] || grid[m - 1][n - 1])
		return 0;
	vector<int> f(n, 0);
	f[0] = grid[0][0] ? 0 : 1;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
			f[j] = grid[i][j] ? 0 : (j == 0 ? 0 : f[j - 1]) + f[j];
	}
	return f[n - 1];
}

/*11.7 The pile contains ‘N’ kg of nuts, and the town is ‘D’ kilometers away from the pile. Get ‘X’ the maximum amount of nuts that can be transported to the town.
The nuts are transported by a horse drawn cart that is initially next to the pile of nuts. The cart can carry at most ‘C’ kilograms of nuts at any one time. 
The horse uses the nuts that it is carrying as fuel. It consumes ‘F’ kilograms of nuts per kilometer traveled regardless of how much weight it is carrying in the cart.
The horse can load and unload the cart without using up any nuts. The function takes as input 4 real numbers D,N,F,C and returns one real number: ‘X’*/
double getMaxNuts(double n, double d, double c, double f)
{
	// base case: We have the capacity to carry all nuts, so fetch all the nuts in one trip
	if (n <= c)
	{
		double x = n - d * f;
		return (x > 0.0) ? x : 0.0;// out of fuel
	}
	// # trips you would travel back and forth
	int tripNum = 2 * (ceil(n / c) - 1) + 1;
	// how many nuts you consume per km
	double costPerKm = tripNum * f;
	// remaining weight of nuts after consumption, only deal the case where N is divisible by C.
	double restNuts = c * (ceil(n / c) - 1.0);
	// this is the distance you are able to travel before you reach ONE LESS round trip fetching nuts
	// derived from eq: N - costPerKm * traveled = restNuts
	double traveled = (n - restNuts) / costPerKm;
	// we are able to travel greater (or equal) than the remaining distance, so fetch the nuts right to the destination
	if (traveled >= d)
		return n - d*costPerKm;
	// calculate recursively as we travel ONE less round trip now.
	return getMaxNuts(restNuts, d - traveled, c, f);
}

//11.8 Snapper Chain Solution https://code.google.com/codejam/contest/dashboard?c=433101#s=p0
bool lightState(int n, int k)
{
	assert(n >= 1);
	assert(k >= 0);
	unsigned int sum = pow(2, n + 1) - 1;
	if (sum == k)
		return true;
	else
		return false;
}
bool isLight(int n, int k)
{
	return (k % (1 << n) == (1 << n) - 1);
}

//11.9 Roller coasters https://code.google.com/codejam/contest/dashboard?c=433101#s=p2
long long maxMoney(long long people[], long long r, long long k, long long n)
{
	long long *money = new long long[n];
	memset(money, 0, sizeof(long long)*n);
	int *start = new int[n];
	memset(start, 0, sizeof(int)*n);
	int st = 0;
	for (int i = 0; i < n; ++i)
	{
		long long sum = 0;
		st = i;
		bool done = false;
		for (int j = 0; j < n; ++j)
		{
			if (sum + people[(i + j) % n] <= k)
			{
				sum += people[(i + j) % n];
				st = (st + 1) % n;
			}
			else
			{
				money[i] = sum;
				start[i] = st;
				done = true;
				break;
			}
		}
		if (!done)
		{
			money[i] = sum;
			start[i] = st;
		}
	}
	long long max = 0;
	st = 0;
	for (long long i = 0; i < r; ++i)
	{
		max += money[st];
		st = start[st];
	}
	return max;
}

//11.10 a. Determine if a Sudoku is valid, Each row, column and 9 sub-boxes of the grid must have the numbers 1-9 occuring just once.
// The Sudoku board could be partially filled, where empty cells are filled with the character '.'
bool check(char ch, bool used[9])
{
	if (ch == '.')
		return true;
	if (used[ch - '1'])
		return false;
	return used[ch - '1'] = true;
}
bool sudoku(vector<vector<char>> &board)
{
	bool used[9];
	for (int i = 0; i < 9; ++i)
	{
		fill(used, used + 9, false);
		for (int r = 0; r < 9; ++r)//check row
		{
			if (!check(board[i][r], used))
				return false;
		}
		fill(used, used + 9, false);
		for (int c = 0; c < 9; ++c)
		{
			if (!check(board[c][i], used))
				return false;
		}
	}
	for (int r = 0; i < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			fill(used, used + 9, false);
			for (int i = r * 3; i < r * 3 + 3; ++i)
			{
				for (int j = c * 3; c < c * 3 + 3; ++j)
				if (!check(board[i][j], used))
					return false;
			}
		}
	}
	return true;
}

//b. Solve a Sudoku puzzle by filling the empty cells. there will be only one unique solution. 时间复杂度O(9^4)，空间复杂度O(1)
class Solution
{
	bool sudoku(vector<vector<char>> &board)
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (board[i][j] == '.')
				{
					for (int k = 0; k < 9; ++k)
					{
						board[i][j] = '1' + k;
						if (isValid(board, i, j) && sudoku(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}
private:
	bool isValid(vector<vector<char>> &board, int x, int y)// 检查(x, y) 是否合法
	{
		int i = 0, j = 0;
		for (i = 0; i < 9; ++i)// check y col
		{
			if (i != x && board[i][y] == board[x][y])
				return false;
		}
		for (j = 0; j < 9; ++j)//check x row
		{
			if (j != y && board[x][j] == board[x][y])
				return false;
		}
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); ++i)
		{
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); ++j)
			{
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
			}
		}
		return true;
	}
};

//11.11 There are N gas stations along a circular route, where the amount of gas at station i is gas[i].You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station(i + 1).
//You begin the journey with an empty tank at one of the gas stations. Return the starting gas station’s index if you can travel around the circuit once, otherwise return -1. Note: The solution is guaranteed to be unique.
// 时间复杂度O(n)，空间复杂度O(1),设置两个变量，sum 判断当前的指针的有效性；total 则判断整个数组是否有解，有就返回通过sum 得到的下标，没有则返回 - 1。
int runCircle(vector<int> &gas, vector<int> &cost)
{
	int total = 0, sum = 0, index = -1;
	for (int i = 0; i < gas.size(); ++i)
	{
		sum += gas[i] - cost[i];
		total += gas[i] - cost[i];
		if (sum < 0)
		{
			index = i;
			sum = 0;
		}
	}
	return total >= 0 ? index + 1 : -1;
}

//11.12 There are N children, Each child has a rating value.You are giving candies according to 1.Each child must have at least one candy.
//2. Children with a higher rating get more candies than their neighbors. What is the minimum candies you must give ?
int candy(vector<int> &rate)
{
	int n = rate.size();
	vector<int> give(n);
	// 左右各扫描一遍
	for (int i = 1, j = 1; i < n; ++i)
	{
		if (rate[i] > rate[i - 1])
			give[i] = max(j++, give[i]);
		else
			j = 1;
	}
	for (int i = n - 2, j = 1; i >= 0; --i)
	{
		if (rate[i] > rate[i + 1])
			give[i] = max(j++, give[i]);
		else
			j = 1;
	}
	// 初始值为n，因为每个小朋友至少一颗糖
	return accumulate(give.begin(), give.end(), n);//accumulate(&give[0], &give[0] + n, n);
}

//11.13 a. Buy and Sell Stock to get Maximize Profit, can do many times.
struct Income
{
	int buy;
	int sell;
};
void StockBuySell(int price[], int n)
{
	if (n < 2)
		return;
	Income *sol = new Income[n / 2 + 1];
	if (sol == NULL)
		return;
	int i = 0, count = 0;
	while (i < n - 1)
	{
		while (i < n - 1 && price[i] >= price[i + 1])
			++i;
		if (i == n - 1)
			break;
		sol[count].buy = i++;
		while (i < n && price[i] >= price[i - 1])
			++i;
		sol[count++].sell = i - 1;
	}
	if (count == 0)
		cout << "no profit" << endl;
	else
	{
		for (i = 0; i<count; ++i)
			printf("buy at %d day, sell at %d day.\n", sol[i].buy, sol[i].sell);
	}
	delete[] sol;
	sol = NULL;
	return;
}
// better 时间复杂度O(n)，空间复杂度O(1)
int maxProfit(vector<int> &price)
{
	if (price.size() < 2)
		return 0;
	int profit = 0, mini = price[0];
	for (int i = 1; i < price.size(); ++i)
	{
		if (price[i] > price[i - 1])
			profit += price[i] - price[i - 1];
	}
	return profit;
}

//b. Buy and Sell Stock to get Maximize Profit, can do only 1 times.
int StockBuySell(int a[], int n)
{
	if (n < 2)
		return 0;
	int buy = 0, sell = 0;
	int maxdiff = a[1] - a[0];
	int min = 0, minval = a[0];
	for (int i = 1; i<n; ++i)
	{
		if ((a[i] - minval) > maxdiff)
		{
			maxdiff = a[i] - minval;
			sell = i;
			buy = min;
		}
		if (a[i] < minval)
		{
			minval = a[i];
			min = i;
		}
	}
	if (maxdiff <= 0)
		cout << "no profit" << endl;
	else
		printf("buy at %d day, sell at %d day, profit is %d.\n", buy, sell, maxdiff);
	return maxdiff;
}
int StockBuySell(int a[], int n)
{
	if (n < 2)
		return 0;
	int buy = 0, sell = 0;
	int diff = a[1] - a[0];
	int cursum = diff;
	int maxsum = cursum;
	for (int i = 1; i<n - 1; ++i)
	{
		diff = a[i + 1] - a[i];
		if (cursum > 0)
			cursum += diff;
		else
			cursum = diff;
		if (cursum > maxsum)
			maxsum = cursum;
	}
	return maxsum;
}
//better 时间复杂度O(n)，空间复杂度O(1)
int maxProfit(vector<int> &price)
{
	if (price.size() < 2)
		return 0;
	int profit = 0;
	int mini = price[0];
	for (int i = 1; i < price.size(); ++i)
	{
		profit = max(profit, price[i] - mini);
		mini = min(mini, price[i]);
	}
	return profit;
}

//c. You may complete at most two transactions. 允许在一天内买进又卖出，相当于不交易，因为题目的规定是最多两次，而不是一定要两次。
//时间复杂度O(n)，空间复杂度O(n), 设状态f(i)，表示区间[0,i](0<=i<=n-1) 的最大利润，状态g(i)，表示区间[i,n-1](0<=i<=n-1)的最大利润，则最终答案为max{f(i) + g(i)},(0<=i<=n-1)
int maxProfit(vector<int> &price)
{
	if (price.size() < 2)
		return 0;
	const int n = price.size();
	vector<int> f(n, 0), g(n, 0);
	for (int i = 1, mini = price[0]; i < n; ++i)
	{
		mini = min(mini, price[i]);
		f[i] = max(f[i - 1], price[i] - mini);
	}
	for (int i = n - 2, peak = price[n - 1]; i >= 0; --i)
	{
		peak = max(peak, price[i]);
		g[i] = max(g[i], peak - price[i]);
	}
	int profit = 0;
	for (int i = 0; i < n; ++i)
		profit = max(profit, f[i] + g[i]);
	return profit;
}

//11.14 a. Given n non - negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
//For example, Given[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], return 6.
//对于每个柱子，找到其左右两边最高的柱子，该柱子能容纳的面积就是min(max_left, max_right) - height。所以，
//时间复杂度O(n)，空间复杂度O(n) 1. 从左往右扫描一遍，对于每个柱子，求取左边最大值；2. 从右往左扫描一遍，对于每个柱子，求最大右值,3. 再扫描一遍，把每个柱子的面积并累加。
int trap(int a[], int n)
{
	int *max_left = new int[n];
	int *max_right = new int[n];
	memset(max_left, 0, sizeof(int)*n);
	memset(max_right, 0, sizeof(int)*n);
	for (int i = 1; i < n; ++i)
	{
		max_left[i] = max(max_left[i - 1], a[i - 1]);
		max_right[n - 1 - i] = max(max_right[n - i], a[n - i]);
	}
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		int height = min(max_left[i], max_right[i]);
		if (height > a[i])
			sum += height - a[i];
	}
	delete[] max_left;
	delete[] max_right;
	return sum;
}
//时间复杂度O(n)，空间复杂度O(1), 1. 扫描一遍，找到最高的柱子，这个柱子将数组分为两半； 2. 处理左边一半；3. 处理右边一半。
int trap(int a[], int n)
{
	int highest = 0;//最高的柱子，将数组分为两半
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > a[highest])
			highest = i;
	}
	int sum = 0;
	for (int i = 0, peak = 0; i < highest; ++i)
	{
		if (a[i] > peak)
			peak = a[i];
		else
			sum += peak - a[i];
	}
	for (int i = n - 1, peak = 0, i > highest; --i)
	{
		if (a[i] > peak)
			peak = a[i];
		else
			sum += peak - a[i];
	}
	return sum;
}

//b. Given n non-negative integers a1, a2 ... an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line 
//i is at(i, ai) and(i, 0).Find two lines, which together with x - axis forms a container, such that the container contains the most water.时间复杂度O(n)，空间复杂度O(1)
int maxArea(vector<int> &height)
{
	int start = 0;
	int end = height.size() - 1;
	int result = INT_MIN;
	while (start < end)
	{
		int area = min(height[end], height[start]) * (end - start);
		result = max(result, area);
		if (height[start] <= height[end])
			++start;
		else
			--end;
	}
	return result;
}

//11.15 Given n positive integers representing the histogram’s bar height where the width of each bar is 1, find the area of largest rectangle in the histogram
//Given height = [2,1,5,6,2,3], return 10. 时间复杂度O(n)，空间复杂度O(n)
//可以维护一个递增的栈，每次比较栈顶与当前元素。如果当前元素小于栈顶元素， 则入栈，否则合并现有栈，直至栈顶元素小于当前元素。结尾时入栈元素0，重复合并一次。
int lra(vector<int> &height)
{
	stack<int> si;
	height.push_back(0);
	int res = 0, tmp = 0;
	for (int i = 0; i < height.size();)
	{
		if (si.empty() || height[i] > height[si.top()])
			si.push(i++);
		else
		{
			tmp = si.top();
			si.pop();
			res = max(res, height[tmp] * (si.empty() ? i : i - si.top() - 1));
		}
	}
	return res;
}

//11.16 You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps.In how many distinct ways can you climb to the top ?
//设f(n) 表示爬n 阶楼梯的不同方法数，为了爬到第n 阶楼梯，有两个选择：• 从第n - 1 阶前进1 步； • 从第n - 2  阶前进2 步； 有f(n) = f(n - 1) + f(n - 2)。这是一个斐波那契数列
//迭代，时间复杂度O(n)，空间复杂度O(1)
int climb(int n)
{
	assert(n > 0);
	int pre = 0, cur = 1, tmp = 0;
	for (int i = 0; i < n; ++i)
	{
		tmp = cur;
		cur += pre;
		pre = tmp;
	}
	return cur;
}
//数学公式，时间复杂度O(1)，空间复杂度O(1)
int climbstair(int n)
{
	double s = sqrt(5);
	return floor((pow((1 + s) / 2, n) - pow((1 - s) / 2, n)) / s);
}

//11.17 Write an algorithm to print all ways of arranging eight queens on a chess board so that none of them share the same row, column or diagonal.
//经典的八皇后问题，即在一个8*8的棋盘上放8个皇后，使得这8个皇后无法互相攻击( 任意2个皇后不能处于同一行，同一列或是对角线上)，输出所有可能的摆放情况。
//如果使用暴力法，每个格子都去考虑放皇后与否，一共有264 种可能,由于皇后们是不能放在同一行的， 所以我们可以去掉“行”这个因素
//我们用一个一维数组来表示相应行对应的列，比如c[i]=j表示， 第i行的皇后放在第j列. 同列：c[r]==c[j]; 同对角线有两种可能，即主对角线方向和副对角线方向。
//主对角线方向满足，行之差等于列之差：r-j==c[r]-c[j]; 副对角线方向满足， 行之差等于列之差的相反数：r-j==c[j]-c[r]。 只有满足了当前皇后和前面所有的皇后都不会互相攻击的时候，才能进入下一级递归
void print8Queen(int arr[], int n)
{
	ofstream fout("8Queen.txt", ios::app);
	for (int i = 0; i<n; ++i)
	{
		for (int j = 0; j<n; ++j)
		{
			if (j == arr[i])
				fout << "1 ";
			else
				fout << "0 ";
		}
		fout << endl;
	}
	fout << endl;
	fout.close();
}
int eightQueen(int arr[], int n, int row)//eightQueen(arr[8], 8, 0);
{
	if (arr == NULL || n < 1 || row < 0)
		return -1;
	static int cnt = 0;
	if (row == n)
	{
		print8Queen(arr, n);
		return ++cnt;
	}
	for (int i = 0; i<n; ++i)//当前皇后赋值
	{
		arr[row] = i;
		bool ok = true;
		for (int j = 0; j<row; ++j)//check if 当前皇后和前面所有的皇后都不会互相攻击
		{
			if (arr[row] == arr[j] || row - j == arr[row] - arr[j] || row - j == arr[j] - arr[row])
			{
				ok = false;
				break;
			}
		}
		if (ok)
			eightQueen(arr, n, row + 1);
	}
	return cnt;
}
//深搜+剪枝, 时间复杂度O(n!)，空间复杂度O(n)
class Solution
{
public:
	vector<vector<string>> nQueens(int n)
	{
		column = vector<int>(n, 0);
		mainDiag = vector<int>(2 * n, 0);
		antiDiag = vector<int>(2 * n, 0);
		vector<vector<string>> result;
		vector<int> col(n, 0);// C[i] 表示第i 行皇后所在的列编号
		dfs(col, result, 0);
		return result;
	}
private:
	// 这三个变量用于剪枝
	vector<int> column;// 表示已经放置的皇后占据了哪些列
	vector<int> mainDiag;// 表示已经放置的皇后占据了哪些主对角线
	vector<int> antiDiag;// 表示已经放置的皇后占据了哪些副对角线
	int count;// 解的个数

	void dfs(vector<int> &c, vector<vector<string>> &result, int row)
	{
		int n = c.size();
		if (row == n)
		{
			// 终止条件，也是收敛条件，意味着找到了一个可行解
			vector<string> solution;
			for (int i = 0; i < n; ++i)
			{
				string s(n, '.');
				for (int j = 0; j < n; ++j)
				{
					if (j == c[i])
						s[j] = 'Q';
				}
				solution.push_back(s);
			}
			result.push_back(solution);
			++count;
			return;
		}
		for (int j = 0; j < n; ++j)
		{
			// 扩展状态，一列一列的试
			bool ok = column[j] == 0 && mainDiag[row + j] == 0 && antiDiag[row - j + n] == 0;
			if (!ok)
				continue;// 剪枝：如果合法，继续递归
			// 执行扩展动作
			c[row] = j;
			column[j] = mainDiag[row + j] = antiDiag[row - j + n] = 1;
			dfs(c, result, row + 1);
			// 撤销动作
			column[j] = mainDiag[row + j] = antiDiag[row - j + n] = 0;
		}
	}
};