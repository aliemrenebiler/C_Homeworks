#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 30000

void sieveOfEratosthenes(int limit, bool sieve[SIZE]){
	int n, m;
	
	//tüm sayýlarý baþta asal iþaretlenmesi
	for(n=2 ; n <= limit ; n++){
		sieve[n] = true;
	}
	
	//asal sayýlarýn katlarýnýn asal deðil iþaretlenmesi
	for(n=2 ; n*n < limit ; n++){
		if (sieve[n] == true){
			for(m=n*n ; m < limit ; m = m + n){
				sieve[m] = false;
			}
		}
	}
}

void printPrimes(int limit, bool sieve[SIZE]){
	int x = 0, n;
	printf("\nAsal Sayilar:\n");
	for (n = 2; n < limit; n++){
		//her satýra 8 adet asal sayý yazdýrýlmasý
		if(sieve[n] == true){
			x = x + 1;
			printf("%d\t", n);
			if(x == 8){
				printf("\n");
				x = 0;
			}
		}
	}
}

int main(){
	//limit: bulunmasýný istediðimiz aralýðýn üst sýnýrý
	//sieve[]: deðerlerin asal veya asal deðil olarak iþaretleneceði dizi
	//sieve[n] = true (asal)
	//sieve[n] = false (asal deðil)
	int limit;
	bool sieve[SIZE];
	double duration; //geçen zaman
	struct timespec start, end; //baþlangýç ve bitiþ zamaný
	
	//pozitif ve tamsayý bir limit deðeri girilmesi
	printf("-----");
	printf("\n\nEratosthenes Kalburu (Sieve of Eratosthenes)");
	printf("\n\n2 ile istediginiz araliktaki tum asal sayilari bulun.");
	printf("\n\n-----");
	printf("\n\nAralik Ust Limiti: ");
	scanf("%d", &limit);
	while(limit <= 1){
		printf("(!) Limit deðeri 1'den buyuk pozitif bir tamsayi olmalidir.");
		printf("\nLutfen uygun bir limit degeri giriniz: ");
		scanf("%d", &limit);
	}
	
	//baþlangýç zamanýnýn belirlenmesi
	clock_gettime(CLOCK_MONOTONIC, &start); 

	//asal sayýlarýn bulunmasý
	sieveOfEratosthenes(limit, sieve);
	
	//bitiþ zamanýnýn belirlenmesi
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	//asal sayýlarýn yazdýrýlmasý
	printPrimes(limit, sieve);
	
	//geçen sürenin hesaplanmasý
	duration = (end.tv_sec - start.tv_sec) * 1e9;
	duration = (duration + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	
	//hesaplama süresinin yazdýrýlmasý
	printf("\n\nHesaplama Suresi: %f sn", duration);
}







