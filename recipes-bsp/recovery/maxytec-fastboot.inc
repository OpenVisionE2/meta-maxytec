SUMMARY = "${MACHINE} fastboot files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${SRCDATE}"

inherit deploy

SRC_URI = "http://downloads.mutant-digital.net/maxytec/${MACHINETYPE}/${MACHINETYPE}-fastboot-${SRCDATE}.zip"

S = "${WORKDIR}"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINETYPE}/fastboot.bin ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}
}

addtask deploy before do_build after do_install
