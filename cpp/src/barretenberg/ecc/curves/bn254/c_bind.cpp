#include "barretenberg/common/serialize.hpp"
#include "c_bind.hpp"
#include "g1.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs + rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_sub_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs - rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_mul_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs * rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_invert_field(fq::in_buf input, fq::out_buf result)
{
    auto input_to_invert = barretenberg::fq::serialize_from_buffer(input);
    auto r = input_to_invert.invert();
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_exp_field(fq::in_buf base, fq::in_buf exp, fq::out_buf result)
{
    auto base_fr = barretenberg::fq::serialize_from_buffer(base);
    auto exp_fr = barretenberg::fq::serialize_from_buffer(exp);
    auto r = base_fr.pow(exp_fr);
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_sqrt_field(fq::in_buf base, fq::out_buf result)
{
    // only works if the field passed in is a square residue
    auto base_fr = barretenberg::fq::serialize_from_buffer(base);
    auto result_pair = base_fr.sqrt();
    barretenberg::fq::serialize_to_buffer(result_pair.second, result);
}

WASM_EXPORT void bn254_random_point(g1::affine_element::out_buf result)
{
    auto r = barretenberg::g1::affine_element::random_element();
    barretenberg::g1::affine_element::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_add_points(fq::in_buf p1_x, fq::in_buf p1_y, fq::in_buf p2_x, fq::in_buf p2_y, fq::out_buf result)
{
    auto p1_x_fq = barretenberg::fq::serialize_from_buffer(p1_x);
    auto p1_y_fq = barretenberg::fq::serialize_from_buffer(p1_y);
    auto p2_x_fq = barretenberg::fq::serialize_from_buffer(p2_x);
    auto p2_y_fq = barretenberg::fq::serialize_from_buffer(p2_y);
    g1::affine_element lhs;
    lhs.x = p1_x_fq.to_montgomery_form();
    lhs.y = p1_y_fq.to_montgomery_form();
    g1::affine_element rhs;
    rhs.x = p2_x_fq.to_montgomery_form();
    rhs.y = p2_y_fq.to_montgomery_form();
    g1::affine_element r = lhs + rhs;
    auto final = r.x.from_montgomery_form();
    barretenberg::fq::serialize_to_buffer(final, result);
}

WASM_EXPORT void bn254_double_point(fq::in_buf p1_x, fq::in_buf p1_y, fq::out_buf x, fq::out_buf z)
{
    auto p1_x_fq = barretenberg::fq::serialize_from_buffer(p1_x);
    auto p1_y_fq = barretenberg::fq::serialize_from_buffer(p1_y);
    g1::affine_element lhs;
    lhs.x = p1_x_fq.to_montgomery_form();
    lhs.y = p1_y_fq.to_montgomery_form();
    auto ext_point = g1::element(lhs);
    g1::element r = ext_point.dbl();
    auto final_x = r.x.from_montgomery_form();
    auto final_z = r.z.from_montgomery_form();
    barretenberg::fq::serialize_to_buffer(final_x, x);
    barretenberg::fq::serialize_to_buffer(final_z, z);
}
}