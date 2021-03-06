# Overview

This project is a full implementation of face detection model running on Arm micro NPU Ethos U55.

The CNN model is based on:

https://github.com/dog-qiuqiu/Yolo-Fastest

dog-qiuqiu. (2021, July 24). dog-qiuqiu/Yolo-Fastest: yolo-fastest-v1.1.0 (Version v.1.1.0). Zenodo. http://doi.org/10.5281/zenodo.5131532


We trained the model for face detection with private and public datasets including: Wider (http://shuoyang1213.me/WIDERFACE/) and our private datasets.

Input image 192x192x1 (grayscale).

Quantization method is standard TFLM, INT8.

The model is running on Arm virtual platform, execution time for single frame inference is (in U55 128 MACs configuration): 5.4 ms (vela compiler).

We provide a step by step guide from environment setup up to deploy the model as follows:


### Face_detection_example_arm_u55
Face detection demo deployed on Arm U55 AI accelerator.

### Installation guide, tested on Ubuntu 20.04:

### Install necessary packages

sudo apt-get update 

sudo apt-get install cmake 

sudo apt-get install curl 

sudo apt install xterm 

sudo apt-get install git 

export GIT_SSL_NO_VERIFY=1 

sudo apt-get install libpython2.7 

sudo apt install python3 

sudo apt install python3.8-venv 

sudo apt install python3-pip 

### Download and install ARM GCC cross-compiler

wget  https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi.tar.xz

sudo tar -vxf gcc-arm-10.3-2021.07-x86_64-arm-none-eabi.tar.xz -C /usr/share/


sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc 

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-g++ /usr/bin/arm-none-eabi-g++

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-size /usr/bin/arm-none-eabi-size

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-ar /usr/bin/arm-none-eabi-ar

sudo ln -s /usr/share/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/arm-none-eabi-objcopy /usr/bin/arm-none-eabi-objcopy


sudo ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.6 /usr/lib/x86_64-linux-gnu/libncurses.so.5

sudo ln -s /usr/lib/x86_64-linux-gnu/libncursesw.so.6 /usr/lib/x86_64-linux-gnu/libncursesw.so.5

sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5



### Download and install FVP simulation platform


wget https://developer.arm.com/-/media/Arm%20Developer%20Community/Downloads/OSS/FVP/Corstone-300/FVP_Corstone_SSE-300_11.15_24.tgz


tar -vxf FVP_Corstone_SSE-300_11.15_24.tgz 

./FVP_Corstone_SSE-300.sh 


### Download and install ARM ml-embedded-evaluation-kit


export GIT_SSL_NO_VERIFY=1

git clone https://git.mlplatform.org/ml/ethos-u/ml-embedded-evaluation-kit.git



cd ml-embedded-evaluation-kit/

rm -rf ./dependencies

python3 ./download_dependencies.py


### Validate default build

./build_default.py


### Clone Emza face detection demo

cd ~

git clone git@github.com:emza-vs/face_detection_example_arm_u55.git

#Apply face_detection_example patch on ARM repo

cp face_detection_example_arm_u55/*.patch ml-embedded-evaluation-kit

cd ml-embedded-evaluation-kit

git am *.patch

./build_default.py


### Run object detection example

~/FVP_Corstone_SSE-300/models/Linux64_GCC-6.4/FVP_Corstone_SSE-300_Ethos-U55 -C ethosu.num_macs=128 -a ~/ml-embedded-evaluation-kit/cmake-build-mps3-sse-300-ethos-u55-128-gnu/bin/ethos-u-object_detection.axf


### Run object detection unit test

cd cmake-build-mps3-sse-300-ethos-u55-128-gnu/

rm -rf ./*

cmake ../ -DTARGET_PLATFORM=native

make

cd bin/

./arm_ml_embedded_evaluation_kit-object_detection-tests 

