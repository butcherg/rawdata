#!/bin/bash

#Extracts raw image to a tiff, adds the metadata to the tiff, and if a camera
#profile is specified, puts it in there, too.
#
#Usage ./raw4tiff.sh file.RAW file.tif [cameraprofile.icc]

./raw2tiff $1 $2
exiftool -TagsFromFile $1 $2
if [ "$3" != "" ]
then
	exiftool "-icc_profile<=$3" $2
fi