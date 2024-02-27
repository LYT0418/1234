#include<bits/stdc++.h>
using namespace std;
int best=0;//最优值 
int n,W;//物品数量 背包容量 
int bestx[1010];//最优解 
struct goods{
	int v;//物品价值 
	int w;//物品重量 
	int id;//物品序号 
	float temp;//性价比 
};
struct node{
	int level;//层数 
	int cw;//已有weight 
	int cv;//已有价值 
	float bound;//上界 
	int bestx[1010];//解向量 
	//以上界为优先级在优先队列存放节点 
	bool operator<(const node& a)const{
		return bound<a.bound;
	}
};
struct goods good[1010];
bool cmp(struct goods &a,struct goods &b){
	return a.temp>b.temp;
}
float bound(int k,int cv,int cw);
void knapsack(int &best);
int main(){
	scanf("%d %d",&n,&W);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&good[i].w,&good[i].v);
		good[i].id=i;
		good[i].temp=good[i].v*1.0/good[i].w;
	}	
	sort(good+1,good+n+1,cmp);//按性价比排序 
	knapsack(best);
	printf("%d\n",best);
	for(int i=1;i<n;i++) printf("%d ",bestx[i]);
	printf("%d",bestx[n]);
	return 0;
}
//计算上界 
float bound(int k,int cv,int cw){
	float b=cv;int c=cw;
	for(int i=k+1;i<=n;i++){
		if(c+good[i].w<=W){
			c=c+good[i].w;b=b+good[i].v;
		}else return b+1.0*(W-c)*good[i].v/good[i].w;
	}
	return b*1.0;	
}
void knapsack(int &best){
	priority_queue<node> p;//优先队列声明，大顶堆 
	node u,v;
	v.level=0;v.cv=0;v.cw=0;best=0;v.bound=bound(v.level,v.cv,v.cw);//初始化第一个节点 
	for(int i=0;i<=n;i++) v.bestx[i]=0;
	p.push(v);
	while(!p.empty()){
		v=p.top();
		p.pop();
		if(v.cv>=best) 
		for(int i=1;i<=n;i++){
			bestx[i]=v.bestx[i];
		}
		//到达叶子，停止扩展结点 
		if(v.level==n) {
		    //更新解向量 
			if(v.cv>=best){
			    best=v.cv;
			}
			continue;
		}
		v.bound=bound(v.level,v.cv,v.cw);
		if(v.bound>best){
			//生成左子树节点 
			u.level=v.level+1;
			u.cw=v.cw+good[u.level].w;
			u.cv=v.cv+good[u.level].v;
			u.bound=bound(u.level,u.cv,u.cw); 
			if(u.cw<=W&&u.cv>best) best=u.cv;//及时更新最优解，增加被剪枝节点，加快算法运行 
			//当满足weight约束时，将左子树节点加入优先队列 
			if(u.cw<=W){
				for(int i=0;i<=n;i++) u.bestx[i]=v.bestx[i];
				u.bestx[good[u.level].id]=1;
				p.push(u);
			}
			u.level=v.level+1;u.cw=v.cw;u.cv=v.cv;u.bound=bound(u.level,u.cv,u.cw);//生成右子树节点 
			//当上界大于best时，入队列 
			if(u.bound>best){
				for(int i=0;i<=n;i++) u.bestx[i]=v.bestx[i];
				u.bestx[good[u.level].id]=0;
				p.push(u);
			}
		}
	}
}
/*
5 100
77 22 29 50 99
92 22 87 46 90
8 200
79 58 86 11 28 62 15 68
83 14 54 79 72 52 48 62
10 300
95 75 23 73 50 22 6 57 89 98
89 59 19 43 100 72 44 16 7 64 
100 1000
88 
85 
59 
100 
94 64 79 75 18 38 47 11 56 12 96 54 23 6 19 31 30 32 21 31 
4 
30 
3 
12 
21 
60 
42 
42 
78 
6 
72 
25 
96 
21 
77 
36 
42 
20 
7 
46 
19 
24 
95 
3 
93 
73 
62 
91 
100 
58 
57 
3 
32 
5 
57 
50 
3 
88 
67 
97
24 
37 
41 
36 
98 
52 
75 
7 
57 
23 
55 
93 
4 
17 
5 
13 
46 
48 
28 
24 
70 
85 
48 
48 
55 
93 
6 
8 
12 
50 
95 
66 
92 
25 
80 
16 

100 1000
75 27
64 21
68 14
18 82
83 36
55 94
60 88
10 71
18 86
83 69
53 75
87 60
80 74
14 16
92 38
18 49
67 24
22 68
64 87
15 85
80 32
33 70
79 37
81 36
43 65
93 29
74 91
48 6
74 54
72 13
70 78
94 70
98 95
57 2
75 38
98 84
4 30
46 44
9 85
80 75
18 39
96 24
78 42
96 76
24 15
14 53
37 68
50 78
52 75
66 24
63 53
27 84
30 34
50 99
88 32
63 22
100 5
68 80
50 39
61 92
55 34
63 59
47 17
95 41
52 17
40 19
65 28
43 57
69 31
34 1
46 21
26 44
45 47
18 71
94 28
93 9
67 15
3 71
34 36
79 24
60 36
67 81
48 33
65 40
4 69
9 65
28 68
10 73
49 4
77 19
98 1
47 11
56 50
11 13
23 78
4 93
70 34
28 60
95 41
21 35


*/ 
