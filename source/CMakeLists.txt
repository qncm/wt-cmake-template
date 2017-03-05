add_definitions(-Wall -std=c++11)

set(WT_PROJECT_SOURCE
    main.cpp
)

set(WT_PROJECT_TARGET wt_app.wt)

add_executable(${WT_PROJECT_TARGET} ${WT_PROJECT_SOURCE})

target_link_libraries(${WT_PROJECT_TARGET} ${WT_CONNECTOR} wt)

include_directories(/usr/include/Wt)
