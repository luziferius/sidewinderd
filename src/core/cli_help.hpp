/**
 * Copyright (c) 2017 Thomas Hess <thomas.hess@udo.edu>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */

#ifndef CLI_HELP_CLASS_H
#define CLI_HELP_CLASS_H

#include <string>
#include <string.h>

/**
 * Defines the components of a command line switch help line.
 * Do not specify dashes for short options (-) or long options (--).
 * The formatter will add those while processing.
 * String options default to empty strings instead of undefined values,
 * so definitions of unneeded elements can be omitted.
 */
struct program_option {
	/** The short option character. Should be a single character string only. */
	const char* short_option = "";
	const char* long_option = "";
	/** The textual option description. Can be of any length. The formatter will do line wrapping. */
	const char* description = "";
	const char* argument = "";
	/**
	 * leading_newlines can be used to specify how many empty lines are printed before printing
	 * this element.
	 */
	uint leading_newlines = 0;
};

constexpr int HELP_OUTPUT_LINE_WIDTH = 80;
/**
 * Minimal distance between a command line switch and its description.
 */
constexpr int HELP_DESCRIPTION_TEXT_HORIZONTAL_DISTANCE = 4;

/** 
 * Define command line argument help here. Element order defines the print output order.
 * NOTE: Element initialisation must be in order of struct declaration and not miss
 * any middle element. Otherwise compilation fails with error message
 * "sorry, unimplemented: non-trivial designated initializers not supported"
 * (at least when using g++ 5.4.0).
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
 * @returns Multiline formatted string containing help text for all command line switches
 */
const std::string format_option_help();


#endif // CLI_HELP_CLASS_H
