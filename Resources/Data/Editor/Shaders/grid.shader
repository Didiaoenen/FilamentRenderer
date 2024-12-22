material {
    name : EditorGridMat,
    shadingModel : unlit,
    parameters : [
        {
            type : float3,
            name : baseColor
        }
    ],
    blending : transparent,
}

fragment {
    float mag(float lp)
    {
        float lineWidth = 1.0f;

        float2 coord     = getWorldPosition().xz / lp;
        float2 grid      = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
        float line       = min(grid.x, grid.y);
        float lineResult = lineWidth - min(line, lineWidth);

        return lineResult;
    }

    float grid(float height, float a, float b, float c)
    {
        float cl   = mag(a);
        float ml   = mag(b);
        float fl   = mag(c);

        float cmit =  10.0f;
        float cmet =  40.0f;
        float mfit =  80.0f;
        float mfet =  160.0f;

        float df   = clamp((height - cmit) / (cmet - cmit), 0.0f, 1.0f);
        float dff  = clamp((height - mfit) / (mfet - mfit), 0.0f, 1.0f);

        float inl  = mix(cl, ml, df);
        float fnl  = mix(inl, fl, dff);

        return fnl;
    }

    void material(inout MaterialInputs material) {
        prepareMaterial(material);

        float height = distance(getWorldViewVector().y, getWorldPosition().y);

        float gridA = grid(height, 1.0f, 4.0f, 8.0f);
        float gridB = grid(height, 4.0f, 16.0f, 32.0f);

        float grid  = gridA * 0.5f + gridB;

        vec2 viewdirW    = getWorldViewVector().xz - getWorldPosition().xz;
        float viewdist    = length(viewdirW);
        
        material.baseColor.rgb = materialParams.baseColor;
        material.baseColor.a = grid;
    }
}
