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

 

#ifndef _FILE_STATE_H
#define _FILE_STATE_H

#include "condor_common.h"
#include "condor_file.h"
#include "syscall_numbers.h"
#include "condor_syscall_mode.h"

class CondorFileInfo;
class CondorFilePointer;

/**
This class multiplexes number of UNIX file system calls.
The fd's used to index this table are "virtual file descriptors",
and could refer to real local fds, remote fds, ioservers, sockets,
or who knows what.  It only makes sense to use this table when
MappingFileDescriptors() is in effect.
<p>
This class does several things:
<dir> 
	<li> checks validity of fds  
	<li> multiplexes fds to file objects
	<li> keeps I/O summaries
	<li> manages checkpoint and restore
</dir>

This class does _not_:
<dir>
	<li> Decide whether mapping is in effect.
	     The system call stubs do that.
	<li> Implement read, write, ioctl, etc. for _any_ file.
	     Subclasses of CondorFile do that (condor_file_*.h)
	<li> Implement buffering.
	     A CondorFileBuffer wrapped around a file object does that.
	<li> Perform operations on names (i.e. stat()).
	     Those are handled transparently by the syscall switches.
</dir>

This file table is similar to an in-kernel file table.
It has several sub-structures:
<dir>
<li> CondorFile -- represents a truly-opened file
<li> CondorFilePointer -- represents a seek pointer
<li> CondorFileInfo -- records I/O summares for a file.
</dir>
<p>
Each integer file descriptor (fd) indexes a CondorFilePointer (CFP) in
the open file table.  Each CFP stores a current seek pointer and a 
pointer to a CondorFile (CF) and CondorFileInfo (CFI).
<p>
An open() causes a new CFP, CFI, and CF to be created.  The CFP is installed
in the file table, and the index is returned as a file descriptor.
open("words") would create this:
<pre>

   fd=3
     |
    CFP
    / \
   CF CFI

</pre>
Suppose that another open() is performed on the same file.  This requires
a separate seek pointer be managed, and a new fd be allocated, but the
same file must be manipulated.
<pre>

   fd=3  fd=4
     |     |
    CFP   CFP
     \ \ / /
      \ X /
      CF CFI

<pre>
Suppose that a dup is performed on fd 4.  A new fd must be allocated, but
it will share the same seek pointer as fd 4.
<pre>

   fd=3  fd=4 fd=5
     |     | /
    CFP   CFP
     \ \ / /
      \ X /
      CF CFI

</pre>
A close() on an fd causes the fd to be de-allocated.  It it is the last
reference to a CFP, that is also de-allocated.  If the last CFP to a CF
is de-allocated, the file is closed, and the CF de-allocated.  However,
the CFI is saved and kept in a list.  If the file is opened again, the
same CFI is used for keeping summaries.  CFIs are reported to the
shadow whenever a file is closed or the job terminates.
<p>
When in standalone checkpointing mode, the structure above is
maintained so that we can use the same object and caching sceme.
However, because stubs are not generated for remapping fds, we try
hard to keep the real fds synchronized with the virtual fds.
*/

class CondorFileTable {
public:

	/** Prepare the table for use */
	void	init();

	/** Write out any buffered data */
	void	flush();

	/** If flush mode is set to 1, all writes are immediately flushed */
	void	set_flush_mode( int on_off );

	/** Display debug info */
	void	dump();

	/** Close all outstanding files */
	void	close_all();

	/** If in LocalSyscalls, just perform a UNIX open.  If in
	    RemoteSyscalls, ask the shadow for the appropriate 
	    access method, and then use that method for the open. */
	int	open( const char *path, int flags, int mode );

	/** Pipe with UNIX semantics.
	    While a pipe is open, checkpointing is disabled.  */
	int	pipe(int fds[]);

	/** Socket with UNIX semantics.
	    While a socket is open, checkpointing is disabled. */
	int	socket( int domain, int type, int prototcol );
	
	/** Close this file with UNIX semantics */
	int	close( int fd );

	/** Read with UNIX semantics */
	ssize_t	read( int fd, void *data, size_t length );

	/** Write with UNIX semantics */
	ssize_t	write( int fd, const void *data, size_t length );

	/** Seek with UNIX semantics */
	off_t	lseek( int fd, off_t offset, int whence );

	/** Dup with UNIX semantics */
	int	dup( int old );

	/** Dup2 with UNIX semantics, even if dup2 is not supported
	    on this platform. */
	int	dup2( int old, int nfd );

	/** Similar to dup2, but will dup to any free fd >= search */
	int	search_dup2( int old, int search );

	/** Find the name of this file, and then chdir() to that
	    name.  This is not exactly UNIX semantics. */
	int	fchdir( int fd );

	/** Handle known fcntl values by modifying the table, or passing
	    the value to the appropriate file object.  Unknown fcntls
	    or those with non-integer third arguments fail with a 
	    warning message and EINVAL. */
	int	fcntl( int fd, int cmd, int arg );

	/** See comments for fcntl. */
	int	ioctl( int fd, int cmd, int arg );

	/** This poll() will only work on certain kinds of files.
	    An error is caused if you poll on an unsupported kind. */
	int	poll( struct pollfd fds[], int count, int timeout );

	/** This select() will only work on certain kinds of files.
	    An error is caused if you poll on an unsupported kind. */
	int	select( int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout );

	/** Truncate with UNIX semantics */
	int	ftruncate( int fd, size_t length );

	/** Flush any Condor-buffered data on this file, then
	    perform a UNIX fsync/fdsync/fdatasync as appropriate. */
	int	fsync( int fd );

	/** Return the max number of bytes to buffer per file */
	int	get_buffer_size();

	/** Return the approximate buffer block size to use */
	int	get_buffer_block_size();

	/** Perform a periodic checkpoint. */
	void	checkpoint();

	/** Suspend everything I know in preparation for a vacate and exit. */
	void	suspend();

	/** A checkpoint has resumed, so open everything up again. */
	void	resume();

	/** Returns the real fd corresponding to this virtual
	    fd.  If the mapping is non trivial, -1 is returned. */
	int	map_fd_hack( int fd );

	/** Returns true if this file can be accessed by local
	    syscalls.  Returns false otherwise. */
	int	local_access_hack( int fd );

private:

	int	install_special( char *kind, int real_fd );
	int	find_name(const char *name);
	int	find_empty();
	void	replace_file( CondorFile *oldfile, CondorFile *newfile );
	int	count_file_uses( CondorFile *f );
	int	count_pointer_uses( CondorFilePointer *f );
	CondorFileInfo	* find_info( char *name, char *kind );

	CondorFilePointer	**pointers;
	CondorFileInfo		*info_head;

	int	length;
	char	working_dir[_POSIX_PATH_MAX];
	int	resume_count;
	int	buffer_size;
	int	buffer_block_size;
	int	got_buffer_info;
	int	flush_mode;
};


/**
This is a pointer to the single global instance of the file
table.  The only user of this pointer should be the system call
switches, who need to send some syscalls to the open file table.
*/

extern CondorFileTable *FileTab;

#endif



