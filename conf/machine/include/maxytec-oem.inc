# We know about rtc
include conf/machine/include/build-extras.inc

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "\
    kernel-module-cdfs \
    ${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'resizerootfs' , '', d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'adwol', 'maxytec-ethwol' , '', d)} \
    "

MACHINE_EXTRA_RRECOMMENDS += " \
    gstreamer1.0-plugin-dvbmediasink \
    "

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    maxytec-dvb-modules-${MACHINE} \
    "

include conf/machine/include/autoload-filesystems.inc
require conf/machine/include/soc-family.inc

MACHINE_FEATURES += "3dtv alsa hdmicec switchoff HDMI hisil-3798mv200 mali emmc multitranscoding himedia blindscan-dvbs dvb-c adwol fastboot"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"

MTD_ROOTFS = "mmcblk0p21"
MTD_KERNEL = "mmcblk0p20"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.tar.bz2"

IMAGE_FSTYPES += " maxytecfastboot8gb"

EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"
