#include <stdio.h>
#include <math.h>

#define SIZE 100

float matris_alma();
float determinant(float[SIZE][SIZE], float);

//Yöntemler
float cramer_y();
float yoketme_gauss();
float yoketme_gauss_jordan();
float cholesky_y();
float jacobi_i();
float gauss_seidal();

int cevap;
float N, matris[SIZE][SIZE];
float degisken[SIZE], deger[SIZE];

//degisken[x] = x1, x2 ...
//deger[x] = c1, c2 ...

int main(){
	printf("\nLINEER DENKLEM TAKIMLARI ICIN COZUM YONTEMLERI");
	printf("\n\nDOLAYSIZ:");
	printf("\n1) Cramer Yontemi");
	printf("\n2) Yok Etme Yontemi");
	printf("\n3) Yogunlastirilmis Yok Etme Yontemi");
	
	printf("\n\nDOLAYLI:");
	printf("\n4) Jacobi Iterasyonu");
	printf("\n5) Gauss-Seidal");
	
	printf("\n\nYontem: ");
	scanf("%d", &cevap);
	printf("\n-----");
	
	if(cevap==1){
		cramer_y();
	}else if(cevap==2){
		printf("\n\nYOK ETME YONTEMLERI:");
		printf("\n1) Gauss Eliminasyonu");
		printf("\n2) Gauss-Jordan Eliminasyonu");
		
		printf("\n\nYontem: ");
		scanf("%d", &cevap);
		printf("\n-----");
		
		if(cevap==1){
			yoketme_gauss();
		}else if(cevap==2){
			yoketme_gauss_jordan();
		}else{
			printf("\n\n(!) Gecersiz secim.");
		}
	}else if(cevap==3){
		cholesky_y();
	}else if(cevap==4){
		jacobi_i();
	}else if(cevap==5){
		gauss_seidal();
	}else{
		printf("\n\n(!) Gecersiz secim.");
	}
	
	return 0;
}

//Fonksiyonlar
float matris_alma(){
	
	int i, j;
	
	//Matrisin geniþliðini alma
	printf("\n\nDenklem ve degisken sayisi: ");
	scanf("%f", &N);
	while(N <= 0){
		printf("\n\n(!) Degisken sayisi pozitif bir tamsayi olmalidir.");
		printf("\nLutfen geçerli bir deger giriniz: ");
		scanf("%f", &N);
	}
	
	//Matrisi alma
	printf("\nDenklem katsayilarini giriniz.\n");
	for(i=0 ; i<N ; i++){
		printf("---\n");
		for(j=0 ; j<N ; j++){
			printf("%d. denklemin, %d. degiskeninin katsayisi: ", i+1, j+1);
			scanf("%f", &matris[i][j]);
		}
		printf("%d. denklemin esit oldugu deger: ", i+1);
		scanf("%f", &deger[i]);
	}
	
	//Matrisi yazdýrma
	printf("\nDenklem Matrisiniz:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
}

float determinant(float a[SIZE][SIZE], float n){
	int i, j, k, p, r;
	float det = 0;
	float minor[SIZE][SIZE];
	
	//1x1
	if(n == 1){
		return a[0][0];
		
	//2x2
	}else if(n == 2){
		det=( a[0][0] * a[1][1] - a[0][1] * a[1][0] );
		return det;
		
	//3x3, 4x4, ...
	}else{
		for(k=0 ; k<n ; k++){
			p = 0;
			r = 0;
			for(i=1 ; i<n ; i++){
				for(j=0 ; j<n ; j++){
					if(j != k){
						minor[p][r] = a[i][j];
						r++;
						if(r == n-1){
							p++;
							r = 0;
						}
					}
				}
			}
			det = det + a[0][k] * pow(-1, k) * determinant(minor, n-1);
		}
    return det;
	}
}

//Yöntemler
float cramer_y(){
	
	int i, j, k;
	float det_matris, temp[SIZE][SIZE];
	
	printf("\n\nCRAMER YONTEMI");
	printf("\n\n-----");
	
	matris_alma();
	
	det_matris = determinant(matris, N);
	
	printf("\n\nDenklem matrisinin determinanti: %.2f", det_matris);
	if(det_matris == 0){
		printf("\n\n(!) Determinant 0 oldugundan Cramer Yontemi'yle hesap yapilamaz.");
	}else{
		for(i=0 ; i<N ;i++){
			for(k=0 ; k<N ; k++){
				for(j=0 ; j<N ; j++){
					if(k == i){
						temp[j][k] = deger[j];
					}else{
						temp[j][k] = matris[j][k];
					}
				}
			}
			degisken[i] = determinant(temp, N)/det_matris;
		}
		//Deðiþkenleri yazdýrma
		printf("\n\nDegiskenler:");
		for(i=0 ; i<N ; i++){
			printf("\nx%d = %f", i+1, degisken[i]);
		}
	}
}

float yoketme_gauss(){
	
	int i, j, k;
	float temp1, temp2, sum;
	
	printf("\n\nGAUSS ELIMINASYONU");
	printf("\n\n-----");
	
	matris_alma();
	
	printf("\n\n-----");
	
	//Üst üçgen matris oluþturma
	for(i=0 ; i<N-1 ; i++){
		temp1 = matris[i][i];
		for(j=i+1 ; j<N ; j++){
			temp2 = matris[j][i];
			for(k=i ; k<N ; k++){
				matris[j][k] = matris[j][k] - ( ( matris[i][k] / temp1 ) * temp2 );
			}
			deger[j] = deger[j] - ( ( deger[i] / temp1 ) * temp2 );
		}
	}
	
	//Üst üçgen matrisi yazdýrma
	printf("\n\nUst Ucgen Matrisiniz:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
	
	printf("\n\n-----");
	
	//Hesaplama
	for(i=(N-1) ; i>=0 ; i--){
		sum = 0;
		for(j=(N-1) ; j>=i ; j--){
			sum = sum + ( degisken[j] * matris[i][j] );
		}
		degisken[i] = (deger[i] - sum) / matris[i][i];
	}
	
	//Deðiþkenleri yazdýrma
	printf("\n\nDegiskenler:");
	for(i=0 ; i<N ; i++){
		printf("\nx%d = %f", i+1, degisken[i]);
	}
}

float yoketme_gauss_jordan(){
	
	int i, j, k;
	float temp1, temp2, sum;
	
	printf("\n\nGAUSS-JORDAN ELIMINASYONU");
	printf("\n\n-----");
	
	matris_alma();
	
	printf("\n\n-----");
	
	printf("\n\nGerekli islemler yapildiginda...");
	
	//Alt üçgen elemanlarýný sýfýrlama
	for(i=0 ; i<N-1 ; i++){
		temp1 = matris[i][i];
		for(j=i ; j<N ; j++){
			matris[i][j] = matris[i][j] / temp1;
		}
		deger[i] = deger[i] / temp1;
		for(j=i+1 ; j<N ; j++){
			temp2 = matris[j][i];
			for(k=i ; k<N ; k++){
				matris[j][k] = matris[j][k] - (matris[i][k] * temp2);
			}
			deger[j] = deger[j] - (deger[i] * temp2);
		}	
	}
	i = N-1;
	temp1 = matris[i][i];
	matris[i][i] = 1;
	deger[i] = deger[i] / temp1;
	
	//Matrisi yazdýrma
	printf("\n\n(!) Alt ucgen sifirlandi.");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
	
	//Üst üçgen elemanlarýný sýfýrlama
	for(i=N-1 ; i>0 ; i--){
		temp1 = matris[i][i];
		for(j=i-1 ; j>=0 ; j--){
			temp2 = matris[j][i];
			for(k=i ; k>j ; k--){
				matris[j][k] = matris[j][k] - (matris[i][k] * temp2);
			}
			deger[j] = deger[j] - (deger[i] * temp2);
		}
	}
	
	//Matrisi yazdýrma
	printf("\n\n(!) Ust ucgen sifirlandi.");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
	
	printf("\n\n(!) Birim matris olusturuldu.");
	
	//Deðiþkenleri yazdýrma
	printf("\n\nDegiskenler, denklemlerin esit oldugu degerlerdir:");
	for(i=0 ; i<N ; i++){
		printf("\nx%d = %f", i+1, deger[i]);
	}
}

float cholesky_y(){
	
	int i, j, k;
	float temp1, temp2, sum;
	float L[SIZE][SIZE], U[SIZE][SIZE], Y[SIZE];
	float L_ters[SIZE][SIZE], U_ters[SIZE][SIZE];
	
	printf("\n\nCHOLESKY YONTEMI");
	printf("\n\n-----");
	
	matris_alma();
	printf("\n\n-----");
	printf("\n\n[A] = [U] x [L]");
	
	//Matrisi üst ve alt matrislere kopyalama
	for(i=0 ; i<N ; i++){
		for(j=0 ; j<N ; j++){
			U[i][j] = matris[i][j];
			L[i][j] = matris[i][j];
		}
	}
	
	//Alt üçgen matrisi oluþturma
	for(i=0 ; i<N-1 ; i++){
		temp1 = L[i][i];
		for(j=i+1 ; j<N ; j++){
			temp2 = L[i][j];
			for(k=i ; k<N ; k++){
				L[k][j] = L[k][j] - ( ( L[k][i] / temp1 ) * temp2 );
			}
		}
	}
	
	//Matrisi yazdýrma
	printf("\n\n[L] Alt Ucgen Matris:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", L[i][j], j+1);
		}
	}
	
	//Üst üçgen matrisi oluþturma
	for(i=0 ; i<N-1 ; i++){
		temp1 = U[i][i];
		for(j=i ; j<N ; j++){
			U[i][j] = U[i][j] / temp1;
		}
		for(j=i+1 ; j<N ; j++){
			temp2 = U[j][i];
			for(k=i ; k<N ; k++){
				U[j][k] = U[j][k] - (U[i][k] * temp2);
			}
		}	
	}
	i = N-1;
	U[i][i] = 1;
	
	//Matrisi yazdýrma
	printf("\n\n[U] Ust Ucgen Matris:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", U[i][j], j+1);
		}
	}
	
	printf("\n\n-----");
	printf("\n\n[L] x [Y] = [C]");
	
	//Y deðerlerini hesaplama
	for(i=0 ; i<N ; i++){
		sum = 0;
		for(j=0 ; j<i ; j++){
			sum = sum + L[i][j] * Y[j];
		}
		Y[i] = (deger[i] - sum) / L[i][i];
	}
	
	//Y deðerlerini yazdýrma
	printf("\n\n[Y] Degerleri:");
	for(i=0 ; i<N ; i++){
		printf("\ny%d = %f", i+1, Y[i]);
	}
	
	printf("\n\n[U] x [X] = [Y]");
	
	//Deðiþkenleri hesaplama
	for(i=N-1 ; i>=0 ; i--){
		sum = 0;
		for(j=N-1 ; j>i ; j--){
			sum = sum + U[i][j] * degisken[j];
		}
		degisken[i] = Y[i] - sum;
	}
	
	//Deðiþkenleri yazdýrma
	printf("\n\nDegiskenler:");
	for(i=0 ; i<N ; i++){
		printf("\nx%d = %f", i+1, degisken[i]);
	}
}

float jacobi_i(){
	
	int i, j, flag = 0, kontrol = 1;
	float temp[SIZE], sum, epsilon;
	//temp[x] baþlangýç deðiþken deðerleri
	
	printf("\n\nJACOBI ITERASYONU");
	printf("\n\n-----");
	
	matris_alma();
	printf("\n\n-----");
	
	//Kontrol
	while(kontrol == 1){
		for(i=0 ; i<N ; i++){	
			sum = 0;
			for(j=0 ; j<N ; j++){
				if(j != i){
					sum = sum + fabs(matris[i][j]);
				}
			}
			if(fabs(matris[i][i]) < sum){
				kontrol = 0;
				printf("\n\n(!) Yakinsama kontrolu saglanmamistir.");
				printf("\nYine de isleme devam etmek istiyor musunuz?");
				printf("\n1) Evet\t2) Iptal Et\n");
				scanf("%d", &cevap);
			}
		}
		if(kontrol == 1){
			printf("\n\n(!) Yakinsama kontrolu saglanmistir.");
			kontrol = 0;
			cevap = 1;
		}
	}
	
	if(cevap == 1){
		//Deðer girme
		printf("\n\nDegiskenlerin baslangic degerlerini giriniz.\n");
		for(i=0 ; i<N ; i++){
			printf("x%d: ", i+1);
			scanf("%f", &temp[i]);
		}
		printf("\nEpsilon degerini giriniz: ");
		scanf("%f", &epsilon);
		printf("\n");
		
		//Tablo yazdýrma
		for(i=0 ; i<N ; i++){
			printf("x%d\t\td(x%d)\t\t", i+1, i+1);
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("------\t\t------\t\t");
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("%f\t-\t\t", temp[i]);
		}
		
		//Yeni x deðiþkenlerini hesaplama
		while(flag == 0){
			for(i=0 ; i<N ; i++){
				sum = 0;
				for(j=0 ; j<N ; j++){
					if(j != i){
						sum = sum + (matris[i][j] * temp[j]);
					}
				}
				degisken[i] = (deger[i] - sum) / matris[i][i];
			}
			
			//Epsilon kontrolü
			kontrol = 1;
			while(kontrol == 1){
				for(i=0 ; i<N ; i++){
					if(fabs(degisken[i]-temp[i]) > epsilon){
						kontrol = 0;
					}
				}
				if(kontrol == 1){
					flag = 1;
					kontrol = 0;
				}
			}
			
			//Yazdýrma
			if(flag != 1){
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f\t", degisken[i], fabs(degisken[i]-temp[i]));
					temp[i] = degisken[i];
				}
			}else{
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("------\t\t------\t\t");
				}
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f < e\t", degisken[i], fabs(degisken[i]-temp[i]));
				}
				printf("\n\nDegiskenler:");
				for(i=0 ; i<N ; i++){
					printf("\nx%d = %f", i+1, degisken[i]);
				}
			}
			
		} //while sonu
	} //if sonu
}

float gauss_seidal(){
	
	int i, j, flag = 0, kontrol = 1;
	float temp[SIZE], sum, epsilon;
	
	printf("\n\nGAUSS-SEIDAL YONTEMI");
	printf("\n\n-----");
	
	matris_alma();
	printf("\n\n-----");
	
	//Kontrol
	while(kontrol == 1){
		for(i=0 ; i<N ; i++){	
			sum = 0;
			for(j=0 ; j<N ; j++){
				if(j != i){
					sum = sum + fabs(matris[i][j]);
				}
			}
			if(fabs(matris[i][i]) < sum){
				kontrol = 0;
				printf("\n\n(!) Yakinsama kontrolu saglanmamistir.");
				printf("\nYine de isleme devam etmek istiyor musunuz?");
				printf("\n1) Evet\t2) Iptal Et\n");
				scanf("%d", &cevap);
			}
		}
		if(kontrol == 1){
			printf("\n\n(!) Yakinsama kontrolu saglanmistir.");
			kontrol = 0;
			cevap = 1;
		}
	}
	
	if(cevap == 1){
		//Deðer girme
		printf("\n\nDegiskenlerin baslangic degerlerini giriniz.\n");
		for(i=0 ; i<N ; i++){
			printf("x%d: ", i+1);
			scanf("%f", &degisken[i]);
		}
		printf("\nEpsilon degerini giriniz: ");
		scanf("%f", &epsilon);
		printf("\n");
		
		//Tablo yazdýrma
		for(i=0 ; i<N ; i++){
			printf("x%d\t\td(x%d)\t\t", i+1, i+1);
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("------\t\t------\t\t");
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("%f\t-\t\t", degisken[i]);
		}
		
		//Yeni x deðiþkenlerini hesaplama
		while(flag == 0){
			for(i=0 ; i<N ; i++){
				sum = 0;
				for(j=0 ; j<N ; j++){
					if(j != i){
						sum = sum + (matris[i][j] * degisken[j]);
					}
				}
				degisken[i] = (deger[i] - sum) / matris[i][i];
			}
			
			//Epsilon kontrolü
			kontrol = 1;
			while(kontrol == 1){
				for(i=0 ; i<N ; i++){
					if(fabs(degisken[i]-temp[i]) > epsilon){
						kontrol = 0;
					}
				}
				if(kontrol == 1){
					flag = 1;
					kontrol = 0;
				}
			}
			
			//Yazdýrma
			if(flag != 1){
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f\t", degisken[i], fabs(degisken[i]-temp[i]));
					temp[i] = degisken[i];
				}
			}else{
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("------\t\t------\t\t");
				}
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f < e\t", degisken[i], fabs(degisken[i]-temp[i]));
				}
				printf("\n\nDegiskenler:");
				for(i=0 ; i<N ; i++){
					printf("\nx%d = %f", i+1, degisken[i]);
				}
			}
			
		} //while sonu
	} //if sonu
}















