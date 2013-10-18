/*----------------------------------------------------------------------------
Copyright (c) 2013 Gauthier Östervall
----------------------------------------------------------------------------*/
#include <assert.h>
#include <malloc.h>

#include "genpool.h"
#include "genome/genome.h"

//******************************************************************************
// Module constants
//******************************************************************************

//******************************************************************************
// Module variables
//******************************************************************************
static double mutation_rate = 0.05;
static int nb_genomes;
// Dynamically allocated array of pointers to genomes.
static genome_t **pool;

//******************************************************************************
// Function prototypes
//******************************************************************************

//******************************************************************************
// Function definitions
//******************************************************************************
//  ----------------------------------------------------------------------------
/// \brief  Create new individuals in a new pool. These are randomly generated
/// according to the rules defined in genome.c.
/// \param  nb_individuals  The number of genomes in the new pool.
//  ----------------------------------------------------------------------------
void genpool_create(const int nb_individuals)
{
    nb_genomes = nb_individuals;

    pool = malloc(nb_genomes * sizeof_genome);
    assert(pool);

    for (int i = 0; i < nb_genomes; i++) {
        pool[i] = genome_random_create();
    }
}

void genpool_destroy(void)
{
    for (int i = 0; i < nb_genomes; i++) {
        genome_destroy(&pool[i]);
    }
    free(pool);
}

//  ----------------------------------------------------------------------------
/// \brief  Set a mutation rate other than the default.
/// \param  new_mutation_rate   The new value.
//  ----------------------------------------------------------------------------
void genpool_mutation_rate_set(const double new_mutation_rate)
{
    mutation_rate = new_mutation_rate;
}


//******************************************************************************
// Internal functions
//******************************************************************************
