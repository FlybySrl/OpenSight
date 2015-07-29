#ifndef CORE_APP_PCH_H
#define CORE_APP_PCH_H

#include <core>
#include <core_app_export.h>

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

#ifndef DEFAULT_INI_FILE
#define DEFAULT_INI_FILE    (metaObject()->className() + QString(".ini"))
#endif

#ifndef LOCK_READ
#define LOCK_READ(mutex, name)    QReadLocker name(mutex)
#endif // LOCK_READ

#ifndef LOCK_WRITE
#define LOCK_WRITE(mutex, name)   QWriteLocker name(mutex)
#endif // LOCK_WRITE

DEF_PTR(QReadWriteLock);

namespace fby
{
/** @typedef Options
 *
 * @brief Implements a map to store a set of options. The key of the map is a
 * QString and the values are of QVariant type.
 */
typedef QMap<QString, QVariant>     Options;
} // end namespace fby.

/* Configuration **************************************************************/

#define LOAD_CONFIG \
    public:\
    virtual void LoadConfig(QSettings& p_rSettings);

#define SAVE_CONFIG \
    public:\
    virtual void SaveConfig(QSettings& p_rSettings);

#define LOAD_SAVE_CONFIG \
    LOAD_CONFIG \
    SAVE_CONFIG


/* Connections ****************************************************************/
#define QT_UNIQUE_AUTO_CONNECTION \
    ((Qt::ConnectionType)(Qt::AutoConnection | Qt::UniqueConnection))

#define QT_UNIQUE_DIRECT_CONNECTION \
    ((Qt::ConnectionType)(Qt::DirectConnection | Qt::UniqueConnection))

#define QT_UNIQUE_QUEUED_CONNECTION \
    ((Qt::ConnectionType)(Qt::QueuedConnection | Qt::UniqueConnection))

/* Data ***********************************************************************/

#define LOAD_DATA \
    public:\
    virtual void LoadData(const QString& p_rstrFilename);

#define SAVE_DATA \
    public:\
    virtual void SaveData(const QString& p_rstrFilename);

#define LOAD_SAVE_DATA \
    LOAD_DATA \
    SAVE_DATA


/* Options ********************************************************************/

#define GET_OPTIONS \
    public:\
    virtual QVariant GetOption(const QString & p_rsKey) const;\
    virtual void GetOptions(Options& p_rDestination) const;\
    virtual QStringList GetOptionsKeys() const;

#define SET_OPTION \
    public:\
    virtual void SetOption(const QString& p_rsKey, const QVariant& p_rValue);

#define GET_SET_OPTIONS \
    GET_OPTIONS\
    SET_OPTION


/* Path ***********************************************************************/

#define APPEND_TO_PATH(rel_path) \
    {\
        QDir            l_Dir;\
        QString         l_strPutenv;\
        l_Dir = QDir::current();\
        l_Dir.cd(rel_path);\
        l_strPutenv = "PATH=";\
        l_strPutenv.append(getenv("PATH"));\
        l_strPutenv.append(";");\
        l_strPutenv.append(l_Dir.absolutePath());\
        _putenv(const_cast<char*>(l_strPutenv.toStdString().c_str())); \
    }

#define PREPEND_TO_PATH(rel_path) \
    {\
        QDir            l_Dir;\
        QString         l_strPutenv;\
        l_Dir = QDir::current();\
        l_Dir.cd(rel_path);\
        l_strPutenv = "PATH=";\
        l_strPutenv.append(l_Dir.absolutePath());\
        l_strPutenv.append(";");\
        l_strPutenv.append(getenv("PATH"));\
        _putenv(const_cast<char*>(l_strPutenv.toStdString().c_str())); \
    }


/* Stylesheet *****************************************************************/

#define SET_STYLESHEET(a, file) \
    {\
        QFile   l_FileStyleSheet(file);\
        l_FileStyleSheet.open(QFile::ReadOnly);\
        a.setStyleSheet(QLatin1String(l_FileStyleSheet.readAll()));\
        l_FileStyleSheet.close();\
}


/* Threads ********************************************************************/

#define CURRENT_THREAD_IS_MAIN \
    (QThread::currentThread() == QApplication::instance()->thread())

/******************************************************************************/
/**
 * @brief To performs the dynamic cast from a pointer to QObject to a derived
 * class. */
template <typename _Dest, typename _Source>
SHARED_PTR<_Dest>   To(const SHARED_PTR<_Source>& p_pObject)
{
    SHARED_PTR<_Dest>    l_pResult;

#if 1

    if (p_pObject)
    {
        register _Dest *ptr = dynamic_cast<_Dest *>(GET_PTR(p_pObject));

        if (ptr)
        {
//            l_pResult = QtSharedPointer::copyAndSetPointer(ptr, p_pObject);
#ifdef __linux
            l_pResult = std::tr1::dynamic_pointer_cast<_Dest>(p_pObject);
#else
            l_pResult = std::dynamic_pointer_cast<_Dest>(p_pObject);
#endif
        }
        else
        {
            std::cout << "Invalid dynamic_cast from: "
                      << p_pObject->metaObject()->className()
                      << " to "
                      << _Dest::staticMetaObject.className()
                      << std::endl;

        }
    }

#else

    if (p_pObject)
    {
        register _Dest *ptr = dynamic_cast<_Dest *>(GET_PTR(p_pObject));

        if (ptr)
        {
            l_pResult = QtSharedPointer::copyAndSetPointer(ptr, p_pObject);
        }
        else
        {
            qDebug() << "Invalid dynamic_cast from:"
                     << p_pObject->metaObject()->className()
                     << "to"
                     << _Dest::staticMetaObject.className();

        }
    }
#endif

    return l_pResult;
}


#endif // CORE_APP_PCH_H
