# Microsoft Developer Studio Generated NMAKE File, Based on SkinDll.dsp
!IF "$(CFG)" == ""
CFG=SkinDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SkinDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SkinDll - Win32 Release" && "$(CFG)" != "SkinDll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkinDll.mak" CFG="SkinDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkinDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SkinDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkinDll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SkinDll.dll"


CLEAN :
	-@erase "$(INTDIR)\FormPart.obj"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\SkinDll.obj"
	-@erase "$(INTDIR)\SkinDll.pch"
	-@erase "$(INTDIR)\SkinDll.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SkinDll.dll"
	-@erase "$(OUTDIR)\SkinDll.exp"
	-@erase "$(OUTDIR)\SkinDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\SkinDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SkinDll.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SkinDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SkinDll.pdb" /machine:I386 /def:".\SkinDll.def" /out:"$(OUTDIR)\SkinDll.dll" /implib:"$(OUTDIR)\SkinDll.lib" 
DEF_FILE= \
	".\SkinDll.def"
LINK32_OBJS= \
	"$(INTDIR)\FormPart.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\SkinDll.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SkinDll.res"

"$(OUTDIR)\SkinDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SkinDll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SkinDll.ski" "$(OUTDIR)\SkinDll.bsc"


CLEAN :
	-@erase "$(INTDIR)\FormPart.obj"
	-@erase "$(INTDIR)\FormPart.sbr"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\Skin.sbr"
	-@erase "$(INTDIR)\SkinDll.obj"
	-@erase "$(INTDIR)\SkinDll.pch"
	-@erase "$(INTDIR)\SkinDll.res"
	-@erase "$(INTDIR)\SkinDll.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SkinDll.bsc"
	-@erase "$(OUTDIR)\SkinDll.exp"
	-@erase "$(OUTDIR)\SkinDll.ilk"
	-@erase "$(OUTDIR)\SkinDll.lib"
	-@erase "$(OUTDIR)\SkinDll.pdb"
	-@erase "$(OUTDIR)\SkinDll.ski"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SkinDll.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\SkinDll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SkinDll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\FormPart.sbr" \
	"$(INTDIR)\Skin.sbr" \
	"$(INTDIR)\SkinDll.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SkinDll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SkinDll.pdb" /debug /machine:I386 /def:".\SkinDll.def" /out:"$(OUTDIR)\SkinDll.ski" /implib:"$(OUTDIR)\SkinDll.lib" /pdbtype:sept 
DEF_FILE= \
	".\SkinDll.def"
LINK32_OBJS= \
	"$(INTDIR)\FormPart.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\SkinDll.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SkinDll.res"

"$(OUTDIR)\SkinDll.ski" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SkinDll.dep")
!INCLUDE "SkinDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "SkinDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SkinDll - Win32 Release" || "$(CFG)" == "SkinDll - Win32 Debug"
SOURCE=.\FormPart.cpp

!IF  "$(CFG)" == "SkinDll - Win32 Release"


"$(INTDIR)\FormPart.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ELSEIF  "$(CFG)" == "SkinDll - Win32 Debug"


"$(INTDIR)\FormPart.obj"	"$(INTDIR)\FormPart.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ENDIF 

SOURCE=.\Skin.cpp

!IF  "$(CFG)" == "SkinDll - Win32 Release"


"$(INTDIR)\Skin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ELSEIF  "$(CFG)" == "SkinDll - Win32 Debug"


"$(INTDIR)\Skin.obj"	"$(INTDIR)\Skin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ENDIF 

SOURCE=.\SkinDll.cpp

!IF  "$(CFG)" == "SkinDll - Win32 Release"


"$(INTDIR)\SkinDll.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ELSEIF  "$(CFG)" == "SkinDll - Win32 Debug"


"$(INTDIR)\SkinDll.obj"	"$(INTDIR)\SkinDll.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SkinDll.pch"


!ENDIF 

SOURCE=.\SkinDll.rc

"$(INTDIR)\SkinDll.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SkinDll - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\SkinDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SkinDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SkinDll - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SkinDll.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SkinDll.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

