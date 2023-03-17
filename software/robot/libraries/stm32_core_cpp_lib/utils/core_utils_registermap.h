/*
 * core_utils_registermap.h
 *
 *  Created on: 26 Feb 2023
 *      Author: Dustin Lehmann
 */

#ifndef UTILS_CORE_UTILS_REGISTERMAP_H_
#define UTILS_CORE_UTILS_REGISTERMAP_H_

typedef enum register_entry_rw_t {
	REGISTER_ENTRY_READ = 0,
	REGISTER_ENTRY_WRITE = 1,
	REGISTER_ENTRY_READWRITE = 2
} register_entry_rw_t;

typedef enum register_entry_type {
	REGISTER_ENTRY_DATA = 1, REGISTER_ENTRY_FUNCTION = 2,
} register_entry_type;

/* ============================================================ */
class RegisterEntry {
public:
	virtual void write(void *value) {
		;
	}
	virtual void write(uint8_t *data) {
		;
	}
	virtual uint8_t readBytes(uint8_t *data) {
		return 0;
	}
	virtual uint8_t getSize() {
		return 0;;
	}
	virtual uint8_t getInputSize() {
		return 0;
	}

	virtual uint8_t getOutputSize() {
		return 0;
	}

	virtual void execute() {
	}

	virtual uint8_t execute(uint8_t *input, uint8_t *output) {
		return 0;
	}

	virtual register_entry_type getType() = 0;
	virtual register_entry_rw_t getReadWriteSetting() = 0;
	register_entry_type type;
	register_entry_rw_t rw;
};

/* ============================================================ */
class RegisterMap {
public:
	virtual void write(uint16_t address, void *data) {
	}
	virtual void write(uint16_t address, uint8_t *data) {
	}
	virtual void addEntry(uint16_t address, RegisterEntry *entry) {

	}
	virtual bool hasEntry(uint16_t address) {
		return false;
	}
	virtual uint8_t read(uint16_t address, uint8_t *data) {
		return 0;
	}
	virtual uint8_t getSize(uint16_t address) {
		return 0;
	}
	virtual register_entry_type getType(uint16_t address) = 0;
	virtual register_entry_rw_t getReadWriteSetting(uint16_t address) = 0;

	/* -------------------------------------------------- */
	virtual uint8_t execute(uint16_t address, uint8_t *input, uint8_t *output) {
		return 0;
	}
	/* -------------------------------------------------- */
	virtual uint8_t execute(uint16_t address) {
		return 0;
	}

	uint16_t address;
	RegisterEntry *entries;
};

/* ============================================================ */
template<int size>
class core_utils_RegisterMap: public RegisterMap {
public:
	core_utils_RegisterMap<size>(uint16_t address){
		this->address = address;
	}

	void write(uint16_t address, void *data) {
		if (this->entries[address] != NULL
				&& this->entries[address]->getType() == REGISTER_ENTRY_DATA) {
			this->entries[address]->write(data);
		}
	}
	/* -------------------------------------------------- */
	void write(uint16_t address, uint8_t *data) {
		if (this->entries[address] != NULL
				&& this->entries[address]->getType() == REGISTER_ENTRY_DATA) {
			this->entries[address]->write(data);
		}
	}
	/* -------------------------------------------------- */
	uint8_t read(uint16_t address, uint8_t *data) {
		if (this->entries[address] != NULL
				&& this->entries[address]->getType() == REGISTER_ENTRY_DATA) {
			return this->entries[address]->readBytes(data);
		}
		return 0;
	}
	/* -------------------------------------------------- */
	uint8_t execute(uint16_t address, uint8_t *input, uint8_t *output) {
		if (this->entries[address] != NULL
				&& this->entries[address]->getType()
						== REGISTER_ENTRY_FUNCTION) {
			return this->entries[address]->execute(input, output);
		}
		return 0;
	}
	/* -------------------------------------------------- */
	uint8_t execute(uint16_t address) {
		if (this->entries[address] != NULL
				&& this->entries[address]->getType()
						== REGISTER_ENTRY_FUNCTION) {
			if (this->entries[address]->getInputSize() == 0
					&& this->entries[address]->getOutputSize() == 0) {
				this->entries[address]->execute();
			}
		}
		return 0;
	}
	/* -------------------------------------------------- */
	void addEntry(uint16_t address, RegisterEntry *entry) {
		this->entries[address] = entry;
	}
	/* -------------------------------------------------- */
	bool hasEntry(uint16_t address) {
		if (this->entries[address] != NULL) {
			return true;
		} else {
			return false;
		}
	}
	/* -------------------------------------------------- */
	uint8_t getSize(uint16_t address) {
		return this->entries[address]->getSize();
	}
	/* -------------------------------------------------- */

	register_entry_type getType(uint16_t address) {
		return this->entries[address]->getType();
	}
	register_entry_rw_t getReadWriteSetting(uint16_t address) {
		return this->entries[address]->getReadWriteSetting();
	}

	RegisterEntry *entries[size] = { 0 };
private:

};

/* ============================================================ */
template<typename T>
class core_utils_RegisterEntry: public RegisterEntry {
public:
	core_utils_RegisterEntry() {

	}
	/* -------------------------------------------------- */
	core_utils_RegisterEntry(uint16_t address) {
		this->address = address;
	}
	/* -------------------------------------------------- */
	core_utils_RegisterEntry(uint16_t address, RegisterMap *map, T *data,
			register_entry_rw_t rw) {
		this->set(address, map, data, rw);
	}
	/* -------------------------------------------------- */
	core_utils_RegisterEntry(uint16_t address, RegisterMap *map, T *data,
			register_entry_rw_t rw, Callback write_callback) {
		this->set(address, map, data, rw, write_callback);
	}

	/* -------------------------------------------------- */
	void set(RegisterMap *map, T *data, register_entry_rw_t rw) {
		this->data = data;
		map->addEntry(address, this);
		this->rw = rw;
	}

	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map, T *data,
			register_entry_rw_t rw) {
		this->address = address;
		this->data = data;
		map->addEntry(address, this);
		this->rw = rw;
	}
	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map, T *data,
			register_entry_rw_t rw, Callback write_function) {
		this->address = address;
		this->data = data;
		this->write_function = write_function;
		map->addEntry(address, this);
		this->rw = rw;
	}
	/* -------------------------------------------------- */
	void write(T value) {
		if (this->rw == REGISTER_ENTRY_READ) {
			return;
		}
		*(this->data) = value;
		this->write_function.call();
	}
	/* -------------------------------------------------- */
	void write(void *value) {
		if (this->rw == REGISTER_ENTRY_READ) {
			return;
		}
		T *value_typed = (T*) value;

		*(this->data) = *value_typed;
		this->write_function.call();
	}
	/* -------------------------------------------------- */
	void write(uint8_t *data) { // TODO: not good
		if (this->rw == REGISTER_ENTRY_READ) {
			return;
		}
		for (uint8_t i = 0; i < sizeof(T); i++) {
			this->data_union.data_bytes[i] = data[i];
		}
		this->write(this->data_union.data);
	}
	/* -------------------------------------------------- */
	uint8_t readBytes(uint8_t *data) {
		if (this->rw == REGISTER_ENTRY_WRITE) {
			return 0;
		}
		this->data_union.data = *(this->data);

		for (uint8_t i = 0; i < sizeof(T); i++) {
			data[i] = this->data_union.data_bytes[i];
		}
		return sizeof(T);
	}
	/* -------------------------------------------------- */
	T read() {
		if (this->rw == REGISTER_ENTRY_WRITE) {
			return;
		}
		return *(this->data);
	}

	/* -------------------------------------------------- */
	uint8_t getSize() {
		return sizeof(T);
	}
	/* -------------------------------------------------- */
	register_entry_type getType() {
		return REGISTER_ENTRY_DATA;
	}
	register_entry_rw_t getReadWriteSetting() {
		return this->rw;
	}

	/* -------------------------------------------------- */
	union data_union_t {
		uint8_t data_bytes[sizeof(T)];
		T data;
	} data_union;

	/* -------------------------------------------------- */
	register_entry_type type = REGISTER_ENTRY_DATA;
	uint16_t address;
	register_entry_rw_t rw;

private:
	T *data;
	Callback write_function = core_utils_Callback<void, void>();
};

/* ============================================================ */
template<typename output_t, typename input_t>
class core_utils_RegisterFunction: public RegisterEntry {
public:
	core_utils_RegisterFunction() {

	}

	core_utils_RegisterFunction(uint16_t address) {
		this->address = address;
	}

	/* -------------------------------------------------- */
	core_utils_RegisterFunction(uint16_t address, RegisterMap *map,
			core_utils_Callback<output_t, input_t> function) {
		this->set(address, map, function);
	}
	/* -------------------------------------------------- */
	void set(RegisterMap *map,
			core_utils_Callback<output_t, input_t> function) {
		this->function = function;
		map->addEntry(this->address, this);
	}
	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map,
			core_utils_Callback<output_t, input_t> function) {
		this->address = address;
		this->function = function;
		map->addEntry(this->address, this);
	}

	/* -------------------------------------------------- */
	output_t execute(uint8_t *data) {
		for (uint8_t i = 0; i < sizeof(input_t); i++) {
			this->input_data_union.data_bytes[i] = data[i];
		}
		return this->function.call(this->input_data_union.data);
	}

	/* -------------------------------------------------- */
	output_t execute(input_t argument) {
		if (this->function.registered) {
			return this->function.call(argument);
		}
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *input_buffer, uint8_t *output_buffer) {
		for (uint8_t i = 0; i < sizeof(input_t); i++) {
			this->input_data_union.data_bytes[i] = input_buffer[i];
		}
		output_t out = this->execute(this->input_data_union.data);

		uint8_t *data_ptr = (uint8_t*) &out;
		for (uint8_t i = 0; i < sizeof(output_t); i++) {
			output_buffer[i] = data_ptr[i];
		}

		return sizeof(output_t);
	}
	/* -------------------------------------------------- */
	uint8_t getSize() {
			return sizeof(input_t);
	}
	/* -------------------------------------------------- */
	uint8_t getInputSize() {
		return sizeof(input_t);
	}

	/* -------------------------------------------------- */
	uint8_t getOutputSize() {
		return sizeof(output_t);
	}
	/* -------------------------------------------------- */
	register_entry_type getType() {
		return REGISTER_ENTRY_FUNCTION;
	}
	/* -------------------------------------------------- */
	register_entry_rw_t getReadWriteSetting() {
		return REGISTER_ENTRY_READWRITE;
	}

	/* -------------------------------------------------- */
	union input_data_union_t {
		uint8_t data_bytes[sizeof(input_t)];
		input_t data;
	} input_data_union;

	register_entry_type type = REGISTER_ENTRY_FUNCTION;
	uint16_t address;
	core_utils_Callback<output_t, input_t> function;
};

/* ============================================================ */
template<typename input_t>
class core_utils_RegisterFunction<void, input_t> : public RegisterEntry {
public:
	core_utils_RegisterFunction() {

	}

	core_utils_RegisterFunction(uint16_t address) {
		this->address = address;
	}

	/* -------------------------------------------------- */
	core_utils_RegisterFunction(uint16_t address, RegisterMap *map,
			core_utils_Callback<void, input_t> function) {
		this->set(address, map, function);
	}
	/* -------------------------------------------------- */
	void set(RegisterMap *map, core_utils_Callback<void, input_t> function) {
		this->function = function;
		map->addEntry(this->address, this);
	}
	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map,
			core_utils_Callback<void, input_t> function) {
		this->address = address;
		this->function = function;
		map->addEntry(this->address, this);
	}

	/* -------------------------------------------------- */
	void execute(uint8_t *data) {
		for (uint8_t i = 0; i < sizeof(input_t); i++) {
			this->input_data_union.data_bytes[i] = data[i];
		}
		this->function.call(this->input_data_union.data);
	}

	/* -------------------------------------------------- */
	void execute(input_t argument) {
		if (this->function.registered) {
			this->function.call(argument);
		}
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *input_buffer, uint8_t *output_buffer) {
		for (uint8_t i = 0; i < sizeof(input_t); i++) {
			this->input_data_union.data_bytes[i] = input_buffer[i];
		}
		this->execute(this->input_data_union.data);
		return 0;
	}
	/* -------------------------------------------------- */
	uint8_t getSize() {
			return sizeof(input_t);
	}
	/* -------------------------------------------------- */
	uint8_t getInputSize() {
		return sizeof(input_t);
	}

	/* -------------------------------------------------- */
	uint8_t getOutputSize() {
		return 0;
	}
	/* -------------------------------------------------- */
	register_entry_type getType() {
		return REGISTER_ENTRY_FUNCTION;
	}
	/* -------------------------------------------------- */
	register_entry_rw_t getReadWriteSetting() {
		return REGISTER_ENTRY_READWRITE;
	}

	/* -------------------------------------------------- */
	union input_data_union_t {
		uint8_t data_bytes[sizeof(input_t)];
		input_t data;
	} input_data_union;

	register_entry_type type = REGISTER_ENTRY_FUNCTION;
	uint16_t address;
	core_utils_Callback<void, input_t> function;
};

/* ============================================================ */
template<typename output_t>
class core_utils_RegisterFunction<output_t, void> : public RegisterEntry {
public:
	core_utils_RegisterFunction() {

	}

	core_utils_RegisterFunction(uint16_t address) {
		this->address = address;
	}

	/* -------------------------------------------------- */
	core_utils_RegisterFunction(uint16_t address, RegisterMap *map,
			core_utils_Callback<output_t, void> function) {
		this->set(address, map, function);
	}
	/* -------------------------------------------------- */
	void set(RegisterMap *map, core_utils_Callback<output_t, void> function) {
		this->function = function;
		map->addEntry(this->address, this);
	}
	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map, core_utils_Callback<output_t, void> function) {
		this->address = address;
		this->function = function;
		map->addEntry(this->address, this);
	}

	/* -------------------------------------------------- */
	output_t execute() {
		if (this->function.registered) {
			return this->function.call();
		}
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *input_buffer, uint8_t *output_buffer) {
		return this->execute(output_buffer);
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *output_buffer) {

		output_t out = this->execute();

		uint8_t *data_ptr = (uint8_t*) &out;
		for (uint8_t i = 0; i < sizeof(output_t); i++) {
			output_buffer[i] = data_ptr[i];
		}

		return sizeof(output_t);
	}
	/* -------------------------------------------------- */
	uint8_t getSize() {
			return 0;
	}
	/* -------------------------------------------------- */
	uint8_t getInputSize() {
		return 0;
	}
	/* -------------------------------------------------- */
	uint8_t getOutputSize() {
		return sizeof(output_t);
	}
	/* -------------------------------------------------- */
	register_entry_type getType() {
		return REGISTER_ENTRY_FUNCTION;
	}
	/* -------------------------------------------------- */
	register_entry_rw_t getReadWriteSetting() {
		return REGISTER_ENTRY_READWRITE;
	}
	register_entry_type type = REGISTER_ENTRY_FUNCTION;
	uint16_t address;
	core_utils_Callback<output_t, void> function;
};

/* ============================================================ */
template<>
class core_utils_RegisterFunction<void, void> : public RegisterEntry {
public:
	core_utils_RegisterFunction() {

	}

	core_utils_RegisterFunction(uint16_t address) {
		this->address = address;
	}

	/* -------------------------------------------------- */
	core_utils_RegisterFunction(uint16_t address, RegisterMap *map,
			void (*function)(void)) {
		this->set(address, map, function);
	}
	/* -------------------------------------------------- */
	void set(RegisterMap *map, core_utils_Callback<void,void> function) {
		this->function = function;
		map->addEntry(this->address, this);
		this->type = REGISTER_ENTRY_FUNCTION;
	}
	/* -------------------------------------------------- */
	void set(uint16_t address, RegisterMap *map, core_utils_Callback<void,void> function) {
		this->address = address;
		this->function = function;
		map->addEntry(this->address, this);
		this->type = REGISTER_ENTRY_FUNCTION;
	}

	/* -------------------------------------------------- */
	void execute() {
		if (this->function.registered) {
			return this->function.call();
		}
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *output_buffer) {

		this->execute();
		return 0;
	}

	/* -------------------------------------------------- */
	uint8_t execute(uint8_t *input_buffer, uint8_t *output_buffer) {
		this->execute();
		return 0;
	}
	/* -------------------------------------------------- */
	uint8_t getSize() {
			return 0;
	}
	/* -------------------------------------------------- */
	uint8_t getInputSize() {
		return 0;
	}

	/* -------------------------------------------------- */
	uint8_t getOutputSize() {
		return 0;
	}

	/* -------------------------------------------------- */
	register_entry_type getType() {
		return REGISTER_ENTRY_FUNCTION;
	}
	/* -------------------------------------------------- */
	register_entry_rw_t getReadWriteSetting() {
		return REGISTER_ENTRY_READWRITE;
	}
	/* -------------------------------------------------- */

	register_entry_type type;
	uint16_t address;
	core_utils_Callback<void,void> function;
};
/* ============================================================ */

#endif /* UTILS_CORE_UTILS_REGISTERMAP_H_ */
