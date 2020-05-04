# SETTING
DESTDIR=build1

# Uncomment for Custom setting
# VTK BUILD Dir or Installation directory in system
MYVTKPATH=/home/ducvd/setup/libraries/graph/VTK-8.2.0/Build

# Uncomment for Custom setting
# MYOPENCVDIR=



#===========================================================================
# mkdir ${DESTDIR}
# cd ${DESTDIR}


build_cmd() {
    if [ -z "${MYVTKPATH}"]
    then
        # Empty VTK
        if [ -z "${MYOPENCVDIR}"]
        then
            echo "cmake .."
            cmake ..
        else
            echo "OpenCV_DIR=${MYOPENCVDIR} cmake .."
            OpenCV_DIR=${MYOPENCVDIR} cmake ..
        fi
    else
        # ----------
        if [ -z "${MYOPENCVDIR}"]
        then
            echo "cmake -DVTK_DIR:PATH=${MYVTKPATH} .."
            cmake -DVTK_DIR:PATH=${MYVTKPATH} ..
        else
            echo "OpenCV_DIR=${MYOPENCVDIR} cmake -DVTK_DIR:PATH=${MYVTKPATH} .."
            OpenCV_DIR=${MYOPENCVDIR} cmake -DVTK_DIR:PATH=${MYVTKPATH} ..
        fi
    fi
}
    

build_cmd