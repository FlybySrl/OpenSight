#include "demoOpenSight.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    demoOpenSight   w;
    QSettings       l_Settings("demoOpenSight.ini", QSettings::IniFormat);

    w.SetAutoSaveConfigOnClose(true, "demoOpenSight.ini");

    w.InitOptions();

    w.SetOption(SETTING_KEY_MODULES_PATH,
                QString("./../mod/")  +
                MACHINE_VERSION_STR + "/" +
                COMPILER_VERSION_STR + "/" +
                QT_VERSION_STR);

    w.SetOption(SETTING_KEY_ICONS_PATH,
                QString("./../icons"));

    w.LoadConfig(l_Settings);

    w.ConfigWidgets();

    w.Start();

    return a.exec();
}
