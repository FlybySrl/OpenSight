#ifndef DATATREEWIDGETITEM_H
#define DATATREEWIDGETITEM_H

#include <Data.h>

namespace fby
{
/**
 * @class DataTreeWidgetItem
 *
 * @brief The DataTreeWidgetItem class expands a QTreeWidgetItem object in order
 * to manage a Data object within a QTreeWidget.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT DataTreeWidgetItem : public QTreeWidgetItem
{
public:

    DataTreeWidgetItem(DataPtr p_pData);

    /**
     * @return the stored Data object.
     */
    DataPtr GetData();

    /**
     * @brief SetData sets the Data object to be managed.
     *
     * @param[in]   p_pData     Data object to be managed.
     */
    void SetData(DataPtr p_pData);

    /**
     * @brief Update updates the appearance of this DataTreeWidgetItem from the
     * current status of the managed Data object.
     */
    virtual void Update();

protected:

    QReadWriteLock  m_Mutex;

    DataPtr     m_pData; /**< Managed Data object. */

}; // end class DataTreeWidgetItem.

} // end namespace fby.

#endif // DATATREEWIDGETITEM_H
