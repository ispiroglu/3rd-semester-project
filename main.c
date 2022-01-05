#include <stdio.h>
#include <strings.h>
//#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct studentNode {
    int num;
    char name[50];
    char surname[50];
    int lectureCount;
    int credit;

    struct studentNode *next;
    struct studentNode *prev;
}student;

typedef struct lectureNode {
    char code[10];
    char name[50];
    int capacity;
    int credit;
    int attendency;
    int *students;
    struct lectureNode *next;
}lecture;

//void traverseStudent(student *head);
//void traverseLecture(lecture *head);


int binarySearch(int a[], int item, int low, int high); //

student* createStudent(int num, char name[20], char surname[20], int lecture, int credit); //
void addStudent(student **studentHead); //
student *isValidNumber(student *head, int num);  //
void addLectureToStudent(student *studentHead, lecture *lectureHead);

void insertionSort(int a[], int n, int count); //
void syncStudentsAndLectures(lecture *lectureHead, student *studentHead); //
student* initStudentList(); //
void saveStudentList(student *head); //
void insertStudentByKey(student **head, int num, char name[20], char surname[20], int lecture, int credit); //
//void traverseStudent(student *head); //

lecture* createLecture(char code[10], char name[50], int capacity, int credit); //
void addFrontLecture(lecture **head, char  code[10], char name[50], int capacity, int credit); //
void insertLectureByKey(lecture **head, char code[10], char name[50], int capacity, int credit); //
void saveLectureList(lecture *head); //
//void traverseLecture(lecture *head); //
lecture* initLectureList(); //


void newLecture(lecture **lectureHead); //
void closeLecture(student *studentHead, lecture **lectureHead); //

void deleteStudent(student **head, lecture **lectureHead); //
void updateRegister(char *code, int num, char *time, char *event); //
void studentsOfLecture(student *studentHead, lecture *lectureHead); //
void deleteLectureFromStudent(lecture *lectureHead, student *studentHead); //
void deleteStudentFromLectures(lecture *lectureHead, int idx); //
void scheduleOfStudent(lecture *lectureHead, student *studentHead); //

int main() {
    int menu;

	setlocale(LC_ALL, "Turkish");
    lecture *lectureHead = initLectureList();
	//traverseLecture(lectureHead);

    student *studentHead = initStudentList();
	//traverseStudent(studentHead);
    syncStudentsAndLectures(lectureHead, studentHead);




    do {
		printf("\n\n\n");
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
			case -1:
				return 0;
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
                deleteLectureFromStudent(lectureHead, studentHead);
                break;
            case 5:
                newLecture(&lectureHead);
                break;
            case 6:
                closeLecture(studentHead, &lectureHead);
                break;
			case 7:
				//printingSpecific lecture
				studentsOfLecture(studentHead, lectureHead);//dosyaya yazilmasi yapilacak.
				break;
			case 8:
				//printingSpecicifProgramme
				scheduleOfStudent(lectureHead, studentHead);
				break;
          	default:

            	printf("Hatali giris yaptiniz. Menuye tekrar yonlendiriliyorsunuz \n\n");
            	break;
        }

    }while (menu != -1);
    return 0;
}
void updateLecture(student *studentNode, lecture *lectureNode) {
	lectureNode -> students = (int*)realloc(lectureNode -> students, (lectureNode -> attendency + 1) * sizeof (int));
	insertionSort(lectureNode -> students, studentNode -> num, lectureNode -> attendency + 1);
	lectureNode -> attendency++;
}
void updateStudent(student *studentNode, lecture *lectureNode) {
	studentNode -> credit += lectureNode -> credit;
	studentNode -> lectureCount++;
}

void updateNodes(student *studentNode, lecture *lectureNode) {
	updateLecture(studentNode, lectureNode);
	updateStudent(studentNode, lectureNode);
}/*
lecture* getToLectureNode(lecture *lectureHead, char *code) {
	while (lectureHead != NULL && strcmp(lectureHead -> code, code) != 0) {
		lectureHead = lectureHead -> next;
	}

	return lectureHead;
}
student* getToStudentNode(student *studentHead, int num) {
	while (studentHead != NULL && studentHead -> num != num) {
		studentHead = studentHead -> next;
	}

	return studentHead;
}

int	 getStudentNum() {
	int num;
	printf("Ogrencinin numarasini giriniz. \n");
	scanf(" %d", &num);
	return num;
}
int getLectureCapacity() {
	int num;
	printf("Dersin kapasitesini giriniz. \n");
	scanf(" %d", &num);
	return num;
}
int getLectureCredit() {
	int num;
	printf("Dersin kredisini giriniz. \n");
	scanf(" %d", &num);
	return num;
}
char* getStudentName() {
	char *name;
	printf("Ogrencinin adini giriniz. \n");
	scanf(" %s", &name);
	return name;
}
char* getStudentSurname() {
	char *name;
	printf("Ogrencinin soyadini giriniz. \n");
	scanf(" %s", &name);
	return name;
}
char* getLectureCode() {
	char *code;
	printf("Dersin kodunu giriniz. \n");
	scanf(" %s", &code);
	return code;
}
char* getLectureName() {
	char *code;
	printf("Dersin adini giriniz. \n");
	scanf(" %s", &code);
	return code;
}
*/
int canRegister(student *studentNode, lecture *lectureNode) {

	int idx = 0, maxLecture = 10, maxCredit = 30;
	int attendency = lectureNode -> attendency;
	do {//derse onceden kayitli olup olmadigi kontrolu, binary search ile yapılabilir.
		if (studentNode -> num == lectureNode -> students[idx++]) {
			return 1;
		}
	}while(attendency-- > 0);

	if (studentNode -> credit + lectureNode -> credit > maxCredit) {
		return 2;
	}
	if (studentNode -> lectureCount + 1 > maxLecture){
		return 3;
	}
	return 0;
}/*
int isValidLecture(lecture *lectureHead, char *code) {
	while (lectureHead != NULL && strcmp(lectureHead -> code, code) != 0) {
		lectureHead = lectureHead -> next;
	}
	if (lectureHead == NULL) {
		return 0;
	}
	return 1;
}*/
lecture* existingLecture(lecture *lectureHead, char code[20]) {
	while (lectureHead != NULL && strcmp(lectureHead -> code, code) != 0) {
		lectureHead = lectureHead -> next;
	}
	return lectureHead;
}


void addLectureToStudent(student *studentHead, lecture *lectureHead){
	int tempNum;
    char tempCode[20];
    printf("Ders eklemek istediginiz ogrencinin numarasini giriniz. \n");
    scanf("%d", &tempNum);
	student *studentNode = isValidNumber(studentHead, tempNum);
    if (studentNode == NULL) {
        printf("Kayitlarda boyle bir ogrenci bulunmamakta. \n");
        return;
    }

    printf("Eklemek istediginiz dersin kodunu giriniz. Birden cok ders eklemek icin sirayla giris yapiniz. \n");
	printf("Ekleme isleminiz bittikten sonra -1'e basarak cikis yapabilirsiniz. \n");
    scanf(" %s", tempCode);

	char date[20];
	printf("Lutfen islemin yapildigi tarihi giriniz. \n");
	scanf(" %s", date);

    while(strcmp(tempCode, "-1") != 0) {
		lecture *lectureNode = existingLecture(lectureHead, tempCode);
		if (lectureNode == NULL) {
			printf("Sistemde boyle bir ders kaydi bulunmamaktadir. Ana menuye yonlendiriliyorsunuz.\n");
		} else {
			int available = canRegister(studentNode, lectureNode);
			if (available == 0) {
				updateNodes(studentNode, lectureNode);
				updateRegister(tempCode, tempNum, date, "kayitli");
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
			printf("Eklemek istediginiz dersin kodunu giriniz. Birden cok ders eklemek icin sirayla giris yapiniz.\n");
			scanf("%s", tempCode);
		}
    }
}
void updateRegister(char code[20], int num, char *date , char *event) {

    FILE *fptr, *tempFile;
    char tmp[255];
    char temp[5][60];
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\kayit.txt", "r");
	tempFile = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\tempKayit.txt", "w");

	int change = 0;
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

		if (atoi(temp[2]) == num) {
			if (strcmp(temp[1], code) == 0) {
				fprintf(tempFile, "%d,%s,%d,%s,%s\n", atoi(temp[0]), code, num, date, event);
				change = 1;
			}
			else {
				fprintf(tempFile, "%d,%s,%d,%s,%s", atoi(temp[0]), temp[1], atoi(temp[2]), temp[3], temp[4]);
			}
		}
		else {
			fprintf(tempFile, "%d,%s,%d,%s,%s", atoi(temp[0]), temp[1], atoi(temp[2]), temp[3], temp[4]);
		}
    }
	if (change == 0 ){
		fprintf(tempFile, "%d,%s,%d,%s,%s\n", atoi(temp[0]) + 1, code, num, date, event);
	}
	fclose(fptr);
	fclose(tempFile);
	remove("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\kayit.txt");
	rename("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\tempKayit.txt", "D:\\Workspaces\\C Workspace\\YapisalDonemProje\\kayit.txt");
}

void newLecture(lecture **lectureHead) {
    int capacity, credit;
    char tempCode[20], tempName[50];
    printf("Olusturmak istediginiz dersin kodunu giriniz.\n");
    scanf("%s", tempCode);
    if (existingLecture(*lectureHead, tempCode)) {
        printf("Girdiginiz ders kayitlarda bulunmaktadir.\n");
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
void replacingCredits(student *studentHead, lecture *tmp) {
	for (int i = 0; i < tmp -> attendency; i++) {
		while (studentHead != NULL) {
			if (tmp -> students[i] == studentHead -> num) {
				studentHead -> credit -= tmp -> credit;
				(studentHead -> lectureCount)--;
			}
			studentHead = studentHead -> next;
		}
	}
}
void closeLecture(student *studentHead, lecture **lectureHead) {

    lecture *tmp;
    lecture *node;
    char tempCode[20];
    printf("Kapatmak istediginiz dersin kodunu giriniz. \n");
    scanf("%s", tempCode);


	tmp = existingLecture(*lectureHead, tempCode);
    if (tmp == NULL) {
        printf("Kapatmak istediginiz ders aktif olarak bulunmamaktadir. \n");
        return;
    }

	char date[20];
	printf("Lutfen islemin yapildigi tarihi giriniz. \n");
	scanf(" %s", date);

	tmp = *lectureHead;
	if (strcmp(tmp -> code, tempCode) == 0) {
		*lectureHead = tmp -> next;
	} else {
		while(strcmp(tmp -> next -> code, tempCode) != 0) {
			tmp = tmp -> next;
		}
		node = tmp -> next;
		tmp -> next = tmp -> next -> next;

		tmp = node;
	}

	replacingCredits(studentHead, tmp);

	for (int i = 0; i < tmp -> attendency; i++ ){
		updateRegister(tmp -> code, tmp -> students[i], date, "ders kapandi");
	}

	free(tmp);

    saveLectureList(*lectureHead);
	saveStudentList(studentHead);
}
void syncStudentsAndLectures(lecture *lectureHead, student *studentHead) {
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

		if (strcmp(temp[4], "kayitli\n") == 0) {
			int num = atoi(temp[2]);
			char code[50];
			strcpy(code, temp[1]);
			lecture *lectureNode = existingLecture(lectureHead, code);

			student *studentNode = isValidNumber(studentHead, num);
			if (studentNode == NULL) {
				printf("Hatali kullanici girisi. \n");

			}
			else if (lectureNode == NULL) {
				printf("Hatali ders girisi. \n");
			}
			else {
				int available = canRegister(studentNode, lectureNode);
				if (available == 0) {
					updateLecture(studentNode, lectureNode);
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
			}
        }
    }

    fclose(fptr);
}
lecture* initLectureList() {
    FILE *fptr;
    char tmp[70];
    lecture *lectureHead = NULL;

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

        insertLectureByKey(&lectureHead, temp[0], temp[1],atoi(temp[3]),atoi(temp[2]));
    }

    fclose(fptr);
    saveLectureList(lectureHead);
    return lectureHead;
}
lecture* createLecture(char code[10], char name[50], int capacity, int credit) {
    lecture *tmpNode;

    tmpNode = (lecture*) malloc(sizeof(lecture));
    strcpy(tmpNode -> code, code);
    strcpy(tmpNode -> name, name);
    tmpNode -> capacity = capacity;
    tmpNode -> credit = credit;
    tmpNode -> attendency = 0;
    tmpNode -> students = (int*) calloc(2, sizeof(int));
    tmpNode -> next = NULL;

    return  tmpNode;
}
void addFrontLecture(lecture **head, char  code[10], char name[50], int capacity, int credit) {
    lecture *tmp;
    lecture *newNode = createLecture(code, name, capacity, credit);

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    tmp = *head;
    *head = newNode;

    newNode -> next = tmp;
}
void insertLectureByKey(lecture **head, char code[10], char name[50], int capacity, int credit) {
    lecture  *tmp;
    lecture *newNode;
    newNode = createLecture(code, name, capacity, credit);


    if (*head == NULL || strcmp((*head) -> code, code) > 0 ) {
        addFrontLecture(head, code, name, capacity, credit);		// Eklenen dersin en kucuk olma durumu.
        return;
    }

    tmp = *head;
    while (tmp -> next != NULL && strcmp(tmp -> next -> code, code) < 0) {
        tmp = tmp -> next;
    }

    if (tmp -> next == NULL) {
        tmp -> next = newNode;										// Eklenen dersin en sona eklenmesi
    }
    else {
        newNode -> next = tmp -> next;								// Eklenen dersin araya koyulmasi.
        tmp -> next = newNode;
    }
}
void scheduleOfStudent(lecture *lectureHead, student *studentHead) {
	int tempNum;
	printf("Hangi ogrencinin ders programini bastirmak istiyorsunuz ? \n");
	scanf("%d", &tempNum);
	student *studentNode = isValidNumber(studentHead, tempNum);
	if (studentNode == NULL) {
		printf("Girdiginiz ogrenci sistemde kayitli degildir. \n");
		printf("Ana menuye yonlendiriliyorsunuz. \n");
		return;
	}
	FILE *fptr;
	char fileName[20];
	itoa(tempNum, fileName, 10);
	strcat(fileName, "_DERSPROGRAMI");
	strcat(fileName, ".txt");
	fptr = fopen(fileName, "a");

	while (lectureHead != NULL)
	{

		int idx = 0, found = 0;
		int attendency = lectureHead -> attendency;
		while (attendency > 0 && found == 0)
		{
			if (lectureHead->students[idx++] == tempNum)
			{
				idx--;
				fprintf(fptr, "%s %s \n", lectureHead -> code, lectureHead -> name);
				found = 1;
			}
			attendency--;
		}
		lectureHead = lectureHead -> next;
	}
	fclose(fptr);
	printf("Dosyaniz basari ile olusturuldu. \n");
}
void saveLectureList(lecture *head) {
    lecture *tmp;
    tmp = head;
    FILE *fptr;
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\inputLec.txt", "w+");
    if (fptr == NULL) {
        exit(1);
    }


    while (tmp != NULL) {
        fprintf(fptr,  "%s,%s,%d,%d\n", tmp -> code, tmp -> name, tmp -> credit, tmp -> capacity);
        tmp = tmp -> next;
    }


    fclose(fptr);
}/*
void printLecture(lecture *n) {
    printf("%s, %s, %d, %d", n -> code, n -> name, n -> capacity, n -> credit);
}
void traverseLecture(lecture *head) {
    lecture *tmp = head;
    while (tmp != NULL) {
        printLecture(tmp);
        tmp = tmp->next;
        printf("\n");
    }
}*/
void deleteLectureFromStudent(lecture *lectureHead, student *studentHead) {
	int tempNum;
	char tempCode[20];
	printf("Lutfen dersten silmek istediginiz ogrencinin numarasini giriniz. \n");
	scanf("%d", &tempNum);

	student *studentNode = isValidNumber(studentHead, tempNum);

	if (studentNode == NULL) {
		printf("Silmek istediginiz ogrenci kayitlarda bulunamadi. \n");
		return;
	}
	printf("Hangi dersten silmek istiyorsunuz ?\n");
	scanf("%s", tempCode);

	lecture *lectureNode = existingLecture(lectureHead, tempCode);
	if (lectureNode == NULL) {
		printf("Girdiginiz kodda ders bulunamamistir. \n");
		return;
	}

	int idx = 0, found = 0;
	int attendency = lectureNode ->  attendency;
	while (attendency > 0 && found == 0) {
		if (lectureNode -> students[idx++] == tempNum) {
			idx--;
			deleteStudentFromLectures(lectureNode, idx);
			found = 1;
		}
		attendency--;
	}
	if (found == 0) {
		printf("Girdiginiz derste sectiginiz ogrenci kayitli degildir. \n");
		return;
	}
	//duzeltilmeli
	while(studentHead -> num != tempNum) {
		studentHead = studentHead -> next;
	}

	studentNode -> credit -= lectureNode -> credit;
	studentNode -> lectureCount--;

	char date[20];
	printf("Lutfen islemin yapildigi tarihi giriniz. \n");
	scanf(" %s", date);
	updateRegister(tempCode, tempNum, date, "birakti");
	saveStudentList(studentHead);
	saveLectureList(lectureHead);
}

student* initStudentList() {
    FILE *fptr;
    char tmp[60];
    student *studentHead = NULL;

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
        insertStudentByKey(&studentHead, atoi(temp[0]), temp[1], temp[2], atoi(temp[4]), atoi(temp[3]));
    }


    fclose(fptr);
    saveStudentList(studentHead);
    return studentHead;
}
student* isValidNumber(student *head, int num) {

    while (head != NULL && head -> num != num) {
        head = head -> next;
	}
	return head;

}
void saveStudentList(student *head) {
    student *tmp;
    tmp = head;
    FILE *fptr;
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\input.txt", "w+");
    if (fptr == NULL) {
        exit(1);
    }

    while (tmp != NULL) {
        fprintf(fptr,  "%d,%s,%s,%d,%d\n", tmp -> num, tmp -> name, tmp -> surname, tmp -> credit, tmp -> lectureCount);
        tmp = tmp -> next;
    }

    fclose(fptr);
}
student* createStudent(int num, char name[20], char surname[20], int lecture, int credit) {
    student *tmpNode;
    tmpNode = (student *)malloc(sizeof(student));
    tmpNode -> num = num;
    strcpy(tmpNode -> name, name);
    strcpy(tmpNode -> surname, surname);
    tmpNode -> lectureCount = lecture;
    tmpNode -> credit = credit;
    tmpNode -> next = NULL;
    tmpNode -> prev = NULL;
    return tmpNode;
}
void addStudent(student **studentHead) {
    int tempNum;
    char tempName[50], tempSurname[50];


    printf("Lutfen ogrencinin numarasini giriniz. \n");
    scanf(" %d", &tempNum);
    student *control = isValidNumber(*studentHead, tempNum);

    if(control != NULL) {
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
void deleteStudentFromLectures(lecture *lectureNode, int idx) {
		int attendency = lectureNode -> attendency;
		if (idx != attendency - 1) {
			while(idx + 1 < attendency) {
				lectureNode -> students[idx] = lectureNode -> students[idx + 1];
				idx++;
			}
		}

	lectureNode -> students = (int*) realloc(lectureNode -> students, (lectureNode -> attendency - 1) * sizeof (int));
	lectureNode -> attendency--;
}
void deleteStudent(student **studentHead, lecture **lectureHead) {

	lecture *ptr = *lectureHead;
    int tempNum;
    printf("Silmek istediginiz ogrencinin numarasini giriniz. \n");
    scanf("%d", &tempNum);

	student *studentNode = isValidNumber(*studentHead, tempNum);
    if (studentNode == NULL) {
        printf("Silmek istediginiz ogrenci kayitlarda bulunamadi. \n");
        return;
    }
	if (*studentHead == studentNode) {
		*studentHead = studentNode -> next;
		(*studentHead) -> prev = NULL;


	}
	else {
		studentNode -> prev -> next = studentNode -> next;
		studentNode -> next -> prev = studentNode -> prev;
	}
	free(studentNode);

	/*
    if (tmp -> num == tempNum) {
        *studentHead = (*studentHead) -> next;
        (*studentHead) -> prev = NULL;
		ptr -> students = realloc( ptr -> students, 0);
		ptr -> attendency = 0;
        free(tmp);
        return;
    }*/

	while (ptr != NULL) {
		int idx = 0, found = 0;
		int attendency = ptr ->  attendency;
		while (attendency > 0 && found == 0) {
			if (ptr -> students[idx++] == tempNum) { //Buraya da bir binary search eklenebilir.
				idx--;
				deleteStudentFromLectures(ptr, idx);
				found = 1;
			}
			attendency--;
		}
		ptr = ptr -> next;
	}

   /* student  *node;
    node = tmp -> next;
    tmp -> next = node -> next;
    node -> next -> prev = tmp;
    free(node);*/
}
void insertStudentByKey(student **head, int num, char name[20], char surname[20], int lecture, int credit)
{
    student *tmp;
    student *newNode;
    newNode = createStudent(num, name, surname, lecture, credit);


    tmp = *head;
    if (*head == NULL) {
        *head = newNode;			// Ogrenci listesinin bos olma durumu.
        return;
    }
    if ((*head) -> num > num) {
        tmp = *head;
        *head = newNode;
									// Ogrenci listesinin basina eklenmesi.
        newNode -> next = tmp;
        tmp -> prev = newNode;

        return;
    }

    while (tmp -> next != NULL && tmp -> next -> num < num) {
        tmp = tmp -> next;
    }
    newNode -> next = tmp -> next;
    if (tmp -> next != NULL) {
        newNode -> next -> prev = newNode;		// Ogrencinin sona eklenmesi
    }
    tmp -> next = newNode;
    newNode -> prev = tmp;						// Araya eklenmesi.

}/*
void printStudent(student *n) {
    printf("%d, %s, %s ", n -> num, n -> name, n -> surname);
}
void traverseStudent(student *head) {
    student *tmp = head;
    while (tmp != NULL) {
        printStudent(tmp);
        tmp = tmp->next;
        printf("\n");
    }
}
*/
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

	if (loc == -1) {
		a[count - 1] = n;
		return;
	}
    j = count - 2;

    while (j >= loc)
    {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = n;
}

void studentsOfLecture(student *studentHead, lecture *lectureHead) {
	FILE *fptr;

	char code[20];
	printf("Hangi dersi alan ogrencileri yazdirmak istiyorsunuz ?\n");
	scanf(" %s", code);

	lecture *lectureNode = existingLecture(lectureHead, code);
	if (lectureHead == NULL) {
		printf("Girdiginiz ders sistemde kayitli degildir.\n");
		printf("Ana menuye yonlendiriliyorsunuz. \n");
		return;
	}
	char fileName[20];
	strcat(fileName, lectureNode -> code);
	strcat(fileName, ".txt");
	fptr = fopen(fileName, "a");

	for (int i = 0; i < lectureNode -> attendency; i++) {
		int num = lectureNode -> students [i];
		student *studentNode = isValidNumber(studentHead, num);
		fprintf(fptr, "%d %s %s \n", studentNode -> num, studentNode -> name, studentNode -> surname);
	}
	fclose(fptr);
	printf("Dosyaniz basari ile olusturuldu. \n");
}