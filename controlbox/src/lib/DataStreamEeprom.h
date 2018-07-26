/*
 * Copyright 2014-2015 Matthew McGowan.
 *
 * This file is part of Nice Firmware.
 *
 * Controlbox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Controlbox.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include "DataStream.h"
#include "EepromTypes.h"
#include "EepromAccess.h"

namespace cbox {

/**
 * Provides storage for a stream offset and length.
 */
template <class Offset, class Length> class StreamRegion
{
	protected:
		Offset _offset;
		Length _length;

	public:
		Offset offset() { return _offset; }
		Length length() { return _length; }

		void reset(Offset o, Length l) {
			_offset = o;
			_length = l;
		}
};

struct EepromStreamRegion : public StreamRegion<eptr_t, stream_size_t>
{
};

/**
 * A datastream implementation that writes to a region of eeprom.
 * Eeprom is written via the EepromAccess helper.
 * The stream is only written up to the length specified - once that length has been filled
 * writes are silently failed.
 * @see EepromAccess
 */
class EepromDataOut : public DataOut, public EepromStreamRegion
{
private:
	EepromAccess& eepromAccess;
public:

	EepromDataOut(EepromAccess& ea) :eepromAccess(ea) {}

	virtual bool write(uint8_t value) override final {
		if (_length) {
			eepromAccess.writeByte(_offset++, value);
			_length--;
			return true;
		}
		return false;
	}

	virtual void close() override final {
		_length = 0;
	}

};


/**
 * A data input stream that reads from a region of eeprom.
 * @see EepromAccess
 */
class EepromDataIn : public DataIn, public EepromStreamRegion
{
private:
    EepromAccess& eepromAccess;
public:

	EepromDataIn(EepromAccess& ea):eepromAccess(ea) {}

	virtual bool hasNext() override final { return _length; }
	virtual uint8_t peek() override final { return eepromAccess.readByte(_offset); }

	virtual uint8_t next() override final {
		uint8_t result = 0;
		if (_length) {
			_length--;
			result = eepromAccess.readByte(_offset++);
		}
		return result;
	}
	virtual stream_size_t available() override final { return _length; }
};

}
