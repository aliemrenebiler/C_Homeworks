#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct student{ // ÖÐRENCÝ
	char id[20]; // öðrenci numarasý
	char name[20]; // isim
	char surname[20]; // soyisim
	int totalLesson; // kaydolduðu toplam ders sayýsý
	int totalCredit; // kaydolduðu toplam kredi sayýsý
}STUDENT;
typedef struct teacher{ // ÖÐRETÝM ÜYESÝ
	char id[20]; // ID
	char title[20]; // unvan
	char name[20]; // isim
	char surname[20]; // soyisim
}TEACHER;
typedef struct lesson{ // DERS
	char id[20]; // ders kodu
	char name[50]; // ders ismi
	int credit; // kredisi
	int usedQuota; // dolmuþ kontenjan
	char teacherId[20]; // dersi veren öðretim üyesinin ID'si
}LESSON;
typedef struct date{ // DERS
	int hour, min;
	int day, month, year;
}DATE;

// GENEL FONKSÝYONLAR
int getCmd(int);
int idCheck(char*, char*);
void setTime(DATE*);
void createTxtFiles();

// KONTROL FONKSÝYONLARI
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

// ARAMA FONKSÝYONLARI
void findStudent(char*, STUDENT*);
void findTeacher(char*, TEACHER*);
void findLesson(char*, LESSON*);

// ÖÐRENCÝ FONKSÝYONLARI
void addLesson(char*, int, int);
void quitLesson(char*);
void studentsLessons(char*);
void searchTeacher();

// ÖÐRETÝM ÜYESÝ FONKSÝYONLARI
void createLesson(char*);
void updateLesson(char*);
void deleteLesson(char*);
void teachersLessons(char*);
void searchLesson();
void attendanceList(char*);

// YÖNETÝCÝ FONKSÝYONLARI
void createStudent();
void updateStudent();
void deleteStudent();
void createTeacher();
void updateTeacher();
void deleteTeacher();

// KOZMETÝK MENÜLER
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
	int maxQuota; // her dersin max kontenjaný
	int maxCredit; // her öðrencinin max kredisi
	
	// dosyalar yoksa oluþtur
	createTxtFiles();
	
	// program baþlangýcý
	printf("\n --> Ders Kontenjan Sýnýrý: ");
	scanf(" %d", &maxQuota);
	printf(" --> Öðrenci Kredi Sýnýrý: ");
	scanf(" %d", &maxCredit);
	do{ // çýkýþ yapana kadar yap
		mainSignIn();
		mainMenu();
		cmd = getCmd(0);
		if(cmd == 1){ // ÖÐRENCÝ GÝRÝÞÝ
			studentSignIn();
			printf("\n --> Öðrenci Numarasý: ");
			scanf(" %[^\n]s", currentId); // öðrenci numarasý alýnýr
			cmd = idCheck(currentId, "STUDENTS.txt");
			if(cmd == 2){
				do{ // geri gidene veya çýkýþ yapana kadar yap
					printf("\n (!) Hoþgeldiniz!");
					printf("\n (!) ID: %s\n", currentId);
					studentMenu();
					cmd = getCmd(1);
					if(cmd == 1){ // ders ekle
						addLesson(currentId, maxCredit, maxQuota);
						cmd = doneMenu();
					}else if(cmd == 2){ // ders kaldýr
						quitLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 3){ // alýnan dersleri öðren
						studentsLessons(currentId);
						cmd = doneMenu();
					}else if(cmd == 4){ // bir öðr. üyesinin verdiði dersleri öðren
						searchTeacher();
						cmd = doneMenu();
					}
				}while(cmd != 0 && cmd != 9);
			}
		}else if(cmd == 2){ // ÖÐRETÝM ÜYESÝ GÝRÝÞÝ
			teacherSignIn();
			printf("\n --> Öðretim Üyesi ID'si: ");
			scanf(" %[^\n]s", currentId); // ID alýnýr
			cmd = idCheck(currentId, "TEACHERS.txt");
			if(cmd == 2){
				do{ // geri gidene veya çýkýþ yapana kadar yap
					printf("\n (!) Hoþgeldiniz!");
					printf("\n (!) ID: %s\n", currentId);
					teacherMenu();
					cmd = getCmd(2);
					if(cmd == 1){ // ders oluþtur
						createLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 2){ // ders güncelle
						updateLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 3){ // ders sil
						deleteLesson(currentId);
						cmd = doneMenu();
					}else if(cmd == 4){ // verilen dersler
						teachersLessons(currentId);
						cmd = doneMenu();
					}else if(cmd == 5){ // bir dersin kontenjanýný öðren
						searchLesson();
						cmd = doneMenu();
					}else if(cmd == 6){ // yoklama listesi oluþtur
						attendanceList(currentId);
						cmd = doneMenu();
					}
				}while(cmd != 0 && cmd != 9);
			}
		}else if(cmd == 3){ // YÖNETÝCÝ GÝRÝÞÝ
			do{ // geri gidene veya çýkýþ yapana kadar yap
				adminSignIn();
				adminMenu();
				cmd = getCmd(3);
				if(cmd == 1){ // öðrenci ekle
					createStudent();
					cmd = doneMenu();
				}else if(cmd == 2){ // öðrenci güncelle
					updateStudent();
					cmd = doneMenu();
				}else if(cmd == 3){ // öðrenci sil
					deleteStudent();
					cmd = doneMenu();
				}else if(cmd == 4){ // öðr. üyesi ekle
					createTeacher();
					cmd = doneMenu();
				}else if(cmd == 5){ // öðr. üyesi güncelle
					updateTeacher();
					cmd = doneMenu();
				}else if(cmd == 6){ // öðr. üyesi sil
					deleteTeacher();
					cmd = doneMenu();
				}
			}while(cmd != 0 && cmd != 9);
		}
	}while(cmd != 0);
	printf("\n (!) Çýkýþ yapýldý.\n");
	printf(" _________________\n");
	printf(" |               |\n");
	printf(" |  Ýyi günler!  |\n");
	printf(" |_______________|\n");
	return 0;
}

// GENEL FONKSÝYONLAR
int getCmd(int X){ // doðru komutu almayý saðlar
	// X == 0 --> ana menü
	// X == 1 --> öðrenci giriþi
	// X == 2 --> öðr. üyesi giriþi
	// X == 3 --> yönetici giriþi
	// X == 4 --> iþlem sonu sayfasý
	int cmd;
	if(X == 0){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 && cmd != 0){
				printf("\n (!) Yanlýþ komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 && cmd != 0);
	}else if(X == 1){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 9 && cmd != 0){
				printf("\n (!) Yanlýþ komut!\n");
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
				printf("\n (!) Yanlýþ komut!\n");
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
				printf("\n (!) Yanlýþ komut!\n");
			}
		}while(cmd != 1 && cmd != 2 && cmd != 3 &&
			   cmd != 4 && cmd != 5 && cmd != 6 &&
			   cmd != 9 && cmd != 0);
	}else if(X == 4){
		do{
			printf("\n --> Komut: ");
			scanf("%d", &cmd);
			if(cmd != 9 && cmd != 0){
				printf("\n (!) Yanlýþ komut!\n");
			}
		}while(cmd != 9 && cmd != 0);
	}
	return cmd;
}
int idCheck(char *id, char *fileName){ // ID kontrolü ile giriþ yapar
	// return 0 --> çýkýþ yap
	// return 1 --> geri
	// return 2 --> giriþ yapýldý
	int found = 0;
	int cmd;
	found = searchById(id, fileName);
	if(found == 0){
		printf("\n (!) ID bulunamadý.\n");
		cmd = doneMenu();
	}else if(found == 1){
		printf("\n (!) Giriþ yapýldý.");
		cmd = 2;
	}
	return cmd;
}
void setTime(DATE *date){ // anlýk zamaný ve tarihi alýr
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

// KONTROL FONKSÝYONLARI
int searchById(char *id, char *fileName){ // ID ile arama yapar
	// found == 0 --> ID bulunamadý
	// found == 1 --> ID bulundu
	// found == 2 --> dosya bulunamadý
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
		printf("\n (!) Dosya bulunamadý.\n");
		found = 2;
	}
	free(tmpId);
	free(tmpStr);
	return found;
}
int controlLesson(char *lessonId, char *teacherId){ // girilen dersin, öðr. üyesine aitliðini kontrol eder
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
int anyLesson(char *teacherId){ // öðretim üyesine ait ders olup olmadýðýný kontrol eder
	// return 0 --> hiç ders yok
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
int getLessonControl(char *studentId, char *lessonId){ // öðrencinin dersi alýp almadýðýný kontrol eder
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
int getAnyLessonControl(char *studentId){ // öðrencinin herhangi bir ders alýp almadýðýný kontrol eder
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
int anyoneGetLessonControl(char *lessonId){ // dersi alan öðrenci olup olmadýðýný kontrol eder
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
int creditControl(char *studentId, char *lessonId, int maxCredit){ // öðrenci kredi durumunu kontrol eder
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
int addControl(char *studentId, char *lessonId){ // dersin önceden eklenip eklenmediðini kontrol eder
	// return 0 --> dersi zaten alýyor
	// return 1 --> dersi hiç almamýþ
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
int emptyFile(char *fileName){ // dosyanýn boþ olup olmadýðýný kontrol eder
	// return 0 --> boþ
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

// ARAMA FONKSÝYONLARI
void findStudent(char *studentId, STUDENT *newStudent){ // öðrenci bul ve bilgilerini al
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
void findTeacher(char *teacherId, TEACHER *newTeacher){ // öðr. üyesi bul ve bilgilerini al
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

// ÖÐRENCÝ FONKSÝYONLARI
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
	printf("\n (!) Ders Ekleme Ýþlemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu alýnýr
	found = searchById(lessonId, "LESSONS.txt");
	control1 = addControl(studentId, lessonId);
	control2 = creditControl(studentId, lessonId, maxCredit); // öðrencinin kredisi yetiyor mu?
	control3 = quotaControl(lessonId, maxQuota); // derste yer var mý?
	if(found == 0){ // ID yoksa ekleme yapýlmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
	}else if(found == 1 && control1 == 0){ // önceden eklendiyse ekleme yapýlmaz
		printf("\n (!) Bu dersi zaten alýyorsunuz.\n");
	}else if(found == 1 && control2 == 0){ // yeterli kredi yoksa ekleme yapýlmaz
		printf("\n (!) Yeterli krediniz kalmamýþtýr.\n");
	}else if(found == 1 && control3 == 0){ // kontenjan doluysa ekleme yapýlmaz
		printf("\n (!) Ders kontenjaný dolmuþtur.\n");
	}else if(found == 1 && control1 == 1 && control2 == 1 && control3 == 1){
		// 1) OgrenciDersKayit.txt dosyasýna ekleme yapýlýr
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
		control1 = emptyFile("OgrenciDersKayit.txt");
		if(control1){ // dosya doluysa bu iþlemi yap
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
		rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt"); // yeni dosya yeniden adlandýrýlýr
		// 2) öðrencinin aldýðý ders ve kredi eklenir
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
			// yeni dosyaya yazýlýr
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
			newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adlandýrýlýr
		// 3) ders kontenjaný arttýrýlýr
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
			// yeni dosyaya yazýlýr
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
			newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
		}
		fclose(fp1);
		fclose(fp2);
		remove("LESSONS.txt"); // eski dosya silinir
		rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adlandýrýlýr
		printf("\n (!) Ders ekleme iþlemi tamamlandý.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
	free(date);
}
void quitLesson(char *studentId){ // ders býrak
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
	printf("\n (!) Ders Býrakma Ýþlemi\n");
	control = getAnyLessonControl(studentId);
	if(control){ // alýnan herhangi bir ders yoksa iþlem yapma
		printf("\n --> Býrakmak Ýstediðiniz Dersin Kodu: ");
		scanf(" %[^\n]s", lessonId); // ders kodu alýnýr
		found = searchById(lessonId, "LESSONS.txt"); // ders var mý?
		control = getLessonControl(studentId, lessonId); // dersi alýyor mu?
		if(found == 0){ // ders yoksa iþlem yapma
			printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
		}else if(found == 1 && control == 0){ // dersi almýyorsa iþlem yapma
			printf("\n (!) Bu dersi zaten almamaktasýnýz.\n");
		}else if(found == 1 && control == 1){
			// 1) OgrenciDersKayit.txt'deki ders alma durumu 0 yapýlýr
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
				// eðer silindiyse tarihi güncelle
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
			// 2) öðrencinin býraktýðý ders ve kredi çýkarýlýr
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
				// yeni dosyaya yazýlýr
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
				newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
			}
			fclose(fp1);
			fclose(fp2);
			remove("STUDENTS.txt"); // eski dosya silinir
			rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adlandýrýlýr
			// 3) ders kontenjaný azaltýlýr
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
				// yeni dosyaya yazýlýr
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
				newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adlandýrýlýr
			printf("\n (!) Ders býrakma iþlemi tamamlandý.\n");
		}
	}else{
		printf("\n (!) Aldýðýnýz herhangi bir ders bulunmamaktadýr.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
	free(date);
}
void studentsLessons(char *studentId){ // öðrencinin aldýðý dersleri yazdýrýr
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
		printf("\n (!) Aldýðýnýz Dersler:\n");
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
				printf(" --- %s --> %s --> Öðr. Üyesi: %s %s %s\n", newLesson->id, newLesson->name,
				newTeacher->title, newTeacher->name, newTeacher->surname);
			}
		}
		fclose(fp);
	}else{
		printf("\n (!) Aldýðýnýz herhangi bir ders bulunmamaktadýr.\n");
	}
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newTeacher);
}
void searchTeacher(){ // ID'si girilen öðr. üyesinin verdiði dersler
	int found, control;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) Öðretim Üyesi Arama Ýþlemi\n");
	// öðretim üyelerini yazdýr
	printf("\n (!) Aþaðýdaki öðr. üyelerinin ID'lerini aratarak");
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
	// öðretim üyesi ID al
	printf("\n --> Aramak Ýstediðiniz Öðretim Üyesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID alýnýr
	found = searchById(id, "TEACHERS.txt"); // öðretim üyesi var mý?
	control = anyLesson(id); // öðretim üyesinin verdiði ders var mý?
	if(found == 0){ // öðretim üyesi yoksa uyar
		printf("\n (!) Bu ID'ye sahip bir öðretim üyesi bulunmamaktadýr.\n");
	}else if(found == 1 && control == 0){ // öðretim üyesinin dersi yoksa uyar
		printf("\n (!) Bu öðretim üyesinin verdiði herhangi bir ders bulunmamaktadýr.\n");
	}else if(found == 1 && control == 1){ // dersi varsa yazdýr
		fp = fopen("LESSONS.txt", "r");
		printf("\n (!) %s ID'li öðretim üyesinin verdiði dersler:\n", id);
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

// ÖÐRETÝM ÜYESÝ FONKSÝYONLARI
void createLesson(char *teacherId){ // ders oluþtur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) Ders Oluþturma Ýþlemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", id); // ders kodu alýnýr
	found = searchById(id, "LESSONS.txt");
	if(found == 0){ // ID yoksa ekleme yapýlýr
		strcpy(newLesson->id, id);
		printf(" --> Dersin Adý: ");
		scanf(" %[^\n]s", newLesson->name);
		printf(" --> Dersin Kredisi: ");
		scanf("%d", &newLesson->credit);
		strcpy(newLesson->teacherId, teacherId);
		newLesson->usedQuota = 0;
		fp = fopen("LESSONS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
		newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
		fclose(fp);
		printf("\n (!) Ders oluþturma iþlemi tamamlandý.\n");
	}else if(found == 1){ // ID varsa ekleme yapýlmaz
		printf("\n (!) Bu koda sahip bir ders bulunmaktadýr.\n");
	}
	free(id);
	free(newLesson);
}
void updateLesson(char *teacherId){ // ders güncelle
	int found, control;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	printf("\n (!) Ders Güncelleme Ýþlemi\n");
	control = anyLesson(teacherId);
	if(control){
		printf(" (!) ÖNEMLÝ: Kredi deðiþikliði, dersi önceden");
		printf("\n     alan öðrencileri etkilemeyecektir.\n");
		printf("\n --> Güncellenecek Dersin Kodu: ");
		scanf(" %[^\n]s", id); // ID alýnýr
		found = searchById(id, "LESSONS.txt"); // ID ile arama yapýlýr
		control = controlLesson(id, teacherId); // ders öðr. üyesine ait mi kontrolü
		if(found == 0){ // ID yoksa güncelleme yapýlmaz
			printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
		}else if(found == 1 && control == 0){ // Ders giren kiþiye ait deðilse güncelleme yapýlmaz
			printf("\n (!) Bu koda sahip ders, size ait deðildir.\n");
		}else if(found == 1 && control == 1){ // ID varsa güncelleme yapýlýr
			printf("\n (!) Ders bulundu.");
			fp1 = fopen("LESSONS.txt", "r");
			fp2 = fopen("NEW_LESSONS.txt", "w"); // güncel hal
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newLesson->id);
				fscanf(fp1, ";%[^;]s", newLesson->name);
				fscanf(fp1, ";%[^;]s", newLesson->teacherId);
				fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
				if(strcmp(newLesson->id, id) == 0){ // deðiþtirilecek ID için yeni deðerler alýnýr
					// anlýk bilgiler yazdýrýlýr
					printf("\n --- Ders Adý: %s", newLesson->name);
					printf("\n --- Dersin Kredisi: %d\n", newLesson->credit);
					// güncel bilgiler girilir
					printf("\n (!) Güncel ders bilgilerini giriniz.");
					printf("\n --> Güncel Ders Adý: ");
					scanf(" %[^\n]s", newLesson->name);
					printf(" --> Güncel Ders Kredisi: ");
					scanf("%d", &newLesson->credit);
				}
				// yeni dosyaya yazýlýr
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
				newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adlandýrýlýr
			printf("\n (!) Ders güncelleme iþlemi tamamlandý.\n");
		}
	}else{
		printf("\n (!) Size ait herhangi bir ders bulunmamaktadýr.\n");
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
	printf("\n (!) Ders Silme Ýþlemi\n");
	control = anyLesson(teacherId);
	if(control){
		printf("\n --> Silinecek Dersin Kodu: ");
		scanf(" %[^\n]s", lessonId); // ID alýnýr
		found = searchById(lessonId, "LESSONS.txt"); // ID ile arama yapýlýr
		control = controlLesson(lessonId, teacherId); // ders öðr. üyesine ait mi kontrolü
		if(found == 0){ // ID yoksa güncelleme yapýlmaz
			printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
		}else if(found == 1 && control == 0){ // Ders giren kiþiye ait deðilse güncelleme yapýlmaz
			printf("\n (!) Bu koda sahip ders, size ait deðildir.\n");
		}else if(found == 1 && control == 1){ // ID varsa güncelleme yapýlýr
			// 1) dersi alan/býrakan öðrencilerde deðiþiklik yapýlýr
			fp1 = fopen("OgrenciDersKayit.txt", "r");
			fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
			findLesson(lessonId, newLesson);
			while(!feof(fp1)){
				fscanf(fp1, "\n%d", &pairId);
				fscanf(fp1, "<%[^-]s", tmpStudent);
				fscanf(fp1, "-%[^>]s", tmpLesson);
				fscanf(fp1, ">%d", &status);
				fscanf(fp1, ";%[^\n]s", tmpStr);
				// dersi alan öðrenciler güncellenir
				if(strcmp(tmpLesson, lessonId) == 0 && status == 1){
					fp3 = fopen("STUDENTS.txt", "r");
					fp4 = fopen("NEW_STUDENTS.txt", "w");
					while(!feof(fp3)){
						fscanf(fp3, "\n%[^;]s", newStudent->id);
						fscanf(fp3, ";%[^;]s", newStudent->name);
						fscanf(fp3, ";%[^;]s", newStudent->surname);
						fscanf(fp3, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
						// o öðrenciye gelindiðinde kredi ve alýnan ders azaltýlýr
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
					rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adlandýrýlýr
				}
				// o ders olmayan diðer tüm dersler yazýlýr
				if(!(strcmp(tmpLesson, lessonId) == 0)){
					fprintf(fp2,"\n%d<%s-%s>%d;%s", counter++, tmpStudent,
					tmpLesson, status, tmpStr);
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("OgrenciDersKayit.txt");
			rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt");
			// 2) ders, diðer dersler arasýndan silinir
			fp1 = fopen("LESSONS.txt", "r");
			fp2 = fopen("NEW_LESSONS.txt", "w"); // güncel hal
			while(!feof(fp1)){
				fscanf(fp1, "\n%[^;]s", newLesson->id);
				fscanf(fp1, ";%[^;]s", newLesson->name);
				fscanf(fp1, ";%[^;]s", newLesson->teacherId);
				fscanf(fp1, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
				if(!(strcmp(newLesson->id, lessonId) == 0)){ // silinen ders dýþýndakiler yazdýrýlýr
					fprintf(fp2,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
					newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
				}
			}
			fclose(fp1);
			fclose(fp2);
			remove("LESSONS.txt"); // eski dosya silinir
			rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adlandýrýlýr
			printf("\n (!) Ders silme iþlemi tamamlandý.\n");
		}
	}else{
		printf("\n (!) Size ait herhangi bir ders bulunmamaktadýr.\n");
	}
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}
void teachersLessons(char *teacherId){ // verilen dersleri yazdýrýr
	int control;
	FILE *fp;
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	control = anyLesson(teacherId); // öðretim üyesinin verdiði ders var mý?
	if(!control){ // öðretim üyesinin dersi yoksa uyar
		printf("\n (!) Verdiðiniz herhangi bir ders bulunmamaktadýr.\n");
	}else{ // dersi varsa yazdýr
		fp = fopen("LESSONS.txt", "r");
		printf("\n (!) Verdiðiniz dersler:\n");
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
void searchLesson(){ // ID'si girilen dersi alan öðrencileri yazdýrýr
	int found, control;
	int pairId, status;
	FILE *fp;
	char *lessonId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Ders Sýnýf Listesi Öðrenme Ýþlemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu alýnýr
	found = searchById(lessonId, "LESSONS.txt"); // ders var mý?
	control = anyoneGetLessonControl(lessonId); // dersi alan öðrenci var mý?
	if(found == 0){ // ders yoksa iþlem yapýlmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
	}else if(found == 1 && control == 0){ // dersi alan yoksa iþlem yapýlmaz
		printf("\n (!) Bu dersi alan herhangi bir öðrenci bulunmamaktadýr.\n");
	}else if(found == 1 && control == 1){ // dersi alan varsa yazdýrýlýr
		printf("\n (!) %s Kodlu Dersin Kontenjaný\n", lessonId);
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
void attendanceList(char *teacherId){ // ID'si girilen dersi alan öðrencileri txt'de listeler
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
	printf("\n (!) Yoklama Listesi Oluþturma Ýþlemi\n");
	printf("\n --> Ders Kodu: ");
	scanf(" %[^\n]s", lessonId); // ders kodu alýnýr
	found = searchById(lessonId, "LESSONS.txt"); // ders var mý?
	control1 = controlLesson(lessonId, teacherId); // bu ders öðr. üyesine ait mi?
	control2 = anyoneGetLessonControl(lessonId); // dersi alan öðrenci var mý?
	if(found == 0){ // ders yoksa iþlem yapýlmaz
		printf("\n (!) Bu koda sahip bir ders bulunmamaktadýr.\n");
	}else if(found == 1 && control1 == 0){ // ders öðr. üyesine ait deðilse iþlem yapmaz
		printf("\n (!) Bu ders size ait deðildir.\n");
	}else if(found == 1 && control2 == 0){ // dersi alan yoksa iþlem yapýlmaz
		printf("\n (!) Bu dersi alan herhangi bir öðrenci bulunmamaktadýr.\n");
	}else if(found == 1 && control1 == 1 && control2 == 1){ // sorun yoksa dosya oluþturulur
		strcpy(fileName, lessonId);
		strcat(fileName, "_SINIF_LISTESI.txt");
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen(fileName, "w");
		fprintf(fp2, "\n --- %s Kodlu Dersin Sýnýf Listesi --- \n\n", lessonId);
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
		printf("\n (!) Yoklama listesi baþarýyla oluþturuldu.\n");
	}
	free(fileName);
	free(lessonId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}

// YÖNETÝCÝ FONKSÝYONLARI
void createStudent(){ // öðrenci oluþtur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Öðrenci Ekleme Ýþlemi\n");
	printf("\n --> Öðrenci Numarasý: ");
	scanf(" %[^\n]s", id); // öðrenci numarasý alýnýr
	found = searchById(id, "STUDENTS.txt"); // ID ile arama yapýlýr
	if(found == 0){ // ID yoksa ekleme yapýlýr
		strcpy(newStudent->id, id);
		printf(" --> Öðrencinin Adý: ");
		scanf(" %[^\n]s", newStudent->name);
		printf(" --> Öðrencinin Soyadý: ");
		scanf(" %[^\n]s", newStudent->surname);
		newStudent->totalCredit = 0;
		newStudent->totalLesson = 0;
		fp = fopen("STUDENTS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
		newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		fclose(fp);
		printf("\n (!) Öðrenci ekleme iþlemi tamamlandý.\n");
	}else if(found == 1){ // ID varsa ekleme yapýlmaz
		printf("\n (!) Bu numaraya sahip bir öðrenci bulunmaktadýr.\n");
	}
	free(id);
	free(newStudent);
}
void updateStudent(){ // öðrenci güncelle
	int found;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Öðrenci Güncelleme Ýþlemi\n");
	printf("\n --> Güncellenecek Öðrencinin Numarasý: ");
	scanf(" %[^\n]s", id); // ID alýnýr
	found = searchById(id, "STUDENTS.txt"); // ID ile arama yapýlýr
	if(found == 0){ // ID yoksa güncelleme yapýlmaz
		printf("\n (!) Bu numaraya sahip bir öðrenci bulunmamaktadýr.\n");
	}else if(found == 1){ // ID varsa güncelleme yapýlýr
		printf("\n (!) Öðrenci bulundu.");
		fp1 = fopen("STUDENTS.txt", "r");
		fp2 = fopen("NEW_STUDENTS.txt", "w"); // güncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newStudent->id);
			fscanf(fp1, ";%[^;]s", newStudent->name);
			fscanf(fp1, ";%[^;]s", newStudent->surname);
			fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(strcmp(newStudent->id, id) == 0){ // deðiþtirilecek ID için yeni deðerler alýnýr
				// anlýk bilgiler yazdýrýlýr
				printf("\n --- Öðrenci Adý: %s", newStudent->name);
				printf("\n --- Öðrenci Soyadý: %s\n", newStudent->surname);
				// güncel bilgiler girilir
				printf("\n (!) Güncel öðrenci bilgilerini giriniz.");
				printf("\n --> Güncel Öðrenci Adý: ");
				scanf(" %[^\n]s", newStudent->name);
				printf(" --> Güncel Öðrenci Soyadý: ");
				scanf(" %[^\n]s", newStudent->surname);
			}
			// yeni dosyaya yazýlýr
			fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
			newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adlandýrýlýr
		printf("\n (!) Öðrenci güncelleme iþlemi tamamlandý.\n");
	}
	free(id);
	free(newStudent);
}
void deleteStudent(){ // öðrenci sil
	int found, control;
	int pairId, status, counter = 1;
	FILE *fp1, *fp2, *fp3, *fp4;
	char *studentId = (char*)malloc(20*sizeof(char));
	char *tmpStudent = (char*)malloc(20*sizeof(char));
	char *tmpLesson = (char*)malloc(20*sizeof(char));
	char *tmpStr = (char*)malloc(20*sizeof(char));
	LESSON *newLesson = (LESSON*)malloc(sizeof(LESSON));
	STUDENT *newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	printf("\n (!) Öðrenci Silme Ýþlemi\n");
	printf("\n --> Silinecek Öðrencinin Numarasý: ");
	scanf(" %[^\n]s", studentId); // ID alýnýr
	found = searchById(studentId, "STUDENTS.txt"); // ID ile arama yapýlýr
	if(found == 0){ // ID yoksa iþlem yapýlmaz
		printf("\n (!) Bu numaraya sahip bir öðrenci bulunmamaktadýr.\n");
	}else if(found == 1){ // ID varsa iþlem yapýlýr
		// 1) OgrenciDersKayit.txt üzerinden dersleri sil
		// Býrakýlmamýþsa LESSONS.txt üzerinden kontenjaný azaltýp siler
		// Býrakýlmýþsa direk siler
		fp1 = fopen("OgrenciDersKayit.txt", "r");
		fp2 = fopen("NEW_OgrenciDersKayit.txt", "w");
		while(!feof(fp1)){
			fscanf(fp1, "\n%d", &pairId);
			fscanf(fp1, "<%[^-]s", tmpStudent);
			fscanf(fp1, "-%[^>]s", tmpLesson);
			fscanf(fp1, ">%d", &status);
			fscanf(fp1, ";%[^\n]s", tmpStr);
			// dersi alýyorsa ders kontenjaný bir azaltýlýr
			if(strcmp(tmpStudent, studentId) == 0 && status == 1){
				fp3 = fopen("LESSONS.txt", "r");
				fp4 = fopen("NEW_LESSONS.txt", "w");
				while(!feof(fp3)){
					fscanf(fp3, "\n%[^;]s", newLesson->id);
					fscanf(fp3, ";%[^;]s", newLesson->name);
					fscanf(fp3, ";%[^;]s", newLesson->teacherId);
					fscanf(fp3, ";%d;%d", &newLesson->credit, &newLesson->usedQuota);
					// o derse gelindiðinde kontenjan azaltýlýr
					if(strcmp(newLesson->id, tmpLesson) == 0){
						newLesson->usedQuota = newLesson->usedQuota - 1;
					}
					// yeni dosyaya yazýlýr
					fprintf(fp4,"\n%s;%s;%s;%d;%d", newLesson->id, newLesson->name,
					newLesson->teacherId, newLesson->credit, newLesson->usedQuota);
				}
				fclose(fp3);
				fclose(fp4);
				remove("LESSONS.txt"); // eski dosya silinir
				rename("NEW_LESSONS.txt", "LESSONS.txt"); // yeni dosya yeniden adlandýrýlýr
			}
			// öðrenciye ait býrakýlmýþ/kayýtlý ders deðilse yeni dosyaya yaz
			if(!(strcmp(tmpStudent, studentId) == 0)){
				fprintf(fp2,"\n%d<%s-%s>%d;%s", counter++, tmpStudent,
				tmpLesson, status, tmpStr);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("OgrenciDersKayit.txt");
		rename("NEW_OgrenciDersKayit.txt", "OgrenciDersKayit.txt");
		// 2) STUDENTS.txt üzerinden öðrenci silinir
		fp1 = fopen("STUDENTS.txt", "r");
		fp2 = fopen("NEW_STUDENTS.txt", "w"); // güncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newStudent->id);
			fscanf(fp1, ";%[^;]s", newStudent->name);
			fscanf(fp1, ";%[^;]s", newStudent->surname);
			fscanf(fp1, ";%d;%d", &newStudent->totalCredit, &newStudent->totalLesson);
			if(!(strcmp(newStudent->id, studentId) == 0)){ // silinen öðrenci dýþýndakiler eklenir
				fprintf(fp2,"\n%s;%s;%s;%d;%d", newStudent->id, newStudent->name,
				newStudent->surname, newStudent->totalCredit, newStudent->totalLesson);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("STUDENTS.txt"); // eski dosya silinir
		rename("NEW_STUDENTS.txt", "STUDENTS.txt"); // yeni dosya yeniden adlandýrýlýr
		printf("\n (!) Öðrenci silme iþlemi tamamlandý.\n");
	}
	free(studentId);
	free(tmpStudent);
	free(tmpLesson);
	free(tmpStr);
	free(newLesson);
	free(newStudent);
}
void createTeacher(){ // öðr. üyesi oluþtur
	int found;
	FILE *fp;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) Öðretim Üyesi Ekleme Ýþlemi\n");
	printf("\n --> Öðretim Üyesi ID'si: ");
	scanf(" %[^\n]s", id); // ID alýnýr
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yapýlýr
	if(found == 0){ // ID yoksa ekleme yapýlýr
		strcpy(newTeacher->id, id);
		printf(" --> Öðretim Üyesinin Adý: ");
		scanf(" %[^\n]s", newTeacher->name);
		printf(" --> Öðretim Üyesinin Soyadý: ");
		scanf(" %[^\n]s", newTeacher->surname);
		printf(" --> Öðretim Üyesinin Unvaný: ");
		scanf(" %[^\n]s", newTeacher->title);
		fp = fopen("TEACHERS.txt", "a");
		fprintf(fp,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
		newTeacher->name, newTeacher->surname);
		fclose(fp);
		printf("\n (!) Öðretim üyesi ekleme iþlemi tamamlandý.\n");
	}else if(found == 1){ // ID varsa ekleme yapýlmaz
		printf("\n (!) Bu ID'ye sahip bir öðretim üyesi bulunmaktadýr.\n");
	}
	free(id);
	free(newTeacher);
}
void updateTeacher(){ // öðr. üyesi güncelle
	int found;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) Öðretim Üyesi Güncelleme Ýþlemi\n");
	printf("\n --> Güncellenecek Öðretim Üyesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID alýnýr
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yapýlýr
	if(found == 0){ // ID yoksa güncelleme yapýlmaz
		printf("\n (!) Bu ID'ye sahip bir öðretim üyesi bulunmamaktadýr.\n");
	}else if(found == 1){ // ID varsa güncelleme yapýlýr
		printf("\n (!) Öðretim üyesi bulundu.");
		fp1 = fopen("TEACHERS.txt", "r");
		fp2 = fopen("NEW_TEACHERS.txt", "w"); // güncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newTeacher->id);
			fscanf(fp1, ";%[^;]s", newTeacher->title);
			fscanf(fp1, ";%[^;]s", newTeacher->name);
			fscanf(fp1, ";%[^\n]s", newTeacher->surname);
			if(strcmp(newTeacher->id, id) == 0){ // deðiþtirilecek ID için yeni deðerler alýnýr
				// anlýk bilgiler yazdýrýlýr
				printf("\n --- Öðretim Üyesi Unvaný: %s", newTeacher->title);
				printf("\n --- Öðretim Üyesi Adý: %s", newTeacher->name);
				printf("\n --- Öðretim Üyesi Soyadý: %s\n", newTeacher->surname);
				// güncel bilgiler girilir
				printf("\n (!) Güncel öðretim üyesi bilgilerini giriniz.\n");
				printf("\n --> Güncel Öðretim Üyesi Adý: ");
				scanf(" %[^\n]s", newTeacher->name);
				printf(" --> Güncel Öðretim Üyesi Soyadý: ");
				scanf(" %[^\n]s", newTeacher->surname);
				printf(" --> Güncel Öðretim Üyesi Unvaný: ");
				scanf(" %[^\n]s", newTeacher->title);
			}
			// yeni dosyaya yazýlýr
			fprintf(fp2,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
			newTeacher->name, newTeacher->surname);
		}
		fclose(fp1);
		fclose(fp2);
		remove("TEACHERS.txt"); // eski dosya silinir
		rename("NEW_TEACHERS.txt", "TEACHERS.txt"); // yeni dosya yeniden adlandýrýlýr
		printf("\n (!) Öðretim üyesi güncelleme iþlemi tamamlandý.\n");
	}
	free(id);
	free(newTeacher);
}
void deleteTeacher(){ // öðr. üyesi sil
	int found, control;
	FILE *fp1, *fp2;
	char *id = (char*)malloc(20*sizeof(char));
	TEACHER *newTeacher = (TEACHER*)malloc(sizeof(TEACHER));
	printf("\n (!) Öðretim Üyesi Silme Ýþlemi\n");
	printf("\n --> Silinecek Öðretim Üyesinin ID'si: ");
	scanf(" %[^\n]s", id); // ID alýnýr
	found = searchById(id, "TEACHERS.txt"); // ID ile arama yapýlýr
	control = anyLesson(id); // öðretim üyesine ait ders var mý?
	if(found == 0){ // ID yoksa iþlem yapýlmaz
		printf("\n (!) Bu ID'ye sahip bir öðretim üyesi bulunmamaktadýr.\n");
	}else if(found == 1 && control == 1){
		printf("\n (!) Bu öðretim üyesine ait ders bulunmaktadýr.");
		printf("\n (!) Bir öðretim üyesini silmek için öðretim üyesinin");
		printf("\n     verdiði herhangi bir ders bulunmamalýdýr.\n");
	}else if(found == 1 && control == 0){ // sorun yoksa iþlem yapýlýr
		fp1 = fopen("TEACHERS.txt", "r");
		fp2 = fopen("NEW_TEACHERS.txt", "w"); // güncel hal
		while(!feof(fp1)){
			fscanf(fp1, "\n%[^;]s", newTeacher->id);
			fscanf(fp1, ";%[^;]s", newTeacher->title);
			fscanf(fp1, ";%[^;]s", newTeacher->name);
			fscanf(fp1, ";%[^\n]s", newTeacher->surname);
			if(!(strcmp(newTeacher->id, id) == 0)){ // deðiþtirilecek ID için yeni deðerler alýnýr
				fprintf(fp2,"\n%s;%s;%s;%s", newTeacher->id, newTeacher->title,
				newTeacher->name, newTeacher->surname);
			}
		}
		fclose(fp1);
		fclose(fp2);
		remove("TEACHERS.txt"); // eski dosya silinir
		rename("NEW_TEACHERS.txt", "TEACHERS.txt"); // yeni dosya yeniden adlandýrýlýr
		printf("\n (!) Öðretim üyesi silme iþlemi tamamlandý.\n");
	}
	free(id);
	free(newTeacher);
}

// KOZMETÝK MENÜLER
void mainSignIn(){ //ana giriþ ekraný
	printf(" ________________________\n");
	printf(" |                      |\n");
	printf(" |  DERS KAYIT SÝSTEMÝ  |\n");
	printf(" |______________________|\n");
}
void mainMenu(){ // ana menü
	printf("\n- 1: Öðrenci Giriþi");
	printf("\n- 2: Öðretim Üyesi Giriþi");
	printf("\n- 3: Yönetici Giriþi\n");
	printf("\n- 0: Çýkýþ Yap\n");
}
void studentSignIn(){ // öðrenci giriþ ekraný
	printf(" ____________________\n");
	printf(" |                  |\n");
	printf(" |  Öðrenci Giriþi  |\n");
	printf(" |__________________|\n");
}
void studentMenu(){ // öðrenci menüsü
	printf("\n- 1: Ders Ekle");
	printf("\n- 2: Ders Býrak");
	printf("\n- 3: Alýnan Dersler");
	printf("\n- 4: Öðretim Üyesi Ara\n");
	printf("\n- 9: Geri");
	printf("\n- 0: Çýkýþ Yap\n");
}
void teacherSignIn(){ // öðretim üyesi giriþ ekraný
	printf(" __________________________\n");
	printf(" |                        |\n");
	printf(" |  Öðretim Üyesi Giriþi  |\n");
	printf(" |________________________|\n");
}
void teacherMenu(){ // öðretim üyesi menüsü
	printf("\n- 1: Ders Oluþtur");
	printf("\n- 2: Ders Güncelle");
	printf("\n- 3: Ders Sil\n");
	printf("\n- 4: Verilen Dersler");
	printf("\n- 5: Ders Sýnýf Listesi Öðren");
	printf("\n- 6: Yoklama Listesi Oluþtur\n");
	printf("\n- 9: Geri");
	printf("\n- 0: Çýkýþ Yap\n");
}
void adminSignIn(){ // yönetici giriþ ekraný
	printf(" _____________________\n");
	printf(" |                   |\n");
	printf(" |  Yönetici Giriþi  |\n");
	printf(" |___________________|\n");
}
void adminMenu(){ // yönetici menüsü
	printf("\n- 1: Öðrenci Ekle");
	printf("\n- 2: Öðrenci Güncelle");
	printf("\n- 3: Öðrenci Sil\n");
	printf("\n- 4: Öðretim Üyesi Ekle");
	printf("\n- 5: Öðretim Üyesi Güncelle");
	printf("\n- 6: Öðretim Üyesi Sil\n");
	printf("\n- 9: Geri");
	printf("\n- 0: Çýkýþ Yap\n");
}
int doneMenu(){ // iþlem bittikten sonra çýkan menü
	// return 0 --> çýkýþ yap
	// return 1 --> geri git
	int cmd;
	printf("\n- 9: Geri");
	printf("\n- 0: Çýkýþ Yap\n");
	cmd = getCmd(4);
	if(cmd == 0){
		return 0;
	}else if(cmd == 9){
		return 1;
	}
}
