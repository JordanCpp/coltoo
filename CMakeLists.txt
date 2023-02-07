cmake_minimum_required(VERSION 3.8)

if (MSVC)
  link_directories("dependencies/SDL2-2.24.0/lib/x86/"
                   "dependencies/SDL2_image-2.6.2/lib/x86"
                   "dependencies/SDL2_ttf-2.20.1/lib/x86")

  include_directories("dependencies/SDL2-2.24.0/include"
                      "dependencies/SDL2_image-2.6.2/include"
                      "dependencies/SDL2_ttf-2.20.1/include")
endif()

add_executable(colto
"src/main.cpp"
"src/actor.cpp"
"src/ai.cpp"
"src/bckgrnd.cpp"
"src/blit.cpp"
"src/CDS1.cpp"
"src/CDSmouse.cpp"
"src/colony.cpp"
"src/ColorData.cpp"
"src/CTileResource.cpp"
"src/CTileType.cpp"
"src/CTileTypes.cpp"
"src/deuro1.cpp"
"src/deuro2.cpp"
"src/deuro3.cpp"
"src/deuro4.cpp"
"src/display.cpp"
"src/Drawcds1.cpp"
"src/Drawcds2.cpp"
"src/eventHandler.cpp"
"src/falseterr.cpp"
"src/font.cpp"
"src/font2.cpp"
"src/gameEngine.cpp"
"src/globalData.cpp"
"src/graphicsEngine.cpp"
"src/hcs1.cpp"
"src/HCSmouse.cpp"

"src/kboard.cpp"
"src/makemask.cpp"
"src/map.cpp"
"src/message.cpp"
"src/misc1.cpp"
"src/mouse.cpp"
"src/move.cpp"
"src/OptionList.cpp"
"src/orders1.cpp"
"src/pixel.cpp"
"src/player.cpp"
"src/recenter.cpp"
"src/skill.cpp"
"src/terrain1.cpp"
"src/tile.cpp"
"src/tinystr.cpp"
"src/tinyxml.cpp"
"src/tinyxmlerror.cpp"
"src/tinyxmlparser.cpp"
"src/truetype.cpp"
"src/unit.cpp"
"src/zoom.cpp")

target_link_libraries(colto SDL2main SDL2 SDL2_image SDL2_ttf)