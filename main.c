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
    int attendency;
    int *students;
    struct lectureNode *next;
}lectureList;
int binarySearch(int a[], int item, int low, int high);

studentList* createStudent(int num, char name[20], char surname[20], int lecture, int credit);
void addStudent(studentList **studentHead);
int isValidNumber(studentList *head, int num);
void addLectureToStudent(studentList *studentHead, lectureList *lectureHead);

void addStudentToLecture(studentList **studentHead,lectureList **lecturehead, char code[20], int num, int val);
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
lectureList* initLectureList();
void deleteElement(int a[], int n, int count);

void newLecture(lectureList **lectureHead);
void closeLecture(studentList **studentHead, lectureList **lectureHead);

void deleteStudent(studentList **head, lectureList **lectureHead);
void updateRegister(char *code, int num, char *event);
void studentsOfLecture(lectureList *lectureHead);

int main() {
    int menu;
    lectureList *lectureHead = initLectureList();
    studentList *studentHead = initStudentList();
    //syncStudentsAndLectures(&lectureHead, studentHead);


    printf("\n\n\n");

    do {
        printf("Ne yapmak isteriniz --- Cikis icin -1\n");
        printf("1 - Ogrenci Eklemek\n");
        printf("2 - Ogrenci Silmek\n");
        printf("3 - Ogrenciye ders eklemek\n");
        printf("4 - Ogrenciden ders silmek\n");
        printf("5 - Ders Acmak\n");
        printf("6 - Ders Kapatmak\n");
		printf("7 - Ders katilimcilari gormek\n");
		printf("8 - Ogrenci programi gormek\n");
        scanf("%d", &menu);



        switch (menu) {
            case 1:
                addStudent(&studentHead);
                break;
            case 2:
                deleteStudent(&studentHead, &lectureHead);
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
                closeLecture(&studentHead, &lectureHead);
                break;
			case 7:
				//printingSpecific lecture
				studentsOfLecture(lectureHead);//dosyaya yazilmasi yapilacak.
				break;
			case 8:
				//printingSpecicifProgramme
				break;
          	default:

            	printf("Hatali giris yaptiniz. \n");
            	break;
        }

    }while (menu != -1);
    return 0;
}

int canRegister(studentList *studentHead, lectureList *lectureHead, int num, char code[20]) {
    int maxCredit = 30;
    int maxLecture = 5;
    int attendency;
    int idx = 0;

    while (studentHead -> num != num) { //kendi ogrencimize gelis
        studentHead = studentHead -> next;
    }
    while (strcmp(lectureHead -> code, code) != 0) { //girilen derse gelis
        lectureHead = lectureHead -> next;
    }
    attendency = lectureHead -> attendency;

    do {//derse onceden kayitli olup olmadigi kontrolu
      if (studentHead -> num == lectureHead -> students[idx++]) {
        return 1;
      }
    }while(attendency-- > 0);


    if (studentHead -> credit + lectureHead -> credit > maxCredit) {
        return 2;
    }
	if (studentHead -> lectureCount + 1 > maxLecture){
        return 3;
    }

	lectureHead -> students = (int*) realloc(lectureHead -> students, (lectureHead -> attendency + 1) * sizeof (int));
	insertionSort(lectureHead -> students, num, lectureHead -> attendency + 1);

    studentHead -> credit += lectureHead -> credit;
    studentHead -> lectureCount++;
    lectureHead -> attendency++;
    return 0;

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
    scanf(" %s", tempCode);

    while(strcmp(tempCode, "-1") != 0) {
		lectureList *tmp = lectureHead;
		while (tmp != NULL && strcmp(tmp -> code, tempCode) != 0) {
			tmp = tmp -> next;
		}
		if (tmp == NULL) {
			printf("Girdiginiz kodda bir ders tanimlamadi. \n");
		} else {
			int available = canRegister(studentHead, lectureHead, tempNum, tempCode);
			if (available == 0) {
				updateRegister(tempCode, tempNum, "kayitli");
				saveStudentList(studentHead);
				saveLectureList(lectureHead);
			}
			else if (available == 1){
				printf("Sistemde bu derse kaydiniz bulunmaktadir\n");
			}
			else if (available == 2) {
				printf("Butun kredi haklarinizi doldurmus bulunmaktasiniz. Bu derse kayit yaptiramazsiniz. \n");
			}
			else if (available == 3){
				printf("Maximum sayida ders kaydiniz bulunmaktadir. Bu derse kayit yaptiramazsiniz. \n");
			}
			printf("Eklemek istediginiz dersin kodunu giriniz. Birden cok ders eklemek icin sirayla giris yapiniz. \nCikmak icin lutfen -1 giriniz\n");
			scanf("%s", tempCode);
		}
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
void replacingCredits(studentList **studentHead, lectureList *tmp) {

	for (int i = 0; i < tmp -> attendency; i++) {
		while ((*studentHead) != NULL) {
			if (tmp -> students[i] == (*studentHead) -> num) {
				(*studentHead) -> credit -= tmp -> credit;
				((*studentHead) -> lectureCount)--;
			}

		}

	}

}
void closeLecture(studentList **studentHead, lectureList **lectureHead) {
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
	replacingCredits(studentHead, tmp);

    node = tmp -> next -> next;
    free(tmp -> next -> students);
    free(tmp -> next);
    tmp -> next = node;

    saveLectureList(*lectureHead);
	saveStudentList(*studentHead);
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

            addStudentToLecture(&studentHead, lectureHead, code, num, 0);
        }

    }

    fclose(fptr);
}
void addStudentToLecture(studentList **studentHead, lectureList **lectureHead, char code[20], int num, int val) {
    lectureList *tmp = *lectureHead;


    while (tmp != NULL && strcmp(tmp -> code, code) != 0) {
        tmp = tmp -> next;
    }





	//tmp -> students[tmp -> attendency] = num; // Öğrenci numaraları sıralı bir şekilde saklanmalı.
	tmp -> attendency++;

	if (val == 0) {
		return;
	}

	printf("Buraya neden 2 kere gledim\n");
	//insertionSort(tmp -> students, tmp2 -> num, tmp -> attendency);

	//tmp2 -> credit += tmp -> credit;

	//(tmp2 -> lectureCount)++;


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
        char *ptr;
        char delim[] = ",";
        char temp[4][70];
        int idx = 0;

        ptr = strtok(tmp, delim);

        while(ptr != NULL)
        {
            strcpy(temp[idx++], ptr);
            ptr = strtok(NULL, delim);
        }

        insertLectureByKey(&lectureHead, temp[0], temp[1],atoi(temp[2]),atoi(temp[3]));
    }

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
    tmpNode -> attendency = 0;
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

    saveStudentList(*studentHead);
}
void deleteStudentFromLectures(lectureList **lectureHead, int idx) {
		int attendency = (*lectureHead) -> attendency;
		if (idx != attendency - 1) {
			while(idx + 1 < attendency) {
				(*lectureHead) -> students[idx] = (*lectureHead) -> students[idx + 1];
				idx++;
			}
		}

	(*lectureHead) -> students = (int*) realloc((*lectureHead) -> students, ((*lectureHead) -> attendency - 1) * sizeof (int));
	(*lectureHead) -> attendency--;
}
void deleteStudent(studentList **studentHead, lectureList **lectureHead) {

    studentList *tmp = *studentHead;
	lectureList *ptr = *lectureHead;
    int tempNum;
    printf("Silmek istediginiz ogrencinin numarasini giriniz. \n");
    scanf("%d", &tempNum);

    if (!isValidNumber(*studentHead, tempNum)) {
        printf("Silmek istediginiz ogrenci kayitlarda bulunamadi. \n");
        return;
    }
    if (tmp -> num == tempNum) {
        *studentHead = (*studentHead) -> next;
        (*studentHead) -> prev = NULL;
		ptr -> students = realloc( ptr -> students, 0);
		ptr -> attendency = 0;
        free(tmp);
        return;
    }
    while (tmp -> next -> num != tempNum) {
        tmp = tmp -> next;
    }

	while (ptr != NULL) {
		int idx = 0, found = 0;
		int attendency = ptr ->  attendency;
		while (attendency > 0 && found == 0) {
			printf("idx = %d --- %d\n", idx, ptr ->students[idx]);
			if (ptr ->students[idx++] == tempNum) {
				idx--;
				printf("Found at idx = %d\n", idx);
				deleteStudentFromLectures(&ptr, idx);
				found = 1;
			}
			attendency--;
		}
		ptr = ptr -> next;
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
        *head = newNode;
        return;
    }
    if ((*head) -> num > num) {
        tmp = *head;
        *head = newNode;

        newNode -> next = tmp;
        tmp -> prev = newNode;

        return;
    }

    while (tmp -> next != NULL && tmp -> next -> num < num) {
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
	int loc, j;

    loc = binarySearch(a, n, 0, a[count - 1]);
    j = count - 2;

	printf("LOC = %d \n", loc);

    while (j >= loc)
    {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = n;
}


void studentsOfLecture(lectureList *lectureHead) {
	char code[20];
	printf("Hangi dersin ogrencisi?\n");
	scanf(" %s", code);

	while (lectureHead != NULL &&strcmp(lectureHead -> code, code) != 0)
	{
		lectureHead = lectureHead -> next;
	}
	if (lectureHead == NULL) {
		return;
	}
	printf("%s dersinin ogrenci listesi :\n", lectureHead -> name);
	for (int i = 0; i < lectureHead -> attendency; i++) {
		printf("%d\n", lectureHead -> students[i]);
	}
}