#include <iostream>

#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;


int rows = 4, cols = 4;




vector<vector<int>> sum(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return result;
}

vector<vector<int>> sub(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] - B[i][j];
		}
	}
	return result;
}

void print(vector<vector<int>> result) {

	int rows = result.size();
	int cols = result[0].size();
	cout << "\n";
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1)
				cout << result[i][j];
			else
				cout << result[i][j] << " ";
		}
		cout << "]\n";
	}
	cout << "\n";
}
vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));

	if (n == 1) {
		result[0][0] = A[0][0] * B[0][0];
		return result;
	}

	else {
		//Basic Attributes
		vector<vector<int>> A11, A12, A21, A22;
		vector<vector<int>> B11, B12, B21, B22;
		vector<vector<int>> C11, C12, C21, C22;
		vector<vector<int>> m1, m2, m3, m4, m5, m6, m7;
		vector<vector<int>> Result_1, Result_2;

		//Initializing Attributes
		A11.resize(n / 2, vector<int>(n / 2, 0));
		A12.resize(n / 2, vector<int>(n / 2, 0));
		A21.resize(n / 2, vector<int>(n / 2, 0));
		A22.resize(n / 2, vector<int>(n / 2, 0));

		B11.resize(n / 2, vector<int>(n / 2, 0));
		B12.resize(n / 2, vector<int>(n / 2, 0));
		B21.resize(n / 2, vector<int>(n / 2, 0));
		B22.resize(n / 2, vector<int>(n / 2, 0));

		C11.resize(n / 2, vector<int>(n / 2, 0));
		C12.resize(n / 2, vector<int>(n / 2, 0));
		C21.resize(n / 2, vector<int>(n / 2, 0));
		C22.resize(n / 2, vector<int>(n / 2, 0));

		m1.resize(n / 2, vector<int>(n / 2, 0));
		m2.resize(n / 2, vector<int>(n / 2, 0));
		m3.resize(n / 2, vector<int>(n / 2, 0));
		m4.resize(n / 2, vector<int>(n / 2, 0));
		m5.resize(n / 2, vector<int>(n / 2, 0));
		m6.resize(n / 2, vector<int>(n / 2, 0));
		m7.resize(n / 2, vector<int>(n / 2, 0));

		//Resultant Vectors
		Result_1.resize(n / 2, vector<int>(n / 2, 0));
		Result_2.resize(n / 2, vector<int>(n / 2, 0));

		//Dividing the Matrices into 4 Sub-Matrices:
		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + n / 2];
				A21[i][j] = A[i + n / 2][j];
				A22[i][j] = A[i + n / 2][j + n / 2];

				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + n / 2];
				B21[i][j] = B[i + n / 2][j];
				B22[i][j] = B[i + n / 2][j + n / 2];
			}
		}

           /** 
              M1 = (A11 + A22)(B11 + B22)
              M2 = (A21 + A22) B11
              M3 = A11 (B12 - B22)
              M4 = A22 (B21 - B11)
              M5 = (A11 + A12) B22
              M6 = (A21 - A11) (B11 + B12)
              M7 = (A12 - A22) (B21 + B22)
            **/



		Result_1 = sum(A11, A22); 
		Result_2 = sum(B11, B22); 
		m1 = strassen(Result_1, Result_2); 

		Result_1 = sum(A21, A22); 
		m2 = strassen(Result_1, B11); 

		Result_2 = sub(B12, B22); 
		m3 = strassen(A11, Result_2); 

		Result_2 = sub(B21, B11);
		m4 = strassen(A22, Result_2); 

		Result_1 = sum(A11, A12); 
		m5 = strassen(Result_1, B22); 

		Result_1 = sub(A21, A11); 
		Result_2 = sum(B11, B12); 
		m6 = strassen(Result_1, Result_2); 

		Result_1 = sub(A12, A22); 
		Result_2 = sum(B21, B22); 
		m7 = strassen(Result_1, Result_2); 

		 /**now
              C11 = M1 + M4 - M5 + M7
              C12 = M3 + M5
              C21 = M2 + M4
              C22 = M1 - M2 + M3 + M6
            **/ 
            
            
            
		C12 = sum(m3, m5); 
		C21 = sum(m2, m4); 

		Result_1 = sum(m1, m4); 
		Result_2 = sum(Result_1, m7); 
		C11 = sub(Result_2, m5); 

		Result_1 = sum(m1, m3); 
		Result_2 = sum(Result_1, m6); 
		C22 = sub(Result_2, m2); 

		
		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				result[i][j] = C11[i][j];
				result[i][j + n / 2] = C12[i][j];
				result[i + n / 2][j] = C21[i][j];
				result[i + n / 2][j + n / 2] = C22[i][j];
			}
		}
	}
	
	return result;
}

vector<vector<int>> iterative(vector<vector<int>> A, vector<vector<int>> B) {

	int rows = A.size();
	int cols = A[0].size();
	int colsb = B[0].size();

	vector<vector<int>> result;
	result.resize(rows, vector<int>(colsb, 0));
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < colsb; j++) {
		int sum = 0;
		for (int k = 0; k < cols; k++)
			sum = sum + (A[i][k] * B[k][j]);
		result[i][j] = sum;
	}
	return result;
}





int main()
{
	vector<vector<int>> A;
	vector<vector<int>> B;

	clock_t tstart;
	double t_time;

	cout << " The Matrix multiplication program :- " << endl;
	

	A.resize(rows, vector<int>(cols, 0));
	B.resize(rows, vector<int>(cols, 0));

	srand(time(NULL));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			A[i][j] = rand() % 10 + 1;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			B[i][j] = rand() % 10 + 1;
		}
	}

	cout << "\nThe randomly Generated Matrix 1 is: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nThe randomly Generated Matrix 2 is: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << B[i][j] << " ";
		}
		cout << endl;
	}



	cout <<" 'Strassen's' Matrix is: " << endl;
	

	tstart = clock();
	print(strassen(A, B));
	t_time = (clock() - tstart) / (double)CLOCKS_PER_SEC;

	cout << "\nt_time of Strassen's Multipliation: " << t_time << "sec." << endl;

	
	cout << " 'Iterative' Matrix is: " << endl;
	
	
	tstart = clock();
	print(iterative(A, B));
	t_time = (clock() - tstart) / (double)CLOCKS_PER_SEC;

	cout << "\nt_time of Basic Multipliation: " << t_time << "sec." <<endl ;

	system("PAUSE");
}