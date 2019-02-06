
#FLEX_HOME=/home/af116el/bin
FLEX=${HOME}/bin/flex

CC= gcc
CFLAGS= -g
LDFLAGS= -g
LDLIBS=
LLEXFLAGS=

PLATFORM=$(OSNAME)$(R_ADDRW)
EXE=mexgen
OBJECTS=$(PLATFORM)/func.tab.o $(PLATFORM)/generator.o $(PLATFORM)/lex.yy.o \
	$(PLATFORM)/arguments_arr.o $(PLATFORM)/functions.o \
	$(PLATFORM)/lists.o $(PLATFORM)/doc_tmp.o $(PLATFORM)/doc_ad_tmp.o \
	$(PLATFORM)/copyright_tmp.o $(PLATFORM)/input_tmp.o \
	$(PLATFORM)/output_tmp.o

help:
	@echo $(PLATFORM)
	@echo "Targets are:"
	@echo "	- build:    build the software: execute $ . amg.init first"
	@echo "	- clean:    remove the machine-binaries"
	@echo ""

build: $(PLATFORM)/$(EXE)
	rm -f $(AMG_HOME)/bin/$(PLATFORM)/$(EXE)
	ln -f $(AMG_HOME)/src/$(PLATFORM)/$(EXE) $(AMG_HOME)/bin/$(PLATFORM)/$(EXE)

$(PLATFORM)/$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $(PLATFORM)/$(EXE)

$(OBJECTS):$(PLATFORM)/%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

func.tab.c: func.y functions.h
	bison -d func.y	

lex.yy.c: functions.h func.lex
	$(FLEX) func.lex

arguments_arr.c: arguments_list.h

functions.c: functions.h

generator.c: functions.h 

lists.c: lists.h

functions.h: lists.h global_properties.h arguments_list.h

doc_tmp.c: ../config/doc.tmp
	echo >$@ "const char *doc_tmp= {";
	sed "s/\(.*\)/\"\1\\\\n\"/" $< >>$@
	echo >>$@ "\"\\0\"};"

doc_ad_tmp.c: ../config/doc-ad.tmp
	echo >$@ "const char *doc_ad_tmp= {";
	sed "s/\(.*\)/\"\1\\\\n\"/" $< >>$@
	echo >>$@ "\"\\0\"};"

copyright_tmp.c: ../config/copyright.tmp
	echo >$@ "const char *copyright_tmp= {";
	sed "s/\(.*\)/\"\1\\\\n\"/" $< >>$@
	echo >>$@ "\"\\0\"};"

input_tmp.c: ../config/input.tmp
	echo >$@ "const char *input_tmp= {";
	sed "s/\(.*\)/\"\1\\\\n\"/" $< >>$@
	echo >>$@ "\"\\0\"};"

output_tmp.c: ../config/output.tmp
	echo >$@ "const char *output_tmp= {";
	sed "s/\(.*\)/\"\1\\\\n\"/" $< >>$@
	echo >>$@ "\"\\0\"};"

clean:
	-rm -f $(PLATFORM)/$(EXE) $(PLATFORM)/*.o ../bin/$(PLATFORM)/$(EXE) 
                                               
distclean: clean
	- rm -f func.tab.* lex.yy.c *_tmp.c
