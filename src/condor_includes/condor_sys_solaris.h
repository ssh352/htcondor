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
#ifndef CONDOR_SYS_SOLARIS_H
#define CONDOR_SYS_SOLARIS_H

#define __EXTENSIONS__

#if defined(Solaris26)
#	define _LARGEFILE64_SOURCE
#endif

#include <sys/types.h>

#include <unistd.h>
/* These are all functions that unistd.h is supposed to prototype that
   for whatever reason, are not defined on Solaris. */
BEGIN_C_DECLS
int gethostname( char *, int );
long gethostid();
int getpagesize();
int getdtablesize();
int getpriority( int, id_t );
int setpriority( int, id_t, int );
int utimes( const char*, struct timeval* );
int getdomainname( char*, size_t );
END_C_DECLS

/* Want stdarg.h before stdio.h so we get GNU's va_list defined */
#include <stdarg.h>
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>

#define BSD_COMP
#include <sys/ioctl.h>
#undef BSD_COMP

#include <sys/stat.h>
#include <sys/statfs.h>

#if defined(_POSIX_C_SOURCE)
#	define HOLD_POSIX_C_SOURCE _POSIX_C_SOURCE
#	undef _POSIX_C_SOURCE
#endif
#include <sys/wait.h>
#if defined(HOLD_POSIX_C_SOURCE)
#	define _POSIX_C_SOURCE HOLD_POSIX_C_SOURCE 
#	undef HOLD_POSIX_C_SOURCE 
#endif

#include <sys/uio.h>
#include <sys/socket.h>

/****************************************
** Condor-specific system definitions
****************************************/
#define HAS_U_TYPES				1

#if defined( Solaris26) 
#	define HAS_64BIT_STRUCTS	1
#	define HAS_64BIT_SYSCALLS	1
#endif

#endif /* CONDOR_SYS_SOLARIS_H */
