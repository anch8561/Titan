include(CMakeFindDependencyMacro)
find_dependency(glfw3)
find_dependency(GLEW)
find_dependency(glm)
find_dependency(CUDA)
find_dependency(OpenGL)

#if (LINUX)
#    find_program(NVCC
#            NAMES nvcc nvcc.exe
#            PATHS
#            /usr/local/cuda/bin
#            ENV CUDA_PATH
#            ENV CUDA_BIN_PATH
#            PATH_SUFFIXES bin bin64
#            DOC "Toolkit location."
#            NO_DEFAULT_PATH
#            )
#
#    if (NVCC)
#        message(STATUS "Found CUDA compiler at " ${NVCC})
#    else()
#        message(FATAL_ERROR "CUDA compiler not found")
#    endif()
#
#    set(CMAKE_CUDA_COMPILER:FILEPATH ${NVCC})
#endif()

#if (NOT CMAKE_CUDA_DEVICE_LINK_EXECUTABLE)
#    set(CMAKE_CUDA_DEVICE_LINK_EXECUTABLE "<CMAKE_CUDA_COMPILER>  <FLAGS> -Xcompiler=-fPIC -Wno-deprecated-gpu-targets -shared -dlink <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
#endif()

include("${CMAKE_CURRENT_LIST_DIR}/TitanTargets.cmake")
