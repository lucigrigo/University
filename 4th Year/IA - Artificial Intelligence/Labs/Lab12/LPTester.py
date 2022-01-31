
# coding: utf-8


from operator import add

# tests two substitutions for equality. Substitutions are instanced.
def get_v_name(f, env):
    return None if not eval("is_variable(f)", env, {"f": f}) else eval("get_name(f)", env, {"f": f})
def s_2_sets(s, env):
    var_sets = {}
    direct = {}
    for v in s:
        t = s[v]
        v2 = get_v_name(t, env)
        var_sets[v] = set([v])
        while v2 and v2 != v:
            var_sets[v].add(v2)
            if v2 in var_sets:
                var_sets[v].update(var_sets[v2])
            var_sets[v2] = var_sets[v]
            if v2 in s:
                t = s[v2]
                v2 = get_v_name(t, env)
            else:
                v2 = None
        if v2 == None and not get_v_name(t, env):
            direct[v] = t
    return var_sets, direct
def eq_s(s1, s2, environment):
    if isinstance(s1, dict) and isinstance(s2, dict):
        ss1 = s_2_sets(s1, environment)
        ss2 = s_2_sets(s2, environment)
#         print(str(ss1) + " /vs/ " + str(ss2))
        return ss1 == ss2
    return s1 == False and s2 == False
# prints a formula f by calling print_formula. If evaluateF, it also evaluates f when printing;
#  otherwise, it is considered that f is already a formula (result of make_*)
def pf(f, environment, evaluateF = True):
    if evaluateF:
        return eval("print_formula("+f+", True)", environment)
    else:
        return eval("print_formula(f, True)", environment, {"f": f})
# prints a substitution s, which is already evaluated (it is either False or a
#  a dictionary with string keys and formula values); uses pf(f, env, False)
def ps(s, environment):
    if s == False:
        return "False"
    return "{" + ", ".join([("?" + v + " -> " + pf(s[v], environment, False)) for v in s]) + "}"
# prints the result (True or False) of a test identified by index.
# if the test fails, the returned value and the check value, and the content of the test (if any) are also printed.
# if printValue, the returned value is also printed if the test passes.
def pTest(index, result, returned, check, test = None, printValue = False):
    out = "Test " + str(index) + ": "
    if result:
        out += "OK" 
        if printValue:
            out += ", got < " + str(returned) + " >"
    else:
        out += "Failed, got < " + str(returned) + " >, should be < " + str(check) + " >."
    if not result and test:
        out += " Test was < " + str(test) + " >."
    print(out)
    return result

# tests for equality of v (not yet evaluated) and c (already evaluated).
def test(v, c, environment, idx):
    value = eval(v, environment)
    result = value == c
    return pTest(idx, result, value, c, v)

# tests for equality of v and c (both already evaluated).
def testA(v, c, environment, idx):
    result = v == c
    return pTest(idx, result, v, c, v)

# calls test(v, c, ...) if all conditions are fulfilled. Conditions are described as
#  tuples (type, params, test_value). c is already evaluated.
def testC(v, c, conds, environment, idx):
    for cond in conds:
        if cond[0] == 'True':
            condition = eval(cond[1], environment)
        elif cond[0] == 'MinLenList':   # (MinLenList, LEN, LIST) -> is LIST a list of length at least LEN
            lst = eval(cond[2], environment)
            condition = isinstance(lst, list) and len(lst) >= cond[1]
        elif cond[0] == 'instance':   # (instance, OBJ, TYPE) -> is OBJ instance of TYPE
            condition = eval(cond[2], environment) and isinstance(eval(cond[2], environment), cond[1])
        elif cond[0] == 'NotSameInstance':  #  (F1, F2, ARG, VAL) -> eval(F1 is F2) with ARG = eval(VAL)
            condition = eval(cond[1] + " is not " + cond[2], environment, {cond[3]: eval(cond[4], environment)})
        else:
            print("Condition type", cond[0], "missing for test", idx)
            return False
        if not condition:
            print("Test", idx, ":", cond[-1] + ". Test was < " + str(v) + " >.")
            return False
    return test(v, c, environment, idx)

# tests if two lists are the same, as sets. The test does not support lists with duplicate elements
def testL(Lv, Lc, env, idx, test = None, renderer = str):
    if test is None: test = [renderer(e) for e in Lc]
    result = isinstance(Lv, list) and len(Lv) == len(Lc) and not [e for e in Lc if e not in Lv]
    if not isinstance(Lv, list): Lc = "a list"
    elif len(Lv) != len(Lc): Lc = "a list of length " + str(len(Lc))
    else: Lc = "a list also containing " + ", ".join([renderer(e) for e in Lc if e not in Lv])
    return pTest(idx, result, [renderer(e) for e in Lv], Lc, test)
    
# creates a testing function that calls Ftest on the result of applying Fval on the test 
#  arguments and the KB. It is presumed that everything is already evaluated, including
#  the test arguments.
def testFKB(Ftest, Fval, KB, singleArgument = False):
    return lambda args, check, env, idx: \
        Ftest(Fval(*(([args] if singleArgument else list(args)) + [KB])), check, env, idx)
    
# tests if two formulas are the same, by evaluating them and testing for equality.
def testForm(v, c, environment, idx):
    value = eval(v, environment)
    check = eval(c, environment)
    Pvalue = pf(v, environment)
    Pcheck = pf(c, environment)
    result = value == check
    return pTest(idx, result, Pvalue, Pcheck, v)

# tests occur-check on two formulas and a substitution (none already evaluated)
def testOccur(f1, f2, si, check, environment, idx):
    value = eval("occur_check("+f1+","+f2+","+si+")", environment)
    initial = eval(si, environment)
    result = value == check
    Ptest = "occur_check " + pf(f1, environment) + " in " + pf(f2, environment) + \
            ((" under " + ps(initial, environment)) if initial else "")
    return pTest(idx, result, value, check, Ptest)

# tests unify on two formulas and a substitution (none already evaluated),
#  and compares the result against the sc substitution (not already evaluated)
def testUnify(f1, f2, si, sc, environment, idx):
    value = eval("unify("+f1+","+f2+","+si+")", environment)
    check = eval(sc, environment)
    initial = eval(si, environment)
    Ptest = "unify " + pf(f1, environment) + " with " + pf(f2, environment) + \
            ((" under " + ps(initial, environment)) if initial else "")
    Pvalue = ps(value, environment)
    Pcheck = ps(check, environment)
    result = eq_s(value, check, environment)
    return pTest(idx, result, Pvalue, Pcheck, Ptest, True)

# tests resolves on two formulas (none already evaluated) and compares the third part of
#  the result with the sc substitution (either False or a dictionary with values not yet evaluated)
def testResolves(f1, f2, sc, environment, idx):
    value = eval("resolves("+f1+","+f2+")", environment)
    Ptest = "resolves " + pf(f1, environment) + " with " + pf(f2, environment)
    # check substitution
    if sc != False and value and isinstance(value, tuple) and len(value) > 2:
        (l1, l2, sv) = value
        Pvalue = "(" + pf(l1, environment, False) + ", " + pf(l2, environment, False) + ", " + ps(sv, environment)
        
        # check literals
        t, res = "Test " + str(idx) + ": ", ". \n\tResult was < " + str(Pvalue) + " > \n\tTest was < " + Ptest + " >"
        lEnv = {'L1': l1, 'L2': l2}
        envs = [environment, lEnv]
        if eval("is_positive_literal(L1)", *envs):
            if not eval("is_negative_literal(L2)", *envs):
                print(t+"First literal is positive but second literal is not negative"+res)
                return False
            else:
                a1 = l1
                a2 = eval("get_args(L2)[0]", *envs)
        elif eval("is_negative_literal(L1)", *envs):
            if not eval("is_positive_literal(L2)", *envs):
                print(t+"First literal is negative but second literal is not positive"+res)
                return False
            else:
                a1 = eval("get_args(L1)[0]", *envs)
                a2 = l2
        else:
            print(t+"First part of the result is not a correct literal"+res)
            return False
        # maybe should check literals belong in sentences and atoms unify under substitution?
        
        
        # check substitution
        scA = {}
        for v in sc:
            scA[v] = eval(sc[v], environment)
        sc = scA
        result = eq_s(sv, sc, environment)
    elif sc == False:
        Pvalue = value
        result = not value
    else:
        print("Test " + str(idx) + " : Result should be a 3-tuple, was < " + str(value) + " >; Test was " + Ptest)
        return False
    Pcheck = ps(sc, environment)
    return pTest(idx, result, Pvalue, Pcheck, Ptest, True)

def testNewClause(c1, c2, l1, l2, s, c, environment, idx):
    s = {v: eval(s[v], environment) for v in s}
    environment['THEC1'] = eval(c1, environment)
    environment['THEC2'] = eval(c2, environment)
    environment['THESUBST'] = s
    value = eval("new_clause((THEC1, THEC2,"+l1+","+l2+", THESUBST))", environment)
    environment['THEVALUE'] = value
    Ptest = "new clause for " + pf(c1, environment) + " / " + pf(c2, environment) + " with "
    Ptest += pf(l1, environment) + " / " + pf(l2, environment) + " " + ps(s, environment)
    isSentence = False if value is None else \
        eval("is_sentence("+("'"+value+"'"  if isinstance(value, str) else 'THEVALUE')+")", environment)
    if isSentence:
        pValue = pf(value, environment, False)
        if pValue.find("???") >= 0:
            pValue += " // " + str(value)
    else:
        pValue = value
    if c == "VOID_CLAUSE":
        if value == eval("VOID_CLAUSE", environment):
            pValue = value
        return pTest(idx, value == eval("VOID_CLAUSE", environment), pValue, "The void clause", Ptest, True)
    Pcheck = pf(c, environment)
    check = eval(c, environment)
    argsval = eval("get_args(THEVALUE)", environment, {'THEVALUE': value}) if isSentence else []
#     print(argsval)
#     print(eval("get_args(THEC1)", environment))
    if not eval("is_atom("+c+")", environment) and (
                eval("get_args(THEC1)", environment) is argsval or eval("get_args(THEC2)", environment) is argsval):
           return pTest(idx, False, pValue, "a different instance than any of the clauses", Ptest, True)
    if not eval("is_atom("+c+")", environment) and eval("len(get_args("+c+"))", environment) > 1 and len(argsval) > 1:
        return testL(eval("get_args(THEVALUE)", environment), eval("get_args("+c+")", environment),
                     environment, idx, Ptest, lambda f: pf(f, environment, False))
    return pTest(idx, value == check, pValue, Pcheck, Ptest, True)

def test_batch(index, environment = None):
    print(">>> Test batch [" + str(index) + "]")
    idx = 0
    succeeded = 0
    for (f, tests) in testBatch[index]:
        for test in tests:
            succeeded += 1 if f(*(list(test) + [environment, idx])) else 0
            idx += 1
    print(">>>  " + str(succeeded) + " / " + str(idx) + " tests successful.")
    return


testBatch = {}

# sanity check
testBatch['sanity'] = [(test, [
            ("True", True),
            ("False", False),
            ("False", True),  # fails
            ("True", False),  # fails
            ("5+3", 8),
            ("add(5,3)", 8),
        ]),
                      (testC, [
            ("True", True, [("True", "True", "This if false.")]),
            ("True", False, [("True", "True", "This if false.")]),  # fails
            ("True", True, [("True", "False", "This if false.")]),  # fails condition
            ("True", True, [("instance", list, "[1, 2]", "Is not list,")]),
            ("True", True, [("instance", list, "[]", "Is None or not list,")]),  # fails condition
            ("True", True, [("instance", list, "(1, 2)", "Is not list,")]),  # fails condition
        ])]
#test_batch('sanity')




args_replaced = "get_args(replace_args(make_and(make_atom('P', make_var('x')), make_atom('Q', make_var('x'))), " +                         "[make_atom('P', make_const(1)), make_atom('Q', make_const(1))]))"
args_replaced2 = "get_args(replace_args(make_neg(make_atom('P', make_var('x'))), [make_atom('P', make_const(5))]))"
args_2 = "get_args(make_and(make_atom('P', make_var('X')), make_atom('Q', make_const('5'))))"
args_3 = "get_args(make_and(make_atom('P', make_var('X')), make_atom('Q', make_var('Y')), make_atom('T', make_var('Z'))))"
args_4 = "get_args(make_and(make_atom('P', make_var('X')), make_atom('Q', make_var('Y')), make_atom('T', make_var('Z')), make_atom('U', make_const('5'))))"
args_4b = "get_args(make_or(make_atom('P', make_var('X')), make_atom('Q', make_var('Y')), make_atom('T', make_var('Z')), make_atom('U', make_const('5'))))"
args_1 = "get_args(replace_args(make_atom('P', make_var('X')), [make_const(2)]))"
args_neg = "get_args(make_neg(make_atom('P', make_var('X'))))"
formula1 = "make_and(make_or(make_neg(make_atom('P', make_var('x'))), make_atom('Q', make_var('x')))," + \
    "make_atom('T', make_var('y'), make_function_call(add, make_const(1), make_const(2))))"
formula2 = "make_and(make_or(make_neg(make_atom('P', make_const(3))), make_atom('Q', make_const(3)))," + \
    "make_atom('T', make_const(4), make_var('z')))"
testBatch[0] = [(test, [
            # 0
            ("is_term(make_const('A'))", True),
            ("is_term(make_var('x'))", True),
            ("is_atom(make_var('x'))", False),
            ("is_term(make_function_call(add, make_const(2), make_var('x')))", True),
            ("is_atom(make_function_call(add, make_const(2), make_var('x')))", False),
            # 5
            ("is_sentence(make_function_call(add, make_const(2), make_var('x')))", False),
            ("is_sentence(make_atom('P', make_var('x')))", True),
            ("is_atom(make_atom('P', make_var('x')))", True),
            ("is_term(make_atom('P', make_var('x')))", False),
            ("is_sentence(make_neg(make_atom('P', make_var('x'))))", True),
            # 10
            ("is_atom(make_neg(make_atom('P', make_var('x'))))", False),
            ("get_value(make_const(2))", 2),
            ("get_name(make_var('X'))", 'X'),
            ("get_name(make_atom('P'))", None),
            ("get_head(make_atom('P'))", 'P'),
            # 15
            ("get_head(make_function_call(add, make_const(2), make_var('x')))", add),
            ("get_head(make_and(make_atom('P', make_const(1)), make_atom('Q', make_const(1)))) ==" + \
             "get_head(make_or(make_atom('P', make_const(1)), make_atom('Q', make_const(1))))", False),
            ("get_head(make_and(make_atom('P', make_const(1)), make_atom('Q', make_const(1)))) == \
              get_head(make_and(make_atom('P', make_const(1)), make_atom('Q', make_const(1)), make_atom('R', make_const(1))))", True),
            ("get_head(make_or(make_atom('P', make_const(1)), make_atom('Q', make_const(1)))) == \
              get_head(make_or(make_atom('P', make_const(1)), make_atom('Q', make_const(1)), make_atom('R', make_const(1))))", True)
        ]),
                (testC, [
            # 19
            ("is_atom("+args_2+"[0])", True, \
                [("MinLenList", 2, args_2, "N/A. Get_args returns a list that is shorter than 2")]),
            ("is_atom("+args_2+"[1])", True, \
                [("MinLenList", 2, args_2, "N/A. Get_args returns a list that is shorter than 2")]),
            ("is_atom("+args_3+"[2])", True, \
                [("MinLenList", 3, args_3, "N/A. Get_args returns a list that is shorter than 3")]),
            ("is_atom("+args_4+"[2])", True, \
                [("MinLenList", 4, args_4, "N/A. Get_args returns a list that is shorter than 4")]),
            ("is_atom("+args_4b+"[2])", True, \
                [("MinLenList", 4, args_4b, "N/A. Get_args returns a list that is shorter than 4")]),
            # 24
            ("is_variable(get_args("+args_2+"[0])[0])", True, \
                [("MinLenList", 2, args_2, "N/A. Get_args returns a list that is shorter than 2")]),
            ("is_sentence("+args_neg+"[0])", True, \
                [("MinLenList", 1, args_neg, "N/A. Get_args did not return a list.")]),
            ("is_constant(get_args("+args_2+"[1])[0])", True, \
                [("MinLenList", 2, args_2, "N/A. Get_args returns a list that is shorter than 2")]),
            ("get_name(get_args(make_atom('P', make_var('X')))[0])", 'X', \
                [("MinLenList", 1, "get_args(make_atom('P', make_var('X')))")]),
            ("is_constant("+args_1+"[0])", True, 
                [("MinLenList", 1, args_1, "N/A. Get_args returns a list that is shorter than 1")]),
            # 25
            ("get_value("+args_1+"[0])", 2, [("MinLenList", 1, args_1, "N/A. Get_args returns a list shorter than 1")]),
            ("get_value(get_args("+args_replaced+"[0])[0])", 1, \
                [("MinLenList", 1, args_replaced, "N/A. Replaced arguments not a list."),
                 ("MinLenList", 1, "get_args("+args_replaced+"[0])", "N/A. Replaced arguments part not a list")]),
            ("is_constant(get_args("+args_replaced2+"[0])[0])", True, \
                [("MinLenList", 1, args_replaced2, "N/A. Replaced arguments not a list"),
                 ("MinLenList", 1, "get_args("+args_replaced2+"[0])", "N/A. Replaced arguments part not a list")]),
            ("True", True, [("NotSameInstance", 
                             "replace_args(F, [make_const(5)])", "F", "F", "make_atom('P', make_var('x'))",
                             "replace_args should return a different instance")]),
        ])]


testBatch[1] = [(testForm, [
            ("substitute(formula1, {'x': make_const(5)})", "test_formula(5)"),
            ("substitute(formula1, {'x': make_var('z'), 'z': make_const(7)})", "test_formula(7)"),
            ("substitute(formula1, {'z': make_const(7), 'x': make_var('z')})", "test_formula(7)"),
            ("substitute(formula1, {'x': make_const(5)})", "test_formula(5)"),
            ("substitute(formula1, {'y': make_function_call(add, make_var('x'), make_const(2)), 'x': make_const(1)})",
                "test_formula(1, True)"),
        ])]

testBatch[2] = [(testOccur, [
            ("make_var('x')", "make_const(5)", "{}", False), #0
            ("make_var('x')", "make_var('y')", "{}", False), #1
            ("make_var('x')", "make_function_call(add, make_var('x'))", "{}", True), #2
            ("make_var('y')", "make_function_call(add, make_var('x'))", "{'x': make_var('y')}", True), #3
            ("make_var('z')", "make_function_call(add, make_var('x'))", \
                                      "{'x': make_var('y'), 'y': make_var('z')}", True), #4
            ("make_var('z')", "make_function_call(add, make_const(5), make_function_call(add, make_var('x')))", \
                                      "{'x': make_var('y'), 'y': make_var('z')}", True), #5
            ("make_var('z')", "make_function_call(add, make_var('w'))",
                                      "{'x': make_var('y'), 'y': make_var('z')}", False), #6
        ])]

testBatch[3] = [(testUnify, [
            #0 # P(B) vs P(A) -> False
            ("make_atom('P', make_const('B'))", "make_atom('P', make_const('A'))", "None", "False"),
            #1 # P(x) vs P(A) -> x: A
            ("make_atom('P', make_var('x'))", "make_atom('P', make_const('A'))", "None", "{'x': make_const('A')}"),
            #2 # P(x, x) vs P(A, A) -> x: A
            ("make_atom('P', make_var('x'), make_var('x'))", "make_atom('P', make_const('A'), make_const('A'))", "None",
                          "{'x': make_const('A')}"),
            #3 # P(x, A) vs P(A, x) -> x: A
            ("make_atom('P', make_var('x'), make_const('A'))", "make_atom('P', make_const('A'), make_var('x'))", "None",
                          "{'x': make_const('A')}"),
            #4 # P(x, A, x) vs P(A, x, A) -> x: A
            ("make_atom('P', make_var('x'), make_const('A'), make_var('x'))", 
                             "make_atom('P', make_const('A'), make_var('x'), make_const('A'))", "None",
                             "{'x': make_const('A')}"),
            #5 # P(x) vs P(add[Z, 5]) -> x: add[Z, 5]
            ("make_atom('P', make_var('x'))", "make_atom('P', make_function_call(add, make_var('Z'), make_const(5)))", "None",
                                "{'x': make_function_call(add, make_var('Z'), make_const(5))}"),
            #6 # P(x, y, z) vs P(A, B, C) -> x: A, y: B, z: C
            ("make_atom('P', make_var('x'), make_var('y'), make_var('z'))", 
                            "make_atom('P', make_const('A'), make_const('B'), make_const('C'))", "None",
                            "{'z': make_const('C'), 'y': make_const('B'), 'x': make_const('A')}"),
            #7 # Q(2, 3, add[x, y]) vs Q(x, y, add[2, 3]) -> x: 2, y: 3
            ("make_atom('Q', make_const(2), make_const(3), make_function_call(add, make_var('x'), make_var('y')))",
                            "make_atom('Q', make_var('x'), make_var('y'), make_function_call(add, make_const(2), make_const(3)))",
                            "None", "{'x': make_const(2), 'y': make_const(3)}"),
            #8 # P(x, y) vs P(x, add[y, 2]) -> False
            ("make_atom('P', make_var('x'), make_var('y'))", 
                         "make_atom('P', make_const('x'), make_function_call(add, make_var('y'), make_const(2)))", "None",
                         "False"),
            #9 # P(B) vs Q(B) -> False
            ("make_atom('P', make_const('B'))", "make_atom('Q', make_const('B'))", "None", "False"),
            #10 # P(A) vs P(A) -> {} (no substitution needed)
            ("make_atom('P', make_const('A'))", "make_atom('P', make_const('A'))", "None", "{}"),
            #11 # P(x) vs P(y) -> {x: y} (or equivalent)
            ("make_atom('P', make_var('x'))", "make_atom('P', make_var('y'))", "None", "{'x': make_var('y')}"),
            #12 # P(y) vs P(x) -> {x: y} (or equivalent)
            ("make_atom('P', make_var('y'))", "make_atom('P', make_var('x'))", "None", "{'x': make_var('y')}"),
           
            #13 # P(x) vs P(A) having x: A -> x: A
            ("make_atom('P', make_var('x'))", "make_atom('P', make_const('A'))", "{'x': make_const('A')}", "{'x': make_const('A')}"),
            #14 # P(x) vs P(A) having x: B -> False
            ("make_atom('P', make_var('x'))", "make_atom('P', make_const('A'))", "{'x': make_const('B')}", "False"),
            
            #15 # P(x, x) vs P(A, A) having x: A -> x: A
            ("make_atom('P', make_var('x'), make_var('x'))", "make_atom('P', make_const('A'), make_const('A'))", 
                         "{'x': make_const('A')}", "{'x': make_const('A')}"),
            
            #16 # P(x, y, z) vs P(A, B, C) having x: A, z: C -> x: A, y: B, z: C
            ("make_atom('P', make_var('x'), make_var('y'), make_var('z'))", 
                            "make_atom('P', make_const('A'), make_const('B'), make_const('C'))",
                            "{'x': make_const('A'), 'z': make_const('C')}",
                            "{'z': make_const('C'), 'y': make_const('B'), 'x': make_const('A')}"),
            #17 # P(A) vs P(A) having x: A -> x: A
            ("make_atom('P', make_const('A'))", "make_atom('P', make_const('A'))",
                            "{'x': make_const('A')}", "{'x': make_const('A')}"),
            #18 # P(x) vs P(y) having x: y -> {x: y} (or equivalent)
            ("make_atom('P', make_var('x'))", "make_atom('P', make_var('y'))", "{'x': make_var('y')}", "{'x': make_var('y')}"),
            #19 # P(y) vs P(x) having y: x -> {y: x} (or equivalent)
            ("make_atom('P', make_var('y'))", "make_atom('P', make_var('x'))", "{'y': make_var('x')}", "{'x': make_var('y')}"),
            
            #20  # P(x, y, z) vs P(y, z, 5) -> {x: 5, y: 5, z: 5}
            ("make_atom('P', make_var('x'), make_var('y'), make_var('z'))",
                "make_atom('P', make_var('y'), make_var('z'), make_const(5))", "None",
                "{'x': make_const(5), 'y': make_const(5), 'z': make_const(5)}"),
#             #21  # P(x, y, z) vs P(y, z, 5) having y: x -> {x: 5, y: 5, z: 5}
#             ("make_atom('P', make_var('x'), make_var('y'), make_var('z'))",
#                 "make_atom('P', make_var('y'), make_var('z'), make_const(5))", "{'y': make_var('x')}",
#                 "{'x': make_const(5), 'y': make_var('x'), 'z': make_const(5)}"),
            #21
            (formula1, formula2, "None", 
                "{'x': make_const(3), 'y': make_const(4), 'z': make_function_call(add, make_const(1), make_const(2))}"),
            ])]
  

testBatch[4] = [(testResolves, [
            #0
            ("KB_America[1]", "KB_America[6]", {'v2': "make_const('General_Awesome')"}),
            ("KB_America[5]", "KB_America[8]", {'v8': "make_const('M1')", 'v9': "make_const('Nono')"}),
            ("KB_America[9]", "KB_America[6]", {'v16': "make_var('v2')"}),
            ("KB_America[3]", "KB_America[10]", {'v18': "make_const('Nono')"}),
            #4
            ("KB_America[0]", "KB_America[1]", False),
            ("KB_America[2]", "KB_America[10]", False),
            ("KB_America[2]", "KB_America[2]", False),
            ("KB_America[6]", "KB_America[6]", False),
            #8
            ("make_or(make_atom('P', make_var('x')), make_atom('Q', make_const(5)))",
                "make_or(make_neg(make_atom('Q', make_const(5))), make_atom('R', make_var('y')))", {}),
            ("make_or(make_atom('P', make_const(5)), make_atom('Q', make_function_call(add, make_var('y'), make_var('x'))))",
                "make_or(make_neg(make_atom('P', make_function_call(add, make_var('x')))), make_neg(make_atom('Q', make_var('x'))))", False)
    ])]

testBatch[5] = [(testNewClause, [
            #0
            ("make_atom('P', make_var('x'))", "make_neg(make_atom('P', make_const(5)))",
                "make_atom('P', make_var('x'))", "make_neg(make_atom('P', make_const(5)))",
                {'x': "make_const(5)"}, "VOID_CLAUSE"),
            ("make_or(make_atom('P', make_var('x')), make_atom('Q', make_var('y')))", "make_neg(make_atom('P', make_const(5)))",
                "make_atom('P', make_var('x'))", "make_neg(make_atom('P', make_const(5)))",
                {'x': "make_const(5)"}, "make_atom('Q', make_var('y'))"),
            ("make_atom('P', make_var('x'))", 
                "make_or(make_neg(make_atom('Q', make_var('x'))), make_neg(make_atom('P', make_const(5))))",
                "make_atom('P', make_var('x'))", "make_neg(make_atom('P', make_const(5)))",
                {'x': "make_const(5)"}, "make_neg(make_atom('Q', make_const(5)))"),
            ("make_or(make_atom('P', make_const(6)), make_atom('P', make_var('x')))", 
                "make_or(make_neg(make_atom('Q', make_var('x'))), make_neg(make_atom('P', make_const(5))))",
                "make_atom('P', make_var('x'))", "make_neg(make_atom('P', make_const(5)))",
                {'x': "make_const(5)"}, "make_or(make_neg(make_atom('Q', make_const(5))), make_atom('P', make_const(6)))")
    ])]

