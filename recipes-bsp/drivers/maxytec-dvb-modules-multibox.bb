SRCDATE = "20200622"

require maxytec-dvb-modules.inc

SRC_URI[md5sum] = "99484caab1163d69ea9c04db1dd82dd0"
SRC_URI[sha256sum] = "58aad3348c457eb77d91538425889553004fd93a9be617d7d7cb60b9ab429db1"

COMPATIBLE_MACHINE = "^(multibox)$"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

/usr/bin/turnoff_power
EOF
}
