#ifndef TFSCONSTANTS_H
#define TFSCONSTANTS_H

#include <QDebug>

namespace VcsBase {
namespace Constants
{
    const char VCS_ID_TFS[] = "T.Tfs";
}
}

namespace Tfs {
namespace Constants {

enum { debug = 0 };

const char ACTION_ID[] = "tfs.Action";
const char MENU_ID[] = "tfs.Menu";

const char TFSDEFAULT[] = "tf";
const char TFSREPO[] = "$tf";
const char TFS_CONTEXT[] = "Tfs Context";

//// Base editor parameters
//const char COMMANDLOG_ID[] = "TFS Command Log Editor";
//const char COMMANDLOG_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("VCS", "TFS Command Log Editor");
//const char COMMANDLOG[] = "TFS Command Log Editor";
//const char COMMANDAPP[] = "application/vnd.nokia.text.scs_tfs_commandlog";
//const char COMMANDEXT[] = "vcsTfsCommand";

//const char FILELOG_ID[] = "TFS File Log Editor";
//const char FILELOG_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("VCS", "TFS File Log Editor");
const char FILELOG[] = "TFS File Log Editor";
//const char LOGAPP[] = "application/vnd.nokia.text.scs_tfs_log";
//const char LOGEXT[] = "vcsTfsLog";

//const char ANNOTATELOG_ID[] = "TFS Annotation Editor";
//const char ANNOTATELOG_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("VCS", "TFS Annotation Editor");
const char ANNOTATELOG[] = "TFS Annotation Editor";
//const char ANNOTATEAPP[] = "application/vnd.nokia.text.scs_tfs_annotatelog";
//const char ANNOTATEEXT[] = "vcsTfsAnnotate";

//const char DIFFLOG_ID[] = "TFS Diff Editor";
//const char DIFFLOG_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("VCS", "TFS Diff Editor");
const char DIFFLOG[] = "TFS Diff Editor";
//const char DIFFAPP[] = "text/x-patch";
//const char DIFFEXT[] = "diff";


// Repository menu actions
const char WORKSPACES[] = "Tfs.Action.Workspaces";


} // namespace Constants
} // namespace Tfs

#endif // TFSCONSTANTS_H

