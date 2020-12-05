SRCDATE = "20201204"

require maxytec-dvb-modules.inc

SRC_URI[md5sum] = "7ece5d08af8033b4e1d8bc1fb98322d7"
SRC_URI[sha256sum] = "1d1370b68624b08277cc5b314bbb08e11e9e5757edaaca4a051f46c6ee9c2186"

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
