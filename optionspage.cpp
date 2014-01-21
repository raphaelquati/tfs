#include "optionspage.h"
#include "tfssettings.h"
#include "tfsplugin.h"
#include "tfsconstants.h"

#include <coreplugin/icore.h>
#include <utils/pathchooser.h>
#include <vcsbase/vcsbaseconstants.h>

#include <QTextStream>

using namespace Tfs::Internal;
using namespace Tfs;

OptionsPageWidget::OptionsPageWidget(QWidget *parent) :
        QWidget(parent)
{
    m_ui.setupUi(this);
    m_ui.commandChooser->setExpectedKind(Utils::PathChooser::ExistingCommand);
    m_ui.commandChooser->setPromptDialogTitle(tr("Tfs Command"));
}

TfsSettings OptionsPageWidget::settings() const
{
    TfsSettings s = TfsPlugin::instance()->settings();
    s.setValue(TfsSettings::binaryPathKey, m_ui.commandChooser->rawPath());
    s.setValue(TfsSettings::userNameKey, m_ui.defaultUsernameLineEdit->text().trimmed());
    s.setValue(TfsSettings::userEmailKey, m_ui.defaultEmailLineEdit->text().trimmed());
//    s.setValue(MercurialSettings::logCountKey, m_ui.logEntriesCount->value());
//    s.setValue(MercurialSettings::timeoutKey, m_ui.timeout->value());
//    s.setValue(MercurialSettings::promptOnSubmitKey, m_ui.promptOnSubmitCheckBox->isChecked());
    return s;
}

void OptionsPageWidget::setSettings(const TfsSettings &s)
{
    m_ui.commandChooser->setPath(s.stringValue(TfsSettings::binaryPathKey));
    m_ui.defaultUsernameLineEdit->setText(s.stringValue(TfsSettings::userNameKey));
    m_ui.defaultEmailLineEdit->setText(s.stringValue(TfsSettings::userEmailKey));
//    m_ui.logEntriesCount->setValue(s.intValue(MercurialSettings::logCountKey));
//    m_ui.timeout->setValue(s.intValue(MercurialSettings::timeoutKey));
//    m_ui.promptOnSubmitCheckBox->setChecked(s.boolValue(MercurialSettings::promptOnSubmitKey));
}

QString OptionsPageWidget::searchKeywords() const
{
    QString rc;
    QLatin1Char sep(' ');
    QTextStream(&rc)
            << sep << m_ui.configGroupBox->title()
            << sep << m_ui.tfsCommandLabel->text()
            << sep << m_ui.userGroupBox->title()
            << sep << m_ui.defaultUsernameLabel->text()
            << sep << m_ui.defaultEmailLabel->text()
//            << sep << m_ui.miscGroupBox->title()
//            << sep << m_ui.showLogEntriesLabel->text()
//            << sep << m_ui.timeoutSecondsLabel->text()
//            << sep << m_ui.promptOnSubmitCheckBox->text()
               ;
    rc.remove(QLatin1Char('&'));
    return rc;
}

OptionsPage::OptionsPage()
{
    setId(VcsBase::Constants::VCS_ID_TFS);
    setDisplayName(tr("Tfs"));
}

QWidget *OptionsPage::widget()
{
    if (!optionsPageWidget)
        optionsPageWidget = new OptionsPageWidget();
    optionsPageWidget->setSettings(TfsPlugin::instance()->settings());
    if (m_searchKeywords.isEmpty())
        m_searchKeywords = optionsPageWidget->searchKeywords();
    return optionsPageWidget;
}

void OptionsPage::apply()
{
    if (!optionsPageWidget)
        return;
    TfsPlugin *plugin = TfsPlugin::instance();
    const TfsSettings newSettings = optionsPageWidget->settings();
    if (newSettings != plugin->settings()) {
        //assume success and emit signal that settings are changed;
        plugin->setSettings(newSettings);
        newSettings.writeSettings(Core::ICore::settings());
        emit settingsChanged();
    }
}

//bool OptionsPage::matches(const QString &s) const
//{
//    return m_searchKeywords.contains(s, Qt::CaseInsensitive);
//}
