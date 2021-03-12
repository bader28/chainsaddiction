#/usr/bin/env python3

from setuptools import setup, Extension
from numpy.distutils.misc_util import get_numpy_include_dirs

setup(
        name            = 'chainsaddiction',
        version         = '0.1',
        description     = 'Discrete time, finit state space, stationary Hidden Markov Model.',
        install_requires = ['numpy>=1.15.0'],
        include_dirs    = get_numpy_include_dirs(),
        ext_modules     =   [
                                Extension(
                                    'chainsaddiction',
                                    sources     = [ 'hmm/stats.c',
                                                    'hmm/fwbw.c',
                                                    'hmm/em.c',
                                                    'hmm/hmm.c',
                                                    'hmm/hmm_module.c'],

                                include_dirs    = ['./include/'])
                            ]
      )

