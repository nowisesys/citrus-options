EXTRA_DIST = libcitrus-options.pc.in libcitrus-options.pc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcitrus-options.pc

otherincludedir = $(includedir)/citrus
otherinclude_HEADERS = options.hpp

lib_LTLIBRARIES = libcitrus-options.la
libcitrus_options_la_SOURCES = options.hpp options.cpp

libcitrus_options_la_LDFLAGS  = -version-info 1:0:0
libcitrus_options_la_CXXFLAGS = -DLIBCITRUS_EXPORTS=1
