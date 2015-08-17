# ============================================================================ #
# Dependencies to the Flysight libraries.

isEmpty(FLYSIGHT_DEPEND) {
   warning("No dependencies from the Flysight libraries.")
} else {

   equals(TEMPLATE, app) {
      CONFIG *= DO_LINK
   } # end equals(TEMPLATE, app)

   equals(TEMPLATE, lib) {
      dll {
         CONFIG *= DO_LINK
      }
   } # end equals(TEMPLATE, app)

   # ========================================================================= #
   # Third party dependencies.

   contains(FLYSIGHT_DEPEND, core) {
      # No third-party dependencies.
   }

   contains(FLYSIGHT_DEPEND, core_app) {
      QT     *= core gui opengl
      CONFIG *= qt
      CONFIG *= core_app_WITH_QT_SUFFIX
   }

   contains(FLYSIGHT_DEPEND, core_geo) {
      CONFIG *= WITH_EIGEN
      CONFIG *= WITH_GDAL
      CONFIG *= WITH_LIBEXIF
      CONFIG *= WITH_OPENCV
      CONFIG *= WITH_TBB
      windows: CONFIG *= WITH_WINDOWS
   }

   contains(FLYSIGHT_DEPEND, core_gis) {
      CONFIG *= WITH_EIGEN
      CONFIG *= WITH_GDAL
      CONFIG *= WITH_LIBEXIF
      CONFIG *= WITH_OPENCV
      CONFIG *= WITH_OSG
      CONFIG *= WITH_OSGEARTH
      CONFIG *= WITH_TBB
      windows: CONFIG *= WITH_WINDOWS
      QT     *= core gui opengl
      CONFIG *= qt
      CONFIG *= core_gis_WITH_QT_SUFFIX
   }

   contains(FLYSIGHT_DEPEND, core_imgproc) {
      CONFIG *= WITH_EIGEN
      CONFIG *= WITH_LIBEXIF
      CONFIG *= WITH_OPENCV
      CONFIG *= WITH_TBB
      windows: CONFIG *= WITH_WINDOWS
   }

   contains(FLYSIGHT_DEPEND, core_license) {
      windows: CONFIG *= WITH_WINDOWS
   }

   contains(FLYSIGHT_DEPEND, core_network) {
      # No third-party dependencies.
      windows: CONFIG *= WITH_WINDOWS
   }

   contains(FLYSIGHT_DEPEND, core_opt) {
      CONFIG *= WITH_EIGEN
      CONFIG *= WITH_SUITESPARSE
      CONFIG *= WITH_TBB
   }

   contains(FLYSIGHT_DEPEND, core_video) {
      QT     *= core gui opengl
      CONFIG *= qt
      CONFIG *= core_video_WITH_QT_SUFFIX
   }

#   contains(FLYSIGHT_DEPEND, fusion) {
#      CONFIG *= WITH_OPENCV
#   }

#   contains(FLYSIGHT_DEPEND, mosaic) {
#      CONFIG *= WITH_OPENCV
#   }

#   contains(FLYSIGHT_DEPEND, mvs) {
#      CONFIG *= WITH_GDAL
#      CONFIG *= WITH_EIGEN
#      CONFIG *= WITH_LIBEXIF
#      CONFIG *= WITH_OPENCV
#      CONFIG *= WITH_SUITESPARSE
#      CONFIG *= WITH_TBB
#   }

   contains(FLYSIGHT_DEPEND, osgQt) {
      QT     *= core gui opengl widgets
      CONFIG *= qt
      CONFIG *= osgQt_WITH_QT_SUFFIX
      CONFIG *= WITH_OSG
   }

#   contains(FLYSIGHT_DEPEND, superres) {
#      CONFIG *= WITH_OPENCV
#      CONFIG *= WITH_TBB
#   }

   contains(FLYSIGHT_DEPEND, video) {
      CONFIG *= WITH_FFMPEG
      CONFIG *= WITH_OPENCV
      windows: CONFIG *= WITH_WINDOWS
   }

   for(fLib, FLYSIGHT_DEPEND): {

      warning($$TARGET "depends on Flysight library" $$fLib)

      contains (CONFIG, $$join(fLib,,,_WITH_QT_SUFFIX)) {
         PATH_SUFFIX = $$QT_VERSION
      } else {
         PATH_SUFFIX =
      }

      # Updates the include path.
      INCLUDEPATH += $$PWD/Libraries/$$fLib/include

      DO_LINK {

         # Sets the dependency path to the libraries.
         DEPENDPATH += $$PWD/$$LIB_PATH/$$PATH_SUFFIX
         LIBS *= -L$$PWD/$$LIB_PATH/$$PATH_SUFFIX

         # Updates the pre-target dependencies.
         CONFIG(debug, debug|release) {
            unix {
               exists($$PWD/lib/$$PATH_SUFFIX/$$join(fLib,,lib,d.a)) {
                  PRE_TARGETDEPS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,lib,d.a)
               }
            }

            windows {
               exists($$PWD/lib/$$PATH_SUFFIX/$$join(fLib,,,d.lib)) {
                  PRE_TARGETDEPS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,,d.lib)
               }
            }

            LIBS *= -l$$join(fLib,,,d)

            equals (TEMPLATE, app) {
               equals (fLib, core_license) {
#                  Doesn't add the library
               } else {
                  android: ANDROID_EXTRA_LIBS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,lib,d.so)
               }
            }

         } else {
            unix {
               exists($$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,lib,.a)) {
                  PRE_TARGETDEPS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,lib,.a)
               }
            }

            windows {
               exists($$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,,.lib)) {
                  PRE_TARGETDEPS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,,.lib)
               }
            }

            LIBS *= -l$$fLib


            equals (TEMPLATE, app) {
               equals (fLib, core_license) {
#                  Doesn't add the library
               } else {
                  android: ANDROID_EXTRA_LIBS *= $$PWD/$$LIB_PATH/$$PATH_SUFFIX/$$join(fLib,,lib,.so)
               }
            }

         } # end CONFIG(debug, debug|release)

      } # end DO_LINK

   } # end for(fLib, FLYSIGHT_DEPEND)

} # end isEmpty(FLYSIGHT_DEPEND)
