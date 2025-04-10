#include <stdio.h>
#include <stdlib.h>

int in = -1, out = -1;
int buffer[5];

void consume();
void produce(int x);
void display();

int main() {
    int choice, item;
    do {
        printf("\n1. Produce\n2. Consume\n3. Display\n4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter item to insert to buffer: ");
                scanf("%d", &item);
                produce(item);
                break;
            case 2:
                consume();
                break;
            case 3:
                display();
                break;
            case 4:
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while (choice != 4);
    return 0;
}

void consume() {
    if (in == -1) {
        printf("Nothing to consume\n");
    } else {
        printf("Item consumed is: %d\n", buffer[in]);
        if (in == out) {
            in = out = -1;
        } else {
            in = (in + 1) % 5;
        }
    }
}

void produce(int x) {
    if ((out + 1) % 5 == in) {
        printf("Cannot produce till consumer consumes an item\n");
    } else {
        if (in == -1) {
            in = out = 0;
        } else {
            out = (out + 1) % 5;
        }
        buffer[out] = x;
        printf("The produced item is: %d\n", buffer[out]);
    }
}

void display() {
    int i;
    if (in == -1) {
        printf("Buffer is empty\n");
        return;
    }
    printf("The buffer contains:\n");
    if (out >= in) {
        for (i = in; i <= out; ++i) {
            printf(" - %d ", buffer[i]);
        }
    } else {
        for (i = in; i < 5; ++i) {
            printf(" - %d ", buffer[i]);
        }
        for (i = 0; i <= out; ++i) {
            printf(" - %d ", buffer[i]);
        }
    }
    printf("\n");
}
