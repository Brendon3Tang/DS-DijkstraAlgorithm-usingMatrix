#include "DijkstraAlgorithm.h"

//ͨ����̬���鴴��ͼ
//vΪ����vertexֵ�����飬nΪvertex��������eΪedege������
MGraph::MGraph(int v[], int n, int e)
{
	//����vertex��������edge������
	this->vertexNum = n;
	this->arcNum = e;

	//����v[]�ﴢ������ݣ�Ϊvertex[]��ֵ
	for (int i = 0; i < this->vertexNum; i++)
	{
		this->vertex[i] = v[i];
	}

	//��ʼ��matrix
	for (int i = 0; i < this->vertexNum; i++)
	{
		for (int j = 0; j < this->vertexNum; j++)
		{
			arc[i][j] = MY_INFINITY;
		}
	}
	//��дmatrix������graph
	BuildGraph();

	//��ʼ��visited
	cleanVisited();
}

//����edgeΪmatrix����ֵ�������������vertex�ı�ţ��������������vertex֮������һ��edge������matrix�϶�Ӧλ������1.
void MGraph::BuildGraph()
{
	//���ж��㵽�Լ��ľ���Ϊ0
	for (int j = 0; j < vertexNum; j++)
	{
		arc[j][j] = 0;
	}

	int vertex1, vertex2, weight;
	for (int i = 0; i < this->arcNum; i++)
	{
		cout << "������Ҫ����ڱߵ�����vertex�ı�ţ�������Ȩֵ��" << endl;
		cin >> vertex1 >> vertex2 >> weight;
		this->arc[vertex1][vertex2] = weight;
		//this->arc[vertex2][vertex1] = weight;

	}

}

//չʾgraph��matrix
void MGraph::displayGraph()
{
	cout << "��ӡgraph����" << endl;
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
	//��ʼ��visited����
	cleanVisited();

	//�����Ѱ���Ϊv�Ķ���
	DFS(v);

	//ѭ������visited���飬����л�δvisit�Ķ��㣬���Ըö���Ϊ������DFS
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
	//����ҵ��ĵ�һ���ڵ㣬�����ýڵ��bool����Ϊtrue
	cout << vertex[v] << " ";
	visited[v] = true;

	//�ھ����е�ǰ�������һ����Ѱ���뵱ǰ������������������
	for (int i = 0; i < vertexNum; i++)
	{
		//����ö������������������㣨arc[v][i]==1���һ�δvisit���Ķ��㣬��ݹ����ڶ���
		if (arc[v][i] == 1 && visited[i] == false)
		{
			DFS(i);
		}
	}
}

void MGraph::BFSTraverse(int v)
{
	//��ʼ��visited����
	cleanVisited();

	BFS(v);

	//ѭ������visited���飬����л�δvisit�Ķ��㣬���Ըö���Ϊ������BFS
	for (int i = 0; i < vertexNum; i++)
	{
		if (visited[i] == false)
			BFS(i);
	}
}

void MGraph::BFS(int v)
{
	//�����ǰ���㣬��������push��queue��
	cout << vertex[v] << " ";
	visited[v] = true;
	myQueue.push(vertex[v]);

	//������в�Ϊ����ѭ�����е����п�Ϊֹ
	while (!myQueue.empty())
	{
		v = myQueue.front();//�����׵�ֵ������ı�ţ�����v
		myQueue.pop();//pop���׵�ֵ

		//ѭ���ö����ھ����ж�Ӧ���У��ҵ���ö�����������������
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

/*Dijkstra�㷨������ʼ��Vs��ʼ���ҵ��õ㵽�������ڵ��Vi�ľ��룬����distance�У�Ȼ��Vs���뼯��S�С�
Ȼ����������ڵ�Vi���ҵ���������ĵ㣬�����ʸõ�Vi1����Vi1���ظ�������Ϊ���ҵ�Vi1���������ڵ�ľ��룬
�������Vi1���ڵ���һ��Vi2�ľ���С��ֱ�Ӵ�Vs��Vi2�ľ��룬��ô����distance��Vi2���ֵ��Ȼ��Vi1��
�뼯��S�У���Ȼ�����������Vi1����ĵ㣬֪�����е㶼�������*/
void MGraph::Dijkstra(int start)
{
	int distance[MAX_VERTEX];
	int path[MAX_VERTEX];
	int s[MAX_VERTEX];

	for (int i = 0; i < vertexNum; i++)
	{
		//��ʼ��disntance[]��ʹ���¼start�㵽����������ľ���
		distance[i] = arc[start][i];

		//��ʼ��path��������ʼ����ڱߵ�path��������ʼ�㣬�������ǵ�path[Vi]��start�������ĳ�ʼ��Ϊ-1
		if (arc[start][i] != MY_INFINITY)
			path[i] = start;
		else
			path[i] = -1;

		//��ʼ������S��0�����ڼ���S�У�1�����ڼ���S��
		s[i] = 0;
	}

	s[start] = 1;//��ʼ����ɺ������Ѿ��������start�㣬���԰�start����뼯��S��
	int min = getMinCost(distance, s);//�ҵ�start�������ڽӵ�
	int num = 1; // s[]��1������
	while (num < vertexNum)
	{
		s[min] = 1;
		//�ҵ�min��ɨ����Ϊmin�Ķ����������ڽӵ��Ȩֵ
		for (int j = 0; j < vertexNum; j++)
		{
			//���s[j]=0����˵���ǻ�δ���ʹ��ĵ㣬δ���ʹ��ĵ���ܴ��ڸ��̵ľ��룬���Լ���õ㣨���Ϊmin��
			// ������������ľ���arc[min][j]�������Vj���ڸ��̾��룬�����Vj��distance��distance[j]����
			//����Vj��path����һ����path[j]
			if (s[j] == 0 && distance[j] > distance[min] + arc[min][j])
			{
				distance[j] = distance[min] + arc[min][j];
				path[j] = min;
			}
		}
		
		min = getMinCost(distance, s);//��������Ϊmin�Ķ���󣬼���Ѱ�ұ��Ϊmin�Ķ��������ڽӵ�
		num++;//����num����num=vertexNum,�����������ж�����˳�ѭ��
	}

	outputDijkstra(path, distance, start);
}

void MGraph::outputDijkstra(int myPath[], int myDis[], int startVertex)
{
	for (int i = 0; i < vertexNum; i++)
	{
		cout << startVertex << "->" << i + 1 << "����̾��룺" << myDis[i] << endl;
	}

	cout << "���·����" << endl;
	for (int j = 0; j < vertexNum; j++)
	{
		cout << "path[" << j << "]��" << myPath[j] << endl;
	}
}

//�ú�������shortEdge�е�lowCost����С��ֵ�����ҵ���ǰ�����������һ������֮��ľ���(��Ϊ0)
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
	cout << "������vertex��������" << endl;
	cin >> vertexNum;
	int* myVertex = new int[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "������vertex��ֵ��" << endl;
		cin >> myVertex[i];
	}
	cout << "������arc��������" << endl;
	cin >> arcNum;

	MGraph mg(myVertex, vertexNum, arcNum);
	mg.displayGraph();

	int start;
	cout << "׼����ʼѰ����С����������������ʼ����ı�ţ�";
	cin >> start;
	mg.Dijkstra(start);

	system("pause");
	return 0;
}