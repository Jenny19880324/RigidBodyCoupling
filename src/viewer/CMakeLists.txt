# -----------------------------------------------------------------------------
# VIEWER LIBRARY
# -----------------------------------------------------------------------------



INCLUDE_DIRECTORIES(
	"${PROJECT_SOURCE_DIR}/ext/glfw3/include"
	"${PROJECT_SOURCE_DIR}/src/viewer"
	"${PROJECT_SOURCE_DIR}/src/viewer/imgui"
	"${PROJECT_SOURCE_DIR}/src/viewer/gl3w"
	"${PROJECT_SOURCE_DIR}/src/viewer/imgui_impl_glfw_gl3"
)


SET (VIEWER_INCL
	viewer.h
	gl3w/gl3w.h
	gl3w/glcorearb.h
	imgui/imconfig.h
	imgui/imgui.h
	imgui/imgui_internal.h
	imgui/stb_rect_pack.h
	imgui/stb_textedit.h
	imgui/stb_truetype.h
	imgui_impl_glfw_gl3/imgui_impl_glfw_gl3.h
)

SET (VIEWER_IMPL
	viewer.cpp
	gl3w/gl3w.c
	imgui/imgui.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui_impl_glfw_gl3/imgui_impl_glfw_gl3.cpp)
	

IF (${BUILD_SHARED_LIBS})

	ADD_DEFINITIONS(-DDLL_EXPORT)
	ADD_LIBRARY (viewer SHARED
		${VIEWER_INCL}
		${VIEWER_IMPL})
		
ELSE (${BUILD_SHARED_LIBS})
	
	ADD_DEFINITIONS(-DSTATIC_LIB)
	ADD_LIBRARY (viewer STATIC
		${VIEWER_INCL}
		${VIEWER_IMPL})
		
ENDIF()	

	

TARGET_LINK_LIBRARIES(viewer
	opengl32
	"${PROJECT_SOURCE_DIR}/ext/glfw3/lib/glfw3.lib")
	

SET_TARGET_PROPERTIES(viewer
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
	
	
	