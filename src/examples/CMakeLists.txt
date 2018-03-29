# -----------------------------------------------------------------------------
# EXAMPLES
# -----------------------------------------------------------------------------

IF (${BUILD_EXAMPLES})

	IF (${BUILD_SHARED_LIBS})
		REMOVE_DEFINITIONS(-DDLL_EXPORT)
		ADD_DEFINITIONS(-DDLL_IMPORT)
	ELSE (${BUILD_SHARED_LIBS})
		ADD_DEFINITIONS(-DSTATIC_LIB)
	ENDIF ()
	
	INCLUDE_DIRECTORIES(
		"${PROJECT_SOURCE_DIR}/ext/glfw3/include"
		"${PROJECT_SOURCE_DIR}/src/viewer"
		"${PROJECT_SOURCE_DIR}/src/viewer/gl3w"
		"${PROJECT_SOURCE_DIR}/src/viewer/imgui"
		"${PROJECT_SOURCE_DIR}/src/viewer/imgui_impl_glfw_gl3"
	)
	
# -----------------------------------------------------------------------------
# rigid_body_coupling example
# -----------------------------------------------------------------------------

	ADD_EXECUTABLE(rigid_body_coupling
		rigid_body_coupling.cpp
		always_do_post_build.cpp)
		
	TARGET_LINK_LIBRARIES(rigid_body_coupling
		viewer)
		
# -----------------------------------------------------------------------------
# after building is complete and as a consequence, 
# if the project target does not need to be
# re-built (as it has no changes), the post-build step will not be run. 
# However, in some projects you may want to always run the post-build step; 
# for example if you need to copy 
# module libraries(i.e. which do not depend on the main project target 
# but have been modified) to the main target's output directory so
# the application can run. 
# Luckily there is a simple workaround to achieve this:

#1. Add an empty header file (.h) to your project with the following name:
# always_do_post_build.cpp
#2. Ensure that this file is monitored by Cmake by including it in 
# add_executable()
#3. Also add the following to your CMakeLists.txt file

#How does it work?
#An extra dummy target (ALWAYS_DO_POST_BUILD) is created which depends on the 
# main project target (CMAKE_PROJECT_NAME). Due to this dependency, 
# the dummy target will run before the main project target and 
# ensures that the always_do_post_build.cpp file
# (which is monitored by the main project target) is always "out of date" 
# via the touch command. This will trigger the main project target to perform 
# a re-build and thus run the post-build step as required. 
# NOTE: A header file (.h) is not going to trigger a rebuild after I updated VS
# -----------------------------------------------------------------------------
	IF (${BUILD_SHARED_LIBS})
		ADD_CUSTOM_TARGET(ALWAYS_DO_POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo touching always_do_post_build.cpp
			COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/always_do_post_build.cpp
			)
			
		SET (VIEWER_COPY_DLL "")
		LIST (APPEND VIEWER_COPY_DLL
			"${PROJECT_BINARY_DiR}/bin/$<CONFIGURATION>/viewer.dll")
			
		
		SET (EXAMPLES "")
		LIST (APPEND EXAMPLES
			rigid_body_coupling
			)
			
		FOREACH(ex ${EXAMPLES})
			MESSAGE(STATUS "Process example: ${ex}")
			
			SET_PROPERTY(TARGET ${ex}
						PROPERTY FOLDER examples)
						
			ADD_DEPENDENCIES(${ex} ALWAYS_DO_POST_BUILD)
			
			ADD_CUSTOM_COMMAND(TARGET ${ex} POST_BUILD
								COMMAND ${CMAKE_COMMAND} -E copy_if_different
								${VIEWER_COPY_DLL}
								$<TARGET_FILE_DIR:${ex}>
								COMMENT "copy dlls to the exe folder" VERBATIM)
		ENDFOREACH(ex)
	ENDIF()
ENDIF()