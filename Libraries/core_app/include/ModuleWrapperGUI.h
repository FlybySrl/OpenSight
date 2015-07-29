#ifndef MODULEDATAPROCESSINGGUI_H
#define MODULEDATAPROCESSINGGUI_H

#include <core_app_pch.h>

namespace fby
{
class CORE_APP_EXPORT ModuleWrapperGUI : public QMainWindow
{
    Q_OBJECT

public:

    ModuleWrapperGUI(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    virtual ~ModuleWrapperGUI();

    /**
     * @brief CreateToolBar creates a QToolBar with default actions. The default
     * actions are the following:
     *  - Start
     *  - Stop
     *  - Pause
     *  - <separator>
     *  - Clear
     *  - Hide
     *
     * If a toolbar for this ModuleWrapperGUI already exists, then it will NOT
     * be created.
     *
     * @return the new QToolBar or the existing one if it has been previously
     * created.
     */
    virtual QToolBar* CreateToolBar();

    /**
     * @brief SetItemList emits the signal to update the list on the widget.
     *
     * @param[in]   p_rlItems       Input list of items.
     */
    virtual void SetItemList(const std::list<std::string>& p_rlItems);

    /**
     * @brief SetModuleWidget sets the widget of the module to be placed within
     * the layout of this ModuleWrapperGUI.
     *
     * @param[in]   p_pWidget   Module's widget.
     */
    virtual void SetModuleWidget(QWidget* p_pWidget);

signals:

    /**
     * @brief sig_ItemDoubleClicked is a signal emitted when an item of the
     * m_pTable member is double-clicked.
     *
     * @param[in]   p_iRow      Row of the double-clicked cell.
     * @param[in]   p_iCol      Column of the double-clicked cell.
     * @param[in]   p_sText     Text of the QTableWidgetItem double-clicked.
     */
    void sig_ItemDoubleClicked(int p_iRow, int p_iCol, QString p_sText);

signals:

    /**
     * @brief sig_Clear is emitted when the m_pactClear action is triggered.
     */
    void sig_Clear();

    /**
     * @brief sig_Hide is emitted when the m_pactHide action is triggered.
     */
    void sig_Hide();

    /**
     * @brief sig_Pause is emitted when the m_pactPause action is toggled.
     */
    void sig_Pause(bool p_bToggle);

    /**
     * @brief sig_SetItemList is a signal to be emitted to update the list of
     * items on the widget.
     *
     * @param[in]   p_lItems    Input list of items.
     */
    void sig_SetItemList(QStringList p_lItems);

    /**
     * @brief sig_Start is emitted when the m_pactStart action is triggered.
     */
    void sig_Start();

    /**
     * @brief sig_Stop is emitted when the m_pactStop action is triggered.
     */
    void sig_Stop();

protected slots:

    /**
     * @brief slot_ActionClearTriggered is connected with the triggered signal
     * of m_pactClear.
     */
    virtual void slot_ActionClearTriggered();

    /**
     * @brief slot_ActionHideTriggered is connected with the triggered signal
     * of m_pactHide.
     */
    virtual void slot_ActionHideTriggered();

    /**
     * @brief slot_ActionPauseToggled is connected with the toggled signal
     * of m_pactPause.
     */
    virtual void slot_ActionPauseToggled(bool p_bToggle);

    /**
     * @brief slot_ActionStartTriggered is connected with the triggered signal
     * of m_pactStart.
     */
    virtual void slot_ActionStartTriggered();

    /**
     * @brief slot_ActionStopTriggered is connected with the triggered signal
     * of m_pactStop.
     */
    virtual void slot_ActionStopTriggered();

    /**
     * @brief slot_SetItemList sets the list of items to be shown on the widget.
     *
     * @param[in]   p_rlItems       Input list of items.
     */
    virtual void slot_SetItemList(QStringList p_lItems);

    /**
     * @brief slot_TableCellDoubleClicked is a slot to be called in reaction to
     * a double-click on an cell of m_pTable QTableWidget object.
     *
     * @param[in]   p_iRow      Row of the double-clicked cell.
     * @param[in]   p_iCol      Column of the double-clicked cell.
     */
    virtual void slot_TableCellDoubleClicked(int p_iRow, int p_iCol);


protected:

    QWidget*        m_pCentralWidget;

    QGridLayout*    m_pGridLayout;

    QTableWidget*   m_pTable;

    QWidget*        m_pModuleWidget; /**< Holds the module's widget. */

    QToolBar*       m_pToolBar; /**< Main toolbar. */

    QAction*        m_pactStart;

    QAction*        m_pactStop;

    QAction*        m_pactPause;

    QAction*        m_pactClear;

    QAction*        m_pactHide;

}; // end class ModuleWrapperGUI.

} // end namespace fby.

#endif // MODULEDATAPROCESSINGGUI_H
