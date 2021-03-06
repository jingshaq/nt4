##############################################################################
#
#  (c) Copyright Microsoft Corp. 1992-1994 All Rights Reserved
#
#  File:
#
#    makefile - makefile for spoly.exe
#
#  Purpose:
#
#    Builds the OLE 2.0 sample IDispatch server, spoly.exe.
#
#
#  Usage:
#
#     NMAKE                     ; build with defaults
#     or: NMAKE option		; build with the given option(s)
#     or: NMAKE clean		; erase all compiled files
#
#     option:
#         dev = [win16 | win32 | mac] ; dev=win16 is the default
#         CPU = [i386 | M68K | MIPS | ALPHA | PPC]
#         DEBUG=[0|1]           ; DEBUG=1 is the default
#
#  Notes:
#
#    This makefile assumes that the PATH, INCLUDE and LIB environment
#    variables are setup properly.
#
##############################################################################



##########################################################################
#
# Default Settings
#

!if "$(dev)" == ""
dev = win16
!endif

!if !("$(dev)" == "win16" || "$(dev)" == "win32" || "$(dev)" == "mac")
!error Invalid dev option, choose from [win16 | win32 | mac]
!endif

!if "$(dev)" == "win16"
TARGET  = WIN16
!endif

!if "$(dev)" == "win32"
TARGET  = WIN32
!endif

!if "$(dev)" == "mac"
TARGET  = MAC
!endif

!if "$(DEBUG)" == ""
DEBUG = 1
!endif


##########################################################################
#
# WIN16 Settings
#
!if "$(TARGET)" == "WIN16"

CC   = cl
LINK = link

RCFLAGS = -dWIN16
CFLAGS = -W3 -AM -GA -GEs -DWIN16
LINKFLAGS = /NOD /NOI /BATCH /ONERROR:NOEXE

LIBS = libw.lib mlibcew.lib

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) -Od -Zi -D_DEBUG $(CL)
LINKFLAGS = $(LINKFLAGS) /COD
!else
CFLAGS = $(CFLAGS) -Ox $(CL)
LINKFLAGS = $(LINKFLAGS) /FAR /PACKC
!endif
!endif


##########################################################################
#
# WIN32 Settings
#
!if "$(TARGET)" == "WIN32"

!if "$(CPU)"==""

!if "$(PROCESSOR_ARCHITECTURE)"=="" || "$(PROCESSOR_ARCHITECTURE)"=="x86"
CPU=i386
!else 
CPU=$(PROCESSOR_ARCHITECTURE)
!endif

!endif #CPU

!if "$(CPU)" == "i386"
CC   = cl386
LINK = link
CFLAGS = -D_X86_=1
!endif
!if "$(CPU)" == "MIPS"
CC   = cl
LINK = link
CFLAGS = -D_MIPS_=1 -DUNICODE
!endif
!if "$(CPU)" == "ALPHA"
CC   = claxp
LINK = link
CFLAGS = -D_ALPHA_=1 -DUNICODE
!endif
!if "$(CPU)" == "PPC"
CC   = cl
LINK = link
CFLAGS = -D_PPC_=1 -DUNICODE
!endif

RCFLAGS = -dWIN32
CFLAGS = $(CFLAGS) -nologo -W3 -DWIN32 -DINC_OLE2 -D_MT $(CL)
LINKFLAGS = -Incremental:NO -Pdb:NONE -subsystem:windows -entry:WinMainCRTStartup -machine:$(CPU) 

LIBS = libc.lib kernel32.lib user32.lib gdi32.lib 


!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) -Od -Z7 -D_DEBUG $(CL)
LINKFLAGS = -debug:full -debugtype:cv,coff $(LINKFLAGS) 
!else
CFLAGS = $(CFLAGS) -Ox
!endif
!endif


##########################################################################
#
# MAC Settings
#
!if "$(TARGET)" == "MAC"

CC   = cl
LINK = link

RCFLAGS = -d_MAC
!if "$(CPU)"=="PPC"
CFLAGS = -W3 -D_MAC -D_PPCMAC -D_pascal= -D__pascal=
LINKFLAGS = -machine:mppc -ENTRY:mainCRTStartup -NOPACK -NODEFAULTLIB
LIBS = interfac.lib libc.lib ole2auto.lib  ole2.lib
!else
CFLAGS = -W3 -AL -D_MAC
LINKFLAGS = -machine:$(CPU) -ENTRY:mainCRTStartup -NOPACK -NODEFAULTLIB
LIBS = interfac.lib llibcs.lib lsanes.lib swap.lib
!endif 

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) -Od -Zi -D_DEBUG $(CL)
LINKFLAGS = $(LINKFLAGS) -debug:full -debugtype:cv
!else
CFLAGS = $(CFLAGS) -Ox $(CL)
!endif

MRC     = mrc
!if "$(CPU)"=="PPC"
MRCOPT = -D_PPCMAC -s$(VBATOOLS)\win32\ppc\lib
!else
MRCOPT =
!endif

MAKEPEF = makepef

!endif


##########################################################################
#
# Application Settings
#

SRCDIR = $(OLEPROG)\SAMPLE\spoly

!if "$(TARGET)" == "MAC" && "$(CPU)"=="PPC"
OBJDIR=$(SRCDIR)\macppc
!else
OBJDIR=$(SRCDIR)\$(TARGET)
!endif

!if [if not exist $(OBJDIR)\*.* mkdir $(OBJDIR)] != 0
!endif


!if "$(TARGET)" == "WIN16"
LIBS = ole2.lib compobj.lib ole2disp.lib ole2nls.lib $(LIBS)
!else 
!if "$(TARGET)" == "WIN32"
LIBS = ole32.lib oleaut32.lib uuid.lib $(LIBS)
!endif
!if "$(TARGET)" == "MAC"
!if "$(CPU)" != "PPC"
LIBS = olenrf.obj oanrf.obj $(LIBS)
!endif
!endif
!endif

OBJS = \
!if "$(TARGET)" == "MAC"
	$(OBJDIR)\macmain.obj	  \
!else
	$(OBJDIR)\winmain.obj	  \
!endif
	$(OBJDIR)\cpoly.obj	  \
	$(OBJDIR)\cpoint.obj	  \
	$(OBJDIR)\cenumpt.obj	  \
!if "$(TARGET)" != "MAC"
	$(OBJDIR)\statbar.obj	  \
!endif
	$(OBJDIR)\clsid.obj	  \
	$(OBJDIR)\misc.obj

goal : setflags $(OBJDIR)\spoly.exe

setflags :
	set CL=$(CFLAGS)

clean :
    if exist $(OBJDIR)\*.obj	   del $(OBJDIR)\*.obj
    if exist $(OBJDIR)\spoly.exe del $(OBJDIR)\spoly.exe
    if exist $(OBJDIR)\spoly.map del $(OBJDIR)\spoly.map
    if exist $(OBJDIR)\spoly.res del $(OBJDIR)\spoly.res
    if exist $(OBJDIR)\spoly.rs  del $(OBJDIR)\spoly.rs
    if exist $(SRCDIR)\*.pdb	   del $(SRCDIR)\*.pdb


##########################################################################
#
# Application Build (WIN16 Specific)
#

!if "$(TARGET)" == "WIN16"

$(OBJDIR)\spoly.exe : $(OBJS) $(SRCDIR)\spoly.def $(OBJDIR)\spoly.res $(SRCDIR)\spoly.ico
	link $(LINKFLAGS) @<<
$(OBJS: =+^
),
$@,$(OBJDIR)\spoly.map/map,
$(LIBS),
$(SRCDIR)\spoly.def
<<
	rc -k -t $(OBJDIR)\spoly.res $@
!endif


##########################################################################
#
# Application Build (WIN32 Specific)
#
!if "$(TARGET)" == "WIN32"

$(OBJDIR)\spoly.exe : $(OBJS) $(SRCDIR)\spoly.def $(OBJDIR)\spoly.res $(SRCDIR)\spoly.ico
      cvtres -r -$(CPU) $(OBJDIR)\spoly.res -o $(OBJDIR)\spoly.rs
      $(LINK) @<< 
        $(LINKFLAGS)
        -out:$@ 
        -map:$*.map
        $(OBJS)
	$(OBJDIR)\spoly.rs
        $(LIBS)
<<
!endif

##########################################################################
#
# Application Build (MAC Specific)
#
!if "$(TARGET)" == "MAC"
$(OBJDIR)\spoly.exe : $(OBJS) $(OBJDIR)\spoly.x
      $(LINK) @<< 
        $(LINKFLAGS)
        -out:$@ 
        -map:$*.map
        $(OBJS)
        $(LIBS)
<<
	copy $(OBJDIR)\spoly.x $(OBJDIR)\spoly
!if "$(CPU)" == "PPC"
	$(MAKEPEF) $(OBJDIR)\spoly.exe $(OBJDIR)\spoly.pef
!else
	cvpack $(OBJDIR)\spoly.exe
	$(MRC) $(MRCOPT) -e $(OBJDIR)\spoly.exe -a -o $(OBJDIR)\spoly
!endif

$(OBJDIR)\spoly.x:     $(SRCDIR)\spoly.r
    $(MRC) $(MRCOPT) -D_MAC -o $(OBJDIR)\spoly.x $(SRCDIR)\spoly.r
!endif

##########################################################################
#
# Application Build (Common)
#
$(OBJDIR)\spoly.res : $(SRCDIR)\spoly.rc $(SRCDIR)\resource.h
	rc $(RCFLAGS) -r -fo$@ $(SRCDIR)\spoly.rc

!if "$(TARGET)" == "MAC"
$(OBJDIR)\macmain.obj: $(SRCDIR)\macmain.cpp $(SRCDIR)\hostenv.h $(SRCDIR)\resource.h $(SRCDIR)\spoly.h $(SRCDIR)\cpoint.h $(SRCDIR)\cpoly.h $(SRCDIR)\statbar.h
	$(CC) -c -Fo$@ $(SRCDIR)\macmain.cpp
!else
$(OBJDIR)\winmain.obj: $(SRCDIR)\winmain.cpp $(SRCDIR)\hostenv.h $(SRCDIR)\resource.h $(SRCDIR)\spoly.h $(SRCDIR)\cpoint.h $(SRCDIR)\cpoly.h $(SRCDIR)\statbar.h
	$(CC) -c -Fo$@ $(SRCDIR)\winmain.cpp
!endif

$(OBJDIR)\cpoint.obj: $(SRCDIR)\cpoint.cpp $(SRCDIR)\cpoint.h $(SRCDIR)\hostenv.h $(SRCDIR)\spoly.h $(SRCDIR)\statbar.h
	$(CC) -c -Fo$@ $(SRCDIR)\cpoint.cpp

$(OBJDIR)\cpoly.obj: $(SRCDIR)\cpoly.cpp $(SRCDIR)\cpoint.h $(SRCDIR)\cpoly.h $(SRCDIR)\hostenv.h $(SRCDIR)\spoly.h $(SRCDIR)\statbar.h
	$(CC) -c -Fo$@ $(SRCDIR)\cpoly.cpp

$(OBJDIR)\clsid.obj: $(SRCDIR)\clsid.c $(SRCDIR)\clsid.h
	$(CC) -c -Fo$@ $(SRCDIR)\clsid.c

$(OBJDIR)\cenumpt.obj: $(SRCDIR)\cenumpt.cpp $(SRCDIR)\cenumpt.h
	$(CC) -c -Fo$@ $(SRCDIR)\cenumpt.cpp

!if "$(TARGET)" != "MAC"
$(OBJDIR)\statbar.obj: $(SRCDIR)\statbar.cpp $(SRCDIR)\statbar.h
	$(CC) -c -Fo$@ $(SRCDIR)\statbar.cpp
!endif

$(OBJDIR)\misc.obj: $(SRCDIR)\misc.cpp $(SRCDIR)\hostenv.h $(SRCDIR)\spoly.h
	$(CC) -c -Fo$@ $(SRCDIR)\misc.cpp
