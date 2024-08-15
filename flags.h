#ifndef FLAGS_LOADED
#define FLAGS_LOADED
class flags {
	unsigned char data;
public:
	flags() {
		this->data = 0;
	}
	void store(unsigned char location, bool val){
		if (val) {
			this->data |= (1 << (location % 8));
		}
		else {
			this->data &= (255 - (1 << (location % 8)));
		}
	}
	bool read(unsigned char location) {
		return (this->data & (1 << (location % 8)));
	}
};
#endif
