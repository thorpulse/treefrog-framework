#ifndef TLOGGER_H
#define TLOGGER_H

#include <QString>
#include <QVariant>
#include <TGlobal>
#include <TLog>

class QTextCodec;


class T_CORE_EXPORT TLogger
{
public:
    enum Priority {
        Fatal = 0, //!< Severe error events that will presumably lead the app to abort.
        Error,  //!< Error events that might still allow the app to continue running.
        Warn,   //!< Potentially harmful situations.
        Info,   //!< Informational messages that highlight the progress of the app. 
        Debug,  //!< Informational events that are most useful to debug the app.
        Trace,  //!< Finer-grained informational events than the DEBUG.
    };

    TLogger();
    virtual ~TLogger() { }
    virtual QString key() const = 0;
    virtual bool isMultiProcessSafe() const = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual void log(const TLog &log) = 0; // thread safe log output
    virtual void flush() { }
    virtual QByteArray logToByteArray(const TLog &log) const;

    void readSettings();
    const QByteArray &layout() const { return layout_; }
    const QByteArray &dateTimeFormat() const { return dateTimeFormat_; }
    Priority threshold() const { return threshold_; }
    const QString &target() const { return target_; }    
    QVariant settingsValue(const QString &key, const QVariant &defaultValue = QVariant()) const;

    static QByteArray logToByteArray(const TLog &log, const QByteArray &layout, const QByteArray &dateTimeFormat, QTextCodec *codec = 0);
    static QByteArray priorityToString(Priority priority);

protected:
    QByteArray layout_;
    QByteArray dateTimeFormat_;
    Priority threshold_;
    QString  target_;
    QTextCodec *codec_;
};

#endif // TLOGGER_H
