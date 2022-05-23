//测试数据：
//6
//4 7 9 3 5 6 
// 打印  中序遍历 3 4 5 6 7 9

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cassert>
using namespace std;
#define maxn 100010
int a[maxn];
typedef struct Node{
	int data;
	struct Node *lc;
	struct Node *rc;
}Tr;
typedef Tr *Tree;
Tree rt;
Tree Y=NULL;
Tree qq=NULL;

Tree Find(Tree rt,int val){
	if(!rt) return 0;
	else{
	if(rt->data==val)
	return rt;
	else if(val<rt->data)
	Find(rt->lc,val);
	else if(val>rt->data)
	Find(rt->rc,val);
   }
}


void insert(Tree &rt,int val){
	if(!rt){
		rt=(Tree)malloc(sizeof(Tr));
		rt->data=val; 
		rt->lc=rt->rc=NULL;
		return;
		}
	if(val==rt->data) {cout<<"插入失败"; return;}
	else if(val<rt->data) {
	insert(rt->lc,val);}//cout<<rt->data;}
	else {//cout<<rt->data;
	insert(rt->rc,val); }
}

Tree Bin_build(int a[],int k){
	Tree rt=NULL;
	for(int i=0;i<k;i++)
	insert(rt,a[i]);
	return rt;
}

bool del(Tree rt,int val,Tree key){
	if(!rt) {cout<<"此点为空";return false;}
	
	else if(Find(rt,val)){ 
	    if(rt->data==val) Y=rt;//Y是记录H的双亲节点的位置 
       else
		while(val!=rt->data){
       	Y=rt;
       	if(val<rt->data)
       	rt=rt->lc;
       	else rt=rt->rc;
		}
		
	    Tree H=rt;
		
		if(rt->rc==NULL&&rt->lc==NULL)
		{
		if(Y->data<val) Y->rc=NULL;
		else if(Y->data>val) Y->lc=NULL;
		
		free(rt);return true;}//待删除结点无左右子树 
	
	
	
		else if(rt->lc!=NULL&&rt->rc!=NULL){//待删除子树左右子树都有 
	    //Tree p=rt;
	    
		Tree I,U=rt;//U是待删除结点的中序遍历下的前驱的前驱  
		//cout<<"-"<<key->data;cout<<rt->data;
		while(rt->data!=key->data){//待删除结点的位置 
				I=rt; 
				if(rt->lc!=NULL) rt=rt->lc;
				else {
					rt=I;rt=rt->rc;}
		}
		//cout<<"-"<<I->data;cout<<"-"<<Y->data;cout<<U->data;//5  6 7
		if(key->data<I->data) I->lc=NULL;
		else if(key->data>I->data) I->rc=NULL;
		U->data =key->data ;
		free(key);
		return true;



       
	}
		else {//待删除子树仅有一个子树 
		if(H->lc==NULL&&H->rc!=NULL){
		
		if(H->data<Y->data)
		{Y->lc=H->rc;H=H->rc;}
		else if(H->data>Y->data)
		while(H->rc!=NULL)
		{Y->rc=H->rc;H=H->rc;Y=Y->rc;}//7 9
		//cout<<H->data;cout<<"--"<<Y->data;//19 7    99  9
		free(H->rc);return true;
		} 
		
		else if(H->rc==NULL&&H->lc!=NULL){
		
		if(H->data>Y->data)
		{Y->rc=H->lc;H=H->lc;}
		else if(H->data<Y->data)
		while(H->lc!=NULL)
		{Y->lc=H->lc;H=H->lc;Y=Y->lc;}
		free(H->lc);return true;
		}		
		
		}
	}
	else cout<<"没有此值可删除"<<endl; 
}

void zxbl(Tree &rt){//树的中序遍历 
	if(rt){//cout<<"hello";
		zxbl(rt->lc);
		cout<<rt->data<<' ';
		zxbl(rt->rc);
	}
}

Tree zxbl_fdg(Tree &rt,int val){
	Tree q;
       int top,b;
       Tree arr[maxn];
       top=0; q=rt; b=0;
       while(b!=1){
       	if(q!=NULL){
       		top++;
       		if(top>maxn){
       			b=1;
				}
				else {arr[top]=q;
				q=q->lc;}}
       	else if(!top) b=1;
       	else{
				q=arr[top];
				if(val==q->data){
       		//qq=u;
				return arr[top+1];//求删除结点时左右子树都存在情况下的替换原结点的值（中序遍历下 待删除结点的前驱） 
				}
				top--;
       		
       	//	cout<<"wdt"<<q->data<<"wu";
				q=q->rc;
			}
		}
}
int main()
{
	int n;
	cout<<"请输入数据数量"<<endl; 
	cin>>n;
	cout<<"输入所有数据"<<endl;
	for(int i=0;i<n;i++)
	cin>>a[i];
	cout<<"二叉树为："<<endl; 
	rt=Bin_build(a,n);
	//zxbl(Bin_build(a,n));
	zxbl(rt);
	cout<<endl; 
	cout<<"请选择："<<endl;
	cout<<"1.查找"<<endl;
	cout<<"2.插入"<<endl;
	cout<<"3.删除"<<endl;
	int t,val;
	while(cin>>t){
	if(t==1){
	    cout<<"请输入查找的数"<<endl;
	    cin>>val;
	    if(Find(rt,val)) cout<<"查找成功"<<endl;
	    else cout<<"查找失败"<<endl;
	}
	
	else if(t==2){
		cout<<"请输入插入的值"<<endl;
		cin>>val;
		insert(rt,val);
       zxbl(rt);
		cout<<endl;
		}

	else if(t==3){
		cout<<"请输入你要删除的值"<<endl;
		cin>>val;
		Tree key=zxbl_fdg(rt,val);
		if(del(rt,val,key))
		cout<<"删除成功"<<endl;
		//cout<<"?"<<rt->rc->data;
		zxbl(rt);
		cout<<endl; 
	}
	else cout<<"请输入正确的值";} 
}

c:
// #include<iostream>
// #include<stdio.h>
// #include<stdlib.h>
// #define maxn 100010
// int a[maxn];
// typedef struct Node{
// 	int data;
// 	struct Node *lc;
// 	struct Node *rc;
// }Tr;
// typedef Tr *Tree;
// Tree rt;
// Tree Y=NULL;
// Tree qq=NULL;

// Tree Find(Tree rt,int val){
// 	if(!rt) return 0;
// 	else{
// 	if(rt->data==val)
// 	return rt;
// 	else if(val<rt->data)
// 	Find(rt->lc,val);
// 	else if(val>rt->data)
// 	Find(rt->rc,val);
//     }
// }


// void insert(Tree &rt,int val){
// 	if(!rt){
// 		rt=(Tree)malloc(sizeof(Tr));
// 		rt->data=val; 
// 		rt->lc=rt->rc=NULL;
// 		return;
// 		}
// 	if(val==rt->data) {printf("插入失败\n"); return;}
// 	else if(val<rt->data) {
// 	insert(rt->lc,val);}
// 	else {
// 	insert(rt->rc,val); }
// }

// Tree Bin_build(int a[],int k){
// 	Tree rt=NULL;
// 	for(int i=0;i<k;i++)
// 	insert(rt,a[i]);
// 	return rt;
// }

// bool del(Tree rt,int val,Tree key){
// 	if(!rt) {printf("此点为空\n");return false;}
	
// 	else if(Find(rt,val)){ 
// 	    if(rt->data==val) Y=rt;//Y是记录H的双亲节点的位置 
//         else
// 		while(val!=rt->data){
//         	Y=rt;
//         	if(val<rt->data)
//         	rt=rt->lc;
//         	else rt=rt->rc;
// 		}
		
// 	    Tree H=rt;
		
// 		if(rt->rc==NULL&&rt->lc==NULL)
// 		{
// 		if(Y->data<val) Y->rc=NULL;
// 		else if(Y->data>val) Y->lc=NULL;
		
// 		free(rt);return true;}//待删除结点无左右子树 
	
	
	
// 		else if(rt->lc!=NULL&&rt->rc!=NULL){//待删除子树左右子树都有 
// 	    //Tree p=rt;
	    
// 		Tree I,U=rt;//U是待删除结点的中序遍历下的前驱的前驱  
// 		//cout<<"-"<<key->data;cout<<rt->data;
// 		while(rt->data!=key->data){//待删除结点的位置 
// 				I=rt; 
// 				if(rt->lc!=NULL) rt=rt->lc;
// 				else {
// 					rt=I;rt=rt->rc;}
// 		}
// 		//cout<<"-"<<I->data;cout<<"-"<<Y->data;cout<<U->data;//5  6 7
// 		if(key->data<I->data) I->lc=NULL;
// 		else if(key->data>I->data) I->rc=NULL;
// 		U->data =key->data ;
// 		free(key);
// 		return true;



        
// 	}
// 		else {
// 		if(H->lc==NULL&&H->rc!=NULL){
// 		if(H->data==Y->data) {rt=H->rc;H=NULL;free(Y);}
// 		if(H->data<Y->data)
// 		{Y->lc=H->rc;H=H->rc;}
// 		else if(H->data>Y->data)
// 		while(H->rc!=NULL&&H->data!=Y->data)
// 		{Y->rc=H->rc;H=H->rc;Y=Y->rc;}
// 		free(H->rc);return true;
// 		} 
		
// 		else if(H->rc==NULL&&H->lc!=NULL){
// 		if(H->data==Y->data) {rt=Y->lc;free(Y);}
// 		if(H->data>Y->data)
// 		{Y->rc=H->lc;H=H->lc;}
// 		else if(H->data<Y->data)
// 		while(H->lc!=NULL)
// 		{Y->lc=H->lc;H=H->lc;Y=Y->lc;}
// 		free(H->lc);return true;
// 		}		
		
// 		}
// 	}
// 	else {printf("没有此值可删除\n");return false;} 
// }

// void zxbl(Tree &rt){//树的中序遍历 
// 	if(rt){
// 		zxbl(rt->lc);
// 		printf("%d ",rt->data);
// 		zxbl(rt->rc);
// 	}
// }

// Tree zxbl_fdg(Tree &rt,int val){
// 	Tree q;
//         int top,b;
//         Tree arr[maxn];
//         top=0; q=rt; b=0;
//         while(b!=1){
//         	if(q!=NULL){
//         		top++;
//         		if(top>maxn){
//         			b=1;
// 				}
// 				else {arr[top]=q;
// 				q=q->lc;}}
//         	else if(!top) b=1;
//         	else{
// 				q=arr[top];
// 				if(val==q->data){
// 				return arr[top+1];//求删除结点时左右子树都存在情况下的替换原结点的值（中序遍历下 待删除结点的前驱） 
// 				}
// 				top--;
// 				q=q->rc;
// 			}
// 		}
// }
// int main()
// {
// 	int n;
// 	printf("请输入数据数量\n"); 
// 	scanf("%d",&n);
// 	printf("请输入所有数据\n");
// 	for(int i=0;i<n;i++)
// 	scanf("%d",&a[i]);
// 	printf("二叉树为：\n"); 
// 	rt=Bin_build(a,n);
// 	zxbl(rt);
// 	printf("\n");
// 	printf("1.查找\n");
// 	printf("2.插入\n");
// 	printf("3.删除\n");
// 	printf("0.退出\n");
// 	int t,val;
// 	while(scanf("%d",&t)){
// 	if(t==0) break;
// 	if(t==1){
// 	    printf("请输入查找的数\n");
// 	    scanf("%d",&val);
// 	    if(Find(rt,val)) printf("查找成功\n");
// 	    else printf("查找失败\n");
// 	}
	
// 	else if(t==2){
// 		printf("请输入插入的值\n"); 
// 		scanf("%d",&val);
// 		insert(rt,val);
//         zxbl(rt);
// 		printf("\n");
// 		}

// 	else if(t==3){
// 		printf("请输入你要删除的值\n");
// 		scanf("%d",&val);
// 		Tree key=zxbl_fdg(rt,val);
// 		if(del(rt,val,key))
// 		printf("删除成功\n");
// 		zxbl(rt);
// 		printf("\n");
// 	}
// 	else printf("请输入正确的值");
// 	} 
// }


