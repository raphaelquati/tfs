#include "tfsplugin.h"
#include "tfsconstants.h"
#include "tfssettings.h"
#include "tfsclient.h"
#include "tfscontrol.h"
#include "clonewizard.h"
#include "tfsworkspacedialog.h"

#include <coreplugin/locator/commandlocator.h>

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>

using namespace Tfs::Internal;
using namespace Tfs;
using namespace VcsBase;
using namespace Utils;

TfsPlugin *TfsPlugin::m_instance = 0;

TfsPlugin::TfsPlugin()  :
    optionsPage(0),
    m_client(0),
    core(0),
    m_commandLocator(0)
{
    m_instance = this;
}

TfsPlugin::~TfsPlugin()
{
    if (m_client) {
        delete m_client;
        m_client = 0;
    }

    m_instance = 0;
}

bool TfsPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    Core::Context context(Constants::TFS_CONTEXT);

//    typedef VcsEditorFactory<MercurialEditor> TfsEditorFactory;
    m_client = new TfsClient(&tfsSettings);
    initializeVcs(new TfsControl(m_client), context);

    optionsPage = new OptionsPage();
    addAutoReleasedObject(optionsPage);
    tfsSettings.readSettings(core->settings());

    connect(m_client, SIGNAL(changed(QVariant)), versionControl(), SLOT(changed(QVariant)));
    //connect(m_client, SIGNAL(needUpdate()), this, SLOT(update()));

//    static const char *describeSlot = SLOT(view(QString,QString));
//    const int editorCount = sizeof(editorParameters)/sizeof(editorParameters[0]);
//    for (int i = 0; i < editorCount; i++)
//        addAutoReleasedObject(new MercurialEditorFactory(editorParameters + i, m_client, describeSlot));

//    addAutoReleasedObject(new VcsSubmitEditorFactory<CommitEditor>(&submitEditorParameters));


    auto cloneWizardFactory = new BaseCheckoutWizardFactory;
    cloneWizardFactory->setId(QLatin1String(VcsBase::Constants::VCS_ID_TFS));
    cloneWizardFactory->setIcon(QIcon(QLatin1String(":/tfs/images/tfs.png")));
    cloneWizardFactory->setDescription(tr("Setup a new Workspace and try to get last version from Team Foundation."));
    cloneWizardFactory->setDisplayName(tr("Tfs Clone"));
    cloneWizardFactory->setWizardCreator([this] (const FileName &path, QWidget *parent) {
        return new CloneWizard(path, parent);
    });
    addAutoReleasedObject(cloneWizardFactory);

    const QString prefix = QLatin1String("tf");
    m_commandLocator = new Core::CommandLocator("TFS", prefix, prefix);
    addAutoReleasedObject(m_commandLocator);


    createMenu();

    createSubmitEditorActions();

    return true;
}

const TfsSettings &TfsPlugin::settings()
{
    return m_instance->tfsSettings;
}

void TfsPlugin::setSettings(const TfsSettings &settings)
{
    if (settings != m_instance->tfsSettings) {
        m_instance->tfsSettings = settings;
        static_cast<TfsControl *>(m_instance->versionControl())->emitConfigurationChanged();
    }
}

void TfsPlugin::workspaces()
{
    TfsWorkspaceDialog d;

    d.exec();
}


void TfsPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized method, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag TfsPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void TfsPlugin::createMenu()
{
    Core::Context context(Core::Constants::C_GLOBAL);

    // Create menu item for Mercurial
    tfsContainer = Core::ActionManager::createMenu("Tfs.TfsMenu");
    QMenu *menu = tfsContainer->menu();
    menu->setTitle(tr("&TFS"));


    createFileActions(context);
    tfsContainer->addSeparator(context);
    createDirectoryActions(context);
    tfsContainer->addSeparator(context);
    createRepositoryActions(context);
    tfsContainer->addSeparator(context);
    createRepositoryManagementActions(context);
    tfsContainer->addSeparator(context);
    createLessUsedActions(context);

    // Request the Tools menu and add the Tfs menu to it
    Core::ActionContainer *toolsMenu = Core::ActionManager::actionContainer(Core::Id(Core::Constants::M_TOOLS));
    toolsMenu->addMenu(tfsContainer);
    m_menuAction = tfsContainer->menu()->menuAction();
}

void TfsPlugin::createSubmitEditorActions()
{
}

void TfsPlugin::createFileActions(const Core::Context &context)
{
}

void TfsPlugin::createDirectoryActions(const Core::Context &context)
{
}

void TfsPlugin::createRepositoryActions(const Core::Context &context)
{
    QAction *action = new QAction(tr("Workspaces..."), this);
    m_repositoryActionList.append(action);
    Core::Command *command = Core::ActionManager::registerAction(action, Core::Id(Constants::WORKSPACES), context);
    connect(action, SIGNAL(triggered()), this, SLOT(workspaces()));
    tfsContainer->addAction(command);
    m_commandLocator->appendCommand(command);

    action->setEnabled(m_instance->versionControl()->isConfigured());
}

void TfsPlugin::createRepositoryManagementActions(const Core::Context &context)
{
}

void TfsPlugin::createLessUsedActions(const Core::Context &context)
{
}

void TfsPlugin::updateActions(VcsBase::VcsBasePlugin::ActionState)
{
}

bool TfsPlugin::submitEditorAboutToClose()
{
    return false;
}

