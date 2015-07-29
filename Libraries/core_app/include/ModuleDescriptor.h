#ifndef MODULE_DESCRIPTOR_H
#define MODULE_DESCRIPTOR_H

/** @file ModuleDescriptor.h
 *
 * @brief Contains the declarations of the ModuleDescriptor class.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

#include <ModuleWrapper.h>

namespace fby
{
/**
 * @class ModuleDescriptor
 *
 * @brief Contains a set of data and methods to properly define a Module
 * together with its dynamic library.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT ModuleDescriptor : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Default constructor: builds an empty ModuleDescriptor.
     */
    ModuleDescriptor();

    /**
     * @brief Builds a new ModuleDescriptor from the input shared library name
     * together with its path.
     *
     * @param[in]   p_rsSharedLibName   Name of the shared library that contains
     *                                  the implementation of the Module.
     * @param[in]   p_rsPath            Path of the shared library.
     */
    ModuleDescriptor(const QString&   p_rsSharedLibName,
                     const QString&   p_rsPath);

    /**
     * @brief Copy constructor.
     */
    ModuleDescriptor(const ModuleDescriptor& p_rModuleDescriptor);

    ModuleDescriptor& operator = (const ModuleDescriptor& p_rModuleDescriptor);

    /**
     * @brief Performs the deallocation of the modules before unloading the
     * dynamic library. */
    ~ModuleDescriptor();

    /**
     * @brief Initializes this ModuleDescriptor with the name of the shared
     * library together with its path.
     *
     * @param[in]   p_rsSharedLibName   Name of the shared library that contains
     *                                  the implementation of the Module.
     * @param[in]   p_rsPath            Path of the shared library.
     */
    void    Init(const QString&   p_rsSharedLibName,
                 const QString&   p_rsPath);

    /**
     * @brief Returns a new instance of a ModulePtr calling the approriate
     * method inside the loaded shared library. If the shared library is not
     * loaded then a null object is returned.
     *
     * @param[in]   p_Mode      Execution mode of the newly created Module.
     *
     * @return The newly created module or a null pointer if something went
     * wrong.
     */
    ModulePtr   New(ModuleExecMode p_Mode);

    /**
     * @overload
     *
     * @param[in]   p_rsPath    Input path.
     * @param[in]   p_Mode      Execution mode of the newly created Module.
     *
     * @return The newly created module or a null pointer if something went
     * wrong.
     */
    ModulePtr   New(const std::string&  p_rsPath,
                    ModuleExecMode      p_Mode);

protected:

    SharedLibPtr    m_pSharedLib; /**< Holds a pointer to the shared library
                                   * that defines the implementation of the
                                   * Module. */

    QString     m_strSharedLibName; /**< Name of the shared library. */

    QString     m_strPath; /**< Path of the shared library. */

    ModuleAllocatorFun  m_funAllocator; /**< Module Allocator function to be
                                         * resolved through the shared library. */

    ModuleWrapperAllocatorFun  m_funAllocatorWrap;
                                        /**< ModuleWrapper Allocator function to
                                         * be resolved through the shared
                                         * library. */

    QString     m_sModuleName; /**< Module name, to be used when resolving
                                  * the module allocator function in the dynamic
                                  * library. */

    int     m_iCreatedModules; /**< Number of created modules from the same
                                * shared library. */

}; // end class ModuleDescriptor.

DEF_PTR(ModuleDescriptor);

} // end namespace fby.

#endif // MODULE_DESCRIPTOR_H
