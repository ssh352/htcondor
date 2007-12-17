##**************************************************************
##
## Copyright (C) 1990-2007, Condor Team, Computer Sciences Department,
## University of Wisconsin-Madison, WI.
## 
## Licensed under the Apache License, Version 2.0 (the "License"); you
## may not use this file except in compliance with the License.  You may
## obtain a copy of the License at
## 
##    http://www.apache.org/licenses/LICENSE-2.0
## 
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
##**************************************************************

##
## convert_config_to_win32.awk
##
## Todd Tannenbaum <tannenba@cs.wisc.edu>, 10/06
##

# This is an awk script to modify condor_config.generic into a form that 
# works with the InstallShield Windows installer.  The packager on Win32
# will pipe condor_config.generic through this awk script and save it as
# condor_config.orig, which is what the InstallShield script expects to 
# modify after unbundling.

BEGIN {
	FS = "="
}

# Make it so we can fill in the VM_GAHP_SERVER option if we choose to in the
# installer. This is done before the .exe append bellow, because that match 
# seems to block any other matches for that line.
/^#VM_GAHP_SERVER/ {
	print "#VM_GAHP_SERVER = $(BIN)/condor_vm-gahp.exe"
	print "VM_GAHP_SERVER = "
	next
}

# Add a .exe to the end of all condor daemon names
/BIN)\/condor_/ {
	printf "%s.exe\n",$0
	next
}

# Email Settings
# Use condor_mail.exe for MAIL, and put in a stub for SMTP_SERVER
/^MAIL/ {
	printf "MAIL = $(BIN)/condor_mail.exe\n\n"
	printf "## For Condor on Win32 we need to specify an SMTP server so\n"
	printf "## that Condor is able to send email.\n"
	printf "SMTP_SERVER =\n\n"
	next
}
/^SMTP_SERVER/ {
	next
}

# Specify $(FULL_HOSTNAME) as the sample commented-out entry for
# FILESYSTEM_DOMAIN and UID_DOMAIN, as this is what the installer expects.
/^UID_DOMAIN/ || /^FILESYSTEM_DOMAIN/ {
	printf "#%s= $(FULL_HOSTNAME)\n", $1
	next
}

# Have $(SBIN) point to $(BIN)
/^SBIN/ {
	printf "%s= $(BIN)\n", $1
	next
}

# QUEUE_SUPER_USERS should be condor and SYSTEM, not root! :)
/^QUEUE_SUPER_USERS/ {
	printf "%s= condor, SYSTEM\n", $1
	next
}

# JOB_RENICE_INCREMENT must be 10 or load average will be messed up
# Be careful, it may be commented out in condor_config.generic.
/^.*JOB_RENICE_INCREMENT/ {
	printf "JOB_RENICE_INCREMENT = 10\n"
	next
}

# Clean out the initial guess of /usr/bin/java for JAVA... ;)
# Note the space after JAVA below, so we do not change other JAVA settings.
/^JAVA / {
	printf "JAVA =\n"
	next
}

# Win32 has a path separator of ';', while on Unix it is ':'
/^JAVA_CLASSPATH_SEPARATOR/ {
	printf "%s= ;\n", $1
	next
}

# There's no reasonable default place to put log files for
# daemons that run as a user (on Unix we use /tmp). Use NUL.
/(^C_GAHP_LOG)|(^C_GAHP_LOCK)|(^C_GAHP_WORKER_THREAD_LOG)|(^C_GAHP_WORKER_THREAD_LOCK)|(^VM_GAHP_LOG)/ {
	printf "%s = NUL\n", $1
	next
}

# PROCD_ADDRESS needs to refer to a valid name for a Windows named
# pipe
/^PROCD_ADDRESS/ {
	print "PROCD_ADDRESS = \\\\.\\pipe\\condor_procd_pipe"
	next
}

# Make it so we can fill in the VM GAHP options if we choose to in the
# installer. 
/^#VM_GAHP_CONFIG/ {
	print "#VM_GAHP_CONFIG = $(RELEASE_DIR)/condor_vmgahp_config.vmware"
	print "VM_GAHP_CONFIG ="
	next
}
/^#VM_TYPE/ {
	print "#VM_TYPE = vmware"
	print "VM_TYPE ="
	next
}

# If we made it here, print out the line unchanged
{print $0}

