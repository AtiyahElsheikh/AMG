# AMG

Automatic Mexfunction Generator for calling C/Fortran Functions from Matlab 

## About 

This software has been initially implemented by Atiyah Elsheikh 2005 during his master thesis at RWTH Aachen.
A private copy of the master thesis and a resulting conference publication can be found at my ResearchGate website. 
The software is now further maintained by Mathemodica.com (C) 2019 

## System Requirements

a- for users
   - linux operating system / mingw
   - gcc version >= 3.3.1 (p.s: previous versions were not tested yet)

b- for developer
   - flex at least >= version 2.5.4 ( version 2.5.3x does not work)
   - bison >= version 1.875d (previous versions were not tested yet) 
   
## Releases
  July 2019 : 1.0-Alpha -- Initial version extracted from the software implemented 2005

## Building

To build amg  

   $ . amg.init
   
   $ gmake build

## Using the software 

Every time you want to use software, some necessary environment 
variables should be defined through

$ . amg.init
 

## Developer Note

	In each directory, there is a special text about developing issues
	Read it carefully, if u want to enhance the structure with any directory/example/file
