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

WASM_EXPORT void bn254_sub_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result)
{
    auto lhs = barretenberg::fr::serialize_from_buffer(left);
    auto rhs = barretenberg::fr::serialize_from_buffer(right);
    auto r = lhs - rhs;
    barretenberg::fr::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_mul_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result)
{
    auto lhs = barretenberg::fr::serialize_from_buffer(left);
    auto rhs = barretenberg::fr::serialize_from_buffer(right);
    auto r = lhs * rhs;
    barretenberg::fr::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_invert_field(fr::in_buf input, fr::out_buf result)
{
    auto input_to_invert = barretenberg::fr::serialize_from_buffer(input);
    auto r = input_to_invert.invert();
    barretenberg::fr::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_exp_field(fr::in_buf base, fr::in_buf exp, fr::out_buf result)
{
    auto base_fr = barretenberg::fr::serialize_from_buffer(base);
    auto exp_fr = barretenberg::fr::serialize_from_buffer(exp);
    auto r = base_fr.pow(exp_fr);
    barretenberg::fr::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_sqrt_field(fr::in_buf base, fr::out_buf result)
{
    // only works if the field passed in is a square residue
    auto base_fr = barretenberg::fr::serialize_from_buffer(base);
    auto result_pair = base_fr.sqrt();
    barretenberg::fr::serialize_to_buffer(result_pair.second, result);
}
}