#ifndef AST_FLAG
#define AST_FLAG
#include <string>
#include <memory>
#include <string>

static int jumpLabel = 0;


//-----------------
class node{
public:
    virtual std::string printCode() {
        return "printCode";
    }
    virtual std::string getVarDec() {
        return "";
    }
    virtual ~node() = default;
    virtual std::string getTypeName() const = 0;  
    //virtual std::string printCode();
};
//-----------------
class expression_node :public node{
    std::string getTypeName() const override {
        return "expression_node";
    }
};
class then_node :public node{
    std::string getTypeName() const override {
        return "then_node";
    }
};
class term_node :public expression_node {
    std::string getTypeName() const override {
        return "term_node";
    }
};
enum class binary_operator {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LESS_THAN,
    EQUAL
};
class binary_expression_node :public expression_node {
    public:
    binary_expression_node(binary_operator op): _op(op) {}
    //binary_expression_node(term_node left, term_node right, binary_operator op) : _left(left), _right(right), _op(op) {}
    std::string getTypeName() const override {
        return "binary_expression_node";
    }
    void set_left(std::unique_ptr<term_node> left) {
        _left = std::move(left);
    }
    void set_right(std::unique_ptr<term_node> right) {
        _right = std::move(right);
    }
    std::string printCode() override {
        std::string result;
        result = _left->printCode() + "\n" + "push rax\n";
        result += _right->printCode() + "\n" + "pop rbx\n";
        switch (_op) {
            case binary_operator::PLUS:
                result += "add rax, rbx";
                break;
            case binary_operator::MINUS:
                result += "sub rax, rbx";
                break;
            case binary_operator::MULTIPLY:
                result += "mul rbx";
                break;
            case binary_operator::DIVIDE:
                result += "div rbx";
                break;
            case binary_operator::LESS_THAN:
                result += "cmp rax, rbx\n";
                break;
            case binary_operator::EQUAL:
                result += "cmp rax, rbx\n";
                break;
        }
        return result;
    }
    binary_operator get_operator() const {
        return _op;
    }
    private:
    std::unique_ptr<term_node> _left;
    std::unique_ptr<term_node> _right;
    binary_operator _op;
};
//----------------
class label_node :public node {
    public:
    label_node(std::string value) : _value(value) {}
    std::string printCode() override {
        return _value ;
    }
    std::string getTypeName() const override {
        return "label_node";
    }
    private:
    std::string _value;
};
class condition_node :public node{
    public:
    condition_node(std::unique_ptr<binary_expression_node> expre) : _expression(std::move(expre)) {}
    std::string printCode() override {
        std::string result = _expression->printCode();
        result += "\n";
        _label = "iflabel" + std::to_string(jumpLabel++);
        
        switch (_expression->get_operator())
        {
            case binary_operator::LESS_THAN:
            result += "jge " + _label + "\n";
            break;
        case binary_operator::EQUAL:
            result += "jne " + _label + "\n";
            break;
        
        default:
            break;
        }
        return result;
    }
    std::string getTypeName() const override {
        return "condition_node";
    }
    std::string getLabel() {
        return _label;
    }
    private:
    std::string _label;
    std::unique_ptr<binary_expression_node> _expression;
};





class input_node :public term_node {
    public:
    input_node() {}
    std::string printCode() override {
        return std::string("; Read input \ncall read_int\nmov [n], rax\n\n");
    
    }
    std::string getTypeName() const override {
        return "input_node";
    }

};

class int_node :public term_node {
    public:
    int_node(std::string value) : _value(value) {}
    std::string printCode() override {
        return "mov rax, " + _value;
    }
    std::string getTypeName() const override {
        return "int_node";
    }
    private:
    std::string _value;
};


class var_node :public term_node {
    public:
    var_node(std::string value) : _value(value) {}

    std::string printCode() override {
        return "mov rax , [" + _value + "]";
    }
    std::string getVar(){
        return _value;
    }
    std::string getTypeName() const override {
        return "var_node";
    }
    private:
    std::string _value;
};



//-----------------

class instraction_node :public node{
    
    std::string getTypeName() const override {
        return "instraction_node";
    }
};
class assign_node :public instraction_node {
    public:
    std::string getTypeName() const override {
        return "assign_node";
    } 
    std::string printCode() override{
        return _value->printCode() + "\n" + "mov [" +_source->getVar() + "] , rax\n";
    }
    void set_source(std::unique_ptr<var_node> source) {
        _source = std::move(source);
    }
    std::string getVarDec() override {
        return  _source->getVar();
    }
    void set_value(std::unique_ptr<expression_node> value) {
        _value = std::move(value);
    }
    //assign_node(term_node source, term_node value) : _source(source), _value(value) {}
    private:
    std::unique_ptr<var_node> _source;
    std::unique_ptr<expression_node> _value;

};

class if_node :public instraction_node {
    public:
    if_node(){}
    std::string getTypeName() const override {
        return "if_node";
    }
    std::string printCode() override {
        return _condition->printCode() + "\n" + _then->printCode() + "\n" + _condition->getLabel() + ":";
    }
    void set_condition(std::unique_ptr<condition_node> condition) {
        _condition = std::move(condition);
    }
    void set_then(std::unique_ptr<instraction_node> then) {
        _then = std::move(then);
    }
    //if_node(condition_node condition, instraction_node*  then) : _condition(condition), _then(then) {}
    private:
    std::unique_ptr<condition_node> _condition;
    std::unique_ptr<instraction_node> _then;

};

class goto_node : public instraction_node {
    public:
    goto_node(){}
    std::string printCode() override {
        return "jmp " + _label->printCode().erase(_label->printCode().size()-1);
    }
    std::string getTypeName() const override {
        return "goto_node";
    }
    void set_label(std::unique_ptr<label_node> label){
        _label = std::move(label);
    }
    //goto_node(label_node label) : _label(label) {}
    private:
    std::unique_ptr<label_node> _label;
    
};
class output_node : public instraction_node{
    public:
    output_node(){}
    std::string printCode() override {
        return _value->printCode() + "\n" + "call print_int_ln\n";
    }
    void set_value(std::unique_ptr<term_node> value) {
        _value = std::move(value);
    }
    //output_node(term_node value) : _value(value) {}
    std::string getTypeName() const override {
        return "output_node";
    }
    private:
    std::unique_ptr<term_node> _value;
};




#endif