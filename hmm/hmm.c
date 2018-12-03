#include "hmm.h"

PoissonHMM*
NewPoissonHMM (size_t m,
			   scalar *init_lambda,
			   scalar *init_gamma,
			   scalar *init_delta,
			   size_t max_iter,
			   scalar tol)
{
	PoissonHMM *phmm = malloc (sizeof (PoissonHMM));
	
	size_t lambda_s 	= m * sizeof (*(phmm->lambda_));
	size_t gamma_s		= m * lambda_s;
	size_t delta_s		= lambda_s;

	phmm->m 			= m;

	phmm->init_lambda	= init_lambda; 
	phmm->init_gamma	= init_gamma;
	phmm->init_delta	= init_delta;

	phmm->max_iter		= max_iter;
	phmm->tol			= tol;
	phmm->n_iter		= 0L;

	phmm->lambda_	 	= malloc (lambda_s);
	phmm->gamma_		= malloc (gamma_s);
	phmm->delta_		= malloc (delta_s);

	memcpy (phmm->lambda_, init_lambda, lambda_s);
	memcpy (phmm->gamma_,  init_gamma,  gamma_s);
	memcpy (phmm->delta_,  init_delta,  delta_s);

	phmm->aic			= 0.0L;
	phmm->bic			= 0.0L;
	phmm->nll			= 0.0L;

	return phmm;
}

void
DeletePoissonHMM (PoissonHMM *phmm)
{
	free (phmm->lambda_);
	free (phmm->gamma_);
	free (phmm->delta_);
	free (phmm);
}

scalar
compute_aic(scalar nll, size_t m, size_t n)
{
	return 2.0L * (scalar) (nll + 2*m + m*m);
}

scalar
compute_bic(scalar nll, size_t m, size_t n)
{
	return 2.0L * nll + logl((scalar) n) * (scalar) (2*m + m*m);
}
