#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#define MAX 15
struct contact{
  char numara[MAX];
  char isimSoyisim[MAX];
  //long long numara[];
  struct contact* sonraki;
};
typedef struct contact contact;

void ekle();
void sil();
void ara();
void guncelle();
void liste();
contact *ilk = NULL;
void menu();
void basla();
void yenieklenen();
void numaraIleArastir();
FILE *dosya;


int main(){
  system("color 5f");
  basla();
return 0;
}

void menu(){
       system("cls");
 // printf("+++++++++++++++++++Phone Book+++++++++++++++++++++++++\n     1.Kisi ekle.\n     2.Kisi sil.\n     3.Kisi ara.\n     4.Guncelle.\n     5.Kisileri listele.\n     6.Yeni Eklenen\n     7.Cik\n ");
  printf("\n\t\t\t\t MENU\n\t\t\t\t___\n\n");
	printf("\t\t\t ----------------------- \n");
	printf("\t\t\t| 1. Add a contact          |\n");
	printf("\t\t\t| 2. Delete a contact            |\n");
	printf("\t\t\t| 3. Search             |\n");
	printf("\t\t\t| 4. Update a contact        |\n");
	printf("\t\t\t| 5. View Phone Book    |\n");
	printf("\t\t\t| 6. The last added contact         |\n");
	printf("\t\t\t| 7. Exit                 |\n");
	printf("\t\t\t| 8. Search by number      |\n");
	printf("\t\t\t -----------------------   \n");
  printf("Choose an operation please\n");
  switch(getch())
  {
    case '1':
        ekle();
        break;
    case '2':
        sil();
        break;
    case '3':
        ara();
        break;
    case '4':
        guncelle();
        break;
    case '5':
        liste();
        break;
    case '6':
        yenieklenen();
        break;
    case '8':
    	numaraIleArastir();
    	break;
    case '7':
        remove("dosya.txt");
        exit(0);
        break;
    default: system("cls");
                printf("\nEnter just the numbers between 1 and 6");
                printf("\nPress a key");
                getch();
menu();
}
}

void basla()
{
    menu();
}

void ekle(){
  system("cls");
  contact* yeni = (contact*)malloc(sizeof(contact));
  //char yeniisim[MAX];
  //long long yeninumara;
  printf("Enter name and surname \n");
  gets(yeni->isimSoyisim);// new line a kadar okur
  printf("Enter a number \n");
  gets(yeni->numara);
  //scanf("%lld", &yeninumara);
  //yeni->numara = yeninumara;
  if(ilk== NULL){
    ilk = yeni;
  }
    else{
    if(ilk->isimSoyisim[0]>yeni->isimSoyisim[0]){
      yeni->sonraki = ilk;
      ilk = yeni;
    }
    else{
    contact* temp = ilk;
    while(temp->sonraki!= NULL && temp->sonraki->isimSoyisim[0]<yeni->isimSoyisim[0]){ //alfabe sıralama göre
      temp = temp-> sonraki;
    }
    yeni->sonraki = temp->sonraki;
    temp->sonraki = yeni;
    getch();

  }


}
dosya = fopen("dosya.txt", "w");
fprintf(dosya, "%s %s", yeni->isimSoyisim, yeni->numara);
fclose(dosya);

system("cls");
menu();
}


void liste(){
    contact *temp = ilk;
    if(ilk==NULL){
      printf("The list is empty\n");
    }
    while(temp!=NULL){
      printf("name: %s  number: %s\n", temp->isimSoyisim, temp->numara);
      temp = temp->sonraki;

    }
    getch();
    system("cls");
  menu();
}



void sil() {
  contact *temp = ilk;
  contact *onceki = NULL;
  char silinecek[MAX];
  if(ilk == NULL){
    printf("The list is empty\n");
    getch();
    basla();
  }
  printf("Enter the name and surname \n");
  gets(silinecek);
    while (temp && strcmp(temp->isimSoyisim ,silinecek)!=0) {
        onceki = temp;
        temp = temp->sonraki;
    }

    if (temp == NULL) {
        printf("The name you entered is not in the list\n");
    } else if (onceki == NULL) {
        ilk = ilk->sonraki;
    } else {

        onceki->sonraki = temp->sonraki;
    }

    free(temp);
    getch();
    system("cls");
 menu();
}

void ara(){
  char aranan[MAX];
  contact *temp = ilk;
  if(ilk == NULL){
    printf("The list is empty\n");
    getch();
    basla();
  }
  printf("Enter the name \n");
  gets(aranan);
    while(temp!=NULL){
    if(strcmp(temp->isimSoyisim, aranan) == 0){
      printf("name and surname: %s: number: %s", temp->isimSoyisim, temp->numara);
      getch();
      basla();

    }
    temp = temp->sonraki;

  }
  printf("The contact %s you are looking for is not in the list \n", aranan);
  getch();
  system("cls");
menu();
}

void guncelle(){
  char guncelleyecekisim[MAX];
  //long long yeninumara;
  if(ilk == NULL){
    printf("The list is empty\n");
    getch();
    basla();
  }
  printf("Enter a name \n");
  gets(guncelleyecekisim);
  contact *temp = ilk;
  while(temp!=NULL){
    if(strcmp(temp->isimSoyisim, guncelleyecekisim) == 0){
      printf("name and surname: %s: number: %s\n", temp->isimSoyisim, temp->numara);
      printf("Enter the new name: \n");
      gets(temp->isimSoyisim);
      printf("Enter the new number: \n");
      gets(temp->numara);
      goto satir;
    }
    temp = temp->sonraki;
  }
  printf("The name you entered is not in the list\n");
  satir:
  getch();
  system("cls");
menu();

}

void yenieklenen(){
  char str[MAX];
  if((dosya = fopen("dosya.txt", "r")) == NULL){
    printf("You did not add any contact recently\n");
    getch();
    basla();
  }
  fscanf(dosya, "%[^\n]", str);
  printf("%s", str);
  fclose(dosya);

  getch();
  system("cls");
menu();
}

void numaraIleArastir(){
	
  char aranan[MAX];
  contact *temp = ilk;
  if(ilk == NULL){
    printf("The list is empty\n");
    getch();
    basla();
  }
  printf("Enter a number \n");
  gets(aranan);
    while(temp!=NULL){
    if(strcmp(temp->numara, aranan) == 0){
      printf("Name and surname: %s: number: %s", temp->isimSoyisim, temp->numara);
      getch();
      basla();

    }
    temp = temp->sonraki;

  }
  printf("The number %s you are looking for is not in the list\n", aranan);
  getch();
  system("cls");
menu();

}
