#ifndef TFSSETTINGS_H
#define TFSSETTINGS_H

#include <vcsbase/vcsbaseclientsettings.h>

namespace Tfs {
namespace Internal {

class TfsSettings : public VcsBase::VcsBaseClientSettings
{
public:
    TfsSettings();
};

} // namespace Internal
} // namespace Tfs

#endif // TFSSETTINGS_H
