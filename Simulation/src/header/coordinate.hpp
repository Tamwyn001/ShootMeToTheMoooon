/*
    we define here the function to convert from spherical to cartesian coordinates and from cartesian to ccordinates
*/

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

R3 to_spherical(const R3& cart_coord)
{
    R3 out(0.0,0.0,0.0);

    out.x=pnorm(2,cart_coord);
    
    if (out.x == 0.0)
    {
        out.y=0.0;
    }
    else{
    out.y=acos(cart_coord.z/out.x);
    }

    if((cart_coord.x == 0.0) && (cart_coord.y == 0.0)) {
        out.z = 0;
        return out;
    }
    out.z=sgn(cart_coord.y)*acos(cart_coord.x/pnorm(2, R3(cart_coord.x, cart_coord.y, 0.0)));
    return out;
}

R3 to_cart(const R3& spher_coord)
{
    R3 out(0.0,0.0,0.0);

    out.x=spher_coord.x*sin(spher_coord.y)*cos(spher_coord.z);
    out.y=spher_coord.x*sin(spher_coord.y)*sin(spher_coord.z);
    out.z=spher_coord.x*cos(spher_coord.y);

    return out;
}