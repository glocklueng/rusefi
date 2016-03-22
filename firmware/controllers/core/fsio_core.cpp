/**
 * @file fsio_core.cpp
 * @brief core FSUI handling logic
 *
 * Here we parse and evaluate logical expressions in
 * http://en.wikipedia.org/wiki/Reverse_Polish_notation
 *
 * Once the expressions are parsed on startup (that's a heavy operation),
 * evaluating those is relatively efficient.
 *
 *
 * @date Oct 3, 2014
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#include "main.h"

#if EFI_FSIO || defined(__DOXYGEN__)

#include "fsio_core.h"
#include "fsio_impl.h"

LENameOrdinalPair * LE_FIRST = NULL;

/**
 * the main point of these static fields is that their constructor would register
 * them in the magic list of operator name/ordinal pairs
 */
static LENameOrdinalPair leAnd(LE_OPERATOR_AND, "and");
static LENameOrdinalPair leAnd2(LE_OPERATOR_AND, "&");
static LENameOrdinalPair leOr(LE_OPERATOR_OR, "or");
static LENameOrdinalPair leOr2(LE_OPERATOR_OR, "|");
static LENameOrdinalPair leNot(LE_OPERATOR_NOT, "not");

static LENameOrdinalPair leAdd(LE_OPERATOR_ADDITION, "+");
static LENameOrdinalPair leSub(LE_OPERATOR_SUBTRACTION, "-");
static LENameOrdinalPair leMul(LE_OPERATOR_MULTIPLICATION, "*");
static LENameOrdinalPair leDiv(LE_OPERATOR_DIVISION, "/");

static LENameOrdinalPair leMore(LE_OPERATOR_MORE, ">");
static LENameOrdinalPair leMoreOrEqual(LE_OPERATOR_MORE_OR_EQUAL, ">=");

static LENameOrdinalPair leLess(LE_OPERATOR_LESS, "<");
static LENameOrdinalPair leLessOrEquals(LE_OPERATOR_LESS_OR_EQUAL, "<=");

static LENameOrdinalPair leMax(LE_METHOD_MAX, "max");
static LENameOrdinalPair leMin(LE_METHOD_MIN, "min");
static LENameOrdinalPair leIf(LE_METHOD_IF, "if");
static LENameOrdinalPair leSelf(LE_METHOD_SELF, "self");

LENameOrdinalPair::LENameOrdinalPair(le_action_e action, const char *name) {
	this->action = action;
	this->name = name;
	this->next = LE_FIRST;
	LE_FIRST = this;
}

LEElement::LEElement() {
	action = LE_UNDEFINED;
	next = NULL;
	fValue = NAN;
	iValue = 0;
}

//void LEElement::init(le_action_e action, int iValue) {
//	this->action = action;
//	this->iValue = iValue;
//}

void LEElement::init(le_action_e action) {
	this->action = action;
}

void LEElement::init(le_action_e action, float fValue) {
	this->action = action;
	this->fValue = fValue;
}

LECalculator::LECalculator() {
	reset();
}

void LECalculator::reset() {
	first = NULL;
	stack.reset();
	currentCalculationLogPosition = 0;
}

void LECalculator::reset(LEElement *element) {
	reset();
	add(element);
}

void LECalculator::add(LEElement *element) {
	if (first == NULL) {
		first = element;
	} else {
		LEElement *last = first;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = element;
	}
}

static bool float2bool(float v) {
	return v != 0;
}

float LECalculator::pop(le_action_e action) {
	if (stack.size() == 0) {
		warning(OBD_PCM_Processor_Fault, "empty stack for %d", action);
		return NAN;
	}
	return stack.pop();
}

void LECalculator::push(le_action_e action, float value) {
	stack.push(value);
	if (currentCalculationLogPosition < MAX_CALC_LOG) {
		calcLogAction[currentCalculationLogPosition] = action;
		calcLogValue[currentCalculationLogPosition] = value;
		currentCalculationLogPosition++;
	}
}

/**
 * @return true in case of error, false otherwise
 */
bool LECalculator::processElement(Engine *engine, LEElement *element) {
#if EFI_PROD_CODE || defined(__DOXYGEN__)
	efiAssert(getRemainingStack(chThdSelf()) > 64, "FSIO logic", false);
#endif
	switch (element->action) {

	case LE_NUMERIC_VALUE:
		push(element->action, element->fValue);
		break;
	case LE_OPERATOR_AND: {
		float v1 = pop(LE_OPERATOR_AND);
		float v2 = pop(LE_OPERATOR_AND);

		push(element->action, float2bool(v1) && float2bool(v2));
	}
		break;
	case LE_OPERATOR_OR: {
		float v1 = pop(LE_OPERATOR_OR);
		float v2 = pop(LE_OPERATOR_OR);

		push(element->action, float2bool(v1) || float2bool(v2));
	}
		break;
	case LE_OPERATOR_LESS: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_LESS);
		float v1 = pop(LE_OPERATOR_LESS);

		push(element->action, v1 < v2);
	}
		break;
	case LE_OPERATOR_NOT: {
		float v = pop(LE_OPERATOR_NOT);
		push(element->action, !float2bool(v));
	}
		break;
	case LE_OPERATOR_MORE: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE);
		float v1 = pop(LE_OPERATOR_MORE);

		push(element->action, v1 > v2);
	}
		break;
	case LE_OPERATOR_ADDITION: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE);
		float v1 = pop(LE_OPERATOR_MORE);

		push(element->action, v1 + v2);
	}
		break;
	case LE_OPERATOR_SUBTRACTION: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE);
		float v1 = pop(LE_OPERATOR_MORE);

		push(element->action, v1 - v2);
	}
		break;
	case LE_OPERATOR_MULTIPLICATION: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE);
		float v1 = pop(LE_OPERATOR_MORE);

		push(element->action, v1 * v2);
	}
		break;
	case LE_OPERATOR_DIVISION: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE);
		float v1 = pop(LE_OPERATOR_MORE);

		push(element->action, v1 / v2);
	}
		break;
	case LE_OPERATOR_LESS_OR_EQUAL: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_LESS_OR_EQUAL);
		float v1 = pop(LE_OPERATOR_LESS_OR_EQUAL);

		push(element->action, v1 <= v2);
	}
		break;
	case LE_OPERATOR_MORE_OR_EQUAL: {
		// elements on stack are in reverse order
		float v2 = pop(LE_OPERATOR_MORE_OR_EQUAL);
		float v1 = pop(LE_OPERATOR_MORE_OR_EQUAL);

		push(element->action, v1 >= v2);
	}
		break;
	case LE_METHOD_IF: {
		// elements on stack are in reverse order
		float vFalse = pop(LE_METHOD_IF);
		float vTrue = pop(LE_METHOD_IF);
		float vCond = pop(LE_METHOD_IF);
		push(element->action, vCond != 0 ? vTrue : vFalse);
	}
		break;
	case LE_METHOD_MAX: {
		float v2 = pop(LE_METHOD_MAX);
		float v1 = pop(LE_METHOD_MAX);
		push(element->action, maxF(v1, v2));
	}
		break;
	case LE_METHOD_MIN: {
		float v2 = pop(LE_METHOD_MIN);
		float v1 = pop(LE_METHOD_MIN);
		push(element->action, minF(v1, v2));
	}
		break;
	case LE_METHOD_FSIO_SETTING: {
		float i = pop(LE_METHOD_FSIO_SETTING);
		int index = (int) i;
		if (index >= 0 && index < LE_COMMAND_COUNT) {
			push(element->action, engine->engineConfiguration->bc.fsio_setting[index]);
		} else {
			push(element->action, NAN);
		}
	}
		break;
	case LE_METHOD_FSIO_TABLE: {
		float i = pop(LE_METHOD_FSIO_TABLE);
		float xValue = pop(LE_METHOD_FSIO_TABLE);
		float yValue = pop(LE_METHOD_FSIO_TABLE);
		int index = (int) i;
		if (index < 0 || index > 2) {
			push(element->action, NAN);
		} else {

		}


	}
		break;
	case LE_METHOD_KNOCK:
		push(element->action, engine->knockCount);
		break;
	case LE_UNDEFINED:
		warning(OBD_PCM_Processor_Fault, "FSIO undefined action");
		return true;
	default:
		push(element->action, getLEValue(engine, &stack, element->action));
	}
	return false;
}

float LECalculator::getValue2(float selfValue, LEElement *fistElementInList, Engine *engine) {
	reset(fistElementInList);
	return getValue(selfValue, engine);
}

float LECalculator::getValue(float selfValue, Engine *engine) {
	if (first == NULL) {
		warning(OBD_PCM_Processor_Fault, "no FSIO code");
		return NAN;
	}
	LEElement *element = first;

	stack.reset();

	int counter = 0;
	while (element != NULL) {
		efiAssert(counter < 200, "FSIOcount", NAN); // just in case

		if (element->action == LE_METHOD_SELF) {
			push(element->action, selfValue);
		} else {
			bool isError = processElement(engine, element);
			if (isError) {
				// error already reported
				return NAN;
			}
		}
		element = element->next;
		counter++;
	}
	if (stack.size() != 1) {
		warning(OBD_PCM_Processor_Fault, "unexpected FSIO stack size: %d", stack.size());
		return NAN;
	}
	return stack.pop();
}

LEElementPool::LEElementPool(LEElement *pool, int size) {
	this->pool = pool;
	this->size = size;
	reset();
}

void LEElementPool::reset() {
	index = 0;
}

int LEElementPool::getSize() {
	return index;
}

LEElement *LEElementPool::next() {
	if (index >= size) {
		// todo: this should not be a fatal error, just an error
		firmwareError("LE_ELEMENT_POOL_SIZE overflow");
		return NULL;
	}
	return &pool[index++];
}

bool isNumeric(const char* line) {
	return line[0] >= '0' && line[0] <= '9';
}

/**
 * @return pointer at the position after the consumed token, null if no token consumed
 */
const char *getNextToken(const char *line, char *buffer, const int bufferSize) {
	while (line[0] != 0 && line[0] == ' ') {
		line++;
	}
	if (line[0] == 0) {
		return NULL;
	}
	int tokenLen = indexOf(line, ' ');
	if (tokenLen == -1) {
		// no space - the whole remaining line is the token
		tokenLen = strlen(line);
	}
	efiAssert(tokenLen < bufferSize, "token overflow", NULL);
	strncpy(buffer, line, tokenLen);
	buffer[tokenLen] = 0;
	line += tokenLen;
	return line;
}

le_action_e parseAction(const char * line) {
	LENameOrdinalPair *pair = LE_FIRST;
	while (pair != NULL) {
		if (strEqualCaseInsensitive(pair->name, line)) {
			return pair->action;
		}
		pair = pair->next;
	}
	return LE_UNDEFINED;
}

static char parsingBuffer[64];

LEElement *LEElementPool::parseExpression(const char * line) {

	LEElement *first = NULL;
	LEElement *last = NULL;

	while (true) {
		line = getNextToken(line, parsingBuffer, sizeof(parsingBuffer));

		if (line == NULL) {
			/**
			 * No more tokens in this line
			 */
			return first;
		}

		LEElement *n = next();
		if (n == NULL) {
			return first;
		}

		if (isNumeric(parsingBuffer)) {
			n->init(LE_NUMERIC_VALUE, atoff(parsingBuffer));
		} else {
			le_action_e action = parseAction(parsingBuffer);
			if (action == LE_UNDEFINED) {
				/**
				 * Cannot recognize token
				 */
				warning((obd_code_e) 0, "unrecognized [%s]", parsingBuffer);
				return NULL;
			}
			n->init(action);
		}

		if (first == NULL) {
			first = n;
			last = n;
		} else {
			last->next = n;
			last = last->next;
		}
	}
	return first;
}

#endif /* EFI_FSIO */
