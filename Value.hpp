#include <tuple>
#include <functional>
#include <iostream>

class Value {
public:
   Value() = delete;
   Value(double data, char op = '0') {
    this -> data = data;
    this -> _op = op;
   }

   //accessor methods
   auto item() { return this -> data; }
   auto backward() { return _backward(); }
   auto grad() { return _grad; }

   //add operation
   Value operator+(Value rhs) { 
    auto out = std::move(Value(this -> data + rhs.item(), '+')); 

    // local derivative for add operation
    auto temp = [&out, &rhs, this](){
        this -> _grad = 1.0 * out._grad;
        rhs._grad = 1.0 * out._grad;
    };
    out._backward = temp;
    return std::move(out);
    }

   // multiplication operation
   Value operator*(Value rhs) { 
    auto out = std::move(Value(this -> data * rhs.item(), '*')); 
    auto temp = [&out, &rhs, this](){
       this -> _grad = rhs.data * out._grad; 
       rhs._grad = this -> _grad * out._grad;
    };
    out._backward = temp;

    return std::move(out);
   }   


   friend std::ostream& operator<<(std::ostream& os, Value& v) {
    return os << "Value(data=" << v.item() << ")";
    }
private:
   double data = 0.0;
   double _grad = 0.0;
   char _op = '0';
    std::function<void(void)> _backward;

   std::tuple<Value, Value>* _children;
};
