// src/main.c
#include "types.h"

// Forward declarations
void demo_struct(void);
void demo_union(void);
void run_system(void);

int main()
{
#ifdef STAGE_STRUCT
    demo_struct();

#elif defined(STAGE_UNION)
    demo_union();

#elif defined(STAGE_ENUM)
    run_system(); // ← DÙNG TẤT CẢ

#else
    printf("Error: No stage defined! Use: make struct/union/enum\n");
#endif

    return 0;
}
