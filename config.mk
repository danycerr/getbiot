CXXFLAGS = -I ${GET_FEM_DIR}/include
CXXFLAGS += -I ${SAMG}/

LFLAGS = -L${QHULL_DIR}/lib
LFLAGS += -L${LAPACK_DIR}/lib64
LFLAGS += -L/opt/lib/samg/

CXXFLAGS +=-DGMM_USES_BLAS -O3 -Wall -W 
CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
CXXFLAGS += -DSAMG_UNIX_LINUX -DSAMG_LCASE_USCORE -DPYRAMID_TRIANGULAR_FACETS
CXXFLAGS +=-fmessage-length=0 -ftemplate-depth-100 -fPIC -std=c++11 
CXXFLAGS +=-pedantic -Wshadow -Wno-unknown-pragmas -Wno-variadic-macros 
CXXFLAGS +=-Wno-unused-but-set-variable -Wpointer-arith -Wcast-qual 
CXXFLAGS +=-Wwrite-strings -Wconversion -Wredundant-decls -Wno-long-long

LIBS =  ${GET_FEM_DIR}/lib/libgetfem.a    
LIBS += -lm  -rdynamic
LIBS += -lqhull 
LIBS += -lblas 
LIBS += -llapack 
LIBS += -lamg -liomp5
