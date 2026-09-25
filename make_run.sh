#!/bin/bash

FILENAME='RasterDraw-3ds'
FILETYPE='3dsx'
DS_IP='' # 192.168.XXX.XXX (without port) (needed if on original hardware)
CITRA_PATH='/home/caio/Apps/citra/citra-qt.AppImage' # (needed if on citra)
CITRA_LOG_PATH='/home/caio/.local/share/citra-emu/log/citra_log.txt'

# -c: clear shell when running the script
# -r: run app after making it
# -n: run the app in native 3ds
# -h: shows help message

while getopts "crnh" opt; do
  case $opt in
    c) clear_arg=true
    ;;
    r) run_arg=true
    ;;
    n) native_arg=true
    ;;
    h) help_arg=true
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    exit 1
    ;;
  esac
done

if [[ "$1" == "help" || "$help_arg" == true ]]; then
    printf "\nMakeRun Script: \n"
    printf " -c bool (false): clear shell when running the script \n"
    printf " -r bool (true ): run app after making it \n"
    printf " -n bool (false): run the app in native 3ds insted of citra \n"
    printf " help: shows this help message \n"
    printf " \n------------------------------------------------------------- \n\n"
    printf " Remember to config this script with the filename, type, \n"
    printf " your 3ds ip and/or the citra path in your system in \n"
    printf " the variables at the top. \n    \n"
    exit
fi


if [ "$clear_arg" == "true" ]; then
    clear
fi

make clean
make

if [ "$run_arg" != "false" ]; then
    if [ ! -f "./$FILENAME.$FILETYPE" ]; then
        printf "MakeRun> File not found! (compilation error?) Will not attempt to run program. \n"
        exit
    fi

    if [ "$native_arg" == "true" ]; then
        printf "MakeRun> Will attempt to run on 3dslink... \n"
        /opt/devkitpro/tools/bin/3dslink $FILENAME.$FILETYPE -a $DS_IP
    else
        printf "MakeRun> Will attempt to run on citra... \n"
        # tail -F "$CITRA_LOG_PATH" &&
        "$CITRA_PATH" "./$FILENAME.$FILETYPE"
    fi
fi