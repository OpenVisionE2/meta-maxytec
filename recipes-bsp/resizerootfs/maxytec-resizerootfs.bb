DESCRIPTION = "MaxyTec resize rootfs"
require conf/license/license-gplv2.inc

COMPATIBLE_MACHINE = "^(multibox|multiboxse)$"

RDEPENDS_${PN} = "e2fsprogs-resize2fs"

SRC_URI = "file://resizerootfs"

inherit update-rc.d

INITSCRIPT_NAME = "resizerootfs"
INITSCRIPT_PARAMS = "start 7 S ."

do_install () {
	install -m 0755 -d ${D}${INIT_D_DIR}
	install -m 0755 ${WORKDIR}/resizerootfs ${D}${INIT_D_DIR}/resizerootfs
}
