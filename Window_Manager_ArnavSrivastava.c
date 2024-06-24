#include <stdio.h>
#include <stdlib.h>

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

void open_w(struct window* wm, int num)
{
    struct window_manager* new_node = create_node(num);
    if (wm->head == NULL)
    {
        wm->head = new_node;
        wm->tail = new_node;
    }
    else
    {
        wm->tail->next = new_node;
        wm->tail = new_node;
    }
}

void switch_w(struct window* wm, int num)
{
    struct window_manager* curr = wm->head;
    struct window_manager* prev = NULL;

    while (curr->ID != num && curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    curr->next = wm->head;
    wm->head = curr;

    if (curr == wm->tail)
    {
        wm->tail = prev;
    }
}

void close_w(struct window* wm, int num)
{
    // Implementation to be added
}

int main()
{
    struct window wm = {NULL};

    open_w(&wm, 0);
    open_w(&wm, 1);
    open_w(&wm, 2);
    switch_w(&wm, 1);

    struct window_manager* current = wm.head;
    while (current != NULL) {
        printf("%d\n", current->ID);
        current = current->next;
    }

    return(0);
}