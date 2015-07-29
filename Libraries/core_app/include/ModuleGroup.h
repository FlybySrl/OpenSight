#ifndef MODULEGROUP_H
#define MODULEGROUP_H

#include <Module.h>
#include <ModuleGroupGUI.h>
#include <ModuleManager.h>
#include <SettingsDefs.h>

namespace fby
{
/**
 * @class ModuleGroup
 *
 * @ingroup Modules
 *
 * @brief Collects and manages a set of Modules that share some common features.
 * This class is a Module itself and is allowed to autonomously detect and
 * collect a given type of modules.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT ModuleGroup : public Module
{
    Q_OBJECT

    LOAD_SAVE_CONFIG;

public:

    ModuleGroup(ModuleExecMode p_Mode = MODULE_MODE_CHECK);

    virtual ~ModuleGroup();

    /**
     * @brief AddModule adds a module to the list of managed modules.
     *
     * @note If ths input module is already managed, then no action is
     * performed.
     *
     * @param[in]   p_pModule   Input module.
     */
    virtual void AddModule(ModulePtr p_pModule);

    /**
     * @brief ContainsModule checks if this ModuleGroup manages a specified
     * Module.
     *
     * @param[in]   p_pModule   Input module.
     *
     * @retval  true    if this ModuleGroup manages the input Module.
     * @retval  flast   if this ModuleGroup does not manage the input Module.
     */
    virtual bool ContainsModule(ModulePtr p_pModule);

    /**
     * @brief FindModules finds all the modules of that has a given flag within
     * a given path.
     *
     * @param[in]   p_rsPath    Search path.
     * @param[in]   p_Flags     Modules flag.
     */
    virtual void FindModules(const QString&     p_rsPath,
                             ModuleFlag         p_Flags);

    /**
     * @return the current module or a null object if there is not a current
     * one.
     */
    virtual ModulePtr GetCurrentModule();

    virtual RetFlag Init(ModuleExecMode p_Mode);

    virtual void InitOptions();

    virtual void InitWidgets();

    /**
     * @brief LinkInputPorts links an input port of this ModuleGroup to a
     * specified input port of the managed module. If the input module is no
     * managed by this ModuleGroup then no action is performed.
     *
     * @param[in]   p_iGroupPortInId    Id of the port of this ModuleGroup.
     * @param[in]   p_pModule           Input module. This module must be
     *                                  managed by this ModuleGroup.
     * @param[in]   p_iModulePortInId   Input port of the module to be linked.
     */
    virtual void LinkInputPorts(const int   p_iGroupPortInId,
                                ModulePtr   p_pModule,
                                const int   p_iModulePortInId);

    /**
     * @brief LinkOutputPorts links an output port of this ModuleGroup to a
     * specified output port of the managed module. If the input module is no
     * managed by this ModuleGroup then no action is performed.
     *
     * @param[in]   p_iGroupPortOutId   Id of the port of this ModuleGroup.
     * @param[in]   p_pModule           Input module. This module must be
     *                                  managed by this ModuleGroup.
     * @param[in]   p_iModulePortOutId  Output port of the module to be linked.
     */
    virtual void LinkOutputPorts(const int  p_iGroupPortOutId,
                                 ModulePtr  p_pModule,
                                 const int  p_iModulePortOutId);

    /**
     * @brief RemoveModule removes a module from the list of managed modules and
     * disconnects the signals/slots connections.
     *
     * @param[in]   p_pModule       Input module to be removed.
     */
    virtual void RemoveModule(ModulePtr p_pModule);

    /**
     * @brief SetParentModule propagates the inpt parent module to the managed
     * modules.
     *
     * @param[in]   p_pParent   Input parent module.
     */
    virtual RetFlag SetParentModule(ModulePtr p_pParent);

    /**
     * @brief SetWorkDir sets the work directory of this ModuleGroup and of all
     * the managed modules.
     *
     * @param[in]   p_rsPath    Input path of the work directory.
     */
    virtual void SetWorkDir(const std::string &p_rsPath);

protected:

    virtual RetFlag _ThreadFunction(const int p_iPortId);

protected:

    ModuleList  m_lModules; /**< List of managed modules. */

    ModuleGroupGUI*  m_pwiGUI;

}; // end class ModuleGroup.

DEF_PTR(ModuleGroup);

} // end namespace fby.

#endif // MODULEGROUP_H
