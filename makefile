help:
	@echo "Build Targets"
	@echo "============="
	cd src;	gmake help
	@echo ""
	@echo "Global Targets are:"
	@echo "==================="
	@echo "	- cleanall: remove all binaries and objects under bin,src,examples"
	@echo "	- version:  make a version of the software in the parent directory version.tar
	@echo ""
	@echo "Test Targets:"
	@echo "============="
	cd tests; gmake -f makefile.tests

build:
	cd src; gmake build

clean:
	cd src; gmake clean

cleanall:
	cd bin; rm -f */mexgen
	cd examples; rm -f */*.mexsol */*.mexa64 */*/*.mexa64 */*/*.mexsol */*.o */*/*.o  
	cd src; rm -f */*.o */mexgen 	
	rm -f */get.ksh

version:
	rm -fR ../amg_version
	mkdir -p ../amg_version
	cp -R * ../amg_version
	cd ../amg_version;gmake cleanall


# for testing

# generate new gateway functions of input files in \tests
new:
	cd tests; gmake -f makefile.tests new

# generate standard gateway function of input files in \tests
standard:
	cd tests; gmake -f makefiles.tests compare

# compare the standard gateways with the new gateways
compare:
	cd tests; gmake -f makefiles.tests tests