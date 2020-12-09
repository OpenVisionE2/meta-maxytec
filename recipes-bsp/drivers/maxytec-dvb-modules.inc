SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

PROVIDES = "virtual/blindscan-dvbs"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://downloads.mutant-digital.net/maxytec/${MACHINE}/${MACHINE}-drivers-${KV}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} = "/"

do_compile() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modprobe.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	for i in ${MACHINE}_1 ${MACHINE}_2 ${MACHINE}_3 ${MACHINE}_4; do
		echo blacklist $i >> ${D}${sysconfdir}/modprobe.d/${MACHINE}.conf
	done
	install -d ${D}${bindir}
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}

RDEPENDS_${PN} = "libjpeg-turbo"
PROVIDES += "virtual/blindscan-dvbc virtual/blindscan-dvbs"
RPROVIDES_${PN} += "virtual/blindscan-dvbc virtual/blindscan-dvbs"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
}

do_package_qa() {
}
