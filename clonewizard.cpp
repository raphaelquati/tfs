/**************************************************************************
**
** Copyright (c) 2013 Brian McGillion
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "clonewizard.h"
#include "clonewizardpage.h"
#include "tfsplugin.h"
#include "tfssettings.h"
#include "tfsconstants.h"
#include "tfsserverwizardpage.h"

#include <coreplugin/iversioncontrol.h>
#include <vcsbase/vcscommand.h>
#include <vcsbase/vcsbaseconstants.h>
#include <vcsbase/vcsconfigurationpage.h>
#include <QDir>


using namespace Tfs::Internal;
using namespace VcsBase;

CloneWizard::CloneWizard(const Utils::FileName &path, QWidget *parent) :
    BaseCheckoutWizard(path, parent)
{
    setTitle(tr("Cloning"));
    setStartedStatus(tr("Cloning started..."));

    //addPage(new TfsServerWizardPage);

    const Core::IVersionControl *vc = TfsPlugin::instance()->versionControl();
    if (!vc->isConfigured()) {
        addPage(new VcsConfigurationPage(vc));
    }


    CloneWizardPage *page = new CloneWizardPage;
    page->setPath(path.toString());
    addPage(page);
}

VcsCommand *CloneWizard::createCommand(Utils::FileName *checkoutDir)
{
    //TODO: cannot use password this way. It will appear in Logs!!!!

    const CloneWizardPage *cwp = 0;
    foreach (int pageId, pageIds()) {
        if ((cwp = qobject_cast<const CloneWizardPage *>(page(pageId))))
            break;
    }

    if (!cwp)
        return 0;

    const TfsSettings &settings = TfsPlugin::settings();

    const CloneOptionsPanel *optionsPanel = cwp->cloneOptionsPanel();

    QString path = cwp->path();
    QString directory = cwp->directory();

    QString workspaceName = QString(QLatin1String("QtCreator-%1")).arg(directory); //TODO: Create uniqueName!
    QString collection = QString(QLatin1String("-collection:%1")).arg(cwp->repository());
    QString workspace = QString(QLatin1String("-workspace:%1")).arg(workspaceName);

    *checkoutDir = Utils::FileName::fromString(path + QLatin1Char('/') + directory);

    //QDir().mkdir(*checkoutPath); //Tfs doesn't create the dir......

    QStringList args;
    args << QLatin1String("workspace") << QLatin1String("-new") << collection << workspaceName;

    if (optionsPanel->useAuthentication()) {
        args = TfsClient::addAuthenticationOptions(args, optionsPanel->authUsername(), optionsPanel->authPassword());
    }

    QStringList args2;
    args2 << QLatin1String("workfold") << QLatin1String("-map") << collection << workspace << QLatin1String("$/") << path;

    if (optionsPanel->useAuthentication()) {
        args2 = TfsClient::addAuthenticationOptions(args2, optionsPanel->authUsername(), optionsPanel->authPassword());
    }

    QStringList args3;
    args3 << QLatin1String("get") << QLatin1String("-all") << QLatin1String("-recursive");

    if (optionsPanel->useAuthentication()) {
        args3 = TfsClient::addAuthenticationOptions(args3, optionsPanel->authUsername(), optionsPanel->authPassword());
    }

    VcsCommand *command = new VcsCommand(settings.binaryPath(), path,
                                         QProcessEnvironment::systemEnvironment());

    command->addJob(args, -1);
    command->addJob(args2, -1);
    command->addJob(args3, -1);

    return command;


    //Check if dir is already controlled (tf workfold)

    //Check if eula was Accepted (in string tf eula);
    //OPen question. Yes:
            //tf eula -accept

    //Credentials (on error): try use SSH Prompt (like others mechanisms). In Windows the user need to use Credential Manager

   //tf workspace -new -collection:"https://tfs.codeplex.com:443/tfs/TFS29/" /login:snd\raphaelquati_cp
   //tf workfold -map -workspace:test $/ /home/raphael.couto/develop/projetos/codeplex
   //tf workfold -map -workspace:test $/  C:\Quati\develop\codeplex -workspace:WRK156 -collection:https://tfs.codeplex.com:443/tfs/TFS29/

   //tf get -all -recursive
}
