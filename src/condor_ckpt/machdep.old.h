#include <setjmp.h>
extern "C" char *sbrk( int );
extern "C" char *brk( char * );

	// NULL gets redefined in <sys/param> on ULTRIX43 machines
#if defined(ULTRIX43) && defined(NULL)
#undef NULL
#endif
#include <sys/param.h>

#include <sys/vmparam.h>

/*
  Portability: A single method works on all the platforms we have tried
  so far, but this may not be true for all platforms.
*/
#if defined(ULTRIX42) || defined(ULTRIX43) || defined(SUNOS41)
#	define SETJMP _setjmp
#	define LONGJMP _longjmp
	extern "C" {
		int SETJMP( jmp_buf env );
		void LONGJMP( jmp_buf env, int retval );
	}
#else
	// Unknown platforms fall through to here, generating compile time error
#	error
#endif


int data_start_addr();
int data_end_addr();
int stack_start_addr();
int stack_end_addr();
void ExecuteOnTmpStk( void (*func)() );
