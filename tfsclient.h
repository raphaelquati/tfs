#ifndef TFSCLIENT_H
#define TFSCLIENT_H

#include "tfssettings.h"
#include "tfsdatatypes.h"

#include <vcsbase/vcsbaseclient.h>
#include <vcsbase/vcsbaseplugin.h>

namespace Tfs {
namespace Internal {

class TfsClient : public VcsBase::VcsBaseClient
{
    Q_OBJECT

public:
    TfsClient(TfsSettings *settings);

    TfsSettings *settings() const;

    bool synchronousClone(const QString &workingDir,
                          const QString &srcLocation,
                          const QString &dstLocation,
                          const QStringList &extraOptions = QStringList());
    bool manifestSync(const QString &repository, const QString &filename);
    QString branchQuerySync(const QString &repositoryRoot);
    QStringList parentRevisionsSync(const QString &workingDirectory,
                             const QString &file /* = QString() */,
                             const QString &revision);
    QString shortDescriptionSync(const QString &workingDirectory, const QString &revision,
                              const QString &format /* = QString() */);
    QString shortDescriptionSync(const QString &workingDirectory, const QString &revision);
    void incoming(const QString &repositoryRoot, const QString &repository = QString());
    void outgoing(const QString &repositoryRoot);
    QString vcsGetRepositoryURL(const QString &directory);


    bool managesFile(const QString &workingDirectory, const QString &fileName) const;

    void annotate(const QString &workingDir, const QString &file,
                  const QString revision = QString(), int lineNumber = -1,
                  const QStringList &extraOptions = QStringList());
    void commit(const QString &repositoryRoot, const QStringList &files,
                const QString &commitMessageFile,
                const QStringList &extraOptions = QStringList());
    void diff(const QString &workingDir, const QStringList &files = QStringList(),
              const QStringList &extraOptions = QStringList());
    void import(const QString &repositoryRoot, const QStringList &files,
                const QStringList &extraOptions = QStringList());
    void revertAll(const QString &workingDir, const QString &revision = QString(),
                   const QStringList &extraOptions = QStringList());
    void view(const QString &source, const QString &id,
              const QStringList &extraOptions = QStringList());

    QString findTopLevelForFile(const QFileInfo &file) const;

    static QStringList addAuthenticationOptions(const QStringList &args,
                                                           const QString &userName,
                                                           const QString &password);

    //Tfs Specifics
    void listWorkspaces();

    QStringList listRemoteDirectory(QString path);

    void setCurrentCollectionURL(const QString &url);
protected:
    Core::Id vcsEditorKind(VcsCommandTag cmd) const;
    QStringList revisionSpec(const QString &revision) const;
    VcsBase::VcsBaseEditorParameterWidget *createDiffEditor(const QString &workingDir,
                                                            const QStringList &files,
                                                            const QStringList &extraOptions);
    StatusItem parseStatusLine(const QString &line) const;

private:
    QString m_currentCollectionURL;

signals:
    void parseWorkspaceOutput(const QString &output);


};

} // namespace Internal
} // namespace Tfs

#endif // TFSCLIENT_H
