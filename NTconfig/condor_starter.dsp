# Microsoft Developer Studio Project File - Name="condor_starter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=condor_starter - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "condor_starter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "condor_starter.mak" CFG="condor_starter - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "condor_starter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "condor_starter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "condor_starter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "..\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"..\Debug\condor_common.pch" /Yu"condor_common.h" /FD /TP $(CONDOR_INCLUDE) $(CONDOR_GSOAP_INCLUDE) $(CONDOR_GLOBUS_INCLUDE) $(CONDOR_KERB_INCLUDE) $(CONDOR_PCRE_INCLUDE) /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../Debug/condor_common.obj ..\Debug\condor_common_c.obj $(CONDOR_LIB) $(CONDOR_LIBPATH) $(CONDOR_GSOAP_LIB) $(CONDOR_GSOAP_LIBPATH) $(CONDOR_KERB_LIB) $(CONDOR_KERB_LIBPATH) $(CONDOR_PCRE_LIB) $(CONDOR_PCRE_LIBPATH) /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "condor_starter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "condor_starter___Win32_Release"
# PROP BASE Intermediate_Dir "condor_starter___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "..\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"..\src\condor_c++_util/condor_common.pch" /Yu"condor_common.h" /FD /TP /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /Z7 /O1 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"..\Release\condor_common.pch" /Yu"condor_common.h" /FD /TP $(CONDOR_INCLUDE) $(CONDOR_GSOAP_INCLUDE) $(CONDOR_GLOBUS_INCLUDE) $(CONDOR_KERB_INCLUDE) $(CONDOR_PCRE_INCLUDE) /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 ../Release/condor_common.obj ../Release/condor_common_c.obj $(CONDOR_LIB) $(CONDOR_LIBPATH) $(CONDOR_GSOAP_LIB) $(CONDOR_GSOAP_LIBPATH) $(CONDOR_KERB_LIB) $(CONDOR_KERB_LIBPATH) $(CONDOR_PCRE_LIB) $(CONDOR_PCRE_LIBPATH) /nologo /subsystem:console /pdb:none /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "condor_starter - Win32 Debug"
# Name "condor_starter - Win32 Release"
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\io_proxy.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\io_proxy.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\io_proxy_handler.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\io_proxy_handler.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\java_detect.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\java_detect.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\java_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\java_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_config.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_config.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_file.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_file.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_schedd.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_local_schedd.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_shadow.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\jic_shadow.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\job_info_communicator.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\job_info_communicator.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\local_user_log.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\local_user_log.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\mpi_comrade_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\mpi_comrade_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\mpi_master_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\mpi_master_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\NTsenders.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\os_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\os_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\script_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\script_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\soap_starterC.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\soap_starterH.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\soap_starterServer.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\soap_starterStub.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\soap_starterStub.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\starter.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\starter_class.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\starter_v61_main.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\stream_handler.C
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\stream_handler.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\tool_daemon_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\tool_daemon_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\user_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\user_proc.h
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\vanilla_proc.C
# End Source File
# Begin Source File

SOURCE=..\src\condor_starter.V6.1\vanilla_proc.h
# End Source File
# End Target
# End Project
