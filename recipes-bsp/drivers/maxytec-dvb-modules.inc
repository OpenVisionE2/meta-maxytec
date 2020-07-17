SUMMARY = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

KV = "4.4.35"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://downloads.mutant-digital.net/maxytec/${MACHINETYPE}/${MACHINETYPE}-drivers-${KV}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} = "/"

do_compile() {
}

do_populate_sysroot() {
}

do_install() {
	install -d ${D}${base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	for i in ${MACHINETYPE}_1 ${MACHINETYPE}_2 ${MACHINETYPE}_3 ${MACHINETYPE}_4; do
		echo $i >> ${D}${sysconfdir}/modules-load.d/_${MACHINE}.conf
	done
	install -d ${D}${bindir}
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f ${base_libdir}/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f ${base_libdir}/modules/${KV}/extra/hi_play.ko;
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
