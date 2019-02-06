The structure of the tests
==========================

* Each test starts with a header of 3 lines that clarifies, what it is for

* Each test has the name test_XX, in which the function name is foo_XX.So
  that whenever amg is applied to, foo_XX.c is generated.

* Makefile has 3 targets, 
  - new: for generating new gateway functions (after some developments)
  - standard: after some developments are approved
  - compare: compare the new generated gateways with the standard ones

* directories
  new:
  standard[_Version]:


Adding new tests
================

* write the headers 
* name it as test_XX, where XX = the last number + 1
* let its function name foo_XX 
