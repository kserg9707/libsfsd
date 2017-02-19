SOURCE=source/
HEADERS=headers/
TMP=tmp/
LIB=lib/

TARGET=test

LIBPATH=-Wl,-rpath,/usr/local/lib -Wl,-rpath,./lib -Wl,-rpath,./ -L./lib

#ALLHEADERS=$(HEADERS)cpicture.h $(HEADERS)cbutton.h $(HEADERS)cmessagebox.h $(HEADERS)sbasevalues.h $(HEADERS)cslide.h $(HEADERS)vcontrol.h $(HEADERS)eaction.h

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfsd
OBJECTS=$(TMP)main.o
GCC=$(CXX) $(CFLAGS) -O1 -Wall -pedantic -Werror -fpic

CLRGRN=\033[00;32m
CLRCYN=\033[00;36m
BCLRGRN=\033[01;32m
BCLRCYN=\033[01;36m
CLRRST=\033[00m
ECHORM=[C] $(CLRGRN)Removing $(CLRCYN)
ECHOBUILD=[B] $(CLRGRN)Building object $(CLRCYN)
ECHOLINK=[L] $(CLRGRN)Linking target $(CLRCYN)
ECHOLINKDYN=[L] $(CLRGRN)Linking dynamic $(CLRCYN)
ECHOLINKSTAT=[A] $(CLRGRN)Archiving static $(CLRCYN)
ECHOINST=
ECHODONE=[R] $(BCLRGRN)Built target $(CLRCYN)


.PHONY: all clean installedlib libinstall

all: installedlib $(TARGET)

clean:
			@echo -e "$(ECHORM)$(TARGET), $(TMP)*$(CLRRST)"
			@rm -f $(TARGET) $(TMP)*

installedlib:
			@cd $(LIB) && $(MAKE)

libinstall: installedlib
			@cd $(LIB) && $(MAKE) install

#main
$(TMP)main.o: $(SOURCE)main.cpp #$(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)main.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)main.cpp -o $(TMP)main.o

#program
#-Wl,-rpath,./lib - for shared. now shared not used
#$(TARGET): $(TMP)main.o $(LIB)$(TARGETLIB).a
#			@echo -e "[L] $(CGREEN)Linking target$(CCLEAR) "
#			@echo -e "[I] $(CGREEN)Using static $(CCYAN)$(TARGETLIB)$(CCLEAR) "
#			@$(GCC) $(LIBS) -L./$(LIB) $(TMP)main.o -Wl,-Bstatic -l$(LDTARGET) -Wl,-Bdynamic -o $(TARGET)
#			@echo -e "[R] $(CGREEN)Built target $(CCYAN)$(TARGET)$(CCLEAR) "

$(TARGET): $(TMP)main.o
			@echo -e "$(ECHOLINK) $@$(CLRRST)"
			@echo -e "[I] $(CLRGRN)Using dynamic $(CLRCYN)$(TARGETLIB)$(CLRRST) "
			@$(GCC) $(LIBS) $(LIBPATH) $(TMP)main.o -o $(TARGET)

#Makefile info
help:
			@echo -e "$(BCLRCYN)information marks:$(CLRRST)"
			@echo -e "[C] - working with files - copying, removing."
			@echo -e "[B] - building object file"
			@echo -e "[L] - linking object files"
			@echo -e "[A] - archiving object files"
			@echo -e "[R] - ready, done some action"
			@echo -e "[I] - info about current action"
			@echo
			@echo -e "$(BCLRCYN)Building commands:$(CLRRST)"
			@echo -e "$(GCC) -c $(SOURCE)main.cpp -o $(TMP)main.o"
			@echo -e "$(GCC) $(LIBS) $(TMP)main.o -o $(TARGET)"
			@echo
			@echo -e "$(BCLRCYN)Clean command:$(CLRRST)"
			@echo -e "rm -f $(TARGET) $(LIB)* $(TMP)*"
