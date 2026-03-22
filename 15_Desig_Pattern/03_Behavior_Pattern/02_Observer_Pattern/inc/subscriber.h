#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct Publisher Publisher;

/* Interfcae subcriber để các thực thể cụ thể kế thừa và ghi đè lại phương thưc update riêng với từng thực thể */
typedef struct Subscriber
{
    void (*update)(struct Subscriber *self, Publisher *context, const char *eventInfo);
    void *data;
} Subscriber;

#endif // SUBSCRIBER_H