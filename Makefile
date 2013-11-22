CXX = u++						# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD ${OPT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = q2Printer.o q2Workshop.o q2Santa.o q2Reindeer.o q2Elf.o q2Driver.o
EXEC1 = northpole

OBJECTS = ${OBJECTS1}					# all object files
DEPENDS = ${OBJECTS:.o=.d}				# substitute ".o" with ".d"
EXECS = ${EXEC1}						# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}						# build all executables

${EXEC1} : ${OBJECTS1}					# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}				# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}					# include *.d files containing program dependences

clean :							# remove files that can be regenerated
	rm -f *.d *.o ${EXECS}
