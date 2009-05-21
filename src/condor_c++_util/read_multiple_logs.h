/***************************************************************
 *
 * Copyright (C) 1990-2007, Condor Team, Computer Sciences Department,
 * University of Wisconsin-Madison, WI.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License.  You may
 * obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************/


#ifndef READ_MULTIPLE_LOGS_H
#define READ_MULTIPLE_LOGS_H

// This class allows reading more than one user log file, as if they
// were merged into one big log file, sorted by event time.  It returns
// ULogEvent objects just like the ReadUserLog class.  It tries to 
// return the events sorted by time, but cannot distinguish between 
// events in different files that occurred in the same second. 

#include "condor_common.h"
#include "read_user_log.h"
#include "MyString.h"
#include "string_list.h"
#include "HashTable.h"
#include "condor_id.h"
#include "CondorError.h"
#include "stat_struct.h"
#include <iosfwd>
#include <string>

// This allows us to gradually commit the code before it's fully
// working without making a branch.  Only commit with this false
// until the lazy log file code is fully working.  wenger 2008-12-19.
#define LAZY_LOG_FILES 0

class MultiLogFiles
{
public:
	    /** Gets the userlog files used by a dag
		    on success, the return value will be ""
		    on failure, it will be an appropriate error message
	    */
    static MyString getJobLogsFromSubmitFiles(const MyString &strDagFileName,
			const MyString &jobKeyword, const MyString &dirKeyword,
			StringList &listLogFilenames);

		/** Gets values from a file, where the file contains lines of
			the form
				<keyword> <value>
			with arbitrary whitespace between the two tokens.
			@param fileName: the name of the file to parse
			@param keyword: the keyword string
			@param values: the list of values found
			@param skipTokens: number of tokens to skip between keyword
				and value
			@return "" if okay, an error message otherwise
		*/
	static MyString getValuesFromFile(const MyString &fileName,
			const MyString &keyword, StringList &values, int skipTokens = 0);

	    /** Gets the log file from a Condor submit file.
		    on success, the return value will be the log file name
		    on failure, it will be ""
		 */
    static MyString loadLogFileNameFromSubFile(const MyString &strSubFilename,
			const MyString &directory);

		/** Makes the given filename an absolute path
			@param the name of the file (input/output)
			@param a CondorError object to hold any error information
			@return true if successful, false if failed
		 */
	static bool makePathAbsolute(MyString filename, CondorError &errstack);

#ifdef HAVE_EXT_CLASSADS
	    /** Gets the log files from a Stork submit file.
		 * @param The submit file name.
		 * @param The directory containing the submit file.
		 * @param Output string list of log file names.
		 * @return "" if okay, or else an error message.
		 */
    static MyString loadLogFileNamesFromStorkSubFile(
		const MyString &strSubFilename,
		const MyString &directory,
		StringList &listLogFilenames);
#endif

		/** Gets the number of job procs queued by a submit file
			@param The submit file name
			@param The submit file directory
			@param A MyString to receive any error message
			@return -1 if an error, otherwise the number of job procs
				queued by the submit file
		*/
	static int getQueueCountFromSubmitFile(const MyString &strSubFilename,
	            const MyString &directory, MyString &errorMsg);

	    /** Truncates the given log files to zero length (as opposed to
			deleting them, which breaks things if the log file is a link).
		 */
	static void TruncateLogs(StringList &logFileNames);

#if LAZY_LOG_FILES
		/** Initializes the given file -- creates it if it doesn't exist,
			possibly truncates it if it does.
			@param the name of the file to create or truncate
			@param whether to truncate the file
			@param a CondorError object to hold any error information
			@return true if successful, false if failed
		 */
	static bool InitializeFile(const char *filename, bool truncate,
				CondorError &errstack);
#endif // LAZY_LOG_FILES

		/** Determines whether the given set of log files have any
			members that are on NFS.
			@param The list of log files
			@param Whether having a log file on NFS is a fatal error (as
				opposed to a warning)
			@return true iff at least one log file is on NFS and nfsIsError
				is true
		*/
	static bool logFilesOnNFS(StringList&, bool nfsIsError);

		/** Determines whether the given log file is on NFS.
			@param The log file name
			@param Whether having a log file on NFS is a fatal error (as
				opposed to a warning)
			@return true iff at least the log file is on NFS and nfsIsError
				is true
		*/
	static bool logFileOnNFS(const char *fileName, bool nfsIsError);

		/** Reads in the specified file, breaks it into lines, and
			combines the lines into "logical" lines (joins continued
			lines).
			@param The filename
			@param The StringList to receive the logical lines
			@return "" if okay, error message otherwise
		*/
	static MyString fileNameToLogicalLines(const MyString &filename,
				StringList &logicalLines);

private:
	    /** Read the entire contents of the given file into a MyString.
		 * @param The name of the file.
		 * @return The contents of the file.
		 */
    static MyString readFileToString(const MyString &strFilename);

		/**
		 * Get the given parameter if it is defined in the given submit file
		 * line.
		 * @param The submit file line.
		 * @param The name of the parameter to get.
		 * @return The parameter value defined in that line, or "" if the
		 *   parameter is not defined.
		 */
	static MyString getParamFromSubmitLine(MyString &submitLine,
			const char *paramName);

		/**
		 * Combine input ("physical") lines that end with the given
		 * continuation character into "logical" lines.
		 * @param Input string list of "physical" lines.
		 * @param Continuation character.
		 * @param Filename (for error messages).
		 * @param Output string list of "logical" lines.
		 * @return "" if okay, or else an error message.
		 */
	static MyString CombineLines(StringList &listIn, char continuation,
			const MyString &filename, StringList &listOut);

#ifdef HAVE_EXT_CLASSADS
		/**
		 * Skip whitespace in a std::string buffer.  This is a helper function
		 * for loadLogFileNamesFromStorkSubFile().  When the new ClassAds
		 * parser can skip whitespace on it's own, this function can be
		 * removed.
		 * @param buffer name
		 * @param input/output offset into buffer
		 * @return void
		 */
	static void skip_whitespace(std::string const &s,int &offset);

		/**
		 * Read a file into a std::string helper function for
		 * loadLogFileNamesFromStorkSubFile().
		 * @param Filename to read.
		 * @param output buffer
		 * @return "" if okay, or else an error message.
		 */
	static MyString readFile(char const *filename,std::string& buf);
#endif

};

class ReadMultipleUserLogs
{
public:
	ReadMultipleUserLogs();
	explicit ReadMultipleUserLogs(StringList &listLogFileNames);

	~ReadMultipleUserLogs();

	    /** Sets the list of log files to monitor; throws away any
		    previous list of files to monitor.
		 */
    bool initialize(StringList &listLogFileNames);

    	/** Returns the "next" event from any log file.  The event pointer 
        	is set to point to a newly instatiated ULogEvent object.
    	*/
    ULogEventOutcome readEvent (ULogEvent * & event);

	    /** Returns true iff any of the logs we're monitoring grew since
		    the last time this method was called.
		 */
	bool detectLogGrowth();

		/** Returns the number of user logs that have been successfully
		 	initialized.
		 */
	int getInitializedLogCount() const;

#if LAZY_LOG_FILES
		/** Monitor the given log file
			@param the log file to monitor
			@param whether to truncate the log file if this is the
				first time we're seeing it
			@param a CondorError object to hold any error information
			@return true if successful, false if failed
		*/
	bool monitorLogFile(MyString logfile, bool truncateIfFirst,
				CondorError &errstack);

		/** Unmonitor the given log file
			@param the log file to unmonitor
			@param a CondorError object to hold any error information
			@return true if successful, false if failed
		*/
	bool unmonitorLogFile(MyString logfile, CondorError &errstack);

		/** Print information about all LogMonitor objects.
			@param the stream to print to.
		*/
	void printAllLogMonitors( FILE *stream );

		/** Print information about active LogMonitor objects.
			@param the stream to print to.
		*/
	void printActiveLogMonitors( FILE *stream );
#endif // LAZY_LOG_FILES

protected:
	friend class CheckEvents;

	static unsigned int hashFuncJobID(const CondorID &key);

private:
	void cleanup();

//TEMP -- get rid of LogFileEntry stuff when lazy code works
	struct LogFileEntry
	{
		bool		isInitialized;
		bool		isValid;
		bool		haveReadEvent;
		MyString	strFilename;
		ReadUserLog	readUserLog;
		ULogEvent *	pLastLogEvent;
		off_t		logSize;
	};

	int				iLogFileCount;
	LogFileEntry *	pLogFileEntries;

#if !LAZY_LOG_FILES
		// Holds CondorID->log mappings to check for duplicate logs.
		// Note: we only map the first CondorID we see for a log, so
		// there is only one entry per log.
	HashTable<CondorID, LogFileEntry *>	logHash;
#endif // LAZY_LOG_FILES

#if LAZY_LOG_FILES
	struct LogFileMonitor {
		LogFileMonitor( const MyString &file ) : logFile(file), refCount(0),
					readUserLog(NULL), state(NULL), lastLogEvent(NULL) {}

		~LogFileMonitor() {
			delete readUserLog;
			readUserLog = NULL;

			if ( state ) {
				ReadUserLog::UninitFileState( *state );
			}
			delete state;
			state = NULL;

			delete lastLogEvent;
			lastLogEvent = NULL;
		}

			// The file name corresponding to this object; if the same
			// actual log file is registered via multiple paths, this
			// is the first path used to register it.
		MyString	logFile;

			// Reference count -- how many net calls to monitor this log?
		int			refCount;

			// The actual log reader object -- may be null
		ReadUserLog	*readUserLog;

			// Log reader state -- used to pick up where we left off if
			// we close and re-open the same log file.
		ReadUserLog::FileState	*state;

			// The last event we read from this log.
		ULogEvent	*lastLogEvent;

		// more stuff here?
	};

	HashTable<StatStructInode, LogFileMonitor *>	allLogFiles;

	HashTable<StatStructInode, LogFileMonitor *>	activeLogFiles;
#endif // LAZY_LOG_FILES

	// For instantiation in programs that use this class.
#define MULTI_LOG_HASH_INSTANCE template class \
		HashTable<CondorID, \
		ReadMultipleUserLogs::LogFileEntry *>


	    /** Goes through the list of logs and tries to initialize (open
		    the file of) any that aren't initialized yet.
			Returns true iff it successfully initialized *any* previously-
			uninitialized log.
		 */
	bool initializeUninitializedLogs();

		/** Returns true iff the given log grew since the last time
		    we called this method on it.
		 */
	static bool LogGrew(LogFileEntry &log);

#if LAZY_LOG_FILES
		/** Returns true iff the given log grew since the last time
		    we called this method on it.
		    @param The LogFileMonitor object to test.
			@param The filename this corresponds to (for error messages
				only).
		    @return True iff the log grew.

		 */
	static bool LogGrew( LogFileMonitor *monitor );
#endif // LAZY_LOG_FILES

#if !LAZY_LOG_FILES
		/**
		 * Read an event from a log, including checking whether this log
		 * is actually a duplicate of another log.  Note that if this *is*
		 * a duplicate log, the method will return ULOG_NO_EVENT, even
		 * though an event was read.
		 * @param The log to read from.
		 * @return The outcome of trying to read an event.
		 */
	ULogEventOutcome readEventFromLog(LogFileEntry &log);
#endif // !LAZY_LOG_FILES

#if LAZY_LOG_FILES
		/**
		 * Read an event from a log monitor.
		 * @param The log monitor to read from.
		 * @return The outcome of trying to read an event.
		 */
	ULogEventOutcome readEventFromLog( LogFileMonitor *monitor );
#endif // LAZY_LOG_FILES

#if !LAZY_LOG_FILES
		/**
		 * Determine whether a log object exists that is a logical duplicate
		 * of the one given (in other words, points to the same log file).
		 * We're checking this in case we have submit files that point to
		 * the same log file with different paths -- if submit files have
		 * the same path to the log file, we already recognize that it's
		 * a single log.
		 * @param The event we just read.
		 * @param The log object from which we read that event.
		 * @return True iff a duplicate log exists.
		 */
	bool DuplicateLogExists(ULogEvent *event, LogFileEntry *log);
#endif // !LAZY_LOG_FILES

#if LAZY_LOG_FILES
	void printLogMonitors(FILE *stream,
				HashTable<StatStructInode, LogFileMonitor *> logTable);
#endif // LAZY_LOG_FILES

};

#endif
