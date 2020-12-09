# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

BOX_BRAND = "maxytec"

require conf/machine/include/soc-family.inc

MACHINE_FEATURES += "alsa hdmicec switchoff hisil-${HICHIPSET} mali emmc multitranscoding blindscan-dvbs dvb-c wol fastboot hisil HDMI hisil-recovery mountboot"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"

EXTRA_ALSA = "mv200"

RCTYPE = "27"
RCNAME = "maxytec1"
