#include "modSimple.h"
#include <osgDB/ReadFile>
#include <osg/CoordinateSystemNode>
#include <osg/PositionAttitudeTransform>

modSimple::modSimple(ModuleExecMode p_Mode)
    : Module(p_Mode),
      m_pMyRender(new DataGISSimple)
{
    /* Empty. */
}

RetFlag modSimple::Init(ModuleExecMode p_Mode)
{
    RetFlag    l_Result;

    l_Result = Module::Init(p_Mode);

    INIT_MAIN_TIMER_CONNECTION;
    INIT_TRIGGER_CONNECTION;

    AddOutput(m_pMyRender);

    return l_Result;
}

bool modSimple::_CreateRootNode()
{
    osg::ref_ptr<osg::PositionAttitudeTransform>    l_pTransf;
    osg::ref_ptr<osg::Node>                         l_pNode;
    osg::EllipsoidModel                             l_Ell;
    osg::Vec3d                                      l_vCenter;
    osg::Quat                                       l_qAttitude;
    osg::Matrixd                                    l_mLocalToWorld;
    double                                          l_dLatitude_deg;
    double                                          l_dLongitude_deg;
    double                                          l_dAltitude_m;
    bool                                            l_bNotify;

    l_bNotify = false;

    l_dLatitude_deg = 43.5066342;
    l_dLongitude_deg = 10.3224053;
    l_dAltitude_m = 19.0;

    LOCK_WRITE(&m_Mutex, l_Lock);

    if (m_pMyRender)
    {
        {
            LOCK_WRITE(&m_pMyRender->m_Mutex, l_LockMyRender);

            if (!m_pMyRender->m_pRoot)
            {
                l_pTransf = new osg::PositionAttitudeTransform;

                m_pMyRender->m_pRoot = l_pTransf;

                l_pNode = osgDB::readRefNodeFile("c:/Flyby/Data/3dModels/cessna.osg");

                if (l_pNode)
                {
                    m_pMyRender->m_pRoot->addChild(l_pNode);

                    l_bNotify = true;
                }
                else
                {
                    m_pMyRender->m_pRoot.release();

                    l_bNotify = false;
                }

                if (l_bNotify == true)
                {
                    l_Ell.convertLatLongHeightToXYZ(
                                DEG_TO_RAD(l_dLatitude_deg),
                                DEG_TO_RAD(l_dLongitude_deg),
                                l_dAltitude_m,
                                l_vCenter.x(),
                                l_vCenter.y(),
                                l_vCenter.z());

                    l_Ell.computeLocalToWorldTransformFromLatLongHeight(
                                DEG_TO_RAD(l_dLatitude_deg),
                                DEG_TO_RAD(l_dLongitude_deg),
                                l_dAltitude_m,
                                l_mLocalToWorld);

                    l_mLocalToWorld.get(l_qAttitude);

                    if (l_pTransf)
                    {
                        l_pTransf->setPosition(l_vCenter);
                        l_pTransf->setAttitude(l_qAttitude);
                    }
                }
            }
        }

        m_pMyRender->SetId("MyRender Id");

        m_pMyRender->AddProperty(SETTING_KEY_CENTER_LATITUDE.toStdString(),
                                 l_dLatitude_deg);

        m_pMyRender->AddProperty(SETTING_KEY_CENTER_LONGITUDE.toStdString(),
                                 l_dLongitude_deg);

        m_pMyRender->AddProperty(SETTING_KEY_CENTER_ALTITUDE.toStdString(),
                                 l_dAltitude_m);
    }

    return l_bNotify;
}

RetFlag modSimple::_ThreadFunction(const int p_iPortId)
{
    RetFlag     l_Result;
    bool        l_bNotify;

    l_Result = RET_SUCCESS;
    l_bNotify = false;

    switch (p_iPortId)
    {
    case TIMER_EVENT_PORT_ID:
    case TRIGGERED_EVENT_PORT_ID:
    default:
        l_bNotify = _CreateRootNode();
        break;
    } // end switch.

    if (l_bNotify == true)
    {
        NotifyOutput(m_pMyRender);
    }

    return l_Result;
}

MODULE_ALLOC_FUN_IMPL(modSimple)
