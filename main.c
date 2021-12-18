#include <stdio.h>
#include <strings.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    int num;
    char name[20];
    char surname[20];
    int lectureCount;
    int credit;

    struct node *next;
    struct node *prev;
}studentList;

typedef struct LectureNode {
    int code;
    char name[20];
    int capacity;
    int credit;
    int *numbers;
}lectureList;


void saveStudentList(studentList *head);
void addFrontStudent(studentList **head, int num, char name[20], char surname[20], int lecture, int credit);
void addLastStudent(studentList **head, int num, char name[20], char surname[20], int lecture, int credit);
void insertByKey(studentList **head, int num, char name[20], char surname[20], int lecture, int credit);
void deleteFrontStudent(studentList **head);
void deleteLastStudent(studentList **head);
void traverseStudent(studentList *head);




int main() {
    FILE *fptr;
    char tmp[50];
    studentList *studentHead = NULL;

    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\input.txt", "r");
    if (fptr == NULL) {
        return 1;
    }


    while (fgets(tmp, 50, fptr) != NULL) {
        char *ptr;
        char delim[] = ",";
        char temp[50][50];
        int idx = 0;

        ptr = strtok(tmp, delim);

        while(ptr != NULL)
        {
            strcpy(temp[idx++], ptr);
            //printf("icerisi %s\n", ptr);
            ptr = strtok(NULL, delim);
        }
        //printf("Num = %d\n", atoi(temp[0]));
        insertByKey(&studentHead, atoi(temp[0]), temp[1], temp[2], atoi(temp[3]), atoi(temp[4]));
        //printf("\n\n\n");
    }

    //Student List.


    fclose(fptr);

    saveStudentList(studentHead);



    return 0;
}

void saveStudentList(studentList *head) {
    studentList *tmp;
    tmp = head;
    FILE *fptr;
    fptr = fopen("D:\\Workspaces\\C Workspace\\YapisalDonemProje\\input.txt", "w+");
    if (fptr == NULL) {
        printf("lan \n");
        exit(1);
    }


    while (tmp -> next != NULL) {
        printf("%d\n", tmp -> num);
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
void insertByKey(studentList **head, int num, char name[20], char surname[20], int lecture, int credit)
{
    studentList *tmp;
    studentList *newNode;

    if (*head == NULL) {
        addFrontStudent(head, num, name, surname, lecture, credit);
        return;
    }
    tmp = *head;
    while (tmp -> next != NULL && tmp -> next -> num < num) {
        tmp = tmp -> next;
    }
    newNode = createStudent(num, name, surname, lecture, credit);
    newNode -> prev = tmp;
    if (tmp -> next == NULL) {
        tmp -> next = newNode;
    }
    else {
        newNode -> next = tmp -> next;
        tmp -> next = newNode;
    }
}
void addFrontStudent(studentList **head, int num, char name[20], char surname[20], int lecture, int credit)
{
    studentList *tmp;
    studentList *newNode = createStudent(num, name, surname, lecture, credit);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    tmp = *head;
    tmp -> prev = newNode;
    *head = newNode;
    newNode -> next = tmp;
}
void addLastStudent(studentList **head, int num, char name[20], char surname[20], int lecture, int credit)
{
    if (*head == NULL)
    {
        addFrontStudent(head, num, name, surname, lecture, credit);
        return;
    }

    studentList *tmp;

    tmp = *head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }
    studentList *newNode = createStudent(num, name, surname, lecture, credit);
    newNode -> prev = tmp;
    tmp -> next = newNode;
}
void deleteFrontStudent(studentList **head) {
    if (*head == NULL) {
        printf("Nothing to delete! \n");
        return;
    }

    studentList *tmp = (*head) -> next;
    tmp -> prev = NULL;
    free(*head);
    *head = tmp;
}
void deleteLastStudent(studentList **head) {
    if (*head == NULL) {
        printf("Nothing to delete! \n");
        return;
    }
    studentList *tmp = *head;

    while(tmp -> next -> next != NULL) {
        tmp = tmp -> next;
    }
    free(tmp -> next -> next);
    tmp -> next = NULL;
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

