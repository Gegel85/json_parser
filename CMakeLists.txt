cmake_minimum_required(VERSION 3.13)
project(json_parser C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(json_parser
	include/concatf.h
	include/flags.h
	include/JsonParser.h
	sources/arrays.c
	sources/bools.c
	sources/data.c
	sources/debug.c
	sources/dicts.c
	sources/dumper.c
	sources/floats.c
	sources/ints.c
	sources/lists.c
	sources/parser.c
	sources/strings.c
	sources/concat.c
	sources/concatf.c
	sources/float_to_str.c
	sources/get_nbrlen.c
	sources/int_to_str.c
	sources/uint_to_str.c
	sources/sub_strings.c
	sources/str.c
	sources/my_showstr.c
	sources/my_putnbr_base.c
	sources/my_putstar.c
	sources/my_putbase.c
	sources/power.c)
