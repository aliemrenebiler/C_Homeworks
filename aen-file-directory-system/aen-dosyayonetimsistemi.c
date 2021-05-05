#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define display(n) printf(#n)

typedef struct node{
	char name[SIZE];
	struct node* parent;
    struct node* sibling;
    struct node* firstChild;
}NODE;

void mkdir(NODE*, char*);
NODE *chdir(NODE*, char*);
void *rmdir(NODE*, char*);
void dir(NODE*);
void count(NODE*);

// Di�er Fonksiyonlar
int searchForDir(NODE*, char*);
NODE *create_node();

int main(){
	char tmp[SIZE], *command, *name;
	int goon = 1;
	
	NODE *root = create_node();
	
	strcpy(root->name, "root");
	root->parent = NULL;
	root->firstChild = NULL;
	root->sibling = NULL;
	
	NODE *selected_dir = root;
	
	printf("\n --- OS DIRECTORY YAPISI ---\n");
	
	while(goon){
		printf("\n  Directory:  %s\n", selected_dir->name);
		printf("\n mkdir name:  Yeni directory yarat.");
		printf("\n chdir name:  Alt directory'ye gec.");
		printf("\n rmdir name:  Alt directory'yi sil.");
		printf("\n        dir:  Directory agacini yazdir.");
		printf("\n      count:  Directory agacini say.");
		printf("\n       exit:  Cikis yap.\n");
		printf("\n > ");
		scanf(" %[^\n]s", tmp);
		
    	command = strtok(tmp, " ");
		name = strtok(NULL, "\n");
		
		if(strcmp(command, "mkdir")==0){
			mkdir(selected_dir, name);
		}else if(strcmp(command, "chdir")==0){
			selected_dir = chdir(selected_dir, name);
		}else if(strcmp(command, "rmdir")==0){
			rmdir(selected_dir, name);
		}else if(strcmp(command, "dir")==0){
			dir(selected_dir);
		}else if(strcmp(command, "count")==0){
			count(selected_dir);
		}else if(strcmp(command, "exit")==0){
			goon = 0;
		}else{
			printf("\n (!) Yanlis Komut!");
			printf("\n (!) Lutfen baska bir komut deneyiniz.\n");
		}
	}
	
	return 0;
}

void mkdir(NODE *selected_dir, char *name){
	NODE *newNode = create_node();
	NODE *tmp = create_node();
	// directory zaten varsa uyar� ver ve i�lem yapma
	if(searchForDir(selected_dir, name)){
		printf("\n (!) Bu isimde bir directory bulunmaktadir.\n");
	}
	// diretory yoksa ekleme i�lemini ba�lat
	else{
		strcpy(newNode->name, name);
		newNode->firstChild = NULL;
		newNode->sibling = NULL;
		// �ocuk yoksa �ocuk olarak ekle
		if(selected_dir->firstChild == NULL){
			selected_dir->firstChild = newNode;
			newNode->parent = selected_dir;
		}
		//�ocuk varsa karde� olarak ekle
		else{
			tmp = selected_dir->firstChild;
			// karde�i olmayana kadar ilerle
			while(tmp->sibling != NULL){
				tmp = tmp->sibling;
			}
			//yeni karde� olarak ekle
			tmp->sibling = newNode;
			newNode->parent = selected_dir;
		}
		printf("\n --> Directory eklendi.\n");
	}
}

NODE *chdir(NODE *selected_dir, char *name){
	NODE *tmp = create_node();
	// �st directory'ye ��k
	if(strcmp(name, "..") == 0){
		if(selected_dir->parent == NULL){
			printf("\n (!) Ust directory yoktur.");
			printf("\n (!) Lutfen tekrar deneyiniz.\n");
			return selected_dir;
		}else{
			printf("\n --> Directory degistirildi.\n");
			return selected_dir->parent;
		}
	}
	// alt directory'ye in
	else{
		// e�er directory varsa se�me i�lemini ba�lat
		if(searchForDir(selected_dir, name)){
			tmp = selected_dir->firstChild;
			// isim e�le�meyene kadar ilerle
			while(strcmp(tmp->name, name) != 0){
				tmp = tmp->sibling;
			}
			//ilerleme i�lemi bitti�inde directory'yi de�i�tir
			printf("\n --> Directory degistirildi.\n");
			return tmp;
		}
		// diretory yoksa uyar� ver ve i�lem yapma
		else{
			printf("\n (!) Bu isimde bir directory yoktur.");
			printf("\n (!) Lutfen tekrar deneyiniz.\n");
			return selected_dir;
		}
	}
}

void *rmdir(NODE *selected_dir, char *name){
	NODE *tmp = create_node();
	NODE *preSibling = create_node();
	// e�er directory varsa devam
	if(searchForDir(selected_dir, name)){
		tmp = selected_dir->firstChild;
		// isim e�le�ene kadar ilerle
		while(strcmp(tmp->name, name) != 0){
			preSibling = tmp;
			tmp = tmp->sibling;
		}
		// �ocu�u yoksa silme i�lemini yap
		if(tmp->firstChild == NULL){
			// ilk �ocuk ise ilk �ocu�u de�i�tir
			if(tmp->parent != NULL){
				tmp->sibling->parent = tmp->parent;
				tmp->parent->firstChild = tmp->sibling;
			}
			// ilk �ocuk de�ilse yan yana olan karde�leri ba�la
			else{
				preSibling->sibling = tmp->sibling;
			}
		}
		// �ocu�u varsa uyar� ver ve i�lem yapma
		else{
			printf("\n (!) Directory'nin alt directory'si bulunmaktadir.\n");
		}
	}
	// diretory yoksa uyar� ver ve i�lem yapma
	else{
		printf("\n (!) Bu isimde bir directory yoktur.\n");
	}
}

void dir(NODE *selected_dir){
	NODE *tmp = create_node();
	if(selected_dir->firstChild != NULL){
		tmp = selected_dir->firstChild;
		printf("\n --- Alt Directory'ler ---");
		do{
			printf("\n --> %s", tmp->name);
			tmp = tmp->sibling;
		}while(tmp != NULL);
		printf("\n");
	}else{
		printf("\n (!) Herhangi bir alt directory yoktur.\n");
	}
}

void count(NODE *selected_dir){
	NODE *tmp = create_node();
	int counter = 0;
	if(selected_dir->firstChild != NULL){
		tmp = selected_dir->firstChild;
		do{
			counter++;
			tmp = tmp->sibling;
		}while(tmp != NULL);
	}
	printf("\n --> Alt Directory Sayisi: %d\n", counter);
}

// Di�er Fonksiyonlar
int searchForDir(NODE *selected_dir, char *name){
	int found = 0;
	NODE *tmp = create_node();
	tmp = selected_dir->firstChild; // directory'nin ilk �ocu�u
	// �ocuk varsa arama i�lemini ba�lat
	if(tmp != NULL){
		// karde� olmad��� ve aranan isim bulunmad��� s�rece aramaya devam et
		do{
			if(strcmp(tmp->name, name) == 0){
				found = 1;
			}
			tmp = tmp->sibling;
		}while(tmp != NULL && found == 0);
	}
	return found;
}

NODE *create_node(){
	return (NODE*)malloc(sizeof(NODE));
}

