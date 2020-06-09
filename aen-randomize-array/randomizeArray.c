
#include <stdio.h>
#include <time.h>
#define SIZE 100

//oluþturulan diziyi karýþtýran algoritma

void printArray(int n, int arr[]){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", arr[i]);
	}
}

void randomize(int n, int arr[]){
	int x, temp, i;
	for(i=0; i<n; i++){
		x = rand() % n;
		temp = arr[i];
		arr[i] = arr[x];
		arr[x] = temp;
	}
}

int main(){
	int arr[SIZE], n, i;
	printf("DIZININ ELEMANLARINI KARISTIRMA");
	printf("\nDizinin eleman sayisi: ");
	scanf("%d", &n);
	
	//random dizi elemanlarý oluþturma
	srand(time(NULL));
	for(i=0; i<n; i++){
		arr[i] = rand() % 100;
	}
	
	printf("\n");
	printArray(n, arr); //yazdýrma
	randomize(n, arr); //karýþtýrma
	printf("\n");
	printArray(n, arr); //bir daha yazdýrma
	
	return 0;
}















