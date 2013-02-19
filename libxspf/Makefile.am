## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = 1.10.1 gnu dist-zip dist-bzip2 dist-lzma subdir-objects

ACLOCAL_AMFLAGS = -I m4

if GENERATE_DOC
SUBDIRS = \
	. \
	doc \
	bindings/c/doc
endif

lib_LTLIBRARIES = libxspf.la

bin_PROGRAMS = \
	examples/check/xspf_check \
	examples/strip/xspf_strip

noinst_PROGRAMS = \
	examples/read/example_read \
	examples/write/example_write

if XSPF_TEST_ENABLED
check_PROGRAMS = test/xspf_test
endif

TESTS = test/xspf_test

pkgconfig_DATA = xspf.pc

pkgconfigdir = $(libdir)/pkgconfig


## Libtool workaround for distcheck
clean-local:
	-rm -f examples/*/.libs/*
if XSPF_TEST_ENABLED
	-rm -f test/.libs/*
endif


libxspf_la_CFLAGS = @URIPARSER_CFLAGS@

libxspf_la_LDFLAGS = @URIPARSER_LIBS@ -version-info 4:1:0

libxspf_la_SOURCES = \
	src/XspfChunkCallback.cpp \
	src/XspfData.cpp \
	src/XspfDataWriter.cpp \
	src/XspfDataWriter.h \
	src/XspfDateTime.cpp \
	src/XspfExtension.cpp \
	src/XspfExtensionReader.cpp \
	src/XspfExtensionReaderFactory.cpp \
	src/XspfExtensionWriter.cpp \
	src/XspfIndentFormatter.cpp \
	src/XspfProps.cpp \
	src/XspfPropsWriter.cpp \
	src/XspfPropsWriter.h \
	src/XspfReader.cpp \
	src/XspfReaderCallback.cpp \
	src/XspfSeamlessFormatter.cpp \
	src/XspfSkipExtensionReader.cpp \
	src/XspfSkipExtensionReader.h \
	src/XspfStrictReaderCallback.cpp \
	src/XspfStrictReaderCallback.h \
	src/XspfToolbox.cpp \
	src/XspfTrack.cpp \
	src/XspfTrackWriter.cpp \
	src/XspfTrackWriter.h \
	src/XspfWriter.cpp \
	src/XspfXmlFormatter.cpp \
	\
	src/ProjectOpus/ProjectOpusPlaylistExtension.cpp \
	src/ProjectOpus/ProjectOpusPlaylistExtensionReader.cpp \
	src/ProjectOpus/ProjectOpusPlaylistExtensionWriter.cpp \
	\
	bindings/c/xspf_c.cpp



include_xspfdir = $(prefix)/include/xspf

include_xspf_HEADERS = \
	include/xspf/Xspf.h \
	include/xspf/XspfChunkCallback.h \
	include/xspf/XspfData.h \
	include/xspf/XspfDateTime.h \
	include/xspf/XspfDefines.h \
	include/xspf/XspfExtension.h \
	include/xspf/XspfExtensionReader.h \
	include/xspf/XspfExtensionReaderFactory.h \
	include/xspf/XspfExtensionWriter.h \
	include/xspf/XspfIndentFormatter.h \
	include/xspf/XspfProps.h \
	include/xspf/XspfReader.h \
	include/xspf/XspfReaderCallback.h \
	include/xspf/XspfSeamlessFormatter.h \
	include/xspf/XspfStack.h \
	include/xspf/XspfToolbox.h \
	include/xspf/XspfTrack.h \
	include/xspf/XspfVersion.h \
	include/xspf/XspfWriter.h \
	include/xspf/XspfXmlFormatter.h \
	\
	bindings/c/xspf_c.h



include_xspf_ProjectOpusdir = $(prefix)/include/xspf/ProjectOpus

include_xspf_ProjectOpus_HEADERS = \
	include/xspf/ProjectOpus/ProjectOpusPlaylistExtension.h \
	include/xspf/ProjectOpus/ProjectOpusPlaylistExtensionReader.h \
	include/xspf/ProjectOpus/ProjectOpusPlaylistExtensionWriter.h



examples_check_xspf_check_LDADD = libxspf.la

examples_check_xspf_check_SOURCES = \
	examples/check/check.cpp



examples_read_example_read_LDADD = libxspf.la

examples_read_example_read_SOURCES = \
	examples/read/read.cpp



examples_strip_xspf_strip_LDADD = libxspf.la

examples_strip_xspf_strip_SOURCES = \
	examples/strip/strip.cpp



examples_write_example_write_LDADD = libxspf.la

examples_write_example_write_SOURCES = \
	examples/write/write.cpp


if XSPF_TEST_ENABLED
test_xspf_test_CFLAGS = @CPPTEST_CFLAGS@

test_xspf_test_LDFLAGS = @CPPTEST_LIBS@

test_xspf_test_LDADD = libxspf.la

test_xspf_test_CPPFLAGS = -DXSPF_SRCDIR=\"${srcdir}\"

test_xspf_test_SOURCES = \
	test/ProjectOpus/ProjectOpusSuite.cpp \
	test/ProjectOpus/ProjectOpusSuite.h \
	\
	test/ChunkCallbackSuite.cpp \
	test/ChunkCallbackSuite.h \
	test/DateTimeSuite.cpp \
	test/DateTimeSuite.h \
	test/ExtensionReaderFactorySuite.cpp \
	test/ExtensionReaderFactorySuite.h \
	test/MaliciousXmlSuite.cpp \
	test/MaliciousXmlSuite.h \
	test/MemoryModelSuite.cpp \
	test/MemoryModelSuite.h \
	test/ReadWriteSuite.cpp \
	test/ReadWriteSuite.h \
	test/OfficialSuite.cpp \
	test/OfficialSuite.h \
	test/WhiteSpaceSuite.cpp \
	test/WhiteSpaceSuite.h \
	\
	test/test.cpp
endif


EXTRA_DIST = \
	bindings/c/doc/m4/pkg.m4 \
	\
	bindings/c/doc/aclocal.m4 \
	bindings/c/doc/configure \
	bindings/c/doc/configure.ac \
	bindings/c/doc/Doxyfile.in \
	bindings/c/doc/Makefile.am \
	bindings/c/doc/Makefile.in \
	bindings/c/doc/release.sh.in \
	\
	doc/m4/pkg.m4 \
	\
	doc/aclocal.m4 \
	doc/configure \
	doc/configure.ac \
	doc/Doxyfile.in \
	doc/Mainpage \
	doc/Makefile.am \
	doc/Makefile.in \
	doc/release.sh.in \
	\
	examples/read/playlist.xspf \
	\
	m4/pkg.m4 \
	\
	test/for_version_0/fail/playlist-extension-forbidden.xspf \
	test/for_version_0/fail/track-extension-forbidden.xspf \
	test/for_version_0/fail/tracklist-no-tracks.xspf \
	test/for_version_1/fail/playlist-attribute-forbidden-annotation.xspf \
	test/for_version_1/fail/playlist-attribute-forbidden-playlist.xspf \
	test/for_version_1/fail/playlist-baddate.xspf \
	test/for_version_1/fail/playlist-badversion.xspf \
	test/for_version_1/fail/playlist-element-forbidden-attribution.xspf \
	test/for_version_1/fail/playlist-extension-application-missing.xspf \
	test/for_version_1/fail/playlist-link-rel-missing.xspf \
	test/for_version_1/fail/playlist-markup-annotation.xspf \
	test/for_version_1/fail/playlist-markup-creator.xspf \
	test/for_version_1/fail/playlist-markup-meta.xspf \
	test/for_version_1/fail/playlist-markup-title.xspf \
	test/for_version_1/fail/playlist-meta-rel-missing.xspf \
	test/for_version_1/fail/playlist-missingtracklist.xspf \
	test/for_version_1/fail/playlist-missingversion.xspf \
	test/for_version_1/fail/playlist-namespace-missing.xspf \
	test/for_version_1/fail/playlist-namespace-nested-broken.xspf \
	test/for_version_1/fail/playlist-namespace-wrong-string.xspf \
	test/for_version_1/fail/playlist-nonleaf-content-attribution.xspf \
	test/for_version_1/fail/playlist-nonleaf-content-playlist.xspf \
	test/for_version_1/fail/playlist-nonleaf-content-trackList.xspf \
	test/for_version_1/fail/playlist-noturi-attribution-identifier.xspf \
	test/for_version_1/fail/playlist-noturi-attribution-location.xspf \
	test/for_version_1/fail/playlist-noturi-extension.xspf \
	test/for_version_1/fail/playlist-noturi-identifier.xspf \
	test/for_version_1/fail/playlist-noturi-image.xspf \
	test/for_version_1/fail/playlist-noturi-info.xspf \
	test/for_version_1/fail/playlist-noturi-license.xspf \
	test/for_version_1/fail/playlist-noturi-link-content.xspf \
	test/for_version_1/fail/playlist-noturi-link-rel.xspf \
	test/for_version_1/fail/playlist-noturi-location.xspf \
	test/for_version_1/fail/playlist-noturi-meta.xspf \
	test/for_version_1/fail/playlist-root-name.xspf \
	test/for_version_1/fail/playlist-toomany-annotation.xspf \
	test/for_version_1/fail/playlist-toomany-attribution.xspf \
	test/for_version_1/fail/playlist-toomany-creator.xspf \
	test/for_version_1/fail/playlist-toomany-date.xspf \
	test/for_version_1/fail/playlist-toomany-identifier.xspf \
	test/for_version_1/fail/playlist-toomany-image.xspf \
	test/for_version_1/fail/playlist-toomany-info.xspf \
	test/for_version_1/fail/playlist-toomany-license.xspf \
	test/for_version_1/fail/playlist-toomany-location.xspf \
	test/for_version_1/fail/playlist-toomany-title.xspf \
	test/for_version_1/fail/playlist-toomany-tracklist.xspf \
	test/for_version_1/fail/track-badint-duration.xspf \
	test/for_version_1/fail/track-badint-tracknum.xspf \
	test/for_version_1/fail/track-extension-application-missing.xspf \
	test/for_version_1/fail/track-link-rel-missing.xspf \
	test/for_version_1/fail/track-markup-album.xspf \
	test/for_version_1/fail/track-markup-annotation.xspf \
	test/for_version_1/fail/track-markup-creator.xspf \
	test/for_version_1/fail/track-markup-meta.xspf \
	test/for_version_1/fail/track-markup-title.xspf \
	test/for_version_1/fail/track-meta-rel-missing.xspf \
	test/for_version_1/fail/track-nonleaf-content.xspf \
	test/for_version_1/fail/track-noturi-extension.xspf \
	test/for_version_1/fail/track-noturi-identifier.xspf \
	test/for_version_1/fail/track-noturi-image.xspf \
	test/for_version_1/fail/track-noturi-info.xspf \
	test/for_version_1/fail/track-noturi-link.xspf \
	test/for_version_1/fail/track-noturi-link-rel.xspf \
	test/for_version_1/fail/track-noturi-location.xspf \
	test/for_version_1/fail/track-noturi-meta-rel.xspf \
	test/for_version_1/fail/track-toomany-album.xspf \
	test/for_version_1/fail/track-toomany-annotation.xspf \
	test/for_version_1/fail/track-toomany-creator.xspf \
	test/for_version_1/fail/track-toomany-duration.xspf \
	test/for_version_1/fail/track-toomany-image.xspf \
	test/for_version_1/fail/track-toomany-info.xspf \
	test/for_version_1/fail/track-toomany-title.xspf \
	test/for_version_1/fail/track-toomany-tracknum.xspf \
	test/for_version_1/fail/track-whitespace-in-between.xspf \
	test/for_version_1/fail/xml-error.xspf \
	test/for_version_1/pass/playlist-empty-annotation.xspf \
	test/for_version_1/pass/playlist-empty-creator.xspf \
	test/for_version_1/pass/playlist-empty-meta.xspf \
	test/for_version_1/pass/playlist-empty-title.xspf \
	test/for_version_1/pass/playlist-extension.xspf \
	test/for_version_1/pass/playlist-extensive.xspf \
	test/for_version_1/pass/playlist-inverted-order.xspf \
	test/for_version_1/pass/playlist-namespace-nested-proper.xspf \
	test/for_version_1/pass/playlist-namespace-nondefault.xspf \
	test/for_version_1/pass/playlist-namespace-two-additions.xspf \
	test/for_version_1/pass/playlist-whitespace-dateTime.xspf \
	test/for_version_1/pass/playlist-xml-base.xspf \
	test/for_version_1/pass/track-empty-album.xspf \
	test/for_version_1/pass/track-empty-annotation.xspf \
	test/for_version_1/pass/track-empty-creator.xspf \
	test/for_version_1/pass/track-empty-meta.xspf \
	test/for_version_1/pass/track-empty-title.xspf \
	test/for_version_1/pass/track-extension.xspf \
	test/for_version_1/pass/track-extensive.xspf \
	test/for_version_1/pass/track-inverted-order.xspf \
	test/for_version_1/pass/track-whitespace-anyURI.xspf \
	test/for_version_1/pass/track-whitespace-nonNegativeInteger.xspf \
	\
	test/ProjectOpus/Example.xspf \
	\
	win32/Code_Blocks/libxspf.cbp \
	win32/Code_Blocks/libxspf.workspace \
	\
	win32/Code_Blocks/check.cbp \
	win32/Code_Blocks/read.cbp \
	win32/Code_Blocks/strip.cbp \
	win32/Code_Blocks/test.cbp \
	win32/Code_Blocks/write.cbp \
	\
	win32/Visual_Studio_2005/libxspf.sln \
	win32/Visual_Studio_2005/libxspf.vcproj \
	\
	win32/Visual_Studio_2005/check.vcproj \
	win32/Visual_Studio_2005/read.vcproj \
	win32/Visual_Studio_2005/test.vcproj \
	win32/Visual_Studio_2005/strip.vcproj \
	win32/Visual_Studio_2005/write.vcproj \
	\
	THANKS
