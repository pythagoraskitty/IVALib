set(the_description "Active Contour Module used in order to implement different active contours")
iva_add_module(ActiveSurfaces ${CORE_LIBRARIES})
iva_module_include_directories(${CORE_INCLUDE_DIRECTORIES})
iva_glob_module_sources()
iva_create_module() 
