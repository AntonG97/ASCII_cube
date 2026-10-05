add_library(Rasterizer
	src/CLIpc.cpp
	src/FrameBuffer.cpp
	src/Iterator.cpp
	src/Rasterizer.cpp
	src/RowView.cpp
)

target_include_directories(Rasterizer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Rasterizer
	PUBLIC
	Shape
	Transformation
)
