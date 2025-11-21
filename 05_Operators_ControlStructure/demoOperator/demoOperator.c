#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

/************************************************************
 *  EXAMPLE 1 — FLOAT COMPARISON
 *  Why floating-point numbers should NOT be compared directly.
 ************************************************************/
#ifdef FLOAT_COMPARE

typedef union
{
    double f;
    uint64_t bits;
} fp64_t;

void example_float_compare()
{
    fp64_t a, b;
    a.f = 0.1 + 0.1 + 0.1;   // mathematically = 0.3
    b.f = 0.3;

    printf("===== EXAMPLE 1: FLOAT COMPARISON =====\n");
    printf("a.f = %.20f\n", a.f);
    printf("b.f = %.20f\n", b.f);
    printf("a.bits = %llu\n", (unsigned long long)a.bits);
    printf("b.bits = %llu\n", (unsigned long long)b.bits);

    if (a.f == b.f)
        printf("Direct compare: a == b (unexpected)\n");
    else
        printf("Direct compare: a != b (expected)\n");

    // Correct comparison using epsilon
    /*
    double epsilon = 1e-12;
    if (fabs(a.f - b.f) < epsilon)
        printf("Approx compare with epsilon: a ≈ b (correct)\n");
    else
        printf("Approx compare with epsilon: a NOT ≈ b\n");
    */

    printf("\n");
}

#endif


/************************************************************
 *  EXAMPLE 2 — LOGICAL OPERATOR SHORT-CIRCUIT TIMING
 *  Demonstrates how && and || affect execution time.
 ************************************************************/
#ifdef LOGIC_TIMING

int slow_function_A()
{
    volatile long long sum = 0;
    for (long long i = 0; i < 50000000LL; i++)
        sum += i;
    return sum > 0;
}

int slow_function_B()
{
    volatile long long sum = 0;
    for (long long i = 0; i < 20000000LL; i++)
        sum += i;
    return sum > 0;
}

void example_logic_timing()
{
    printf("===== EXAMPLE 2: LOGICAL OPERATOR TIMING =====\n");

    clock_t start, end;
    int ret;

    /************************************************************
     *  CASE 1 — (0 && slow_function_A())
     *  Left side is FALSE → short-circuit → A() never runs
     ************************************************************/
    start = clock();
    ret = (0 && slow_function_A());
    end = clock();
    printf("Case 1: 0 && slow_function_A(): result=%d, time=%.3f sec\n",
           ret, (double)(end - start) / CLOCKS_PER_SEC);

    /************************************************************
     *  CASE 2 — (1 && slow_function_A())
     *  Left side is TRUE → must evaluate right side
     ************************************************************/
    start = clock();
    ret = (1 && slow_function_A());
    end = clock();
    printf("Case 2: 1 && slow_function_A(): result=%d, time=%.3f sec\n",
           ret, (double)(end - start) / CLOCKS_PER_SEC);

    /************************************************************
     *  CASE 3 — (1 || slow_function_B())
     *  Left side is TRUE → short-circuit → B() never runs
     ************************************************************/
    start = clock();
    ret = (1 || slow_function_B());
    end = clock();
    printf("Case 3: 1 || slow_function_B(): result=%d, time=%.3f sec\n",
           ret, (double)(end - start) / CLOCKS_PER_SEC);

    /************************************************************
     *  CASE 4 — (0 || slow_function_B())
     *  Left side is FALSE → must evaluate right side
     ************************************************************/
    start = clock();
    ret = (0 || slow_function_B());
    end = clock();
    printf("Case 4: 0 || slow_function_B(): result=%d, time=%.3f sec\n",
           ret, (double)(end - start) / CLOCKS_PER_SEC);

    printf("\n");
}

#endif


/************************************************************
 *  EXAMPLE 3 — POINTER INCREMENT (p++, ++p, *p++)
 *  Shows pointer movement and evaluation order.
 ************************************************************/
#ifdef PTR_INCREMENT

void example_ptr_increment()
{
    printf("===== SHORT POINTER INCREMENT EXAMPLE =====\n");

    int arr[5] = {5, 10, 15, 20, 25};
    int *p = arr;

    printf("Start: %d\n", *p);

    // p++ : use current, then move pointer
    printf("*p++ = %d\n", *p++);
    printf("After p++ → %d\n", *p);

    // ++p : move pointer, then use
    printf("*++p = %d\n", *++p);

    // (*p)++ : increment value after using it
    printf("(*p)++ returns: %d\n", (*p)++);
    printf("Value after (*p)++: %d\n", *p);

    // ++(*p) : increment value before using it
    printf("++(*p) returns: %d\n", ++(*p));
    printf("Value after ++(*p): %d\n", *p);

    printf("\n");
}

#endif


/************************************************************
 *                  MAIN FUNCTION
 ************************************************************/
int main()
{
#ifdef FLOAT_COMPARE
    example_float_compare();
#endif

#ifdef LOGIC_TIMING
    example_logic_timing();
#endif

#ifdef PTR_INCREMENT
    example_ptr_increment();
#endif

#if !defined(FLOAT_COMPARE) && !defined(LOGIC_TIMING) && !defined(PTR_INCREMENT)
    printf("No example enabled. Use -DFLOAT_COMPARE, -DLOGIC_TIMING, or -DPTR_INCREMENT.\n");
#endif

    return 0;
}

