#ifndef FORTRANIZE_H
#define FORTRANIZE_H

/* We have to munge identifiers so that they are compatible
   with the symbols spit out by the Fortran compiler. 
   Unfortunately, there is no standard for this: some
   compilers use all-caps, some use all lower-case,
   some append an underscore...  We have built in some
   rules to handle the systems we are familiar with.

   Any identifier that will be linked against a Fortran
   symbol (e.g. a Fortran subroutine name), must be
   wrapped in the FORTRANIZE(x,X) macro, where x is the
   lower-case version of the identifier and X is all-caps. */

#if defined(CRAY) || defined(_UNICOS) || defined(_CRAYMPP)
#define FORTRANIZE(x,X) X /* all upper-case on the Cray */

#elif defined(IBM6000) || defined(_AIX)
#define FORTRANIZE(x,X) x  /* all lower-case on RS/6000 */

#elif defined(__hpux)
#define FORTRANIZE(x,X) x  /* all lower-case on HP-UX */

#else
#define FORTRANIZE(x,X) x##_  /* use all lower-case with underscore
                                 by default */

#endif

/* Passing strings to C programs from Fortran is a pain.  We can simplify
   matters by requiring that the caller pass the length of the string,
   but things are still bad because Cray Fortran passes an "_fcd"
   (Fortran character descriptor) structure instead of a char * when
   a string is passed to a subroutine.   Sigh.  */

#if defined(CRAY) || defined(_UNICOS) || defined(_CRAYMPP)
#include <fortran.h>
typedef _fcd fortran_string;

#define fcp2ccp(fs) _fcdtocp(fs)

#else
typedef char *fortran_string;
#define fcp2ccp(fs) (fs)

#endif

#endif /* FORTRANIZE_H */
