#ifndef LINK_H
#define LINK_H

typedef struct Link {
    struct Link* next;
    int value;
} Link;

#endif /* LINK_H */