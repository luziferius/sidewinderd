/**
 * Copyright (c) 2017 Thomas Hess <thomas.hess@udo.edu>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */
#include "cli_help.hpp"

#include <string.h>


constexpr int HELP_OUTPUT_LINE_WIDTH = 80;
/**
 * Minimal distance between a command line switch and its description.
 */
constexpr int HELP_DESCRIPTION_TEXT_HORIZONTAL_DISTANCE = 4;

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

/*
 * Formatter code below.
 */


/**
 * Calculate the indention width for descriptions.
 * This is the amount of characters in a line before the description starts:
 *   -l --long_option ARG   description of long_option
 * _________________________ ← indention width
 * 
 * This function is used to align all description texts, even when line wrapping is required.
 * Starting with C++14, this can be declared as constexpr.
 */
constexpr int indention_width() {
	int max_length = -1;
	for (auto option : available_options) {
		int current_length = 6 // length of formatted short option: "  -x, "
			+ (*option.long_option ?  strlen(option.long_option) + 3 : 0)
			+ (*option.argument ? strlen(option.argument) + 1: 0)
			+ HELP_DESCRIPTION_TEXT_HORIZONTAL_DISTANCE;
		if (current_length > max_length)
			max_length = current_length;
	}
	return max_length;
}

inline std::string format_short_option(std::string line, struct program_option* option) {
	if (*option->short_option) {
		line.append("-")
			.append(option->short_option);
		if (*option->long_option)
			line.append(", ");
		else
			line.append("  ");
	} else
		line.append("    ");
	return line;
}

inline std::string format_long_option(std::string line, struct program_option* option) {
	if(*option->long_option)
			line.append("--").append(option->long_option);
	return line;
}

inline std::string format_description(std::string line, struct program_option* option) {
	// TODO: Wrap the description text to fit into HELP_OUTPUT_LINE_WIDTH characters.
	// -> Implementing proper word wrap.
	line.append(indention_width() - line.length() + option->leading_newlines, ' ')
		.append(option->description)
		.append("\n");
	return line;

}

/**
 * Format the help text for command line switches
 * @returns Multiline formatted string containing help text for all command line switches
 */
const std::string format_option_help() {
	std::string result = std::string();
	for(auto option : available_options) {
		std::string line = std::string(option.leading_newlines, '\n');
		// building the line
		line.append("  ");
		line = format_short_option(line, &option);
		line = format_long_option(line, &option);
		if(*option.argument)
			line.append(" ").append(option.argument);
		line = format_description(line, &option);
		result.append(line);
	}
	return result;
}

const std::string get_formatted_help_text(const std::string program_name) {
	std::string result = std::string()
		.append("usage:\t").append(program_name).append(" [OPTION]..." "\n")
		.append("Enables usage of advanced features of Microsoft Sidewinder X4/X6 keyboards and some" "\n")
		.append("supported Logitech keyboards (like G105, G710 and G710+)." "\n")
		.append("This includes macro recording and playback, profile switching and more." "\n")
		.append("It is meant to be run as a background service or daemon." "\n")
		.append("\n")
		.append("Mandatory arguments to long options are mandatory for short options too." "\n")
		.append(format_option_help())
		.append("Report bugs here: https://github.com/tolga9009/sidewinderd/issues");
	return result;
}
