bin_PROGRAMS               = hardisp
hardisp_SOURCES            = hardisp.cpp
## Only use the following flags for debuging purposes
## hardisp_CXXFLAGS           = -std=c++11 -g -Wall -Wextra -pedantic -W -Wshadow -Winline -Wdisabled-optimization -I$(srcdir) -L$(srcdir)
hardisp_CXXFLAGS           = -std=c++11 -Wall -O3
hardisp_LDADD              = libiers10++.a
lib_LIBRARIES           = libiers10++.a
dist_include_HEADERS    = iers2010.hpp hardisp.hpp dehanttideinel.hpp
## Only use the following flags for debuging purposes
## libiers10___a_CXXFLAGS     = -std=c++11 -g -Wall -Wextra -Werror -pedantic -W -Wshadow -Winline -Wdisabled-optimization
libiers10___a_CXXFLAGS     = -std=c++11 -Wall -O3
dist_pkgdata_DATA          = ../gpt2_5.grd
nodist_libiers10___a_SOURCES = gpt2.cpp
EXTRA_DIST = gpt2-unset.cpp
dist_libiers10___a_SOURCES = fundarg.cpp \
							 pmsdnut2.cpp \
							 utlibr.cpp \
							 fcnnut.cpp \
							 arg2.cpp \
							 vmf1_ht.cpp \
							 vmf1.cpp \
							 gmf.cpp \
							 dehanttideinel.cpp \
							 rg_zont2.cpp \
							 cnmtx.cpp \
							 ortho_eop.cpp \
							 apg.cpp \
							 fcul_a.cpp \
							 fcul_b.cpp \
							 fcul_zd_hpa.cpp \
							 st1idiu.cpp \
							 st1isem.cpp \
							 st1l1.cpp \
							 step2diu.cpp \
							 step2lon.cpp \
							 cal2jd.cpp \
							 dat.cpp \
							 etutc.cpp \
							 eval.cpp \
							 recurs.cpp \
							 shells.cpp \
							 utils.cpp \
							 spline.cpp \
							 tdfrph.cpp \
							 admint.cpp \
							 iohardisp.cpp \
							 gpt.cpp
gpt2.cpp: gpt2-unset.cpp
	cp gpt2-unset.cpp gpt2.cpp
	$(SED) -i "s|#define PATH_TO_GRD25_GRD.*|#define PATH_TO_GRD25_GRD \"@datarootdir@/libiers10/gpt2_5.grd\"|g" $@
	@echo "$(SED) -i \"s|#define PATH_TO_GRD25_GRD.*|#define PATH_TO_GRD25_GRD \"@datarootdir@/gpt2_5.grd\"|g\" $@"

## TODO Remove the gpt2-unset.cpp file
