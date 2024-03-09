#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <fstream>
#include <random>
#include <string>

using namespace std;

using ll = long long;

const int maxn = 100001;
int n, m, s;
int maxy;
vector<pair<int, int>> adj[maxn]; //mang luu ma tran
vector<int> Snode; //mang luu vi tri dac biet
vector<pair<int, int>> Sroad; //mang luu duong di dac biet
vector<int> tramSac; //mang luu vi tri tram sac

ifstream fi("input.txt");
ifstream ni("name.txt");
ofstream fo("output.txt");


struct passenger
{
	string name;
	char gender[4];
	char destination[10];
	int creds;
	int pointCard;
};
struct electricBus
{
	int sohanhkhach;
	passenger hanhkhach[10];
	int pin;
	int point;
	char position[10];
	int morality;
	int credsSum;
	int damage;
};
electricBus B;
struct timeControl
{
	pair<int, int> time = { 6, 0 };
	int day = 1;
};
timeControl realtime;

void nhap();
void dijkstra(int s);
void outputChoice(vector<ll> &d);
void gameStar();
int checkForSpecial(int s); //Ham kiem tra vi tri tiep theo co phai la vi tri dac biet ko
int specialNodeLibrary(int s); //Thu vien vi tri dat biet
float specialRoadLibrary(int sPrev, int s); //Thu bien duong di dac biet
void findingNearestChargingStation(vector<ll> d, int s);
int randomInRange(int a, int b);
void createPassenger();
void createCarInfo();
void carInfo();
void passengerList();
void deletePassenger(int x);
void timeChecker();
void timeRightNow();
bool laDuongDiTrungLap(int x, int y);
void themDuongDi(int x, int y, int w);
bool xoaDuongDi(int x, int y);
bool kiemTraDuongDiHopLe(int x, int y);
int CalculateTotalPoints();
void resourceNow(int s, int sPrev, float hsg);
void writeInfoToFile(const std::string& name, int n);
std::vector<std::pair<std::string, int>> readInfoFromFile();
void sortInfoByCountDescending(std::vector<std::pair<std::string, int>>& info);
int ranking();

void nhap() 
{
	fi >> n >> m >> s;
	for (int i = 0; i < m; i++) {
		int x, y, w; 
		//Tu x den y co trong so w
		fi >> x >> y >> w;
		maxy = y;
		adj[x].push_back({ y, w });
	}

	int a, A;
	fi >> a;
	for (int i = 0; i < a; i++)
	{
		fi >> A;
		Snode.push_back(A);
	}

	int b, B, Be;
	fi >> b;
	for (int i = 0; i < b; i++)
	{
		fi >> B;
		fi >> Be;
		Sroad.push_back({B, Be});
	}

	int sl, temp;
	fi >> sl;
	for (int i = 0; i < sl; i++)
	{
		fi >> temp;
		tramSac.push_back(temp);
	}
}

const int INF = 1e9;
int pre[maxn];

//Thuat toan dijkstra
void dijkstra(int s) {
	//Mang luu khoang cach duong di
	vector<ll> d(n + 1, INF);
	d[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	//Dung hang doi uu tien de luu cac dinh, dinh co khoang cach toi s gan nhat se duoc uu tien dau tien
	//{khoang cach, dinh}
	Q.push({ 0, s });
	while (!Q.empty()) {
		//Chọn ra đỉnh có khoảng cách từ s nhỏ nhất 
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;
		int kc = top.first;
		if (kc > d[u]) continue;
		//Relaxtion : Thông qua đỉnh u đã biết khoảng cách ngắn nhất tính từ S, cập
		//nhật khoảng cách với các đỉnh kề với u
		for (auto it : adj[u]) 
		{
			int v = it.first;
			int w = it.second;
			if (d[v] > d[u] + w) 
			{
				d[v] = d[u] + w;
				Q.push({ d[v], v });
			}
		}
	}
	findingNearestChargingStation(d, s);
	outputChoice(d);
}
//Ham xuat ra man hinh diem co the den tiep theo
void outputChoice(vector<ll> &d)
{
	cout << "Diem co the den tiep theo:" << endl;
		if (!adj[s].empty())
		{
			for (const auto& p : adj[s])
			{
				cout <<"\t" << s << " --> ";
				cout << p.first << ": " << p.second << endl;
			}
			cout << endl;
		}
}
//Ham kiem tra vi tri hien tai co phai la tinh nang khong
int checkForSpecial(int s)
{
	int temp = 0;
	for (auto i : Snode)
	{
		if (s == i)
		{
			temp++;
			break;
		}
	}

	for (auto i : Sroad)
	{
		if (s == i.second)
		{
			temp += 2;
			break;
		}
	}
	return temp;
}
//Ham cac nut tinh nang
int specialNodeLibrary(int s)
{
	if (s < 10)
	{
		if (s == 3)
		{
			char choice[4];
			int choose;
			cout << "===Chao mung ban den tram don khach===" << endl << "Ban muon tra khach hay don khach ? (Tra / Don): ";
			cin >> choice;
			cout << endl;

			if (strcmp(choice, "Tra") == 0)
			{
				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
				passengerList();
				cout << "Ban muon tra bao nhieu khach hang? " << endl;
				int n;
				cin >> n;
				for(int i = 0; i < n; i++)
				{
					cout << "Tra khach hang thu: ";
					cin >> choose;
					cout << endl;
					if (strcmp(B.hanhkhach[choose - 1].destination, "Thanh Pho") == 0)
						B.point += 100;
					else B.point -= 100;
					deletePassenger(choose - 1);
				}
				
				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
				passengerList();
			}
			else if (strcmp(choice, "Don") == 0)
			{
				int temp = randomInRange(1, 3);
				int tomp = randomInRange(1, 5 - temp);
				cout << "=====Danh sach hanh khach co the don=====" << endl;
				cout << "|Co " << temp << " hanh khach muon di bien\t\t|" << endl;
				cout << "|Co " << tomp << " hanh khach muon di nui\t\t|" << endl;
				cout << "|Co " << 5 - temp - tomp << " hanh khach muon di quoc lo\t|" << endl;
				cout << "=========================================" << endl;
				passenger hanhkhachtram[5];
				int dem = 0;
				for (int i = 0; i < temp; i++) 
				{
					hanhkhachtram[dem].name = "A";
					strcpy_s(hanhkhachtram[dem].gender, "Nam");
					strcpy_s(hanhkhachtram[dem].destination, "Bien");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < tomp; i++)
				{
					hanhkhachtram[dem].name = "B";
					strcpy_s(hanhkhachtram[dem].gender, "Nu");
					strcpy_s(hanhkhachtram[dem].destination, "Nui");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < 5 - temp - tomp; i++)
				{
					hanhkhachtram[dem].name = "C";
					strcpy_s(hanhkhachtram[dem].gender, "Nu");
					strcpy_s(hanhkhachtram[dem].destination, "Quoc Lo");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < 5; i++)
				{
					cout << "Hanh khach thu " << i + 1 << ":" << endl;
					cout << "Ten: " << hanhkhachtram[i].name << endl;
					cout << "Diem den: " << hanhkhachtram[i].destination << endl;
				}
				cout << "Ban muon don bao nhieu khach hang di bien, nui, quoc lo? ";
				int n[3];
				cin >> n[0] >> n[1] >> n[2];
				if (n[0] > temp)
				{
					cout << "Nhap lai so khach hang di bien: ";
					cin >> n[0];
				}
				if (n[1] > tomp)
				{
					cout << "Nhap lai so khach hang di nui: ";
					cin >> n[1];
				}
				if (n[2] > 5 - temp - tomp)
				{
					cout << "Nhap lai so khach hang di quoc lo: ";
					cin >> n[2];
				}
				int dem1 = 0;
				int dem2 = temp;
				int dem3 = temp + tomp;
				for(int i = 0; i < n[0]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem1];
					B.sohanhkhach++;
					dem1++;
				}
				for (int i = 0; i < n[1]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem2];
					B.sohanhkhach++;
					dem2++;
				}
				for (int i = 0; i < n[2]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem3];
					B.sohanhkhach++;
					dem3++;
				}
				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai la:" << endl;
				passengerList();
			}
		}
		if (s == 6)
		{
			cout << "===Chao mung ban den tram sac===" << endl;
			char choice[2];
			cout << "Ban co muon sac lai pin cho xe khong?(Y/N)";
			cin >> choice;

			if (strcmp(choice, "Y") == 0)
			{
				cout << endl << "Ban muon sac bao lau(Phut): ";
				int tg;
				cin >> tg;
				cout << endl;
				B.pin += tg;

				realtime.time.second += tg;
				timeChecker();
				carInfo();
				timeRightNow();
			}
			else if (strcmp(choice, "config") == 0)//config duong di
			{
				int pick;
				cout << "1. Them duong di" << endl;
				cout << "2. Xoa duong di" << endl;
				cin >> pick;
				if (pick == 1)
				{
					int x, y, w;
					cin >> x >> y >> w;
					themDuongDi(x, y, w);
				}
				else if (pick == 2)
				{
					int x, y;
					cin >> x >> y;
					xoaDuongDi(x, y);
				}
			}
		}
		if (s == 8)
		{
			cout << "===Chao mung ban den tram tich diem===" << endl;
			int dem = 0;
			for (int i = 0; i < B.sohanhkhach; i++)
			{
				if (B.hanhkhach[i].pointCard == 1)
				{
					B.hanhkhach[i].pointCard = 3;
					dem++;
				}
			}
			cout << "Da co " << dem << " hanh khach duoc kich hoat the tich diem" << endl;
		}
		if (s == 9)
		{
			cout << "===Chao mung ban dem tram thu phi===" << endl;
			cout << "Tien ve la 50k moi nguoi (co khuyen mai tuy thuoc vao the tich diem)" << endl;
			for (int i = 0; i < B.sohanhkhach; i++)
			{
				if (B.hanhkhach[i].pointCard == 3)
				{
					B.hanhkhach[i].creds -= 37500;
				}
				else if (B.hanhkhach[i].pointCard == 1)
				{
					B.hanhkhach[i].creds -= 45000;
				}
				else B.hanhkhach[i].creds -= 50000;
			}

		}
	}
	else if (s > 12 && s < 22)
	{
		if (s == 13)
		{
			{
				cout << "===Chao mung ban dem tram thu phi===" << endl;
				cout << "Tien ve la 50k moi nguoi (co khuyen mai tuy thuoc vao the tich diem)" << endl;
				for (int i = 0; i < B.sohanhkhach; i++)
				{
					if (B.hanhkhach[i].pointCard == 3)
					{
						B.hanhkhach[i].creds -= 56250;
					}
					else if (B.hanhkhach[i].pointCard == 1)
					{
						B.hanhkhach[i].creds -= 65500;
					}
					else B.hanhkhach[i].creds -= 75000;
				}

			}
		}
		if (s == 14)
		{
			{
				{
					char choice[4];
					int choose;
					cout << "==Chao mung ban den tram don khach===" << endl << "Ban muon tra khach hay don khach ? (Tra / Don)" << endl;
					cin >> choice;
					if (strcmp(choice, "Tra") == 0)
					{
						cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
						passengerList();
						cout << "Ban muon tra bao nhieu khach hang? " << endl;
						int n;
						cin >> n;
						for (int i = 0; i < n; i++)
						{
							cout << "Tra khach hang thu: ";
							cin >> choose;
							cout << endl;
							if (strcmp(B.hanhkhach[choose - 1].destination, "Quoc lo") == 0)
								B.point += 100;
							else B.point -= 100;
							deletePassenger(choose - 1);
						}

						cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
						passengerList();
					}
					else if (strcmp(choice, "Don") == 0)
					{
						int temp = randomInRange(1, 3);
						int tomp = randomInRange(1, 5 - temp);
						cout << "Danh sach hanh khach co the don:" << endl;
						cout << "Co " << temp << "hanh khach muon di bien" << endl;
						cout << "Co " << tomp << "hanh khach muon di nui" << endl;
						cout << "Co " << 5 - temp - tomp << "hanh khach muon di quoc lo" << endl;
						passenger hanhkhachtram[5];
						int dem = 0;
						for (int i = 0; i < temp; i++)
						{
							hanhkhachtram[dem].name = "A";
							strcpy_s(hanhkhachtram[dem].gender, "Nam");
							strcpy_s(hanhkhachtram[dem].destination, "Bien");
							int money = randomInRange(150000, 300000);
							hanhkhachtram[dem].creds = money;
							hanhkhachtram[dem].pointCard = 0;
							dem++;
						}
						for (int i = 0; i < tomp; i++)
						{
							hanhkhachtram[dem].name = "B";
							strcpy_s(hanhkhachtram[dem].gender, "Nu");
							strcpy_s(hanhkhachtram[dem].destination, "Nui");
							int money = randomInRange(150000, 300000);
							hanhkhachtram[dem].creds = money;
							hanhkhachtram[dem].pointCard = 0;
							dem++;
						}
						for (int i = 0; i < 5 - temp - tomp; i++)
						{
							hanhkhachtram[dem].name = "C";
							strcpy_s(hanhkhachtram[dem].gender, "Nu");
							strcpy_s(hanhkhachtram[dem].destination, "Quoc Lo");
							int money = randomInRange(150000, 300000);
							hanhkhachtram[dem].creds = money;
							hanhkhachtram[dem].pointCard = 0;
							dem++;
						}
						for (int i = 0; i < 5; i++)
						{
							cout << "Hanh khach thu " << i + 1 << ":" << endl;
							cout << "Ten: " << hanhkhachtram[i].name << endl;
							cout << "Diem den: " << hanhkhachtram[i].destination << endl;
						}
						cout << "Ban muon don bao nhieu khach hang di bien, nui, quoc lo? ";
						int n[3];
						cin >> n[0] >> n[1] >> n[2];
						if (n[0] > temp)
						{
							cout << "Nhap lai so khach hang di bien: ";
							cin >> n[0];
						}
						if (n[1] > tomp)
						{
							cout << "Nhap lai so khach hang di nui: ";
							cin >> n[1];
						}
						if (n[2] > 5 - temp - tomp)
						{
							cout << "Nhap lai so khach hang di quoc lo: ";
							cin >> n[2];
						}
						int dem1 = 0;
						int dem2 = temp;
						int dem3 = temp + tomp;
						for (int i = 0; i < n[0]; i++)
						{
							B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem1];
							B.sohanhkhach++;
							dem1++;
						}
						for (int i = 0; i < n[1]; i++)
						{
							B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem2];
							B.sohanhkhach++;
							dem2++;
						}
						for (int i = 0; i < n[2]; i++)
						{
							B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem3];
							B.sohanhkhach++;
							dem3++;
						}
						cout << "Danh sach hanh khach va diem den cua hanh khach hien tai la:" << endl;
						passengerList();
					}
				}
			}
		}
		if (s == 19)
		{
			cout << "===Chao mung ban den khu du lich===" << endl;
			int dem1 = 0, dem2 = 0;//dem1 la nam dem2 la nu
			for (int i = 0; i < B.sohanhkhach; i++)
			{
				if (strcmp(B.hanhkhach->gender, "Nam") == 0)
					dem1++;
				else dem2++;
			}
			if (dem1 > dem2)
			{
				B.morality += 10;
			}
			else if (dem1 < dem2)
			{
				B.morality += 20;
			}
			else B.morality += 15;

		}
		if (s == 20)
		{
			cout << "===Chao mung ban den tram sac===" << endl;
			char choice[2];
			cout << "Ban co muon sac lai pin cho xe khong?(Y/N)";
			cin >> choice;
			if (strcmp(choice, "Y") == 0)
			{
				cout << endl << "Ban muon sac bao lau(Phut): ";
				int tg;
				cin >> tg;
				cout << endl;
				B.pin += tg;

				realtime.time.second += tg;
				timeChecker();
				carInfo();
				timeRightNow();
			}
			if (strcmp(choice, "config") == 0)//config duong di
			{
				int pick;
				cout << "1. Them duong di" << endl;
				cout << "2. Xoa duong di" << endl;
				cin >> pick;
				if (pick == 1)
				{
					int x, y, w;
					cin >> x >> y >> w;
					themDuongDi(x, y, w);
				}
				else if (pick == 2)
				{
					int x, y;
					cin >> x >> y;
					xoaDuongDi(x, y);
				}
			}
		}
		
	}
	else if (s > 22 && s < 32)
	{
		if (s == 23)
		{
			char choice[4];
			int choose;
			cout << "==Chao mung ban den tram don khach===" << endl << "Ban muon tra khach hay don khach ? (Tra / Don)" << endl;
			cin >> choice;
			if (strcmp(choice, "Tra") == 0)
			{
				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
				passengerList();
				cout << "Ban muon tra bao nhieu khach hang? " << endl;
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
				{
					cout << "Tra khach hang thu: ";
					cin >> choose;
					cout << endl;
					if (strcmp(B.hanhkhach[choose - 1].destination, "Thanh Pho") == 0)
						B.point += 100;
					else B.point -= 100;
					deletePassenger(choose - 1);
				}

				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
				passengerList();
			}
			else if (strcmp(choice, "Don") == 0)
			{
				int temp = randomInRange(1, 3);
				int tomp = randomInRange(1, 5 - temp);
				cout << "Danh sach hanh khach co the don:" << endl;
				cout << "Co " << temp << "hanh khach muon di bien" << endl;
				cout << "Co " << tomp << "hanh khach muon di nui" << endl;
				cout << "Co " << 5 - temp - tomp << "hanh khach muon di quoc lo" << endl;
				passenger hanhkhachtram[5];
				int dem = 0;
				for (int i = 0; i < temp; i++)
				{
					hanhkhachtram[dem].name = "A";
					strcpy_s(hanhkhachtram[dem].gender, "Nam");
					strcpy_s(hanhkhachtram[dem].destination, "Bien");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < tomp; i++)
				{
					hanhkhachtram[dem].name = "B";
					strcpy_s(hanhkhachtram[dem].gender, "Nu");
					strcpy_s(hanhkhachtram[dem].destination, "Nui");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < 5 - temp - tomp; i++)
				{
					hanhkhachtram[dem].name = "C";
					strcpy_s(hanhkhachtram[dem].gender, "Nu");
					strcpy_s(hanhkhachtram[dem].destination, "Quoc Lo");
					int money = randomInRange(150000, 300000);
					hanhkhachtram[dem].creds = money;
					hanhkhachtram[dem].pointCard = 0;
					dem++;
				}
				for (int i = 0; i < 5; i++)
				{
					cout << "Hanh khach thu " << i + 1 << ":" << endl;
					cout << "Ten: " << hanhkhachtram[i].name << endl;
					cout << "Diem den: " << hanhkhachtram[i].destination << endl;
				}
				cout << "Ban muon don bao nhieu khach hang di bien, nui, quoc lo? ";
				int n[3];
				cin >> n[0] >> n[1] >> n[2];
				if (n[0] > temp)
				{
					cout << "Nhap lai so khach hang di bien: ";
					cin >> n[0];
				}
				if (n[1] > tomp)
				{
					cout << "Nhap lai so khach hang di nui: ";
					cin >> n[1];
				}
				if (n[2] > 5 - temp - tomp)
				{
					cout << "Nhap lai so khach hang di quoc lo: ";
					cin >> n[2];
				}
				int dem1 = 0;
				int dem2 = temp;
				int dem3 = temp + tomp;
				for (int i = 0; i < n[0]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem1];
					B.sohanhkhach++;
					dem1++;
				}
				for (int i = 0; i < n[1]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem2];
					B.sohanhkhach++;
					dem2++;
				}
				for (int i = 0; i < n[2]; i++)
				{
					B.hanhkhach[B.sohanhkhach] = hanhkhachtram[dem3];
					B.sohanhkhach++;
					dem3++;
				}
				cout << "Danh sach hanh khach va diem den cua hanh khach hien tai la:" << endl;
				passengerList();
			}
		}
		if (s == 27)
		{
			cout << "===Khu vuc co quan canh dep, khach hang da tro nen vui ve hon===" << endl;
			B.morality += 20;
		}
		if (s == 28)
		{
			cout << "===Chao mung ban den tram sac===" << endl;
			char choice[2];
			cout << "Ban co muon sac lai pin cho xe khong?(Y/N)";
			cin >> choice;
			if (strcmp(choice, "Y") == 0)
			{
				cout << endl << "Ban muon sac bao lau(Phut): ";
				int tg;
				cin >> tg;
				cout << endl;
				B.pin += tg;

				realtime.time.second += tg;
				timeChecker();
				carInfo();
				timeRightNow();
			}
			if (strcmp(choice, "config") == 0)//config duong di
			{
				int pick;
				cout << "1. Them duong di" << endl;
				cout << "2. Xoa duong di" << endl;
				cin >> pick;
				if (pick == 1)
				{
					int x, y, w;
					cin >> x >> y >> w;
					themDuongDi(x, y, w);
				}
				else if (pick == 2)
				{
					int x, y;
					cin >> x >> y;
					xoaDuongDi(x, y);
				}
			}
		}
		if (s == 30)
		{
			cout << "===Chao mung ban den suoi nuoc nong===" << endl;
			cout << "Khach hang da tro nen vui ve hon" << endl;
			B.morality += 50;
		}
	}
	else if (s > 32 && s < 43)
	{
		if (s == 33)
		{
			cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
			passengerList();
			cout << "Ban muon tra bao nhieu khach hang? " << endl;
			int n, choose;
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "Tra khach hang thu: ";
				cin >> choose;
				cout << endl;
				deletePassenger(choose - 1);
			}
			B.point -= 50*n;
			cout << "Danh sach hanh khach va diem den cua hanh khach hien tai: " << endl;
			passengerList();
		}
		if (s == 36)
		{
			cout << "===Xe da den benh vien===" << endl;
			for (int i = 0; i < B.sohanhkhach; i++)
			{
				B.hanhkhach[i].creds -= 50;
			}
			B.morality += 30;
		}
		if (s == 40)
		{
			cout << "Xe da duoc sua chua" << endl;
			B.damage -= 50;
			if (B.damage < 0)
				B.damage = 0;
		}
	}
		return 1;
}
//Ham cac con duong tinh nang
//Tra ve 0 khi xay ra tai nan(GAME OVER)
float specialRoadLibrary(int sPrev, int s)
{
	int temp = Sroad.size();
	if (s < 10)
	{
		for (int i = 0; i < temp; i++)
		{
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 0)
			{
				if ((realtime.time.first >= 10 && realtime.time.first <= 12) || (realtime.time.first >= 3 && realtime.time.first <= 5))
				cout << "Duong ket xe" << endl;
				cout << "ban se mat gap doi thoi gian qua quan duong nay" << endl;
				return 2; //Tra ve 2 khi xay ra ket xe, dung 2 de nhan voi trong so quang duong o diem nay
			}
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 1)
			{
				cout << "Doan duong nay de xay ra tai nan" << endl;
				int dem1 = 0, dem2 = 0;//dem1 la nam dem2 la nu
				for (int i = 0; i < B.sohanhkhach; i++)
				{
					if (strcmp(B.hanhkhach->gender, "Nam") == 0)
						dem1++;
					else dem2++;
				}
				if (dem1 > dem2)
				{
					int temp = randomInRange(1, 100);
					if (temp <= 25)
					{
						cout << "Game Over";
						return 0; //Tra ve -1 khi xay ra tai nan, ket thuc game
					}
				}
				else if (dem1 < dem2)
				{
					int temp = randomInRange(1, 100);
					if (temp <= 35)
					{
						cout << "Game Over";
						return 0;//Tra ve -1 khi xay ra tai nan, ket thuc game
					}
				}
				else 
				{
					int temp = randomInRange(1, 100);
						if (temp <= 30)
						{
							cout << "Game Over";
							return 0;//Tra ve -1 khi xay ra tai nan, ket thuc game
						}
				}
				cout << "Khong xay ra tai nan" << endl;
				break;
			}
		}
	}
	else if (s > 12 && s < 21)
	{
		for (int i = 0; i < temp; i++)
		{
			if (sPrev == Sroad[i].first && s == Sroad[i].second && ((i == 2) || (i == 3)))//13 17, 13 18
			{
				if ((realtime.time.first >= 10 && realtime.time.first <= 12) || (realtime.time.first >= 3 && realtime.time.first <= 5))
				{
					cout << "Cao toc dang ket xe" << endl;
					return 2 ;//tra ve 2(x2) thoi gian can de qua doan duong
				}
				else return (float)0.4;//tra ve 0.5(giam x2.5) thoi gian can de qua doan duong
			}

			if (sPrev == Sroad[i].first && s == Sroad[i].second && ((i == 4) || (i == 5)))//17 20, 19 20
			{
				cout << "===Duong de xay ra tai nan===" << endl;
				int dem1 = 0, dem2 = 0;//dem1 la nam dem2 la nu
				for (int i = 0; i < B.sohanhkhach; i++)
				{
					if (strcmp(B.hanhkhach->gender, "Nam") == 0)
						dem1++;
					else dem2++;
				}
				int chance = randomInRange(1, 100);
				if (dem1 > dem2 && chance <= 20)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 5;
				} 
				else if (dem1 < dem2 && chance <= 30)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 5;
				}
				else if (dem1 == dem2 && chance <= 25)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 5;
				}
			}
		}
	}
	else if (s > 22 && s < 32)
	{
		for (int i = 0; i < temp; i++)
		{
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 6)
			{
				cout << "===Xe dang len deo===" << endl;
				int dem1 = 0, dem2 = 0;//dem1 la nam dem2 la nu
				for (int i = 0; i < B.sohanhkhach; i++)
				{
					if (strcmp(B.hanhkhach->gender, "Nam") == 0)
						dem1++;
					else dem2++;
				}
				int chance = randomInRange(1, 100);
				if (dem1 > dem2 && chance <= 20)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 8;
				}
				else if (dem1 < dem2 && chance <= 30)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 8;
				}
				else if (dem1 == dem2 && chance <= 25)
				{
					cout << "Xay ra tai nan" << endl;
					B.damage += B.sohanhkhach * 8;
				}
			}
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 7)
			{
				cout << "===Xe dang vao ham===" << endl;
				char choice[6];
				cout << "Ban muon di nhanh hay cham? ";
				cin >> choice;
				int chance = randomInRange(1, 100);
				if (strcmp(choice, "Nhanh"))
				{
					if (chance <= 5)
					{
						cout << "Da xay ra tai nan" << endl << "GAME OVER!" << endl;
						return 0;
					}
					else return 0.3;//tra ve 0.3 (giam thoi gian can de di qua)
				}
				if (strcmp(choice, "Cham"))
				{
					if (chance == 1)
					{
						cout << "Da xay ra tai nan" << endl << "GAME OVER!" << endl;
						return 0;
					}
					else return 0.3;//tra ve 0.3 (giam thoi gian can de di qua)
				}
			}
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 8)
			{
				cout << "===Xe dang vao ham===" << endl;
				char choice[6];
				cout << "Ban muon di nhanh hay cham? ";
				cin >> choice;
				int chance = randomInRange(1, 100);
				if (strcmp(choice, "Nhanh"))
				{
					if (chance % 2 == 0)
					{
						cout << "Da xay ra tai nan" << endl << "GAME OVER!" << endl;
						return 0;
					}
					else return 0.3;
				}
				if (strcmp(choice, "Cham"))
				{
					if (chance <= 25)
					{
						cout << "Da xay ra tai nan" << endl << "GAME OVER!" << endl;
						return 0;
					}
					else return 0.3;
				}
			}
		}
	}
	else if (s > 32 && s < 43)
	{
		for (int i = 0; i < temp; i++)
		{
			if (sPrev == Sroad[i].first && s == Sroad[i].second && i == 9)
			{
				cout << "===Xe dang di qua duong cat===" << endl;
				B.morality += 20;
				B.damage += 10;
			}
		}
	}
	return 1;
}
//Bat dau tro choi
void gameStar()
{
	int sPrev; 
	float hsg = 1;
	while (1)
	{
		cout << "~Buoc tiep theo: ";
		sPrev = s;
		cin >> s;
		cout << endl;
		while (kiemTraDuongDiHopLe(sPrev, s) == false)
		{
			cin >> s;
			cout << endl;
		}

		int temp = checkForSpecial(s);
		if (temp == 1)
			specialNodeLibrary(s);

		if (temp == 2)
			hsg = specialRoadLibrary(sPrev, s);

		if (temp == 3)
		{
			specialNodeLibrary(s);
			hsg = specialRoadLibrary(sPrev, s);
		}
		resourceNow(s, sPrev, hsg);
		if (hsg == 0)
		{
			cout << "GAME OVER!" << endl;
			break;
		}


		if (B.pin <= 0 || B.damage >= 100)
		{
			cout << "GAME OVER!" << endl;
			break;
		}

		dijkstra(s);
		if (s == maxy)
		{
			B.point += CalculateTotalPoints();
			cout << "Tong diem: ";
			cout << B.point;
			ranking();
			break;
		}
	}
}
//Ham tim cac tram sac gan nhat co the den
void findingNearestChargingStation(vector<ll> d, int s)
{
	cout << "============Danh sach tram sac gan day===========" << endl;
	if (s < 7)
	{
		for (int i = 0; i < tramSac.size(); i++)
		{
			int j = tramSac[i];
			cout << "| Tram " << i << " - Thoi luong pin can thiet la: " << d[j] << "\t|" << endl;
		}
	}
	else if (s > 6 && s < 21)
	{
		for (int i = 1; i < tramSac.size(); i++)
		{
			int j = tramSac[i];
			cout << "| Tram " << i << " - Thoi luong pin can thiet la: " << d[j] << "\t|" << endl;
		}
	} 
	else if (s > 6 && s < 29)
	{
		for (int i = 2; i < tramSac.size(); i++)
		{
			int j = tramSac[i];
			cout << "| Tram " << i << " - Thoi luong pin can thiet la: " << d[j] << "\t|" << endl;
		}
	}
	cout << "=================================================" << endl;
}
//Ham ngau nhien 1 so tu a den b (Ho tro)
int randomInRange(int a, int b)
{
	mt19937 rng(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> distribution(a, b);

	return distribution(rng);
}

//Cac ham thiet lap ban dau va quan ly cac thong so tai nguyen
void createPassenger()
{

	for (int i = 0; i < 5; i++)
	{
		getline(ni, B.hanhkhach[i].name);
	}
	for (int i = 0; i < 5; i++)
	{
		strcpy_s(B.hanhkhach[i].destination, "Bien");
	}
	int temp = randomInRange(1, 4);
	for (int j = 0; j < temp; j++)
	{
		strcpy_s(B.hanhkhach[j].gender, "Nam");
	}
	for (int k = temp; k < 5 - temp; k++)
	{
		strcpy_s(B.hanhkhach[k].gender, "Nu");
	}
	temp = randomInRange(1, 5);
	for(int z = 0; z < temp; z++)
	{
		B.hanhkhach[z].pointCard = 1;
	}
	for (int l = temp; l < 5- temp; l++)
	{
		B.hanhkhach[l].pointCard = 0;
	}
	for (int m = 0; m < 5; m++)
	{
		temp = randomInRange(150000, 300000);
		B.hanhkhach[m].creds = temp;
	}
}
void createCarInfo()
{
	B.sohanhkhach = 5;
	strcpy_s(B.position, "Thanh pho");
	B.pin = 100;
	B.point = 0;
	B.morality = 100;

	B.credsSum = 0;
	for (int i = 0; i < 5; i++)
	{
		B.credsSum += B.hanhkhach[i].creds;
	}
}
void passengerList()
{
	cout << "==========Thiet lap ban dau - Danh sach hanh khach tren xe==========" << endl << endl;
	for (int i = 0; i < B.sohanhkhach; i++)
	{
		cout << "Hanh khach thu " << i + 1 << ":" << endl;
		cout << "Ten: " << B.hanhkhach[i].name << endl;
		cout << "Diem den: " << B.hanhkhach[i].destination << endl;
		cout << "Tinh trang the tich diem: " << B.hanhkhach[i].pointCard << endl;
		cout << "So tien cua hanh khach: " << B.hanhkhach[i].creds << endl;
	}

}
void deletePassenger(int x)
{
	for (int i = x; i < B.sohanhkhach; i++)
	{
		B.hanhkhach[i] = B.hanhkhach[i + 1];
	}
	B.sohanhkhach--;
}
void timeChecker()
{
	while (realtime.time.second >= 60)
	{
		realtime.time.first += 1;
		realtime.time.second -= 60;
	}
	while (realtime.time.first >= 24)
	{
		realtime.day += 1;
		realtime.time.first -= 24;
	}
}
void carInfo()
{
	cout <<endl << "==========Thiet lap ban dau - Tinh trang cua xe==========" << endl<< endl;

	cout << "So hanh khach: " << B.sohanhkhach << endl;
	cout << "Tinh trang tinh than hanh khach: " << B.morality << endl;
	cout << "Tong tien toan bo hanh khach tren xe: " << B.credsSum << endl;
}
void timeRightNow()
{
	cout << "Bay gio la " << realtime.time.first << " gio " << realtime.time.second << " phut" << endl;
	cout << "Ngay thu " << realtime.day << endl;
}

//Cac ham quan ly do thi
bool laDuongDiTrungLap(int x, int y) {
	for (const auto& p : adj[x]) {
		if (p.first == y) {
			return true;
		}
	}
	return false;
}
void themDuongDi(int x, int y, int w) {
	bool tonTaiDuongDi = false;
	int trongSoHienTai = -1;

	for (auto& p : adj[x]) {
		if (p.first == y) {
			tonTaiDuongDi = true;
			trongSoHienTai = p.second;
			break;
		}
	}

	if (tonTaiDuongDi) {
		cout << "duong di tu " << x << " den " << y << " da ton tai. Ban co muon thay doi trong so? (C/K): ";
		char luaChon;
		cin >> luaChon;
		if (luaChon == 'C' || luaChon == 'c') {
			// Thực hiện thay đổi trọng số
			for (auto& p : adj[x]) {
				if (p.first == y) {
					p.second = w;
				}
			}
			cout << "Trong so da duoc thay doi thannh " << w << endl; // trọng số đã dược thay đổi thành
		}
		else {
			cout << "Khong thay doi trong so." << endl;
		}
	}
	else {
		adj[x].push_back({ y, w });
		cout << "duong di da duoc them tu " << x << " đến " << y << " voi trong số " << w << endl; // duong di đã được thêm từ
	}
}
bool xoaDuongDi(int x, int y) {
	bool timThay = false;
	for (int i = 0; i < adj[x].size(); i++) {
		if (adj[x][i].first == y) {
			adj[x].erase(adj[x].begin() + i);
			timThay = true;
			break;
		}
	}
	if (timThay) {
		cout << "duong di tu " << x << " den " << y << " da đuoc xoa." << endl;
	}
	else {
		cout << "duong di khong hop le đe xoa." << endl;
	}
	return timThay;
}
//Ham tinh diem tong sau khi tro choi ket thuc
int CalculateTotalPoints() 
 {
	int totalPoints = 0;

	// Tính điểm cho hành khách
	for (int i = 0; i < B.sohanhkhach; i++) {
		if (strcmp(B.hanhkhach[i].destination, "Bien") == 0) {
			totalPoints += 100;  // Mỗi khách hàng đến đúng điểm +100 đ
		}
		else {
			totalPoints -= 100;  // Mỗi khách hàng đến sai điểm -100 đ
		}

		if (B.morality > 80) {
			totalPoints += 50;  // Mỗi khách hàng có tình trạng và sức khỏe > 80% +50 đ
		}
	}

	// Tính điểm cho xe
	if (B.damage <= 20) {
		totalPoints += 100;  // Điểm hao mòn < 20% +100 đ
	}
	else if (B.damage < 50) {
		totalPoints += 50;   // Điểm hao mòn < 50% +50 đ
	}
	else if (B.damage >= 80) {
		totalPoints -= 100;  // Điểm hao mòn >= 80% -100 đ
	}
	else if (B.damage >= 50) {
		totalPoints -= 50;   // Điểm hao mòn >= 50% -50 đ
	}

	// Thời gian về đích có thể tính thêm điểm, ví dụ +1 điểm cho mỗi phút.

	if (realtime.day == 1 && realtime.time.first < 24)
	{
		int temp = 24 - realtime.time.first;//so gio den som hon du kien
		int point = (temp * 60) + realtime.time.second; //Tong so phut den som hon du kien
		totalPoints += 2 * point;
	}

	return totalPoints;
}
//Ham kiem tra diem tiep theo muon di co hop le khong
bool kiemTraDuongDiHopLe(int x, int y) 
{
	// Kiểm tra xem đỉnh y có trong danh sách các đỉnh kề của x không
	bool hopLe = false;
	for (const auto& p : adj[x]) {
		if (p.first == y) {
			hopLe = true;
			break;
		}
	}

	if (!hopLe) 
	{
		cout << "Duong di khong hop le. Vui long nhap lai." << endl;
		return false;
	}
	return hopLe;
}
//Ham quan ly tai nguyen (pin, hao mon, thoi gian) hien tai va xuat ra man hinh
void resourceNow(int s, int sPrev, float hsg)
{
	for (const auto& k : adj[sPrev])
	{
		if (k.first == s)
		{
			B.pin -= k.second;
		}
	}
	if (B.pin > 100)
		B.pin = 100;


	for (const auto& k : adj[sPrev])
	{
		if (k.first == s)
		{
			realtime.time.second += hsg * k.second * 6;
		}
	}
	timeChecker();
	
	
	if (s <= 11)
	{
		B.damage += 1;
	}
	else if (s <= 22)
	{
		B.damage += 2;
	}
	else if (s <= 32)
	{
		B.damage += 4;
	}
	else if (s <= 43)
	{
		B.damage += 2;
	}
	cout << "X========================================X" << endl;
	cout << "| Pin con lai: " << B.pin << "\t\t\t |" << endl;
	cout << "| Bay gio la " << realtime.time.first << " gio " << realtime.time.second << " phut" << ", ngay thu " << realtime.day << "\t |" << endl;
	cout << "| Do hao mon xe: " << B.damage << "\t\t\t |" << endl;
	cout << "X========================================X" << endl << endl;
}

//Cac ham bang xep hang (file)
void writeInfoToFile(const std::string& name, int n) {
	std::ofstream file("info.txt", std::ios::app);
	if (file.is_open()) {
		file << name << " " << n << "\n";
		file.close();
	}
	else {
		std::cout << "Khong the mo file!" << std::endl;
	}
}
std::vector<std::pair<std::string, int>> readInfoFromFile() {
	std::vector<std::pair<std::string, int>> info;
	std::ifstream file("info.txt");
	if (file.is_open()) {
		std::string name;
		int number;
		while (file >> name >> number) {
			info.push_back(std::make_pair(name, number));
		}
		file.close();
	}
	else {
		std::cout << "Khong the mo file!!" << std::endl;
	}
	return info;
}
void sortInfoByCountDescending(std::vector<std::pair<std::string, int>>& info) {
	std::sort(info.begin(), info.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second > b.second;
		});
}
int ranking(){
	string name;
	int n = B.point;

	cout << "Nhap ten: ";
	cin >> name;

	writeInfoToFile(name, n);

	vector<pair<string, int>> info = readInfoFromFile();
	sortInfoByCountDescending(info);

	int rank = -1;
	for (int i = 0; i < info.size(); i++) {
		if (info[i].second == n && info[i].first == name) {
			rank = i + 1;
			break;
		}
	}

	ofstream resultFile("ranking.txt");
	if (resultFile.is_open()) {
		resultFile << "\t\t\t Bang Xep hang:" << std::endl;
		for (int i = 0; i < info.size(); i++) {
			resultFile << i + 1 << ". diem dat duoc :" << info[i].second << "\t ten nguoi choi: " << info[i].first << std::endl;
		}

		if (rank != -1) {
			resultFile << "Thu hang cua " << name << " lan choi " " la " << rank << std::endl;
		}
		else {
			resultFile << "Khong tim that thong tin " << name << " lan choi  " << n << " trong du lieu." << endl;
		}

		resultFile.close();
	}
	else {
		cout << "Khong the mo file ket qua!" << endl;
	}

	return 0;
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	nhap();
	createPassenger();
	createCarInfo();
	passengerList();
	carInfo();
	cout << "==========Hoan tat thiet lap ban dau==========" << endl ;
	cout << "\t\t~GAME START!" << endl;
	cout << "==============================================" << endl << endl;
	dijkstra(s);
	gameStar();

	fi.close();
	fo.close();
}