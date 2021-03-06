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

#include "clonewizardpage.h"
#include "cloneoptionspanel.h"
#include "tfsplugin.h"
#include "tfscontrol.h"
#include "tfsclient.h"

using namespace Tfs::Internal;

CloneWizardPage::CloneWizardPage(QWidget *parent)
        : VcsBase::BaseCheckoutWizardPage(parent),
        m_optionsPanel(new CloneOptionsPanel)
{
    setTitle(tr("Location"));
    setSubTitle(tr("Specify collection URL, root workspace directory and path."));
    setRepositoryLabel(tr("Collection URL:"));
    setBranchSelectorVisible(true);
    setDirectoryVisible(false);
    addLocalControl(m_optionsPanel);

    //connect(this, SIGNAL())
}

const CloneOptionsPanel *CloneWizardPage::cloneOptionsPanel() const
{
    return m_optionsPanel;
}

QString CloneWizardPage::directoryFromRepository(const QString &repository) const
{
    // Mercurial repositories are generally of the form protocol://repositoryUrl/repository/
    // We are just looking for repository.
    const QChar slash = QLatin1Char('/');
    QString repo = repository.trimmed();
    if (repo.endsWith(slash))
        repo.truncate(repo.size() - 1);

    // Take the basename or the repository url.
    return repo.mid(repo.lastIndexOf(slash) + 1);
}

QStringList CloneWizardPage::branches(const QString &repository, int *current)
{
    TfsPlugin::instance()->client()->setCurrentCollectionURL(repository);
    return  TfsPlugin::instance()->client()->listRemoteDirectory(QLatin1String(""));
}
