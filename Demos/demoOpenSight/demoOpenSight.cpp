#include "demoOpenSight.h"

demoOpenSight::demoOpenSight(QWidget* p_pParent, Qt::WindowFlags p_Flags)
    : AppBase(p_pParent, p_Flags)
{
    /* Empty. */
}

demoOpenSight::~demoOpenSight()
{
    /* Empty. */
}

void demoOpenSight::ConfigModules()
{
    QDir    l_dirModules;

    l_dirModules.setPath(GetOption(SETTING_KEY_MODULES_PATH).toString());

    ModuleManager::FindModules(l_dirModules.absolutePath(),
                               QStringList()
                               << "modEarth"
                               << "modSimple",
                               MODULE_MODE_CHECK);

    if (!m_pEarth)
    {
        m_pEarth = ModuleManager::New("modEarth", MODULE_MODE_CHECK);
    }

    if (!m_pSimple)
    {
        m_pSimple = ModuleManager::New("modSimple", MODULE_MODE_CHECK);
    }

    if (m_pEarth)
    {
        AddModule(m_pEarth);
    }

    if (m_pSimple)
    {
        AddModule(m_pSimple);
    }
}

void demoOpenSight::ConfigWidgets()
{
    if (m_pEarth)
    {
        m_pEarth->Init(MODULE_MODE_WIDGET);

        if (m_pEarth->GetWidget(0))
        {
            GetDockWidgetLayout(Qt::LeftDockWidgetArea)
                    ->addWidget(m_pEarth->GetWidget(0),
                                0,
                                0,
                                1,
                                1);

            m_pEarth->GetWidget(0)->setSizePolicy(
                        QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
        }

        if (m_pEarth->GetWidget(1))
        {
            setCentralWidget(m_pEarth->GetWidget(1));
        }
    }
    else
    {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("Invalid modEarth"));

        exit(-1);
    }

    if (m_pSimple)
    {
        m_pSimple->Init(MODULE_MODE_WIDGET);

        if (m_pSimple->GetWidget(0))
        {
            GetDockWidgetLayout(Qt::LeftDockWidgetArea)
                    ->addWidget(m_pSimple->GetWidget(0),
                                0,
                                0,
                                1,
                                1);

            m_pSimple->GetWidget(0)->setSizePolicy(
                        QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
        }
    }
    else
    {
        QMessageBox::critical(
                    this,
                    tr("Error"),
                    tr("Invalid modSimple"));

        exit(-1);
    }

    if (m_pEarth && m_pSimple)
    {
        m_pEarth->AddInput(1);

        g_LinkModules(m_pSimple, 0, m_pEarth, 0);
    }

    show();
}

void demoOpenSight::Start()
{
    AppBase::Start();

    if (m_pSimple)
    {
        m_pSimple->Trigger();
    }
}

void demoOpenSight::slot_WidgetModified()
{
    ConfigWidgets();
}
