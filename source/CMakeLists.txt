add_definitions (-Wall -std=c++11)

set (WT_PROJECT_SOURCE
    main.cpp
)

file (COPY "strings.xml" DESTINATION "${CMAKE_BINARY_DIR}/source/")
file (COPY "strings_ru.xml" DESTINATION "${CMAKE_BINARY_DIR}/source/")

set (WT_PROJECT_TARGET wt_app.wt)
add_executable (${WT_PROJECT_TARGET} ${WT_PROJECT_SOURCE})

find_package (Wt REQUIRED)

include_directories (${Wt_INCLUDE_DIR})

if (USE_WTFCGI)
    set (WT_CONNECTOR_LIB ${Wt_FCGI_LIBRARY})
else ()
    set (WT_CONNECTOR_LIB ${Wt_HTTP_LIBRARY})
endif ()

target_link_libraries (${WT_PROJECT_TARGET} 
    ${Wt_LIBRARY}
    ${WT_CONNECTOR_LIB}
)
