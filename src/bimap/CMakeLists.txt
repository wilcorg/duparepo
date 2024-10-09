project(src-bimap CXX)

add_library(src-bimap SHARED)

target_sources(${PROJECT_NAME}
        PUBLIC
        ${INCLUDE_DIR}/bimap/BiMap.hpp
        ${INCLUDE_DIR}/bimap/BiMapIterator.hpp

        PRIVATE
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)