
set(NAME classic_solver)

add_library(${NAME} STATIC)

target_link_libraries(${NAME} 
PUBLIC
sudoku
)

target_include_directories(${NAME}
PUBLIC
    include/
)

target_sources(${NAME}
PRIVATE
    include/classic_solver/ClassicSolver.hpp
    
    src/ClassicSolver.cpp
)