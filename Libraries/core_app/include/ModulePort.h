#ifndef MODULE_PORT_H
#define MODULE_PORT_H

/** @file ModulePort.h
 *
 * @brief Defines the Port class that is the way to link different Modules.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

#include <Data.h>

namespace fby
{
/******************************************************************************/
/* Forward declarations. */
class CORE_APP_EXPORT ModulePort;
DEF_PTR(ModulePort);

typedef std::list<ModulePortPtr>    ModulePortList;

/******************************************************************************/
/**
 * @class ModulePort
 *
 * @brief Base class that represents a generic input or output port of a Module.
 * This class acts as an interface between different modules.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT ModulePort : public QObject
{
    Q_OBJECT

public:

    /**
     * @enum Type
     *
     * @brief Enumerates of the available port types.
     */
    enum Type
    {
        PORT_INVALID = -1, /**< Invalid port type. */
        PORT_INPUT, /**< Input port type. */
        PORT_OUTPUT /**< Output port type. */

    }; // end enum Type

public:

    /**
     * @brief Builds a new port with the specified id number.
     *
     * @param[in]   p_iPortId   Port id number.
     */
    ModulePort(const int p_iPortId, Type p_Type = PORT_INVALID);

    virtual ~ModulePort();

    /**
     * @return The data associated to this port.
     */
    virtual DataPtr GetData();

    /**
     * @return The id number of this port.
     */
    virtual int     GetId() const;

    /**
     * @return The type of this port.
     */
    virtual Type    GetType() const;

    /**
     * @brief Links this port to the specified port so that the two ports share
     * the same data.
     *
     * @param[in]   p_pPort     Port which will be linked to this Port.
     * @param[in]   p_pOutToOut If true performs a link assuming that the
     *                          specified ModulePort and this ModulePort are
     *                          output ports.
     */
    virtual void    LinkToPort(ModulePortPtr    p_pPort,
                               bool             p_bOutToOut = false);

    /**
     * @brief Notifies the id of the input port that received the signal from
     * an output port of another module.
     */
    virtual void    NotifyIn();

    /**
     * @brief Emits the sig_Out() signal to notify that the data are available
     * to this Port.
     */
    virtual void    NotifyOut();

    /** @brief Sets the data associated to this port.
     *
     * @param[in]   p_pData     Data to be associated ot this Port.
     */
    virtual void    SetData(DataPtr p_pData);

signals:

    /**
     * @brief Signal to be emitted whenever the input port is triggered.
     *
     * @warning To be used only for input ports.
     *
     * @param[in]   p_iId   Id number of the port.
     */
    void sig_In(int p_iId);

    /**
     * @brief Signal to be emitted whenever the output port must notify the
     * availability of the data it contains.
     *
     * @warning To be used only for output ports.
     */
    void sig_Out();

    /**
     * @brief sig_ProcessingFinished is a signel to be emitted to notify that
     * the processing of the data contained in this ModulePort is finished.
     */
    void sig_ProcessingFinished();

protected slots:

    /**
     * @brief slot_In is a slot that is called when this port is notified by
     * an output port.
     */
    virtual void slot_In();

    /**
     * @brief slot_PropagateOut is a slot that propagates the output
     * notification between two linked output ports.
     */
    virtual void slot_PropagateOut();

protected:

    int     m_iPortId; /**< Id number of this Port. */

    DataPtr m_pData; /**< Data associated to this Port. */

    ModulePortPtr m_pLinkedPort; /**< Effective only for input ports: stores the
                                  * output port which is linked to this port. */

    const Type    m_Type; /**< Port type. */

}; // end class ModulePort.

} // end namespace fby.

#endif // PORT_H
