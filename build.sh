# @Author: adebray
# @Date:   2016-07-18 19:05:15
# @Last Modified by:   adebray
# @Last Modified time: 2016-07-18 19:56:01

/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -cl-auto-vectorize-enable -emit-gcl mykernel.cl

/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple i386-applecl-darwin -emit-llvm-bc -o mykernel.cl.i386.bc mykernel.cl
/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple x86_64-applecl-darwin -emit-llvm-bc -o mykernel.cl.x86_64.bc mykernel.cl
/System/Library/Frameworks/OpenCL.framework/Libraries/openclc -x cl -cl-std=CL1.1 -Os -triple gpu_32-applecl-darwin -emit-llvm-bc -o mykernel.cl.gpu_32.bc mykernel.cl

clang -c -Os -Wall -arch x86_64 -o mykernel.cl.o mykernel.cl.c
clang -c -Os -Wall -arch x86_64 -o main.o main.c
clang -framework OpenCL -o square mykernel.cl.o main.o
