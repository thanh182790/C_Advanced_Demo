#include <stdio.h>
#include <stdlib.h>

/* .data */
int g_counter = 42;
static int s_configValue = 100;

/* .bss */
int g_errorCount;
static int s_statusFlag;

const int g_constValue = 12345;                                 /* where is the segment ??? ---> */
char g_message[] = "Hello C_Advanced";                              /* where is the segment ??? ---> */
const char *g_constText = "Hello C_Advanced";                   /* where is the segment of "Hello C_Advanced" ??? ---> */

/* Heap pointers */
void *g_buffer1 = NULL;
void *g_buffLeak = NULL; 

/* Function prototypes */
void processData(int value);
void computeResult(int input);
void analyzeBuffer(int depth);

/* Helper to print section titles */
static void printSection(const char *title) {
    printf("\n==== %s ====\n", title);
}

int main(void)
{
    int mainLocal = 7;

    /* Allocate memory on the heap */
    g_buffer1 = malloc(64);
    g_buffLeak = malloc(128);

    if (!g_buffer1 || !g_buffLeak) {
        perror("malloc");
        return 1;
    }

    ((char*)g_buffer1)[0] = 'A';
    ((char*)g_buffLeak)[0] = 'B';

    printSection("MEMORY SEGMENTS");

    /* .text section (functions) */
    printf("Address of main()                : %p (.text)\n", (void*) &main);
    printf("Address of processData()         : %p (.text)\n", (void*) &processData);
    printf("Address of computeResult()       : %p (.text)\n", (void*) &computeResult);
    printf("Address of analyzeBuffer()       : %p (.text)\n", (void*) &analyzeBuffer);

    /* .rodata */
    printf("Address of g_constText pointer : %p (.data, points to .rodata)\n", (void*) &g_constText);
    printf("Address of string literal      : %p (.rodata) -> \"%s\"\n", (void*) g_constText, g_constText);
    printf("Address of g_constValue        : %p (.rodata) value=%d\n", (void*) &g_constValue, g_constValue);

    /* .data / .bss */
    /* g_constText[0] = 'N';
       g_message[0] = 'N' */
    printf("Address of g_counter           : %p (.data) value=%d\n", (void*) &g_counter, g_counter);
    printf("Address of g_message           : %p (.data) -> \"%s\"\n", (void*) g_message, g_message);
    printf("Address of g_errorCount        : %p (.bss) value=%d\n", (void*) &g_errorCount, g_errorCount);
    printf("Address of s_configValue       : %p (.data) value=%d\n", (void*) &s_configValue, s_configValue);
    printf("Address of s_statusFlag        : %p (.bss) value=%d\n", (void*) &s_statusFlag, s_statusFlag);

    /* heap */
    printf("Address of g_buffer1 (heap)     : %p (allocated 64 bytes)\n", g_buffer1);
    printf("Address of g_buffLeak (heap)    : %p (allocated 128 bytes)\n", g_buffLeak);

    /* stack */
    printf("Address of mainLocal (stack)   : %p value=%d\n", (void*) &mainLocal, mainLocal);

    /* Call nested functions to illustrate stack frame growth */
    printSection("CALL STACK DEMO");
    processData(10);

    free(g_buffer1);
    // g_buffer1 = NULL;           /* Why need do this ???? */

    printSection("AFTER FREE OPERATION");
    printf("g_buffer1 after free            : %p\n", g_buffer1);
    printf("g_buffLeak still allocated      : %p\n", g_buffLeak);

    printSection("PROGRAM END");
    return 0;
}

/* ---------------------------
   Function definitions
   --------------------------- */

void processData(int value)
{
    const int thanhTroll = 10;
    static const int staticTroll = 99;
    int temp = value + 1;
    static int s_callCount = 1;          /* ---> .bss/.data/stack ?*/
    static int s_errorFlag;              /* ---> .bss/.data/stack ?*/

    printf("Gia trị của thanhTroll %d\n", thanhTroll);
    printf("%s(): param value addr  : %p value=%d\n", __func__, (void*)&value, value);
    printf("%s(): local temp addr   : %p value=%d\n", __func__, (void*)&temp, temp);
    printf("%s(): static callCount  : %p value=%d\n", __func__, (void*)&s_callCount, s_callCount);
    printf("%s(): static errorFlag  : %p value=%d\n", __func__, (void*)&s_errorFlag, s_errorFlag);

    s_callCount++;
    computeResult(temp + 2);
}

void computeResult(int input)
{
    int result = input * 2;
    static int s_lastResult = 0;

    printf("%s(): param input addr: %p value=%d\n", __func__, (void*)&input, input);
    printf("%s(): local result addr: %p value=%d\n", __func__, (void*)&result, result);
    printf("%s(): static lastResult: %p value=%d\n", __func__, (void*)&s_lastResult, s_lastResult);

    s_lastResult = result;
    analyzeBuffer(result + 5);
}

void analyzeBuffer(int depth)
{
    int localDepth = depth;
    char stackBuffer[32];   /* stackBuffer on stack */
    static char s_analysisState[16]; /* .bss/.data ?*/

    for (int i = 0; i < (int)sizeof(stackBuffer); ++i)
        stackBuffer[i] = (char)(i + 65); /* fill to ensure it exists on stack */

    printf("%s(): param depth addr : %p value=%d\n", __func__, (void*)&depth, depth);
    printf("%s(): localDepth addr  : %p value=%d\n", __func__, (void*)&localDepth, localDepth);
    printf("%s(): stackBuffer addr : %p size=%zu\n", __func__, (void*)stackBuffer, sizeof(stackBuffer));
    printf("%s(): static state addr: %p\n", __func__, (void*)&s_analysisState);
}
