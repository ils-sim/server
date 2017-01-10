FROM ubuntu:16.10
RUN apt-get -y update && apt-get install -y \
	cmake                                   \
	cppcheck                                \
	libboost-all-dev                        \
	libmysqlcppconn-dev                     \
	g++                                     \
	wget                                    \
	unzip                                   \
	sqlite3                                 \
	libsqlite3-dev                          \
	qt5-default                             \
	qttools5-dev-tools                      \
	&& rm -rf /var/lib/apt/lists/*
RUN wget https://github.com/google/protobuf/releases/download/v3.0.0-beta-3/protobuf-cpp-3.0.0-beta-3.zip && \
	unzip protobuf-cpp-3.0.0-beta-3.zip && \
	cd protobuf-3.0.0-beta-3/ &&           \
	./configure &&                         \
	make &&                                \
	make install

