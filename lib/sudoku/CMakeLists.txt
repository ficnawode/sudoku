
set(NAME sudoku)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/sudoku/Board.hpp
    include/sudoku/types.hpp
    
    src/Board.cpp
)