cmake_minimum_required(VERSION 3.12)
project(http-server-async)

# Добавьте имена файлов исходного кода
set(SOURCES 
    src/main.cpp 
    src/config.cpp 
    src/request.cpp 
    src/call_center.cpp 
    src/listener.cpp 
    src/queue_request.cpp 
    src/session.cpp 
)

# Добавьте имена файлов заголовков
set(HEADERS
    include/config.hpp
    include/request.hpp
    include/call_center.hpp
    include/listener.hpp
    include/queue_request.hpp
    include/session.hpp
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
