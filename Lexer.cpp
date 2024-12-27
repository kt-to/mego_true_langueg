#include "Lexer.h"

void Program() {
    int cnt = 1;
    while (cnt--) {
        if (lex.get_type() == "name") {
            Function_declarations();
            cnt++;
        } else {
            if (lex.get_type() == "type") {
                Declaring_variables();
                cnt++;
            }
        }
    }
    if (lex.get_type() == "main") {
        Main();
    } else {
        throw "Problem with Main";
    }
}

void Main() {
    pz.add_plz(lex.data);
    getlex();
    Code_block();
}

void Function_declarations() {
    Name();
    if (lex.get_type() == "(") {
        pz.add_op(lex.data);
        getlex();
        Declaring_arguments();
        if (lex.get_type() == ")") {
            pz.add_op(lex.data);
            getlex();
            if (lex.get_type() == "type") {
                pz.add_plz(lex.data);
                getlex();
                Description_of_functions();
                if (lex.get_type() == "}") {
                    getlex();
                    return;
                } else {
                    throw "Didn't find } in Function_declarations";
                }
            } else {
                throw "Didn't find type in Function_declarations";
            }
        } else {
            throw "Didn't find ) in Function_declarations";
        }
    } else {
        throw "Didn't find ( in Function_declarations";
    }
}

void Description_of_functions() {
    if (lex.get_type() == "{") {
        Code_block();
    } else {
        throw "Didn't find { in Description_of_functions";
    }
}

void Type() {
    if (lex.get_type() == "type") {
        pz.add_plz(lex.data);
        getlex();
        return;
    } else {
        throw "Didn't find type in Type";
    }
}

void Declaring_variables() {
    if (lex.get_type() == "type") {
        pz.add_plz(lex.data);
        getlex();
        Name();
        while (lex.get_type() == ",") {
            pz.add_op(lex.data);
            getlex();
            Name();
        }
    } else {
        throw "Didn't find type in Declaring_variables";
    }
    if (lex.get_type() != ";") {
        throw "Didn't find ; in Declaring_variables";
    }
    pz.add_op(lex.data);
    getlex();
}

void Declaring_arguments() {
    Declaring_argument();
    while (lex.get_type() == ",") {
        pz.add_op(lex.data);
        getlex();
        Declaring_argument();
    }
}

void Declaring_argument() {
    Type();
    Name();
    if (lex.get_type() == "=") {
        pz.add_op(lex.data);
        getlex();
        exp0();
    }
}

void Name() {
    if (lex.get_type() == "name") {
        pz.add_plz(lex.data);
        getlex();
        return;
    } else {
        throw "Didn't find name";
    }
}

void Literal() {
    if (lex.get_type() == "'") {
        getlex();
        getlex();
    }
    if (lex.get_type() == "name" ||
    lex.get_type() == "number" ||
    lex.get_type() == "double" || lex.get_type() == "literal" || lex.get_type() == "'") {
        pz.add_plz(lex.data);
        getlex();
        return;
    } else {
        throw "Didn't find literal";
    }
}

void Code_block() {
    if (lex.get_type() != "{") {
        throw "Didn't find { in Code_block";
    }
    getlex();
    int cnt = 1;
    while (cnt--) {
        if (lex.get_type() == "return") {
            pz.add_plz(lex.data);
            getlex();
            Exp_main();
            ++cnt;
        } else if (Keyword()) {
            cnt++;
            if (lex.get_type() == "between") {
                Between();
                continue;
            }
            if (lex.get_type() == "while") {
                While();
                continue;
            }
            if (lex.get_type() == "for") {
                For();
                continue;
            }
            if (lex.get_type() == "if") {
                If();
                continue;
            }
            if (lex.get_type() == "switch") {
                Switch();
                continue;
            }
        } else if (lex.get_type() == "type") {
            Declaring_variables();
            ++cnt;
        } else {
            if (lex.get_type() != "}") {
                Exp_main();
                cnt++;
            } else {
                return;
            }
        }
    }
}

bool Keyword() {
    if (lex.get_type() == "between" ||
    lex.get_type() == "while" ||
    lex.get_type() == "for" ||
    lex.get_type() == "if" ||
    lex.get_type() == "switch") {
        return true;
    } else {
        return false;
    }
}

void Exp_main() {
    exp0();
    if (lex.get_type() != ";") {
        throw "Didn't find ; in Exp_main";
    }
    pz.add_op(lex.data);
    getlex();
}

void While() {
    if (lex.get_type() == "while") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "(") {
            pz.add_op(lex.data);
            getlex();
            exp0();
            if (lex.get_type() == ")") {
                pz.add_op(lex.data);
                getlex();
                if (lex.get_type() == "{") {
                    Code_block();
                    if (lex.get_type() == "}") {
                        getlex();
                        return;
                    } else {
                        throw "Didn't find } in While";
                    }
                } else {
                    throw "Didn't find { in While";
                }
            } else {
                throw "Didn't find ) in While";
            }
        } else {
            throw "Didn't find ( in While";
        }
    } else {
        throw "Didn't find while in While";
    }
}

void For() {
    if (lex.get_type() == "for") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "(") {
            pz.add_op(lex.data);
            getlex();
            Declaring_argument();
            if (lex.get_type() == ";") {
                pz.add_op(lex.data);
                getlex();
                Exp_main();
                exp0();
                if (lex.get_type() == ")") {
                    pz.add_op(lex.data);
                    getlex();
                    if (lex.get_type() == "{") {
                        Code_block();
                        if (lex.get_type() == "}") {
                            getlex();
                            return;
                        } else {
                            throw "Didn't find } in for";
                        }
                    } else {
                        throw "Didn't find { in for";
                    }
                } else {
                    throw "Didn't find ) in for";
                }
            } else {
                throw "Didn't find ; in for";
            }
        } else {
            throw "Didn't find ( in for";
        }
    } else {
        throw "Didn't find for in for";
    }
}

void If() {
    if (lex.get_type() == "if") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "(") {
            pz.add_op(lex.data);
            getlex();
            exp0();
            if (lex.get_type() == ")") {
                pz.add_op(lex.data);
                getlex();
                if (lex.get_type() == "{") {
                    Code_block();
                    if (lex.get_type() == "}") {
                        getlex();
                        Else();
                        return;
                    } else {
                         throw "Didn't find } in if";
                    }
                } else {
                    throw "Didn't find { in if";
                }
            } else {
                throw "Didn't find ) in if";
            }
        } else {
            throw "Didn't find ( in if";
        }
    } else {
        throw "Didn't find if in if";
    }
}

void Else() {
    if (lex.get_type() == "else") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "{") {
            getlex();
            Exp_main();
            if (lex.get_type() == "}") {
                getlex();
                return;
            } else {
                throw "Didn't find } in else";
            }
        } else {
            throw "Didn't find { in else";
        }
    }
}

void Switch() {
    if (lex.get_type() == "switch") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "(") {
            pz.add_op(lex.data);
            getlex();
            exp0();
            if (lex.get_type() == ")") {
                pz.add_op(lex.data);
                getlex();
                if (lex.get_type() == "{") {
                    getlex();
                    while (lex.get_type() == "case") {
                        Case();
                    }
                    if (lex.get_type() == "}") {
                        getlex();
                    } else {
                        throw "Didn't find } in swich";
                    }
                } else {
                    throw "Didn't find { in swich";
                }
            } else {
                throw "Didn't find ) in swich";
            }
        } else {
            throw "Didn't find ( in swich";
        }
    } else {
        throw "Didn't find swich in swich";
    }
}

void Case() {
    if (lex.get_type() == "case") {
        pz.add_plz(lex.data);
        getlex();
        if (lex.get_type() == "(") {
            pz.add_op(lex.data);
            getlex();
            exp0();
            if (lex.get_type() == ")") {
                pz.add_op(lex.data);
                getlex();
                if (lex.get_type() == "{") {
                    Code_block();
                    if (lex.get_type() == "}") {
                        getlex();
                        return;
                    } else {
                        throw "Didn't find } in case";
                    }
                } else {
                    throw "Didn't find { in case";
                }
            } else {
                throw "Didn't find ) in case";
            }
        } else {
            throw "Didn't find ( in case";
        }
    } else {
        throw "Didn't find case in case";
    }
}

void Call_func() {
    Name();
    if (lex.get_type() == "(") {
        pz.add_op(lex.data);
        getlex();
        Argument_enumerationn();
        if (lex.get_type() == ")") {
            pz.add_op(lex.data);
            getlex();
        } else {
            throw "Didn't find ) in Call_func";
        }
    } else {
        throw "Didn't find ( in Call_func";
    }
}

void Argument_enumerationn() {
    exp0();
    while (lex.get_type() == ",") {
        pz.add_op(lex.data);
        getlex();
        exp0();
    }
}

void Between() {}
