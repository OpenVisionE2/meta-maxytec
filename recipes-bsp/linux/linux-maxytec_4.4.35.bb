DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"
PACKAGE_ARCH = "${MACHINE_ARCH}"

COMPATIBLE_MACHINE = "^(multibox|multiboxplus)$"

KERNEL_RELEASE = "4.4.35"

SRCDATE = "20200219"

inherit kernel machine_kernel_pr samba_change_dialect

SRC_URI[md5sum] = "f9e67e2d0ceab518510413f8f4315bc3"
SRC_URI[sha256sum] = "45ae717b966a74326fd7297d81b3a17fd5b3962b7704170682a615ca7cdec644"

SRC_URI = "http://source.mynonpublic.com/maxytec/linux-${PV}-${SRCDATE}-${ARCH}.tar.gz \
	file://defconfig \
	file://${OPENVISION_BASE}/meta-openvision/recipes-linux/kernel-patches/kernel-add-support-for-gcc${VISIONGCCVERSION}.patch \
	file://0002-log2-give-up-on-gcc-constant-optimizations.patch \
	file://0003-dont-mark-register-as-const.patch \
	file://0001-remote.patch \
	file://initramfs-subdirboot.cpio.gz;unpack=0 \
	file://HauppaugeWinTV-dualHD.patch \
	file://dib7000-linux_4.4.179.patch \
	file://dvb-usb-linux_4.4.179.patch \
	file://wifi-linux_4.4.183.patch \
	file://findkerneldevice.sh \
	file://0004-linux-fix-buffer-size-warning-error.patch \
	file://0005-xbox-one-tuner-4.4.patch \
	file://0006-dvb-media-tda18250-support-for-new-silicon-tuner.patch \
	file://0007-dvb-mn88472-staging.patch \
	file://mn88472_reset_stream_ID_reg_if_no_PLP_given.patch \
	"

# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "${KERNEL_PACKAGE_NAME}-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "${KERNEL_PACKAGE_NAME}-image-${KERNEL_VERSION}"

S = "${WORKDIR}/linux-${PV}"
B = "${WORKDIR}/build"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "uImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

FILES_${KERNEL_PACKAGE_NAME}-image = "/${KERNEL_IMAGEDEST}/findkerneldevice.sh"

kernel_do_configure_prepend() {
    install -d ${B}/usr
    install -m 0644 ${WORKDIR}/initramfs-subdirboot.cpio.gz ${B}/
}

kernel_do_install_append() {
	install -d ${D}${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/findkerneldevice.sh ${D}/${KERNEL_IMAGEDEST}
}

pkg_postinst_${KERNEL_PACKAGE_NAME}-image() {
	if [ "x$D" == "x" ]; then
		if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
			/${KERNEL_IMAGEDEST}/./findkerneldevice.sh
			dd if=${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} of=/dev/kernel
		fi
	fi
	true
}

do_rm_work() {
}

export KCFLAGS = "-Wno-error=missing-attributes \
                  "
