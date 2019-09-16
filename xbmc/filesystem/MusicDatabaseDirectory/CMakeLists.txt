set(SOURCES DirectoryNodeAlbum.cpp
            DirectoryNodeAlbumRecentlyAdded.cpp
            DirectoryNodeAlbumRecentlyAddedSong.cpp
            DirectoryNodeAlbumRecentlyPlayed.cpp
            DirectoryNodeAlbumRecentlyPlayedSong.cpp
            DirectoryNodeArtist.cpp
            DirectoryNode.cpp
            DirectoryNodeGrouped.cpp
            DirectoryNodeOverview.cpp
            DirectoryNodeRoot.cpp
            DirectoryNodeSingles.cpp
            DirectoryNodeSong.cpp
            DirectoryNodeYearAlbum.cpp
            DirectoryNodeYearSong.cpp
            QueryParams.cpp)

set(HEADERS DirectoryNode.h
            DirectoryNodeAlbum.h
            DirectoryNodeAlbumRecentlyAdded.h
            DirectoryNodeAlbumRecentlyAddedSong.h
            DirectoryNodeAlbumRecentlyPlayed.h
            DirectoryNodeAlbumRecentlyPlayedSong.h
            DirectoryNodeArtist.h
            DirectoryNodeGrouped.h
            DirectoryNodeOverview.h
            DirectoryNodeRoot.h
            DirectoryNodeSingles.h
            DirectoryNodeSong.h
            DirectoryNodeYearAlbum.h
            DirectoryNodeYearSong.h
            QueryParams.h)

core_add_library(musicdatabasedirectory)
