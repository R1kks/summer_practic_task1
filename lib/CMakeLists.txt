#CMakeLists.txt - файл сборки библиотеки
#
#Дозоров Владимир Евгеньевич
#Группа МК - 101

# Собираем все файлы из папки lib в библиотеку
get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}" LIB_FILES)

add_library(replacer_lib ${LIB_FILES})

# Указываем, где лежат заголовочные файлы
target_include_directories(replacer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)