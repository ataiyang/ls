// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"iostream"
#include "time.h"
#include "fstream"
using namespace std;
int judge(int a[9][9], int i, int j)
{
	int m, n, p, q;
	for (m = 0, n = j; m < 9; m++) {//判断行里是否有重复的数
		if (a[m][n] == a[i][j] && m != i) {
			return 0;
		}
	}
	for (m = i, n = 0; n < 9; n++) {//判断列里是否有重复的数
		if (a[m][n] == a[i][j] && n != j) {
			return 0;
		}
	}
	p = i / 3;
	q = j / 3;
	for (m = p * 3, n = q * 3; m < (p + 1) * 3;) {//判断本宫里是否有重复的数
		if (a[m][n] == a[i][j] && m != i&&n != j) {
			return 0;
		}
		else {
			if (n < (q * 3 + 2)) {
				n++;
			}
			else {
				n = q * 3;
				m++;
			}
		}
	}
	return 1;
}
int main()
{
	ofstream outfile;
	outfile.open("sudoku.txt");
	srand((int)time(NULL));
	int l, n,x;
	cin >> n;
	for (l = 0; l < n; l++) {
		int a[9][9] = { 0 };//九宫格初始化
		int i, j, m, n, x, k = 0;
		for (i = 0, j = 0; i != 9;) {
			if (i == 0 && j == 0) {//学号后2位为23，所以是6
				a[i][j] = 6;
				k = 1;
			}
			if (k == 0) {
				a[i][j] = rand() % 9 + 1;//填当前格
			}
			if (judge(a, i, j)) {
				if (j < 8) {
					j++;
					k = 0;
				}
				else {
					i++;
					j = 0;
					k = 0;
				}
			}
			else if (k<50) {//k用来记录当前格错误次数，当超过50个时，从头开始
				k++;
				a[i][j] = rand() % 9 + 1;
			}
			else if (k == 50) {
				k = 0;
				for (i = 0, j = 0; i < 9;) {//重新初始化
					a[i][j] = 0;
					if (j < 8) { j++; }
					else {
						j = 0;
						i++;
					}
				}
				i = 0;
				j = 0;
			}
		}
		for (m = 0, n = 0; m < 9;) {//输出到文件
			if (n < 8) {
				outfile << a[m][n] << " ";
				n++;
			}
			else {
				outfile << a[m][n] << endl;
				m++;
				n = 0;
			}
		}
		outfile << endl;
	}
	if (l == n) cout << "finish";
	cin >> x;
    return 0;
}

