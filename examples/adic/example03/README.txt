This example shows how to use AMG to call a generated code 
from adic. 

Contents : 
==========
  - simple.c : 
    a simple routine which takes 2 numbers c and x and return 
    thier product in y
  - driver.c :
    driver to initialize the gradients.  
  - test:
    amg input file to produce mex file for the augemented code
    of simple.c 

1- generate adic code
=====================
  $ . adc.init
  $ adiC -d gradient -h simple.c 

2- build the adic example
=========================
  $ . amg.init
  $ cc -c -g -I$ADIC/include -I$AMG_HOME/include simple.ad.c
  $ cc -c -g -I$ADIC/include -I$AMG_HOME/include driver.c 
  $ cc -g driver.o simple.ad.o -L$ADIC/lib/linux -ladic -laif_grad
  $ ./a.out

3- generate and build the mex file
==================================    
  $ amg test
  $ mv makefile.adic makefile
  $ gmake 
  $ gmake MOD=g_times KERNEL=simple.ad build

4- test
=======

$ gmake run TEST=test_g_times
