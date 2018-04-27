HTTP Server
-----------

[![Build Status][travis-badge]][travis-link]
[![codecov][codecov-badge]][codecov-link]
[![release][release-badge]][release-link]
[![MIT License][license-badge]][license-link]

[travis-badge]:     https://travis-ci.org/pashinov/server.svg?branch=master
[travis-link]:      https://travis-ci.org/pashinov/server
[codecov-badge]:    https://codecov.io/gh/pashinov/server/branch/master/graph/badge.svg
[codecov-link]:     https://codecov.io/gh/pashinov/server
[release-badge]:    https://img.shields.io/badge/release-v1.0.0-blue.svg
[release-link]:     https://github.com/pashinov/server/releases
[license-badge]:    https://img.shields.io/badge/License-MIT-yellow.svg
[license-link]:     https://github.com/pashinov/server/blob/master/LICENSE

http-server is a simple asynchronous http server running as linux daemon.

To build and install the application:
$ mkdir build && cd build
$ cmake [-DCMAKE_BUILD_TYPE=Release|Debug] ..
$ make
$ sudo make install

To run the application:
$ /etc/init.d/http-server start

To stop the application:
$ /etc/init.d/http-server stop

To check status the application:
$ /etc/init.d/http-server status