//LRU算法 
//数据结构的使用 ： 哈希链表 

//双向链表 哈希表
//find()找该进程是否已经在链表中 如果是就更新链表(记录当前节点  删去节点  头插法再插入节点) 
//不是就删除使用次数最少的进程(即链表最后端的节点)，将该进程添入链表 

//FIFO算法
//数据结构的使用 :  队列
//队列模拟先入先出操作，如果队列已存在进程就不进行操作，否则进行出队 入队操作 ，STL中queue无法使用迭代器遍历
//所以不能直接使用queue  而是需要我们手动用数组模拟队列的机制 然后遍历将其输出 

 
//测试用例:
//1
//物理块：4 
//1 1  2 2  3 3  4 6  5 4  6 7  3 3  2 2  1 1  5 4  6 7  7 5  4 6  7 5  2 2  1 1
//缺页次数为10， 缺页率为0.875

//2
//物理块：4
//1 2 3 3 4 6 3
//缺页次数为5，  缺页率为0.714 
#include<iostream>
#include<algorithm>
#include<map>
//#include<queue>
using namespace std;
int m, t = 1;//m : 物理块数目 t : FIFO中计数 

struct Node{
	int val, key;//数值 键 
	Node *pre, *next;//前驱 后继 
	Node(int v, int k) : val(v), key(k), pre(NULL), next(NULL){}//构造函数 
};

typedef map<int, Node*>::iterator Auto;//迭代器用于遍历哈希表 

class FIFO{
	public:
//		queue<int> q;
		int num, res, tot, cnt, f;//res : 缺页次数 tot : 总进程数 
		int ub[200] = {0};//存放数据 
		
		FIFO(int size)//初始化 
		{
			num = size;
			res = tot = cnt = f = 0;
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

//			if(q.size() > num) q.pop();
			
//			q.push(v);
			res ++;//缺页次数 
		}
		
		void Way()//打印结果 
		{
			int V; 
			cout << "请输入进程值, 以0结束\n";
		
			while(cin >> V, V)
			{	
				Set(V);
				tot ++;//总共进程数 
				
				if(t ++ - f >= m)//从物理块装满后开始计数 
				{
					cout << "第" << t - m - 1 << "次 ： " << endl; 
					for(int j = t - m - f > 0 ? t - m - 1 - f : 0; j < cnt; j ++)
						cout << ub[j] << ' ';
					cout << endl;
				}
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
					cout << "缺页次数 : " << res - m << endl;
					printf("缺页率 : %.2lf%\n", (res + 0.0) / tot * 100);
					break;
			
					case -1 : cout << "进程运行完毕\n"; break;
					default : cout << "请输入正确的值\n"; break;
				}
			}
		}
};

int main()
{
	int T;//选择算法 
	cout << "请输入物理块个数" << endl;
	cin >> m;
	cout << "1:LRU\n2:FIFO\n";
	cin >> T;
	
	if(T == 1) {LRU *P = new LRU(m); P -> Way();}
	else if(T == 2) {FIFO *F = new FIFO(m); F -> Way();}
	else cout << "请输入正确的值\n";
	
	return 0;
}
