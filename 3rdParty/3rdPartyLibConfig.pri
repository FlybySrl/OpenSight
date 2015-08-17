isEmpty(MACHINE_VERSION) {
   message("The symbol MACHINE_VERSION is not defined. Using default: MACHINE_VERSION = x86")
   MACHINE_VERSION = x86
}

isEmpty(COMPILER_VERSION) {
   message("The symbol COMPILER_VERSION is not defined. Using default: COMPILER_VERSION = vc10")
	 windows: COMPILER_VERSION = vc10
   unix:  COMPILER_VERSION = gcc
}

warning("---------- Running configuration for" $$TARGET "----------")
warning("Machine:" $$MACHINE_VERSION)
warning("Compiler:" $$COMPILER_VERSION)
#warning("========== End configuration ==========")

# OSGConfig must be included before OpenCVConfig.pri and GDALConfig.pri.
WITH_OSG: include ($$PWD/osg/OSGConfig.pri)
WITH_OPENCV: include ($$PWD/opencv/OpenCVConfig.pri)
WITH_GDAL: include ($$PWD/gdal/GDALConfig.pri)
WITH_TBB: include ($$PWD/tbb/TbbConfig.pri)
WITH_UNIX: include($$PWD/unix/UnixLibConfig.pri)
WITH_WINDOWS: include ($$PWD/windows/WindowsLibConfig.pri)
