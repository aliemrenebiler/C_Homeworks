/*
Ali Emre Nebiler
19011070
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

typedef struct colorWithAmount{
	int colorNum; // renk
	int repetition; // rengin tekrar say�s�
	struct colorWithAmount* prev; // �nceki renk
	struct colorWithAmount* next; // sonraki renk
}COLOR;
typedef struct pgmImage{
	char fileType[5]; // dosya t�r�
	int N, M; // sat�r s�tun say�s�
	int maxGrayValue; // maksimum gri de�eri
	int *imgArray; // renk matrisi
}PGM;
typedef struct encodedImage{
	char fileType[5]; // dosya t�r�
	int N, M; // sat�r s�tun say�s�
	int maxGrayValue; // maksimum gri de�eri
	COLOR *head; // ilk renk
}ENCODED;

// eylemler
void get_pgm(char*, PGM*);
void encode(PGM*, ENCODED*);
void write_to_txt(char*, ENCODED*);
void get_txt(char*, ENCODED*);
void decode(ENCODED*, PGM*);
void write_to_pgm(char*, PGM*);
void change_area_color(ENCODED*);
void change_pixel_color(ENCODED*);
void learn_color_amounts(ENCODED*);

// kontroller
int pgm_control(char*);
int bin_control(char*);
int encoded_pgm_control(ENCODED*);

// di�er fonksiyonlar
int get_cmd(int);
void get_filename(char*);
void print_encoded(char*, ENCODED*);
void print_decoded(char*, PGM*);
COLOR *create_color();
PGM *create_pgm();
ENCODED *create_encoded();

int main(){
	int cmd = 1;
	char fileName[SIZE];
	PGM *image;
	ENCODED *img_encoded;
	
	printf(" _________________________________\n");
	printf(" |                               |\n");
	printf(" |  ENCODE AND DECODE PGM FILES  |\n");
	printf(" |_______________________________|\n");
	
	do{ // ��k�� yapana kadar yap
		image = create_pgm();
		img_encoded = create_encoded();
		get_filename(fileName);
		
		printf("\n  1: Encode file");
		printf("\n  2: Decode file\n");
		printf("\n  3: Change an area's color");
		printf("\n  4: Change a pixel's color");
		printf("\n  5: Learn the amounts of colors\n");
		printf("\n  0: Exit\n");
		cmd = get_cmd(1);
		if(cmd == 1){ // G�R�NT� SIKI�TIR
			// girilen dosya pgm uzant�l� ise i�lem yap
			if(pgm_control(fileName)){
				get_pgm(fileName, image); // pgm verilerini al
				encode(image, img_encoded); // s�k��t�r�lm�� halini kaydet
				strcpy(fileName, "test_encoded.txt");
				write_to_txt(fileName, img_encoded); // s�k��t�r�lm�� halini belgeye yaz
				print_encoded(fileName, img_encoded); // sonucu yazd�r
			}
		}else if(cmd == 2){ // G�R�NT� ��Z
			// girilen dosya txt uzant�l� ise i�lem yap
			if(txt_control(fileName)){
				get_txt(fileName, img_encoded); // bin verilerini al
				// kontroller sonucunda uygunsa ��zme i�lemini yap
				if(encoded_pgm_control(img_encoded)){
					decode(img_encoded, image); // ��z�lm�� halini kaydet
					strcpy(fileName, "test_decoded.pgm");
					write_to_pgm(fileName, image); // ��z�lm�� halini belgeye yaz
					print_decoded(fileName, image); // sonucu yazd�r
				}
			}
		}else if(cmd == 3){ // B�R RENG� TAMAMEN DE���T�R
			// girilen dosya txt uzant�l� ise i�lem yap
			if(txt_control(fileName)){
				get_txt(fileName, img_encoded); // bin verilerini al
				// kontroller sonucunda uygunsa de�i�tirme i�lemini yap
				if(encoded_pgm_control(img_encoded)){
					change_area_color(img_encoded); // kay�tl� de�erlerden istenilenleri de�i�tir
					write_to_txt(fileName, img_encoded); // de�i�tirilmi� halini belgeye yaz
				}
			}
		}else if(cmd == 4){ // B�R P�XEL�N RENG�N� DE���T�R
			// girilen dosya txt uzant�l� ise i�lem yap
			if(txt_control(fileName)){
				get_txt(fileName, img_encoded); // bin verilerini al
				// kontroller sonucunda uygunsa de�i�tirme i�lemini yap
				if(encoded_pgm_control(img_encoded)){
					change_pixel_color(img_encoded); // kay�tl� de�erlerden istenilenleri de�i�tir
					write_to_txt(fileName, img_encoded); // de�i�tirilmi� halini belgeye yaz
				}
			}
		}else if(cmd == 5){ // T�M RENKLER�N ADED�N� ��REN
			// girilen dosya txt uzant�l� ise i�lem yap
			if(txt_control(fileName)){
				get_txt(fileName, img_encoded); // bin verilerini al
				// kontroller sonucunda uygunsa de�i�tirme i�lemini yap
				if(encoded_pgm_control(img_encoded)){
					learn_color_amounts(img_encoded);
				}
			}
		}else if(cmd == 0){ // �IKI� YAP
			printf("\n -------------");
			printf("\n (!) Finished.");
			printf("\n -------------\n");
		}
		if(cmd != 0){
			printf("\n ------------------------");
			printf("\n (?) Would you like to do");
			printf("\n     anything else?\n");
			printf("\n     1: Yes     0: No");
			printf("\n ------------------------\n");
			cmd = get_cmd(0);
			if(cmd == 0){ // �IKI� YAP
				printf("\n -------------");
				printf("\n (!) Finished.");
				printf("\n -------------\n");
			}
		}
		free(image);
		free(img_encoded);
	}while(cmd != 0);
	
	return 0;
}

// eylemler
void get_pgm(char *fileName, PGM *image){ // pgm dosyas�n� oku
	long int i, imgSize;
	char aChar, *tmp;
	FILE *fp;
	
	fp = fopen(fileName, "r");
	
	// bilgileri al
	fscanf(fp, "%[^\n]s", image->fileType);
	fscanf(fp, "\n%c", &aChar);
	if(aChar != '#'){ // yorum sat�r� yoksa ba�a d�n
		fseek(fp, 0, SEEK_SET);
	}
	fscanf(fp, "%[^\n]s", tmp); // gereksiz sat�r� tara ve ge�
	fscanf(fp, "\n%d %d", &image->M, &image->N);
	fscanf(fp, "\n%d", &image->maxGrayValue);
	
	// resim dizisini olu�tur
	imgSize = image->N * image->M;
	image->imgArray = (int*)malloc(imgSize*sizeof(int));
	
	// t�m piksel de�erlerini diziye al
	for(i=0 ; i<imgSize ; i++){
		fscanf(fp, " %d", &image->imgArray[i]);
	}
	
	fclose(fp);
}
void encode(PGM *image, ENCODED *img_encoded){ // dosyay� s�k��t�r
	long int i, imgSize;
	COLOR *newColor;
	
	// bilgileri kopyala
	strcpy(img_encoded->fileType, image->fileType);
	img_encoded->N = image->N;
	img_encoded->M = image->M;
	img_encoded->maxGrayValue = image->maxGrayValue;
	imgSize = img_encoded->M * img_encoded->N;
	
	// resmin ilk rengini ekle
	img_encoded->head = create_color();
	img_encoded->head->colorNum = image->imgArray[0];
	img_encoded->head->repetition = 1;
	img_encoded->head->next = NULL;
	img_encoded->head->prev = NULL;
	newColor = img_encoded->head;
	// renkler ayn� oldu�u s�rece miktar� artt�r
	// renk de�i�ti�inde yeni renk olu�tur
	for(i=0 ; i<imgSize-1 ; i++){
		if(image->imgArray[i] == image->imgArray[i+1]){
			newColor->repetition++;
		}else{
			newColor->next = create_color(); // yeni rengi olu�tur
			newColor->next->colorNum = image->imgArray[i+1]; // rengi ata
			newColor->next->repetition = 1; // miktar�n� 1 yap
			newColor->next->prev = newColor; // �nceki renge ba�la
			newColor->next->next = NULL; // sonraki rengi bo� b�rak
			newColor = newColor->next; // yeni renge ge�
		}
	}
}
void write_to_txt(char *fileName, ENCODED *img_encoded){ // txt dosyas�na yaz
	int length;
	FILE *fp;
	COLOR *newColor;
	
	fp = fopen(fileName, "wb");
	
	// bilgileri binary olarak yazd�r
	fwrite(&img_encoded->fileType, sizeof(char[5]), 1, fp);
	fwrite(&img_encoded->M, sizeof(int), 1, fp);
	fwrite(&img_encoded->N, sizeof(int), 1, fp);
	fwrite(&img_encoded->maxGrayValue, sizeof(int), 1, fp);
	
	// renkleri ve miktarlar�n� binary olarak yazd�r
	newColor = img_encoded->head;
	do{
		fwrite(&newColor->repetition, sizeof(int), 1, fp);
		fwrite(&newColor->colorNum, sizeof(int), 1, fp);
		newColor = newColor->next;
	}while(newColor != NULL);
	fclose(fp);
}
void get_txt(char *fileName, ENCODED *img_encoded){ // txt dosyas�n� oku
	COLOR *newColor;
	FILE *fp;
	
	fp = fopen(fileName, "rb");
	
	// bilgileri binary olarak oku
	fread(&img_encoded->fileType, sizeof(char[5]), 1, fp);
	fread(&img_encoded->M, sizeof(int), 1, fp);
	fread(&img_encoded->N, sizeof(int), 1, fp);
	fread(&img_encoded->maxGrayValue, sizeof(int), 1, fp);
	
	// ilk rengin bilgilerini binary olarak oku
	img_encoded->head = create_color();
	img_encoded->head->next = NULL;
	img_encoded->head->prev = NULL;
	fread(&img_encoded->head->repetition, sizeof(int), 1, fp);
	fread(&img_encoded->head->colorNum, sizeof(int), 1, fp);
	newColor = img_encoded->head;
	// dosyan�n sonuna kadar renk ve miktar bilgilerini binary olarak oku
	while(!feof(fp)){
		newColor->next = create_color();
		newColor->next->prev = newColor;
		newColor = newColor->next;
		fread(&newColor->repetition, sizeof(int), 1, fp);
		fread(&newColor->colorNum, sizeof(int), 1, fp);
		newColor->next = NULL;
	}
	
	// en sonda fazladan al�nan renk bilgisini ve adedini sil
	newColor->prev->next = NULL;
	free(newColor);
	
	fclose(fp);
}
void decode(ENCODED *img_encoded, PGM *image){ // s�k��t�r�lm�� dosyay� ��z
	long int i, imgSize, recentSize;
	int length;
	char newFileName[SIZE];
	COLOR *newColor;
	
	// bilgileri kopyala
	strcpy(image->fileType, img_encoded->fileType);
	image->N = img_encoded->N;
	image->M = img_encoded->M;
	image->maxGrayValue = img_encoded->maxGrayValue;
	
	// resim dizisini olu�tur
	imgSize = image->N * image->M;
	image->imgArray = (int*)malloc(imgSize*sizeof(int));
	
	// renkleri resim dizisine ekle
	newColor = img_encoded->head;
	recentSize = 0;
	// �uanki boyut resim boyutunu ge�medi�i s�rece devam et
	do{
		// ayn� rengi miktar� kadar resim dizisine ekle
		for(i=0 ; i<newColor->repetition ; i++){
			image->imgArray[recentSize+i] = newColor->colorNum;
		}
		recentSize = recentSize + newColor->repetition; // g�ncel boyutu eklenen miktar kadar artt�r
		newColor = newColor->next; // yeni renge ge�
	}while(recentSize<imgSize);
}
void write_to_pgm(char *fileName, PGM *image){ // pgm dosyas�na yaz
	long int i, j;
	FILE *fp;
	COLOR *newColor;
	
	fp = fopen(fileName, "w");
	// bilgileri yazd�r
	fprintf(fp, "%s", image->fileType);
	fprintf(fp, "\n%d %d", image->M, image->N);
	fprintf(fp, "\n%d", image->maxGrayValue);
	// renkleri matris �eklinde yazd�r
	for(i=0 ; i<image->N ; i++){
		j = 0;
		fprintf(fp, "\n%d", image->imgArray[i*image->M+j]);
		for(j=1 ; j<image->M ; j++){
			fprintf(fp, " %d", image->imgArray[i*image->M+j]);
		}
	}
	fclose(fp);
}
void change_area_color(ENCODED *img_encoded){ // alan�n rengini de�itir
	int colorNum, newColorNum;
	long int changedPixels = 0;
	COLOR *newColor;
	
	do{
		printf("\n --> The color value of the area");
		printf("\n     that you want to change: ");
		scanf("%d", &colorNum);
		if(colorNum>255 || colorNum<0){
			printf("\n ----------------------------------");
			printf("\n (!) This color value is out of");
			printf("\n     the color spectrum.\n");
			printf("\n     (The color spectrum is between");
			printf("\n     the values of 0 and 255.)");
			printf("\n ----------------------------------\n");
		}
	}while(colorNum>255 || colorNum<0);
	
	do{
		printf("\n --> The new value of this area's color: ");
		scanf("%d", &newColorNum);
		if(newColorNum>255 || newColorNum<0){
			printf("\n ----------------------------------");
			printf("\n (!) This color value is out of");
			printf("\n     the color spectrum.\n");
			printf("\n     (The color spectrum is between");
			printf("\n     the values of 0 and 255.)");
			printf("\n ----------------------------------\n");
		}
	}while(newColorNum>255 || newColorNum<0);
	
	newColor = img_encoded->head;
	
	do{
		// istenen renge denk gelindi�inde yap
		if(newColor->colorNum == colorNum){
			changedPixels += newColor->repetition; // de�i�en piksel say�s�na ekleme yap
			newColor->colorNum = newColorNum; // yeni renk ile de�i�tir
			// e�er yeni renk, �ncesinde gelen renkle ayn�ysa birle�tir
			if(newColor->prev != NULL){
				if(newColor->prev->colorNum == newColor->colorNum){
					newColor->prev->repetition += newColor->repetition;
					// �ncesi ve sonras�n� ba�la
					if(newColor->next != NULL){
						newColor->prev->next = newColor->next;
						newColor->next->prev = newColor->prev;
					}else{
						newColor->prev->next = NULL;
					}
					newColor = newColor->prev;
				}
			}
			// e�er yeni renk, sonras�nda gelen renkle ayn�ysa birle�tir
			if(newColor->next != NULL){
				if(newColor->next->colorNum == newColor->colorNum){
					newColor->repetition += newColor->next->repetition;
					// �ncesi ve sonras�n� ba�la
					if(newColor->next->next != NULL){
						newColor->next = newColor->next->next;
						newColor->next->prev = newColor;
					}else{
						newColor->next = NULL;
					}
				}
			}
		}
		newColor = newColor->next; // s�radaki renge ge�
	}while(newColor != NULL);
	
	printf(" ____________________________________________\n");
	printf(" |                                          |\n");
	printf(" |  (!) The area's color has been changed.  |\n");
	printf(" |__________________________________________|\n");
	printf("\n --- Brevious Color Value: %d", colorNum);
	printf("\n --- New Color Value: %d", newColorNum);
	printf("\n     (%d pixels has been changed.)\n", changedPixels);
}
void change_pixel_color(ENCODED *img_encoded){ // bir pikselin rengini de�i�tir
	int N, M, colorNum, newColorNum, notDone = 1;
	long int i, destination, recentSize = 0;
	COLOR *newColor, *tmp;
	
	do{
		printf("\n --> The pixel's row number");
		printf("\n     (Between 0 and %d): ", img_encoded->N-1);
		scanf("%d", &N);
		if(N>img_encoded->N-1 || N<0){
			printf("\n ----------------------");
			printf("\n (!) Out of image size.");
			printf("\n ----------------------\n");
		}
	}while(N>img_encoded->N-1 || N<0);
	
	do{
		printf("\n --> The pixel's column number");
		printf("\n     (Between 0 and %d): ", img_encoded->M-1);
		scanf("%d", &M);
		if(M>img_encoded->M-1 || M<0){
			printf("\n ----------------------");
			printf("\n (!) Out of image size.");
			printf("\n ----------------------\n");
		}
	}while(M>img_encoded->M-1 || M<0);
	
	do{
		printf("\n --> The new color value of this pixel: ");
		scanf("%d", &newColorNum);
		if(newColorNum>255 || newColorNum<0){
			printf("\n ----------------------------------");
			printf("\n (!) This color value is out of");
			printf("\n     the color spectrum.\n");
			printf("\n     (The color spectrum is between");
			printf("\n     the values of 0 and 255.)");
			printf("\n ----------------------------------\n");
		}
	}while(newColorNum>255 || newColorNum<0);
	
	newColor = img_encoded->head;
	destination = (N * img_encoded->M) + M;
	
	// hedefi ge�medi�i s�rece renkleri atla
	while((recentSize + newColor->repetition) <= destination){
		recentSize += newColor->repetition;
		newColor = newColor->next;
	}
	
	colorNum = newColor->colorNum;
	
	if(newColor->colorNum == newColorNum){ // renk de�i�miyorsa uyar� ver
		printf("\n ------------------------");
		printf("\n (!) Nothing has changed.");
		printf("\n ------------------------\n");
	}else{ // renk de�i�iyorsa bunlar� yap
		if(newColor->repetition == 1){ // renk tekrar� 1 ise
			if(newColor->prev != NULL && newColor->next != NULL &&
			newColor->prev->colorNum == newColorNum &&
			newColor->next->colorNum == newColorNum){
				// hem �nceki hem soldaki ile ayn�ysa ikisini birle�tir
				newColor->prev->repetition += newColor->next->repetition + 1;
				if(newColor->next->next != NULL){
					newColor->prev->next = newColor->next->next;
					newColor->next->next->prev = newColor->prev;
				}else{
					newColor->prev->next = NULL;
				}
			}else if(newColor->prev != NULL &&
			newColor->prev->colorNum == newColorNum){
				// sadece �nceki ile ayn�ysa �ncekinin miktar�n� artt�r
				newColor->prev->repetition++;
				if(newColor->next != NULL){
					newColor->prev->next = newColor->next;
					newColor->next->prev = newColor->prev;
				}else{
					newColor->prev->next = NULL;
				}
			}else if(newColor->next != NULL &&
			newColor->next->colorNum == newColorNum){
				// sadece sonraki ile ayn�ysa sonrakinin miktar�n� artt�r
				newColor->next->repetition++;
				if(newColor->prev != NULL){
					newColor->next->prev = newColor->prev;
					newColor->prev->next = newColor->next;
				}else{
					newColor->next->prev = NULL;
				}
			}else{
				// iki taraf ile de ayn� de�ilse sadece rengi de�i�tir
				newColor->colorNum = newColorNum;
			}
		}else{ // renk tekrar� 1'den fazla ise
			newColor->repetition--; // miktar� azalt
			
			// renk tekrar� i�indeki tam konumunu bul
			i=0;
			while(recentSize != destination){
				recentSize++;
				i++; // rengin tekrar i�indeki konumu
			}
			
			if(i == 0){ // piksel, tekrar�n en ba��ndaysa yap
				if(newColor->prev != NULL &&
				newColor->prev->colorNum == newColorNum){
					newColor->prev->repetition++;
				}else{
					// eski de�erleri aktar
					tmp = create_color();
					tmp->colorNum = newColor->colorNum;
					tmp->repetition = newColor->repetition;
					// ba�la
					tmp->prev = newColor;
					if(newColor->next != NULL){
						tmp->next = newColor->next;
					}else{
						tmp->next = NULL;
					}
					newColor->next = tmp;
					// yeni de�erleri yaz
					newColor->colorNum = newColorNum;
					newColor->repetition = 1;
				}
			}else if(i == newColor->repetition){ // piksel, tekrar�n en sonundaysa yap
				if(newColor->next != NULL &&
				newColor->next->colorNum == newColorNum){
					newColor->next->repetition++;
				}else{
					// yeni de�erleri yaz
					tmp = create_color();
					tmp->colorNum = newColorNum;
					tmp->repetition = 1;
					// ba�la
					tmp->prev = newColor;
					if(newColor->next != NULL){
						tmp->next = newColor->next;
					}else{
						tmp->next = NULL;
					}
					newColor->next = tmp;
				}
			}else{ // piksel, tekrar�n ortas�ndaysa yap
				// yeni de�erleri yaz
				tmp = create_color();
				tmp->colorNum = newColorNum;
				tmp->repetition = 1;
				// �nceye ba�la
				tmp->prev = newColor;
				if(newColor->next != NULL){
					tmp->next = newColor->next;
				}else{
					tmp->next = NULL;
				}
				newColor->next = tmp;
				// bir ad�m kay
				newColor = tmp;
				// sonraki de�erleri yaz
				tmp = create_color();
				tmp->colorNum = newColor->prev->colorNum;
				tmp->repetition = newColor->prev->repetition - i;
				// sonraya ba�la
				tmp->prev = newColor;
				if(newColor->next != NULL){
					tmp->next = newColor->next;
				}else{
					tmp->next = NULL;
				}
				newColor->next = tmp;
				// en soldaki rengin say�s�n� d�zelt
				newColor->prev->repetition = i;
			}
		}
		printf(" _____________________________________________\n");
		printf(" |                                           |\n");
		printf(" |  (!) The pixel's color has been changed.  |\n");
		printf(" |___________________________________________|\n");
		printf("\n --- Pixel: [%d,%d]", N, M);
		printf("\n --- Brevious Color Value: %d", colorNum);
		printf("\n --- New Color Value: %d\n", newColorNum);
	}
}
void learn_color_amounts(ENCODED *img_encoded){ // resmin histogram�n� hesapla
	long int colors[256];
	int i;
	COLOR *newColor;
	
	// diziyi s�f�rla
	for(i=0  ; i<256 ; i++){
		colors[i] = 0;
	}
	
	newColor = img_encoded->head;
	do{
		colors[newColor->colorNum] += newColor->repetition;
		newColor = newColor->next;
	}while(newColor != NULL);
	
	printf(" _______________________\n");
	printf(" |                     |\n");
	printf(" |  ALL COLOR AMOUNTS  |\n");
	printf(" |_____________________|\n\n");
	for(i=0 ; i<256 ; i++){
		if(colors[i] != 0){
			printf(" --- Color Value: %3d --- Amount: %d\n", i, colors[i]);
		}
	}
}

// kontroller
int pgm_control(char *fileName){ // dosya uzant�s� kontrol�
	int i, equal = 1;
	char ext[4] = ".pgm";
	int extSize = strlen(fileName);
	
	while(equal && i<4){
		if(ext[i] != fileName[i+extSize-4]){
			equal = 0;
		}
		i++;
	}
	if(equal == 0){
		printf("\n -------------------");
		printf("\n (!) Not a PGM file.");
		printf("\n -------------------\n");
	}
	return equal;
}
int txt_control(char *fileName){ // dosya uzant�s� kontrol�
	int i, equal = 1;
	char ext[4] = ".txt";
	int extSize = strlen(fileName);
	
	while(equal && i<4){
		if(ext[i] != fileName[i+extSize-4]){
			equal = 0;
		}
		i++;
	}
	if(equal == 0){
		printf("\n -------------------");
		printf("\n (!) Not a TXT file.");
		printf("\n -------------------\n");
	}
	return equal;
}
int encoded_pgm_control(ENCODED *img_encoded){ // do�ru s�k��t�rma kontrol�
	long int imgSize, recentSize = 0;
	int colorControl = 1, repeatControl = 1, sizeControl = 1;
	COLOR *newColor;
	
	newColor = img_encoded->head;
	imgSize = img_encoded->M*img_encoded->N;
	
	// b�t�n renkleri ve adetlerini tara
	do{
		// renk aral��� uygun de�ilse renk kontrol�n� s�f�rla
		if(newColor->colorNum > 255 || newColor->colorNum < 0){
			colorControl = 0;
		}
		// ayn� renk ayr� olarak yaz�lm��sa tekrar kontrol�n� s�f�rla
		if(newColor->next != NULL){
			if(newColor->colorNum == newColor->next->colorNum){
				repeatControl = 0;
			}
		}
		// renk miktarlar�n� topla ve s�radaki renge ge�
		recentSize = recentSize + newColor->repetition;
		newColor = newColor->next;
	}while(newColor != NULL);
	
	if(recentSize != imgSize){ // piksel say�s�, boyut oran� kontrol�
		sizeControl = 0;
		printf("\n -------------------------------------");
		printf("\n (!) Amount of pixels are not matching");
		printf("\n     with size of the image.");
		printf("\n -------------------------------------\n");
	}
	if(!colorControl){ // renk aral��� kontrol�
		printf("\n ------------------------------------");
		printf("\n (!) There are color values which are");
		printf("\n     out of the color spectrum.");
		printf("\n ------------------------------------\n");
	}
	if(!repeatControl){ // ayn� rengin tekrar� kontrol�
		printf("\n ---------------------------------");
		printf("\n (!) Same colors were seperated.");
		printf("\n     Encoding had been done wrong.");
		printf("\n ---------------------------------\n");
	}
	// �� kontrol� de ge�iyorsa 1, ge�emiyorsa 0 d�nd�r
	if((sizeControl+colorControl+repeatControl) == 3){
		printf("\n --------------------------");
		printf("\n     Size Test = OK");
		printf("\n     Color Values Test = OK");
		printf("\n     Repetition Test = OK\n");
		printf("\n (!) Tests were passed.");
		printf("\n --------------------------\n");
		return 1;
	}else{
		return 0;
	}
}

// di�er fonksiyonlar
int get_cmd(int X){ // do�ru komutu alma
	int cmd;
	if(X == 1){
		do{
			printf("\n --> Command: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 0){
			   	printf("\n ------------------");
				printf("\n (!) Wrong command.");
				printf("\n ------------------\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 &&
		       cmd != 4 && cmd != 5 && cmd != 0);
	}else if(X == 0){
		do{
			printf("\n --> Command: ");
			scanf(" %d", &cmd);
			if(cmd != 0 && cmd != 1){
				printf("\n ------------------");
				printf("\n (!) Wrong command.");
				printf("\n ------------------\n");
			}
		}while(cmd != 0 && cmd != 1);
	}
	return cmd;
}
void get_filename(char *fileName){ // dosya ad�n� al
	char enteredName[SIZE];
	FILE *fp;
	do{ // ge�erli bir dosya a��lana kadar dosya ismi al
		printf("\n --> File Name (with extension): ");
		scanf(" %[^\n]s", enteredName);
		fp = fopen(enteredName, "r");
		// dosya ismi ge�ersizse uyar� ver
		if(fp == NULL){
			printf("\n ----------------------");
			printf("\n (!) Invalid file name.");
			printf("\n ----------------------\n");
		}
	}while(fp == NULL);
	strcpy(fileName, enteredName);
	fclose(fp);
}
void print_encoded(char *fileName, ENCODED *img_encoded){ // s�k��t�r�lm�� dosya ��kt�s�
	int i = 0;
	COLOR *newColor;
	printf(" ______________________________\n");
	printf(" |                            |\n");
	printf(" |  (!) The file is encoded.  |\n");
	printf(" |____________________________|\n");
	printf("\n --- File Name: %s", fileName);
	printf("\n --- File Type: %s", img_encoded->fileType);
	printf("\n --- Imge Size: %d x %d", img_encoded->M, img_encoded->N);
	printf("\n --- Max Gray Value: %d", img_encoded->maxGrayValue);
	printf("\n --- Amounts x Colors:");
	newColor = img_encoded->head;
	do{
		if(i==0){
			printf("\n    ");
			i = 5;
		}else{
			i--;
		}
		printf(" %dx%d ", newColor->repetition, newColor->colorNum);
		newColor = newColor->next;
	}while(newColor != NULL);
	printf("\n");
}
void print_decoded(char *fileName, PGM *image){ // ��z�lm�� dosya ��kt�s�
	printf(" ______________________________\n");
	printf(" |                            |\n");
	printf(" |  (!) The file is decoded.  |\n");
	printf(" |____________________________|\n");
	printf("\n --- File Name: %s", fileName);
	printf("\n --- File Type: %s", image->fileType);
	printf("\n --- Imge Size: %d x %d", image->M, image->N);
	printf("\n --- Max Gray Value: %d\n", image->maxGrayValue);
}
COLOR *create_color(){
	return (COLOR*)malloc(sizeof(COLOR));
}
PGM *create_pgm(){
	return (PGM*)malloc(sizeof(PGM));
}
ENCODED *create_encoded(){
	return (ENCODED*)malloc(sizeof(ENCODED));
}

/*
RES�M �RNEKLER�
---------------
https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html
*/
