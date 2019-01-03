#pragma once

#include <krpc_cnano/decoder.h>
#include <krpc_cnano/encoder.h>
#include <krpc_cnano/error.h>
#include <krpc_cnano/memory.h>
#include <krpc_cnano/pb_decode.h>
#include <krpc_cnano/pb_encode.h>
#include <krpc_cnano/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KRPC_TYPE_TUPLE_DOUBLE_DOUBLE
#define KRPC_TYPE_TUPLE_DOUBLE_DOUBLE

typedef struct krpc_tuple_double_double_s krpc_tuple_double_double_t;
struct krpc_tuple_double_double_s {
  double e0;
  double e1;
};

krpc_error_t krpc_encode_tuple_double_double(
  pb_ostream_t * stream, const krpc_tuple_double_double_t * value);
krpc_error_t krpc_encode_size_tuple_double_double(
  size_t * size, const krpc_tuple_double_double_t * value);
bool krpc_encode_callback_tuple_double_double(
  pb_ostream_t * stream, const pb_field_t * field, void * const * arg);
krpc_error_t krpc_decode_tuple_double_double(
  pb_istream_t * stream, krpc_tuple_double_double_t * value);

#endif  // KRPC_TYPE_TUPLE_DOUBLE_DOUBLE

krpc_error_t krpc_Trajectories_GetImpactTime(krpc_connection_t connection, double * returnValue);

krpc_error_t krpc_Trajectories_HasImpact(krpc_connection_t connection, bool * returnValue);

krpc_error_t krpc_Trajectories_ImpactPos(krpc_connection_t connection, krpc_tuple_double_double_t * returnValue);

// Implementation

#ifndef KRPC_IMPL_TYPE_TUPLE_DOUBLE_DOUBLE
#define KRPC_IMPL_TYPE_TUPLE_DOUBLE_DOUBLE

static bool krpc_encode_callback_items_tuple_double_double(
  pb_ostream_t * stream, const pb_field_t * field, void * const * arg) {
  const krpc_tuple_double_double_t * value = (const krpc_tuple_double_double_t*)(*arg);
  {
    if (!pb_encode_tag_for_field(stream, field))
      KRPC_CALLBACK_RETURN_ERROR("encoding tag for tuple item");
    size_t size;
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_size_double(&size, value->e0));
    if (!pb_encode_varint(stream, size))
      KRPC_CALLBACK_RETURN_ERROR("encoding size for tuple item");
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_double(stream, value->e0));
  }
  {
    if (!pb_encode_tag_for_field(stream, field))
      KRPC_CALLBACK_RETURN_ERROR("encoding tag for tuple item");
    size_t size;
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_size_double(&size, value->e1));
    if (!pb_encode_varint(stream, size))
      KRPC_CALLBACK_RETURN_ERROR("encoding size for tuple item");
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_double(stream, value->e1));
  }
  return true;
}

inline krpc_error_t krpc_encode_tuple_double_double(
  pb_ostream_t * stream, const krpc_tuple_double_double_t * value) {
  krpc_schema_Tuple message = krpc_schema_Tuple_init_default;
  message.items.funcs.encode = &krpc_encode_callback_items_tuple_double_double;
  message.items.arg = (krpc_tuple_double_double_t*)value;
  KRPC_RETURN_ON_ERROR(krpc_encode_message_Tuple(stream, &message));
  return KRPC_OK;
}

inline krpc_error_t krpc_encode_size_tuple_double_double(
  size_t * size, const krpc_tuple_double_double_t * value) {
  pb_ostream_t stream = PB_OSTREAM_SIZING;
  KRPC_RETURN_ON_ERROR(krpc_encode_tuple_double_double(&stream, value));
  *size = stream.bytes_written;
  return KRPC_OK;
}

inline bool krpc_encode_callback_tuple_double_double(
  pb_ostream_t * stream, const pb_field_t * field, void * const * arg) {
  if (!pb_encode_tag_for_field(stream, field))
    KRPC_CALLBACK_RETURN_ERROR("encoding tag for tuple_double_double");
  krpc_tuple_double_double_t * value = (krpc_tuple_double_double_t*)(*arg);
  size_t size;
  KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_size_tuple_double_double(&size, value));
  if (!pb_encode_varint(stream, size))
    KRPC_CALLBACK_RETURN_ERROR("encoding size for tuple_double_double");
  KRPC_CALLBACK_RETURN_ON_ERROR(krpc_encode_tuple_double_double(stream, value));
  return true;
}

static bool krpc_decode_callback_item_tuple_double_double(
  pb_istream_t * stream, const pb_field_t * field, void ** arg) {
  typedef struct {size_t pos; krpc_tuple_double_double_t * value;} State;
  State * state = (State*)(*arg);
  krpc_tuple_double_double_t * value = state->value;
  switch (state->pos) {
  case 0:
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_decode_double(stream, &value->e0));
    break;
  case 1:
    KRPC_CALLBACK_RETURN_ON_ERROR(krpc_decode_double(stream, &value->e1));
    break;
  default:
    KRPC_CALLBACK_RETURN_ERROR("unexpected tuple item");
  }
  state->pos++;
  return true;
}

inline krpc_error_t krpc_decode_tuple_double_double(
  pb_istream_t * stream, krpc_tuple_double_double_t * value) {
  krpc_schema_Tuple message = krpc_schema_Tuple_init_default;
  message.items.funcs.decode = &krpc_decode_callback_item_tuple_double_double;
  typedef struct { size_t pos; krpc_tuple_double_double_t * value; } State;
  State state = { 0, value };
  message.items.arg = &state;
  KRPC_RETURN_ON_ERROR(krpc_decode_message_Tuple(stream, &message));
  return KRPC_OK;
}

#endif  // KRPC_IMPL_TYPE_TUPLE_DOUBLE_DOUBLE

inline krpc_error_t krpc_Trajectories_GetImpactTime(krpc_connection_t connection, double * returnValue) {
  krpc_call_t _call;
  krpc_argument_t _arguments[0];
  KRPC_CHECK(krpc_call(&_call, 3442197282, 2, 0, _arguments));
  krpc_result_t _result = KRPC_RESULT_INIT_DEFAULT;
  KRPC_CHECK(krpc_init_result(&_result));
  KRPC_CHECK(krpc_invoke(connection, &_result.message, &_call.message));
  if (returnValue) {
    pb_istream_t _stream;
    KRPC_CHECK(krpc_get_return_value(&_result, &_stream));
    KRPC_CHECK(krpc_decode_double(&_stream, returnValue));
  }
  KRPC_CHECK(krpc_free_result(&_result));
  return KRPC_OK;
}

inline krpc_error_t krpc_Trajectories_HasImpact(krpc_connection_t connection, bool * returnValue) {
  krpc_call_t _call;
  krpc_argument_t _arguments[0];
  KRPC_CHECK(krpc_call(&_call, 3442197282, 3, 0, _arguments));
  krpc_result_t _result = KRPC_RESULT_INIT_DEFAULT;
  KRPC_CHECK(krpc_init_result(&_result));
  KRPC_CHECK(krpc_invoke(connection, &_result.message, &_call.message));
  if (returnValue) {
    pb_istream_t _stream;
    KRPC_CHECK(krpc_get_return_value(&_result, &_stream));
    KRPC_CHECK(krpc_decode_bool(&_stream, returnValue));
  }
  KRPC_CHECK(krpc_free_result(&_result));
  return KRPC_OK;
}

inline krpc_error_t krpc_Trajectories_ImpactPos(krpc_connection_t connection, krpc_tuple_double_double_t * returnValue) {
  krpc_call_t _call;
  krpc_argument_t _arguments[0];
  KRPC_CHECK(krpc_call(&_call, 3442197282, 1, 0, _arguments));
  krpc_result_t _result = KRPC_RESULT_INIT_DEFAULT;
  KRPC_CHECK(krpc_init_result(&_result));
  KRPC_CHECK(krpc_invoke(connection, &_result.message, &_call.message));
  if (returnValue) {
    pb_istream_t _stream;
    KRPC_CHECK(krpc_get_return_value(&_result, &_stream));
    KRPC_CHECK(krpc_decode_tuple_double_double(&_stream, returnValue));
  }
  KRPC_CHECK(krpc_free_result(&_result));
  return KRPC_OK;
}

#ifdef __cplusplus
}  // extern "C"
#endif
