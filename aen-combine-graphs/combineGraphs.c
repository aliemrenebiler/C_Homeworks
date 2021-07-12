/*
Ali Emre NEB�LER
19011070
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct node{
	char queryName[SIZE]; // sorgu ismi
	int queryNumber; // sorgu say�s�
	struct node* next; // s�radaki d���m
}NODE;

typedef struct graph{
	int nodeNumber; // d���m say�s�
	int nodeBonds[SIZE][SIZE]; // ba� ili�kisi
	struct node* head; // ba�lang�� d���m�
}GRAPH;

// ��lem Fonksiyonlar�
void merge_graphs(GRAPH*, GRAPH*, GRAPH*);
void list_neighbours(char[SIZE], GRAPH*);
void search_query(char[SIZE], GRAPH*);

// Deneme Fonksiyonlar�
void print_list(GRAPH*);
void print_graph(GRAPH*);

// Yard�mc� Fonksiyonlar
int find_bond(char[SIZE], char[SIZE], GRAPH*);
void set_nodes(GRAPH*);
void set_bonds(GRAPH*);
GRAPH *create_graph();
NODE *create_node();

int main(){
	int i, cmd, goOn = 1, merged = 0;
	char query[SIZE];
	GRAPH *graph1 = create_graph();
	GRAPH *graph2 = create_graph();
	GRAPH *newGraph = create_graph();
	NODE *newNode = create_node();
	
	printf("\n - ARAMA GRAFLARI -");
	printf("\n _________________________\n");
	// 1. graf de�erlerini al
	printf("\n --- 1. Arama Grafi ---\n");
	printf("\n --> Sorgulanan Ifade Sayisi: ");
	scanf("%d", &graph1->nodeNumber);
	set_nodes(graph1);
	set_bonds(graph1);
	printf(" _________________________\n");
	// 2. graf de�erlerini al
	printf("\n --- 2. Arama Grafi ---\n");
	printf("\n --> Sorgulanan Ifade Sayisi: ");
	scanf("%d", &graph2->nodeNumber);
	set_nodes(graph2);
	set_bonds(graph2);
	printf(" _________________________\n");
	// birle�tirme ya da sorgulama i�in se�im yap
	while(goOn){
		printf("\n --- Islem Secenekleri ---\n");
		printf("\n >>> 1 >>> Sorgulama Yap");
		printf("\n >>> 2 >>> Aramalari Birlestir");
		printf("\n >>> 0 >>> Cikis Yap\n");
		printf("\n --> ");
		scanf("%d", &cmd);
		if(cmd == 1){
			printf(" _________________________\n");
			printf("\n --- Sorgulama Islemi\n");
			// graflar birle�tirilmemi�se birle�tir
			if(!merged){
				merge_graphs(graph1, graph2, newGraph);
				printf("\n (!) Sorgular otomatik olarak birlestirildi.\n");
			}
			// sorgulamay� ara
			printf("\n --> Sorgu Kelimesi: ");
			scanf(" %s", query);
			search_query(query, newGraph);
			printf(" _________________________\n");
		}else if(cmd == 2){
			printf(" _________________________\n");
			printf("\n --- Birlestirme Islemi\n");
			// graflar� birle�tir
			merge_graphs(graph1, graph2, newGraph);
			merged = 1;
			printf("\n (!) Birlestirme islemi tamamlandi.\n");
			newNode = newGraph->head;
			// her d���m�n kom�ular�n� listele
			for(i=0 ; i<(newGraph->nodeNumber) ; i++){
				list_neighbours(newNode->queryName, newGraph);
				newNode = newNode->next;
			}
			printf(" _________________________\n");
		}else if(cmd == 0){
			// ��k�� yap
			printf("\n (!) Cikis yapildi.");
			goOn = 0;
		}else{
			// yanl�� komut girildi�inde uyar� ver ve ba�a d�n
			printf("\n (!) Yanlis komut!");
		}
	}
	return 0;
}

// ��lem Fonksiyonlar�
void merge_graphs(GRAPH *g1, GRAPH *g2, GRAPH *new_g){
	int i, j;
	int found, found2;
	char name1[SIZE], name2[SIZE];
	
	// Gerekli nodlar� yarat.
	NODE *tmp = create_node();
	NODE *tmp2 = create_node();
	NODE *tmp3 = create_node();
	
	// (1) �lk graf�n ba�lang�� de�erini yeni grafa aktar.
	new_g->head = g1->head;
	new_g->nodeNumber = g1->nodeNumber;
	
	// (2) �kinci graf�n farkl� olan d���mlerini listeye ekle.
	tmp3 = new_g->head;
	// yeni graf�n son d���m�n� bul
	while(tmp3->next != NULL){
		tmp3 = tmp3->next;
	}
	// d���m� yeni grafta ara
	tmp2 = g2->head;
	for(i=0 ; i<(g2->nodeNumber) ; i++){
		found = 0;
		tmp = new_g->head;
		while((!found) && tmp != NULL){
			if(strcmp(tmp->queryName, tmp2->queryName) == 0){
				found = 1;
			}else{
				tmp = tmp->next;
			}
		}
		// bulunmad�ysa yeni d���m olarak en sona ekle
		// d���m say�s�n� artt�r
		if(!found){
			tmp3->next = create_node();
			strcpy(tmp3->next->queryName, tmp2->queryName);
			tmp3->next->queryNumber = tmp2->queryNumber;
			tmp3 = tmp3->next;
			tmp3->next = NULL;
			new_g->nodeNumber++;
		}
		tmp2 = tmp2->next;
	}
	
	// (3) Yeni graf ba�lant� de�erlerini s�f�rla.
	for(i=0 ; i<(new_g->nodeNumber) ; i++){
		for(j=0 ; j<(new_g->nodeNumber) ; j++){
			new_g->nodeBonds[i][j] = 0;
		}
	}
	
	// (4) T�m d���mlerin de�erlerini g�ncelle.
	tmp = new_g->head;
	tmp2 = new_g->head;
	for(i=0 ; i<(new_g->nodeNumber) ; i++){
		// Her seferinde sat�rda ba�layaca��m nokta de�i�iyor.
		// Bu sebeple tmp3 de�i�keni tutuyorum.
		tmp2 = tmp->next;
		for(j=i+1 ; j<(new_g->nodeNumber) ; j++){
			// di�er iki listeden herhangi birinde ba� varsa ba� kur
			found = find_bond(tmp->queryName, tmp2->queryName, g1);
			found2 = find_bond(tmp->queryName, tmp2->queryName, g2);
			if(found || found2){
				new_g->nodeBonds[i][j] = 1;
				new_g->nodeBonds[j][i] = 1;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
void list_neighbours(char name[SIZE], GRAPH *newGraph){
	int i = 0, j = 0, k, found = 0;
	NODE *newNode = create_node();
	NODE *tmp = create_node();
	// isim var m� kontrol et
	newNode = newGraph->head;
	while((!found) && j<(newGraph->nodeNumber)){
		// isim varsa bulundu i�aretle
		if(strcmp(name, newNode->queryName) == 0){
			found = 1;
		}
		// yoksa i de�erini 1 artt�r ve s�radaki d���me ge�
		if(!found){
			i++;
			newNode = newNode->next;
		}
		j++;
		// (i de�i�keni, aranan ismin listedeki konumu)
	}
	// varsa ba�l� olanlar� yazd�r
	printf("\n --- Sorgu: '%s'", name);
	printf("\n --- Ilgili Sorgular:");
	if(found){
		printf("\n >>>");
		for(j=0 ; j<(newGraph->nodeNumber) ; j++){
			// listedeki her sorgunun, aranan sorguyla ba��n� kontrol et
			// ba� de�eri varsa (de�er 1 ise) yazd�r
			if(newGraph->nodeBonds[i][j]){
				tmp = newGraph->head;
				// ba�l� olan sorguyu bul
				for(k=0 ; k<j ; k++){
					tmp = tmp->next;
				}
				// yazd�r
				printf(" %s -", tmp->queryName);
			}
		}
		printf("\n");
	}else{
		// sorgu yoksa uyar� ver ve i�lem yapma
		printf("\n (!) Sorgulama yok.\n");
	}
}
void search_query(char query[SIZE], GRAPH *newGraph){
	int i, j = 0, k, found = 0;
	NODE *newNode = create_node();
	NODE *tmp = create_node();
	NODE *mostSearched[3];
	for(i=0 ; i<3 ; i++){
		mostSearched[i] = create_node();
		strcpy(mostSearched[i]->queryName, " ");
		mostSearched[i]->queryNumber = 0;
		mostSearched[i]->next = NULL;
	}
	// sorgu var m� kontrol et
	i = 0;
	newNode = newGraph->head;
	while((!found) && j<(newGraph->nodeNumber)){
		// sorgu varsa bulundu i�aretle ve sorgu say�s�n� 1 artt�r
		if(strcmp(query, newNode->queryName) == 0){
			found = 1;
			newNode->queryNumber++;
		}
		// yoksa i de�erini 1 artt�r ve s�radaki d���me ge�
		if(!found){
			i++;
			newNode = newNode->next;
		}
		j++;
		// (i de�i�keni, aranan sorgunun listedeki konumu)
	}
	// varsa ba�l� olanlar� yazd�r
	if(found){
		printf("\n --- Sorgu Sayisi = %d\n", newNode->queryNumber);
		printf("\n (!) En Cok Aranan Ilgili Ilk 3 Sorgu:");
		for(j=0 ; j<(newGraph->nodeNumber) ; j++){
			// listedeki her sorgunun, aranan sorguyla ba��n� kontrol et
			// ba� de�eri varsa (de�er 1 ise) sorgu say�s�n� kontrol et
			if(newGraph->nodeBonds[i][j]){
				tmp = newGraph->head;
				// ba�l� olan sorguyu bul
				for(k=0 ; k<j ; k++){
					tmp = tmp->next;
				}
				// sorgu say�s�n� kontrol et ////////////////
				if((mostSearched[0]->queryNumber) <= (tmp->queryNumber)){
					strcpy(mostSearched[2]->queryName, mostSearched[1]->queryName);
					mostSearched[2]->queryNumber = mostSearched[1]->queryNumber;
					
					strcpy(mostSearched[1]->queryName, mostSearched[0]->queryName);
					mostSearched[1]->queryNumber = mostSearched[0]->queryNumber;
					
					strcpy(mostSearched[0]->queryName, tmp->queryName);
					mostSearched[0]->queryNumber = tmp->queryNumber;
				}else if((mostSearched[1]->queryNumber) <= (tmp->queryNumber)){
					strcpy(mostSearched[2]->queryName, mostSearched[1]->queryName);
					mostSearched[2]->queryNumber = mostSearched[1]->queryNumber;
					
					strcpy(mostSearched[1]->queryName, tmp->queryName);
					mostSearched[1]->queryNumber = tmp->queryNumber;
				}else if((mostSearched[2]->queryNumber) <= (tmp->queryNumber)){
					strcpy(mostSearched[2]->queryName, tmp->queryName);
					mostSearched[2]->queryNumber = tmp->queryNumber;
				}
			}
		}
		for(j=0 ; j<3 ; j++){
			printf("\n >>> %d - '%s' - Sorgu Sayisi: %d", j, mostSearched[j]->queryName, mostSearched[j]->queryNumber);
		}
		printf("\n");
	}else{
		// sorgu yoksa uyar� ver ve i�lem yapma
		printf("\n (!) Boyle bir sorgu bulunmamaktadir.\n");
	}
}

// Deneme Fonksiyonlar�
void print_graph(GRAPH *newGraph){
	int i, j;
	int limit = newGraph->nodeNumber;
	printf("\n");
	for(i=0 ; i<limit ; i++){
		printf("\n");
		for(j=0 ; j<limit ; j++){
			printf("\t%d", newGraph->nodeBonds[i][j]);
		}
	}
	printf("\n");
}
void print_list(GRAPH *graph){
	NODE *tmp = graph->head;
	printf("\n\n");
	while(tmp != NULL){
		printf("\t%s", tmp->queryName);
		tmp = tmp->next;
	}
	printf("\n");
}

// Yard�mc� Fonksiyonlar
int find_bond(char name1[SIZE], char name2[SIZE], GRAPH *newGraph){
	int i = 0, j = 0, k = 0;
	int found1 = 0, found2 = 0;
	NODE *newNode = create_node();
	// isimler var m� kontrol et
	newNode = newGraph->head;
	while(((!found1) || (!found2)) && k<(newGraph->nodeNumber)){
		// ilk isim var m�?
		if(strcmp(name1, newNode->queryName) == 0){
			found1 = 1;
		}
		// ikinci isim var m�?
		if(strcmp(name2, newNode->queryName) == 0){
			found2 = 1;
		}
		// bulunmad�ysa de�erlerini artt�rmaya devam et
		if(!found1){
			i++;
		}
		if(!found2){
			j++;
		}
		k++;
		newNode = newNode->next;
	}
	// ikisi de bulunduysa ba� durumlar�n� d�nd�r
	// herhangi biri yoksa ba� olmad��� i�in 0 d�nd�r
	if(found1 && found2){
		return newGraph->nodeBonds[i][j];
	}else{
		return 0;
	}
}
void set_nodes(GRAPH *newGraph){
	int i;
	NODE *tmp = create_node();
	NODE *tmp2;
	printf("\n --- Sorgular:");
	// ilk d���m� olu�tur
	newGraph->head = create_node();
	printf("\n --> 1 Nolu Sorgu: ");
	scanf(" %[^\n]s", newGraph->head->queryName);
	newGraph->head->queryNumber = 0;
	newGraph->head->next = NULL;
	// sonraki d���mleri olu�tur
	tmp = newGraph->head;
	for(i=1 ; i<(newGraph->nodeNumber) ; i++){
		tmp2 = create_node();
		printf(" --> %d Nolu Sorgu: ", i+1);
		scanf(" %[^\n]s", tmp2->queryName);
		tmp2->queryNumber = 0;
		tmp2->next = NULL;
		// sonraki d���me ge�
		tmp->next = tmp2;
		tmp = tmp2;
	}
}
void set_bonds(GRAPH *newGraph){
	int i, j;
	// t�m tabloyu s�f�rla
	for(i=0 ; i<(newGraph->nodeNumber) ; i++){
		for(j=0 ; j<(newGraph->nodeNumber) ; j++){
			newGraph->nodeBonds[i][j] = 0;
		}
	}
	// e�er d���m say�s� 1'den b�y�kse ba� sor
	if((newGraph->nodeNumber)>1){
		printf("\n --- Baglar:");
		printf("\n (!) Bagli olan sorgular icin 1,");
		printf("\n     bagli olmayan sorgular icin 0 giriniz.\n\n");
		// tablonun sa� �st ��genine ba� de�erlerini al
		for(i=0 ; i<(newGraph->nodeNumber) ; i++){
			for(j=i+1 ; j<(newGraph->nodeNumber) ; j++){
				printf(" ---> %d - %d Nolu Sorgularin Bagi = ", i+1, j+1);
				scanf("%d", &newGraph->nodeBonds[i][j]);
				// tabloyu simetrik yap
				newGraph->nodeBonds[j][i] = newGraph->nodeBonds[i][j];
			}
		}
	}
}
GRAPH *create_graph(){
	return (GRAPH*)malloc(sizeof(GRAPH));
}
NODE *create_node(){
	return (NODE*)malloc(sizeof(NODE));
}
