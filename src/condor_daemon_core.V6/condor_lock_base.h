/***************************Copyright-DO-NOT-REMOVE-THIS-LINE**
  *
  * Condor Software Copyright Notice
  * Copyright (C) 1990-2004, Condor Team, Computer Sciences Department,
  * University of Wisconsin-Madison, WI.
  *
  * This source code is covered by the Condor Public License, which can
  * be found in the accompanying LICENSE.TXT file, or online at
  * www.condorproject.org.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * AND THE UNIVERSITY OF WISCONSIN-MADISON "AS IS" AND ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY, OF SATISFACTORY QUALITY, AND FITNESS
  * FOR A PARTICULAR PURPOSE OR USE ARE DISCLAIMED. THE COPYRIGHT
  * HOLDERS AND CONTRIBUTORS AND THE UNIVERSITY OF WISCONSIN-MADISON
  * MAKE NO MAKE NO REPRESENTATION THAT THE SOFTWARE, MODIFICATIONS,
  * ENHANCEMENTS OR DERIVATIVE WORKS THEREOF, WILL NOT INFRINGE ANY
  * PATENT, COPYRIGHT, TRADEMARK, TRADE SECRET OR OTHER PROPRIETARY
  * RIGHT.
  *
  ****************************Copyright-DO-NOT-REMOVE-THIS-LINE**/
#ifndef __CONDOR_LOCK_BASE__
#define __CONDOR_LOCK_BASE__

#include "condor_common.h"
#include "condor_timer_manager.h"
#include "condor_daemon_core.h"

// Lock events
typedef enum { LOCK_SRC_APP, LOCK_SRC_POLL } LockEventSrc;

/// Service Method that returns an int (C++ Version).
typedef int     (Service::*LockEvent)( LockEventSrc );

// Define a base "Condor lock" class
// Derived from "Serice" for the timer
class CondorLockBase : public Service
{
  public:
	CondorLockBase( void );
	~CondorLockBase( void );

	// Actually create the lock
	virtual int BuildLock( const char	*lock_url,
						   const char	*lock_name ) = 0;

	// Adjust the peeriods
	virtual int SetPeriods( time_t	poll_period,
							time_t	lock_hold_time ) = 0;

	// Basic lock operations
	virtual int AcquireLock( bool	background,
							 int	*callback_status = NULL ) = 0;
	virtual int ReleaseLock( int	*callback_status = NULL ) = 0;
	virtual int RefreshLock( int	*callback_status = NULL ) = 0;
	virtual bool HaveLock( void ) = 0;

  private:

};

#endif
