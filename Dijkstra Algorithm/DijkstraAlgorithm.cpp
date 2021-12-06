#include "DijkstraAlgorithm.h"

//通过静态数组创建图
//v为包含vertex值的数组，n为vertex的数量，e为edege的数量
MGraph::MGraph(int v[], int n, int e)
{
	//设置vertex的数量于edge的数量
	this->vertexNum = n;
	this->arcNum = e;

	//根据v[]里储存的数据，为vertex[]赋值
	for (int i = 0; i < this->vertexNum; i++)
	{
		this->vertex[i] = v[i];
	}

	//初始化matrix
	for (int i = 0; i < this->vertexNum; i++)
	{
		for (int j = 0; j < this->vertexNum; j++)
		{
			arc[i][j] = MY_INFINITY;
		}
	}
	//填写matrix，构造graph
	BuildGraph();

	//初始化visited
	cleanVisited();
}

//根据edge为matrix填上值，如果输入两个vertex的编号，则可以在这两个vertex之间增加一条edge，并在matrix上对应位置填入1.
void MGraph::BuildGraph()
{
	//所有顶点到自己的距离为0
	for (int j = 0; j < vertexNum; j++)
	{
		arc[j][j] = 0;
	}

	int vertex1, vertex2, weight;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "请输入要添加邻边的两个vertex的编号，并输入权值：" << endl;
		cin >> vertex1 >> vertex2 >> weight;
		this->arc[vertex1][vertex2] = weight;
		//this->arc[vertex2][vertex1] = weight;

	}

}

//展示graph的matrix
void MGraph::displayGraph()
{
	cout << "打印graph矩阵：" << endl;
	for (int i = 0; i < this->vertexNum; i++)
	{
		cout << "\t" << this->vertex[i];
	}
	cout << endl;
	for (int i = 0; i < this->vertexNum; i++)
	{
		cout << this->vertex[i] << "\t";
		for (int j = 0; j < this->vertexNum; j++)
		{
			cout << this->arc[i][j] << "\t";
		}
		cout << endl;
	}
}

void MGraph::DFSTraverse(int v)
{
	//初始化visited数组
	cleanVisited();

	//深度搜寻编号为v的顶点
	DFS(v);

	//循环整个visited数组，如果有还未visit的顶点，则以该顶点为起点继续DFS
	for (int i = 0; i < vertexNum; i++)
	{
		if (visited[i] == false)
		{
			DFS(i);
		}

	}
}

void MGraph::DFS(int v)
{
	//输出找到的第一个节点，并将该节点的bool设置为true
	cout << vertex[v] << " ";
	visited[v] = true;

	//在矩阵中当前顶点的这一行中寻找与当前顶点相连的其他顶点
	for (int i = 0; i < vertexNum; i++)
	{
		//如果该顶点有相连的其他顶点（arc[v][i]==1）且还未visit过的顶点，则递归相邻顶点
		if (arc[v][i] == 1 && visited[i] == false)
		{
			DFS(i);
		}
	}
}

void MGraph::BFSTraverse(int v)
{
	//初始化visited数组
	cleanVisited();

	BFS(v);

	//循环整个visited数组，如果有还未visit的顶点，则以该顶点为起点继续BFS
	for (int i = 0; i < vertexNum; i++)
	{
		if (visited[i] == false)
			BFS(i);
	}
}

void MGraph::BFS(int v)
{
	//输出当前顶点，并将顶点push到queue里
	cout << vertex[v] << " ";
	visited[v] = true;
	myQueue.push(vertex[v]);

	//如果队列不为空则循环运行到队列空为止
	while (!myQueue.empty())
	{
		v = myQueue.front();//将队首的值（顶点的编号）传给v
		myQueue.pop();//pop队首的值

		//循环该顶点在矩阵中对应的行，找到与该顶点相连的其他顶点
		for (int i = 0; i < vertexNum; i++)
		{
			if (arc[v][i] == 1 && visited[i] == false)
			{
				myQueue.push(vertex[i]);
				cout << vertex[i] << " ";
				visited[i] = true;
			}
		}

	}
}

void MGraph::cleanVisited()
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		visited[i] = false;
	}
}

/*Dijkstra算法：从起始点Vs开始，找到该点到所有相邻点的Vi的距离，存入distance中，然后将Vs放入集合S中。
然后从所有相邻点Vi中找到距离最近的点，并访问该点Vi1，在Vi1中重复上述行为（找到Vi1的所有相邻点的距离，
如果经过Vi1点在到另一点Vi2的距离小于直接从Vs到Vi2的距离，那么更新distance中Vi2点的值，然后将Vi1放
入集合S中）。然后继续访问离Vi1最近的点，知道所有点都访问完毕*/
void MGraph::Dijkstra(int start)
{
	int distance[MAX_VERTEX];
	int path[MAX_VERTEX];
	int s[MAX_VERTEX];

	for (int i = 0; i < vertexNum; i++)
	{
		//初始化disntance[]，使其记录start点到所有其他点的距离
		distance[i] = arc[start][i];

		//初始化path，所有起始点的邻边的path均包含起始点，所以他们的path[Vi]是start，其他的初始化为-1
		if (arc[start][i] != MY_INFINITY)
			path[i] = start;
		else
			path[i] = -1;

		//初始化集合S，0代表不在集合S中，1代表在集合S中
		s[i] = 0;
	}

	s[start] = 1;//初始化完成后，我们已经访问完毕start点，所以把start点放入集合S中
	int min = getMinCost(distance, s);//找到start点的最近邻接点
	int num = 1; // s[]中1的数量
	while (num < vertexNum)
	{
		s[min] = 1;
		//找到min后，扫描编号为min的顶点与所有邻接点的权值
		for (int j = 0; j < vertexNum; j++)
		{
			//如果s[j]=0，则说明是还未访问过的点，未访问过的点可能存在更短的距离，所以检验该点（序号为min）
			// 到所有其他点的距离arc[min][j]，如果离Vj存在更短距离，则更新Vj的distance：distance[j]，与
			//经过Vj的path的上一个点path[j]
			if (s[j] == 0 && distance[j] > distance[min] + arc[min][j])
			{
				distance[j] = distance[min] + arc[min][j];
				path[j] = min;
			}
		}
		
		min = getMinCost(distance, s);//访问完编号为min的顶点后，继续寻找编号为min的顶点的最近邻接点
		num++;//增加num，在num=vertexNum,即访问完所有顶点后退出循环
	}

	outputDijkstra(path, distance, start);
}

void MGraph::outputDijkstra(int myPath[], int myDis[], int startVertex)
{
	for (int i = 0; i < vertexNum; i++)
	{
		cout << startVertex << "->" << i + 1 << "的最短距离：" << myDis[i] << endl;
	}

	cout << "最短路径：" << endl;
	for (int j = 0; j < vertexNum; j++)
	{
		cout << "path[" << j << "]：" << myPath[j] << endl;
	}
}

//该函数返回shortEdge中的lowCost中最小的值。即找到当前顶点与最近的一个顶点之间的距离(不为0)
int MGraph::getMinCost(int myArr[], int s[])
{
	int min = MY_INFINITY;
	int index = 0;

	for (int i = 0; i < vertexNum; i++)
	{
		if ( s[i] == 0 && myArr[i] < min)
		{
			min = myArr[i];
			index = i;
		}
	}

	return index;
}

int main()
{

	int vertexNum, arcNum = 0;
	cout << "请输入vertex的数量：" << endl;
	cin >> vertexNum;
	int* myVertex = new int[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "请输入vertex的值：" << endl;
		cin >> myVertex[i];
	}
	cout << "请输入arc的数量：" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	int start;
	cout << "准备开始寻找最小生成树，请输入起始顶点的编号：";
	cin >> start;
	mg.Dijkstra(start);

	system("pause");
	return 0;
}