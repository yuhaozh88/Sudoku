//sudoku 数独游戏
//@ author yuhaozh88
#include<iostream>
using namespace std;
const int N = 10;

class element
{
public:
	bool ele[N];
public:
	element() {
		for (int i = 1; i < N; i++) {
			ele[i] = true;
		}
		ele[0] = false;
	}
};
class sudoku
{
public :
	int matrix[N][N];
	element** record;
public :
	sudoku(int in_matrix[N][N]);
	int get_district(int row,int col);
	int find_answer(int in_row,int in_col);
	void set();
	void print();
};

sudoku::sudoku(int in_matrix[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = in_matrix[i][j];
		}
	}
	record = new element*[3];
	for (int i = 0; i < 3; i++) {
		record[i] = new element[N];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j < N; j++) {
			for (int k = 1; k < N; k++) {
				record[i][j].ele[k] = true;
			}
		}
	}
};

int sudoku::get_district(int row, int col)
{//用于获得某个格所处的宮数
	if (row>=1&&row<=3) {
		if (col >= 1 && col <= 3) {
			return 1;
		}
		else if (col >= 4 && col <= 6) {
			return 2;
		}
		else return 3;
	}
	else if (row >= 4 && row <= 6) {
		if (col >= 1 && col <= 3) {
			return 4;
		}
		else if (col >= 4 && col <= 6) {
			return 5;
		}
		else return 6;
	}
	else {
		if (col >= 1 && col <= 3) {
			return 7;
		}
		else if (col >= 4 && col <= 6) {
			return 8;
		}
		else return 9;
	};
}


void sudoku::set()
{
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			if (matrix[i][j] != 0) {
				int temp = matrix[i][j];
				int block = get_district(i, j);
				record[0][i].ele[temp] = false;
				record[1][j].ele[temp] = false;
				record[2][block].ele[temp] = false;
			}
		}
	}
};

int sudoku::find_answer(int in_row,int in_col)
{
	if (in_row == N) {//所有查找全部完成
		return 0;
	}
	else if (in_row < N&&in_col == N) {//列查找完成
		return 1;
	}
	else {//填入的位置合法
		if (matrix[in_row][in_col] == 0) {//目前单元格内没有被填入数字
			int block = get_district(in_row, in_col);
			bool found = false;
			for (int num = 1; num < N; num++) {
				if (record[0][in_row].ele[num] && record[1][in_col].ele[num] && record[2][block].ele[num]) {//num可以填入该单元格
					matrix[in_row][in_col] = num;
					record[0][in_row].ele[num] = false;
					record[1][in_col].ele[num] = false;
					record[2][block].ele[num] = false;
					found = true;
					cout << "(" << in_row << "," << in_col << ")" << "填入" << num << endl;
					int type = find_answer(in_row, in_col+1);
					if (type == -1) {//下一个单元格无法填入，需要回溯调整
						record[0][in_row].ele[num] = true;
						record[1][in_col].ele[num] = true;
						record[2][block].ele[num] = true;
						matrix[in_row][in_col] = 0;
						found = false;
						cout << "(" << in_row << "," << in_col << ")" << "删除" << num << endl;
					}
					else if (type == 1) {//该行已经填充完毕
						int type=find_answer(in_row+1 , 1);
						if (type == -1) {
							record[0][in_row].ele[num] = true;
							record[1][in_col].ele[num] = true;
							record[2][block].ele[num] = true;
							matrix[in_row][in_col] = 0;
							found = false;
							cout << "(" << in_row << "," << in_col << ")" << "删除" << num << endl;
						}
						else if (type == 0) {
							return 0;
						}
					}
					else if (type == 0) {
						return 0;
					}
				}
			}
			if (!found) {
				cout << "(" << in_row << "," << in_col << ")" << "无法填入" << endl;
				return -1;
			}
		}
		else {
			int type=find_answer(in_row, in_col+1 );
			if (type == 0) {
				return 0;
			}
			else if (type == -1) {
				return -1;
			}
			else if (type == 1) {
				find_answer(in_row+1 , 1);
			}
		}
	}
};

void sudoku::print()
{
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}



int main()
{
	int arr[10][10] = {
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,9,0,0,3,0,0,4,0,5 },
		{ 0,7,4,0,0,0,0,0,3,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,1,0,8,0,6,0,0,0 },
		{ 0,4,9,0,0,0,0,0,8,3 },
		{ 0,0,0,0,4,0,1,0,9,0 },
		{ 0,0,2,0,0,0,0,0,0,0 },
		{ 0,0,7,0,0,0,0,0,6,9 },
		{ 0,1,0,9,0,0,0,0,0,7 }
	};
	sudoku s(arr);
	s.set();
	cout << s.find_answer(1, 1) << endl;
	s.print();
}