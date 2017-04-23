/**
 * Copyright (c) 2017 Thomas Hess <thomas.hess@udo.edu>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */

#ifndef CLI_HELP_CLASS_H
#define CLI_HELP_CLASS_H

#include <string>

/**
 * Formats and returns the command line help text. This function does not print anything to std::cout.
 * @returns Formatted command line help text
 */
const std::string get_formatted_help_text(const std::string program_name);

#endif // CLI_HELP_CLASS_H
