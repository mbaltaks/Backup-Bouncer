#!/bin/sh

xar=/usr/bin/xar

can-copy () {
    test -e $xar
}

version () {
    $xar --version
    echo
    echo "command =
    cd src
    sudo $xar -c -f tmpfile . \
        && cd dst \
        && sudo $xar -x -P -f tmpfile"
}

backup () {
    cd $1
    # xar doesn't work with pipes yet, so we use a tmpfile
    tmpfile=`mktemp -t bbouncer-xar` || exit 1
    sudo $xar -c -f $tmpfile . \
        && cd $2 \
        && sudo $xar -x -P -f $tmpfile
    code=$?
    rm -f $tmpfile
    return $code
}
