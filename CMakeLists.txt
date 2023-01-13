if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(game VERSION 0.0.1 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

# libs
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/submodules/json/single_include/nlohmann)
include_directories(${PROJECT_SOURCE_DIR}/submodules/thread_pool)

# engine code
set(engine_dir src/engine)
set(SRC ${engine_dir}/map.hpp ${engine_dir}/window.hpp)
set(SRC ${SRC} ${engine_dir}/core.hpp ${engine_dir}/camera.hpp)
set(SRC ${SRC} ${engine_dir}/logger.hpp ${engine_dir}/assets_manager.hpp)
set(SRC ${SRC} ${engine_dir}/gui.hpp ${engine_dir}/widget.hpp ${engine_dir}/state.hpp)

# old_game code
set(game_dir src/game)
set(SRC ${SRC} ${game_dir}/menu.hpp ${game_dir}/game.hpp)


#for correct start
file(COPY gamedata/assets DESTINATION gamedata)

# create an exec file
add_executable(game src/main.cpp ${SRC})

# libs (maybe I can drag it up)
target_link_libraries(game sfml-graphics sfml-audio)

add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:game> $<TARGET_FILE_DIR:game>
        COMMAND_EXPAND_LISTS
        )