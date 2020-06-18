#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 30000

void sieveOfAtkin(int limit, bool sieve[SIZE]){
	//n: denenecek de�er
	int x, y, n;
	
	//t�m say�lar� ba�ta asal de�il i�aretlenmesi
	for(n=2 ; n <= limit ; n++){
		sieve[n] = false;
	}
	//limit=2 durumu
	if(limit >= 2){
		sieve[2] = true;
	}
	//limit=3 durumu
	if(limit >= 3){
		sieve[3] = true;
	}
	
	//x=1, y=1'den ba�lanarak �artlar�n denenmesi
	for(x=1 ; x*x < limit ; x++){
		for(y=1 ; y*y < limit ; y++){
			
			//4*x*x + y*y mod 12 kural�
			n = 4*x*x + y*y;
			if(n <= limit && (n % 12 == 1 || n % 12 == 5)){
				sieve[n] ^= true;
			}
			//3*x*x + y*y mod 12 kural�
			n = 3*x*x + y*y;
			if(n <= limit && n % 12 == 7){
				sieve[n] ^= true;
			}
			//3*x*x - y*y mod 12 kural�
			n = 3*x*x - y*y;
			if(x>y && n <= limit && n % 12 == 11){
				sieve[n] ^= true;
			}
			
		}
	}
	
	//asal bulunan say�lar�n karesinin katlar�n�n ��kar�lmas�
	for (n = 5 ; n*n < limit ; n++){
        if (sieve[n] == true){
            for (x = n*n ; x < limit ; x = x + n*n){
            	sieve[x] = false;
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
	printf("\n\nAtkin Kalburu (Sieve of Atkin)");
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
	sieveOfAtkin(limit, sieve);
	
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







