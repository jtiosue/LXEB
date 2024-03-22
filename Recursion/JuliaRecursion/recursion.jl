filename = "computedG.csv";

g = Dict();

for line = readlines(filename)
    l = split(line, ",");
    n = parse(Int, l[1]);
    a = [parse(Int, l[2]), parse(Int, l[3]), parse(Int, l[4])];
    val = Vector{BigInt}();
    for v = l[5:length(l)]
        push!(val, parse(BigInt, v));
    end
    g[(n, a)] = val;
end

function appendG(n, a, val)
    f = open(filename, "a");
    write(f, string(n)*","*string(a[1])*","*string(a[2])*","*string(a[3])*",")
    for i=1:length(val)-1
        write(f, string(val[i])*",");
    end
    write(f, string(val[length(val)])*"\n");
    close(f);
end

caseToP = Dict(
   1 => [], 2 => [], -2 => [], 3 => [], 4 => [], 
   5 => [1, 1], -5 => [3, 3], 6 => [1, 1], -6 => [3, 3], 7 => [2, 2], 
   8 => [2, 2], 9 => [1, 2], -9 => [2, 3], 
   10 => [1, 2], -10 => [2, 3], 11 => [1, 3], 12 => [1, 3],
   13.1 => [1, 1, 2, 2], 13.2 => [1, 1, 2, 2], 13.3 => [1, 1, 2, 2],
   -13.1 => [2, 2, 3, 3], -13.2 => [2, 2, 3, 3], -13.3 => [2, 2, 3, 3],
   14.1 => [1, 1, 3, 3], 14.2 => [1, 1, 3, 3], 14.3 => [1, 1, 3, 3],
   15.1 => [1, 1, 2, 3], 15.2 => [1, 1, 2, 3], 15.3 => [1, 1, 2, 3],
   -15.1 => [1, 2, 3, 3], -15.2 => [1, 2, 3, 3], -15.3 => [1, 2, 3, 3],
   16.1 => [1, 2, 2, 3], 16.2 => [1, 2, 2, 3], 16.3 => [1, 2, 2, 3],
   17.1 => [1, 1, 2, 2, 3, 3], 17.2 => [1, 1, 2, 2, 3, 3], 
   17.3 => [1, 1, 2, 2, 3, 3], 17.4 => [1, 1, 2, 2, 3, 3]
);

caseToLoop = Dict(
   1 => Vector{BigInt}([0, 2, 2]), 2 => Vector{BigInt}([0, 4, 3, 1]), -2 => Vector{BigInt}([0, 4, 3, 1]), 
   3 => Vector{BigInt}([0, 6, 2]), 4 => Vector{BigInt}([0, 16, 14, 2]), 5 => Vector{BigInt}([2, 2]), -5 => Vector{BigInt}([2, 2]), 
   6 => Vector{BigInt}([4, 3, 1]), -6 => Vector{BigInt}([4, 3, 1]), 7 => Vector{BigInt}([2, 2]), 8 => Vector{BigInt}([6, 2]), 
   9 => Vector{BigInt}([8, 6, 2]), -9 => Vector{BigInt}([8, 6, 2]), 
   10 => Vector{BigInt}([16, 14, 2]), -10 => Vector{BigInt}([16, 14, 2]), 11 => Vector{BigInt}([12, 4]), 
   12 => Vector{BigInt}([16, 14, 2]), 13.1 => Vector{BigInt}([1]), 13.2 => Vector{BigInt}([2, 1]), 
   13.3 => Vector{BigInt}([0]), -13.1 => Vector{BigInt}([1]), -13.2 => Vector{BigInt}([2, 1]), -13.3 => Vector{BigInt}([0]), 
   14.1 => Vector{BigInt}([2]), 14.2 => Vector{BigInt}([0]), 14.3 => Vector{BigInt}([2]), 15.1 => Vector{BigInt}([4, 2]), 
   15.2 => Vector{BigInt}([4, 1]), 
   15.3 => Vector{BigInt}([4, 1]), -15.1 => Vector{BigInt}([4, 2]), -15.2 => Vector{BigInt}([4, 1]), -15.3 => Vector{BigInt}([4, 1]), 
   16.1 => Vector{BigInt}([6, 1]), 16.2 => Vector{BigInt}([6, 1]), 16.3 => Vector{BigInt}([2]), 17.1 => Vector{BigInt}([1]), 
   17.2 => Vector{BigInt}([1]), 17.3 => Vector{BigInt}([1]), 17.4 => Vector{BigInt}([1])
);

caseToInternal = Dict(
   1 => [0, 0, 0], 
   2 => [2, 0, 0], -2 => [0, 0, 2], 3 => [0, 2, 0], 4 => [1, 1, 1], 
   5 => [0, 0, 0], -5 => [0, 0, 0], 6 => [0, 0, 2], -6 => [2, 0, 0], 
   7 => [0, 0, 0], 8 => [0, 2, 0], 9 => [1, 0, 0], -9 => [0, 0, 1], 
   10 => [0, 1, 1], -10 => [1, 1, 0], 11 => [0, 1, 0],
   12 => [1, 0, 1],
   13.1 => [0, 0, 0], 13.2 => [0, 0, 0], 13.3 => [0, 0, 0],
   -13.1 => [0, 0, 0], -13.2 => [0, 0, 0], -13.3 => [0, 0, 0],
   14.1 => [0, 0, 0], 14.2 => [0, 0, 0], 14.3 => [0, 0, 0],
   15.1 => [0, 0, 1], 15.2 => [0, 0, 1], 15.3 => [0, 0, 1],
   -15.1 => [1, 0, 0], -15.2 => [1, 0, 0], -15.3 => [1, 0, 0],
   16.1 => [0, 1, 0], 16.2 => [0, 1, 0], 16.3 => [0, 1, 0],
   17.1 => [0, 0, 0], 17.2 => [0, 0, 0], 17.3 => [0, 0, 0], 
   17.4 => [0, 0, 0]
);

ordering1Through12 = Dict(0 => [[1, 2]]);
ordering13Through16 = Dict(
   1 => [[1, 2], [3, 4]],
   2 => [[1, 3], [2, 4]],
   3 => [[1, 4], [2, 3]]
);
ordering17 = Dict(
   1 => [[1, 2], [3, 5], [4, 6]],
   2 => [[1, 6], [2, 4], [3, 5]],
   3 => [[1, 3], [2, 5], [4, 6]],
   4 => [[1, 3], [2, 4], [5, 6]]
);

function getOrdering(case)
    subcase = Int(round(10*(abs(case) - floor(abs(case)))));
    if abs(case) <= 12
        return ordering1Through12[subcase];
    elseif abs(case) >= 17
        return ordering17[subcase];
    else
        return ordering13Through16[subcase];
    end
end

function raggedAdd(x, y)
    if length(x) == length(y)
        return x + y;
    elseif length(x) > length(y)
        return raggedAdd(y, x);
    else
        z = copy(y);
        for i=1:length(x)
            z[i] += x[i];
        end
        return z;
    end
end

function multiply(x, y)
    z = zeros(eltype(x), length(x)+length(y)-1);
    for k=0:length(x)-1
        for j=1:length(y)
            z[k+j] += x[k+1] * y[j];
        end
    end
    return z;
end

function bij(n, b, i, j)
    """
    returns BigInt
    """
    if i == j == 1
        return BigInt(n - (b[1] + b[2]) / 2);
    elseif i == j == 2
        return BigInt(n - (b[1] + b[3]) / 2);
    elseif i == j == 3
        return BigInt(n - (b[2] + b[3]) / 2);
    elseif (i == 1 && j == 2) || (j == 1 && i == 2)
        return big(b[1]);
    elseif (i == 1 && j == 3) || (j == 1 && i == 3)
        return big(b[2]);
    elseif (i == 2 && j == 3) || (j == 2 && i == 3)
        return big(b[3]);
    end
end

function tuples(a, len)
    args = [];
    for i=1:len
        push!(args, a);
    end
    return Iterators.product(args...)
end

function computeDeltaAndComb(n, case, a)
    list = [];
    for v = tuples((1, 2, 3), length(caseToP[case]))
        # v is ab, abcd, or abcdef
        Delta = delta(case, collect(v)) - caseToInternal[case];
        push!(list, (combinatorial(n-1, case, a+Delta, collect(v)), Delta));
    end
    return list;
end

function delta(case, v)
    x = Dict("11"=> 0, "12"=>0, "13"=>0, "22"=>0, "23"=>0, "33"=>0);
    p = caseToP[case];
    
    if length(p) != 0
        for index = getOrdering(case)
            x[join(map(a->string(a), sort(v[index])))] += 1;
        end
        for i=1:length(v)
            x[join(map(a->string(a), sort([p[i], v[i]])))] -= 1;
        end
        
    end
    
    return [x["12"], x["13"], x["23"]];
end

function combinatorial(n, case, b, vv)
    """
    returns BigInt
    """
    if length(vv) == 0
        return 1;
    end
    
    lenp = length(caseToP[case]);
    v = vv[collect(Iterators.flatten(getOrdering(case)))];
    
    if lenp == 0
        return 1;
    elseif lenp == 2
        return 2^Int(v[1] == v[2]) * bij(n, b, v[1], v[2]);
    elseif lenp == 4
        return 2^Int(v[1] == v[2]) * 2^Int(v[3] == v[4]) * (
            2 * binomial(bij(n, b, v[1], v[2]), 2) * Int(sort(v[1:2]) == sort(v[3:4]))
            + bij(n, b, v[1], v[2]) * bij(n, b, v[3], v[4]) * Int(sort(v[1:2]) != sort(v[3:4]))
        );
    elseif lenp == 6
        return (
            8^Int(v[1] == v[2]) * 6 * binomial(bij(n, b, v[1], v[2]), 3) * Int(sort(v[1:2]) == sort(v[3:4]) == sort(v[5:6]))
            + 2^Int(v[1] == v[2]) * 2^Int(v[3] == v[4]) * 2 * binomial(bij(n, b, v[1], v[2]), 2) * 2^Int(v[5] == v[6]) * bij(n, b, v[5], v[6]) * Int(sort(v[1:2]) == sort(v[3:4]) != sort(v[5:6]))
            + 2^Int(v[1] == v[2]) * 2^Int(v[5] == v[6]) * 2 * binomial(bij(n, b, v[1], v[2]), 2) * 2^Int(v[3] == v[4]) * bij(n, b, v[3], v[4]) * Int(sort(v[1:2]) == sort(v[5:6]) != sort(v[3:4]))
            + 2^Int(v[3] == v[4]) * 2^Int(v[5] == v[6]) * 2 * binomial(bij(n, b, v[3], v[4]), 2) * 2^Int(v[1] == v[2]) * bij(n, b, v[1], v[2]) * Int(sort(v[1:2]) != sort(v[3:4]) == sort(v[5:6]))
            + 2^Int(v[1] == v[2]) * 2^Int(v[3] == v[4]) * 2^Int(v[5] == v[6]) * bij(n, b, v[1], v[2]) * bij(n, b, v[3], v[4]) * bij(n, b, v[5], v[6]) * Int(sort(v[1:2]) != sort(v[3:4]) != sort(v[5:6]) != sort(v[1:2]))
        );
    end
end

function computeG(n, a)
    val = [big(0)];
    if haskey(g, (n, a))
        return g[(n, a)];
    elseif a[1] < 0 || a[2] < 0 || a[3] < 0
        return val;
    end
    for index = [[1, 2], [1, 3], [2, 3]]
        if sum(a[index]) > 2*n || isodd(sum(a[index]))
            return val;
        end
    end
    
    for case = keys(caseToP)
        for tup = computeDeltaAndComb(n, case, a)
            # tup = [combinatorial factor, Delta]
            val = raggedAdd(
                val,
                tup[1] * multiply(caseToLoop[case], computeG(n-1, a + tup[2]))
            );
        end
    end
    
    g[(n, a)] = val;
    appendG(n, a, val);
    return val;
end


for n=1:30
    println("Starting n = ", n)
    l = computeG(n, [0, 0, 0]);
end


