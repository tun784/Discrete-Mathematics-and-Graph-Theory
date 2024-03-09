#include<iostream>
#include<fstream>

#define maxn 1000
#define inf 1000000000

using namespace std;

//n: số đỉnh , m: số cạnh, s: đỉnh bắt đầu , e : đỉnh đến 
//t : loại đồ thị ( 0 : đồ thị vô hướng , 1 : đồ thị có hướng)
int n, m, s, e, t;
int a[maxn][maxn], check[maxn], d[maxn], pre[maxn];

void readFile()
{
	fstream f("input.txt");
	f >> n >> m >> t;
	f >> s >> e;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			a[i][j] = inf;
	}

	if (t == 0)
	{
		//Đồ thị vô hướng
		for (int i = 1; i <= m; i++)
		{
			int u, v, x;
			f >> u >> v;
			f >> x;
			a[u][v] = a[v][u] = x;
		}
	}
	else
	{
		//Đồ thị có hướng
		for (int i = 1; i <= m; i++)
		{
			int u, v, x;
			f >> u >> v;
			f >> x;
			a[u][v] = x;
		}
	}
	f.close();
}

void Dijkstra()
{
	for (int i = 1; i <= n; i++)
	{
		d[i] = inf;
		check[i] = 0;
		pre[i] = 0;
	}
	d[s] = 0;
	int v = s, dmin;
	while (v != e)
	{
		dmin = inf;
		for (int i = 1; i <= n; i++)
		{
			if (check[i] == 0 && dmin > d[i])
			{
				dmin = d[i];
				v = i;
			}
		}

		if (dmin == inf)
			break;
		// Đánh dấu đỉnh ngắn nhất
		check[v] = 1;

		for (int i = 1; i <= n; i++)
		{
			if (a[v][i] != inf && d[i] > d[v] + a[v][i])
			{
				d[i] = d[v] + a[v][i];
				pre[i] = v;
			}
		}
	}
}

void Xuat()
{
	if (d[e] == inf)
		cout << "Khong ton tai duong di";
	else
	{
		cout << "Chi phi : " << d[e] << "\n";
		//Dùng mảng lưu đường đi
		int path[maxn], q = 0;
		path[q] = e;
		while (pre[e] != 0)
		{
			q++;
			path[q] = pre[e];
			e = pre[e];
		}

		for (int i = q; i >= 0; i--)
		{
			cout << " " << path[i];
		}
	}
}


int main()
{
	readFile();
	Dijkstra();
	Xuat();
	return 1;
}