IF(Audi_INCLUDE_DIR)
	# Already in cache, be silent
	SET(Audi_FIND_QUIETLY TRUE)
ENDIF(Audi_INCLUDE_DIR)

FIND_PATH(Audi_INCLUDE_DIR NAMES audi/audi.hpp)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Audi DEFAULT_MSG Audi_INCLUDE_DIR)

MARK_AS_ADVANCED(Audi_INCLUDE_DIR)
