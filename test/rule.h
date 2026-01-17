#ifndef RULE_H
#define RULE_H

typedef enum
{
    MODE_INSTANT,
    MODE_AVG
} RuleMode;

typedef struct
{
    char name[32];
    char sensor[16];
    RuleMode mode;
    int window;
    int stateful;
    char condition[128];
    char action[64];
    char message[128];
    int persist;
    int counter;
} Rule;

extern Rule rules[];
extern int rule_count;
void print_all_rules(void); 
#endif
