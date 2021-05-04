require recipes-mediacenter/kodi/stb-kodi_19.bb

SRC_URI_append = " file://HiPlayer-for-kodi-19.patch \
	file://HiPlayer-defaultplayer-19.patch \
	file://HiPlayer-Subs-19.patch \
	"

PROVIDES += "virtual/kodi"
RPROVIDES_${PN} += "virtual/kodi"
PROVIDES += "kodi"
RPROVIDES_${PN} += "kodi"

RDEPENDS_${PN} += "maxytec-mali-${MACHINE}"

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=mali-cortexa15 \
    -DWITH_FFMPEG=stb \
"
