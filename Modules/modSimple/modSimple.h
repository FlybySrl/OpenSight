#ifndef MODSIMPLE_H
#define MODSIMPLE_H

#include <core>
#include <core_app>

#include <osg/Group>

#define MODSIMPLE_EXPORT   __declspec(dllexport)

using namespace fby;

class DataGISSimple : public Data
{
public:

    osg::ref_ptr<osg::Group>    m_pRoot;

}; // end class DataGISSimple.

DEF_PTR(DataGISSimple);

class modSimple : public Module
{
    Q_OBJECT

public:
    modSimple(ModuleExecMode p_Mode);

    RetFlag Init(ModuleExecMode p_Mode);

protected:

    bool _CreateRootNode();

    RetFlag _ThreadFunction(const int p_iPortId);

protected:

    DataGISSimplePtr    m_pMyRender;
};

MODULE_ALLOC_FUN_DEC(modSimple, MODSIMPLE_EXPORT)


#endif // MODSIMPLE_H
