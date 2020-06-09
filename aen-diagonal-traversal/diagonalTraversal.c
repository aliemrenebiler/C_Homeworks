#include <stdio.h>

#define MAXSIZE 100

//matrisi diagonal olarak yazd�ran algoritma

int initializeMatrix(int matrix[MAXSIZE][MAXSIZE], int n){
	int i, j, k=1;
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++){
			matrix[i][j] = k;
			k++;
		}
	}
}

void printMatrix(int matrix[MAXSIZE][MAXSIZE], int n){
	int i, j;
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++){
			printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void diagonalTraversal(int matrix[MAXSIZE][MAXSIZE], int n){
	int i, j, k=0;
	for(i=0 ; i<n*2-1 ; i++){
		if(i>=n){
			k++;
		}
		for(j=k ; j<i+1-k ; j++){
			printf("%4d ", matrix[j][i-j]);
		}
		printf("\n");
	}
}

int main(){
	int n;
	int matrix[MAXSIZE][MAXSIZE];
	printf(" - DIAGONAL TRAVERSAL - ");
	printf("\n\n Kare matrisin satir ve sutun sayisi: ");
	scanf("%d", &n);
	initializeMatrix(matrix, n); //matris olu�turma
	printf("\n Matris:\n");
	printMatrix(matrix, n); //matrisi yazd�rma
	printf("\n Diagonal Traversal:\n");
	diagonalTraversal(matrix, n); //diagonal yazd�rma
	return 0;
}
