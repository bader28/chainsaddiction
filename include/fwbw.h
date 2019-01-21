#ifndef FWBW_H
#define FWBW_H

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include "stats.h"
#include "scalar.h"
#include "hmm.h"

int PoisHmm_log_forward_backward(
        const long *restrict x,
        const size_t n,
        const size_t m,
        PoisParams *restrict params,
        scalar *restrict alpha,
        scalar *restrict beta,
        scalar *restrict pois_pr);

#endif  /* FWBW_H */
