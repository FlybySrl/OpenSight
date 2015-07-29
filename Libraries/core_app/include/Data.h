#ifndef DATA_H
#define DATA_H

/**
 * @file Data.h
 *
 * @brief Contains the structures and methods to share data between different
 * Modules through the output/input ports mechanism.
 *
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */

#include <core_app_pch.h>

#define DATA_LIST(DataName) \
    class DataName##_List : public fby::Data\
    {\
    public:\
        std::list<DataName##Ptr>     m_l##DataName;\
    };\
    DEF_PTR(DataName##_List)

#define DATA_WRAPPER(DataType, ClassName, MemberName) \
    class ClassName : public fby::Data\
    {\
    public:\
        inline DataType& Get()\
        {\
            LOCK_READ(&m_Mutex, l_Lock);\
            return MemberName;\
        }\
        inline const DataType& Get() const\
        {\
            LOCK_READ(&m_Mutex, l_Lock);\
            return MemberName;\
        }\
        inline void Set(const DataType& p_Value)\
        {\
            LOCK_WRITE(&m_Mutex, l_Lock);\
            MemberName = p_Value;\
        }\
    protected:\
        DataType    MemberName;\
    };\
    DEF_PTR(ClassName)

#define DEFINE_DATA_PROPERTY(name, value)  m_mapProperties[name] = value

#define DATA_PROP_ID        "DataId"

namespace fby
{
/******************************************************************************/
/* Forward declarations. */
class Data;
DEF_PTR(Data);
typedef std::list<DataPtr>      DataList;

/******************************************************************************/
/* Typedefs. */
typedef QVariant                            DataProperty;
typedef std::map<std::string, DataProperty> DataProperties;

/******************************************************************************/
/* Data. */
/**
 * @class Data
 *
 * @brief Base class that defines the interface to exchange shared data among
 * different Modules using the output/input ports mechanism.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT Data : public QObject
{
    Q_OBJECT

public:

    Data(QObject* p_pParent = 0);

    virtual ~Data();

    /**
     * @brief AddProperty adds a new property to this Data.
     *
     * @param[in]   p_rsKey     Key of the property.
     * @param[in]   p_rValue    Value of the property.
     */
    virtual void AddProperty(const std::string&     p_rsKey,
                             const DataProperty&    p_rValue);

    /**
     * @brief CopyProperties clears the current properties of this Data and
     * copies the input ones.
     *
     * @param[in]   p_rProperties   Input properties.
     */
    virtual void CopyProperties(const DataProperties& p_rProperties);

    /**
     * @brief GetId is a shorcut to get this Data's main id.
     *
     * @return the main Id of this Data.
     */
    virtual std::string GetId() const;

    /**
     * @brief GetMenu creates and returns the menu of this Data. If this Data
     * does not have actions linked to the QMenu then an empty (but valid) QMenu
     * object is created.
     *
     * @warning If the member m_pMenu is a null pointer, this function tries to
     * allocate it. The allocation is performed only if the current thread is
     * the main thread (the GUI thread). The returned pointer is null only if
     * the current m_pMenu is null AND the current thread is NOT the main
     * thread.
     *
     * @return the pointer to the menu of this Data.
     */
    QMenu* GetMenu();

    /**
     * @return a copy of the properties of this Data.
     */
    virtual DataProperties GetProperties() const;

    /**
     * @brief GetProperty gets the property associated to the specified key, or
     * an invalid value if the key does not exeist.
     *
     * @param[in]   p_rsKey     Key of the property to be returned.
     *
     * @return the value of the property of an invalid value if the property
     * does not exist.
     */
    virtual DataProperty GetProperty(const std::string& p_rsKey) const;

    /**
     * @brief HasProperty checks if this Data has the specified property.
     *
     * @param[in]   p_rsKey     Key of the queried property.
     *
     * @retval  true    if this Data has the specified property.
     * @retval  false   if this Data does not have the specified property.
     */
    virtual bool HasProperty(const std::string& p_rsKey) const;

    /**
     * @brief InitMenu initializes the menu of this Data. The default
     * implementation allocates a new QMenu object.
     *
     * @warning This method must be called in the GUI thread (the main thread)
     * otherwise the menu is not initialized.
     */
    virtual void InitMenu();

    /**
     * @brief RemoveProperty removes the property associated to the specified
     * key.
     *
     * @param[in]   p_rsKey     Key of the property to be removed.
     */
    virtual void RemoveProperty(const std::string& p_rsKey);

    /**
     * @brief SetId is a shortcut to set this Data's main id.
     *
     * @param[in]   p_rsId      Input id.
     */
    virtual void SetId(const std::string& p_rsId);

    /**
     * @brief SetProperty sets the value of the specified property, if it
     * exists. If the property does not exist, then this function does nothing.
     *
     * @param[in]   p_rsKey     Key of the property to be set.
     * @param[in]   p_rValue    Value of the property.
     */
    virtual void SetProperty(const std::string  p_rsKey,
                             DataProperty       p_rValue);

public:

    mutable QReadWriteLock  m_Mutex;

protected:

    DataProperties  m_mapProperties; /**< Map of properties of this Data. The
                                      * properties are a set of key-value pairs. */

    QMenu*  m_pMenu; /**< Menu of this Data. By default it is a null pointer:
                      * subclasses must implement their own instantiation
                      * methods. This object holds a set of actions that
                      * operates on this Data. WARNING: the creation of a new
                      * QMenu must be performed in the main thread. */

}; // end class Data.

} // end namespace fby.

DATA_WRAPPER(std::string, DataFile, m_sFile);
DATA_WRAPPER(std::string, DataId, m_sId);
DATA_WRAPPER(std::string, DataString, m_sString);

//DATA_WRAPPER(std::list<std::string>, DataFileList, m_lFiles);

DATA_LIST(DataFile);

#endif // DATA_H
