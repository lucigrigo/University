function sol = met_bisect(a, b, tolerance, func)
    if (func(a) * func(b)) > 0
        sol = -1;
        return;
    end
    sol = ((a + b) / 2);
    while abs(sol) > tolerance
        if func(sol) > 0
            if func(a) > func(b)
                a = sol;
            else
                b = sol;
            end
        else
            if func(a) > func(b)
                b = sol;
            else
                a = sol;
            end
        end
        sol = ((a + b) / 2);
    end
endfunction