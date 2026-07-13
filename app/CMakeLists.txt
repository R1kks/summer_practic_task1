#CMakeLists.txt - файл сборки приложения
#
#Дозоров Владимир Евгеньевич
#Группа МК - 101

# Собираем все файлы из папки app в исполняемый файл
get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}" APP_FILES)

add_executable(replacer_app ${APP_FILES})

# Подключаем нашу библиотеку к программе
target_link_libraries(replacer_app PRIVATE replacer_lib)