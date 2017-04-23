/**
 * Copyright (c) 2017 Thomas Hess <thomas.hess@udo.edu>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */
#include "cli_help.hpp"

/**
 * Calculate the indention width for descriptions.
 * This is the amount of characters in a line before the description starts:
 *   -l --long_option ARG   description of argument
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