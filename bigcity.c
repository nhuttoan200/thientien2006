#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float math;
    float physics;
    float chemistry;
    float average;
} Student;

// Hàm xóa bộ đệm nhập
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inputStudent(Student *s, int index) {
    printf("Nhap thong tin sinh vien thu %d:\n", index + 1);
    printf("ID: ");
    scanf("%d", &s->id);
    clearInputBuffer(); 

    printf("Ten: ");
    fgets(s->name, NAME_LENGTH, stdin);
    s->name[strcspn(s->name, "\n")] = 0;

    printf("Diem Toan: ");
    scanf("%f", &s->math);
    printf("Diem Ly: ");
    scanf("%f", &s->physics);
    printf("Diem Hoa: ");
    scanf("%f", &s->chemistry);

    s->average = (s->math + s->physics + s->chemistry) / 3.0;
}

void printStudent(const Student *s) {
    printf("ID: %d | Ten: %s | Toan: %.2f | Ly: %.2f | Hoa: %.2f | TB: %.2f\n",
           s->id, s->name, s->math, s->physics, s->chemistry, s->average);
}

void printAllStudents(Student students[], int n) {
    printf("\nDanh sach sinh vien:\n");
    for (int i = 0; i < n; i++) {
        printStudent(&students[i]);
    }
}

void swapStudents(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void sortByAverage(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].average < students[j].average) {
                swapStudents(&students[i], &students[j]);
            }
        }
    }
}

int searchByName(Student students[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void updateScore(Student *s) {
    printf("Cap nhat diem cho sinh vien %s:\n", s->name);
    printf("Diem Toan moi: ");
    scanf("%f", &s->math);
    printf("Diem Ly moi: ");
    scanf("%f", &s->physics);
    printf("Diem Hoa moi: ");
    scanf("%f", &s->chemistry);
    s->average = (s->math + s->physics + s->chemistry) / 3.0;
}

int main() {
    Student students[MAX_STUDENTS];
    int n;

    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    if (n > MAX_STUDENTS || n <= 0) {
        printf("So luong khong hop le.\n");
        return 1;
    }
    clearInputBuffer();

    // Nhap danh sach sinh vien
    for (int i = 0; i < n; i++) {
        inputStudent(&students[i], i);
    }

    // In danh sach sinh vien
    printAllStudents(students, n);

    // Sap xep sinh vien theo diem trung binh giam dan
    sortByAverage(students, n);
    printf("\nDanh sach sau khi sap xep theo diem trung binh giam dan:\n");
    printAllStudents(students, n);

    // Tim kiem sinh vien theo ten
    char searchName[NAME_LENGTH];
    printf("\nNhap ten sinh vien can tim: ");
    fgets(searchName, NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int idx = searchByName(students, n, searchName);
    if (idx != -1) {
        printf("Tim thay sinh vien:\n");
        printStudent(&students[idx]);
        // Cap nhat diem
        updateScore(&students[idx]);
        printf("Thong tin sau cap nhat:\n");
        printStudent(&students[idx]);
    } else {
        printf("Khong tim thay sinh vien co ten %s\n", searchName);
    }

    return 0;
}
