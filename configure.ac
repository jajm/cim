AC_PREREQ([2.67])
LT_PREREQ([2.2])

AC_INIT(cim, [0.0.1], [jajm@jajm.org])
LT_INIT()

AC_SUBST(LIBTOOL_CURRENT, 0)
AC_SUBST(LIBTOOL_REVISION, 0)
AC_SUBST(LIBTOOL_AGE, 0)

AC_PROG_CC
AC_CHECK_HEADERS([stdlib.h stdio.h string.h stdbool.h])

PKG_CHECK_MODULES(EMBODY, [embody >= 1.2])
PKG_CHECK_MODULES(SDS, [sds])
PKG_CHECK_MODULES(LIBGENDS, [libgends >= 2])

BUILD_TESTS=no
PKG_CHECK_MODULES(LIBTAP13, [libtap13], [BUILD_TESTS=yes], [BUILD_TESTS=no])
AC_SUBST(BUILD_TESTS)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	include/Makefile
	t/Makefile
	config.mk
	cim.pc
])

AC_OUTPUT
