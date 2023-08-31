#include "barretenberg/common/serialize.hpp"
#include "c_bind.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result)
{
    auto lhs = barretenberg::fr::serialize_from_buffer(left);
    auto rhs = barretenberg::fr::serialize_from_buffer(right);
    auto r = lhs + rhs;
    barretenberg::fr::serialize_to_buffer(r, result);
}
}