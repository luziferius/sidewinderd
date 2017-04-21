/**
 * Copyright (c) 2014 - 2016 Tolga Cakir <tolga@cevel.net>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */

#ifndef HELP_CLASS_H
#define HELP_CLASS_H

#include <string>
#include <string.h>

struct program_option {
	// Default to empty strings instead of undefined values, so definitions of unneeded elements
	// can be omitted.
	const char* short_option = "";
	const char* long_option = "";
	const char* description = "";
	const char* argument = "";
	/**
	 * leading_newlines can be used to specify how many empty lines are printed before printing
	 * this element.
	 */
	uint leading_newlines = 0;
};

constexpr int HELP_OUTPUT_LINE_WIDTH = 80;
constexpr int HELP_DESCRIPTION_TEXT_HORIZONTAL_DISTANCE = 4;

/** 
 * Define command line argument help here. Element order defines the print output order.
 * NOTE: Initialisation must be in order of struct declaration and not miss
 * any middle element. Otherwise compilation fails with
 * "sorry, unimplemented: non-trivial designated initializers not supported"
 * (at least when using g++ 5.4.0)
 * This compiler restriction reduces the usefulness of this construct a bit, but
 * may be lifted in the future.
 */
constexpr struct program_option available_options[] = {
	{
		.short_option = "c",
		.long_option =  "config",
		.description =  "use the given configuration file instead of the default",
		.argument =     "FILE",
	},
	{
		.short_option = "d",
		.long_option =  "daemon",
		.description =  "run the program in the background",
	},
	{
		.short_option = "p",
	},
	{
		.short_option = "h",
		.long_option =  "help",
		.description =  "display this help and exit",
		.argument =     "",
		.leading_newlines = 2,
	},
	{
		.short_option = "v",
		.long_option =  "version",
		.description =  "output version information and exit",
	},
};


/**
 * Format the help text for command line switches
 */
const std::string format_option_help();


#endif // HELP_CLASS_H
