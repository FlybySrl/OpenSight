#ifndef DATAVIDEOPLAYLIST_H
#define DATAVIDEOPLAYLIST_H

#include <Data.h>

namespace fby
{
class DataVideoPlaylist : public Data
{
public:

    DataVideoPlaylist()
    {
        m_llPts_start = -1;
        m_llPts_stop = -1;
    }

    std::list<std::string>      m_lPlaylist;

    std::string     m_sMetadataFile;

    long long   m_llPts_start;
    long long   m_llPts_stop;

}; // end class DataVideoPlaylist.

DEF_PTR(DataVideoPlaylist);

} // end namespace fby.

#endif // DATAVIDEOPLAYLIST_H
