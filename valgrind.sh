#!/bin/sh
exec valgrind $@ ./build/Demo/Demo 2> valgrind.log
