#include <stdio.h>

//istenilen adým kadar pascal üçgenini yazdýran algoritma

void computePascal(int N){
	int arr[N], temp1, temp2;
	int i, j;
	arr[0] = 1;
	
	for(i=0 ; i<N ; i++){
		//satýr yazdýrma
		for(j=0 ; j<i+1 ; j++){
			printf("%d ", arr[j]);
		}
		printf("\n");
		
		//satýr hesaplama
		temp1 = arr[0];
		temp2 = arr[1];
		for(j=0 ; j<i ; j++){
			arr[j+1] = temp1 + temp2;
			temp1 = temp2;
			temp2 = arr[j+2];
		}
		arr[i+1] = 1;
	}
}

int main(){
	int N;
	printf("\n - PASCAL UCGENI - \n");
	printf("\n Hesaplanacak satir sayisi = ");
	scanf("%d", &N);
	printf("\n");
	computePascal(N); //Pascal üçgenini hesaplama ve yazdýrma
	return 0;
}
