# Process this file with autoconf to produce a configure script.
AC_PREREQ(2.61)
AC_INIT(src/XspfReader.cpp)
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE(libxspf, 1.2.0)

AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX
PKG_PROG_PKG_CONFIG

AC_HEADER_STDC



## Option --disable-test
AC_ARG_ENABLE(test, [
===========================================================================
Extra options:
AS_HELP_STRING(
	[--disable-test], [disable 'make check' and libcpptest dependency]
)], [
	XSPF_TEST_YESNO=${enableval}
],[
	XSPF_TEST_YESNO=yes
])
AM_CONDITIONAL([XSPF_TEST_ENABLED], [test "${XSPF_TEST_YESNO}" = "yes"])



# Expat
AC_ARG_WITH(expat, [
===========================================================================
Extra options:
AS_HELP_STRING([--with-expat=DIR], [override path of Expat])
AS_HELP_STRING([], [("/lib" and "/include" is appended)]
)], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-expat])
	fi
	LDFLAGS="-L${withval}/lib ${LDFLAGS}"
	CPPFLAGS="-I${withval}/include ${CPPFLAGS}"
], [])

AC_ARG_WITH(expat-inc, [AS_HELP_STRING(
	[--with-expat-inc=DIR], [override include path of Expat]
)], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-expat-inc])
	fi
	CPPFLAGS="-I${withval} ${CPPFLAGS}"
], [])

AC_ARG_WITH(expat-lib, [AS_HELP_STRING(
	[--with-expat-lib=DIR], [override library path of Expat]
)], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-expat-lib])
	fi
	LDFLAGS="-L${withval} ${LDFLAGS}"
], [])



# uriparser
AC_ARG_WITH(uriparser, [AS_HELP_STRING(
	[--with-uriparser=DIR], [override path of uriparser])
AS_HELP_STRING([], [("/lib" and "/include" is appended)]
)], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-uriparser])
	fi
	LDFLAGS="-L${withval}/lib ${LDFLAGS}"
	CPPFLAGS="-I${withval}/include ${CPPFLAGS}"
], [])

AC_ARG_WITH(uriparser-inc, [AS_HELP_STRING(
	[--with-uriparser-inc=D], [override include path of uriparser]
)], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-uriparser-inc])
	fi
	CPPFLAGS="-I${withval} ${CPPFLAGS}"
], [])

AC_ARG_WITH(uriparser-lib, [AS_HELP_STRING(
	[--with-uriparser-lib=D], [override library path of uriparser])
===========================================================================], [
	if test "x${withval}" = "x"; then
		AC_MSG_ERROR([No path given for option --with-uriparser-lib])
	fi
	LDFLAGS="-L${withval} ${LDFLAGS}"
], [])


## API documentation
AC_ARG_ENABLE(doc, [AS_HELP_STRING(
	[--enable-doc], [generate API documentation with Doxygen])
===========================================================================], [
	XSPF_DOC_YESNO=${enableval}
	if test ${enableval} = yes ; then
		AC_CONFIG_SUBDIRS([doc])
		AC_CONFIG_SUBDIRS([bindings/c/doc])
	fi
],[
	XSPF_DOC_YESNO=no
], [])
AM_CONDITIONAL(GENERATE_DOC, test ${XSPF_DOC_YESNO} = yes)



# Local headers must come very first. Otherwise we
# risk including headers of an already installed
# libxspf version if its path is in CPPFLAGS
CPPFLAGS="-I${srcdir}/include ${CPPFLAGS}"



# Append $prefix as a fallback at the very end
if test "x${prefix}" != "xNONE"; then
	WORKING_PREFIX=${prefix}
else
	WORKING_PREFIX=${ac_default_prefix}
fi
LDFLAGS="${LDFLAGS} -L${WORKING_PREFIX}/lib"
CPPFLAGS="${CPPFLAGS} -I${WORKING_PREFIX}/include"



# Check presence
EXPAT_MISSING="Please install expat 1.95.8 or later.
   On a Debian-based system enter 'sudo apt-get install libexpat-dev'."
AC_CHECK_LIB(expat, XML_ResumeParser,, AC_MSG_ERROR(${EXPAT_MISSING}))
AC_CHECK_HEADER(expat.h,, AC_MSG_ERROR(${EXPAT_MISSING}))

PKG_CHECK_MODULES([URIPARSER], [
	liburiparser >= 0.7.5
], [], [
	AC_MSG_ERROR(Please install uriparser 0.7.5 or later.)
])



## Check for CppTest
if test "${XSPF_TEST_YESNO}" = "yes"; then
	PKG_CHECK_MODULES([CPPTEST], [
		libcpptest >= 1.1.0
	], [], [
		AC_MSG_ERROR(Please install libcpptest 1.1.0 or later.)
	])
fi



AC_OUTPUT(
	xspf.pc
	Makefile
	doc/Makefile
	bindings/c/doc/Makefile
)

cat <<CONFIG
===========================================================================

Configuration
  Prefix ........... ${prefix}
  Test suite ....... ${XSPF_TEST_YESNO}
  Documentation .... ${XSPF_DOC_YESNO}

CONFIG

cat <<"INFO"
Continue with
  make
  make check
  sudo make install

INFO
