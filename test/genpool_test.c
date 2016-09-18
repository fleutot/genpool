/*----------------------------------------------------------------------------
Copyright (c) 2013 Gauthier Östervall
----------------------------------------------------------------------------*/

// Module under test
#include "../genpool.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "../genome/genome.h"

//******************************************************************************
// Module macros
//******************************************************************************
#define TEST_START_PRINT()    do {              \
        printf("Running %s...", __func__);      \
        fflush(stdout);                         \
    } while (0)

#define TEST_END_PRINT()  do {                  \
        printf("OK.\n");                        \
    } while (0)

//******************************************************************************
// Module constants
//******************************************************************************

//******************************************************************************
// Module variables
//******************************************************************************

//******************************************************************************
// Function prototypes
//******************************************************************************
static void test_genpool_create(void);
static int fitness(genome_t const *candidate1, genome_t const *candidate2);

//******************************************************************************
// Function definitions
//******************************************************************************
int main(void)
{
    test_genpool_create();
    printf("All tests passed.\n");
}

//******************************************************************************
// Internal functions
//******************************************************************************
static void test_genpool_create(void)
{
    TEST_START_PRINT();

    struct genpool *gp = genpool_create(100, 0.1, 4, 2, fitness);

    // This test is not automatic. Run with e.g. valgrind to see if all memory
    // is freed.
    genpool_destroy(&gp);
    TEST_END_PRINT();
}

static int fitness(genome_t const *candidate1, genome_t const *candidate2)
{
    assert(candidate1);
    assert(candidate2);
    // This fitness function is stupid, just for testing.
    return candidate2 > candidate2;
}
