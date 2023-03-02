/*
 * core_utils_registermap.h
 *
 *  Created on: 26 Feb 2023
 *      Author: Dustin Lehmann
 */

#ifndef UTILS_CORE_UTILS_REGISTERMAP_H_
#define UTILS_CORE_UTILS_REGISTERMAP_H_

/* ============================================================ */
class RegisterEntry {
public:
	virtual void set(void *value){

	}
	virtual void set(uint8_t* data){

	}
};

/* ============================================================ */
class RegisterMap {

};

/* ============================================================ */
class core_utils_RegisterMap {
public:

	void set(uint16_t address, void *data) {
		if (this->entries[address] != NULL){
			this->entries[address]->set(data);
		}
	}
	void set(uint16_t address, uint8_t *data) {
		if (this->entries[address] != NULL){
			this->entries[address]->set(data);
		}
	}

	void addEntry(uint16_t address, RegisterEntry *entry) {
		this->entries[address] = entry;
	}

	RegisterEntry *entries[10] = {0};
private:

};

/* ============================================================ */
template<typename T>
class core_utils_RegisterEntry: public RegisterEntry {
public:
	core_utils_RegisterEntry(uint16_t address, core_utils_RegisterMap *map,
			T *data) {
		this->data = data;
		this->address = address;
		map->addEntry(address, this);
		this->size = sizeof(T);
	}
	/* -------------------------------------------------- */
	core_utils_RegisterEntry(uint16_t address, core_utils_RegisterMap *map,
			T *data, core_utils_Callback write_callback) {
		this->address = address;
		this->data = data;
		this->write_callback = write_callback;
		this->write_callback_set = true;
		map->addEntry(address, this);
		this->size = sizeof(T);
	}
	/* -------------------------------------------------- */
	void set(T value) {
		*(this->data) = value;
		this->write_callback();
	}
	/* -------------------------------------------------- */
	void set(void *value) {

		T* value_typed = (T*) value;

		*(this->data) = *value_typed;
	}
	/* ------------------------- */
	void set(uint8_t *data) { // TODO: not good

		for (uint8_t i  = 0; i < sizeof(T); i++) {
			this->data_union.data_bytes[i] = data[i];
		}
		this->set(this->data_union.data);
	}
	/* -------------------------------------------------- */
	uint8_t getBytes(uint8_t *data) {
		this->data_union.data = *(this->data);

		for (uint8_t i =0; i<sizeof(T); i++){
			data[i] = this->data_union.data_bytes[i];
		}
		return sizeof(T);
	}
	/* -------------------------------------------------- */
	T get() {
		return *(this->data);
	}

	/* -------------------------------------------------- */

	union data_union_t {
		uint8_t data_bytes[sizeof(T)];
		T data;
	} data_union;

	uint16_t address;
private:
	T *data;
	uint8_t size;
	bool write_callback_set = false;
	core_utils_Callback write_callback;
};

/* ============================================================ */

/* ============================================================ */

/* ============================================================ */

#endif /* UTILS_CORE_UTILS_REGISTERMAP_H_ */
