/***************************Copyright-DO-NOT-REMOVE-THIS-LINE**
 * CONDOR Copyright Notice
 *
 * See LICENSE.TXT for additional notices and disclaimers.
 *
 * Copyright (c)1990-1998 CONDOR Team, Computer Sciences Department, 
 * University of Wisconsin-Madison, Madison, WI.  All Rights Reserved.  
 * No use of the CONDOR Software Program Source Code is authorized 
 * without the express consent of the CONDOR Team.  For more information 
 * contact: CONDOR Team, Attention: Professor Miron Livny, 
 * 7367 Computer Sciences, 1210 W. Dayton St., Madison, WI 53706-1685, 
 * (608) 262-0856 or miron@cs.wisc.edu.
 *
 * U.S. Government Rights Restrictions: Use, duplication, or disclosure 
 * by the U.S. Government is subject to restrictions as set forth in 
 * subparagraph (c)(1)(ii) of The Rights in Technical Data and Computer 
 * Software clause at DFARS 252.227-7013 or subparagraphs (c)(1) and 
 * (2) of Commercial Computer Software-Restricted Rights at 48 CFR 
 * 52.227-19, as applicable, CONDOR Team, Attention: Professor Miron 
 * Livny, 7367 Computer Sciences, 1210 W. Dayton St., Madison, 
 * WI 53706-1685, (608) 262-0856 or miron@cs.wisc.edu.
****************************Copyright-DO-NOT-REMOVE-THIS-LINE**/
#ifndef CONDOR_SYS_IRIX_H
#define CONDOR_SYS_IRIX_H


#if defined(IRIX65)

/* On IRIX 6.5 the header files are just generally wacky.  So lets
   define what we want.  NOTE: things like _ABIAPI only work in #if
   statments! */

/* The following should set things like _ABIAPI to something that
we want, and it gives us a lot of the 64 bit stuff that was lacking
before */

#define _SGI_SOURCE 1
#define _ABI_SOURCE 1

/* We also want LARGEFILE support so define: */

#define _LARGEFILE64_SOURCE 1

/* We also can do without _POSIX_SOURCE on IRIX */
#if defined(_POSIX_SOURCE)
#	undef _POSIX_SOURCE
#endif

#endif

//#define _XOPEN_SOURCE 1
//#define _XOPEN_SOURCE_EXTENDED 1

#define _BSD_COMPAT 1

/* While we want _BSD_TYPES defined, we can't just define it ourself,
   since we include rpc/types.h later, and that defines _BSD_TYPES
   itself without any checks.  So, instead, we'll just include
   <rpc/types.h> as our first header, to make sure we get BSD_TYPES.
   This also includes <sys/types.h>, so we don't need to include that
   ourselves anymore. */

#include <rpc/types.h>

#if defined(IRIX65)
/* Now time for some sanity checks... */
#if !(_ABIAPI)
#	error "STOP:  Check out why _ABIAPI is FALSE!"
#endif

#endif


#if defined(IRIX65)
#	undef _ABIAPI
#	include <sys/resource.h>
#	define _ABIAPI 1
#endif /* defined (IRIX65) */

/* For strdup to get prototyped, we need to still have the XOPEN stuff 
   defined when we include string.h */ // Need to check this
#include <string.h>

/******************************
** unistd.h
******************************/
//#define __vfork fork

/* if _BSD_COMPAT is defined, then getpgrp will get funny arguments from 
   <unistd.h> and that will break receivers.c - Ballard 10/99
   ( and note how this is done! )*/
#if _BSD_COMPAT
#	define _save_BSD_COMPAT 1
#else
#	define _save_BSD_COMPAT 0
#endif
#undef _BSD_COMPAT

#include <unistd.h>
//#undef __vfork

#define _BSD_COMPAT _save_BSD_COMPAT
#undef _save_BSD_COMPAT

/* Some prototypes we should have but did not pick up from unistd.h */
BEGIN_C_DECLS
extern int getpagesize(void);
END_C_DECLS

/* Want stdarg.h before stdio.h so we get GNU's va_list defined */
#include <stdarg.h>

/******************************
** stdio.h
******************************/
#include <stdio.h>
/* These aren't defined if _POSIX_SOURCE is defined. */
FILE *popen (const char *command, const char *type);
int pclose(FILE *stream);


/******************************
** signal.h
******************************/
#define SIGTRAP 5
#define SIGBUS 10
#define SIGIO 22
#define _save_NO_ANSIMODE _NO_ANSIMODE
#undef _NO_ANSIMODE
#define _NO_ANSIMODE 1
//#undef _SGIAPI
//#define _SGIAPI 1
#include <signal.h>
#include <sys/signal.h>
/* We also want _NO_ANSIMODE and _SGIAPI defined to 1 for sys/wait.h,
   math.h and limits.h */  
#include <sys/wait.h>    
/* Some versions of IRIX don't define WCOREFLG, but we need it */
#if !defined( WCOREFLG )
#  define WCOREFLG 0200
#endif

#include <math.h>
#include <limits.h>
#undef _NO_ANSIMODE
#define _NO_ANSIMODE _save_NO_ANSIMODE
#undef _save_NO_ANSIMODE
//#undef _SGIAPI
//#define _SGIAPI _save_SGIAPI
//#undef _save_SGIAPI

/******************************
** sys/socket.h
******************************/
/* On Irix 6.5, they actually implement socket() in sys/socket.h by
   having it call some other xpg socket thing, if you're using XOPEN4.
   We can't have that, or file_state.C gets really confused.  So, if
   we're building the ckpt_lib, turn off XOPEN4.
	!!!THIS IS BAAAAD. We are just hacking the _NO_XOPEN4 since we
	know what the value is. This should be fixed to correctly hold
	onto the value and restore it afterward.

* #if defined(IRIX65) && defined(IN_CKPT_LIB)
* #undef _NO_XOPEN4
* #define _NO_XOPEN4 1
* #include <sys/socket.h>
* #undef _NO_XOPEN4
* #define _NO_XOPEN4 0
* #endif

	-- NOTE.  You cannot do the following:

	# define _save_foo foo
	# define foo 1
	....

	#define foo _save_foo

*/



#include <sys/select.h>

/* A bunch of sanity checks. */

#if !(_LFAPI)
#	error "STOP:  Find out why _LFAPI is false!!!"
#endif
#if !(_SGI_SOURCE)
#	error "STOP:  Find out why _SGIAPI is false!!!"
#endif

#if !(_NO_POSIX)
#	error "STOP:  Find out why _NO_POSIX is false!!!"
#endif

#if (!_NO_XOPEN4)
#	error "STOP:  Find out why _NO_XOPEN4 is false!!!"
#endif

#if (!_NO_XOPEN5)
#	error "STOP:  Find out why _NO_XOPEN5 is false!!!"
#endif

#if !(_SGIAPI)
#	error "STOP:  Find out why _SGIAPI is false!!!"
#endif

#if defined(_POSIX_SOURCE)
#	error "STOP:  why is _POSIX_SOURCE defined?"
#endif

#if defined(_POSIX_C_SOURCE)
#	error "STOP:  why is _POSIX_C_SOURCE defined?"
#endif


#undef _SGIAPI
#define _SGIAPI 1

/* Need these to get statfs and friends defined */
#include <sys/stat.h>
#include <sys/statfs.h>

#if defined(IRIX62)
/* Needed to get TIOCNOTTY defined - not needed after IRIX62 */
#include <sys/ttold.h>
#endif

/****************************************
** Condor-specific system definitions
****************************************/

#if defined(IRIX65)
#	include <sys/file.h>
#	define HAS_64BIT_SYSCALLS 1
#endif

#define HAS_U_TYPES			1
#define SIGSET_CONST			const
#define SYNC_RETURNS_VOID		1
#define NO_VOID_SIGNAL_RETURN		1
#define HAS_64BIT_STRUCTS		1

typedef void * MMAP_T;

#endif /* CONDOR_SYS_IRIX_H */
