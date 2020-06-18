#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 30000

void sieveOfAtkin(int limit, bool sieve[SIZE]){
	//n: denenecek deðer
	int x, y, n;
	
	//tüm sayýlarý baþta asal deðil iþaretlenmesi
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
	
	//x=1, y=1'den baþlanarak þartlarýn denenmesi
	for(x=1 ; x*x < limit ; x++){
		for(y=1 ; y*y < limit ; y++){
			
			//4*x*x + y*y mod 12 kuralý
			n = 4*x*x + y*y;
			if(n <= limit && (n % 12 == 1 || n % 12 == 5)){
				sieve[n] ^= true;
			}
			//3*x*x + y*y mod 12 kuralý
			n = 3*x*x + y*y;
			if(n <= limit && n % 12 == 7){
				sieve[n] ^= true;
			}
			//3*x*x - y*y mod 12 kuralý
			n = 3*x*x - y*y;
			if(x>y && n <= limit && n % 12 == 11){
				sieve[n] ^= true;
			}
			
		}
	}
	
	//asal bulunan sayýlarýn karesinin katlarýnýn çýkarýlmasý
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
	printf("\n\nAtkin Kalburu (Sieve of Atkin)");
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
	sieveOfAtkin(limit, sieve);
	
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







