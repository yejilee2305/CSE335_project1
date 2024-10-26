project(project1Lib)

set(SOURCE_FILES
        Gate.cpp
        Gate.h
        Item.cpp
        Item.h
        MainFrame.cpp
        MainFrame.h
        pch.h
        Sensor.cpp
        Sensor.h
        Scoreboard.cpp
        Scoreboard.h
        Conveyor.cpp
        Conveyor.h
        Sparty.cpp
        Sparty.h
        Product.cpp
        Product.h
		Game.cpp
		Game.h
		GameView.cpp
		GameView.h
		ids.h
		Beam.cpp
		Beam.h
		Game.h
		XMLParser.cpp
		XMLParser.h
		Team.cpp
		Team.h
		Pins.cpp
		Pins.h
		PinInput.cpp
		PinInput.h
		PinOutput.cpp
		PinOutput.h
		Wire.cpp
		Wire.h
		#		Pins.cpp
#		Pins.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
