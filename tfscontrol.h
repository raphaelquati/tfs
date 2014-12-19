#ifndef TFSCONTROL_H
#define TFSCONTROL_H

#include <coreplugin/iversioncontrol.h>

namespace Tfs {
namespace Internal {


class TfsClient;

class TfsControl : public Core::IVersionControl
{
    Q_OBJECT

public:
    explicit TfsControl(TfsClient *client);
    QString displayName() const;
    Core::Id id() const;

    bool managesDirectory(const QString &directory, QString *topLevel = 0) const;
    bool managesFile(const QString &workingDirectory, const QString &fileName) const;

    bool isConfigured() const;
    bool supportsOperation(Operation operation) const;
    OpenSupportMode openSupportMode(const QString &fileName) const;

    bool vcsOpen(const QString &fileName);
    bool vcsAdd(const QString &fileName);
    bool vcsDelete(const QString &filename);
    bool vcsMove(const QString &from, const QString &to);
    bool vcsCreateRepository(const QString &directory);
    bool vcsCheckout(const QString &directory, const QByteArray &url);
    QString vcsGetRepositoryURL(const QString &directory);
    QString vcsCreateSnapshot(const QString &topLevel);
    QStringList vcsSnapshots(const QString &topLevel);
    bool vcsRestoreSnapshot(const QString &topLevel, const QString &name);
    bool vcsRemoveSnapshot(const QString &topLevel, const QString &name);
    bool vcsAnnotate(const QString &file, int line);

    QStringList listRemoteDirectory(QString path);
public slots:
    void changed(const QVariant&);
    void emitConfigurationChanged();

private:
    TfsClient *tfsClient;
};

}
}

#endif // TFSCONTROL_H

