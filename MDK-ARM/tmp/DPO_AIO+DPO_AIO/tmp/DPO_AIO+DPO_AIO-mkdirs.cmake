# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO")
  file(MAKE_DIRECTORY "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO")
endif()
file(MAKE_DIRECTORY
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/1"
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO"
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/tmp"
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/src/DPO_AIO+DPO_AIO-stamp"
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/src"
  "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/src/DPO_AIO+DPO_AIO-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/src/DPO_AIO+DPO_AIO-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/87407/Keil_prj/DPO_AIO/MDK-ARM/tmp/DPO_AIO+DPO_AIO/src/DPO_AIO+DPO_AIO-stamp${cfgdir}") # cfgdir has leading slash
endif()
