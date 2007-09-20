/***************************Copyright-DO-NOT-REMOVE-THIS-LINE**
  *
  * Condor Software Copyright Notice
  * Copyright (C) 1990-2006, Condor Team, Computer Sciences Department,
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

#ifndef _CONDOR_PERMS_H_
#define _CONDOR_PERMS_H_

#include "condor_common.h"

// IMPORTANT NOTE:  If you add a new enum value here, please add a new
// case to PermString() in condor_perms.c (in the util lib).
// Also make any necessary updates to DCpermissionHierarchy.
// Be sure to leave "LAST_PERM" last.  It's a place holder so 
// we can iterate through all the permission levels, and know when to 
// stop. 
/// enum for Daemon Core socket/command/signal permissions
typedef enum {
  /** Place holder, must be 0 */             FIRST_PERM = 0,
  /** Open to everyone */                    ALLOW = 0,
  /** Able to read data */                   READ = 1,
  /** Able to modify data (submit jobs) */   WRITE = 2,
  /** From the negotiator */                 NEGOTIATOR = 3,
  /** Not yet implemented, do NOT use */     IMMEDIATE_FAMILY = 4,
  /** Administrative cmds (on, off, etc) */  ADMINISTRATOR = 5,
  /** The machine owner (vacate) */          OWNER = 6,
  /** Changing config settings remotely */   CONFIG_PERM = 7,
  /** Daemon to daemon communcation     */   DAEMON = 8,
  /** SOAP interface (http PUT) */			 SOAP_PERM = 9,
  /** DEFAULT */                             DEFAULT_PERM = 10,
  /** CLIENT */                              CLIENT_PERM = 11,
  /** startd ad */                           ADVERTISE_STARTD_PERM = 12,
  /** schedd ad */                           ADVERTISE_SCHEDD_PERM = 13,
  /** master ad */                           ADVERTISE_MASTER_PERM = 14,
  /** Place holder, must be last */          LAST_PERM
} DCpermission;

// convenience macro for iterating through DCpermission values
#define NEXT_PERM(perm) ( (DCpermission) (((int)perm)+1) )

BEGIN_C_DECLS
	
	/** PermString() converts the given DCpermission into the
		human-readable string version of the name.
		@param perm The permission you want to convert
		@return The string version of it
	*/
const char* PermString( DCpermission perm );

END_C_DECLS

#if defined(__cplusplus)

class DCpermissionHierarchy {

private:
	DCpermission m_base_perm; // the specified permission level

		// [0] is base perm, [1] is implied by [0], ...
		// Terminated by an entry with value LAST_PERM.
	DCpermission m_implied_perms[LAST_PERM+1];

		// List of perms that imply base perm, not including base perm,
		// and not including things that indirectly imply base perm, such
		// as the things that imply the members of this list.
		// Example: for base perm WRITE, this list includes DAEMON and
		// ADMINISTRATOR.
		// Terminated by an entry with value LAST_PERM.
	DCpermission m_directly_implied_by_perms[LAST_PERM+1];

		// [0] is base perm, [1] is perm to param for if [0] is undefined, ...
		// The list ends with DEFAULT_PERM, followed by LAST_PERM.
	DCpermission m_config_perms[LAST_PERM+1];

public:

		// [0] is base perm, [1] is implied by [0], ...
		// Terminated by an entry with value LAST_PERM.
	DCpermission const * getImpliedPerms() const { return m_implied_perms; }

		// List of perms that imply base perm, not including base perm,
		// and not including things that indirectly imply base perm, such
		// as the things that imply the members of this list.
		// Example: for base perm WRITE, this list includes DAEMON and
		// ADMINISTRATOR.
		// Terminated by an entry with value LAST_PERM.
	DCpermission const * getPermsIAmDirectlyImpliedBy() const { return m_directly_implied_by_perms; }

		// [0] is base perm, [1] is perm to param for if [0] is undefined, ...
		// The list ends with DEFAULT_PERM, followed by LAST_PERM.
	DCpermission const * getConfigPerms() const { return m_config_perms; }

	DCpermissionHierarchy(DCpermission perm) {
		m_base_perm = perm;
		unsigned int i = 0;

		m_implied_perms[i++] = m_base_perm;

			// Add auth levels implied by specified perm
		bool done = false;
		while(!done) {
			switch( m_implied_perms[i-1] ) {
			case DAEMON:
			case ADMINISTRATOR:
				m_implied_perms[i++] = WRITE;
				break;
			case WRITE:
			case NEGOTIATOR:
			case CONFIG_PERM:
				m_implied_perms[i++] = READ;
				break;
			default:
					// end of hierarchy
				done = true;
				break;
			}
		}
		m_implied_perms[i] = LAST_PERM;

		i=0;
		switch(m_base_perm) {
		case READ:
			m_directly_implied_by_perms[i++] = WRITE;
			m_directly_implied_by_perms[i++] = NEGOTIATOR;
			m_directly_implied_by_perms[i++] = CONFIG_PERM;
			break;
		case WRITE:
			m_directly_implied_by_perms[i++] = ADMINISTRATOR;
			m_directly_implied_by_perms[i++] = DAEMON;
			break;
		default:
			break;
		}
		m_directly_implied_by_perms[i] = LAST_PERM;

		i=0;
		m_config_perms[i++] = m_base_perm;
		done = false;
		while( !done ) {
			switch(m_config_perms[i-1]) {
			case DAEMON:
				m_config_perms[i++] = WRITE;
				break;
			case ADVERTISE_STARTD_PERM:
			case ADVERTISE_SCHEDD_PERM:
			case ADVERTISE_MASTER_PERM:
				m_config_perms[i++] = DAEMON;
				break;
			default:
					// end of config hierarchy
				done = true;
				break;
			}
		}
		m_config_perms[i++] = DEFAULT_PERM;
		m_config_perms[i] = LAST_PERM;
	}
};

#endif


#endif /* _CONDOR_PERMS_H_ */

