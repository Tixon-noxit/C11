# Официальный образ Ubuntu
FROM ubuntu:latest

# Установка необходимых пакетов
RUN apt-get update && \
    apt-get install -y\
    clang-format\ 
    valgrind\
    cppcheck\
    make \
    git \
    gcc \
    sudo \
    vim

# Установка рабочего каталога
WORKDIR /app

# Копирую исходный код в контейнер
COPY . /app

# Права на файлы (если это необходимо)
# RUN chmod +x script.sh

# Терминал в контейнере (можно использовать bash)
CMD ["/bin/bash"]



