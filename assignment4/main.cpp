#include<iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
//define max as 2^31 - 1
#define max 2147483647

//store the whole graph
typedef struct {
	vector<vector<int> > arcs;
	int vertex_num, arc_num;
}Graph;

//use Entry to sort
struct {
	int head;
	int tail;
	int direct_distance;
}Entry[100];

//use dynamic structure vector instead of array
vector<int> vertex_vector;

int kruskal_destory(Graph g);
int kruskal_connect(Graph g);

//use this method to get and print the final cost
void get_and_print_cost(string value_str, string connect_str, string destory_str, Graph& g) {
	vector<vector<int> > matrix;
	vector<vector<int> > matrix_destory;
	g.vertex_num = 0;
	g.arc_num = 0;

	std::stringstream s_v(value_str);
	std::string str_v;

	while (getline(s_v, str_v, ',')) {
		int length = str_v.length();
		vector<int> tmp_vec;
		g.vertex_num++;

		for (int i = 0; i < length; i++)
		{
			tmp_vec.push_back(str_v[i] - 48);

			if (str_v[i] == 49) {
				g.arc_num++;
			}
		}

		matrix.push_back(tmp_vec);
		tmp_vec.clear();
	}

	g.arc_num = g.arc_num / 2;

	std::stringstream s_d(destory_str);
	std::string str_d;

	while (getline(s_d, str_d, ',')) {
		int length = str_d.length();
		vector<int> tmp_vec;

		for (int i = 0; i < length; i++)
		{
			if (str_d[i] < 91)
			{
				tmp_vec.push_back(str_d[i] - 65);
			}
			else
			{
				tmp_vec.push_back(str_d[i] - 71);
			}
		}

		matrix_destory.push_back(tmp_vec);
		tmp_vec.clear();
	}

	for (int i = 0; i < g.vertex_num; i++) {
		vector<int> tmp;

		for (int j = 0; j < g.vertex_num; j++) {
			tmp.push_back(max);
		}

		g.arcs.push_back(tmp);
		tmp.clear();
	}

	int tmp = 0;

	for (int i = 0; i < g.vertex_num; i++) {
		for (int j = 0; j < g.vertex_num; j++) {
			int i_tmp = i;
			int j_tmp = j;
			if (i_tmp > j_tmp)
			{
				if (matrix[i][j] == 1)
				{
					g.arcs[i][j] = max - matrix_destory[i][j];
					g.arcs[j][i] = max - matrix_destory[i][j];
					Entry[tmp].direct_distance = max - matrix_destory[i][j];
					Entry[tmp].head = i;
					Entry[tmp].tail = j;
					tmp++;
				}
			}
		}
	}

	//the cost of destoring redundant edge
	int val_destory = kruskal_destory(g);

	vector<vector<int> > matrix_connect;

	std::stringstream s_c(connect_str);
	std::string str_c;

	while (getline(s_c, str_c, ',')) {
		int length = str_c.length();
		vector<int> tmp_vec;

		for (int i = 0; i < length; i++)
		{
			if (str_c[i] < 91)
			{
				tmp_vec.push_back(str_c[i] - 65);
			}
			else
			{
				tmp_vec.push_back(str_c[i] - 71);
			}
		}

		matrix_connect.push_back(tmp_vec);
		tmp_vec.clear();
	}

	g.arc_num = g.vertex_num;

	for (int i = 0; i < g.vertex_num; i++) {
		vector<int> tmp;

		for (int j = 0; j < g.vertex_num; j++) {
			tmp.push_back(max);
		}

		g.arcs.push_back(tmp);
		tmp.clear();
	}

	tmp = 0;

	for (int i = 0; i < g.vertex_num; i++) {
		for (int j = 0; j < g.vertex_num; j++) {
			int i_tmp = i;
			int j_tmp = j;
			if (i_tmp > j_tmp)
			{
				g.arcs[i][j] = matrix_connect[i][j];
				g.arcs[j][i] = matrix_connect[i][j];
				Entry[tmp].direct_distance = matrix_connect[i][j];
				Entry[tmp].head = i;
				Entry[tmp].tail = j;
				tmp++;
			}
		}
	}

	//the cost of connect left edge
	int val_connect = kruskal_connect(g);

	cout << val_destory + val_connect << endl;
}

//the number to be sort is different from connect part
void sort_destory(Graph g) {
	int m = g.arc_num - 2;
	bool flag = 1;

	while (m > 0 && flag == 1) {
		flag = 0;

		for (int i = 0; i <= m; i++) {
			if (Entry[i].direct_distance > Entry[i + 1].direct_distance)
			{
				flag = 1;

				char head_tmp = Entry[i].head;
				Entry[i].head = Entry[i + 1].head;
				Entry[i + 1].head = head_tmp;

				char tail_tmp = Entry[i].tail;
				Entry[i].tail = Entry[i + 1].tail;
				Entry[i + 1].tail = tail_tmp;

				int distance_tmp = Entry[i].direct_distance;
				Entry[i].direct_distance = Entry[i + 1].direct_distance;
				Entry[i + 1].direct_distance = distance_tmp;
			}
		}

		m--;
	}
}

void sort_connect(Graph g) {
	int m = g.arc_num * (g.arc_num - 1) / 2 - 2;
	bool flag = 1;

	while (m > 0 && flag == 1) {
		flag = 0;

		for (int i = 0; i <= m; i++) {
			if (Entry[i].direct_distance > Entry[i + 1].direct_distance)
			{
				flag = 1;

				char head_tmp = Entry[i].head;
				Entry[i].head = Entry[i + 1].head;
				Entry[i + 1].head = head_tmp;

				char tail_tmp = Entry[i].tail;
				Entry[i].tail = Entry[i + 1].tail;
				Entry[i + 1].tail = tail_tmp;

				int distance_tmp = Entry[i].direct_distance;
				Entry[i].direct_distance = Entry[i + 1].direct_distance;
				Entry[i + 1].direct_distance = distance_tmp;
			}
		}

		m--;
	}
}

int kruskal_destory(Graph g) {
	int head, tail, vertex_vextor_ele1, vertex_vextor_ele2;
	int val = 0;
	sort_destory(g);

	for (int i = 0; i < g.vertex_num; i++) {
		vertex_vector.push_back(i);
	}

	for (int i = 0; i < g.arc_num; i++) {
		head = Entry[i].head;
		tail = Entry[i].tail;
		vertex_vextor_ele1 = vertex_vector[head];
		vertex_vextor_ele2 = vertex_vector[tail];

		if (vertex_vextor_ele1 != vertex_vextor_ele2) {

			for (int j = 0; j < g.vertex_num; j++) {
				if (vertex_vector[j] == vertex_vextor_ele2)
				{
					vertex_vector[j] = vertex_vextor_ele1;
				}
			}
		}
		else
		{
			val = val + (max - Entry[i].direct_distance);
		}
	}

	return val;
}

//do not need to init vertex_vector
int kruskal_connect(Graph g) {
	int head, tail, vertex_vextor_ele1, vertex_vextor_ele2;
	int val = 0;
	sort_connect(g);

	for (int i = 0; i < g.arc_num * (g.arc_num - 1) / 2; i++) {
		head = Entry[i].head;
		tail = Entry[i].tail;
		vertex_vextor_ele1 = vertex_vector[head];
		vertex_vextor_ele2 = vertex_vector[tail];

		if (vertex_vextor_ele1 != vertex_vextor_ele2) {
			val = val + Entry[i].direct_distance;

			for (int j = 0; j < g.vertex_num; j++) {
				if (vertex_vector[j] == vertex_vextor_ele2)
				{
					vertex_vector[j] = vertex_vextor_ele1;
				}
			}
		}
	}

	return val;
}

int main() {
	//get input
	string value_str;
	string connect_str;
	string destory_str;
	cin >> value_str;
	cin >> connect_str;
	cin >> destory_str;

	Graph g;
	get_and_print_cost(value_str, connect_str, destory_str, g);

	return 0;
}
