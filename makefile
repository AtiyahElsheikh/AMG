help:
	@echo "Build Targets"
	@echo "============="
	cd src;	make help
	@echo ""
	@echo "Global Targets are:"
	@echo "==================="
	@echo "	- cleanall: remove all binaries and objects under bin,src,examples "
	@echo "	- version:  make a version of the software in the parent directory version.tar"
	@echo ""
	@echo "Test Targets:"
	@echo " - "
	@echo "============="
	cd tests; make -f makefile.tests

build:
	cd src; make build

clean:
	cd src; make clean

cleanall:
	cd bin; rm -f */mexgen
	cd examples; rm -f */*.mexsol */*.mexa64 */*/*.mexa64 */*/*.mexsol */*.o */*/*.o  
	cd src; rm -f */*.o */mexgen 	
	rm -f */get.ksh

version:
	rm -fR ../amg_version
	mkdir -p ../amg_version
	cp -R * ../amg_version
	cd ../amg_version;make cleanall


# for testing

# generate new gateway functions of input files in \tests
new:
	cd tests; make -f makefile.tests new

# generate standard gateway function of input files in \tests
standard:
	cd tests; make -f makefiles.tests standard

# compare the standard gateways with the new gateways
compare:
	cd tests; make -f makefiles.tests compare 