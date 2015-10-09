/*
 * persist.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Jake Vandereay
 *
 *  A persistent storage template using eeprom
 */

#ifndef PERSIST_H_
#define PERSIST_H_

#include <avr/eeprom.h>

template <class T> class Persist{ //wrapper for EEMEM variables
public:
	Persist(T *variable_ptr) : val(value) { //pointer to eemem variable
		store = variable_ptr;
		eeprom_read_block(&value, store, sizeof(value));
	}
	T get() {//get stored value
		return value;
	}
	T set (T value) {//set value
		this->value = value;
		eeprom_write_block(&value, store, sizeof(value));
	}
	T operator=(T value) { //use the = as an accessor
		set(value);
	}
	const T &val; //constant public reference to value, to prevent changing value directly.
private:
	T *store; //pointer to eemem variable
	T value; //ram copy of variable
};


//macro for persistent variable creation. Creates EEMEM var and wrapper object.
#define PERSIST(type, name) \
	type EEMEM __name; /*create eemem variable*/ \
	Persist<type> name(&__name); /*create interface object*/


#endif /* PERSIST_H_ */
