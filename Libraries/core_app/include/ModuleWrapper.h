#ifndef MODULEWRAPPER_H
#define MODULEWRAPPER_H

#include <Module.h>
#include <ModuleWrapperGUI.h>

/******************************************************************************/
/* Macros. */
#define MODULE_WRAPPER_ALLOC_FUN_DEC(name, exp) \
    extern "C"\
    {\
    exp fby::Module* NewWrap##name(const std::string&, fby::ModuleExecMode);\
    }

#define MODULE_WRAPPER_ALLOC_FUN_STRING(name)  (QString("NewWrap") + #name)

#define MODULE_WRAPPER_ALLOC_FUN_IMPL(name) \
fby::Module* NewWrap##name(const std::string& p_rsPath, fby::ModuleExecMode p_Mode)\
{ \
   fby::Module*     l_pResult = new name(p_rsPath, p_Mode); \
   if (l_pResult) \
   {\
      if (l_pResult->CheckLicense() == true) \
      { \
         if (p_Mode != fby::MODULE_MODE_CHECK) \
         {\
            l_pResult->Init(p_Mode);\
         }\
         l_pResult->InitOptions();\
      } \
      else \
      { \
         delete l_pResult; \
         l_pResult = NULL; \
       } \
   }\
   return l_pResult; \
}

namespace fby
{
/**
 * @class ModuleWrapper
 *
 * @brief The ModuleWrapper class is a Module itself and wraps another Module.
 * This class is designed to manage the inputs and outputs of a Module from
 * another Module so that this ModuleWrapper acts as an interface to the managed
 * Module.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT ModuleWrapper : public Module
{
    Q_OBJECT

    LOAD_SAVE_CONFIG

public:

    /**
     * @brief Standard Module's constructor.
     *
     * @param[in]   p_Mode      Module's execution mode.
     */
    ModuleWrapper(ModuleExecMode p_Mode);

    /**
     * @brief Constructor that accepts a name of a Module and a path to a folder
     * in the system where the shared library of the wrapped Module must be.
     * This constructor can be useful to allocate the wrapped Module directly in
     * the constructor of this ModuleWrapper.
     *
     * @param[in]   p_rsName    Name of the shared library of the Module to
     *                          be wrapped.
     * @param[in]   p_rsPath    Path where to find the shared library of the
     *                          wrapped Module.
     * @param[in]   p_Mode      Module's execution mode.
     */
    ModuleWrapper(const std::string&    p_rName,
                  const std::string&    p_rsPath,
                  ModuleExecMode        p_Mode);

    virtual ~ModuleWrapper();

    /**
     * @return the wrapped Module object.
     */
    virtual ModulePtr GetModule();

    /**
     * @brief Init initializes the ModuleWrapper.
     *
     * @warning The default implementation allows only one input and one output
     * port and locks the number of input and output ports. If the user requires
     * a different port management must override this function.
     *
     * @param[in]   p_Mode      Input mode.
     *
     * @return the execution flag.
     */
    virtual RetFlag Init(ModuleExecMode p_Mode);

    virtual void InitWidgets();

    /**
     * @brief SetModule sets the Module to be managed by this class.
     *
     * @warning By default this ModuleWrapper does not perform any link
     * between the input and output ports of the managed Module and this
     * ModuleWrapper.
     *
     * @param[in]   p_pModule       Module to be managed by this
     *                              ModuleWrapper.
     */
    virtual void SetModule(ModulePtr p_pModule);

    /**
     * @brief SetWorkDir sets the work dir of this ModuleWrapper and of the
     * managed Module.
     *
     * @param[in]   p_rsPath    Absolute path of the work directory.
     */
    virtual void SetWorkDir(const std::string &p_rsPath);

protected:

    /**
     * @brief _FilterInput filters the input data and builds the appropriate
     * data to be provided to the managed Module.
     *
     * @note This function is a pure virtual one. Subclasses are responsible of
     * the appropriate filtering of the input Data object.
     *
     * @param[in]   p_pData     Input data to be filtered.
     */
    virtual void _FilterInput(DataPtr p_pData) = 0;

    /**
     * @brief _NotifyModuleInputs is a virtual function to notify the
     * appropriate inputs of the managed Module. This function is automatically
     * called by the _ThreadFunction of this ModuleWrapper after the
     * _FilterInput function.
     *
     * @warning The default implementation is empty: whenever this ModuleWrapper
     * has received one input, it does NOT notify the managed Module. Subclasses
     * must implement their own notification methods.
     */
    virtual void _NotifyModuleInputs();

    /**
     * @brief _ThreadFunction gets the input data coming from the notifying port
     * and performs the input filtering through _FilterInput method. Then this
     * function calls the virtual method _NotifyModuleInputs().
     *
     * @warning If the input port is TRIGGERED_EVENT_PORT_ID or
     * TIMER_EVENT_PORT_ID, then the data are captured from the first input port
     * of this ModuleWrapper.
     */
    virtual RetFlag _ThreadFunction(const int p_iPortId);

protected slots:

    /**
     * @brief slot_ItemSelected is a slot to be called when an item of the
     * QTableWidget of the ModuleDataProcessingGUI has been double-clicked.
     *
     * @param[in]   p_iRow      Row of the double-clicked item.
     * @param[in]   p_iCol      Column of the double-clicked item.
     * @param[in]   p_sText     Text of the selected item. This text can be, for
     *                          instance, the full name of a file to be
     *                          processed.
     */
    virtual void slot_ItemSelected(int p_iRow, int p_iCol, QString p_sText);

protected:

    ModulePtr       m_pModule; /**< Data processing module. */

    ModuleWrapperGUI*    m_pwiGUI;

}; // end class ModuleWrapper.

/** @typedef Generic module allocator function, for the use with modules defined
 * inside a shared library (*.dll, *.so). */
typedef Module* (*ModuleWrapperAllocatorFun)(const std::string&, ModuleExecMode);

DEF_PTR(ModuleWrapper);

} // end namespace fby.

#endif // MODULEDATAPROCESSING_H
