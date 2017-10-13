include config.mk

SRCS=$(wildcard *.cc)
OBJS=$(SRCS:.cc=.o)

all: example

example: $(OBJS)
	   $(CXX) -o $@ $(OBJS) $(LFLAGS) $(LIBS)
%.o:%.cc
	   $(CXX) ${CXXFLAGS} ${INCLUDES} -c -o $@ $<
%.cc:%.h
	@touch $@
clean:
	$(RM) $(OBJS)

resu_clean:
	$(RM) $(RESU_OBJS)
.PHONY: all clean 

#g++ -DHAVE_CONFIG_H -I. -I..  -I../src -I../src -DGMM_USES_BLAS  -I/u/archive/agip/cerroni/software/getfem/getfem/include  -O3 -Wall -W -fmessage-length=0 -ftemplate-depth-100 -std=c++11 -fPIC -pedantic -Wshadow -Wno-unknown-pragmas -Wno-variadic-macros -Wno-unused-but-set-variable -Wpointer-arith -Wcast-qual -Wwrite-strings -Wconversion -Wredundant-decls -Wno-long-long -c -o elastostatic.o elastostatic.cci
#/u/archive/agip/cerroni/software/getfem/getfem/lib/libgetfem.a -lm  -rdynamic 
