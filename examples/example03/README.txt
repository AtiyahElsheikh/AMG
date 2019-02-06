
1- generate the mex file with the command 

   $ amg test

   this will produce 3 files : 
   - The source code of the mex file 
   - a log text for the output of mex generator 
   - a help makefile for testing

2- type gmake to know the various options u have 

   $ gmake 

3- compile the kernel file

   cc -c -g -fast -xopenmp kernel.c
or 
   cc -c -g -fast -xrestrict -xautopar -xreduction kernel.c 
  
3- compile the mex file 

   $ gmake  MOD=times2 KERNEL=kernel build 

4- test the result 

   $ gmake MOD=time2 run 

5- compile with openmp

   $ gmake MOD=times2 KERNEL=kernel build_omp

6- test the result
   
   $ gmake NUM_THREADS=4 MOD=times2 run_par
