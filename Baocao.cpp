#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    char reason[100];
    int hour;
} Patient;

typedef struct Node {
    Patient data;
    struct Node *next;
} Node;

Node* createNode(Patient p) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

void insertSorted(Node **head, Patient p) {
    Node *newNode = createNode(p);
    if (*head == NULL || p.hour < (*head)->data.hour) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL && current->next->data.hour < p.hour)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }
}

void printSchedule(Node *head) {
    if (!head) {
        printf("Lich trong!\n");
        return;
    }
    printf("\n--- LICH KHAM ---\n");
    while (head) {
        printf("Ten: %s | Tuoi: %d | Gio: %dh | Ly do: %s\n", head->data.name, head->data.age, head->data.hour, head->data.reason);
        head = head->next;
    }
}

void searchPatient(Node *head, char *target) {
    int found = 0;
    while (head) {
        if (strcmp(head->data.name, target) == 0) {
            printf("Tim thay: %s - Tuoi: %d - Gio: %dh - Ly do: %s\n",
                   head->data.name, head->data.age, head->data.hour, head->data.reason);
            found = 1;
        }
        head = head->next;
    }
    if (!found) printf("Khong tim thay benh nhan %s\n", target);
}

void deletePatient(Node **head, char *target) {
    Node *current = *head, *prev = NULL;
    while (current && strcmp(current->data.name, target) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay benh nhan de xoa.\n");
        return;
    }
    if (!prev)
        *head = current->next;
    else
        prev->next = current->next;
    free(current);
    printf("Da xoa benh nhan %s khoi lich kham.\n", target);
}

void freeList(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Patient *waitingList = NULL;
    int n = 0, choice;
    Node *schedule = NULL;

    do {
        printf("\n===== MENU PHONG KHAM =====\n");
        printf("1. Nhap danh sach benh nhan cho\n");
        printf("2. Dat lich kham\n");
        printf("3. In lich kham\n");
        printf("4. Tim benh nhan theo ten\n");
        printf("5. Huy lich kham\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap so benh nhan: ");
                scanf("%d", &n);
                getchar();
                waitingList = (Patient*)malloc(n * sizeof(Patient));
                for (int i = 0; i < n; i++) {
                    printf("\nBenh nhan %d:\n", i + 1);
                    printf("Ten: "); gets(waitingList[i].name);
                    printf("Tuoi: "); scanf("%d", &waitingList[i].age); getchar();
                    printf("Ly do kham: "); gets(waitingList[i].reason);
                    printf("Gio hen (0-23): "); scanf("%d", &waitingList[i].hour); getchar();
                }
                break;

            case 2:
                if (!waitingList) {
                    printf("Chua nhap danh sach cho!\n");
                    break;
                }
                for (int i = 0; i < n; i++)
                    insertSorted(&schedule, waitingList[i]);
                free(waitingList);
                waitingList = NULL;
                printf("Da dat lich cho tat ca benh nhan.\n");
                break;

            case 3:
                printSchedule(schedule);
                break;

            case 4: {
                char name[50];
                printf("Nhap ten can tim: "); gets(name);
                searchPatient(schedule, name);
                break;
            }

            case 5: {
                char name[50];
                printf("Nhap ten can xoa: "); gets(name);
                deletePatient(&schedule, name);
                break;
            }

            case 0:
                printf("Dang thoat...\n");
                free(waitingList);
                freeList(schedule);
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);

    return 0;
}

