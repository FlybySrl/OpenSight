# This CONFIG is to speed up qmake for Qt version greater or equal to 5.0.0
CONFIG -= depend_includepath

# This flag is to allow a larger amount of memory for Windows applications:
# - 3.0 GB for 32-bits applications in 32-bit environment.
# - 4.0 GB for 32-bits applications in 64-bit environment.
# - 8.0 TB for 64-bits applications in 64-bit environment.
windows: QMAKE_LFLAGS *= /LARGEADDRESSAWARE

# This flag enables the multicore parallel build.
windows: QMAKE_CXXFLAGS *= /MP

CONFIG(debug, debug|release) {
   # This flag is to avoid the following error:
   #
   # LINK : fatal error LNK1123: failure during conversion to COFF: file invalid
   # or corrupt.
   #
   # when building in debug mode.
   windows: QMAKE_LFLAGS *= /INCREMENTAL:NO
} else {
   # Enables parallel operations.
   equals(MACHINE_VERSION, x86) {
      windows:QMAKE_CXXFLAGS_RELEASE *= /openmp
      DEFINES *= USE_OPENMP
   }
}

exists($$PWD/UserConfig.pri) {
   warning(Using configuration file $$PWD/UserConfig.pri)
   include($$PWD/UserConfig.pri)
}

DEFINES *= COMPILER_VERSION_STR=\\\"$$COMPILER_VERSION\\\"
DEFINES *= MACHINE_VERSION_STR=\\\"$$MACHINE_VERSION\\\"

contains (CONFIG, qt) {
   QT_SUFFIX = $$QT_VERSION
} else {
   QT_SUFFIX =
}

VERSION_SUFFIX = $$MACHINE_VERSION/$$COMPILER_VERSION

BIN_PATH = bin/$$VERSION_SUFFIX
LIB_PATH = lib/$$VERSION_SUFFIX
MOD_PATH = mod/$$VERSION_SUFFIX


# ============================================================================ #
# Applications configuration. ================================================ #

equals(TEMPLATE, app) {
   demo {
      DESTDIR = $$PWD/$$BIN_PATH/demos/$$TARGET/$$QT_SUFFIX
   } else {
      test {
         DESTDIR = $$PWD/$$BIN_PATH/tests/$$TARGET/$$QT_SUFFIX
      } else {
         extern {
            DESTDIR = $$PWD/ext/$$EXTERN_ROOT_NAME/$$BIN_PATH/$$QT_SUFFIX
         } else {
            DESTDIR = $$PWD/$$BIN_PATH/$$TARGET/$$QT_SUFFIX
         } # end extern
      } # end test
   } # end demo

   # Sets the path where to search for the shared libraries.
   LIBS *= -L$$PWD/$$BIN_PATH
   LIBS *= -L$$PWD/$$BIN_PATH/$$QT_SUFFIX
   LIBS *= -L$$PWD/$$BIN_PATH/3rdParty
   CONFIG (debug, debug|release) {
      LIBS *= -L$$PWD/$$BIN_PATH/3rdParty/Debug
   } else {
      LIBS *= -L$$PWD/$$BIN_PATH/3rdParty/Release
   } # end CONFIG (debug, debug|release).

} # end equals(TEMPLATE, app)


# ============================================================================ #
# Libraries configuration. =================================================== #

equals(TEMPLATE, lib) {

   contains(CONFIG, flysight_lib) {
      FLYSIGHT_LIBRARY_STATIC: {
         CONFIG *= staticlib
         DEFINES *= $$join(TARGET,,,_LIBRARY_STATIC)
      } else {
         CONFIG *= dll
         DEFINES *= $$join(TARGET,,,_LIBRARY_SHARED)
         unix: CONFIG *= plugin
         windows: CONFIG *= WITH_WINDOWS
      }
   } # end contains(CONFIG, flysight_lib).

   extern {
      dll {
         DESTDIR = $$PWD/ext/$$EXTERN_ROOT_NAME/$$LIB_PATH/$$QT_SUFFIX
         windows: DLLDESTDIR = $$PWD/ext/$$EXTERN_ROOT_NAME/$$BIN_PATH/$$QT_SUFFIX
      } # end dll

      staticlib {
         DESTDIR = $$PWD/ext/$$EXTERN_ROOT_NAME/$$LIB_PATH/$$QT_SUFFIX
      }
   } else {

      flysight_module {

         isEmpty(MODULE_LIBRARY_STATIC) {
            CONFIG *= dll
            DEFINES *= MODULE_LIBRARY_SHARED
         } else {
            CONFIG *= staticlib
            DEFINES *= MODULE_LIBRARY_STATIC
         }

         CONFIG *= dll
         DESTDIR = $$PWD/$$MOD_PATH/$$QT_SUFFIX
         windows: DLLDESTDIR = $$PWD/$$MOD_PATH/$$QT_SUFFIX

      } else {
         dll {
            DESTDIR = $$PWD/$$LIB_PATH/$$QT_SUFFIX
            windows: DLLDESTDIR = $$PWD/$$BIN_PATH/$$QT_SUFFIX
         } # end dll
      } # end module

      staticlib {
         contains (CONFIG, flysight_module) {
            # DESTDIR has already been set.
         } else {
            DESTDIR = $$PWD/$$LIB_PATH/$$QT_SUFFIX
         }
      } # end staticlib

   } # end extern

   unix: {
      dll: CONFIG *= plugin
   }

} # end equals(TEMPLATE, lib)

include($$PWD/LibrariesConfig.pri)


# ============================================================================ #
# Target name for the debug build configuration. ============================= #

CONFIG(debug, debug|release) {
   TARGET = $$join(TARGET,,,d)
} # end CONFIG(debug, debug|release)


# ============================================================================ #
# Third party libraries configuration. ======================================= #

isEmpty(LOCAL_LIBS_ROOT) {
   unix: THIRD_PARTY_LIBS_ROOT = /mnt/server/Progetti/FLYSIGHT/COMMON_LIBS/3rdPartyBuild
   windows: THIRD_PARTY_LIBS_ROOT = Z:/Progetti/FLYSIGHT/COMMON_LIBS/3rdPartyBuild
} else {
   THIRD_PARTY_LIBS_ROOT = $$LOCAL_LIBS_ROOT
} # end isEmpty(LOCAL_LIBS_ROOT)

exists($$THIRD_PARTY_LIBS_ROOT/3rdPartyLibConfig.pri) {
   include($$THIRD_PARTY_LIBS_ROOT/3rdPartyLibConfig.pri)
}
