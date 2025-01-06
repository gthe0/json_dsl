#ifndef JSONSETOPERATIONS_HPP
#define JSONSETOPERATIONS_HPP

#include <JsonVar.hpp>

namespace jsonlang
{

class SetOperator {
public:
	virtual JsonVar& op(JsonVar& var) = 0;
};

class AssignOperator : public SetOperator{
public:
	virtual JsonVar& op(JsonVar& var) { return var; }
};


class AppendOperator : public SetOperator {
public:
	virtual JsonVar& op(JsonVar& var) { return var; }
};

} // namespace jsonlang

#endif //! JSONSETOPERATIONS_HPP

