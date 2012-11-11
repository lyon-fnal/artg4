#!/bin/bash 

# Make a detector service from templates

# Arguments: $1 = namespace
#            $2 = Class name (case is important)

namespace=$1
classname=$2

upperClassName=$( echo $classname | tr '[:lower:]' '[:upper:]' )

fileName="${classname}_service"
headerName="${fileName}.hh"

# Make the cc file
sed -e "s/%%classNameAllCaps%%/$upperClassName/g"\
    -e "s/%%className%%/$classname/g"\
    -e "s/%%namespace%%/$namespace/g"\
    -e "s/%%headerName%%/$fileName/g"\
    Detector_service.cc_template > ${fileName}.cc
echo "Created ${fileName}.cc"

# Make the hh file
sed -e "s/%%classNameAllCaps%%/$upperClassName/g"\
    -e "s/%%className%%/$classname/g"\
    -e "s/%%namespace%%/$namespace/g"\
    Detector_service.hh_template > ${fileName}.hh
echo "Created ${fileName}.hh"

echo "Edit each file and look for CHANGE_ME"
