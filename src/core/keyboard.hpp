/**
 * Copyright (c) 2014 - 2016 Tolga Cakir <tolga@cevel.net>
 *
 * This source file is part of Sidewinder daemon and is distributed under the
 * MIT License. For more information, see LICENSE file.
 */

#ifndef KEYBOARD_CLASS_H
#define KEYBOARD_CLASS_H

#include <string>

#include <poll.h>

#include <process.hpp>
#include <core/hid_interface.hpp>
#include <core/key.hpp>
#include <core/led.hpp>
#include <core/device.hpp>
#include <core/virtual_input.hpp>

/* constants */
const int MAX_BUF = 8;
const int MIN_PROFILE = 0;
const int MAX_PROFILE = 3;

class Keyboard : public Device {
	public:
		void listen();
		Keyboard(Process *process);
		~Keyboard();

	protected:
		bool captureDelays_;
		int profile_;
		int fd_, evfd_;
		Process *process_;
		struct pollfd fds[2];
		HidInterface hidInterface_;
		VirtualInput *virtInput_;
		virtual struct KeyData getInput() = 0;
		void setupPoll();
		static void playMacro(std::string macroPath, VirtualInput *virtInput);
		void recordMacro(std::string path, Led *ledRecord, const int *keyRecord);
		struct KeyData pollDevice(nfds_t nfds);
		virtual void handleKey(struct KeyData *keyData) = 0;
		void handleRecordMode(Led *ledRecord, const int *keyRecord);
};

#endif
