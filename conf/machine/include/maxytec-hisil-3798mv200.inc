DISTRO_FEATURES_append = " opengl"

DISTRO_FEATURES_remove += "x11 wayland directfb"

PREFERRED_PROVIDER_virtual/egl ?= "maxytec-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "maxytec-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "maxytec-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libopencl ?= "maxytec-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgbm ?= "maxytec-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"

PREFERRED_PROVIDER_virtual/blindscan-dvbc = "maxytec-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "maxytec-dvb-modules-${MACHINE}"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-${HICHIPSET}', 'maxytec-bootlogo-${HICHIPSET} maxytec-libs-${HICHIPSET} maxytec-param-${HICHIPSET} maxytec-bootargs-${MACHINE} maxytec-fastboot-${MACHINE} maxytec-tntfs-${HICHIPSET}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisi-recovery', 'maxytec-recovery-${MACHINE}' , '', d)} \
	"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "\
	${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'maxytec-mali-${HICHIPSET} kernel-module-mali-${HICHIPSET}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'bluetooth', 'kernel-module-btusb bluez5' , '', d)} \
	"

MACHINE_EXTRA_RRECOMMENDS += "\
	ffmpeg \
	"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

CMDLINE ?= "console=ttyAMA0,115200n8"

KERNEL_MODULE_AUTOLOAD += "mali"

PREFERRED_PROVIDER_virtual/kernel = "linux-maxytec"
PREFERRED_VERSION_linux-maxytec = "4.4.35"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

MTD_ROOTFS = "mmcblk0p20"
MTD_KERNEL = "mmcblk0p19"
MTD_BLACK  = "mmcblk0"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.tar.bz2"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/maxytec-oem.inc
