SOURCE=source/
HEADERS=headers/
TMP=tmp/
LIB=lib/

TARGET=sfsd
TARGETLIB=lib$(TARGET)

INSTALLPATHLIB=/usr/local/lib/
INSTALLPATHINCLUDE=/usr/local/include/$(TARGET)/
INSTALLPATHSHARE=/usr/local/share/$(TARGET)/

ALLHEADERS=$(HEADERS)controls.hpp $(HEADERS)cpicture.hpp $(HEADERS)cbutton.hpp $(HEADERS)cmessagebox.hpp $(HEADERS)sglobal.hpp $(HEADERS)cslide.hpp $(HEADERS)vcontrol.hpp $(HEADERS)eaction.hpp
RESOURCES=../share/$(TARGET)/

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJECTS=$(TMP)cpicture.o $(TMP)cbutton.o $(TMP)cmessagebox.o $(TMP)sglobal.o $(TMP)cslide.o
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


.PHONY: all clean install uninstall $(TARGET) install_resources

all: $(TARGETLIB)

clean:
			@echo -e "$(ECHORM)$(TARGETLIB)*, $(TMP)*$(CLRRST)"
			@rm -f $(TARGETLIB)* $(TMP)*

#base values
$(TMP)sglobal.o: $(SOURCE)sglobal.cpp $(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)sglobal.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)sglobal.cpp -o $(TMP)sglobal.o

#class Picture
$(TMP)cpicture.o: $(SOURCE)cpicture.cpp $(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)cpicture.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)cpicture.cpp -o $(TMP)cpicture.o

#class Button
$(TMP)cbutton.o: $(SOURCE)cbutton.cpp $(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)cbutton.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)cbutton.cpp -o $(TMP)cbutton.o

#classes: MessageBox (virtual), InfoMessageBox, Ask-, Choose-
$(TMP)cmessagebox.o: $(SOURCE)cmessagebox.cpp $(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)cmessagebox.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)cmessagebox.cpp -o $(TMP)cmessagebox.o

#class Slide
$(TMP)cslide.o: $(SOURCE)cslide.cpp $(ALLHEADERS)
			@echo -e "$(ECHOBUILD)$(TMP)cslide.o$(CLRRST)"
			@$(GCC) -c $(SOURCE)cslide.cpp -o $(TMP)cslide.o

#lib
$(TARGETLIB): $(TARGETLIB).so $(TARGETLIB).a
$(TARGETLIB).so: $(OBJECTS)
			@echo -e "$(ECHOLINKDYN)$(TARGETLIB).so$(CLRRST) "
			@$(GCC) -shared $(LIBS) $(OBJECTS) -o $(TARGETLIB).so
$(TARGETLIB).a: $(OBJECTS)
			@echo -e "$(ECHOLINKSTAT)$(TARGETLIB).a$(CLRRST) "
			@$(AR) crs $(TARGETLIB).a $(OBJECTS)

install: install_resources $(INSTALLPATHLIB)$(TARGETLIB).so $(INSTALLPATHLIB)$(TARGETLIB).a

$(INSTALLPATHLIB)$(TARGETLIB).so: $(TARGETLIB).so
			@echo -e "[C] $(CLRGRN)Copying libs to $(CLRCYN)$(INSTALLPATHLIB)$(CLRRST) "
			@install $(TARGETLIB).so $(INSTALLPATHLIB)$(TARGETLIB).so

$(INSTALLPATHLIB)$(TARGETLIB).a: $(TARGETLIB).a
			@echo -e "[C] $(CLRGRN)Copying libs to $(CLRCYN)$(INSTALLPATHLIB)$(CLRRST) "
			@install $(TARGETLIB).a $(INSTALLPATHLIB)$(TARGETLIB).a

install_resources:
			@echo -e "[C] $(CLRGRN)Creating directories$(CLRRST) "
			@-mkdir $(INSTALLPATHINCLUDE)
			@echo -e "[C] $(CLRGRN)Copying headers to $(CLRCYN)$(INSTALLPATHINCLUDE)$(CLRRST) "
			@install --mode=0644 -t $(INSTALLPATHINCLUDE) $(ALLHEADERS)
			@echo -e "[C] $(CLRGRN)Copying resources to $(CLRCYN)$(INSTALLPATHSHARE)$(CLRRST) "
			@cp -r -t $(INSTALLPATHSHARE) $(RESOURCES)/*
			@chmod -R +r $(INSTALLPATHSHARE)/*
			@chmod +x $(INSTALLPATHSHARE)/*

uninstall:
			@echo -e "[C] $(CLRGRN)Removing libs from $(CLRCYN)$(INSTALLPATHLIB)$(CLRRST) "
			@rm -f $(INSTALLPATHLIB)$(TARGETLIB).so
			@rm -f $(INSTALLPATHINCLUDE)$(TARGETLIB).a
			@echo -e "[C] $(CLRGRN)Removing headers from $(CLRCYN)$(INSTALLPATHINCLUDE)$(CLRRST) "
			@rm -f $(INSTALLPATHINCLUDE)*
			@echo -e "[C] $(CLRGRN)Removing resources from $(CLRCYN)$(INSTALLPATHSHARE)$(CLRRST) "
			@rm -rf $(INSTALLPATHSHARE)*
			@rm -rf $(INSTALLPATHSHARE)../$(TARGET)
			@echo -e "[C] $(CLRGRN)Removing directories$(CLRRST) "
			@rm -r $(INSTALLPATHINCLUDE)

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
