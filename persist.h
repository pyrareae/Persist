/*
 * persist.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Jake Vandereay
 * 	Modified 3/6/19
 * 		Author: Jefferson Lee
 *
 *  A persistent storage template using eeprom
 * 	modified to switch to the FlashStorage library on non-avrs
 */

#ifndef PERSIST_H_
#define PERSIST_H_
#ifndef __AVR__
#include <FlashStorage.h>
#else
#include <avr/eeprom.h>

template <class T> class Persist { //wrapper for EEMEM variables
public:
	Persist(T *variable_ptr) : val(value) { //pointer to eemem variable
		store = variable_ptr;
		eeprom_read_block(&value, store, sizeof(value));
	}
	T read() {//get stored value
		return value;
	}
	T write (T value) {//set value
		this->value = value;
		eeprom_write_block(&value, store, sizeof(value));
		return value;
	}
	T operator=(T value) { //use the = as an accessor
		write(value);
		return value;
	}
	const T &val; //constant public reference to value, to prevent changing value directly.
private:
	T *store; //pointer to eemem variable
	T value; //ram copy of variable
};


//macro for persistent variable creation. Creates EEMEM var and wrapper object.
#define FlashStorage(name, type) \
	type EEMEM __##name; /*create eemem variable*/ \
	Persist<type> name (&__##name); /*create interface object*/

#endif
#endif /* PERSIST_H_ */