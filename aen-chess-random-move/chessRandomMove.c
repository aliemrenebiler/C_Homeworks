#include <stdio.h>
#include <time.h>

/*0,0 noktasýndaki atý, satranç tahtasýnda
rastgele gezdiren algoritma*/

void printTahta(int tahta[8][8]){
	int i, j;
	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			printf("%2d ", tahta[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int tahta[8][8];
	int hareket[8][2] = //atýn yapabileceði tüm hareketler
	{{+2, +1},{+2, -1},{-2, +1},{-2, -1},
	{+1, +2},{+1, -2},{-1, +2},{-1, -2}};
	int atX=0, atY=0; //atýn konumlarý
	int tempX=0, tempY=0; //geçici olarak hareketi depolamak için
	int adim; //hareket sayýsý
	int i, j, rastgele;
	
	srand(time(NULL)); //rastgele sayýyý zamana baðlama
	//tüm tahtayý sýfýrlama
	for(i=0 ; i<8 ; i++){
		for(j=0 ; j<8 ; j++){
			tahta[i][j] = 0;
		}
	}
	printf("SATRANC TAHTASINDAKI AT");
	printf("\n\nAdim Sayisi: ");
	scanf("%d", &adim);
	
	for(i=1 ; i<=adim ; i++){
		
		rastgele = rand() % 7;
		tempX = tempX + hareket[rastgele][0];
		tempY = tempY + hareket[rastgele][1];
		//hareketin tahta içinde olduðunu kontrol etme
		while( tempX > 7 || tempX < 0 || tempY > 7 || tempY < 0){
			tempX = atX;
			tempY = atY;
			rastgele = rand() % 7;
			tempX = tempX + hareket[rastgele][0];
			tempY = tempY + hareket[rastgele][1];
		}
		//kontrol sonucu yeni konumu yazma
		atX = tempX;
		atY = tempY;
		
		tahta[atX][atY] = i; //hareket sonrasý yeri yazma
		printf("\nAdim %d", i);
		printf("\nRastgele Sayi: %d\n", rastgele);
		printTahta(tahta); //tahtayý yazdýrma
	}
}
