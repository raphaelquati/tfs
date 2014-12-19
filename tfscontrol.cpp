#include "tfscontrol.h"
#include "tfsclient.h"
#include "tfsconstants.h"

#include <vcsbase/vcsbaseclientsettings.h>
#include <vcsbase/vcsbaseconstants.h>

#include <QFileInfo>
#include <QVariant>
#include <QStringList>
#include <QDir>

namespace Tfs {
namespace Internal {

TfsControl::TfsControl(TfsClient *client)
    : tfsClient(client)
{
}

QString TfsControl::displayName() const
{
    return tr("TFS");
}

Core::Id TfsControl::id() const
{
    return Core::Id(VcsBase::Constants::VCS_ID_TFS);
}

bool TfsControl::managesDirectory(const QString &directory, QString *topLevel) const
{
    //DONE
    QFileInfo dir(directory);
    const QString topLevelFound = tfsClient->findTopLevelForFile(dir);
    if (topLevel)
        *topLevel = topLevelFound;
    return !topLevelFound.isEmpty();
}

bool TfsControl::managesFile(const QString &workingDirectory, const QString &fileName) const
{
    return tfsClient->managesFile(workingDirectory, fileName);
}

bool TfsControl::isConfigured() const
{
    //DONE
    const QString binary = tfsClient->settings()->binaryPath().toString();
    if (binary.isEmpty())
        return false;
    QFileInfo fi(binary);
    return fi.exists() && fi.isFile() && fi.isExecutable();
}

bool TfsControl::supportsOperation(Operation operation) const
{
    //TODO: Check supported operations

    bool supported = isConfigured();
    switch (operation) {
    case Core::IVersionControl::AddOperation:
    case Core::IVersionControl::DeleteOperation:
    case Core::IVersionControl::MoveOperation:
    case Core::IVersionControl::AnnotateOperation:
    case Core::IVersionControl::CheckoutOperation:
    case Core::IVersionControl::GetRepositoryRootOperation:
        break;
    case Core::IVersionControl::CreateRepositoryOperation:
    case Core::IVersionControl::SnapshotOperations:
        supported = false;
        break;
    }
    return supported;
}

Core::IVersionControl::OpenSupportMode TfsControl::openSupportMode(const QString &fileName) const
{
    if (managesFile(QFileInfo(fileName).absolutePath(), fileName)) {
        return IVersionControl::OpenMandatory;
    } else {
        return IVersionControl::NoOpen;
    }
}

bool TfsControl::vcsOpen(const QString &filename)
{
    Q_UNUSED(filename)
    return true;
}

bool TfsControl::vcsAdd(const QString &filename)
{
    const QFileInfo fi(filename);
    return tfsClient->synchronousAdd(fi.absolutePath(), fi.fileName());
}

bool TfsControl::vcsDelete(const QString &filename)
{
    const QFileInfo fi(filename);
    return tfsClient->synchronousRemove(fi.absolutePath(), fi.fileName());
}

bool TfsControl::vcsMove(const QString &from, const QString &to)
{
    const QFileInfo fromInfo(from);
    const QFileInfo toInfo(to);
    return tfsClient->synchronousMove(fromInfo.absolutePath(),
                                            fromInfo.absoluteFilePath(),
                                            toInfo.absoluteFilePath());
}

bool TfsControl::vcsCreateRepository(const QString &directory)
{
    //DONE
    return tfsClient->synchronousCreateRepository(directory);
}

QString TfsControl::vcsCreateSnapshot(const QString &)
{
    //DONE
    return QString();
}

QStringList TfsControl::vcsSnapshots(const QString &)
{
    //DONE
    return QStringList();
}

bool TfsControl::vcsRestoreSnapshot(const QString &, const QString &)
{
    //DONE
    return false;
}

bool TfsControl::vcsRemoveSnapshot(const QString &, const QString &)
{
    //DONE
    return false;
}

bool TfsControl::vcsAnnotate(const QString &file, int line)
{
    const QFileInfo fi(file);
    tfsClient->annotate(fi.absolutePath(), fi.fileName(), QString(), line);
    return true;
}

bool TfsControl::vcsCheckout(const QString &directory, const QByteArray &url)
{
    return tfsClient->synchronousClone(QString(), directory, QLatin1String(url));
}

QString TfsControl::vcsGetRepositoryURL(const QString &directory)
{
    return tfsClient->vcsGetRepositoryURL(directory);
}

void TfsControl::changed(const QVariant& v)
{
    switch (v.type()) {
    case QVariant::String:
        emit repositoryChanged(v.toString());
        break;
    case QVariant::StringList:
        emit filesChanged(v.toStringList());
        break;
    default:
        break;
    }
}

void TfsControl::emitConfigurationChanged()
{
    emit configurationChanged();
}

QStringList TfsControl::listRemoteDirectory(QString path) {
    if (path.isEmpty()) {
        path = QLatin1String("$/");
    }
    return tfsClient->listRemoteDirectory(path);
}

} // namespace Internal
} // namespace Tfs
