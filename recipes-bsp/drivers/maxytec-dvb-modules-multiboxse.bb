SRCDATE = "20201204"

require maxytec-dvb-modules.inc

SRC_URI[md5sum] = "d1b1ef9676bd54e8c1e46f8db67627d8"
SRC_URI[sha256sum] = "1efc0331f9123bd2d69ab61d075186c3830b0c3c3e942c01949e5bc52c63d175"

COMPATIBLE_MACHINE = "^(multiboxse)$"

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
