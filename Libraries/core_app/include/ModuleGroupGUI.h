#ifndef MODULEGROUPGUI_H
#define MODULEGROUPGUI_H

#include <Module.h>

namespace fby
{
/* Forward declarations. */
class ModuleGroup;

/******************************************************************************/
/**
 * @class ModuleGroupGUI
 *
 * @brief Implements the GUI to manage a ModuleGroup. This class holds a copy
 * of the list of the Modules managed by a ModuleGroup and manages the widgets
 * of these Modules.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT ModuleGroupGUI : public QMainWindow
{
    Q_OBJECT

    LOAD_SAVE_CONFIG;

public:

    ModuleGroupGUI(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    ~ModuleGroupGUI();

    inline QToolBar* GetToolBar()
    {
        return m_pToolBar;
    }

    inline void InitButtons()
    {
        emit(sig_InitButtons());
    }

    virtual void SetModuleList(const ModuleList& p_rlModules);

protected:

    virtual void closeEvent(QCloseEvent* p_pEvent);

signals:

    void sig_InitButtons();
    void sig_WidgetClosed();

protected slots:

    /**
     * @brief slot_ActionTriggered manages the trigger event of an action. The
     * actions are linked to the QToolButtons shown on the GUI to switch among
     * the widgets of the available Modules.
     *
     * @param p_pAction
     */
    virtual void slot_ActionTriggered(QAction* p_pAction);

    /**
     * @brief slot_Back hides the current central widget and shows the buttons
     * to select among the managed modules.
     */
    virtual void slot_Back();

    /**
     * @brief slot_InitButtons initializes the selection buttons in the main
     * window of this widget.
     */
    virtual void slot_InitButtons();

protected:

    mutable QReadWriteLock  m_Mutex;

    ModuleList  m_lModules; /**< Auxiliary list of managed modules. */

    QWidget*        m_pSelectionWidget; /**< Selection widget that contains a
                                         * set of buttons to switch among the
                                         * managed modules. */

    QWidget*        m_pHiddenWidget; /**< Auxiliary widget where to place the
                                      * hidden widgets avoiding deallocation of
                                      * the widgets when replacing the central
                                      * widget of m_pMainWindow. */

    QGridLayout*    m_pLayout; /**< Layout of the selection widget. */

    QToolBar*       m_pToolBar; /**< Main toolbar of this widget. */

    QAction*        m_pactBack; /**< Action to go back to the main window that
                                 * shows the buttons to select among the managed
                                 * modules. */

    QCheckBox*      m_pCBOpenNewWindow; /**< If checked, the selected modules
                                         * are open in a new window. */

    std::list<QAction*>     m_lActions; /**< List of QActions of the GUI of this
                                         * ModuleGroup. */

    std::list<QToolButton*>     m_lButtons; /**< List of buttons of the GUI of
                                             * this ModuleGroup. */

    std::map<QAction*, ModulePtr>   m_mapActionModules; /**< Map action-modules
                                                         * to retrieve the module
                                                         * that triggered an
                                                         * action. */

}; // end class ModuleGroupWidget.

} // end namespace fby.

#endif // MODULEGROUPGUI_H
