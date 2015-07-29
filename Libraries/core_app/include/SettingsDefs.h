#ifndef SETTINGSDEFS_H
#define SETTINGSDEFS_H

#include <core_app_pch.h>

/** @file SettingsDefs
 *
 * @brief Contains the definitions of the common settings string to be used in
 * combination with QSettings to configure an application through an *.ini
 * file. Specific settings (e. g. specific settings of a module) must be defined
 * in other files.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

/* QSettings values common keys. **********************************************/
#define SETTING_KEY_3D_MODEL                        QString("3dModel")
#define SETTING_KEY_ALTITUDE                        QString("Altitude")
#define SETTING_KEY_ANGLE_SPAN                      QString("AngleSpan")
#define SETTING_KEY_BAUDRATE                        QString("BaudRate")
#define SETTING_KEY_BUFFER_SIZE                     QString("BufferSize")
#define SETTING_KEY_CENTER_ALTITUDE                 QString("CenterAltitude")
#define SETTING_KEY_CENTER_LATITUDE                 QString("CenterLatitude")
#define SETTING_KEY_CENTER_LONGITUDE                QString("CenterLongitude")
#define SETTING_KEY_CHARACTER_SIZE                  QString("CharacterSize")
#define SETTING_KEY_COL_STRETCH                     QString("ColStretch")
#define SETTING_KEY_DECIMATION_VALUE                QString("DecimationValue")
#define SETTING_KEY_DELTA_TIME                      QString("DeltaTime")
#define SETTING_KEY_DTED_LEVEL                      QString("DTEDLevel")
#define SETTING_KEY_EAST                            QString("East")
#define SETTING_KEY_ELEVATION_LAYERS                QString("ElevationLayers")
#define SETTING_KEY_ELEVATION_LAYERS_NUM            QString("ElevationLayersNum")
#define SETTING_KEY_ENABLED                         QString("Enabled")
#define SETTING_KEY_FLOATING                        QString("Floating")
#define SETTING_KEY_FOOTPRINT_COLOR                 QString("FootprintColor")
#define SETTING_KEY_FRAMED                          QString("Framed")
#define SETTING_KEY_GEOMETRY                        QString("Geometry")
#define SETTING_KEY_HEADING                         QString("Heading")
#define SETTING_KEY_ICON_FILE                       QString("IconFile")
#define SETTING_KEY_ICONS_PATH                      QString("IconsPath")
#define SETTING_KEY_INNER_RADIUS                    QString("InnerRadius")
#define SETTING_KEY_LABEL_COLOR                     QString("LabelColor")
#define SETTING_KEY_LAST_PATH                       QString("LastPath")
#define SETTING_KEY_LATITUDE                        QString("Latitude")
#define SETTING_KEY_LATITUDE_MIN                    QString("LatitudeMax")
#define SETTING_KEY_LATITUDE_MAX                    QString("LatitudeMin")
#define SETTING_KEY_LINE_WIDTH                      QString("LineWidth")
#define SETTING_KEY_LONGITUDE                       QString("Longitude")
#define SETTING_KEY_LONGITUDE_MAX                   QString("LongitudeMax")
#define SETTING_KEY_LONGITUDE_MIN                   QString("LongitudeMin")
#define SETTING_KEY_MAX_BANK_ANGLE                  QString("MaxBankAngle")
#define SETTING_KEY_MODULES_PATH                    QString("ModulesPath")
#define SETTING_KEY_NORTH                           QString("North")
#define SETTING_KEY_OFFSET_X                        QString("OffsetX")
#define SETTING_KEY_OFFSET_Y                        QString("OffsetY")
#define SETTING_KEY_OFFSET_Z                        QString("OffsetZ")
#define SETTING_KEY_OFFSET_ROT_X                    QString("OffsetRotX")
#define SETTING_KEY_OFFSET_ROT_Y                    QString("OffsetRotY")
#define SETTING_KEY_OFFSET_ROT_Z                    QString("OffsetRotZ")
#define SETTING_KEY_OUTER_RADIUS                    QString("OuterRadius")
#define SETTING_KEY_PATH_COLORS                     QString("PathColors")
#define SETTING_KEY_PITCH                           QString("Pitch")
#define SETTING_KEY_POINT_SIZE                      QString("PointSize")
#define SETTING_KEY_RANGE                           QString("Range")
#define SETTING_KEY_ROAD_DISTANCE_THR               QString("RoadDistanceThr")
#define SETTING_KEY_ROAD_FILES                      QString("RoadFiles")
#define SETTING_KEY_ROAD_FILES_NUM                  QString("RoadFilesNum")
#define SETTING_KEY_ROW_STRETCH                     QString("RowStretch")
#define SETTING_KEY_ROLL                            QString("Roll")
#define SETTING_KEY_SCALE                           QString("Scale")
#define SETTING_KEY_SCALE_TO_SCREEN                 QString("ScaleToScreen")
#define SETTING_KEY_SENSOR                          QString("Sensor")
#define SETTING_KEY_SERIAL_PORT                     QString("SerialPort")
#define SETTING_KEY_SIDE                            QString("Side")
#define SETTING_KEY_SIZE                            QString("Size")
#define SETTING_KEY_SOUTH                           QString("South")
#define SETTING_KEY_STATE                           QString("State")
#define SETTING_KEY_THRESHOLD                       QString("Threshold")
#define SETTING_KEY_TIME_DECIMATION                 QString("TimeDecimation")
#define SETTING_KEY_TITLE                           QString("Title")
#define SETTING_KEY_VEHICLE                         QString("Vehicle")
#define SETTING_KEY_VISIBLE                         QString("Visible")
#define SETTING_KEY_WEIGHT                          QString("Weight")
#define SETTING_KEY_WEST                            QString("West")
#define SETTING_KEY_WORK_DIR                        QString("WorkDir")
#define SETTING_KEY_YAW                             QString("Yaw")



/* QSettings groups common keys. **********************************************/
#define SETTING_GROUP_MAINWINDOW    QString("MainWindow")
#define SETTING_GROUP_MENU          QString("Menu")
#define SETTING_GROUP_MODULES       QString("Modules")
#define SETTING_GROUP_TOOLBAR       QString("ToolBar")
#define SETTING_GROUP_STATUSBAR     QString("StatusBar")
#define SETTING_GROUP_VIEWPOINT     QString("Viewpoint")
#define SETTING_GROUP_WIDGET        QString("Widget")

#endif // SETTINGSDEFS_H
