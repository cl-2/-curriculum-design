//LRU算法:最近最久未使用算法 
//数据结构的使用 ： 哈希链表 
//双向链表 哈希表
//find()找该进程是否已经在链表中 如果是就更新链表(记录当前节点  删去节点  头插法再插入节点) 
//不是就删除使用次数最少的进程(即链表最后端的节点)，将该进程添入链表 

//FIFO算法:先进先出页面置换算法 
//数据结构的使用 :  队列
//队列模拟先入先出操作，如果队列已存在进程就不进行操作，否则进行出队 入队操作 ，STL中queue无法使用迭代器遍历
//所以不能直接使用queue  而是需要我们手动用数组模拟队列的机制 然后遍历将其输出 

//OPT算法:最佳置换算法 
//数据结构的使用 :  线性表，首先我们需要准备两个数组如a与b，a数组存放所有输入的值，b数组模拟物理块大小。
//在向b中插入页面时， 
//如果页面已经存在，就不用进行操作跳过即可，
//如果页面不存在，我们就需要从a数组中判断当前物理块中找到  之后再未使用的页面  是哪一个
//(我们可以遍历a数组如果a数组中存在和物理块中页面相同的值，就进行标记，如果最后都没有标记，就表面页面在之后并未被使用过) 
//否则我们就要找到  最长时间未使用的页面  是哪一个(我们这里可以利用一个变量来记录下标,如果之后的页面在物理块中已经出现，就
//  记录其下标，并进行标记，之后再出现此页面就直接跳过，这样就能找到最长时间未使用的页面)，然后就可以将这个页面所在的物理块中的下标
//所映射的页面进行删除，然后再添入新的页面。 

 
//测试用例:
//1
//物理块：4 
//1 1  2 2  3 3  4 6  5 4  6 7  3 3  2 2  1 1  5 4  6 7  (单看页面号为 1 2 3 6 4 7 3 2 1 4 7) 
//缺页次数为10， 缺页率为90.9%

//2
//物理块：4
//1 2 3 3 4 6 3
//缺页次数为5，  缺页率为71.4% 

//3
//物理块：3
//12
//1 2 3 4 1 2 5 1 2 3 4 5
//缺页次数为8,   缺页率为66.7% 


#include<iostream>
#include<algorithm>
#include<map>//哈希表进行键值和数值的映射 
#include<cstring>
#include<vector>//不定长数组 
using namespace std;
int m;//m : 物理块数目

struct Node{
	int val, key;//数值 键 
	Node *pre, *next;//前驱 后继 
	Node(int v, int k) : val(v), key(k), pre(NULL), next(NULL){}//构造函数 
};

typedef map<int, Node*>::iterator Auto;//迭代器用于遍历哈希表 
typedef vector<int>::iterator AUTO;//迭代器遍历不定长数组 

class FIFO{
	public:
		int num, res, tot, cnt, f;//res : 缺页次数 tot : 总进程数 
		int ub[200];//存放数据 
		
		FIFO(int size)//初始化 
		{
			num = size;
			res = tot = cnt = f = 0;
			memset(ub, 0, sizeof ub);
		}
		
		bool Check(int v)//查询是否已经存在v 
		{
			for(int i = cnt - 1; i >= (cnt - m >= 0 ? cnt - m : 0); i --)
			if(ub[i] == v) return true;
			return false;
		}
		
		void Set(int v)//插入操作 
		{
			if(Check(v)) {f ++; return;}//判断是否已经有此进程 f是偏移量 

			ub[cnt ++] = v;//插入数据至数组 
			res ++;//缺页次数 
		}
		
		void Way()//打印结果 
		{
			int V, t = 0; //t : FIFO中计数  
			cout << "请输入进程值, 以0结束\n";
		
			while(cin >> V, V)
			{	
				Set(V);
				tot ++;//总共进程数 
				
				cout << "第" << ++ t << "次 ： " << endl; 
				for(int j = t - m - f > 0 ? t - m - f : 0; j < cnt; j ++)
					cout << ub[j] << ' ';
				cout << endl;
			}
			cout << "缺页次数 : " << res << endl;
			printf("缺页率 : %.2lf%\n", (res + 0.0) / tot * 100);
		}
};

class LRU{
	
	public:	
		int num, res, tot;//物理块数目 
		Node *head, *tail;//定义头节点  尾节点 
		map<int, Node*> p;//定义一个哈希表 
		
		LRU(int size)//构造函数初始化 
		{
			num = size;
			head = tail = NULL;
			res = tot = 0;
		}
		
		void Del_list(Node *node)//双向链表的删除节点 
		{
			if(node -> pre != NULL) node -> pre -> next = node -> next;
			else head = node -> next;
			
			if(node -> next != NULL) node -> next -> pre = node -> pre;
			else tail = node -> pre;
		}
	
		void Add_list(Node *node)//头插法插入节点 
		{
			node -> next = head;
			node -> pre = NULL;
		
			if(head != NULL) head -> pre = node;
			head = node;
		
			if(tail == NULL) tail = head;
		}
		
		int Get_val(int k)//获取当前键值所对应的值 
		{
			Auto it = p.find(k);
			if(it != p.end())//如果找到了键值 
			{
				Node *node = it -> second;//记录键值所在节点 
				Del_list(node);//删除节点 
				Add_list(node);//头插至链表最前面 
				return node -> val;//返回这个键值所指向的数值 
			}
			return -1;//未找到这个数值 
		}
		
		void Insert(int v, int k)//插入元素 
		{
			Auto it = p.find(k);
			
			if(it != p.end())//若其不是最后一个节点  若当前值已经存在 
			{
				Node *node; 
				for(Auto a = p.begin(); a != p.end(); a ++)//如果加入的节点在哈希表中已经存在 则记录节点 
		     	if(a -> second -> val == v) {node = a -> second;}
			 	
				node -> val = v;
				Del_list(node); //删除找到的节点 
				Add_list(node);//将节点放入表头 
			}
			
			else//当前值不存在   
			{
				Node *node = new Node(v, k);//开辟一个新空间 
				if(p.size() >= num) //若map中的值大于了我们的物理块 
				{
					Auto it = p.find(tail -> key);//找到最后一个节点 
					Del_list(tail);//从表中移除 
					p.erase(it);//从内存中删去 
					
				}
				Add_list(node);//添加新来的进程 
				p[k] = node;//节点添加至哈希表中
				res ++;//记录缺页次数 
			}
		}

		void Way()
		{
			int i, y;//i : 第几次操作  y : switch选择操作 
			i = y = 1; 
	
			while(y != -1)
			{
				cout << "1 : 查询当前索引表中的进程\n2 : 添加进程\n-1 : 退出算法程序\n";
				cin >> y;
				int V, K;//V : 进程数值  K : 键值 
				switch(y)
				{
					case 1 : cout << "请输入一个键值,以0结束输入\n";
					while(cin >> y, y)
					Get_val(y) == -1 ?
					cout << "不在进程中" << endl : cout << "索引下标为" << y << "的值为: " << Get_val(y) << endl; break;
			
					case 2 : cout << "请输入进程的索引和值(索引与值必须一一对应，如1 4表示键值为1，值为4)，以0 0结束输入\n";
					while(cin >> K >> V ,K ,V)
					{	
						Insert(V, K);
						tot ++;//总共进程数 
				
						if(i ++ >= m)
						{
							cout << "第" << i - m << "次 ： " << endl; 
							for(Node* it = head; it != tail -> next; it = it -> next)
							cout << it -> val << ' ';
							cout << endl;
						}
					}
					cout << "缺页次数 : " << res << endl;
					printf("缺页率 : %.2lf%\n", (res + 0.0) / tot * 100);
					break;
			
					case -1 : cout << "进程运行完毕\n"; break;
					default : cout << "请输入正确的值\n"; break;
				}
			}
		}
};

class OPT{
	public:
		vector<int> vec;//物理块中的数据 
		int arr[200];//记录输入的数据 
		int num, s;//num : 输入的数量, s : 页面总数量 
		bool st[200];//判断是否在后续数据中出现 
		int res, tot;
		
		OPT(int size){
			s = res = tot = 0;
			memset(arr, 0, sizeof arr);
			memset(st, false, sizeof st);
			num = size;
		}
		
		bool check(int v)//检查当前数值v是否在后续数据中出现 
		{
			for(AUTO it = vec.begin(); it != vec.end(); it ++)
			if(*it == v) return true;
			return false;
		}
		
		int get(int x) // 获取应该被替换的值的下标 
		{
			int pl = -1;
			for(int i = 0; i < s; i ++)//找到后续数据中出现的最不常用的数据下标 
			{
				if(check(arr[i]) && st[arr[i]] == false) 
				{
					st[arr[i]] = true;
					pl = max(i, pl);
				}
			}
			
			for(int i = 0; i < vec.size(); i ++)//找到后续数据中再未出现的数据的下标 
			if(st[vec[i]] == false) return i;//如果物理块中元素没出现过，就直接删除下标为i的值，并添加页面 
			else if(vec[i] == arr[pl]) return i;//否则就是元素在后续出现过， 我们找最远最久未使用的页面下标为i，进行替换 
			 
		}
		
		void in(int v, int i)//插入数据 
		{
			tot ++;
			if(check(v)) return;//如果已存在此页面  则跳过 
			else //否则插入 
			{
				res ++;
				if(vec.size() >= num)//如果插入的页面数大于等于物理块数目 
				{
					memset(st, false, sizeof st); 
					int t = get(i);
					vec.erase(t + vec.begin());//删除下标为t的值 
					vec.insert(t + vec.begin(), v);//在下标为t处插入 
				}
				else vec.push_back(v);//直接插入页面 
			}
		}
		
		void Way()
		{
			cout << "请输出页面数目及所有页面\n";
			cin >> s;
			for(int i = 0; i < s; i ++)
			cin >> arr[i];
			
			for(int i = 0; i < s; i ++)
			{
				in(arr[i], i);
				printf("第%d轮 : \n", i + 1);
				for(int j = 0; j < vec.size(); j ++)
					cout << vec[j] << ' ';
				cout << endl;
			}
			
			cout << "缺页次数 : " << res << endl;
			printf("缺页率 : %.2lf%\n", (res + 0.0) / tot * 100);
		}
};

int main()
{
	int T;//选择算法 
	cout << "请输入物理块个数" << endl;
	cin >> m;
	cout << "1:LRU\n2:FIFO\n3:OPT\n4:EXIT PROCEDURE\n";
	cin >> T;
	
	if(T == 1) {LRU *P = new LRU(m); P -> Way();}
	else if(T == 2) {FIFO *F = new FIFO(m); F -> Way();}
	else if(T == 3) {OPT *O = new OPT(m); O -> Way();}
	else if(T == 4) return 0;
	else cout << "请输入正确的值\n";
}
