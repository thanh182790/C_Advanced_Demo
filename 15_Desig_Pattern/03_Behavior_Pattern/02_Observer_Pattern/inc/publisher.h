#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "subscriber.h"

#define MAX_SUBSCRIBERS 10

/* Interface để các subject cụ thể kế thừa */
typedef struct Publisher
{
    Subscriber *subscribers[MAX_SUBSCRIBERS];
    int subscriberCount;

    void (*subscribe)(struct Publisher *self, Subscriber *s);
    void (*unsubscribe)(struct Publisher *self, Subscriber *s);
    void (*notifySubscribers)(struct Publisher *self, const char *eventInfo);
} Publisher;

void publisherInit(Publisher *pub);

#endif // PUBLISHER_H