#ifndef MODULE_H
#define MODULE_H

/** @file Module.h
 *
 * @brief Contains the definition of the Module class that is the basic class
 * of a Flysight application.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

#include <ModulePort.h>

/******************************************************************************/
/* Macros. */

#define INIT_MAIN_TIMER_CONNECTION \
connect(&m_timerMain,\
    SIGNAL(timeout()),\
    this,\
    SLOT(slot_TimerTimeout()),\
    Qt::QueuedConnection)

#define INIT_TRIGGER_CONNECTION \
connect(this,\
        SIGNAL(sig_Trigger(int)),\
        SLOT(slot_Triggered(int)),\
        Qt::QueuedConnection);

#define MODULE_ALLOC_FUN_DEC(name, exp) \
    extern "C"\
    {\
    exp fby::Module* New##name(fby::ModuleExecMode);\
    }

#define MODULE_ALLOC_FUN_STRING(name)  (QString("New") + #name)

#define MODULE_ALLOC_FUN_IMPL(name) \
fby::Module* New##name(fby::ModuleExecMode p_Mode) \
{ \
   fby::Module*     l_pResult = new name(p_Mode); \
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

#define INPUT_DATA(res, id) \
   {\
      LOCK_READ(&m_Mutex, l_LockInputData);\
      if (id >= 0 && id < m_lPortIn.size())\
      {\
         res = LIST_AT(m_lPortIn, id)->GetData();\
      }\
      else\
      {\
         RELEASE_PTR(res);\
      }\
   }

#define MODULE_STOP_NO_WAIT         -1
#define NOTIFY_OUTPUT(id) \
    {\
        if (id < m_lPortOut.size()) \
        {\
            LIST_AT(m_lPortOut, id)->NotifyOut();\
        }\
    }
FIXME // ADD A LOCKING MECHANISM IN NOTIFY_OUTPUT(id)

#define TIMER_EVENT_PORT_ID         -1
#define TRIGGERED_EVENT_PORT_ID     -2

namespace fby
{
/* Forward declarations. */
class CORE_APP_EXPORT Module;
DEF_PTR(Module);
typedef std::list<ModulePtr>    ModuleList;
typedef QUuid                   ModuleId;

/******************************************************************************/
/**
 * @enum ModuleExecMode
 *
 * @brief Enumerates of the available Module execution modes.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
enum ModuleExecMode
{
    MODULE_MODE_INVALID = -1,   /**< Invalid execution mode. */
    MODULE_MODE_CONSOLE = 0,    /**< Console mode. */
    MODULE_MODE_WIDGET,         /**< Widget mode. */
    MODULE_MODE_CHECK,          /**< Validity-check mode. */
    MODULE_MODE_DEBUG           /**< Debug mode. */

}; // end enum ModuleExecMode.

/******************************************************************************/
/**
 * @enum ModuleFlag
 *
 * @brief Enumerates of the Module flags.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
enum ModuleFlag
{
    MODULE_FLAG_GENERIC     = 0x0000000000000000,
    MODULE_FLAG_PLUGIN      = 0x0000000000000001,

    MODULE_FLAG_CUSTOM      = 0x0000000000000080

}; // end enum ModuleFlag.

/******************************************************************************/
/**
 * @class SharedLib
 *
 * @brief Holds a QLibrary object and unloads it in the destructor.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT SharedLib : public QObject
{
    Q_OBJECT

public:

    SharedLib(const QString& p_rstrFilename);
    virtual ~SharedLib();

public:

    QLibrary    m_SharedLibrary;

}; // end class SharedLib.

DEF_PTR(SharedLib);

/******************************************************************************/

/**
 * @class Module
 *
 * @ingroup Modules
 *
 * @brief Base class for a single processing unit that operates in a separate
 * thread.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT Module : public QObject
{
    Q_OBJECT

    GET_SET_OPTIONS;

    /**
     * @fn LoadConfig
     *
     * @brief Loads the settings contained in the input QSettings object and
     * stores it into the Module's options object.
     */

    /**
     * @fn SaveConfig
     *
     * @brief Saves the options of this Module to a QSettings object.
     */
    LOAD_SAVE_CONFIG;

    LOAD_SAVE_DATA;

public:

    /**
     * @brief Default constructor. Allocates a new Module object with the
     * specified execution mode.
     *
     * @param[in]   p_Mode      Execution mode of this module.
     */
    Module(ModuleExecMode   p_Mode);

    virtual ~Module();

    /**
     * @brief Abort is a virtual function to be implmemented in subclasses to
     * abort the current computation. By default this function is empty since
     * only subclasses know how to abort the computation.
     */
    virtual void Abort();

    /**
     * @brief Adds one or more input ports.
     *
     * @note The id number of the new ports will be automatically computed.
     *
     * @param[in]   p_iNumPorts     Number of input ports to be added.
     *
     * @return RET_SUCCESS if the new ports have been successfully added.
     */
    virtual RetFlag AddInput(const int p_iNumPorts = 1);

    /**
     * @brief AddOutput adds a number of empty output ports. The added ports
     * are not linked to any data.
     *
     * @warning This is an advanced feature that must be used with care. An
     * example of usage of this function is to define a number of output ports
     * of a ModuleGroup that are linked to the output ports of the managed
     * groups.
     *
     * @param[in]   p_iNumOutputs   Number of empty output ports to be added.
     */
    virtual void AddOutput(const int p_iNumOutputs);

    /**
     * @brief Adds an output port and associates to it the specified data.
     *
     * @note The id number of the output port will be automatically computed.
     *
     * @warning The data to be associated to the output port must be
     * instantiated before the call to this function.
     *
     * @param[in]   p_pData     Data associated to the new output port.
     *
     * @return RET_SUCCESS if the new output port has been successfully added.
     */
    virtual RetFlag AddOutput(DataPtr p_pData);

    /**
     * @brief Adds as output ports as the number of data contained in the input
     * list.
     *
     * @note The id number of the input ports is automatically computed.
     *
     * @warning The data to be associated to the output ports must be
     * instantiated before the call to this function.
     *
     * @param[in]   p_rlData    List of data to be associated to the new output
     *                          ports.
     *
     * @return RET_SUCCESS if all the output ports have been successfully added.
     */
    virtual RetFlag AddOutput(QList<DataPtr>&   p_rlData);

    /**
     * @brief Changes the loop time of the main timer. If this Module is
     * running, the main-timer-id will be changed without stopping the loop.
     * Otherwise nothing is done.
     *
     * @param[in]   p_iPeriod_ms    New loop time (ms).
     */
    virtual void ChangeLoopTime(const int p_iPeriod_ms);

    /**
     * @brief Checks the licensing of this module. Subclasses must implement
     * their own licensing management.
     *
     * @note The default implementation returns true.
     *
     * @return True if this module is licensed, or false otherwise.
     */
    virtual bool CheckLicense();

    /**
     * @brief Close performs a clean closure of this Module.
     *
     * @note The default implementation calls the Stop() method.
     *
     * @retval  true    if this Module has been cleanly closed.
     * @retval  falst   if this Module has not been cleanly closed.
     */
    virtual bool Close();

    /**
     * @return the current loop time in milliseconds. If this moduel is not
     * running, then returns a negative value.
     */
    virtual int GetLoopTime() const;

    /**
     * @return the ID of this Module.
     */
    virtual ModuleId GetId() const;

    /**
     * @return The menu of this Module.
     */
    virtual QMenu* GetMenu();

    /**
     * @return the name of this Module. If the member m_sName is empty returns
     * the className using the meta-object mechanism of Qt.
     */
    virtual std::string GetName() const;

    /**
     * @return the number of output ports.
     */
    inline int GetNumPortIn() const
    {
        return m_lPortIn.size();
    }

    /**
     * @return the number of output ports.
     */
    inline int GetNumPortOut() const
    {
        return m_lPortOut.size();
    }

    /**
     * @param[in]  p_iPortId   Id of the requested input port.
     *
     * @return The input port object or a null object if the id is not valid.
     */
    virtual ModulePortPtr GetPortIn(const int p_iPortId);

    /**
     * @param[in]  p_iPortId   Id of the requested output port.
     *
     * @return The output port object or a null object if the id is not valid.
     */
    virtual ModulePortPtr GetPortOut(const int p_iPortId);

    /**
     * @return The status bar of this Module.
     */
    virtual QStatusBar* GetStatusBar();

    /**
     * @return The toolbar of this Module.
     */
    virtual QToolBar* GetToolBar();

    /**
     * @brief GetWidget returns the widget managed by this module, relative to
     * the specified index. If the index is zero, then the main QWidget is
     * returned.
     *
     * @param[in]   p_sIndex    Index of the widget to be returned.
     *
     * @return The pointer to a widget managed by this module.
     */
    virtual QWidget* GetWidget(size_t p_sIndex = 0);

    /**
     * @brief GetWorkDir returns the absolute path to the current work directory
     * of this Module.
     *
     * @return the current work directory.
     */
    std::string GetWorkDir() const;

    /**
     * @brief HasFlag checks if this module has the input flags set. The check
     * is performed using a bitwise AND between the input flags and the flags
     * of this Module.
     *
     * @param[in]   p_Flags     Module flags to be checked.
     *
     * @retval  true    if this Module has all the specified flags set.
     * @retval  false   if this Module has at least one of not the specified
     *                  flags not set.
     */
    virtual bool HasFlag(const ModuleFlag p_Flags);

    /**
     * @brief Initialization function of this module. The default
     * implementation sets the member variables to their default value.
     * Subclasses must implement their own methods.
     *
     * @param[in]   p_Mode      Execution mode of this module.
     *
     * @return RET_SUCCESS in case of a successfull initialization.
     */
    virtual RetFlag Init(ModuleExecMode     p_Mode);

    /** @brief Initializes the options common to all the Modules.
     */
    virtual void InitOptions();

    /**
     * @brief Initializes the threading data of this module.
     *
     * @return RET_SUCCESS in case of a successfull initialization.
     */
    virtual RetFlag InitThread();

    /**
     * @brief InitWidgets initializes the widgets in the running thread.
     */
    virtual void InitWidgets();

    /**
     * @return true if this Module has been closed and hence no more actions
     * are allowed.
     */
    virtual bool IsClosed() const;

    /** @return true if the main loop of this module is running.
     */
    virtual bool IsRunning() const;

    /**
     * @brief NotifyOutput notifies the outputs whose data matches the input
     * DataPtr parameter. If no output has the specified data, then no
     * notification is performed.
     *
     * @note If more than one output port share the same DataPtr, all that ports
     * will be notified.
     *
     * @param[in]   p_pData     Input data whose respective output ports has
     *                          to be notified.
     *
     * @retval  true    if a notification has been performed.
     * @retval  false   if no notification has been performed.
     */
    virtual bool NotifyOutput(DataPtr p_pData);

    /**
     * @brief Pauses this module by skipping the execution of the thread
     * function. This behavior is obtained by setting the pause-flag.
     *
     * @param[in]   p_bPause    Input pause flag.
     */
    virtual void Pause(const bool p_bPause);

    /**
     * @brief Sets the thread continuation flag.
     *
     * @param[in]   p_bContinueThread   Thread continuation flag.
     */
    virtual void SetContinueThread(const bool p_bContinueThread);

    /**
     * @brief SetId sets the ID of this Module. The ID of a Module should be
     * unique in the application.
     *
     * @param[in]   p_rId   Input ID.
     */
    virtual void SetId(const ModuleId& p_rId);

    /**
     * @brief SetName sets the user-friendly name of this Module.
     *
     * @param[in]   p_rsName    Input user-friendly name.
     */
    virtual void SetName(const std::string& p_rsName);

    /**
     * @brief Generic virtual function to allow a parent-children mechanism
     * among Modules. The default implementation is empty: subclasses must
     * implement their own methods.
     *
     * @param[in]   p_pParent   Parent module.
     *
     * @return RET_SUCCESS in the default implementation.
     */
    virtual RetFlag SetParentModule(ModulePtr p_pParent);

    /**
     * @brief SetSharedLib sets the SharedLib object linked to this Module.
     *
     * @param[in]   p_pSharedLib    Input SharedLib object.
     */
    virtual void SetSharedLib(SharedLibPtr   p_pSharedLib);

    /**
     * @brief SetWorkDir sets the current working directory of this Module.
     *
     * @param[in]   p_rsPath    Input path to the new working directory.
     */
    virtual void SetWorkDir(const std::string& p_rsPath);

    /**
     * @brief Starts the thread of this module allowing a periodic or an
     * asynchronous execution loop.
     *
     * @param[in]   p_iPeriod_ms    Loop period in milliseconds. If this
     *                              parameter is set to zero then the loop will
     *                              be executed asynchronously.
     *
     * @return The execution flag.
     */
    virtual RetFlag Start(int p_iPeriod_ms = 0);

    /**
     * @brief Stops the execution of the thread of this module.
     *
     * @param[in]   p_iWait_ms  Waits until this module has stopped or until
     *                          a maximum number of milliseconds. If this input
     *                          is negative or null then no wait is performed.
     *
     * @return true if the module was successfully stopped within the specified
     * wait time.
     */
    virtual bool Stop(int p_iWait_ms = MODULE_STOP_NO_WAIT);

    /**
     * @brief Triggers a single execution of the thread function of this Module.
     * The _ThreadFunction is called with argument equal to the input port id.
     *
     * @param[in]   p_iPortId   Input port id. By default this parameter is set
     *                          to TRIGGERED_EVENT_PORT_ID.
     */
    virtual void Trigger(int p_iPortId = TRIGGERED_EVENT_PORT_ID);

protected:

    /**
     * @return true if the thread of this Module has to be continued.
     */
    bool    _ContinueThread() const;

    /**
     * @brief _LockInputPort locks the number of input ports.
     */
    void    _LockInputPortNum();

    /**
     * @brief _LockOutputPort locks the number of output ports.
     */
    void    _LockOutputPortNum();

    /**
     * @brief Function that is called by either the timerEvent (in the case of
     * a timed module execution) and by the execution of slot_InputPortTriggered.
     * Subclasses must implement their own methods.
     *
     * @warning The difference between the timed execution and the execution
     * triggered by an input port may be determined by the value of the id.
     *
     * @param[in]   p_iPortId   Id number of the port that triggered the
     *                          execution of the thread, or the equivalent port
     *                          id of the timerEvent.
     *
     * @return The execution flag.
     */
    virtual RetFlag _ThreadFunction(const int p_iPortId) = 0;

signals:

    /**
     * @brief sig_Progress is a signal to be emitted to notify an overall
     * progress of the computation of this Module.
     *
     * @param[in]   p_dProgress     Overall progress (range: 0.0, 1.0).
     */
    void    sig_Progress(double p_dProgress);

    /**
     * @brief sig_Start is signal to be emitted to start this Module.
     *
     * @param[in]   p_iPeriod_ms    Loop time of the timed version of the
     *                              execution of this Module (ms).
     */
    void    sig_Start(int p_iPeriod_ms);

    /**
     * @brief sig_Stop is a signal to be emitted to stop the timer of this
     * Module.
     */
    void    sig_Stop();

    /**
     * @brief sig_ThreadFunctionFinished is a signal to be emitted to notify
     * the end of execution of the thread function.
     */
    void    sig_ThreadFunctionFinished();

    /**
     * @brief sig_Trigger is a signal to be emitted to trigger this Module with
     * an input port index.
     *
     * @param[in]   p_iPortId       Input port index.
     */
    void    sig_Trigger(int p_iPortId);

    /**
     * @brief sig_WidgetClosed is a signal to be emitted to notify that the
     * widget of this Module has been closed.
     */
    void    sig_WidgetClosed();

    /**
     * @brief sig_WidgetUpdated is a signal to be emitted to notify that the
     * widget of this Module has been modified.
     */
    void    sig_WidgetModified();

protected slots:

    /**
     * @brief Executes the thread function providing it with the id number of
     * the input port that was triggered.
     *
     * @param[in]   p_iPortId   Id of the input port that was triggered.
     */
    virtual void    slot_InputPortTriggered(int p_iPortId);

    virtual void    slot_TimerTimeout();

    virtual void    slot_Triggered(int p_iPortId = TRIGGERED_EVENT_PORT_ID);

    virtual void    slot_WidgetClosed();

    virtual void    slot_WidgetModified();

protected:

    mutable QReadWriteLock  m_Mutex; /**< General purpose read/write mutex to
                                      * protect the data of this module. */

    SharedLibPtr    m_pSharedLib; /**< Holds a pointer to the shared library that
                                   * contains the implementation of this Module. */

    ModuleExecMode  m_Mode; /**< Module execution mode. */

    ModuleFlag      m_Flag; /**< Module flags. */

    std::string     m_sName; /**< User-friendly name of this Module. */

    QTime   m_timeCount; /**< General QTime object to count the elapsed time
                          * between two points in the code. */

    bool    m_bContinueThread; /**< True if the thread must continue its
                                 * execution. */

    QWidget*    m_pwiWidget; /**< Widget to define a custom GUI to be interfaced
                              * with this module. */

    std::list<QWidget*> m_lWidgets; /**< List of widgets managed by this Module.
                                     * When accessing this list, the first
                                     * element is the main QWidget, that is
                                     * m_pwiWidget. */

    QMenu*      m_pMenu; /**< Custom menu to be included in the GUI of the main
                          * application. */

    QStatusBar* m_pStatusBar; /**< Custom status bar to be included in the GUI of
                               * the main application. */

    QToolBar*   m_pToolBar; /**< Custom toolbar to be included in the GUI of the
                             * main application. */

    ModulePortList  m_lPortIn; /**< List of input ports. */

    ModulePortList  m_lPortOut; /**< List of output ports. */

    QSemaphore  m_semStop; /**< Semaphore to perform a clean stop of the Module. */

    QTimer  m_timerMain; /**< Main timer. */

    QTime   m_timeCountMain; /**< Main timer counter. */

    int     m_iMainTimerInterval_ms; /**< Main timer interval. */

    Options m_Options; /**< Options of this Module. */

    QDir    m_WorkDir; /**< Holds the current working directory of this Module. */

    bool m_bPause; /**< Pause flag. */

    bool m_bLockInputPortNum; /**< If true, locks the number of input ports. */

    bool m_bLockOutputPortNum; /**< If true, locks the number of output ports. */

    ModuleId    m_Id; /**< Module id. */

    bool m_bIsClosed; /**< If true, it means that this Module has been closed
                       * and hence no other actions are allowed. */

}; // end class Module.

/** @typedef Generic module allocator function, for the use with modules defined
 * inside a shared library (*.dll, *.so). */
typedef Module* (*ModuleAllocatorFun)(ModuleExecMode);

/** @brief Global function that links an output port of the first module with an
 * input port of the second module.
 *
 * @param[in]   p_pModule   First module.
 * @param[in]   p_iOutPort1 Id of the output port of the first module.
 * @param[in]   p_pModule   Second module.
 * @param[in]   p_iInPort2  Id of the input port of the second module.
 *
 * @retval  RET_SUCCESS     if the two modules have been successfully linked.
 */
CORE_APP_EXPORT
RetFlag g_LinkModules(ModulePtr     p_pModule1,
                      const int     p_iOutPort1,
                      ModulePtr     p_pModule2,
                      const int     p_iInPort2);

} // end namespace fby.

#endif // MODULE_H
