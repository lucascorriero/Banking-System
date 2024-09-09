#ifndef RECORD_H
#define RECORD_H
struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
#endif