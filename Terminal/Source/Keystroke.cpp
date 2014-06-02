/*
* BearLibTerminal
* Copyright (C) 2014 Cfyz
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is furnished to do
* so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define BEARLIBTERMINAL_BUILDING_LIBRARY
#include "BearLibTerminal.h"
#include "Keystroke.hpp"
#include <stdexcept>

namespace BearLibTerminal
{
	/*
	constexpr std::uint32_t Keystroke::None;
	constexpr std::uint32_t Keystroke::KeyPress;
	constexpr std::uint32_t Keystroke::KeyRelease;
	constexpr std::uint32_t Keystroke::Keys;
	constexpr std::uint32_t Keystroke::MouseMove;
	constexpr std::uint32_t Keystroke::MouseScroll;
	constexpr std::uint32_t Keystroke::Mouse;
	constexpr std::uint32_t Keystroke::Unicode;
	constexpr std::uint32_t Keystroke::All;

	Keystroke::Keystroke(Type type, std::uint8_t scancode): // keypress/keyrelease events
		type(type),
		scancode(scancode),
		character(0),
		x(0), y(0), z(0)
	{ }

	Keystroke::Keystroke(Type type, std::uint8_t scancode, char16_t character): // character-producing keypress event
		type(type),
		scancode(scancode),
		character(character),
		x(0), y(0), z(0)
	{ }

	Keystroke::Keystroke(Type type, std::uint8_t scancode, int x, int y, int z): // mouse events
		type(type),
		scancode(scancode),
		character(0),
		x(x), y(y), z(z)
	{ }
	//*/

	// ------------------------------------------------------------------------

	Event::Event(int code):
		domain(GetDomainByCode(code)),
		code(code)
	{ }

	Event::Event(int code, std::unordered_map<int, int> properties):
		domain(GetDomainByCode(code)),
		code(code),
		properties(std::move(properties))
	{ }

	int& Event::operator[](int index)
	{
		return properties[index];
	}

	Event::Domain Event::GetDomainByCode(int code)
	{
		if ((code & 0xFF) >= TK_A && (code & 0xFF) <= TK_CONTROL+1) // FIXME: TK_ALT constant
		{
			return Domain::Keyboard;
		}
		else if ((code & 0xFF) >= TK_MOUSE_LEFT && (code & 0xFF) <= TK_MOUSE_PIXEL_Y)
		{
			return Domain::Mouse;
		}
		else if (code <= 0 || (code >= TK_CLOSE && code <= TK_RESIZED))
		{
			return Domain::System;
		}
		else if (code >= 0x1000)
		{
			return Domain::Internal;
		}
		else
		{
			throw std::runtime_error("Unknown event code");
		}
	}
}
