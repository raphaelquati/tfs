#include "tfsclient.h"
#include "tfsconstants.h"
#include <QFileInfo>
#include <QSignalMapper>

namespace Tfs {
namespace Internal {

TfsClient::TfsClient(TfsSettings *settings):
    VcsBase::VcsBaseClient(settings)
{
}

TfsSettings *TfsClient::settings() const
{
    return dynamic_cast<TfsSettings *>(VcsBase::VcsBaseClient::settings());
}

bool TfsClient::synchronousClone(const QString &workingDir,
                      const QString &srcLocation,
                      const QString &dstLocation,
                      const QStringList &extraOptions)
{
    return false;
}


bool TfsClient::manifestSync(const QString &repository, const QString &filename)
{
    return false;
}

QString TfsClient::branchQuerySync(const QString &repositoryRoot)
{
    return QLatin1String("todo");
}

QStringList TfsClient::parentRevisionsSync(const QString &workingDirectory,
                         const QString &file /* = QString() */,
                         const QString &revision)
{
    return QStringList();
}

QString TfsClient::shortDescriptionSync(const QString &workingDirectory, const QString &revision,
                          const QString &format /* = QString() */)
{
    return QLatin1String("todo");
}

QString TfsClient::shortDescriptionSync(const QString &workingDirectory, const QString &revision)
{
    return QLatin1String("todo");
}

void TfsClient::incoming(const QString &repositoryRoot, const QString &repository)
{

}

void TfsClient::outgoing(const QString &repositoryRoot)
{

}

QString TfsClient::vcsGetRepositoryURL(const QString &directory)
{
    return QLatin1String("todo");
}


bool TfsClient::managesFile(const QString &workingDirectory, const QString &fileName) const
{
    return false;
}



void TfsClient::annotate(const QString &workingDir, const QString &file,
                               const QString revision, int lineNumber,
                               const QStringList &extraOptions)
{
//    QStringList args(extraOptions);
//    args << QLatin1String("-u") << QLatin1String("-c") << QLatin1String("-d");
//    VcsBaseClient::annotate(workingDir, file, revision, lineNumber, args);
}

void TfsClient::commit(const QString &repositoryRoot, const QStringList &files,
                             const QString &commitMessageFile,
                             const QStringList &extraOptions)
{
//    QStringList args(extraOptions);
//    args << QLatin1String("--noninteractive") << QLatin1String("-l") << commitMessageFile << QLatin1String("-A");
//    VcsBaseClient::commit(repositoryRoot, files, commitMessageFile, args);
}

void TfsClient::diff(const QString &workingDir, const QStringList &files,
                           const QStringList &extraOptions)
{
//    QStringList args(extraOptions);
//    args << QLatin1String("-g") << QLatin1String("-p") << QLatin1String("-U 8");
//    VcsBaseClient::diff(workingDir, files, args);
}

void TfsClient::import(const QString &repositoryRoot, const QStringList &files,
                             const QStringList &extraOptions)
{
//    VcsBaseClient::import(repositoryRoot, files,
//                          QStringList(extraOptions) << QLatin1String("--no-commit"));
}

void TfsClient::revertAll(const QString &workingDir, const QString &revision,
                                const QStringList &extraOptions)
{
//    VcsBaseClient::revertAll(workingDir, revision,
//                             QStringList(extraOptions) << QLatin1String("--all"));
}

void TfsClient::view(const QString &source, const QString &id,
                           const QStringList &extraOptions)
{
//    QStringList args;
//    args << QLatin1String("log") << QLatin1String("-p") << QLatin1String("-g");
//    VcsBaseClient::view(source, id, args << extraOptions);
}

QString TfsClient::findTopLevelForFile(const QFileInfo &file) const
{
    const QString repositoryCheckFile =
            QLatin1String(Constants::TFSREPO) + QLatin1String("/properties.tf1");
    return file.isDir() ?
                VcsBase::VcsBasePlugin::findRepositoryForDirectory(file.absoluteFilePath(),
                                                                   repositoryCheckFile) :
                VcsBase::VcsBasePlugin::findRepositoryForDirectory(file.absolutePath(),
                                                                   repositoryCheckFile);
}

Core::Id TfsClient::vcsEditorKind(VcsCommand cmd) const
{
    switch (cmd) {
    case AnnotateCommand:
        return Constants::ANNOTATELOG;
    case DiffCommand:
        return Constants::DIFFLOG;
    case LogCommand:
        return Constants::FILELOG;
    default:
        return Core::Id();
    }
}

QStringList TfsClient::revisionSpec(const QString &revision) const
{
    QStringList args;
    if (!revision.isEmpty())
        args << QLatin1String("-r") << revision;
    return args;
}


TfsClient::StatusItem TfsClient::parseStatusLine(const QString &line) const
{
    StatusItem item;

    item.flags = QLatin1String("Unknow");
    return item;
}


VcsBase::VcsBaseEditorParameterWidget *TfsClient::createDiffEditor(const QString &workingDir,
                                                        const QStringList &files,
                                                        const QStringList &extraOptions)
{
return NULL;
}


QStringList TfsClient::addAuthenticationOptions(const QStringList &args,
                                                       const QString &userName,
                                                       const QString &password)
{
    if (userName.isEmpty())
        return args;

    QString loginLine = QString(QLatin1String("-login:%1,%2")).arg(userName).arg(password);

    QStringList rc;
    rc.push_back(loginLine);

    rc.append(args);
    return rc;
}

void TfsClient::listWorkspaces()
{
    QStringList args;
    args << QLatin1String("workspaces") << QLatin1String("-computer:*") << QLatin1String("-format:xml") << QLatin1String("-collection:http://srvtfs:8080/tfs");

    addAuthenticationOptions(args, QLatin1String("****"), QLatin1String("****"));

    VcsBase::Command *command = createCommand(QLatin1String("."));
//    connect(command, SIGNAL(output(QString)),  [=](const QString &newValue) {
//        parser->parse(newValue);
//    });

    connect(command, SIGNAL(output(QString)), this, SIGNAL(parseWorkspaceOutput(QString)));
}


} // namespace Internal
} // namespace Tfs
