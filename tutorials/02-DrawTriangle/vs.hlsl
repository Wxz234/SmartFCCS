float4 main(uint v_id : SV_VertexID) : SV_POSITION
{
    const float4 MyPos[3] = {
        { 0.00f, 0.25f, 0.00f, 1.00f },
        { 0.25f,-0.25f, 0.00f, 1.00f },
        {-0.25f,-0.25f, 0.00f, 1.00f }
    };
    return MyPos[v_id];
}