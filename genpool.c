/*----------------------------------------------------------------------------
Copyright (c) 2016 Gauthier Östervall
----------------------------------------------------------------------------*/
#include <assert.h>
#include <malloc.h>

#include "genpool.h"
#include "genome/genome.h"
#include "genome/randomizer.h"

//******************************************************************************
// Module types
//******************************************************************************
struct genpool {
    genome_t **individuals;
    double mutation_rate;
    int nb_genomes;
    int fight_size;     //< Number of individuals fighting each other
    int nb_victors;
    int (*fitness)(genome_t const *candidate1, genome_t const *candidate2);

    // Array of randomly ordered indexes of individuals. Rerandomized at each
    // evolution step.
    int *fight_order;
    int nb_fights_per_round;
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
static void fight_order_permute(struct genpool *gp);
static int groups_fight(struct genpool *gp);
static void group_fight(genome_t *inds, int nb_cand);
static void group_kill_losers();
static void fight(genome_t *, genome_t *,int  score_i, int score_j);

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
    pool->fitness = fitness;

    pool->fight_order = malloc(nb_individuals * sizeof (*pool->fight_order));
    if (!pool->fight_order) {
        perror("malloc for fight_order");
        return NULL;
    }
    for (int i = 0; i < nb_individuals; ++i) {
        pool->fight_order[i] = i; // order does not matter, going to be permuted
    }

    pool->nb_fights_per_round = nb_individuals / fight_size;

    pool->individuals = malloc(nb_individuals * sizeof (*pool->individuals));
    if (!pool->individuals) {
        perror("malloc for individuals");
        free(pool->fight_order);
        free(pool);
        return NULL;
    }

    for (int i = 0; i < pool->nb_genomes; i++) {
        pool->individuals[i] = genome_random_create();
        if (!pool->individuals[i]) {
            for (int j = 0; j < i; j++)
                genome_destroy(&pool->individuals[j]);
            free(pool->fight_order);
            free(pool->individuals);
            free(pool);
            return NULL;
        }
    }
    return pool;
}

int genpool_round_run(struct genpool *gp)
{
    assert(gp);
    assert(gp->fight_order);

    fight_order_permute(gp);
    groups_fight(gp);

    return -1;
}

void genpool_destroy(struct genpool **genpool)
{
    struct genpool *gp = *genpool;

    for (int i = 0; i < gp->nb_genomes; i++) {
        genome_destroy(&gp->individuals[i]);
    }
    free(gp->fight_order);
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
static void fight_order_permute(struct genpool *gp)
{
    // Fisher-Yates shuffle
    for (int i = gp->nb_genomes - 1; i >= 0; --i) {
        int swap_pos = random_get(i + 1);
        int tmp = gp->fight_order[swap_pos];
        gp->fight_order[swap_pos] = gp->fight_order[i];
        gp->fight_order[i] = tmp;
    }
}

static int groups_fight(struct genpool *gp)
{
    for (int fight_n = 0, group_i = 0;
         fight_n < gp->nb_fights_per_round;
         ++fight_n, group_i += gp->fight_size
        ) {
        genome_t **losers = malloc(gp->nb_victors * sizeof (*losers));
        if (!losers) {
            perror("malloc for losers");
            return -1;
        }
        genome_t **winners = malloc(gp->nb_victors * sizeof (*winners));
        if (!winners) {
            perror("malloc for winners");
            free(losers);
            return -1;
        }

        group_fight(gp->individuals[gp->fight_order[group_i]], gp->fight_size);
                    //gp->individuals[gp->fight_order[group_i + 1]],
                    //gp->individuals[gp->fight_order[group_i + 2]],
                    //gp->individuals[gp->fight_order[group_i + 3]]);
        group_kill_losers();
        group_mate_winners();
    }
    return 0;
}

static void group_fight(genome_t *ind[], int nb_cand, int scores[])
{
    for (int i = 0; i < nb_cand; ++i)
        scores[i] = 0;

    for (int i = 0; i < nb_cand; ++i) {
        for (int j = i + 1; j < nb_cand; ++j) {
            int score_i = 0, score_j = 0;
            fight(ind[i], ind[j], score_i, score_j);
            scores[i] += score_i;
            scores[j] += score_j;
        }
    }
}

static void group_kill_losers()
{
}

static void group_mate_winners()
{
}
