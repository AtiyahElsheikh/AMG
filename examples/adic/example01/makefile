# Describtion :
#       Makefile to compile mex files with generated codes from 
#       adic. on several platforms. It uses the mexopts.*.sh scripts 
#	under $AMG_HOME/config
#
#
# Tested Platforms :
#	Linux 32 bits and solaris
# Author      : Attiya ElSheikh  
#
# made        : 18 Jul 2005
# last changes: 
#--------------------------------------------------------------------------

ADD_CFLAGS = 
ADD_LFLAGS = 

NUM_THREADS = 1

ifeq ($(OSNAME),SunOS)
	EXECUTE=LAPACK_VERBOSITY=1  BLAS_VERSION=libsunperf.so.4 matlab -nodisplay -nojvm -nodesktop -nosplash -r 
else
	EXECUTE=LAPACK_VERBOSITY=1 matlab -nodisplay -nojvm -nodesktop -nosplash -r
endif 

KERNEL	=
MOD 	= 
TEST 	= test_$(MOD)
ifeq ($(KERNEL),)
	OBJECTS=$(MOD).o 
else
	OBJECTS=$(MOD).o $(KERNEL).o
endif

MEXSCRIPT =

ifeq ($(OSNAME),SunOS)
	PLATFORM=mexsol
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.sun.sh
	ADIC_LIB=$(ADIC)/lib/solaris -ladic -laif_grad
	CFLAGS=
else
  ifeq ($(OSNAME),Linux)
    ifeq ($(R_ADDRW),32)
	PLATFORM=mexglx
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.linux32.sh
	ADIC_LIB=$(ADIC)/lib/linux -ladic -laif_grad
	CFLAGS=-g -O3
    else
	PLATFORM=mexa64
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.linux64.sh
	ADIC_LIB=
	CFLAGS=-g -O3
    endif
  else
	@echo "not supported platform"
  endif
endif

MEX  = mex -f $(MEXSCRIPT)

EXE1 = $(MOD).$(PLATFORM)

help	:
	@echo ""
	@echo "Target are : "
	@echo "	build [MOD=*] [KERNEL=*]"
	@echo "		MOD:    The name of the mex file"
	@echo "		KERNEL : extra kernel routine like kernel"
	@echo "	to build a parallel version on SunOS"
	@echo "	- $ gmake build MEXSCRIPT=mexopts.sun-par.sh ..."
	@echo ""
	@echo "	run: [TEST=*]"
	@echo "	    - run the testing matlab code"
	@echo "	    - to run in parallel on SunOS, export OMP_NUM_THREADS=*"
	@echo "		TEST=the name of the m-file, default = test_$(MOD)"
	@echo ""
	@echo "	clean"
	@echo ""
	@echo "FLAGS :"
	@echo "	ADD_CFLAGS  : extra C flags"
	@echo "	ADD_LDFLAGS : extra linkage flags" 
	@echo "	NUM_THREADS = number of threads for shared mem. parallelization"

build : $(EXE1)
	@echo $(MEXSCRIPT)

run: 	
	$(EXECUTE) $(TEST)

$(EXE1)	: $(OBJECTS)
	$(MEX) -L$(ADIC_LIB) $(OBJECTS) -v

$(MOD).o: $(MOD).c 
	$(MEX) -c -I$(ADIC)/include $(MOD).c -v

$(KERNEL).o: $(KERNEL).c
	cc -c $(CFLAGS) -I$(ADIC)/include -I$(AMG_HOME)/include $(KERNEL).c

clean_obj:
	rm -f *.o
clean:
	rm -f *.out *.o  *.$(PLATFORM) core

