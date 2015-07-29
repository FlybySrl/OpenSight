#ifndef DEMOOPENSIGHT_H
#define DEMOOPENSIGHT_H

#include <core>
#include <core_app>

using namespace fby;

class demoOpenSight : public AppBase
{
    Q_OBJECT

public:
    demoOpenSight(QWidget* p_pParent = 0, Qt::WindowFlags p_Flags = 0);
    ~demoOpenSight();

    void ConfigModules();

    void ConfigWidgets();

    void Start();

protected slots:

    void slot_WidgetModified();

protected:

    ModulePtr       m_pEarth;
    ModulePtr       m_pSimple;
};

#endif // DEMOOPENSIGHT_H
