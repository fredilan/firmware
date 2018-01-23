/*
 * Copyright 2017 BrewPi
 *
 * This file is part of BrewPi.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "catch.hpp"
#include <cstdio>

#include "Values.h"
#include "SetPointSimpleBloc.h"
#include "Commands.h"


SCENARIO("A Bloc SetPointSimple object can be created from streamed protobuf data"){
    GIVEN("a protobuf message defining a SetPointSimple object"){
        blox_SetPointSimple_Settings message;
        message.value = 123;

        WHEN("it is encoded to a buffer"){
            uint8_t buf[100];
            pb_ostream_t stream = pb_ostream_from_buffer(buf, sizeof(buf));
            bool status = pb_encode_delimited(&stream, blox_SetPointSimple_Settings_fields, &message);
            THEN("no errors occur"){
                if (!status)
                {
                    WARN("Decoding failed: " << PB_GET_ERROR(&stream));
                    CAPTURE(stream);
                }
                CHECK(status);
            }

            AND_WHEN("we create a DataIn object form that buffer"){
                BufferDataIn in(buf);

                THEN("a newly created SetPointSimpleBloc object can receive settings from the DataIn stream")
                {
                    SetPointSimpleBloc sp;
                    sp.writeMaskedFrom(in, in); // use in as mask too, it is not used.
                    temp_t setting = sp.get().read();
                    temp_t valid;
                    valid.setRaw(123);
                    CHECK(setting == valid);

                    AND_THEN("we can stream that bloc object to a DataOut stream")
                    {
                        // change the value for a round trip test
                        sp.get().write(21.0);

                        uint8_t buf2[100];
                        BufferDataOut out(buf2, sizeof(buf2));
                        sp.readTo(out);

                        sp.get().write(25.0); // change again, so we can verify the receive
                        CHECK(sp.get().read() == temp_t(25.0));

                        BufferDataIn in_roundtrip(buf2);
                        sp.writeMaskedFrom(in_roundtrip, in_roundtrip);
                        CHECK(sp.get().read() == temp_t(21.0));
                    }
                }
            }
        }
    }
}

SCENARIO("Create blox SetPointSimple application object from definition"){
    GIVEN("A BrewBlox SetPointSimple definition")
    {
        bool status;
        blox_SetPointSimple_Settings settings = {123};

        uint8_t buffer1[100];
        pb_ostream_t stream1 = pb_ostream_from_buffer(buffer1, sizeof(buffer1));
        status = pb_encode_delimited(&stream1, blox_SetPointSimple_Settings_fields, &settings);
        CHECK(status);

        BufferDataIn in(buffer1);
        uint8_t len = SetPointSimpleBloc::settingsMaxSize();
        uint8_t typeId = 7;

        ObjectDefinition dfn = {&in, len, typeId};

        WHEN("an application object is created form the definition"){
            Object* obj;
            uint8_t error = createApplicationObject(obj, dfn, false);

            THEN("No errors occur"){
                CHECK(error == errorCode(no_error));
            }
        }
    }
}


