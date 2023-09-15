#ifndef maximus_h
#define maximus_h
#endif

#pragma once

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004,              K005, K006, K007, K008, K009,  \
	K100, K101, K102, K103, K104,              K105, K106, K107, K108, K109,  \
	K200, K201, K202, K203, K204,              K205, K206, K207, K208, K209,  \
	      K301, K302, K303, K304,              K305, K306, K307, K308         \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005, K006,   K007,  K008,  K009, }, \
	{ K100,  K101,  K102,  K103,  K104,  K105, K106,   K107,  K108,  K109, }, \
	{ K200,  K201,  K202,  K203,  K204,  K205, K206,   K207,  K208,  K209, }, \
	{ KC_NO, K301,  K302,  K303,  K304,  K305, K306 ,  K307,  K308,  KC_NO}  \
}
