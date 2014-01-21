#ifndef TFS_H
#define TFS_H

#include "tfs_global.h"

#include "tfssettings.h"
#include "tfsclient.h"
#include "optionspage.h"

#include <vcsbase/vcsbaseclient.h>
#include <vcsbase/vcsbaseplugin.h>
#include <coreplugin/icontext.h>
#include <coreplugin/locator/commandlocator.h>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace Core {
class ActionContainer;
class ActionManager;
class ICore;
class Id;
class IEditor;
} // namespace Core


namespace Utils { class ParameterAction; }
namespace Locator { class CommandLocator; }

namespace Tfs {
namespace Internal {

class TfsPlugin : public VcsBase::VcsBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Tfs.json")

public:
    TfsPlugin();
    ~TfsPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();


    static TfsPlugin *instance() { return m_instance; }
    TfsClient *client() const { return m_client; }

    static const TfsSettings &settings();
    void setSettings(const TfsSettings &settings);

private slots:
//    // File menu action slots
//    void addCurrentFile();
//    void annotateCurrentFile();
//    void diffCurrentFile();
//    void logCurrentFile();
//    void revertCurrentFile();
//    void statusCurrentFile();

//    // Directory menu action slots
//    void diffRepository();
//    void logRepository();
//    void revertMulti();
//    void statusMulti();

    // Repository menu action slots
    void workspaces();

//    void pull();
//    void push();
//    void update();
//    void import();
//    void incoming();
//    void outgoing();
//    void commit();
//    void showCommitWidget(const QList<VcsBase::VcsBaseClient::StatusItem> &status);
//    void commitFromEditor();
//    void diffFromEditorSelected(const QStringList &files);

protected:
    void updateActions(VcsBase::VcsBasePlugin::ActionState);
    bool submitEditorAboutToClose();

private:
    void createMenu();
    void createSubmitEditorActions();
    void createFileActions(const Core::Context &context);
    void createDirectoryActions(const Core::Context &context);
    void createRepositoryActions(const Core::Context &context);
    void createRepositoryManagementActions(const Core::Context &context);
    void createLessUsedActions(const Core::Context &context);

    static TfsPlugin *m_instance;
    TfsSettings tfsSettings;
    OptionsPage *optionsPage;
    TfsClient *m_client;

    Core::ICore *core;
    Core::CommandLocator *m_commandLocator;
    Core::ActionContainer *tfsContainer;

    QList<QAction *> m_repositoryActionList;
    Utils::ParameterAction *workspaceEdit;


    QAction *m_menuAction;
};

} // namespace Internal
} // namespace tfs

#endif // TFS_H

