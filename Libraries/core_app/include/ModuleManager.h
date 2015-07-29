#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

/** @file ModuleManager.h
 *
 * @brief Contains the data and methods to manage the Modules compiled as
 * shared libraries.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

#include <ModuleDescriptor.h>

namespace fby
{
/******************************************************************************/
/* Forward declarations. */
class CORE_APP_EXPORT ModuleManager;
DEF_PTR(ModuleManager);

/** Manages the available modules and their relative *.dlls. This class is
implemented as a singleton since, for each application there can be only one
module manager object. */
class CORE_APP_EXPORT ModuleManager
{
public:

    /**
     * @return a list with the names of the available modules. */
    static QStringList  AvailableModules();

    /**
     * @brief Detects all the available modules in the specified path and
     * stores their configuration in the internal map.
     *
     * @param[in]   p_rstrPath  Path to the folder where the Modules are sought.
     * @param[in]   p_Mode      Execution mode to check the Modules validity.
     */
    static void FindModules(const QString&  p_rstrPath,
                            ModuleExecMode  p_Mode);

    /**
     * @brief Detects specified modules in the specified path and stores their
     * configuration in the internal map.
     *
     * @param[in]   p_rstrPath      Path to the folder where the Modules are
     *                              sought.
     * @param[in]   p_rlModuleName  List of name of the required modules.
     * @param[in]   p_Mode          Execution mode to check the Modules validity.
     */
    static void     FindModules(const QString&      p_rstrPath,
                                const QStringList&  p_rlModuleNames,
                                ModuleExecMode      p_Mode);

    /**
     * @brief Returns a new instance of the specified module, if available.
     * Otherwise returns a null object.
     *
     * @param[in]   p_rsModuleName      Name of the module to be instantiated.
     * @param[in]   p_Mode              Execution mode of the new Module.
     *
     * @return The newly instantiated module or a null pointer if something
     * was wrong.
     */
    static ModulePtr    New(const QString&  p_rsModuleName,
                            ModuleExecMode  p_Mode);

    /**
     * @brief Returns a new instance of the specified module, if available.
     * Otherwise returns a null object.
     *
     * @param[in]   p_rsModuleName      Name of the module to be instantiated.
     * @param[in]   p_rsPath            Path to be provided to the constructor
     *                                  of the Module.
     * @param[in]   p_Mode              Execution mode of the new Module.
     *
     * @return The newly instantiated module or a null pointer if something
     * was wrong.
     */
    static ModulePtr    NewWrapper(const QString&   p_rsModuleName,
                                   const QString&   p_rsPath,
                                   ModuleExecMode   p_Mode);

protected:

    static ModuleManagerPtr     m_pInstance; /**< Unique instance of the module
                                              * manager. */

    static QMap<QString, ModuleDescriptorPtr> m_mapAvailableModules; /** Set of
                                              * available modules. */

    static std::map<ModuleId, ModulePtr>    m_mapIdModule; /** Map Id-module. */

protected:

    /** @brief Protected constructor to prevent direct instantiation.
     */
    ModuleManager();

    /** @brief Returns the unique instance of the ModuleManager class. This
     * function is protected so that the user can use only the interface
     * (public) member functions without accessing the instance itself.
     *
     * @return The unique instance of the ModuleManager object.
     */
    static ModuleManagerPtr _Instance();

}; // end class ModuleManager.

} // end namespace fby.

#endif // MODULE_MANAGER_H
