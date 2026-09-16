#include <stdio.h>
#include <string.h>

#define MAX 50

struct Patient {
    char name[30];
    int priority;
    int order;
};

struct Patient heap[MAX];
int size = 0;
int arrivalOrder = 0;

// Swap two patients
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Check whether patient a has higher priority than b
int isHigherPriority(struct Patient a, struct Patient b) {
    if (a.priority < b.priority)
        return 1;

    if (a.priority == b.priority && a.order < b.order)
        return 1;

    return 0;
}

// Add a patient to the priority queue
void addPatient(char name[], int priority) {
    if (size >= MAX) {
        printf("Queue is full!\n");
        return;
    }

    struct Patient newPatient;
    strcpy(newPatient.name, name);
    newPatient.priority = priority;
    newPatient.order = arrivalOrder++;

    int i = size;
    heap[size] = newPatient;
    size++;

    // Move upward to maintain min-heap
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (isHigherPriority(heap[i], heap[parent])) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }

    printf("Patient %s added successfully.\n", name);
}

// Treat the next patient
void treatNextPatient() {
    if (size == 0) {
        printf("No patients waiting.\n");
        return;
    }

    struct Patient treated = heap[0];

    printf("\nTreating Patient: %s\n", treated.name);
    printf("Priority: %d\n", treated.priority);

    // Move last patient to root
    heap[0] = heap[size - 1];
    size--;

    // Move downward to maintain min-heap
    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size &&
            isHigherPriority(heap[left], heap[smallest])) {
            smallest = left;
        }

        if (right < size &&
            isHigherPriority(heap[right], heap[smallest])) {
            smallest = right;
        }

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

// Display waiting patients
void displayQueue() {
    if (size == 0) {
        printf("\nNo patients in queue.\n");
        return;
    }

    printf("\nWaiting Patients:\n");

    for (int i = 0; i < size; i++) {
        printf("%s - Priority %d\n",
               heap[i].name, heap[i].priority);
    }
}

int main() {
    int choice, priority;
    char name[30];

    while (1) {
        printf("\n===== PATIENT PRIORITY QUEUE =====\n");
        printf("1. Add Patient\n");
        printf("2. Treat Next Patient\n");
        printf("3. Display Waiting Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter patient name: ");
                scanf("%s", name);

                printf("Enter priority (1=Emergency, 2=Urgent, 3=Routine): ");
                scanf("%d", &priority);

                if (priority < 1 || priority > 3) {
                    printf("Invalid priority!\n");
                } else {
                    addPatient(name, priority);
                }
                break;

            case 2:
                treatNextPatient();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
