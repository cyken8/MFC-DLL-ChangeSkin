# Microsoft Developer Studio Generated NMAKE File, Based on ChangeSkin.dsp
!IF "$(CFG)" == ""
CFG=ChangeSkin - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ChangeSkin - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ChangeSkin - Win32 Release" && "$(CFG)" != "ChangeSkin - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ChangeSkin.mak" CFG="ChangeSkin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChangeSkin - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChangeSkin - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ChangeSkin.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg1.obj"
	-@erase "$(INTDIR)\ChangeSkin.obj"
	-@erase "$(INTDIR)\ChangeSkin.pch"
	-@erase "$(INTDIR)\ChangeSkin.res"
	-@erase "$(INTDIR)\ChangeSkinDlg.obj"
	-@erase "$(INTDIR)\CustomMenu.obj"
	-@erase "$(INTDIR)\FornPart.obj"
	-@erase "$(INTDIR)\SkinManage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ChangeSkin.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ChangeSkin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ChangeSkin.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ChangeSkin.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ChangeSkin.pdb" /machine:I386 /out:"$(OUTDIR)\ChangeSkin.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChangeSkin.obj" \
	"$(INTDIR)\ChangeSkinDlg.obj" \
	"$(INTDIR)\CustomMenu.obj" \
	"$(INTDIR)\FornPart.obj" \
	"$(INTDIR)\SkinManage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ChangeSkin.res" \
	"$(INTDIR)\AboutDlg1.obj"

"$(OUTDIR)\ChangeSkin.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ChangeSkin.exe" "$(OUTDIR)\ChangeSkin.bsc"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg1.obj"
	-@erase "$(INTDIR)\AboutDlg1.sbr"
	-@erase "$(INTDIR)\ChangeSkin.obj"
	-@erase "$(INTDIR)\ChangeSkin.pch"
	-@erase "$(INTDIR)\ChangeSkin.res"
	-@erase "$(INTDIR)\ChangeSkin.sbr"
	-@erase "$(INTDIR)\ChangeSkinDlg.obj"
	-@erase "$(INTDIR)\ChangeSkinDlg.sbr"
	-@erase "$(INTDIR)\CustomMenu.obj"
	-@erase "$(INTDIR)\CustomMenu.sbr"
	-@erase "$(INTDIR)\FornPart.obj"
	-@erase "$(INTDIR)\FornPart.sbr"
	-@erase "$(INTDIR)\SkinManage.obj"
	-@erase "$(INTDIR)\SkinManage.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ChangeSkin.bsc"
	-@erase "$(OUTDIR)\ChangeSkin.exe"
	-@erase "$(OUTDIR)\ChangeSkin.ilk"
	-@erase "$(OUTDIR)\ChangeSkin.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ChangeSkin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ChangeSkin.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ChangeSkin.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChangeSkin.sbr" \
	"$(INTDIR)\ChangeSkinDlg.sbr" \
	"$(INTDIR)\CustomMenu.sbr" \
	"$(INTDIR)\FornPart.sbr" \
	"$(INTDIR)\SkinManage.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\AboutDlg1.sbr"

"$(OUTDIR)\ChangeSkin.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ChangeSkin.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ChangeSkin.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChangeSkin.obj" \
	"$(INTDIR)\ChangeSkinDlg.obj" \
	"$(INTDIR)\CustomMenu.obj" \
	"$(INTDIR)\FornPart.obj" \
	"$(INTDIR)\SkinManage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ChangeSkin.res" \
	"$(INTDIR)\AboutDlg1.obj"

"$(OUTDIR)\ChangeSkin.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("ChangeSkin.dep")
!INCLUDE "ChangeSkin.dep"
!ELSE 
!MESSAGE Warning: cannot find "ChangeSkin.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ChangeSkin - Win32 Release" || "$(CFG)" == "ChangeSkin - Win32 Debug"
SOURCE=.\AboutDlg1.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\AboutDlg1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\AboutDlg1.obj"	"$(INTDIR)\AboutDlg1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\ChangeSkin.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\ChangeSkin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\ChangeSkin.obj"	"$(INTDIR)\ChangeSkin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\ChangeSkin.rc

"$(INTDIR)\ChangeSkin.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ChangeSkinDlg.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\ChangeSkinDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\ChangeSkinDlg.obj"	"$(INTDIR)\ChangeSkinDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\CustomMenu.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\CustomMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\CustomMenu.obj"	"$(INTDIR)\CustomMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\FornPart.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\FornPart.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\FornPart.obj"	"$(INTDIR)\FornPart.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\SkinManage.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"


"$(INTDIR)\SkinManage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"


"$(INTDIR)\SkinManage.obj"	"$(INTDIR)\SkinManage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ChangeSkin.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ChangeSkin - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ChangeSkin.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ChangeSkin.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ChangeSkin - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ChangeSkin.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ChangeSkin.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

