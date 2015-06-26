/*Controls invalid inputs and the exceptions they throw.*/

class InvalidInput
{
public:
	InvalidInput(const char* in_ptr) : msg_ptr(in_ptr) { }
	const char* const msg_ptr;
private:
	InvalidInput(); // no default construction
};
