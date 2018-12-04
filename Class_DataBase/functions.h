#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DEFAULT_SIZE = 150;
const char nullStr[] = "";
const char STUDENTS_FILE[] = "Students.txt";
const char SEPERATOR[] = "================================================";
int stCounter = 0;

struct Student {
    char id[9];
    char name[20];
    char email[30];
    char address[50];
};

int countLines(const char *);
char *formatName(char []);
char *demangleName(char []);
void addId(struct Student *);
int validId(char studentId[]);
void addName(struct Student *);
void addEmail(struct Student *);
void initialize(struct Student *);
void appendToFile(struct Student);
void addAddress(struct Student *);
void addStudent(struct Student *);
void overwriteFile(struct Student *);
void formatStudent(struct Student *);
void updateStudent(struct Student *);
void deleteStudent(struct Student *);
void printStudentInfo(struct Student *);
int searchStudents(struct Student *);
void viewAllStudents(struct Student *);
void updateStudentStructure(struct Student *);
void swap(struct Student *, struct Student *);
void deleteStudentStructure(struct Student *, int);

void formatStudent(struct Student *student) {
    strcpy(student->name, demangleName(student->name));
    strcpy(student->address, demangleName(student->address));
}

void overwriteFile(struct Student StudentList[]) {
    char rmCommand[17] = "rm ";
    strcat(rmCommand, STUDENTS_FILE);
    system(rmCommand);
    FILE *fp = fopen(STUDENTS_FILE, "w");
    fclose(fp);
    int i;
    for(i=0; i<stCounter; i++) {
        appendToFile(StudentList[i]);
    }
}

void appendToFile(struct Student student) {
    FILE *file = fopen(STUDENTS_FILE, "a");
    fprintf(file, "%s %s %s %s\n", student.id, 
    formatName(student.name), student.email, formatName(student.address));
    fclose(file);
}

int validId(char studentId[]) {
    if(studentId[0] == 'M' && studentId[1] == 'E' 
       && studentId[2] == 'C' && strlen(studentId) == 8) {
	    return 1;	
    }
    return 0;
}

void swap(struct Student *stu1, struct Student *stu2) {
    struct Student temp;
    temp = *stu1;
    *stu1 = *stu2;
    *stu2 = temp;
}

void printStudentInfo(struct Student *student) {
    printf("Id: \t\t%s\n", student->id);
    printf("Name: \t\t%s\n", student->name);
    printf("Email: \t\t%s\n", student->email);
    printf("Address: \t%s\n", student->address);
    printf("\n%s\n", SEPERATOR);
}

int countLines(const char fileName[]) {
    FILE *file = fopen(fileName, "r");
    int ch = 0;
    int lines = 0;
    while ((ch = fgetc(file)) != EOF) {
        if(ch == '\n')
            lines++;
    }
    return lines;
}

char *formatName(char text[]) {
    char *result;
    int size = strlen(text);
    result = malloc(size);
    int i, j=0;
    for(i=0; i < size; i++) {
        if(text[i] == ' ') {
            result[j++] = '^';
        } else {
            result[j++] = text[i];
        }
    }
    return result;
}

char *demangleName(char text[]) {
    char *result;
    int size = strlen(text);
    result = malloc (sizeof(char) * size);
    int i, j=0;
    for(i=0; i < size; i++) {
        if(text[i] == '^') {
            result[j++] = ' ';
        } else {
            result[j++] = text[i];
        }
    }
    return result;
}

void initialize(struct Student StudentList[]) {
    stCounter = 0;
    FILE *file = fopen(STUDENTS_FILE, "r");
    if(!file) {
        FILE *newFile = fopen(STUDENTS_FILE, "w");
        fclose(newFile);
        return;
    }
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    if(file_size == 0) {
        return; 
    }
    rewind(file);
    int lineCount = countLines(STUDENTS_FILE);
    while (!feof(file) ) {
        struct Student student;
        fscanf(file,"%s %s %s %s", student.id, 
            student.name, student.email, student.address);
        formatStudent(&student);
        StudentList[stCounter] = student;
        stCounter++;
    }
    stCounter--; // Takes the counter one step back
    fclose(file);
}

void addId(struct Student StudentList[]) {
  char tmpId[9];
  int isValid = 0;
  do {
    int exists = 0;
    printf("Enter an Id starting with MECxxxxx: ");
    getchar();
    scanf("%[^\n]s", tmpId);

    if (validId(tmpId)) {
        int i;
      for(i=0; i < stCounter; i++) {
          if(!strcmp(StudentList[i].id, tmpId)) {
            printf("Id already Exists\n");
            exists = 1;
            break;
          }
        }
        if(!exists){
          strcpy(StudentList[stCounter].id, tmpId);
          isValid = 1;
        } else {
            printf("Student already exists in the database\n");
        }
    } else {
      printf("Id's must start with MEC and must be 8 characters in length\n");
    }
  } while(!isValid);
}

void addName(struct Student StudentList[]) {
  char tmpName[20];
  printf("Enter your Full name: ");
  getchar();
  scanf("%[^\n]s", tmpName);
  strcpy(StudentList[stCounter].name, tmpName);
}

void addEmail(struct Student StudentList[]) {
  char tmpEmail[30];
  printf("Enter your email address: ");
  getchar();
  scanf("%[^\n]s", tmpEmail);
  strcpy(StudentList[stCounter].email, tmpEmail);
}

void addAddress(struct Student StudentList[]) {
  char tmpAddress[40];
  printf("Enter your Home address: ");
  getchar();
  scanf("%[^\n]s", tmpAddress);
  strcpy(StudentList[stCounter].address, tmpAddress);
}

void addStudent(struct Student StudentList[]) {
  addId(StudentList);
  addName(StudentList);
  addEmail(StudentList);
  addAddress(StudentList);
  appendToFile(StudentList[stCounter]);
  stCounter++;
}

void viewAllStudents(struct Student StudentList[]) {
  if(stCounter == 0) {
    printf("Database is Empty\n");
  } else {
      int i;
    printf("There are %d students in the database", stCounter);
    printf("\n================== Students ==================\n");
    for(i = 0; i < stCounter; i++) {
        printStudentInfo(&StudentList[i]);
    }
  }
}

int searchStudents(struct Student StudentList[]) {
    if(stCounter == 0) {
        printf("Database is Empty\n");
    } else {
      char tmpId[9];
      int i=0;
      int found = 0; // used as booleans
      int isValid = 0; // used as booleans
      printf("Enter Student's Id: ");
      getchar();
      scanf("%s", tmpId);
      do {
        if(validId(tmpId)) {
          isValid = 1;
          for(; i < stCounter; i++) {
            if(!strcmp(StudentList[i].id, tmpId)) {
              found = 1;
              printf("\n%s\n", SEPERATOR);
              printStudentInfo(&StudentList[i]);
              break;
            }
          }
          if(!found) {
            printf("No student was found with that Id\n");
          } else {
              return i;
          }
        } else {
          printf("Id's must start with MEC and must be 8 characters in length\n");
        }
      } while(!isValid);
    }
    return -1;
}

void updateStudent(struct Student StudentList[]) {
    int found = searchStudents(StudentList);
    char option;
    if(found != -1) {
        printf("Student found\n");
        while(1) {
            printf("Do you wish to continue (Y/N): ");
            getchar();
            scanf("%c", &option);
            if(option == 'Y' || option == 'N')
                break;
        }
        if(option == 'Y') {
            updateStudentStructure(&(StudentList[found]));
            overwriteFile(StudentList);
        }
    }
}

void updateStudentStructure(struct Student *student) {
    printf("Update Student's Name: ");
    getchar();
    scanf("%[^\n]s", student->name);
    printf("Update Student's Email: ");
    getchar();
    scanf("%[^\n]s", student->email);
    printf("Update Student's Address: ");
    getchar();
    scanf("%[^\n]s", student->address);
}


void deleteStudent(struct Student StudentList[]) {
    char option;
    int found = searchStudents(StudentList);
    if(found != -1) {
        while(1) {
            printf("Do you wish to continue (Y/N): ");
            getchar();
            scanf("%c", &option);
            if(option == 'Y' || option == 'N')
                break;
        }
        if(option == 'Y') {
            deleteStudentStructure(StudentList, found);
            overwriteFile(StudentList);
        }
    }
}

void deleteStudentStructure(struct Student StudentList[], int indexOfFound) {
    int i = indexOfFound;
    for(; i < stCounter-1; i++) {
        swap(&StudentList[i], &StudentList[i+1]);
    }
    strcpy(StudentList[i].id, nullStr);
    strcpy(StudentList[i].name, nullStr);
    strcpy(StudentList[i].email, nullStr);
    strcpy(StudentList[i].address, nullStr);
    stCounter--;
}

#endif // FUNCTIONS_H