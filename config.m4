PHP_ARG_ENABLE(mmseg,
	[Whether to enable mmseg support],
	[	--enable-mmseg		Enable mmseg support])

if test "$PHP_MMSEG" = "yes"; then
	PHP_REQUIRE_CXX()
	PHP_SUBST(MMSEG_SHARED_LIBADD)
	PHP_ADD_LIBRARY(stdc++, 1, MMSEG_SHARED_LIBADD)
	PHP_ADD_INCLUDE(mmseg-cpp)
	PHP_NEW_EXTENSION(mmseg, mmseg.cpp mmseg-cpp/algor.cpp mmseg-cpp/dict.cpp mmseg-cpp/memory.cpp, $ext_shared)
fi
