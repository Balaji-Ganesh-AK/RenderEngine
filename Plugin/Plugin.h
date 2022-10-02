#pragma once
#include <stdio.h>
int plugin_func(void) {
	printf("Hello from the plugin!\n");
	return 42;
}