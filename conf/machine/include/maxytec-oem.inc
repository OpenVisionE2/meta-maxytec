# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

BOX_BRAND = "maxytec"

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "\
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'maxytec-resizerootfs partitions-by-name' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'wol', 'maxytec-ethwol' , '', d)} \
	"

MACHINE_EXTRA_RRECOMMENDS += "\
	gstreamer1.0-plugin-dvbmediasink \
	"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	maxytec-dvb-modules-${MACHINE} \
	"


require conf/machine/include/soc-family.inc

MACHINE_FEATURES += "alsa hdmicec switchoff hisil-3798mv200 mali emmc multitranscoding himedia blindscan-dvbs dvb-c wol fastboot hisil HDMI"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

RCTYPE = "0"

MTD_ROOTFS = "mmcblk0p21"
MTD_KERNEL = "mmcblk0p20"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.tar.bz2"

EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"
