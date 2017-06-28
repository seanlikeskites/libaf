cmake_minimum_required (VERSION 2.6)
project (libaf)

# set the version number
set (libaf_VERSION_MAJOR 0)
set (libaf_VERSION_MINOR 1)
set (libaf_VERSION_PATCH 0)

# Selection of data type
if (DATA_TYPE STREQUAL float)
	message (STATUS "Configuring libaf for type float.")
	add_definitions (-DATFFT_TYPE_FLOAT -DLIBAF_TYPE_FLOAT)
	set (LIB_NAME aff)
elseif (DATA_TYPE STREQUAL longdouble)
	message (STATUS "Configuring libaf for type long double.")
	add_definitions (-DATFFT_TYPE_LONG_DOUBLE -DLIBAF_TYPE_LONG_DOUBLE)
	set (LIB_NAME afl)
else()
	message (STATUS "Configuring libaf for type double.")
	set (DATA_TYPE double)
	add_definitions (-DATFFT_TYPE_DOUBLE -DLIBAF_TYPE_DOUBLE)
	set (LIB_NAME af)
endif()

# find all the headers
include_directories ("${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/atfft/include")

# find all the libaf sources
file (GLOB LIBAF_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# find the relevant atfft sources
set (ATFFT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/atfft/src")
set (ATFFT_SOURCES "${ATFFT_SOURCE_DIR}/atfft_shared.c")

if (FFT_IMPL STREQUAL fftw3)
	message (STATUS "Configuring libaf using fftw3.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct_fftw.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_fftw.c")
elseif (FFT_IMPL STREQUAL ffts)
	message (STATUS "Configuring libaf using ffts.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_ffts.c")
elseif (FFT_IMPL STREQUAL gsl)
	message (STATUS "Configuring libaf using gsl.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_gsl.c")
elseif (FFT_IMPL STREQUAL kiss)
	message (STATUS "Configuring libaf using kiss fft.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_kiss.c")
elseif (FFT_IMPL STREQUAL ffmpeg)
	message (STATUS "Configuring libaf using ffmpeg.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct_ffmpeg.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_ffmpeg.c")
elseif (FFT_IMPL STREQUAL pffft)
	message (STATUS "Configuring libaf using pffft.")
	set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct.c"
		"${ATFFT_SOURCE_DIR}/dft/atfft_dft_pffft.c" "${ATFFT_SOURCE_DIR}/pffft/pffft.c")
elseif (FFT_IMPL STREQUAL vdsp)
	message (STATUS "Configuring libaf using vdsp.")
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct_vdsp.c"
		"${ATFFT_SOURCE_DIR}/dft/atfft_dft_vdsp.c")
else()
	message (STATUS "Configuring libaf using ooura fft.")
	set (FFT_IMPL ooura)
	set (ATFFT_SOURCES ${ATFFT_SOURCES} "${ATFFT_SOURCE_DIR}/dct/atfft_dct_ooura.c"
	     "${ATFFT_SOURCE_DIR}/dft/atfft_dft_ooura.c" "${ATFFT_SOURCE_DIR}/ooura/fft4g.c")
endif()

add_library (${LIB_NAME} SHARED ${LIBAF_SOURCES} ${ATFFT_SOURCES})

# link the relevant fft library
if (FFT_IMPL STREQUAL fftw3)
	if (DATA_TYPE STREQUAL float)
		target_link_libraries (${LIB_NAME} fftw3f)
	elseif (DATA_TYPE STREQUAL longdouble)
		target_link_libraries (${LIB_NAME} fftw3l)
	else()
		target_link_libraries (${LIB_NAME} fftw3)
	endif()
elseif (FFT_IMPL STREQUAL ffts)
	target_link_libraries (${LIB_NAME} ffts)
elseif (FFT_IMPL STREQUAL gsl)
	target_link_libraries (${LIB_NAME} gsl gslcblas)
elseif (FFT_IMPL STREQUAL kiss)
	if (DATA_TYPE STREQUAL float)
		target_link_libraries (${LIB_NAME} kissfftf)
	elseif (DATA_TYPE STREQUAL longdouble)
		target_link_libraries (${LIB_NAME} kissfftl)
	else()
		target_link_libraries (${LIB_NAME} kissfft)
	endif()
elseif (FFT_IMPL STREQUAL ffmpeg)
	target_link_libraries (${LIB_NAME} avutil avcodec)
elseif (FFT_IMPL STREQUAL vdsp)
	target_link_libraries (${LIB_NAME} "-framework Accelerate")
endif()
