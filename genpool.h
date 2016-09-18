/*----------------------------------------------------------------------------
Copyright (c) 2016 Gauthier Östervall
----------------------------------------------------------------------------*/
#ifndef GENPOOL_H_INCLUDED
#define GENPOOL_H_INCLUDED

#include <stdbool.h>
#include "genome/genome.h"

struct genpool;

/* Good default for init:
 * nb_individuals: 1000
 * mutation_rate: 0.001
 * fight_size: 4. Note: only 4 is supported so far.
 * nb_victors: 2. Note: only nb_victors that is half of fight_size.
 */
struct genpool *genpool_create(const int nb_individuals,
                               const double mutation_rate,
                               const int fight_size,
                               const int nb_victors,
                               int (* const fitness)(genome_t const *candidate1,
                                                     genome_t const *candidate2)
    );

void genpool_mutation_rate_set(struct genpool *gp,
                               const double new_mutation_rate);

void genpool_destroy(struct genpool **gp);

void genpool_round_run(int (*fitness)(genome_t const *candidate1,
                                      genome_t const *candidate2));

#endif // GENPOOL_H_INCLUDED
