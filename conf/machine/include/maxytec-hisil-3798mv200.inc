DISTRO_FEATURES_append = " opengl"

DISTRO_FEATURES_remove += "x11 wayland directfb"

KERNELVERSION = "4.4.35"

PREFERRED_PROVIDER_virtual/egl ?= "maxytec-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "maxytec-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "maxytec-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libopencl ?= "maxytec-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "maxytec-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"

PREFERRED_PROVIDER_virtual/blindscan-dvbc = "maxytec-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "maxytec-dvb-modules-${MACHINE}"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-${HICHIPSET}', 'maxytec-bootlogo-${MACHINE} maxytec-libs-${MACHINE} maxytec-param-${MACHINE} maxytec-bootargs-${MACHINE} maxytec-fastboot-${MACHINE}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'hisil-recovery', 'maxytec-recovery-${MACHINE}' , '', d)} \
	maxytec-dvb-modules-${MACHINE} \
	${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'maxytec-mali-${MACHINE} kernel-module-mali-${MACHINE}' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'bluetooth', 'kernel-module-btusb bluez5' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'maxytec-resizerootfs partitions-by-name' , '', d)} \
	${@bb.utils.contains('MACHINE_FEATURES', 'wol', 'maxytec-ethwol' , '', d)} \
	gstreamer1.0-plugin-dvbmediasink \
	firmware-rt2870 \
	firmware-rtl8192cu \
	kernel-module-extrawlan-rtl8192fu \
	kernel-module-extrawlan-rt8188fu \
	kernel-module-rt2800usb \
	kernel-module-rtl8192cu \
	"

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

CMDLINE ?= "console=ttyAMA0,115200n8"

KERNEL_MODULE_AUTOLOAD += "mali"

PREFERRED_PROVIDER_virtual/kernel = "linux-maxytec"
PREFERRED_VERSION_linux-maxytec = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

MTD_BOOTFS = "mmcblk0p4"
MTD_ROOTFS = "mmcblk0p20"
MTD_KERNEL = "mmcblk0p19"
MTD_BLACK  = "mmcblk0"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.tar.bz2"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/maxytec-oem.inc

IMAGE_CLASSES += "maxytec-fastboot8gb_image"
IMAGE_FSTYPES += "maxytecfastboot8gb"

IMAGE_CMD_maxytecfastboot8gb_append = " \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}; \
	cp -f ${IMGDEPLOYDIR}/bootoptions.img ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/bootoptions.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/update_bootargs_${MACHINETYPE}.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/update_bootargs_${MACHINE}.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/bootargs-8gb.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/pq_param.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/baseparam.img ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/baseparam.img; \
	if [ -e ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/recovery.bin ]; then \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/recovery.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/recovery.bin; \
	fi; \
	cp -f ${DEPLOY_DIR_IMAGE}/maxytec-partitions-${MACHINE}/${MACHINE}/logo.img ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/logo.img; \
	echo "${MACHINE}-${DATE}-RECOVERY" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/${IMAGEDIR}/recoveryversion; \
	echo "***** ATTENTION *****" >${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This RECOVERY only need when you have issue access the MULTIBOOT MENU" >>${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "The ${IMAGE_NAME}_recovery_emmc.zip should been install normally once (or if there is an update.)" >>${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This is needed for avoid images conflicts as the partition layout (bootargs) is of huge essential." >>${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "A small change can destroy all your install images. So we can better leave it and not install it if it's not need." >>${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY} ; \
	zip -r ../${IMAGE_NAME}_recovery_emmc.zip *; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/${IMAGEDIRRECOVERY}; \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/uImage; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/rootfs.tar; \
	echo "${IMAGE_NAME}" > ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${MACHINE/${IMAGEDIR}/donate.txt; \
	echo "${IMAGE_NAME}_usb.zip" > ${DEPLOY_DIR_IMAGE}/${MACHINE}/unforce_${MACHINE}.txt; \
	echo "Rename the unforce_${MACHINE}.txt to force_${MACHINE}.txt and move it to the root of your usb-stick" > ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	echo "When you enter the recovery menu then it will force to install the image ${IMAGE_NAME}_usb.zip in the linux1 selection" >> ${DEPLOY_DIR_IMAGE}/${MACHINE}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	cd ${DEPLOY_DIR_IMAGE}/${MACHINE}; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/${MACHINE}; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"
