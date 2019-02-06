# Describtion :
#       Makefile to compile mex files on several platforms and compilers
#       it makes use of mexopts.*.sh under $AMG_HOME/config
#
# Tested Platforms :
#	Linux 32,64 bits and solaris
# Author      : Attiya ElSheikh  
#
# made        : 10 Jul 2005
# last changes: 29 Jul 2005
#--------------------------------------------------------------------------

CC=cc
F90=f90

ADD_CFLAGS = 
ADD_LFLAGS = 
ADD_FFLAGS =

NUM_THREADS = 1

ifeq ($(OSNAME),SunOS)
	EXECUTE=LAPACK_VERBOSITY=1  BLAS_VERSION=libsunperf.so.4 matlab -nodisplay -nojvm -nodesktop -nosplash -r 
else
	EXECUTE=LAPACK_VERBOSITY=1 matlab -nodisplay -nojvm -nodesktop -nosplash -r
endif 

KERNEL	=
KERNELF =
MOD 	= 
TEST 	= test_$(MOD)

ifeq ($(KERNEL),)
    ifeq ($(KERNELF),)
	OBJECTS=$(MOD).o
    else
	OBJECTS=$(MOD).o $(KERNELF).o
    endif 
else
    ifeq ($(KERNELF),)	
	OBJECTS=$(MOD).o $(KERNEL).o
    else
	OBJECTS=$(MOD).o $(KERNEL).o $(KERNELF).o
    endif
endif

MEXSCRIPT =
CC	  = cc
ifeq ($(MEXSCRIPT),mexopts.opteron-icc-omp.sh)
	CC=cc -gcc-version=340
	F90=ifort -gcc-version=340
	CFLAGS=-g -O3 -openmp
else
  ifeq ($(MEXSCRIPT),mexopts.opteron-icc-par.sh)
	CC=cc -gcc-version=340
	F90=ifort -gcc-version=340
	CFLAGS=-g -O3 -parallel
  endif 
endif

ifeq ($(OSNAME),SunOS)
	PLATFORM=mexsol
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.sun.sh
	CFLAGS=-g -fast
	FFLAGS=-g -fast
else
  ifeq ($(OSNAME),Linux)
    ifeq ($(R_ADDRW),32)
	PLATFORM=mexglx
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.linux32.sh
	CFLAGS=-g -O3
    else
	PLATFORM=mexa64
	MEXSCRIPT=$(AMG_HOME)/config/mexopts.linux64.sh
	CFLAGS=-g -O3
    endif
    F90=g77 -ffree-form -ff90
    FFLAGS=-g -O3
  else
	@echo "not supported platform"
  endif
endif

MEX  = mex -f $(MEXSCRIPT)

EXE1 = $(MOD).$(PLATFORM)

help	:
	@echo ""
	@echo "Target are : "
	@echo "	build [MOD=*] [KERNEL=*] [KERNELF=*]"
	@echo "		MOD:    The name of the mex file"
	@echo "		KERNEL : extra kernel routine like kernel"
	@echo "		KERNELF : extra kernel routine in fortran"
	@echo "			  assumend that the target is *.f"
	@echo ""
	@echo "	to build a parallel version on SunOS/Opteron you need to copy one of" 
	@echo "	the following scripts und $AMG_HOME/config to the current directory:"
	@echo "	- mexopts.sun-omp.sh for explicit parallelization on SunOS"
	@echo "	- mexopts.sun-par.sh for implicit parallelization on SunOS"
	@echo "	- mexopts.opteron-icc-omp.sh on opteron with intel compiler"
	@echo "	- mexopts.opteron-icc-par.sh "
	@echo "	then build your program with:"
	@echo "	$ gmake build MOD=.. MEXSCRIPT=mexopts.opteron-icc-omp.sh"
	@echo ""
	@echo "	WARNING:"
	@echo "	- if you change the names of any script, it will not work"
	@echo ""
	@echo "	run: [TEST=*]"
	@echo "	    - run the testing matlab code"
	@echo "		TEST=the name of the m-file, default = test_$(MOD)"
	@echo "	    - to run in parallel on SunOS/Opteron, export OMP_NUM_THREADS=*"
	@echo ""
	@echo "	clean"
	@echo ""
	@echo "FLAGS :"
	@echo "	ADD_CFLAGS  : extra C flags"
	@echo "	ADD_LDFLAGS : extra linkage flags" 
	@echo "	ADD_FFLAGS :  extra F90 flags for the kernel" 
	@echo "	NUM_THREADS = number of threads for shared mem. parallelization"

build : $(EXE1)
	@echo $(MEXSCRIPT)

run: 	
	$(EXECUTE) $(TEST)

$(EXE1)	: $(OBJECTS)
	$(MEX) $(OBJECTS) $(ADD_LDFLAGS) -v

$(MOD).o: $(MOD).c 
	$(MEX) $(ADD_CFLAGS) -c $(MOD).c -v

$(KERNEL).o: $(KERNEL).c
	$(CC) -c $(CFLAGS) $(ADD_CFLAGS) $(KERNEL).c

$(KERNELF).o: $(KERNELF).f
	$(F90) -c $(FFLAGS) $(ADD_FFLAGS) $(KERNELF).f

clean_obj:
	rm -f *.o
clean:
	rm -f *.out *.o  *.$(PLATFORM) core

