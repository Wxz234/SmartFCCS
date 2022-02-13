cbuffer cb_static : register(b0) {
    row_major matrix camera_mat;
};

float4 main(uint v_id : SV_VertexID) : SV_POSITION
{
    const float4 MyPos[3] = {
        { 0.0f, 25.f, 99.00f, 1.00f },
        { 25.f,-25.f, 99.00f, 1.00f },
        {-25.f,-25.f, 99.00f, 1.00f }
    };
    return mul(MyPos[v_id], camera_mat);
}