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

struct window_manager* create_node(int num)
{
    struct window_manager* wm = (struct window_manager*)malloc(sizeof(struct window_manager));

    wm->ID = num;
    wm->next = NULL;
    
    return(wm);
}

int print_top(struct window* wm)
{
    if (wm->head == NULL)
    {
        return(-1); // List is empty
    }

    return(wm->head->ID);
}

void open_w(struct window* wm, int num)
{
    struct window_manager* new_node = create_node(num);

    if (wm->head == NULL) // List is empty
    {
        wm->head = new_node;
        wm->tail = new_node;
    }
    else // List is not empty
    {
        new_node->next = wm->head;
        wm->head = new_node;
    }
}

void switch_w(struct window* wm, int num)
{
    if (wm->head == NULL || wm->head->ID == num)
    {
        return; // List is empty or window is already at the head
    }

    struct window_manager* curr = wm->head;
    struct window_manager* prev = NULL;

    while (curr != NULL && curr->ID != num)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        return; // Node not found
    }

    if (prev != NULL)
    {
        prev->next = curr->next;
        curr->next = wm->head;
        wm->head = curr;
        if (curr == wm->tail)
        {
            wm->tail = prev;
        }
    }
}

void close_w(struct window* wm, int num)
{
    if (wm->head == NULL)
    {
        return; // No windows to close
    }

    struct window_manager* curr = wm->head;
    struct window_manager* prev = NULL;

    while (curr != NULL && curr->ID != num)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        return; // Window with the given ID not found
    }

    if (prev == NULL)
    {
        wm->head = curr->next; // Window to close is the head
    }
    else
    {
        prev->next = curr->next;
    }

    if (curr == wm->tail)
    {
        wm->tail = prev; // Window to close is the tail
    }

    free(curr);
}

void process_input(struct window* wm)
{
    char command[16];
    int num;

    while (scanf("%s %d", command, &num) == 2)
    {
        if (strcmp(command, "open") == 0)
        {
            open_w(wm, num);
        }
        else if (strcmp(command, "switch") == 0)
        {
            switch_w(wm, num);
        }
        else if (strcmp(command, "close") == 0)
        {
            close_w(wm, num);
        }

        int top_id = print_top(wm);
        if (top_id != -1)
        {
            printf("%d\n", top_id);
        }
    }
}

int main()
{
    struct window wm = {NULL, NULL};
    process_input(&wm);

    return(0);
}
