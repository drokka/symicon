//
// Created by peter on 6/09/18.
//

#include "symi_interface.cpp"
#include "/usr/lib/dart/include/dart_api.h"
#include "/usr/lib/dart/include/dart_native_api.h"
#include "../../../../usr/lib/dart/include/dart_native_api.h"


void wrapCallSym(Dart_Port reply_port_id,
                 Dart_CObject *message) {
    if (message->type == Dart_CObject_Type::Dart_CObject_kArray &&
        1 == message->value.as_array.length) {
        // Use .as_array and .as_int32 to access the data in the Dart_CObject.
        Dart_CObject *param0 = message->value.as_array.values[0];
        if (param0->type == Dart_CObject_Type::Dart_CObject_kInt64) {
            long iters = param0->value.as_int64;

            long value = callSym(iters);

            /* if (value >= -1) */{
                Dart_CObject result;
                result.type = Dart_CObject_kInt64;
                result.value.as_int64 = value;
                //               result.type = Dart_CObject::kUint8Array;
                //               result.value.as_byte_array.values = values;
                //               result.value.as_byte_array.length = length;
                Dart_PostCObject(reply_port_id, &result);
                //               free(values);
                // It is OK that result is destroyed when function exits.
                // Dart_PostCObject has copied its data.
                return;
            }
        }
    }
    Dart_CObject result;
    result.type = Dart_CObject_kNull;
    Dart_PostCObject(reply_port_id, &result);
}

void symServicePort(Dart_NativeArguments arguments) {
    Dart_SetReturnValue(arguments, Dart_Null());
    Dart_Port service_port =
            Dart_NewNativePort("SymArrayService", wrapCallSym, true);
    if (service_port != ILLEGAL_PORT) {
        Dart_Handle send_port = Dart_NewSendPort(service_port);
        Dart_SetReturnValue(arguments, send_port);
    }
}