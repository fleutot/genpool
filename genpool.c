/*----------------------------------------------------------------------------
Copyright (c) 2016 Gauthier Östervall
----------------------------------------------------------------------------*/
#include <assert.h>
#include <malloc.h>

#include "genpool.h"
#include "genome/genome.h"

//******************************************************************************
// Module types
//******************************************************************************
struct genpool {
    genome_t **individuals;
    double mutation_rate;
    int nb_genomes;
    int fight_size;     //< Number of individuals fighting each other
    int nb_victors;
    int (*fitness)(genome_t *candidate1, genome_t *candidate2);
};

//******************************************************************************
// Module constants
//******************************************************************************

//******************************************************************************
// Module variables
//******************************************************************************

//******************************************************************************
// Function prototypes
//******************************************************************************

//******************************************************************************
// Function definitions
//******************************************************************************
//  ----------------------------------------------------------------------------
/// \brief  Create a new pool of individuals. These are randomly generated
/// according to the rules defined in genome.c.
/// \param  nb_individuals  The number of genomes in the new pool.
/// \return Pointer to the newly generated pool.
//  ----------------------------------------------------------------------------
struct genpool *genpool_create(const int nb_individuals,
                               const double mutation_rate,
                               const int fight_size,
                               const int nb_victors,
                               int (* const fitness)(genome_t const *candidate1,
                                                     genome_t const *candidate2)
    )
{
    assert(nb_victors * 2 == fight_size);

    struct genpool *pool = malloc(sizeof(struct genpool));
    if (!pool)
        return NULL;

    pool->nb_genomes = nb_individuals;
    pool->mutation_rate = mutation_rate;
    pool->fight_size = fight_size;
    pool->nb_victors = nb_victors;

    pool->individuals = malloc(nb_individuals * sizeof (*pool->individuals));
    if (!pool->individuals) {
        free(pool);
        return NULL;
    }

    for (int i = 0; i < pool->nb_genomes; i++) {
        pool->individuals[i] = genome_random_create();
        if (!pool->individuals[i]) {
            for (int j = 0; j < i; j++)
                genome_destroy(&pool->individuals[j]);
            free(pool->individuals);
            free(pool);
            return NULL;
        }
    }
    return pool;
}

void genpool_round_run(int (*fitness)(genome_t const *candidate1,
                                      genome_t const *candidate2))
{
}

void genpool_destroy(struct genpool **genpool)
{
    struct genpool *gp = *genpool;

    for (int i = 0; i < gp->nb_genomes; i++) {
        genome_destroy(&gp->individuals[i]);
    }
    free(gp->individuals);
    free(gp);
    *genpool = NULL;
}

//  ----------------------------------------------------------------------------
/// \brief  Set a mutation rate other than the default.
/// \param  new_mutation_rate   The new value.
//  ----------------------------------------------------------------------------
void genpool_mutation_rate_set(struct genpool *gp,
                               const double new_mutation_rate)
{
    gp->mutation_rate = new_mutation_rate;
}


//******************************************************************************
// Internal functions
//******************************************************************************
