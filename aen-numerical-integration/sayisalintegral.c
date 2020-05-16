#include <stdio.h>
#include <math.h>

#define SIZE 100
#define E 2.7182818

float denklem_alma();
float denklem_hesap(float);

//yöntem fonksiyonlarý
float trapez_y();
float simpson_y();

int derece, cevap;
float denklem_katsayi[SIZE], trigo_katsayi[4], trigo_ic_katsayi[4];
float ln_katsayi, ln_ic_katsayi, e_katsayi, e_uskatsayi;

int main(){
		
	printf("\nSAYISAL INTEGRAL");
	printf("\n\nLutfen kullanmak istediginiz yontemi seciniz:");
	
	printf("\n\n1) Trapez Yontemi"); //grafik_y
	printf("\n2) Simpson Yontemi"); //aralik_y
	
	printf("\n\nYontem: ");
	scanf("%d", &cevap);
	printf("\n-----");
	
	if(cevap==1){
		trapez_y();
	}else if(cevap==2){
		simpson_y();
	}else{
		printf("\n\n(!) Gecersiz secim!");
	}
	
	return 0;
}

//Fonksiyonlar buradan sonra.

float denklem_alma(){
	
	int i;
	
	//üslü ifadeler
	printf("\n\nDenkleminizin derecesini giriniz: ");
	scanf("%d", &derece);
	while(derece < 0){
		printf("\n(!) Denkleminizin derecesi negatif olamaz.");
		printf("\nLutfen gecerli bir tamsayi degeri giriniz: ");
		scanf("%d", &derece);
	}
	for(i=0 ; i<=derece ; i++){
		printf("x^%d degiskeninin katsayisi: ", i);
		scanf("%f", &denklem_katsayi[i]);
	}
	
	//trigonometrik ifadeler
	printf("\nTrigonometrik degisken var mi?");
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){
		printf("\nTrigonometrik degiskenlerin katsayilarini giriniz.");
		//sin
		printf("\n\n(A)sin(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &trigo_katsayi[0]);
		if(trigo_katsayi[0] != 0){
			printf("B katsayisini giriniz: ");
			scanf("%f", &trigo_ic_katsayi[0]);
		}
		printf("-----");
		//cos
		printf("\n(A)cos(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &trigo_katsayi[1]);
		if(trigo_katsayi[1] != 0){
			printf("B katsayisini giriniz: ");
			scanf("%f", &trigo_ic_katsayi[1]);
		}
		printf("-----");
		//tan
		printf("\n(A)tan(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &trigo_katsayi[2]);
		if(trigo_katsayi[2] != 0){
			printf("B katsayisini giriniz: ");
			scanf("%f", &trigo_ic_katsayi[2]);
		}
		printf("-----");
		//cot
		printf("\n(A)cot(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &trigo_katsayi[3]);
		if(trigo_katsayi[3] != 0){
			printf("B katsayisini giriniz: ");
			scanf("%f", &trigo_ic_katsayi[3]);
		}
	}else{
		for(i=0 ; i<4 ; i++){
			trigo_katsayi[i]=0;
		}
	}
	
	//logaritmik ifade
	printf("\nlnx degiskeni var mi?");
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){
		printf("\n(A)ln(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &ln_katsayi);
		printf("B katsayisini giriniz: ");
		scanf("%f", &ln_ic_katsayi);
	}else{
		ln_katsayi=0;
		ln_ic_katsayi=1;
	}
	
	//Üstel ifade
	printf("\ne^x degiskeni var mi?");
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){
		printf("\n(A)e^((B)x)");
		printf("\nA katsayisini giriniz: ");
		scanf("%f", &e_katsayi);
		printf("B katsayisini giriniz: ");
		scanf("%f", &e_uskatsayi);
	}else{
		e_katsayi=0;
	}
	
	//denklemi yazdýrma
	printf("\nDenkleminiz:\n");
	
	if(denklem_katsayi[derece]!=0){
		printf("(%.2fx^%d)", denklem_katsayi[derece], derece);
	}
	for(i=derece-1 ; i>=0 ; i--){
		if(denklem_katsayi[i]!=0){
			printf("+(%.2fx^%d)", denklem_katsayi[i], i);
		}
	}
	if(trigo_katsayi[0]!=0){
		printf("+(%.2fsin(%.2fx))", trigo_katsayi[0], trigo_ic_katsayi[0]);
	}
	if(trigo_katsayi[1]!=0){
		printf("+(%.2fcos(%.2fx))", trigo_katsayi[1], trigo_ic_katsayi[1]);
	}
	if(trigo_katsayi[2]!=0){
		printf("+(%.2ftan(%.2fx))", trigo_katsayi[2], trigo_ic_katsayi[2]);
	}
	if(trigo_katsayi[3]!=0){
		printf("+(%.2fcot(%.2fx))", trigo_katsayi[3], trigo_ic_katsayi[3]);
	}
	if(ln_katsayi!=0){
		printf("+(%.2fln(%.2fx))", ln_katsayi, ln_ic_katsayi);
	}
	if(e_katsayi!=0){
		printf("+(%.2fe^(%.2fx))", e_katsayi, e_uskatsayi);
	}
}

float denklem_hesap(float x){
	
	int i;
	float sum=0, x_sum=1;
	float sinx, cosx, tanx, cotx, lnx, ex;
	
	//trigonometrik deðerler
	sinx = trigo_katsayi[0]*sin(trigo_ic_katsayi[0]*x);
	cosx = trigo_katsayi[1]*cos(trigo_ic_katsayi[1]*x);
	if(trigo_katsayi[2] == 0){
		tanx = 0;
	}else{
		tanx = trigo_katsayi[2]*tan(trigo_ic_katsayi[2]*x);
	}
	if(trigo_katsayi[3] == 0){
		cotx = 0;
	}else{
		cotx = trigo_katsayi[3]/(tan(trigo_ic_katsayi[3]*x));
	}
	
	//logaritmik deðer
	if(ln_katsayi == 0){
		lnx = 0;
	}else{
		lnx = ln_katsayi*log(ln_ic_katsayi*x);
	}
	
	//Üstel deðer
	if(e_katsayi == 0){
		ex = 0;
	}else{
		ex = e_katsayi*pow(E, e_uskatsayi*x);
	}
	
	//diðer deðiþkenler
	for(i=0 ; i<=derece ; i++){
		sum = sum + (denklem_katsayi[i]*x_sum);
		x_sum = x_sum * x;
	}
	
	//toplam
	sum = sum + sinx + cosx + tanx + cotx + lnx + ex;
	return sum;
}

//Yöntemler
float trapez_y(){
	
	int i;
	float alt, ust, n;
	float x0, x1, y0, y1;
	float sum = 0, h;
	
	printf("\n\nTRAPEZ YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	printf("\n\n-----");
	
	printf("\n\nIntegralin hesaplanacagi aralik icin...");
	printf("\nAlt deger: ");
	scanf("%f", &alt);
	printf("Ust deger: ");
	scanf("%f", &ust);
	
	printf("\nAralik sayisi: ");
	scanf("%f", &n);
	
	while(n <= 0){
		printf("\n(!) Aralik sayisi pozitif bir sayi olmalidir.");
		printf("\nLutfen uygun bir aralik sayisi giriniz: ");
		scanf("%f", &n);
	}
	
	h = (ust - alt) / n;
	x1 = alt;
	
	for(i=0 ; i<n ; i++){
		x0 = x1;
		x1 = x1 + h;
		y0 = denklem_hesap(x0);
		y1 = denklem_hesap(x1);
		sum = sum + (y0 + y1);
	}
	sum = (sum * h) / 2;
	
	printf("\nIntegral degeri: %f", sum);
}

float simpson_y(){
	int i;
	float alt, ust, n, h;
	float x, y0, yn;
	float sum_cift = 0, sum_tek = 0, sum;
	
	printf("\n\nSIMPSON YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	printf("\n\n-----");
	
	printf("\n\nIntegralin hesaplanacagi aralik icin...");
	printf("\nAlt deger: ");
	scanf("%f", &alt);
	printf("Ust deger: ");
	scanf("%f", &ust);
	
	printf("\nAralik sayisi: ");
	scanf("%f", &n);
	i = n;
	
	while(i%2 == 1 || i <= 0){
		printf("\n(!) Aralik sayisi bu yontemde pozitif ve cift sayi olmalidir.");
		printf("\nLutfen uygun bir aralik sayisi giriniz: ");
		scanf("%f", &n);
		i = n;
	}
	
	h = (ust - alt) / n;
	y0 = denklem_hesap(alt);
	yn = denklem_hesap(ust);
	x = alt;
	
	for(i=1 ; i<n ; i++){
		x = x + h;
		if(i%2 == 1){
			sum_tek = sum_tek + denklem_hesap(x);
		}else{
			sum_cift = sum_cift + denklem_hesap(x);
		}
	}
	
	sum = ( (y0 + yn + (4 * sum_tek) + (2 * sum_cift)) * h ) / 3;
	
	printf("\nIntegral degeri: %f", sum);
}





