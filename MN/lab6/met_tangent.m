function sol = met_tangent(a, b, tolerance, func, deriv)
    if(func(a) * func(b)) > 0
        sol = -1;
        return;
    end
    sol = ((a + b) / 2);
    sol_one = (sol - (func(sol) / deriv(sol)));
    if func(a) > func(b)
        temp = b;
        b = a;
        a = temp;
    end
    while abs(sol_one) > tolerance
        sol = sol_one;
        sol_one = (sol - (func(sol) / deriv(sol)));
        break;
    endwhile
endfunction