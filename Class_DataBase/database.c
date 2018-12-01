#include "functions.h"

int main(int argc, char **argv) {
  struct Student students[DEFAULT_SIZE];
  int choice;
  initialize(students);
  while(1) {
    printf("\n==================== Menu ====================\n");
    printf("1. Add Students\n");
    printf("2. Search For Student\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. View All Students\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
  
    switch(choice) {
      case 1:
        addStudent(students);
        break;
      case 2:
        searchStudents(students);
        break;
      case 3:
        updateStudent(students);
        break;
      case 4:
        deleteStudent(students);
        break;
      case 5:
        viewAllStudents(students);
        break;
      case 6:
        exit(0);
    }
  }
    return 0;
}