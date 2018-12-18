#include <stdio.h>
#include "fwbw.h"
#include "em.h"
#include "hmm.h"

int main(void)
{
	const size_t	m	=  3;
	const size_t    n	= 107;
	int success		=	0;	
	
	long	x[n]	= { 13, 14,  8, 10, 16, 26, 32, 27, 18, 32,
						36, 24, 22, 23, 22, 18, 25, 21, 21, 14,
						 8, 11, 14, 23, 18, 17, 19, 20, 22, 19,
						13, 26, 13, 14, 22, 24, 21, 22, 26, 21,
						23, 24, 27, 41, 31, 27, 35, 26, 28, 36,
						39, 21, 17, 22, 17, 19, 15, 34, 10, 15,
						22, 18, 15, 20, 15, 22, 19, 16, 30, 27,
						29, 23, 20, 16, 21, 21, 25, 16, 18, 15,
						18, 14, 10, 15,  8, 15,  6, 11,  8,  7,
						18, 16, 13, 12, 13, 20, 15, 16, 12, 18,
						15, 16, 13, 15, 16, 11, 11 };
	
	scalar	l[m]	=	{ 10L, 20L, 30L };
	scalar	g[m*m]	=	{ .8, .1, .1,
						  .1, .8, .1,
						  .1, .1, .8  };
	scalar	d[m]	=	{ 1./3., 1./3., 1./3. };
	

	PoissonHMM *phmm = NewPoissonHMM(m, l, g, d, 1000, 1e-5);
	success = poisson_expectation_maximization(x, n, phmm);

	phmm->aic = compute_aic (phmm->nll, phmm->m, n);
	phmm->bic = compute_bic (phmm->nll, phmm->m, n);

	if (success == 1)
	{
		printf("Lambda:\n");
		for (size_t i = 0; i < m; i++)
			printf("%Lf\t", phmm->lambda_[i]);

		printf("\n\nGamma:\n");
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				printf("%10.10Lf\t", phmm->gamma_[i*m+j]);
			}
			printf("\n");
		}

		printf("\nDelta:\n");
		for (size_t i = 0; i < m; i++)
			printf("%Lf\t", phmm->delta_[i]);
		
		printf("\n\nNLL:\t%Lf\n", phmm->nll);
		printf("AIC:\t%Lf\n", phmm->aic);
		printf("BIC:\t%Lf\n\n", phmm->bic);
		printf("n_iter:\t%zu\n", phmm->n_iter);
		
		DeletePoissonHMM(phmm);
		return 0;
	}
	else
	{
		puts("No convergence.");
		DeletePoissonHMM(phmm);
		return 125;
	}
}
