# Сборочный файл для программы

# Минимальная версия CMake
cmake_minimum_required( VERSION 3.7.2 )

# Указываем компилятору на стандарт
set_target_properties(${TARGET} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
		)

# Устанавливаем флаги компилятора
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX" )

# Устанавливаем значение переменной PROJECT
set ( PROJECT server )

# Имя проекта
project ( ${PROJECT} )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

# Указываем пути, где искать заголовочники, дополнительно к стандартным путям
include_directories ( "inc"
					"inc/common"
					"inc/logger" )

# Собираем исходные файлы программы
aux_source_directory( src SOURCES )
aux_source_directory( src/common SOURCES )
aux_source_directory( src/logger SOURCES )

# Собираем исполняемый файл с именем ${PROJECT}
add_executable( ${PROJECT} ${SOURCES} )

# Линковка исполняемого файла
target_link_libraries( ${PROJECT} )
