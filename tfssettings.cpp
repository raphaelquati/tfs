#include "tfssettings.h"
#include "tfsconstants.h"

namespace Tfs {
namespace Internal {

TfsSettings::TfsSettings()
{
    setSettingsGroup(QLatin1String("TFS"));
    // Override default binary path
    declareKey(binaryPathKey, QLatin1String(Constants::TFSDEFAULT));
    //declareKey(diffIgnoreWhiteSpaceKey, false);
    //declareKey(diffIgnoreBlankLinesKey, false);

}

} // namespace Internal
} // namespace Tfs
