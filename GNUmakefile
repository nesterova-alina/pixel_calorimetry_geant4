# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := calorimeter
G4TARGET := $(name)
G4EXLIB := true


.PHONY: all
all: lib bin


# ROOT support
CPPFLAGS += -I$(shell root-config --incdir) 
EXTRALIBS = $(shell root-config --glibs)

include $(G4INSTALL)/config/binmake.gmk


#histclean:
#	rm ${G4WORKDIR}/tmp/${G4SYSTEM}/${G4TARGET}/HistoManager.o


