#include <stdio.h>
#include <strings.h>
#include <stdio.h>
#include <malloc.h>
typedef struct node {
    int num;
    char name[50];
    char surname[50];
    int lectureCount;
    int credit;

    struct node *next;
    struct node *prev;
}studentList;

typedef struct lectureNode {
    char code[10];
    char name[50];
    int capacity;
    int credit;
    int *students;
    struct lectureNode *next;
}lectureList;
int binarySearch(int a[], int item, int low, int high);

studentList* createStudent(int num, char name[20], char surname[20], int lecture, int credit);
void addStudent(studentList **studentHead);
int isValidNumber(studentList *head, int num);
void addLectureToStudent(studentList *studentHead, lectureList *lectureHead);

void addStudentToLecture(lectureList **lecturehead, char code[20], int num);
void insertionSort(int a[], int n, int count);
void syncStudentsAndLectures(lectureList **lectureHead, studentList *studentHead);
studentList* initStudentList();
void saveStudentList(studentList *head);
void insertStudentByKey(studentList **head, int num, char name[20], char surname[20], int lecture, int credit);
void traverseStudent(studentList *head);

lectureList* createLecture(char code[10], char name[50], int capacity, int credit);
void addFrontLecture(lectureList **head, char  code[10], char name[50], int capacity, int credit);
void insertLectureByKey(lectureList **head, char code[10], char name[50], int capacity, int credit);
void saveLectureList(lectureList *head);
void traverseLecture(lectureList *head);
int getStudentCount(lectureList *node);
lectureList* initLectureList();

void newLecture(lectureList **lectureHead);
void closeLecture(lectureList **lectureHead);

void deleteStudent(studentList **head);
void updateRegister(char *code, int num, char *event);

int main() {
    int menu;
    lectureList *lectureHead = initLectureList();
    studentList *studentHead = initStudentList();
    syncStudentsAndLectures(&lectureHead, studentHead);


    printf("\n\n\n");

    do {
        printf("Ne yapmak isteriniz --- Cikis icin -1\n");
        printf("1 - Ogrenci Eklemek\n");
        printf("2 - Ogrenci Silmek\n");
        printf("3 - Ogrenciye ders eklemek\n");
        printf("4 - Ogrenciden ders silmek\n");
        printf("5 - Ders Acmak\n");
        printf("6 - Ders Kapatmak\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                addStudent(&studentHead);
                break;
            case 2:
                deleteStudent(&studentHead);
                saveStudentList(studentHead);
                break;
            case 3:
                addLectureToStudent(studentHead, lectureHead);
                break;
            case 4:
                //deleteLectureFromStudent();
                break;
            case 5:
                newLecture(&lectureHead);
                break;
            case 6:
                closeLecture(&lectureHead);
                break;

        }

    }while (menu != -1);
    return 0;
}
int canRegister(studentList *studentHead, lectureList *lectureHead, int num, char code[20]) {
    int maxCredit = 30;
    int maxLecture = 5;
    int idx = 0;

    while (studentHead -> num != num) {
        studentHead = studentHead -> next;
    }
    while (strcmp(lectureHead -> code, code) != 0) {
        lectureHead = lectureHead -> next;
    }
    while (lectureHead -> students[idx] > 22000000) {
        if (studentHead -> num == lectureHead -> students[idx++]) {
            return 3;
        }
    }

    //KONTROLLER

    if (studentHead -> credit + lectureHead -> credit > maxCredit) {
        return 0;
    }
    else if (studentHead -> lectureCount + 1 > maxLecture){
        return 1;
    }

    studentHead -> credit += lectureHead -> credit;
    studentHead -> lectureCount++;
    return 2;

}

void addLectureToStudent(studentList *studentHead, lectureList *lectureHead){
    int tempNum;
    char tempCode[20];
    printf("Ders eklemek istediginiz ogrencinin numarasini giriniz. \n");
    scanf("%d", &tempNum);
    if (!isValidNumber(studentHead, tempNum)) {
        printf("Kayitlarda boyle bir ogrenci bulunmamakta. \n");
        return;
    }

    printf("Eklemek istediginiz dersin kodunu giriniz. Birden cok ders eklemek icin sirayla giris yapiniz. \nCikmak icin lutfen -1 giriniz\n");
    scanf("%s", tempCode);


    while(strcmp(tempCode, "-1") != 0) {
        int available = canRegister(studentHead, lectureHead, tempNum, tempCode);
        if (available == 2) {
            addStudentToLecture(&lectureHead, tempCode, tempNum);
            updateRegister(tempCode, tempNum, "kayitli");
            saveStudentList(studentHead);
        }
        else if (available == 1){
            printf("Maximum sayida ders kaydiniz bulunmaktadir. Bu derse kayit yaptiramazsiniz. \n");
        }
        else if (available == 3) {
            printf("Bu dersi zaten eklemis bulunuyorsunuz. \n");
        }
        else {
            printf("Butun kredi haklarinizi doldurmus bulunmaktasiniz. Bu derse kayit yaptiramazsiniz. \n");
        }


        printf("Eklemek istediginiz dersin kodunu giriniz. Birden cok ders eklemek icin sirayla giris yapiniz. \nCikmak icin lutfen -1 giriniz\n");
        scanf("%s", tempCode);
    }
}


void updateRegister(char code[20], int num, char *event) {
    FILE *fptr;
    char tmp[50];
    char temp[5][60];
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\kayit.txt", "r+");


    while (fgets(tmp, 50, fptr) != NULL) {
        char *ptr;
        char delim[] = ",";

        int idx = 0;
        ptr = strtok(tmp, delim);

        while(ptr != NULL)
        {
            strcpy(temp[idx++], ptr);
            ptr = strtok(NULL, delim);
        }

    }

    fprintf(fptr, "%d,%s,%d,%s,%s\n", atoi(temp[0]) + 1, code, num, "19.12.2021", event);

    fclose(fptr);
}

int existingLecture(lectureList *lectureHead, char code[20]) {
    while (lectureHead != NULL && strcmp(lectureHead -> code, code) != 0) {
        lectureHead = lectureHead -> next;
    }
    if (lectureHead == NULL) {
        return 0;
    }
    return 1;
}
void newLecture(lectureList **lectureHead) {
    int capacity, credit;
    char tempCode[20], tempName[50];
    printf("Olusturmak istediginiz dersin kodunu giriniz.\n");
    scanf("%s", tempCode);
    if (existingLecture(*lectureHead, tempCode)) {
        printf("Girdiginiz ders aktif olarak bulunmaktadir.\n");
        return;
    }
    printf("Olusturmak istediginiz dersin adini giriniz. \n");
    scanf("%s", tempName);

    printf("Olusturmak istediginiz dersin kontenjan sayisini giriniz. \n");
    scanf("%d", &capacity);

    printf("Olusturmak istediginiz dersin kredisini giriniz. \n");
    scanf("%d", &credit);

    insertLectureByKey(lectureHead, tempCode, tempName, capacity, credit);

    saveLectureList(*lectureHead);
}
void closeLecture(lectureList **lectureHead) {
    lectureList *tmp = *lectureHead;
    lectureList *node;
    char tempCode[20];
    printf("Kapatmak istediginiz dersin kodunu giriniz. \n");
    scanf("%s", tempCode);

    if (!existingLecture(*lectureHead, tempCode)) {
        printf("Kapatmak istediginiz ders aktif olarak bulunmamaktadir. \n");
        return;
    }

    while(strcmp(tmp -> next -> code, tempCode) != 0) {
        tmp = tmp -> next;
    }
    node = tmp -> next -> next;
    free(tmp -> next -> students);
    free(tmp -> next);
    tmp -> next = node;

    saveLectureList(*lectureHead);
}
void syncStudentsAndLectures(lectureList **lectureHead, studentList *studentHead) {
    FILE *fptr;
    char tmp[50];
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\kayit.txt", "r");

    while(fgets(tmp, 50, fptr) != NULL) {

        char *ptr;
        char delim[] = ",";
        char temp[5][50];
        int idx = 0;

        ptr = strtok(tmp, delim);
        while(ptr != NULL)
        {
            strcpy(temp[idx++], ptr);
            ptr = strtok(NULL, delim);
        }

        if (strcmp(temp[4], "kayitli") != 0) {
            int num = atoi(temp[2]);
            char code[50];
            strcpy(code, temp[1]);

            addStudentToLecture(lectureHead, code, num);
        }

    }

    fclose(fptr);
}
void addStudentToLecture(lectureList **lectureHead, char code[20], int num) {
    lectureList *tmp = *lectureHead;
    while (tmp != NULL && strcmp(tmp -> code, code) != 0) {
        //printf("%s - %s\n", tmp -> code, code);
        tmp = tmp -> next;
    }

    if (tmp == NULL) {
        printf("Girdiginiz kodda bir ders tanimlamadi. \n");
        return;
    }

    int count = getStudentCount(tmp);
    tmp -> students = (int*) realloc(tmp -> students, (count + 1) * sizeof (int));
    tmp -> students[count] = num; // Öğrenci numaraları sıralı bir şekilde saklanmalı.


}
int getCreditOfLecture(lectureList *head, char code[20]) {
    while (head != NULL && strcmp( head -> code, code) == 0) {
        head = head -> next;
    }
    return head -> credit;
}

int getStudentCount(lectureList *node) {
    int i = 0;
    while(node -> students[i] != 0) {
        i++;
    }
    return i;
}
lectureList* initLectureList() {
    FILE *fptr;
    char tmp[70];
    lectureList *lectureHead = NULL;

    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\inputLec.txt", "r");
    if (fptr == NULL) {
        exit(1);
    }


    while (fgets(tmp, 70, fptr) != NULL) {
        puts(tmp);
        char *ptr;
        char delim[] = ",";
        char temp[4][70];
        int idx = 0;

        ptr = strtok(tmp, delim);

        while(ptr != NULL)
        {
            //printf("Elimdeki string = %s\n" ,ptr);
            strcpy(temp[idx++], ptr);
            ptr = strtok(NULL, delim);
        }
        insertLectureByKey(&lectureHead, temp[0], temp[1],atoi(temp[2]),atoi(temp[3]));
        //printf("HEAD = %s\n", lectureHead->code);
    }
    //traverseLecture(lectureHead);
    fclose(fptr);
    saveLectureList(lectureHead);
    return lectureHead;
}
lectureList* createLecture(char code[10], char name[50], int capacity, int credit) {
    lectureList *tmpNode;

    tmpNode = (lectureList*) malloc(sizeof(lectureList));
    strcpy(tmpNode -> code, code);
    strcpy(tmpNode -> name, name);
    tmpNode -> capacity = capacity;
    tmpNode -> credit = credit;
    tmpNode -> students = (int*) calloc(1, sizeof(int));
    tmpNode -> next = NULL;

    return  tmpNode;
}
void addFrontLecture(lectureList **head, char  code[10], char name[50], int capacity, int credit) {
    lectureList *tmp;
    lectureList *newNode = createLecture(code, name, capacity, credit);

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    tmp = *head;
    *head = newNode;

    newNode -> next = tmp;
}
void insertLectureByKey(lectureList **head, char code[10], char name[50], int capacity, int credit) {
    lectureList  *tmp;
    lectureList *newNode;
    newNode = createLecture(code, name, capacity, credit);


    if (*head == NULL || strcmp((*head) -> code, code) > 0 ) {
        addFrontLecture(head, code, name, capacity, credit);
        return;
    }

    tmp = *head;
    while (tmp -> next != NULL && strcmp(tmp -> next -> code, code) < 0) {
        tmp = tmp -> next;
    }



    if (tmp -> next == NULL) {
        tmp -> next = newNode;
    }
    else {
        newNode -> next = tmp -> next;
        tmp -> next = newNode;
    }

}
void saveLectureList(lectureList *head) {
    printf("Kaydetme basladi \n");
    lectureList *tmp;
    tmp = head;
    FILE *fptr;
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\inputLec.txt", "w+");
    if (fptr == NULL) {
        exit(1);
    }


    while (tmp != NULL) {
        fprintf(fptr,  "%s,%s,%d,%d\n", tmp -> code, tmp -> name, tmp -> capacity, tmp -> credit);
        tmp = tmp -> next;
    }


    fclose(fptr);
    printf("Kaydetme bitti \n");
}
void printLecture(lectureList *n) {
    printf("%s, %s, %d, %d", n -> code, n -> name, n -> capacity, n -> credit);
}
void traverseLecture(lectureList *head) {
    lectureList *tmp = head;
    while (tmp != NULL) {
        printLecture(tmp);
        tmp = tmp->next;
        printf("\n");
    }
}



studentList* initStudentList() {
    FILE *fptr;
    char tmp[60];
    studentList *studentHead = NULL;

    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\input.txt", "r");
    if (fptr == NULL) {
        exit(1);
    }


    while (fgets(tmp, 60, fptr) != NULL) {
        char *ptr;
        char delim[] = ",";
        char temp[5][60];
        int idx = 0;

        ptr = strtok(tmp, delim);

        while(ptr != NULL)
        {
            strcpy(temp[idx++], ptr);
            ptr = strtok(NULL, delim);
        }
        insertStudentByKey(&studentHead, atoi(temp[0]), temp[1], temp[2], atoi(temp[3]), atoi(temp[4]));
    }


    fclose(fptr);
    saveStudentList(studentHead);
    return studentHead;
}
int isValidNumber(studentList *head, int num) {

    while (head != NULL && head -> num != num) {
       // printf("Karsilastirilan numaralar %d - %d", head -> num, num);
        head = head -> next;
    }
    if (head == NULL) {
        return 0;
    }
    return 1;

}
void saveStudentList(studentList *head) {
    studentList *tmp;
    tmp = head;
    FILE *fptr;
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\input.txt", "w+");
    if (fptr == NULL) {
        exit(1);
    }

  //printf("Traverse in save \n");
  //traverseStudent(head);


    while (tmp != NULL) {
        fprintf(fptr,  "%d,%s,%s,%d,%d\n", tmp -> num, tmp -> name, tmp -> surname, tmp -> lectureCount, tmp -> credit);
        tmp = tmp -> next;
    }


    fclose(fptr);
}
studentList* createStudent(int num, char name[20], char surname[20], int lecture, int credit) {
    studentList *tmpNode;
    tmpNode = (studentList *)malloc(sizeof(studentList));
    tmpNode -> num = num;
    strcpy(tmpNode -> name, name);
    strcpy(tmpNode -> surname, surname);
    tmpNode -> lectureCount = lecture;
    tmpNode -> credit = credit;
    tmpNode -> next = NULL;
    tmpNode -> prev = NULL;
    return tmpNode;
}
void addStudent(studentList **studentHead) {
    int tempNum, control;
    char tempName[50], tempSurname[50];


    printf("Lutfen ogrencinin numarasini giriniz. \n");
    scanf(" %d", &tempNum);
    control = isValidNumber(*studentHead, tempNum);

    if( control == 1) {
        printf("Ogrenci listede bulunmaktadir. \n");
        return;
    }

    printf("Lutfen ogrencinin ismini giriniz. \n");
    scanf("%s", tempName);
    printf("Lutfen ogrencinin soyismini giriniz. \n");
    scanf("%s", tempSurname);

    insertStudentByKey(studentHead, tempNum, tempName, tempSurname, 0, 0);

  printf("\n\n1taverse in addstudent\n");
  traverseStudent(*studentHead);
  //saveStudentList(*studentHead);
}
void deleteStudent(studentList **head) {
    studentList *tmp = *head;
    int tempNum;
    printf("Silmek istediginiz ogrencinin numarasini giriniz. \n");
    scanf("%d", &tempNum);

    if (!isValidNumber(*head, tempNum)) {
        printf("Silmek istediginiz ogrenci kayitlarda bulunamadi. \n");
        return;
    }
    if (tmp -> num == tempNum) {
        *head = (*head) -> next;
        (*head) -> prev = NULL;
        free(tmp);
        return;
    }
    while (tmp -> next -> num != tempNum) {
        printf("Karsilastirilanlar %d - %d\n", tmp -> num, tempNum);
        tmp = tmp -> next;
    }
    studentList  *node;
    node = tmp -> next;
    tmp -> next = node -> next;
    node -> next -> prev = tmp;
    free(node);


}
void insertStudentByKey(studentList **head, int num, char name[20], char surname[20], int lecture, int credit)
{
    studentList *tmp;
    studentList *newNode;
    newNode = createStudent(num, name, surname, lecture, credit);


    tmp = *head;
    if (*head == NULL) {
        //newNode -> next = *head;
        *head = newNode;
        return;
    }
    if ((*head) -> num > num) {
       //printf("ARADIGIM YERDEYIZ\n");
        tmp = *head;
      //printf("tmp name %s\n", tmp -> name);
        *head = newNode;

        newNode -> next = tmp;
      //printf("newNext name %s\n", newNode -> next -> name);
        tmp -> prev = newNode;
      printf("tmpPrev name %s\n\n", tmp -> prev -> name);

      //printf("%s - %s - %s", (*head) -> name, (*head) -> next -> name, (*head) -> next -> next -> name);

        //*head = newNode;
        return;
    }

    while (tmp -> next != NULL && tmp -> next -> num < num) {
        //printf("Kiyasladim %d, %d\n", tmp->num , num);
        tmp = tmp -> next;
    }
    newNode -> next = tmp -> next;
    if (tmp -> next != NULL) {
        newNode -> next -> prev = newNode;
    }
    tmp -> next = newNode;
    newNode -> prev = tmp;

}
void printStudent(studentList *n) {
    printf("%d, %s, %s ", n -> num, n -> name, n -> surname);
}
void traverseStudent(studentList *head) {
    studentList *tmp = head;
    while (tmp != NULL) {
        printStudent(tmp);
        tmp = tmp->next;
        printf("\n");
    }
}

int binarySearch(int a[], int item, int low, int high)
{
    if (high <= low)
        return (item > a[low]) ? (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item,
                            mid + 1, high);
    return binarySearch(a, item, low,
                        mid - 1);
}

void insertionSort(int a[], int n, int count)
{
    printf("1\n");
    int i, loc, j, selected;

    loc = binarySearch(a, n, 0, a[count - 1]);

    j = count - 2;

    while (j >= loc)
    {
        a[j + 1] = a[j];
        j--;
    }

    a[j + 1] = n;
    printf("2\n");
}