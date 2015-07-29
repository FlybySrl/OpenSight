#ifndef APPBASE_H
#define APPBASE_H

#include <Module.h>
#include <SettingsDefs.h>
#include <Stylesheet.h>

namespace Ui {
class AppBase;
}

namespace fby
{
/** @class AppBase
 *
 * @brief Base class that defines the common functions and the interface to
 * manage the modules in an application. Inherits from QMainWindows so that it
 * can be used also as the main widget of a graphical application.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT AppBase : public QMainWindow
{
    Q_OBJECT

    /**
     * @fn LoadConfig
     *
     * Loads the configuration from an *.ini file and propagates the same file
     * to each managed module.
     */
    LOAD_CONFIG;

    /**
     * @fn SaveConfig
     *
     * @brief Saves the configuration of this AppBase to an *.ini file and
     * propagates the same file to each managed module to save their specific
     * configuration data.
     */
    SAVE_CONFIG;

    GET_SET_OPTIONS;

public:

    /** @brief Default constructor.
     */
    AppBase(QWidget* p_pParent = 0, Qt::WindowFlags p_Flags = 0);

    /**
     * @brief Destructor: saves the last configuration on the *.ini file
     * specified by the member m_sSettings.
     */
    virtual ~AppBase();

    /**
     * @brief Adds a module to the list of managed modules if it is not yet
     * managed.
     *
     * @warning This function changes the working directory of the input Module
     * to be the same of this AppBase.
     *
     * @param[in]   p_pModule       Module to be managed.
     */
    virtual void AddModule(ModulePtr p_pModule);

    /**
     * @brief Builds the modules menu depending on the currently managed
     * modules.
     */
    virtual void BuildModulesMenu();

    /**
     * @brief Configures the modules managed by this AppBase. This is a pure
     * virtual function that needs to be implemented in subclasses in order to
     * properly set the managed modules.
     *
     * @note In order to add a module to be manages, the user must call the
     * method AddModule().
     */
    virtual void ConfigModules() = 0;

    QDockWidget* GetDockWidget(Qt::DockWidgetArea p_DockArea);

    QGridLayout* GetDockWidgetLayout(Qt::DockWidgetArea p_DockArea);

    /**
     * @brief GetWorkDir returns the absolute path of the current work
     * directory.
     *
     * @return the current work directory.
     */
    std::string GetWorkDir() const;

    /**
     * @brief Init initializes the layout of this AppBase.
     */
    virtual void Init();

    /** @brief Initializes the options of this AppBase.
     */
    virtual void InitOptions();

    /**
     * @brief Removes the input module from the list of managed modules.
     *
     * @param[in]   p_pModule       Module to e removed.
     */
    virtual void RemoveModule(ModulePtr p_pModule);

    /**
     * @brief SetAutoSaveConfigOnClose enables or disables the automatic saving
     * of the last configuration when closing the application.
     *
     * @param[in]   p_bAutoSave     If true enables the automatic saving of the
     *                              last coniguration on closing.
     * @param[in]   p_rsFile        [optional] Name of the save file where to
     *                              store the configuration.
     */
    virtual void SetAutoSaveConfigOnClose(
            bool                p_bAutoSave,
            const std::string&  p_rsFile = "");

    /**
     * @brief Sets the stylesheets of the widget of the managed modules.
     *
     * @param[in]   p_rsFilename        Filename of the stylesheet.
     */
    virtual void SetStyleSheet(const QString& p_rsFilename);

    /**
     * @brief SetWorkDir sets the path of the current working directory and sets
     * the working directory of all the managed Modules.
     *
     * @param[in]   p_rsPath    Input path to the new working directory.
     */
    virtual void SetWorkDir(const std::string& p_rsPath);

    /**
     * @brief Start triggers all the managed modules.
     */
    virtual void Start();

protected:

    void    closeEvent(QCloseEvent* p_pEvent);

signals:

    void    sig_InitWidgets();

protected slots:

    virtual void    slot_InitWidgets();

    virtual void    slot_WidgetClosed();

    virtual void    slot_WidgetModified();

protected slots:

    void on_actionLoad_Config_triggered();
    void on_actionSave_Config_triggered();

protected:

    Ui::AppBase* ui;

    ModuleList      m_lModules; /**< List of modules managed by this AppBase. */

    QWidget*        m_pCentralWidget; /**< Central widget. */

    QGridLayout*    m_pMainLayout; /**< Main layout of the central widget. */

    QMenu   m_menuModules; /**< Modules menu. */

    Options m_Options; /**< Global options of this class. */

    QString   m_sSettings; /**< Holds the filename of a QSettings object where
                            * to save the configuration on exit. This member has
                            * a valid value if LoadConfig or SaveConfig was
                            * called at least once at runtime. */

    QDir    m_WorkDir; /**< Holds the current working directory. */

    bool    m_bAutoSaveOnClose; /**< If true automatically saves on closing the
                                 * last configuration of ths application on
                                 * close. */

}; // end class AppBase.

} // end namespace fby.

#endif // APPBASE_H
