
1- generate the mex file with the command 

   $ amg test

   this will produce 3 files : 
   - The source code of the mex.file 
   - a log text for the output of mex generator 
   - a help makefile for testing

2- type gmake to know the various options u have 

   $ gmake 

3- compile the mex file 

   $ gmake MOD=fast_transpose KERNELF=transpose ADD_FFLAGS="-free" build 

4- test the result 

   $ gmake MOD=fast_transpose run 
