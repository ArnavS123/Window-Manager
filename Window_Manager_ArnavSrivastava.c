#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct window_manager
{
    int ID;
    struct window_manager* next;
};

struct window
{
    struct window_manager *head;
    struct window_manager *tail;
};

struct window_manager* create_node(int num) {
    struct window_manager* wm = (struct window_manager*)malloc(sizeof(struct window_manager));

    wm->ID = num;
    wm->next = NULL;
    
    return wm;
}

int top(struct window* wm) {
    if (wm->head == NULL) {
        // Handle the case where the list is empty
        return -1; // Return a special value to indicate the list is empty
    }
    return wm->head->ID;
}

void print_windows(struct window* wm) {
    struct window_manager* curr = wm->head;
    while (curr != NULL) {
        printf("Window ID: %d\n", curr->ID);
        curr = curr->next;
    }
}

void open_w(struct window* wm, int num) {
    struct window_manager* new_node = create_node(num);
    if (new_node == NULL) {
        return; // Handle the case where node creation fails
    }
    if (wm->head == NULL) {
        wm->head = new_node;
        wm->tail = new_node;
    } else {
        new_node->next = wm->head;
        wm->head = new_node;
    }
}

void switch_w(struct window* wm, int num) {
    if (wm->head == NULL || wm->head->ID == num) {
        return; // No need to switch if the list is empty or the window is already at the head
    }

    struct window_manager* curr = wm->head;
    struct window_manager* prev = NULL;

    while (curr != NULL && curr->ID != num) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return; // Node not found
    }

    if (prev != NULL) {
        prev->next = curr->next;
        curr->next = wm->head;
        wm->head = curr;
        if (curr == wm->tail) {
            wm->tail = prev;
        }
    }
}

void close_w(struct window* wm, int num) {
    if (wm->head == NULL) {
        return; // No windows to close
    }

    struct window_manager* curr = wm->head;
    struct window_manager* prev = NULL;

    while (curr != NULL && curr->ID != num) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return; // Window with the given ID not found
    }

    if (prev == NULL) {
        // The window to close is the head
        wm->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (curr == wm->tail) {
        // The window to close is the tail
        wm->tail = prev;
    }

    free(curr);
}

void process_file(struct window* wm, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char command[16];
        int num;
        if (sscanf(line, "%s %d", command, &num) == 2) {
            if (strcmp(command, "open") == 0) {
                open_w(wm, num);
            } else if (strcmp(command, "switch") == 0) {
                switch_w(wm, num);
            } else if (strcmp(command, "close") == 0) {
                close_w(wm, num);
            }
            int top_id = top(wm);
            if (top_id != -1) {
                printf("%d\n", top_id);
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <info_file>\n", argv[0]);
        return 1;
    }

    struct window wm = {NULL, NULL};
    process_file(&wm, argv[1]);

    return 0;
}
