#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 30000

void sieveOfAtkin(int i, int limit[], bool sieve[SIZE]){
	//n: denenecek deðer
	int x, y, n;
	
	//tüm sayýlarý baþta asal deðil iþaretlenmesi
	for(n=2 ; n <= limit[i] ; n++){
		sieve[n] = false;
	}
	//limit=2 durumu
	if(limit[i] >= 2){
		sieve[2] = true;
	}
	//limit=3 durumu
	if(limit[i] >= 3){
		sieve[3] = true;
	}
	
	//x=1, y=1'den baþlanarak þartlarýn denenmesi
	for(x=1 ; x*x < limit[i] ; x++){
		for(y=1 ; y*y < limit[i] ; y++){
			
			//4*x*x + y*y mod 12 kuralý
			n = 4*x*x + y*y;
			if(n <= limit[i] && (n % 12 == 1 || n % 12 == 5)){
				sieve[n] ^= true;
			}
			//3*x*x + y*y mod 12 kuralý
			n = 3*x*x + y*y;
			if(n <= limit[i] && n % 12 == 7){
				sieve[n] ^= true;
			}
			//3*x*x - y*y mod 12 kuralý
			n = 3*x*x - y*y;
			if(x>y && n <= limit[i] && n % 12 == 11){
				sieve[n] ^= true;
			}
			
		}
	}
	
	//asal bulunan sayýlarýn karesinin katlarýnýn çýkarýlmasý
	for (n = 5 ; n*n < limit[i] ; n++){
        if (sieve[n] == true){
            for (x = n*n ; x < limit[i] ; x = x + n*n){
            	sieve[x] = false;
			}
        } 
    }
}

void printPrimes(int i, int limit[], bool sieve[SIZE]){
	int x = 0, n;
	printf("\n\nLimit = %d", limit[i]);
	printf("\nAsal Sayilar:\n");
	for (n = 2; n < limit[i]; n++){
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
	//limit[]: bulunmasýný istediðimiz aralýðýn üst sýnýrý
	//sieve[]: deðerlerin asal veya asal deðil olarak iþaretleneceði dizi
	//sieve[n] = true (asal)
	//sieve[n] = false (asal deðil)
	int limit[8], i, j, max;
	bool sieve[SIZE];
	double duration[8]; //geçen zamanlar
	struct timespec start, end; //baþlangýç ve bitiþ zamanlarý
	
	//pozitif ve tamsayý bir limit deðeri girilmesi
	printf("-----");
	printf("\n\nAtkin Kalburu (Sieve of Atkin)");
	printf("\n\n2 ile istediginiz araliktaki tum asal sayilari bulun.");
	printf("\n\n-----");
	printf("\n\nAraliklarin Ust Limitleri\n");
	for(i=0 ; i<8 ; i++){
		printf("Limit %d: ", i+1);
		scanf("%d", &limit[i]);
		while(limit[i] <= 1){
			printf("(!) Limit deðeri 1'den buyuk pozitif bir tamsayi olmalidir.");
			printf("\nLutfen uygun bir limit degeri giriniz: ");
			scanf("%d", &limit[i]);
		}
	}
	
	for(i=0 ; i<8 ; i++){
		//baþlangýç zamanýnýn belirlenmesi
		clock_gettime(CLOCK_MONOTONIC, &start); 
	
		//asal sayýlarýn bulunmasý
		sieveOfAtkin(i, limit, sieve);
		
		//bitiþ zamanýnýn belirlenmesi
		clock_gettime(CLOCK_MONOTONIC, &end);
		
		//asal sayýlarýn yazdýrýlmasý
		printPrimes(i, limit, sieve);
		
		//geçen sürenin hesaplanmasý
		duration[i] = (end.tv_sec - start.tv_sec) * 1e9;
		duration[i] = (duration[i] + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	}
	
	//hesaplama sürelerinin yazdýrýlmasý
	printf("\n\n------------------");
	printf("\nHesaplama Sureleri");
	printf("\n\nUst Limit:\tSure:");
	printf("\n----------\t--------");
	for(i=0 ; i<8 ; i++){
		printf("\n%10d\t%f sn", limit[i], duration[i]);
	}
	
	//bar diyagramýnýn yazdýrýlmasý
	printf("\n\nBar Diyagrami");
	printf("\n--------------------------------------------------------> Sure");
	for(i=0 ; i<8 ; i++){
		printf("\n       | \n %5d | ", limit[i]);
		max = duration[i] * 200000;
		for(j=0 ; j<max ; j++){
			printf("o");
		}
	}
	printf("\n       | \n       | \n       V");
	printf("\n       Girdiler");
}







