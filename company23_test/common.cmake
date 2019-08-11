if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "i[3-6]86")
    set(
        ARCHITECTURE
        x86_32
    )
else()
    set(
        ARCHITECTURE
        x86_64
    )
endif()

#TBD: add auto split debug info command?

set_target_properties (${PROJECT} PROPERTIES
      LINK_FLAGS -Wl,-rpath,.
)

if(DEFINED Mac32)
  set(PLATFORM "Mac32")
elseif(DEFINED iOS)
  set(PLATFORM "iOS")
else()
  set(PLATFORM "")
endif()
