#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 30000

void sieveOfEratosthenes(int limit, bool sieve[SIZE]){
	int n, m;
	
	//t�m say�lar� ba�ta asal i�aretlenmesi
	for(n=2 ; n <= limit ; n++){
		sieve[n] = true;
	}
	
	//asal say�lar�n katlar�n�n asal de�il i�aretlenmesi
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
		//her sat�ra 8 adet asal say� yazd�r�lmas�
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
	//limit: bulunmas�n� istedi�imiz aral���n �st s�n�r�
	//sieve[]: de�erlerin asal veya asal de�il olarak i�aretlenece�i dizi
	//sieve[n] = true (asal)
	//sieve[n] = false (asal de�il)
	int limit;
	bool sieve[SIZE];
	double duration; //ge�en zaman
	struct timespec start, end; //ba�lang�� ve biti� zaman�
	
	//pozitif ve tamsay� bir limit de�eri girilmesi
	printf("-----");
	printf("\n\nEratosthenes Kalburu (Sieve of Eratosthenes)");
	printf("\n\n2 ile istediginiz araliktaki tum asal sayilari bulun.");
	printf("\n\n-----");
	printf("\n\nAralik Ust Limiti: ");
	scanf("%d", &limit);
	while(limit <= 1){
		printf("(!) Limit de�eri 1'den buyuk pozitif bir tamsayi olmalidir.");
		printf("\nLutfen uygun bir limit degeri giriniz: ");
		scanf("%d", &limit);
	}
	
	//ba�lang�� zaman�n�n belirlenmesi
	clock_gettime(CLOCK_MONOTONIC, &start); 

	//asal say�lar�n bulunmas�
	sieveOfEratosthenes(limit, sieve);
	
	//biti� zaman�n�n belirlenmesi
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	//asal say�lar�n yazd�r�lmas�
	printPrimes(limit, sieve);
	
	//ge�en s�renin hesaplanmas�
	duration = (end.tv_sec - start.tv_sec) * 1e9;
	duration = (duration + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	
	//hesaplama s�resinin yazd�r�lmas�
	printf("\n\nHesaplama Suresi: %f sn", duration);
}







