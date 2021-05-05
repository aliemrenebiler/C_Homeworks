#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct student{ // ��RENC�
	char id[20]; // ��renci numaras�
	char name[20]; // isim
	char surname[20]; // soyisim
	int totalLesson; // kaydoldu�u toplam ders say�s�
	int totalCredit; // kaydoldu�u toplam kredi say�s�
}STUDENT;
typedef struct teacher{ // ��RET�M �YES�
	char id[20]; // ID
	char title[20]; // unvan
	char name[20]; // isim
	char surname[20]; // soyisim
}TEACHER;
typedef struct lesson{ // DERS
	char id[20]; // ders kodu
	char name[50]; // ders ismi
	int credit; // kredisi
	int usedQuota; // dolmu� kontenjan
	char teacherId[20]; // dersi veren ��retim �yesinin ID'si
}LESSON;
typedef struct date{ // DERS
	int hour, min;
	int day, month, year;
}DATE;

// GENEL FONKS�YONLAR
int getCmd(int);
int idCheck(char*, char*);
void setTime(DATE*);
void createTxtFiles();

// KONTROL FONKS�YONLARI
int searchById(char*, char*);
int controlLesson(char*, char*);
int anyLesson(char*);
int getLessonControl(char*, char*);
int getAnyLessonControl(char*);
int anyoneGetLessonControl(char*);
int creditControl(char*, char*, int);
int quotaControl(char*, int);
int addControl(char*, char*);
int emptyFile(char*);

// ARAMA FONKS�YONLARI
void findStudent(char*, STUDENT*);
void findTeacher(char*, TEACHER*);
void findLesson(char*, LESSON*);

// ��RENC� FONKS�YONLARI
void addLesson(char*, int, int);
void quitLesson(char*);
void studentsLessons(char*);
void searchTeacher();

// ��RET�M �YES� FONKS�YONLARI
void createLesson(char*);
void updateLesson(char*);
void deleteLesson(char*);
void teachersLessons(char*);
void searchLesson();
void attendanceList(char*);

// Y�NET�C� FONKS�YONLARI
void createStudent();
void updateStudent();
void deleteStudent();
void createTeacher();
void updateTeacher();
void deleteTeacher();

// KOZMET�K MEN�LER
void mainSignIn();
void mainMenu();
void studentSignIn();
void studentMenu();
void teacherSignIn();
void teacherMenu();
void adminSignIn();
void adminMenu();
int doneMenu();

int main(){
	setlocale(LC_ALL, "Turkish");
	
	int cmd; // komut
	char currentId[20]; // girilen ID
	int maxQuota; // her dersin max kontenjan�
	int maxCredit; // her ��rencinin max kredisi
	
	// dosyalar yoksa olu�tur
	createTxtFiles();
	
	// program ba�lang�c�
	printf("\n --> Ders Kontenjan S�n�r�: ");
	scanf(" %d", &maxQuota);
	printf(" --> ��renci Kredi S�n�r�: ");
	scanf(" %d", &maxCredit);
	do{ // ��k�� yapana kadar yap
		mainSignIn();
		mainMenu();
		cmd = getCmd(0);
		if(cmd == 1){ // ��RENC� G�R���
			studentSignIn();
			printf("\n --> ��renci Numaras�: ");
			scanf(" %[^\n]s", currentId); // ��renci numaras� al�n�r
			cmd = idCheck(currentId, "STUDENTS.txt");
			if(cmd == 2){
				do{ // geri gidene veya ��k�� yapana kadar yap
					printf("\n (!) Ho�geldiniz!");
					printf("\n (!) ID: %s\n", currentId);
					studentMenu();
					cmd = getCmd(1);
					if(cmd == 1){ // ders ekle
						addLesson(currentId, maxCredit, maxQuota);
						cmd = doneMenu();
					}else if(cmd == 2){ // ders kald�r
						quitLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 3){ // al�nan dersleri ��ren
						studentsLessons(currentId);
						cmd = doneMenu();
					}else if(cmd == 4){ // bir ��r. �yesinin verdi�i dersleri ��ren
						searchTeacher();
						cmd = doneMenu();
					}
				}while(cmd != 0 && cmd != 9);
			}
		}else if(cmd == 2){ // ��RET�M �YES� G�R���
			teacherSignIn();
			printf("\n --> ��retim �yesi ID'si: ");
			scanf(" %[^\n]s", currentId); // ID al�n�r
			cmd = idCheck(currentId, "TEACHERS.txt");
			if(cmd == 2){
				do{ // geri gidene veya ��k�� yapana kadar yap
					printf("\n (!) Ho�geldiniz!");
					printf("\n (!) ID: %s\n", currentId);
					teacherMenu();
					cmd = getCmd(2);
					if(cmd == 1){ // ders olu�tur
						createLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 2){ // ders g�ncelle
						updateLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 3){ // ders sil
						deleteLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 4){ // verilen dersler
						teachersLessons(currentId);
						cmd = doneMenu();
					}else if(cmd == 5){ // bir dersin kontenjan�n� ��ren
						searchLesson();
						cmd = doneMenu();
					}else if(cmd == 6){ // yoklama listesi olu�tur
						attendanceList(currentId);
						cmd = doneMenu();
					}
				}while(cmd != 0 && cmd != 9);
			}
		}else if(cmd == 3){ // Y�NET�C� G�R���
			do{ // geri gidene veya ��k�� yapana kadar yap
				adminSignIn();
				adminMenu();
				cmd = getCmd(3);
				if(cmd == 1){ // ��renci ekle
					createStudent();
					cmd = doneMenu();
				}else if(cmd == 2){ // ��renci g�ncelle
					updateStudent();
					cmd = doneMenu();
				}else if(cmd == 3){ // ��renci sil
					deleteStudent();
					cmd = doneMenu();
				}else if(cmd == 4){ // ��r. �yesi ekle
					createTeacher();
					cmd = doneMenu();
				}else if(cmd == 5){ // ��r. �yesi g�ncelle
					updateTeacher();
					cmd = doneMenu();
				}else if(cmd == 6){ // ��r. �yesi sil
					deleteTeacher();
					cmd = doneMenu();
				}
			}while(cmd != 0 && cmd != 9);
		}
	}while(cmd != 0);
	printf("\n (!) ��k�� yap�ld�.\n");
	printf(" _________________\n");
	printf(" |               |\n");
	printf(" |  �yi g�nler!  |\n");
	printf(" |_______________|\n");
	return 0;
}

// GENEL FONKS�YONLAR
int getCmd(int X){ // do�ru komutu almay� sa�lar
	// X == 0 --> ana men�
	// X == 1 --> ��renci giri�i
	// X == 2 --> ��r. �yesi giri�i
	// X == 3 --> y�netici giri�i
	// X == 4 --> i�lem sonu sayfas�
	int cmd;
	if(X == 0){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 && cmd != 0){
				printf("\n (!) Yanl�� komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 && cmd != 0);
	}else if(X == 1){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 9 && cmd != 0){
				printf("\n (!) Yanl�� komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 &&
		       cmd != 4 && cmd != 9 && cmd != 0);
	}else if(X == 2){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 6 &&
			   cmd != 9 && cmd != 0){
				printf("\n (!) Yanl�� komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 6 &&
			   cmd != 9 && cmd != 0);
	}else if(X == 3){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 6 &&
			   cmd != 9 && cmd != 0){
				printf("\n (!) Yanl�� komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 6 &&
			   cmd != 9 && cmd != 0);
	}else if(X == 4){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 9 && cmd != 0){
				printf("\n (!) Yanl�� komut!\n");
			}
		}while(cmd != 9 && cmd != 0);
	}
	return cmd;
}
int idCheck(char *id, char *fileName){ // ID kontrol� ile giri� yapar
	// return 0 --> ��k�� yap
	// return 1 --> geri
	// return 2 --> giri� yap�ld�
	int found = 0;
	int cmd;
	found = searchById(id, fileName);
	if(found == 0){
		printf("\n (!) ID bulunamad�.\n");
		cmd = doneMenu();
	}else if(found == 1){
		printf("\n (!) Giri� yap�ld�.");
		cmd = 2;
	}
	return cmd;
}
void setTime(DATE *date){ // anl�k zaman� ve tarihi al�r
	time_t now;
	time(&now);
	struct tm *local = localtime(&now);
    date->day = local->tm_mday;
    date->month = local->tm_mon + 1;
    date->year = local->tm_year + 1900;
    date->hour = local->tm_hour;
    date->min = local->tm_min;
}
void createTxtFiles(){
	FILE *fp;
	fp = fopen("LESSONS.txt", "r");
	if(fp == NULL){
		fp = fopen("LESSONS.txt", "w");
	}
	fclose(fp);
	fp = fopen("STUDENTS.txt", "r");
	if(fp == NULL){
		fp = fopen("STUDENTS.txt", "w");
	}
	fclose(fp);
	fp = fopen("TEACHERS.txt", "r");
	if(fp == NULL){
		fp = fopen("TEACHERS.txt", "w");
	}
	fclose(fp);
	fp = fopen("OgrenciDersKayit.txt", "r");
	if(fp == NULL){
		fp = fopen("OgrenciDersKayit.txt", "w");
	}
	fclose(fp);
}

// KONTROL FONKS�YONLARI
int searchById(char *id, char *fileName){ // ID ile arama yapar
	// found == 0 --> ID bulunamad�
	// found == 1 --> ID bulundu
	// found == 2 --> dosya bulunamad�
	int found = 0;
	char *tmpId = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(100*sizeof(char));
	FILE *fp = fopen(fileName, "r");
	
	if(fp!=NULL){
		while(!feof(fp) && !found){
			fscanf(fp, "\n%[^;]s", tmpId);
			fscanf(fp, ";%[^\n]s", tmpStr);
			if(strcmp(tmpId, id) == 0){
				found = 1;
			}
		}
		fclose(fp);
	}else{
		printf("\n (!) Dosya bulunamad�.\n");
		found = 2;
	}
	free(tmpId);
	free(tmpStr);
	return found;
}
int controlLesson(char *lessonId, char *teacherId){ // girilen dersin, ��r. �yesine aitli�ini kontrol eder
	int control = 0;
	FILE *fp;
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	fp = fopen("LESSONS.txt", "r");
	while(!feof(fp) && !control){
		fscanf(fp, "\n%[^;]s", newLesson->id);
		fscanf(fp, ";%[^;]s", newLesson->name);
		fscanf(fp, ";%[^;]s", newLesson->teacherId);
		fscanf(fp, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
		if(strcmp(newLesson->id, lessonId) == 0 &&
		strcmp(newLesson->teacherId, teacherId) == 0){
			control = 1;
		}
	}
	fclose(fp);
	free(newLesson);
	return control;
}
int anyLesson(char *teacherId){ // ��retim �yesine ait ders olup olmad���n� kontrol eder
	// return 0 --> hi� ders yok
	// return 1 --> ders var
	int control = 0;
	FILE *fp;
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	fp = fopen("LESSONS.txt", "r");
	while(!feof(fp) && !control){
		fscanf(fp, "\n%[^;]s", newLesson->id);
		fscanf(fp, ";%[^;]s", newLesson->name);
		fscanf(fp, ";%[^;]s", newLesson->teacherId);
		fscanf(fp, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
		if(strcmp(newLesson->teacherId, teacherId) == 0){
			control = 1;
		}
	}
	fclose(fp);
	free(newLesson);
	return control;
}
int getLessonControl(char *studentId, char *lessonId){ // ��rencinin dersi al�p almad���n� kontrol eder
	int control = 0;
	int pairId, status;
	FILE *fp;
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	fp = fopen("OgrenciDersKayit.txt", "r");
	while(!feof(fp) && !control){
		fscanf(fp, "\n%d", &pairId);
		fscanf(fp, "<%[^-]s", tmpStudent);
		fscanf(fp, "-%[^>]s", tmpLesson);
		fscanf(fp, ">%d", &status);
		fscanf(fp, ";%[^\n]s", tmpStr);
		if(strcmp(tmpStudent, studentId) == 0 &&
		   strcmp(tmpLesson, lessonId) == 0 && status == 1){
			control = 1;
		}
	}
	fclose(fp);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	return control;
}
int getAnyLessonControl(char *studentId){ // ��rencinin herhangi bir ders al�p almad���n� kontrol eder
	int control = 0;
	int pairId, status;
	FILE *fp;
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	fp = fopen("OgrenciDersKayit.txt", "r");
	while(!feof(fp) && !control){
		fscanf(fp, "\n%d", &pairId);
		fscanf(fp, "<%[^-]s", tmpStudent);
		fscanf(fp, "-%[^>]s", tmpLesson);
		fscanf(fp, ">%d", &status);
		fscanf(fp, ";%[^\n]s", tmpStr);
		if(strcmp(tmpStudent, studentId) == 0 && status == 1){
			control = 1;
		}
	}
	fclose(fp);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	return control;
}
int anyoneGetLessonControl(char *lessonId){ // dersi alan ��renci olup olmad���n� kontrol eder
	int control = 0;
	int pairId, status;
	FILE *fp;
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	fp = fopen("OgrenciDersKayit.txt", "r");
	while(!feof(fp) && !control){
		fscanf(fp, "\n%d", &pairId);
		fscanf(fp, "<%[^-]s", tmpStudent);
		fscanf(fp, "-%[^>]s", tmpLesson);
		fscanf(fp, ">%d", &status);
		fscanf(fp, ";%[^\n]s", tmpStr);
		if(strcmp(tmpLesson, lessonId) == 0 && status == 1){
			control = 1;
		}
	}
	fclose(fp);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	return control;
}
int creditControl(char *studentId, char *lessonId, int maxCredit){ // ��renci kredi durumunu kontrol eder
	int totalCredit;
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	findStudent(studentId, newStudent);
	findLesson(lessonId, newLesson);
	totalCredit = newStudent->totalCredit + newLesson->credit;
	if(totalCredit > maxCredit){
		return 0;
	}else{
		return 1;
	}
	free(newLesson);
	free(newStudent);
}
int quotaControl(char *lessonId, int maxQuota){ // ders kontenjan durumunu kontrol eder
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	findLesson(lessonId, newLesson);
	if((newLesson->usedQuota + 1) > maxQuota){
		return 0;
	}else{
		return 1;
	}
	free(newLesson);
}
int addControl(char *studentId, char *lessonId){ // dersin �nceden eklenip eklenmedi�ini kontrol eder
	// return 0 --> dersi zaten al�yor
	// return 1 --> dersi hi� almam��
	int control = 1;
	int pairId, status;
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	FILE *fp = fopen("OgrenciDersKayit.txt", "r");
	if(fp!=NULL){
		while(!feof(fp) && control){
			fscanf(fp, "\n%d", &pairId);
			fscanf(fp, "<%[^-]s", tmpStudent);
			fscanf(fp, "-%[^>]s", tmpLesson);
			fscanf(fp, ">%d", &status);
			fscanf(fp, ";%[^\n]s", tmpStr);
			if(strcmp(tmpStudent, studentId) == 0 &&
			strcmp(tmpLesson, lessonId) == 0 && status == 1){
				control = 0;
			}
		}
		fclose(fp);
	}
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	return control;
}
int emptyFile(char *fileName){ // dosyan�n bo� olup olmad���n� kontrol eder
	// return 0 --> bo�
	// return 1 --> dolu
	int control = 0;
	FILE *fp = fopen(fileName, "r");
    fseek(fp, 0, SEEK_END);
    control = ftell(fp);
    if(control > 0){
    	control = 1;
	}
    fclose(fp);
    return control;
}

// ARAMA FONKS�YONLARI
void findStudent(char *studentId, STUDENT *newStudent){ // ��renci bul ve bilgilerini al
	int found = 0;
	FILE *fp = fopen("STUDENTS.txt", "r");
	if(fp!=NULL){
		while(!feof(fp) && !found){
			fscanf(fp, "\n%[^;]s", newStudent->id);
			fscanf(fp, ";%[^;]s", newStudent->name);
			fscanf(fp, ";%[^;]s", newStudent->surname);
			fscanf(fp, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(strcmp(newStudent->id, studentId) == 0){
				found = 1;
			}
		}
		fclose(fp);
	}
}
void findTeacher(char *teacherId, TEACHER *newTeacher){ // ��r. �yesi bul ve bilgilerini al
	int found = 0;
	FILE *fp = fopen("TEACHERS.txt", "r");
	if(fp!=NULL){
		while(!feof(fp) && !found){
			fscanf(fp, "\n%[^;]s", newTeacher->id);
			fscanf(fp, ";%[^;]s", newTeacher->title);
			fscanf(fp, ";%[^;]s", newTeacher->name);
			fscanf(fp, ";%[^\n]s", newTeacher->surname);
			if(strcmp(newTeacher->id, teacherId) == 0){
				found = 1;
			}
		}
		fclose(fp);
	}
}
void findLesson(char *lessonId, LESSON *newLesson){ // ders bul ve bilgilerini al
	int found = 0;
	FILE *fp = fopen("LESSONS.txt", "r");
	if(fp!=NULL){
		while(!feof(fp) && !found){
			fscanf(fp, "\n%[^;]s", newLesson->id);
			fscanf(fp, ";%[^;]s", newLesson->name);
			fscanf(fp, ";%[^;]s", newLesson->teacherId);
			fscanf(fp, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
			if(strcmp(newLesson->id, lessonId) == 0){
				found = 1;
			}
		}
		fclose(fp);
	}
}

// ��RENC� FONKS�YONLARI
void addLesson(char *studentId, int maxCredit, int maxQuota){ // ders al
	int found, control1, control2, control3;
	int pairId, status, counter = 1;
	FILE *fp1, *fp2;
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(100*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	DATE *date = (DATE*)malloc(sizeof(DATE));
	printf("\n (!) Ders Ekleme ��lemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu al�n�r
	found = searchById(lessonId, "LESSONS.txt");
	control1 = addControl(studentId, lessonId);
	control2 = creditControl(studentId, lessonId, maxCredit); // ��rencinin kredisi yetiyor mu?
	control3 = quotaControl(lessonId, maxQuota); // derste yer var m�?
	if(found == 0){ // ID yoksa ekleme yap�lmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
	}else if(found == 1 && control1 == 0){ // �nceden eklendiyse ekleme yap�lmaz
		printf("\n (!) Bu dersi zaten al�yorsunuz.\n");
	}else if(found == 1 && control2 == 0){ // yeterli kredi yoksa ekleme yap�lmaz
		printf("\n (!) Yeterli krediniz kalmam��t�r.\n");
	}else if(found == 1 && control3 == 0){ // kontenjan doluysa ekleme yap�lmaz
		printf("\n (!) Ders kontenjan� dolmu�tur.\n");
	}else if(found == 1 && control1 == 1 && control2 == 1 && control3 == 1){
		// 1) OgrenciDersKayit.txt dosyas�na ekleme yap�l�r
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
		control1 = emptyFile("OgrenciDersKayit.txt");
		if(control1){ // dosya doluysa bu i�lemi yap
			while(!feof(fp1)){
				fscanf(fp1, "\n%d", &pairId);
				fscanf(fp1, "<%[^-]s", tmpStudent);
				fscanf(fp1, "-%[^>]s", tmpLesson);
				fscanf(fp1, ">%d", &status);
				fscanf(fp1, ";%[^\n]s", tmpStr);
				if(strcmp(tmpStudent, studentId) != 0 ||
				strcmp(tmpLesson, lessonId) != 0 || status == 1){
					fprintf(fp2,"\n%d<%s-%s>%d;%s", counter++, tmpStudent,
					tmpLesson, status, tmpStr);
				}
			}
		}
		setTime(date);
		fprintf(fp2,"\n%d<%s-%s>1;", counter, studentId, lessonId);
		fprintf(fp2,"%02d/%02d/%d;%02d:%02d",
		date->day, date->month, date->year, date->hour, date->min);
		fclose(fp1);
		fclose(fp2);
		remove("OgrenciDersKayit.txt"); // eski dosya silinir
		rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt"); // yeni dosya yeniden adland�r�l�r
		// 2) ��rencinin ald��� ders ve kredi eklenir
		findLesson(lessonId, newLesson);
		fp1 = fopen("STUDENTS.txt", "r");
		fp2 = fopen("NEW_STUDENTS.txt", "w");
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newStudent->id);
			fscanf(fp1, ";%[^;]s", newStudent->name);
			fscanf(fp1, ";%[^;]s", newStudent->surname);
			fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(strcmp(newStudent->id, studentId) == 0){
				newStudent->totalCredit = newStudent->totalCredit + newLesson->credit;
				newStudent->totalLesson = newStudent->totalLesson + 1;
			}
			// yeni dosyaya yaz�l�r
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
			newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adland�r�l�r
		// 3) ders kontenjan� artt�r�l�r
		fp1 = fopen("LESSONS.txt", "r");
		fp2 = fopen("NEW_LESSONS.txt", "w");
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newLesson->id);
			fscanf(fp1, ";%[^;]s", newLesson->name);
			fscanf(fp1, ";%[^;]s", newLesson->teacherId);
			fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
			if(strcmp(newLesson->id, lessonId) == 0){
				newLesson->usedQuota = newLesson->usedQuota + 1;
			}
			// yeni dosyaya yaz�l�r
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
			newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
		}
		fclose(fp1);
		fclose(fp2);
		remove("LESSONS.txt"); // eski dosya silinir
		rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adland�r�l�r
		printf("\n (!) Ders ekleme i�lemi tamamland�.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
	free(date);
}
void quitLesson(char *studentId){ // ders b�rak
	int found, control;
	int pairId, status;
	FILE *fp1, *fp2;
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	DATE *date = (DATE*)malloc(sizeof(DATE));
	printf("\n (!) Ders B�rakma ��lemi\n");
	control = getAnyLessonControl(studentId);
	if(control){ // al�nan herhangi bir ders yoksa i�lem yapma
		printf("\n --> B�rakmak �stedi�iniz Dersin Kodu: ");
		scanf(" %[^\n]s", lessonId); // ders kodu al�n�r
		found = searchById(lessonId, "LESSONS.txt"); // ders var m�?
		control = getLessonControl(studentId, lessonId); // dersi al�yor mu?
		if(found == 0){ // ders yoksa i�lem yapma
			printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
		}else if(found == 1 && control == 0){ // dersi alm�yorsa i�lem yapma
			printf("\n (!) Bu dersi zaten almamaktas�n�z.\n");
		}else if(found == 1 && control == 1){
			// 1) OgrenciDersKayit.txt'deki ders alma durumu 0 yap�l�r
			fp1 = fopen("OgrenciDersKayit.txt", "r");
			fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
			while(!feof(fp1)){
				fscanf(fp1, "\n%d", &pairId);
				fscanf(fp1, "<%[^-]s", tmpStudent);
				fscanf(fp1, "-%[^>]s", tmpLesson);
				fscanf(fp1, ">%d", &status);
				fscanf(fp1, ";%[^\n]s", tmpStr);
				if(strcmp(tmpStudent, studentId) == 0 &&
				strcmp(tmpLesson, lessonId) == 0 && status == 1){
					status = 0;
				}
				fprintf(fp2,"\n%d<%s-%s>%d;", pairId, tmpStudent,
				tmpLesson, status);
				// e�er silindiyse tarihi g�ncelle
				if(strcmp(tmpStudent, studentId) == 0 &&
				strcmp(tmpLesson, lessonId) == 0){
					setTime(date);
					fprintf(fp2,"%02d/%02d/%d;%02d:%02d",
					date->day, date->month, date->year, date->hour, date->min);
				}else{ // silinmediyse eski tarihi yaz
					fprintf(fp2,"%s", tmpStr);
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("OgrenciDersKayit.txt");
			rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt");
			// 2) ��rencinin b�rakt��� ders ve kredi ��kar�l�r
			findLesson(lessonId, newLesson);
			fp1 = fopen("STUDENTS.txt", "r");
			fp2 = fopen("NEW_STUDENTS.txt", "w");
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newStudent->id);
				fscanf(fp1, ";%[^;]s", newStudent->name);
				fscanf(fp1, ";%[^;]s", newStudent->surname);
				fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
				if(strcmp(newStudent->id, studentId) == 0){
					newStudent->totalCredit = newStudent->totalCredit - newLesson->credit;
					newStudent->totalLesson = newStudent->totalLesson - 1;
				}
				// yeni dosyaya yaz�l�r
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
				newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
			}
			fclose(fp1);
			fclose(fp2);
			remove("STUDENTS.txt"); // eski dosya silinir
			rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adland�r�l�r
			// 3) ders kontenjan� azalt�l�r
			fp1 = fopen("LESSONS.txt", "r");
			fp2 = fopen("NEW_LESSONS.txt", "w");
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newLesson->id);
				fscanf(fp1, ";%[^;]s", newLesson->name);
				fscanf(fp1, ";%[^;]s", newLesson->teacherId);
				fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
				if(strcmp(newLesson->id, lessonId) == 0){
					newLesson->usedQuota = newLesson->usedQuota - 1;
				}
				// yeni dosyaya yaz�l�r
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
				newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adland�r�l�r
			printf("\n (!) Ders b�rakma i�lemi tamamland�.\n");
		}
	}else{
		printf("\n (!) Ald���n�z herhangi bir ders bulunmamaktad�r.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
	free(date);
}
void studentsLessons(char *studentId){ // ��rencinin ald��� dersleri yazd�r�r
	int control;
	int pairId, status;
	FILE *fp;
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	control = getAnyLessonControl(studentId);
	if(control){
		printf("\n (!) Ald���n�z Dersler:\n");
		fp = fopen("OgrenciDersKayit.txt", "r");
		while(!feof(fp)){
			fscanf(fp, "\n%d", &pairId);
			fscanf(fp, "<%[^-]s", tmpStudent);
			fscanf(fp, "-%[^>]s", tmpLesson);
			fscanf(fp, ">%d", &status);
			fscanf(fp, ";%[^\n]s", tmpStr);
			if(strcmp(tmpStudent, studentId) == 0 && status == 1){
				findLesson(tmpLesson, newLesson);
				findTeacher(newLesson->teacherId, newTeacher);
				printf(" --- %s --> %s --> ��r. �yesi: %s %s %s\n", newLesson->id, newLesson->name,
				newTeacher->title, newTeacher->name, newTeacher->surname);
			}
		}
		fclose(fp);
	}else{
		printf("\n (!) Ald���n�z herhangi bir ders bulunmamaktad�r.\n");
	}
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newTeacher);
}
void searchTeacher(){ // ID'si girilen ��r. �yesinin verdi�i dersler
	int found, control;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) ��retim �yesi Arama ��lemi\n");
	// ��retim �yelerini yazd�r
	printf("\n (!) A�a��daki ��r. �yelerinin ID'lerini aratarak");
	printf("\n     verdikleri dersleri bulabilirsiniz.\n\n");
	fp = fopen("TEACHERS.txt", "r");
	while(!feof(fp)){
		fscanf(fp, "\n%[^;]s", newTeacher->id);
		fscanf(fp, ";%[^;]s", newTeacher->title);
		fscanf(fp, ";%[^;]s", newTeacher->name);
		fscanf(fp, ";%[^\n]s", newTeacher->surname);
		printf(" --- %s --> %s %s %s\n", newTeacher->id, newTeacher->title, newTeacher->name, newTeacher->surname);
	}
	fclose(fp);
	// ��retim �yesi ID al
	printf("\n --> Aramak �stedi�iniz ��retim �yesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID al�n�r
	found = searchById(id, "TEACHERS.txt"); // ��retim �yesi var m�?
	control = anyLesson(id); // ��retim �yesinin verdi�i ders var m�?
	if(found == 0){ // ��retim �yesi yoksa uyar
		printf("\n (!) Bu ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n");
	}else if(found == 1 && control == 0){ // ��retim �yesinin dersi yoksa uyar
		printf("\n (!) Bu ��retim �yesinin verdi�i herhangi bir ders bulunmamaktad�r.\n");
	}else if(found == 1 && control == 1){ // dersi varsa yazd�r
		fp = fopen("LESSONS.txt", "r");
		printf("\n (!) %s ID'li ��retim �yesinin verdi�i dersler:\n", id);
		while(!feof(fp)){
			fscanf(fp, "\n%[^;]s", newLesson->id);
			fscanf(fp, ";%[^;]s", newLesson->name);
			fscanf(fp, ";%[^;]s", newLesson->teacherId);
			fscanf(fp, ";%d", &newLesson->credit);
			fscanf(fp, ";%d", &newLesson->usedQuota);
			if(strcmp(newLesson->teacherId, id) == 0){
				printf(" --- %s --> %s --> Kredi: %d\n", newLesson->id, newLesson->name, newLesson->credit);
			}
		}
		fclose(fp);
	}
	free(id);
	free(newTeacher);
	free(newLesson);
}

// ��RET�M �YES� FONKS�YONLARI
void createLesson(char *teacherId){ // ders olu�tur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) Ders Olu�turma ��lemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", id); // ders kodu al�n�r
	found = searchById(id, "LESSONS.txt");
	if(found == 0){ // ID yoksa ekleme yap�l�r
		strcpy(newLesson->id, id);
		printf(" --> Dersin Ad�: ");
		scanf(" %[^\n]s", newLesson->name);
		printf(" --> Dersin Kredisi: ");
		scanf("%d", &newLesson->credit);
		strcpy(newLesson->teacherId, teacherId);
		newLesson->usedQuota = 0;
		fp = fopen("LESSONS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
		newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
		fclose(fp);
		printf("\n (!) Ders olu�turma i�lemi tamamland�.\n");
	}else if(found == 1){ // ID varsa ekleme yap�lmaz
		printf("\n (!) Bu koda sahip bir ders bulunmaktad�r.\n");
	}
	free(id);
	free(newLesson);
}
void updateLesson(char *teacherId){ // ders g�ncelle
	int found, control;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) Ders G�ncelleme ��lemi\n");
	control = anyLesson(teacherId);
	if(control){
		printf(" (!) �NEML�: Kredi de�i�ikli�i, dersi �nceden");
		printf("\n     alan ��rencileri etkilemeyecektir.\n");
		printf("\n --> G�ncellenecek Dersin Kodu: ");
		scanf(" %[^\n]s", id); // ID al�n�r
		found = searchById(id, "LESSONS.txt"); // ID ile arama yap�l�r
		control = controlLesson(id, teacherId); // ders ��r. �yesine ait mi kontrol�
		if(found == 0){ // ID yoksa g�ncelleme yap�lmaz
			printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
		}else if(found == 1 && control == 0){ // Ders giren ki�iye ait de�ilse g�ncelleme yap�lmaz
			printf("\n (!) Bu koda sahip ders, size ait de�ildir.\n");
		}else if(found == 1 && control == 1){ // ID varsa g�ncelleme yap�l�r
			printf("\n (!) Ders bulundu.");
			fp1 = fopen("LESSONS.txt", "r");
			fp2 = fopen("NEW_LESSONS.txt", "w"); // g�ncel hal
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newLesson->id);
				fscanf(fp1, ";%[^;]s", newLesson->name);
				fscanf(fp1, ";%[^;]s", newLesson->teacherId);
				fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
				if(strcmp(newLesson->id, id) == 0){ // de�i�tirilecek ID i�in yeni de�erler al�n�r
					// anl�k bilgiler yazd�r�l�r
					printf("\n --- Ders Ad�: %s", newLesson->name);
					printf("\n --- Dersin Kredisi: %d\n", newLesson->credit);
					// g�ncel bilgiler girilir
					printf("\n (!) G�ncel ders bilgilerini giriniz.");
					printf("\n --> G�ncel Ders Ad�: ");
					scanf(" %[^\n]s", newLesson->name);
					printf(" --> G�ncel Ders Kredisi: ");
					scanf("%d", &newLesson->credit);
				}
				// yeni dosyaya yaz�l�r
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
				newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adland�r�l�r
			printf("\n (!) Ders g�ncelleme i�lemi tamamland�.\n");
		}
	}else{
		printf("\n (!) Size ait herhangi bir ders bulunmamaktad�r.\n");
	}
	free(id);
	free(newLesson);
}
void deleteLesson(char *teacherId){ // ders sil
	int found, control;
	int pairId, status, counter = 1;
	FILE *fp1, *fp2, *fp3, *fp4;
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Ders Silme ��lemi\n");
	control = anyLesson(teacherId);
	if(control){
		printf("\n --> Silinecek Dersin Kodu: ");
		scanf(" %[^\n]s", lessonId); // ID al�n�r
		found = searchById(lessonId, "LESSONS.txt"); // ID ile arama yap�l�r
		control = controlLesson(lessonId, teacherId); // ders ��r. �yesine ait mi kontrol�
		if(found == 0){ // ID yoksa g�ncelleme yap�lmaz
			printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
		}else if(found == 1 && control == 0){ // Ders giren ki�iye ait de�ilse g�ncelleme yap�lmaz
			printf("\n (!) Bu koda sahip ders, size ait de�ildir.\n");
		}else if(found == 1 && control == 1){ // ID varsa g�ncelleme yap�l�r
			// 1) dersi alan/b�rakan ��rencilerde de�i�iklik yap�l�r
			fp1 = fopen("OgrenciDersKayit.txt", "r");
			fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
			findLesson(lessonId, newLesson);
			while(!feof(fp1)){
				fscanf(fp1, "\n%d", &pairId);
				fscanf(fp1, "<%[^-]s", tmpStudent);
				fscanf(fp1, "-%[^>]s", tmpLesson);
				fscanf(fp1, ">%d", &status);
				fscanf(fp1, ";%[^\n]s", tmpStr);
				// dersi alan ��renciler g�ncellenir
				if(strcmp(tmpLesson, lessonId) == 0 && status == 1){
					fp3 = fopen("STUDENTS.txt", "r");
					fp4 = fopen("NEW_STUDENTS.txt", "w");
					while(!feof(fp3)){
						fscanf(fp3, "\n%[^;]s", newStudent->id);
						fscanf(fp3, ";%[^;]s", newStudent->name);
						fscanf(fp3, ";%[^;]s", newStudent->surname);
						fscanf(fp3, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
						// o ��renciye gelindi�inde kredi ve al�nan ders azalt�l�r
						if(strcmp(newStudent->id, tmpStudent) == 0){
							newStudent->totalCredit = newStudent->totalCredit - newLesson->credit;
							newStudent->totalLesson = newStudent->totalLesson - 1;
						}
						fprintf(fp4,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
						newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
					}
					fclose(fp3);
					fclose(fp4);
					remove("STUDENTS.txt"); // eski dosya silinir
					rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adland�r�l�r
				}
				// o ders olmayan di�er t�m dersler yaz�l�r
				if(!(strcmp(tmpLesson, lessonId) == 0)){
					fprintf(fp2,"\n%d<%s-%s>%d;%s", counter++, tmpStudent,
					tmpLesson, status, tmpStr);
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("OgrenciDersKayit.txt");
			rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt");
			// 2) ders, di�er dersler aras�ndan silinir
			fp1 = fopen("LESSONS.txt", "r");
			fp2 = fopen("NEW_LESSONS.txt", "w"); // g�ncel hal
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newLesson->id);
				fscanf(fp1, ";%[^;]s", newLesson->name);
				fscanf(fp1, ";%[^;]s", newLesson->teacherId);
				fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
				if(!(strcmp(newLesson->id, lessonId) == 0)){ // silinen ders d���ndakiler yazd�r�l�r
					fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
					newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adland�r�l�r
			printf("\n (!) Ders silme i�lemi tamamland�.\n");
		}
	}else{
		printf("\n (!) Size ait herhangi bir ders bulunmamaktad�r.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}
void teachersLessons(char *teacherId){ // verilen dersleri yazd�r�r
	int control;
	FILE *fp;
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	control = anyLesson(teacherId); // ��retim �yesinin verdi�i ders var m�?
	if(!control){ // ��retim �yesinin dersi yoksa uyar
		printf("\n (!) Verdi�iniz herhangi bir ders bulunmamaktad�r.\n");
	}else{ // dersi varsa yazd�r
		fp = fopen("LESSONS.txt", "r");
		printf("\n (!) Verdi�iniz dersler:\n");
		while(!feof(fp)){
			fscanf(fp, "\n%[^;]s", newLesson->id);
			fscanf(fp, ";%[^;]s", newLesson->name);
			fscanf(fp, ";%[^;]s", newLesson->teacherId);
			fscanf(fp, ";%d", &newLesson->credit);
			fscanf(fp, ";%d", &newLesson->usedQuota);
			if(strcmp(newLesson->teacherId, teacherId) == 0){
				printf(" --- %s --> %s --> Kredi: %d\n", newLesson->id, newLesson->name, newLesson->credit);
			}
		}
		fclose(fp);
	}
	free(newTeacher);
	free(newLesson);
}
void searchLesson(){ // ID'si girilen dersi alan ��rencileri yazd�r�r
	int found, control;
	int pairId, status;
	FILE *fp;
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Ders S�n�f Listesi ��renme ��lemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu al�n�r
	found = searchById(lessonId, "LESSONS.txt"); // ders var m�?
	control = anyoneGetLessonControl(lessonId); // dersi alan ��renci var m�?
	if(found == 0){ // ders yoksa i�lem yap�lmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
	}else if(found == 1 && control == 0){ // dersi alan yoksa i�lem yap�lmaz
		printf("\n (!) Bu dersi alan herhangi bir ��renci bulunmamaktad�r.\n");
	}else if(found == 1 && control == 1){ // dersi alan varsa yazd�r�l�r
		printf("\n (!) %s Kodlu Dersin Kontenjan�\n", lessonId);
		fp = fopen("OgrenciDersKayit.txt", "r");
		while(!feof(fp)){
			fscanf(fp, "\n%d", &pairId);
			fscanf(fp, "<%[^-]s", tmpStudent);
			fscanf(fp, "-%[^>]s", tmpLesson);
			fscanf(fp, ">%d", &status);
			fscanf(fp, ";%[^\n]s", tmpStr);
			if(strcmp(tmpLesson, lessonId) == 0){
				findStudent(tmpStudent, newStudent);
				printf(" --- %s --> %s %s --->", newStudent->id, newStudent->name, newStudent->surname);
				if(status){
					printf(" KAYITLI\n");
				}else{
					printf(" BIRAKTI\n");
				}
			}
		}
		fclose(fp);
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}
void attendanceList(char *teacherId){ // ID'si girilen dersi alan ��rencileri txt'de listeler
	int found, control1, control2;
	int pairId, status;
	FILE *fp1, *fp2;
	char *fileName = (char*)malloc(50*sizeof(char));
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Yoklama Listesi Olu�turma ��lemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu al�n�r
	found = searchById(lessonId, "LESSONS.txt"); // ders var m�?
	control1 = controlLesson(lessonId, teacherId); // bu ders ��r. �yesine ait mi?
	control2 = anyoneGetLessonControl(lessonId); // dersi alan ��renci var m�?
	if(found == 0){ // ders yoksa i�lem yap�lmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktad�r.\n");
	}else if(found == 1 && control1 == 0){ // ders ��r. �yesine ait de�ilse i�lem yapmaz
		printf("\n (!) Bu ders size ait de�ildir.\n");
	}else if(found == 1 && control2 == 0){ // dersi alan yoksa i�lem yap�lmaz
		printf("\n (!) Bu dersi alan herhangi bir ��renci bulunmamaktad�r.\n");
	}else if(found == 1 && control1 == 1 && control2 == 1){ // sorun yoksa dosya olu�turulur
		strcpy(fileName, lessonId);
		strcat(fileName, "_SINIF_LISTESI.txt");
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen(fileName, "w");
		fprintf(fp2, "\n --- %s Kodlu Dersin S�n�f Listesi --- \n\n", lessonId);
		while(!feof(fp1)){
			fscanf(fp1, "\n%d", &pairId);
			fscanf(fp1, "<%[^-]s", tmpStudent);
			fscanf(fp1, "-%[^>]s", tmpLesson);
			fscanf(fp1, ">%d", &status);
			fscanf(fp1, ";%[^\n]s", tmpStr);
			if(strcmp(tmpLesson, lessonId) == 0 && status == 1){
				findStudent(tmpStudent, newStudent);
				fprintf(fp2, " --- %s --> %s %s\n", newStudent->id, newStudent->name, newStudent->surname);
			}
		}
		fclose(fp1);
		fclose(fp2);
		printf("\n (!) Yoklama listesi ba�ar�yla olu�turuldu.\n");
	}
	free(fileName);
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}

// Y�NET�C� FONKS�YONLARI
void createStudent(){ // ��renci olu�tur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) ��renci Ekleme ��lemi\n");
	printf("\n --> ��renci Numaras�: ");
	scanf(" %[^\n]s", id); // ��renci numaras� al�n�r
	found = searchById(id, "STUDENTS.txt"); // ID ile arama yap�l�r
	if(found == 0){ // ID yoksa ekleme yap�l�r
		strcpy(newStudent->id, id);
		printf(" --> ��rencinin Ad�: ");
		scanf(" %[^\n]s", newStudent->name);
		printf(" --> ��rencinin Soyad�: ");
		scanf(" %[^\n]s", newStudent->surname);
		newStudent->totalCredit = 0;
		newStudent->totalLesson = 0;
		fp = fopen("STUDENTS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
		newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		fclose(fp);
		printf("\n (!) ��renci ekleme i�lemi tamamland�.\n");
	}else if(found == 1){ // ID varsa ekleme yap�lmaz
		printf("\n (!) Bu numaraya sahip bir ��renci bulunmaktad�r.\n");
	}
	free(id);
	free(newStudent);
}
void updateStudent(){ // ��renci g�ncelle
	int found;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) ��renci G�ncelleme ��lemi\n");
	printf("\n --> G�ncellenecek ��rencinin Numaras�: ");
	scanf(" %[^\n]s", id); // ID al�n�r
	found = searchById(id, "STUDENTS.txt"); // ID ile arama yap�l�r
	if(found == 0){ // ID yoksa g�ncelleme yap�lmaz
		printf("\n (!) Bu numaraya sahip bir ��renci bulunmamaktad�r.\n");
	}else if(found == 1){ // ID varsa g�ncelleme yap�l�r
		printf("\n (!) ��renci bulundu.");
		fp1 = fopen("STUDENTS.txt", "r");
		fp2 = fopen("NEW_STUDENTS.txt", "w"); // g�ncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newStudent->id);
			fscanf(fp1, ";%[^;]s", newStudent->name);
			fscanf(fp1, ";%[^;]s", newStudent->surname);
			fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(strcmp(newStudent->id, id) == 0){ // de�i�tirilecek ID i�in yeni de�erler al�n�r
				// anl�k bilgiler yazd�r�l�r
				printf("\n --- ��renci Ad�: %s", newStudent->name);
				printf("\n --- ��renci Soyad�: %s\n", newStudent->surname);
				// g�ncel bilgiler girilir
				printf("\n (!) G�ncel ��renci bilgilerini giriniz.");
				printf("\n --> G�ncel ��renci Ad�: ");
				scanf(" %[^\n]s", newStudent->name);
				printf(" --> G�ncel ��renci Soyad�: ");
				scanf(" %[^\n]s", newStudent->surname);
			}
			// yeni dosyaya yaz�l�r
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
			newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adland�r�l�r
		printf("\n (!) ��renci g�ncelleme i�lemi tamamland�.\n");
	}
	free(id);
	free(newStudent);
}
void deleteStudent(){ // ��renci sil
	int found, control;
	int pairId, status, counter = 1;
	FILE *fp1, *fp2, *fp3, *fp4;
	char *studentId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) ��renci Silme ��lemi\n");
	printf("\n --> Silinecek ��rencinin Numaras�: ");
	scanf(" %[^\n]s", studentId); // ID al�n�r
	found = searchById(studentId, "STUDENTS.txt"); // ID ile arama yap�l�r
	if(found == 0){ // ID yoksa i�lem yap�lmaz
		printf("\n (!) Bu numaraya sahip bir ��renci bulunmamaktad�r.\n");
	}else if(found == 1){ // ID varsa i�lem yap�l�r
		// 1) OgrenciDersKayit.txt �zerinden dersleri sil
		// B�rak�lmam��sa LESSONS.txt �zerinden kontenjan� azalt�p siler
		// B�rak�lm��sa direk siler
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
		while(!feof(fp1)){
			fscanf(fp1, "\n%d", &pairId);
			fscanf(fp1, "<%[^-]s", tmpStudent);
			fscanf(fp1, "-%[^>]s", tmpLesson);
			fscanf(fp1, ">%d", &status);
			fscanf(fp1, ";%[^\n]s", tmpStr);
			// dersi al�yorsa ders kontenjan� bir azalt�l�r
			if(strcmp(tmpStudent, studentId) == 0 && status == 1){
				fp3 = fopen("LESSONS.txt", "r");
				fp4 = fopen("NEW_LESSONS.txt", "w");
				while(!feof(fp3)){
					fscanf(fp3, "\n%[^;]s", newLesson->id);
					fscanf(fp3, ";%[^;]s", newLesson->name);
					fscanf(fp3, ";%[^;]s", newLesson->teacherId);
					fscanf(fp3, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
					// o derse gelindi�inde kontenjan azalt�l�r
					if(strcmp(newLesson->id, tmpLesson) == 0){
						newLesson->usedQuota = newLesson->usedQuota - 1;
					}
					// yeni dosyaya yaz�l�r
					fprintf(fp4,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
					newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
				}
				fclose(fp3);
				fclose(fp4);
				remove("LESSONS.txt"); // eski dosya silinir
				rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adland�r�l�r
			}
			// ��renciye ait b�rak�lm��/kay�tl� ders de�ilse yeni dosyaya yaz
			if(!(strcmp(tmpStudent, studentId) == 0)){
				fprintf(fp2,"\n%d<%s-%s>%d;%s", counter++, tmpStudent,
				tmpLesson, status, tmpStr);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("OgrenciDersKayit.txt");
		rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt");
		// 2) STUDENTS.txt �zerinden ��renci silinir
		fp1 = fopen("STUDENTS.txt", "r");
		fp2 = fopen("NEW_STUDENTS.txt", "w"); // g�ncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newStudent->id);
			fscanf(fp1, ";%[^;]s", newStudent->name);
			fscanf(fp1, ";%[^;]s", newStudent->surname);
			fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(!(strcmp(newStudent->id, studentId) == 0)){ // silinen ��renci d���ndakiler eklenir
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
				newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adland�r�l�r
		printf("\n (!) ��renci silme i�lemi tamamland�.\n");
	}
	free(studentId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}
void createTeacher(){ // ��r. �yesi olu�tur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) ��retim �yesi Ekleme ��lemi\n");
	printf("\n --> ��retim �yesi ID'si: ");
	scanf(" %[^\n]s", id); // ID al�n�r
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yap�l�r
	if(found == 0){ // ID yoksa ekleme yap�l�r
		strcpy(newTeacher->id, id);
		printf(" --> ��retim �yesinin Ad�: ");
		scanf(" %[^\n]s", newTeacher->name);
		printf(" --> ��retim �yesinin Soyad�: ");
		scanf(" %[^\n]s", newTeacher->surname);
		printf(" --> ��retim �yesinin Unvan�: ");
		scanf(" %[^\n]s", newTeacher->title);
		fp = fopen("TEACHERS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
		newTeacher->name, newTeacher->surname);
		fclose(fp);
		printf("\n (!) ��retim �yesi ekleme i�lemi tamamland�.\n");
	}else if(found == 1){ // ID varsa ekleme yap�lmaz
		printf("\n (!) Bu ID'ye sahip bir ��retim �yesi bulunmaktad�r.\n");
	}
	free(id);
	free(newTeacher);
}
void updateTeacher(){ // ��r. �yesi g�ncelle
	int found;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) ��retim �yesi G�ncelleme ��lemi\n");
	printf("\n --> G�ncellenecek ��retim �yesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID al�n�r
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yap�l�r
	if(found == 0){ // ID yoksa g�ncelleme yap�lmaz
		printf("\n (!) Bu ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n");
	}else if(found == 1){ // ID varsa g�ncelleme yap�l�r
		printf("\n (!) ��retim �yesi bulundu.");
		fp1 = fopen("TEACHERS.txt", "r");
		fp2 = fopen("NEW_TEACHERS.txt", "w"); // g�ncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newTeacher->id);
			fscanf(fp1, ";%[^;]s", newTeacher->title);
			fscanf(fp1, ";%[^;]s", newTeacher->name);
			fscanf(fp1, ";%[^\n]s", newTeacher->surname);
			if(strcmp(newTeacher->id, id) == 0){ // de�i�tirilecek ID i�in yeni de�erler al�n�r
				// anl�k bilgiler yazd�r�l�r
				printf("\n --- ��retim �yesi Unvan�: %s", newTeacher->title);
				printf("\n --- ��retim �yesi Ad�: %s", newTeacher->name);
				printf("\n --- ��retim �yesi Soyad�: %s\n", newTeacher->surname);
				// g�ncel bilgiler girilir
				printf("\n (!) G�ncel ��retim �yesi bilgilerini giriniz.\n");
				printf("\n --> G�ncel ��retim �yesi Ad�: ");
				scanf(" %[^\n]s", newTeacher->name);
				printf(" --> G�ncel ��retim �yesi Soyad�: ");
				scanf(" %[^\n]s", newTeacher->surname);
				printf(" --> G�ncel ��retim �yesi Unvan�: ");
				scanf(" %[^\n]s", newTeacher->title);
			}
			// yeni dosyaya yaz�l�r
			fprintf(fp2,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
			newTeacher->name, newTeacher->surname);
		}
		fclose(fp1);
		fclose(fp2);
		remove("TEACHERS.txt"); // eski dosya silinir
		rename("NEW_TEACHERS.txt", "TEACHERS.txt"); // yeni dosya yeniden adland�r�l�r
		printf("\n (!) ��retim �yesi g�ncelleme i�lemi tamamland�.\n");
	}
	free(id);
	free(newTeacher);
}
void deleteTeacher(){ // ��r. �yesi sil
	int found, control;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) ��retim �yesi Silme ��lemi\n");
	printf("\n --> Silinecek ��retim �yesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID al�n�r
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yap�l�r
	control = anyLesson(id); // ��retim �yesine ait ders var m�?
	if(found == 0){ // ID yoksa i�lem yap�lmaz
		printf("\n (!) Bu ID'ye sahip bir ��retim �yesi bulunmamaktad�r.\n");
	}else if(found == 1 && control == 1){
		printf("\n (!) Bu ��retim �yesine ait ders bulunmaktad�r.");
		printf("\n (!) Bir ��retim �yesini silmek i�in ��retim �yesinin");
		printf("\n     verdi�i herhangi bir ders bulunmamal�d�r.\n");
	}else if(found == 1 && control == 0){ // sorun yoksa i�lem yap�l�r
		fp1 = fopen("TEACHERS.txt", "r");
		fp2 = fopen("NEW_TEACHERS.txt", "w"); // g�ncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newTeacher->id);
			fscanf(fp1, ";%[^;]s", newTeacher->title);
			fscanf(fp1, ";%[^;]s", newTeacher->name);
			fscanf(fp1, ";%[^\n]s", newTeacher->surname);
			if(!(strcmp(newTeacher->id, id) == 0)){ // de�i�tirilecek ID i�in yeni de�erler al�n�r
				fprintf(fp2,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
				newTeacher->name, newTeacher->surname);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("TEACHERS.txt"); // eski dosya silinir
		rename("NEW_TEACHERS.txt", "TEACHERS.txt"); // yeni dosya yeniden adland�r�l�r
		printf("\n (!) ��retim �yesi silme i�lemi tamamland�.\n");
	}
	free(id);
	free(newTeacher);
}

// KOZMET�K MEN�LER
void mainSignIn(){ //ana giri� ekran�
	printf(" ________________________\n");
	printf(" |                      |\n");
	printf(" |  DERS KAYIT S�STEM�  |\n");
	printf(" |______________________|\n");
}
void mainMenu(){ // ana men�
	printf("\n- 1: ��renci Giri�i");
	printf("\n- 2: ��retim �yesi Giri�i");
	printf("\n- 3: Y�netici Giri�i\n");
	printf("\n- 0: ��k�� Yap\n");
}
void studentSignIn(){ // ��renci giri� ekran�
	printf(" ____________________\n");
	printf(" |                  |\n");
	printf(" |  ��renci Giri�i  |\n");
	printf(" |__________________|\n");
}
void studentMenu(){ // ��renci men�s�
	printf("\n- 1: Ders Ekle");
	printf("\n- 2: Ders B�rak");
	printf("\n- 3: Al�nan Dersler");
	printf("\n- 4: ��retim �yesi Ara\n");
	printf("\n- 9: Geri");
	printf("\n- 0: ��k�� Yap\n");
}
void teacherSignIn(){ // ��retim �yesi giri� ekran�
	printf(" __________________________\n");
	printf(" |                        |\n");
	printf(" |  ��retim �yesi Giri�i  |\n");
	printf(" |________________________|\n");
}
void teacherMenu(){ // ��retim �yesi men�s�
	printf("\n- 1: Ders Olu�tur");
	printf("\n- 2: Ders G�ncelle");
	printf("\n- 3: Ders Sil\n");
	printf("\n- 4: Verilen Dersler");
	printf("\n- 5: Ders S�n�f Listesi ��ren");
	printf("\n- 6: Yoklama Listesi Olu�tur\n");
	printf("\n- 9: Geri");
	printf("\n- 0: ��k�� Yap\n");
}
void adminSignIn(){ // y�netici giri� ekran�
	printf(" _____________________\n");
	printf(" |                   |\n");
	printf(" |  Y�netici Giri�i  |\n");
	printf(" |___________________|\n");
}
void adminMenu(){ // y�netici men�s�
	printf("\n- 1: ��renci Ekle");
	printf("\n- 2: ��renci G�ncelle");
	printf("\n- 3: ��renci Sil\n");
	printf("\n- 4: ��retim �yesi Ekle");
	printf("\n- 5: ��retim �yesi G�ncelle");
	printf("\n- 6: ��retim �yesi Sil\n");
	printf("\n- 9: Geri");
	printf("\n- 0: ��k�� Yap\n");
}
int doneMenu(){ // i�lem bittikten sonra ��kan men�
	// return 0 --> ��k�� yap
	// return 1 --> geri git
	int cmd;
	printf("\n- 9: Geri");
	printf("\n- 0: ��k�� Yap\n");
	cmd = getCmd(4);
	if(cmd == 0){
		return 0;
	}else if(cmd == 9){
		return 1;
	}
}
