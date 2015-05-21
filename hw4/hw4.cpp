#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 10002
#define INMAX 1000000
using namespace std;

class DATA {
public:
	DATA();
	int YN;
	double *condition;
};

DATA::DATA() {condition = new double[MAX];}

void Read(vector<DATA> &data, int& max_index, FILE *file)
{
	char *input = new char[INMAX];
	
	while (fgets(input, INMAX, file) != 0) {
		DATA temp_data;
		int index = 0;
		double index_value = 0;
		input[strlen(input)-1] = '\0';
		char *temp = strtok(input, " ");
		temp_data.YN = atoi(temp);
		temp = strtok(NULL, ":");
		while (temp != NULL) {
			index = atoi(temp);
			temp = strtok(NULL, " ");
			index_value = atof(temp);
			temp_data.condition[index] = index_value;
			temp = strtok(NULL, ":");
			if (index > max_index) max_index = index;
		}
		data.push_back(temp_data);
	}
	
}

class Compare { 
public:
	int cond_index;
	Compare(int i) {this->cond_index = i;};
	bool operator()(const DATA &a, const DATA &b) {return a.condition[cond_index] < b.condition[cond_index];};
};

double Confusion(int Y, int N) {return 1-pow((double)Y/(Y+N), 2)-pow((double)N/(Y+N), 2);}

void PrintTab(int n) {for (int i = 0 ; i < n ; i++) printf("\t");}

void Div(vector<DATA> &data, int max_index, double std_confusion, int depth)
{
	double min_confusion = 1;	
	double temp_confusion = 0;
	double div_point = 0; int div_cond = -1, div_pos, yn = 0;
	int size = data.size();
	int allsum_Y = 0;
	for (int i = 0 ; i < size ; i++) if (data[i].YN > 0) allsum_Y++; //find sum of Y
	for (int cond = 0 ; cond <= max_index ; cond++) { // find the smallest confusion
		Compare cmp(cond);
		sort(data.begin(), data.end(), cmp);
		int frontsum_Y = 0, backsum_Y = 0;
		for (int pos = 1 ; pos < size ; pos++) { // pos represent the number of front data
			if (data[pos-1].YN > 0) frontsum_Y++;
			backsum_Y = allsum_Y - frontsum_Y;
			if (fabs(data[pos-1].condition[cond] - data[pos].condition[cond]) >= 0.000001) {
				temp_confusion = (pos*Confusion(frontsum_Y, pos-frontsum_Y)+(size-pos)*Confusion(backsum_Y, size-pos-backsum_Y))/(double)size;
				//cout << temp_confusion << endl;
				if (temp_confusion < min_confusion) {
					min_confusion = temp_confusion;
					div_point = (data[pos].condition[cond]+data[pos-1].condition[cond])/2;
					div_cond = cond;
					div_pos = pos;
				}
			}
		}
	}
	if (Confusion(allsum_Y, size-allsum_Y) <= std_confusion+0.000001 || fabs(min_confusion - 1) < 0.000001) {
		PrintTab(depth);printf("return %d;\n", (allsum_Y >= size-allsum_Y)? 1 : -1);
		return;
	}
	vector<DATA> front_data; vector<DATA> back_data;
	Compare cmp(div_cond);
	sort (data.begin(), data.end(), cmp);
	for (int i = 0 ; i < div_pos ; i++) front_data.push_back(data[i]);
	for (int i = div_pos ; i < size ; i++) back_data.push_back(data[i]);
	PrintTab(depth); printf("if(attr[%d] < %f){\n", div_cond, div_point);
	Div(front_data, max_index, std_confusion, depth+1);
	PrintTab(depth); printf("}\n");
	PrintTab(depth); printf("else{\n");
	Div(back_data, max_index, std_confusion, depth+1);
	PrintTab(depth); printf("}\n");
}

int main(int argc, char const *argv[])
{
	vector<DATA> data;
	int max_index = 0;
	FILE *file = fopen(argv[1], "r");
	Read(data, max_index, file);
	fclose(file);
	printf("int tree_predict(double *attr){\n");
	Div(data, max_index, atof(argv[2]), 1);
	printf("}\n");
	return 0;
}