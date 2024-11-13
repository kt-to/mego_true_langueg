//
// Created by Дмитрий Фоминых on 13.11.2024.
//
#include "main.cpp"
#include "Lexer.h"
#include "lexer_exp.h"

void Program() {
    int cnt = 1;
    while (cnt--) {
        if (lex.get_type() == "name") {
            Function_declarations();
            cnt++;
        } else {
            if (lex.get_type() == "type") {
                Declaring_variable();
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
    getlex();
    Code_block();
}

void Function_declarations() {
    Name();
    if (lex.get_type() == "(") {
        Declaring_arguments();
        if (lex.get_type() == ")") {
            getlex();
            if (lex.get_type() == "type") {
                getlex();
                if (lex.get_type() == "{") {
                    getlex();
                    Description_of_functions();
                    if (lex.get_type() == "}") {
                        if (lex.get_type() == ";") {
                            getlex();
                            return;
                        } else {
                            throw "; not find";
                        }
                    } else {
                        throw "} not find";
                    }
                } else {
                    throw "{ not find";
                }
            } else {
                throw "type not find";
            }
        } else {
            throw ") not find";
        }
    } else {
        throw "( not find";
    }
}

void Description_of_functions() {
    if (lex.get_type() == "{") {
        Code_block();
        if (lex.get_type() == "return") {
            getlex();
            Literal();
            if (lex.get_type() == "}") {
                getlex();
                return;
            } else {
                throw "Didn't find { in Description_of_functions";
            }
        } else {
            throw "Didn't find return in Description_of_functions";
        }
    } else {
        throw "Didn't find } in Description_of_functions";
    }
}

void Type() {
    if (lex.get_type() == "type") {
        getlex();
        return;
    } else {
        throw "Didn't find type in Type";
    }
}

void Declaring_variables() {
    if (lex.get_type() == "type") {
        getlex();
        Name();
        while (lex.get_type() == ",") {
            getlex();
            Name();
        }
    } else {
        throw "Didn't find type in Declaring_variables";
    }
}

void Declaring_arguments() {
    Declaring_argument();
    while (lex.get_type() == ",") {
        getlex();
        Declaring_argument();
    }
}

void Declaring_argument() {
    Type();
    Name();
    if (lex.get_type() == "=") {
        getlex();
        Literal();
    }
}

void Declaring_variable() {
    Type();
    Name();
}

void Name() {
    if (lex.get_type() == "name") {
        getlex();
        return;
    } else {
        throw "Didn't find name";
    }
}

void Literal() {
    if (lex.get_type() == "name" ||
    lex.get_type() == "number" ||
    lex.get_type() == "float") {
        getlex();
        return;
    } else {
        throw "Didn't find literal";
    }
}

void Code_block() {
    int cnt = 1;
    while (cnt--) {
        if (Keyword()) {
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
        return true;
    }
}

void Exp_main() {
    exp1();
}

void While() {
    if (lex.get_type() == "while") {
        getlex();
        if (lex.get_type() == "(") {
            exp1();
            if (lex.get_type() == ")") {
                getlex();
                if (lex.get_type() == "{") {
                    Code_block();
                    if (lex.get_type() == "}") {
                        getlex();
                        if (lex.get_type() == ";") {
                            getlex();
                            return;
                        } else {
                            throw "Didn't find ; in While";
                        }
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


