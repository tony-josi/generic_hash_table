/** 
 *  @file   legacy_macros.h
 *  @brief  Usual utility legacy file
 *
 *  This contains the Header file for usual utility legacy file
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#ifndef _LEGACY_MACROS_H
#define _LEGACY_MACROS_H

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS                    0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE                    (-1)
#endif

#define UNUSED(X)                       (void)X      /* To avoid gcc/g++ warnings */

#define RAND_GEN(N)                     (int)((double)rand() / ((double)RAND_MAX + 1) * N)

#endif /* _LEGACY_MACROS_H */
