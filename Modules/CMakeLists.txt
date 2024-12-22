add_subdirectory(FRGUI)
add_subdirectory(FRLog)
add_subdirectory(FRWarp)
add_subdirectory(FRCore)
add_subdirectory(FRTools)
add_subdirectory(FREditor)

set_target_properties(FRGUI FRLog FRWarp FRCore FRTools FREditor PROPERTIES FOLDER "Modules")