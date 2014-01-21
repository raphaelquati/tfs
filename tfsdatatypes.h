#ifndef TFSDATATYPES_H
#define TFSDATATYPES_H

#include <QObject>

namespace Tfs {
namespace Internal {


class TfsWorkFolder {
public:
    TfsWorkFolder();
    virtual ~TfsWorkFolder();

    QString m_serverItem;
    QString m_localItem;
    QString m_type;
    QString m_depth;
};

class TfsWorkspace: public QObject {
    Q_OBJECT

    QString m_name;
    QString m_owner;
    QString m_computer;
    QString m_comment;
    QString m_server;


    QList<TfsWorkFolder *> m_workfolders;
public:
    TfsWorkspace(TfsWorkspace *workspace = 0);


    const QList<TfsWorkFolder *> workfolders() const;

    Q_PROPERTY(QString Name READ Name WRITE setName)
    Q_PROPERTY(QString Owner READ Owner WRITE setOwner)
    Q_PROPERTY(QString Computer READ Computer WRITE setComputer)
    Q_PROPERTY(QString Comment READ Comment WRITE setComment)
    Q_PROPERTY(QString Server READ Server WRITE setServer)

    QString Name() const
    {
        return m_name;
    }
    QString Owner() const
    {
        return m_owner;
    }

    QString Computer() const
    {
        return m_computer;
    }

    QString Comment() const
    {
        return m_comment;
    }

    QString Server() const
    {
        return m_server;
    }


public slots:
    void setName(QString arg)
    {
        m_name = arg;
    }
    void setOwner(QString arg)
    {
        m_owner = arg;
    }
    void setComputer(QString arg)
    {
        m_computer = arg;
    }
    void setComment(QString arg)
    {
        m_comment = arg;
    }
    void setServer(QString arg)
    {
        m_server = arg;
    }

};



} // namespace Internal
} // namespace Tfs

#endif // TFSDATATYPES_H
