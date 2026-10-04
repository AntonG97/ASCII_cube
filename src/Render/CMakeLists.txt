add_library(Render
	src/CLIpc.cpp
	src/FrameBuffer.cpp
	src/Iterator.cpp
	src/Renderer.cpp
	src/RowView.cpp
)

target_include_directories(Render
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Render
	PUBLIC
	Shape
	Transformation
)
