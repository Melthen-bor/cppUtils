#ifndef UGROW_LOADED
#define UGROW_LOADED
#include <vector>
#include <string>
#include <sstream>
using namespace std;
struct small_ugrow {
	unsigned location;
	unsigned char val;
};
class ugrow {
	vector<unsigned char> value;
public:
	void set_val_zero() {
		unsigned count = 0;
		while (count < this->size()) {
			this->value.at(count) = 0;
			count++;
		}
	}
	ugrow() {
		this->value = vector<unsigned char>();
	}
	ugrow(unsigned char val) {
		this->value = vector<unsigned char>();
		this->value.push_back(val);
	}
	ugrow(vector<unsigned char> val) {
		this->value = val;
	}
	unsigned size() {
		return this->value.size();
	}
	unsigned char& get_byte(unsigned location) {
		return this->value.at(location);
	}
	void add_bytes(unsigned num) {
		unsigned count = 0;
		while (count < num) {
			this->value.push_back(0);
			count++;
		}
	}
	void increment_byte(unsigned byte_location) {
		if (byte_location > (this->size() - 1)) {
			pass();
		}
		else if (this->get_byte(byte_location) == 255) {
			this->get_byte(byte_location) = 0;
			increment_byte(byte_location + 1);
		}
		else {
			this->get_byte(byte_location)++;
		}
	}
	void decrement_byte(unsigned byte_location) {
		if(this->size()==0){
			pass();
		}
		else if (this->get_byte(byte_location) == 0) {
			if (!((byte_location + 1) == this->size())) {
				this->get_byte(byte_location) = 255;
				decrement_byte(byte_location + 1);
			}
		}
		else {
			this->get_byte(byte_location)--;
		}
	}
	unsigned char pop_byte() {
		unsigned char out = this->get_byte(this->size() - 1);
		this->value.pop_back();
		return out;
	}
	bool is_max_current_size() {
		unsigned count = 0;
		while (count < this->size()) {
			if (!(this->get_byte(count) == 255)) {
				return false;
			}
			count++;
		}
		return true;
	}
	void remove_excess() {
		while (this->size() > 0) {
			if (!(this->get_byte(this->size() - 1)) == 0) {
				break;
			}
			this->pop_byte();
		}
	}
	bool operator ==(ugrow other) {
		if (!(this->size() == other.size())) {
			return false;
		}
		unsigned count = 0;
		while (count < this->size()) {
			if (!(this->get_byte(count) == other.get_byte(count))) {
				return false;
			}
			count++;
		}
		return true;
	}
	bool operator >(ugrow other) {
		if (this->size() > other.size()) {
			return true;
		}
		if (*this == other) {
			return false;
		}
		unsigned count = this->size();
		while (count > 0) {
			if (this->get_byte(count - 1) < other.get_byte(count - 1)) {
				return false;
			}
			count--;
		}
		return true;
	}
	bool operator <(ugrow other) {
		if (this->size() < other.size()) {
			return true;
		}
		if (*this == other) {
			return false;
		}
		unsigned count = this->size();
		while (count > 0) {
			if (this->get_byte(count - 1) > other.get_byte(count - 1)) {
				return false;
			}
			count--;
		}
		return true;
	}
	bool operator >=(ugrow other) {
		return *this == other || *this > other;
	}
	bool operator <=(ugrow other) {
		return *this == other || *this < other;
	}
	ugrow& operator ++() {
		if (this->is_max_current_size()) {
			this->set_val_zero();
			this->value.push_back(1);
		}
		else {
			this->increment_byte(0);
		}
		return *this;
	}
	ugrow operator ++(int) {
		ugrow out = ugrow(this->value);
		if (this->is_max_current_size()) {
			this->set_val_zero();
			this->value.push_back(1);
		}
		else {
			this->increment_byte(0);
		}
		return out;
	}
	/*operator small_ugrow() {
		unsigned char byte = this->get_byte(this->size() - 1);
		if (this->get_byte(this->size() - 2) > 127) {
			if (byte == 255) {
				return small_ugrow{ this->size(),1 };
			}
			byte++;
		}
		return small_ugrow{ this->size() - 1,255 };
	}*/
	ugrow& operator --() {
		this->decrement_byte(0);
		this->remove_excess();
		return *this;
	}
	ugrow operator --(int) {
		ugrow out = *this;
		this->decrement_byte(0);
		this->remove_excess();
		return out;
	}
	void operator -(ugrow other) {
		ugrow count(0);
		while (count < other) {
			this->operator--();
			count++;
		}
	}
	void operator -(small_ugrow other) {
		this->add_bytes(other.location - (this->size() - 1));
		unsigned char count = 0;
		while (count < other.val) {
			this->decrement_byte(other.location);
			count++;
		}
	}
	void operator +(ugrow other) {
		ugrow count(0);
		while (count < other) {
			this->operator ++();
			count++;
		}
	}
	void operator +(small_ugrow other) {
		this->add_bytes(other.location - (this->size() - 1));
		unsigned char count = 0;
		while (count < other.val) {
			this->increment_byte(other.location);
			count++;
		}
	}
	ugrow(small_ugrow val) {
		this->value = vector<unsigned char>();
		this->operator+(val);
	}
	void operator *(ugrow other) {
		ugrow temp(this->value);
		ugrow count(0);
		while (count < other) {
			this->operator+(temp);
			count++;
		}
	}
	void operator /(ugrow other) {
		ugrow temp(this->value);
		ugrow count(0);
		while (count < other) {
			this->operator-(temp);
			count++;
		}
	}
	void operator *(small_ugrow other) {
		ugrow producer(other);
		this->operator*(producer);
	}
	void operator /(small_ugrow other) {
		ugrow producer(other);
		this->operator/(producer);
	}
	string to_string() {
		if (this->size() == 0) {
			return "0";
		}
		stringstream out;
		unsigned count = this->size();
		while (count > 0) {
			out << this->get_byte(count);
			count++;
		}
		return out.str();
	}
	void reset_value() {
		while (this->size() > 0) {
			this->pop_byte();
		}
	}
	void load_byte(unsigned char byte) {
		this->value.push_back(byte);
	}
	void load_byte(char byte) {
		this->load_byte((unsigned char)byte);
	}
	void load_byte(signed char byte) {
		this->load_byte((unsigned char)byte);
	}
	string encode() {
		unsigned count = 0;
		string out;
		while (count < size()) {
			out.push_back((char)get_byte(count));
			count++;
		}
		return out;
	}
};
#endif
