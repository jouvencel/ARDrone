SET(EXEC_NAME test_gps)

SET(${EXEC_NAME}_SRC
   test_dronegps.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})
# ----------------------------------------------------------

SET(EXEC_NAME move_drone2)
SET(${EXEC_NAME}_SRC
   move_drone2.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})





# ----------------------------------------------------------

SET(EXEC_NAME move2_drone)
SET(${EXEC_NAME}_SRC
   move2_drone.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})



# ----------------------------------------------------------
SET(EXEC_NAME move_drone)

SET(${EXEC_NAME}_SRC
   move_drone.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})



# ----------------------------------------------------------
SET(EXEC_NAME test_drone)

SET(${EXEC_NAME}_SRC
    test_drone.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})



# ----------------------------------------------------------
SET(EXEC_NAME calib_com)

SET(${EXEC_NAME}_SRC
    calib_drone.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})



# ----------------------------------------------------------



SET(EXEC_NAME reinit_drone)

SET(${EXEC_NAME}_SRC
    reinit_drone.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})


# ----------------------------------------------------------



SET(EXEC_NAME test_video_RGB24)

SET(${EXEC_NAME}_SRC
	test_video_RGB24.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})


# ----------------------------------------------------------



SET(EXEC_NAME test_video_YUV420)

SET(${EXEC_NAME}_SRC
    test_video_YUV420.c
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
LINK_DIRECTORIES(${${PROJECT_NAME}_BINARY_DIR})

ADD_EXECUTABLE(${EXEC_NAME}
    ${${EXEC_NAME}_SRC}
)

TARGET_LINK_LIBRARIES(${EXEC_NAME} ${PROJECT_NAME})




