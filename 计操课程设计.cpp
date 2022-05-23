//LRU�㷨 
//���ݽṹ��ʹ�� �� ��ϣ���� 

//˫������ ��ϣ��
//find()�Ҹý����Ƿ��Ѿ��������� ����Ǿ͸�������(��¼��ǰ�ڵ�  ɾȥ�ڵ�  ͷ�巨�ٲ���ڵ�) 
//���Ǿ�ɾ��ʹ�ô������ٵĽ���(���������˵Ľڵ�)�����ý����������� 

//FIFO�㷨
//���ݽṹ��ʹ�� :  ����
//����ģ�������ȳ���������������Ѵ��ڽ��̾Ͳ����в�����������г��� ��Ӳ��� ��STL��queue�޷�ʹ�õ���������
//���Բ���ֱ��ʹ��queue  ������Ҫ�����ֶ�������ģ����еĻ��� Ȼ������������ 

 
//��������:
//1
//����飺4 
//1 1  2 2  3 3  4 6  5 4  6 7  3 3  2 2  1 1  5 4  6 7  7 5  4 6  7 5  2 2  1 1
//ȱҳ����Ϊ10�� ȱҳ��Ϊ0.875

//2
//����飺4
//1 2 3 3 4 6 3
//ȱҳ����Ϊ5��  ȱҳ��Ϊ0.714 
#include<iostream>
#include<algorithm>
#include<map>
//#include<queue>
using namespace std;
int m, t = 1;//m : �������Ŀ t : FIFO�м��� 

struct Node{
	int val, key;//��ֵ �� 
	Node *pre, *next;//ǰ�� ��� 
	Node(int v, int k) : val(v), key(k), pre(NULL), next(NULL){}//���캯�� 
};

typedef map<int, Node*>::iterator Auto;//���������ڱ�����ϣ�� 

class FIFO{
	public:
//		queue<int> q;
		int num, res, tot, cnt, f;//res : ȱҳ���� tot : �ܽ����� 
		int ub[200] = {0};//������� 
		
		FIFO(int size)//��ʼ�� 
		{
			num = size;
			res = tot = cnt = f = 0;
		}
		
		bool Check(int v)//��ѯ�Ƿ��Ѿ�����v 
		{
			for(int i = cnt - 1; i >= (cnt - m >= 0 ? cnt - m : 0); i --)
			if(ub[i] == v) return true;
			return false;
		}
		
		void Set(int v)//������� 
		{
			if(Check(v)) {f ++; return;}//�ж��Ƿ��Ѿ��д˽��� f��ƫ���� 

			ub[cnt ++] = v;//�������������� 

//			if(q.size() > num) q.pop();
			
//			q.push(v);
			res ++;//ȱҳ���� 
		}
		
		void Way()//��ӡ��� 
		{
			int V; 
			cout << "���������ֵ, ��0����\n";
		
			while(cin >> V, V)
			{	
				Set(V);
				tot ++;//�ܹ������� 
				
				if(t ++ - f >= m)//�������װ����ʼ���� 
				{
					cout << "��" << t - m - 1 << "�� �� " << endl; 
					for(int j = t - m - f > 0 ? t - m - 1 - f : 0; j < cnt; j ++)
						cout << ub[j] << ' ';
					cout << endl;
				}
			}
			cout << "ȱҳ���� : " << res << endl;
			printf("ȱҳ�� : %.2lf%\n", (res + 0.0) / tot * 100);
		}
};

class LRU{
	
	public:	
		int num, res, tot;//�������Ŀ 
		Node *head, *tail;//����ͷ�ڵ�  β�ڵ� 
		map<int, Node*> p;//����һ����ϣ�� 
		
		LRU(int size)//���캯����ʼ�� 
		{
			num = size;
			head = tail = NULL;
			res = tot = 0;
		}
		
		void Del_list(Node *node)//˫�������ɾ���ڵ� 
		{
			if(node -> pre != NULL) node -> pre -> next = node -> next;
			else head = node -> next;
			
			if(node -> next != NULL) node -> next -> pre = node -> pre;
			else tail = node -> pre;
		}
	
		void Add_list(Node *node)//ͷ�巨����ڵ� 
		{
			node -> next = head;
			node -> pre = NULL;
		
			if(head != NULL) head -> pre = node;
			head = node;
		
			if(tail == NULL) tail = head;
		}
		
		int Get_val(int k)//��ȡ��ǰ��ֵ����Ӧ��ֵ 
		{
			Auto it = p.find(k);
			if(it != p.end())//����ҵ��˼�ֵ 
			{
				Node *node = it -> second;//��¼��ֵ���ڽڵ� 
				Del_list(node);//ɾ���ڵ� 
				Add_list(node);//ͷ����������ǰ�� 
				return node -> val;//���������ֵ��ָ�����ֵ 
			}
			return -1;//δ�ҵ������ֵ 
		}
		
		void Insert(int v, int k)//����Ԫ�� 
		{
			Auto it = p.find(k);
			
			if(it != p.end())//���䲻�����һ���ڵ�  ����ǰֵ�Ѿ����� 
			{
				Node *node; 
				for(Auto a = p.begin(); a != p.end(); a ++)//�������Ľڵ��ڹ�ϣ�����Ѿ����� ���¼�ڵ� 
		     	if(a -> second -> val == v) {node = a -> second;}
			 	
				node -> val = v;
				Del_list(node); //ɾ���ҵ��Ľڵ� 
				Add_list(node);//���ڵ�����ͷ 
			}
			
			else//��ǰֵ������   
			{
				Node *node = new Node(v, k);//����һ���¿ռ� 
				if(p.size() >= num) //��map�е�ֵ���������ǵ������ 
				{
					Auto it = p.find(tail -> key);//�ҵ����һ���ڵ� 
					Del_list(tail);//�ӱ����Ƴ� 
					p.erase(it);//���ڴ���ɾȥ 
				}
				Add_list(node);//��������Ľ��� 
				p[k] = node;//�ڵ��������ϣ���� 
				res ++;//��¼ȱҳ���� 
			}
		}

		void Way()
		{
			int i, y;//i : �ڼ��β���  y : switchѡ����� 
			i = y = 1; 
	
			while(y != -1)
			{
				cout << "1 : ��ѯ��ǰ�������еĽ���\n2 : ��ӽ���\n-1 : �˳��㷨����\n";
				cin >> y;
				int V, K;//V : ������ֵ  K : ��ֵ 
				switch(y)
				{
					case 1 : cout << "������һ����ֵ,��0��������\n";
					while(cin >> y, y)
					Get_val(y) == -1 ?
					cout << "���ڽ�����" << endl : cout << "�����±�Ϊ" << y << "��ֵΪ: " << Get_val(y) << endl; break;
			
					case 2 : cout << "��������̵�������ֵ(������ֵ����һһ��Ӧ����1 4��ʾ��ֵΪ1��ֵΪ4)����0 0��������\n";
					while(cin >> K >> V ,K ,V)
					{	
						Insert(V, K);
						tot ++;//�ܹ������� 
				
						if(i ++ >= m)
						{
							cout << "��" << i - m << "�� �� " << endl; 
							for(Node* it = head; it != tail -> next; it = it -> next)
							cout << it -> val << ' ';
							cout << endl;
						}
					}
					cout << "ȱҳ���� : " << res - m << endl;
					printf("ȱҳ�� : %.2lf%\n", (res + 0.0) / tot * 100);
					break;
			
					case -1 : cout << "�����������\n"; break;
					default : cout << "��������ȷ��ֵ\n"; break;
				}
			}
		}
};

int main()
{
	int T;//ѡ���㷨 
	cout << "��������������" << endl;
	cin >> m;
	cout << "1:LRU\n2:FIFO\n";
	cin >> T;
	
	if(T == 1) {LRU *P = new LRU(m); P -> Way();}
	else if(T == 2) {FIFO *F = new FIFO(m); F -> Way();}
	else cout << "��������ȷ��ֵ\n";
	
	return 0;
}
