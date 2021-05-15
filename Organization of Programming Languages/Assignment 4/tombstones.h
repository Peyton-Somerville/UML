using std::cerr;

template <class T>
class Tombstone {
public:
	T* val;
	bool expired;

	Tombstone<T>() {
		val = NULL;
		expired = false;
	}
};

template <class T>
class Pointer {
public:
	Pointer<T>() {	// default constructor
		ptr = new Tombstone<T>();
	}

	Pointer<T>(Pointer<T>& t) {	// copy constructor
		if (!t.ptr->expired)
			ptr = t.ptr;
	}

	Pointer<T>(T* value) {	// bootstrapping constructor
		ptr = new Tombstone<T>();
		ptr->val = value;
		ptr->expired = false;
	}
	// The parameter for the bootstrapping constructor should always be
	// a call to operator new.

	~Pointer<T>() {	// destructor
		ptr = NULL;
	}

	T& operator*() const { // dereferencing
		if (!ptr->expired)
			return *(ptr->val);
		else {
			cerr << "(op*) tombstone is expired. Exiting...\n";
			exit(1);
		}
	}

	T* operator->() const { // field dereferencing
		if (!ptr->expired)
			return ptr->val;
		else {
			cerr << "(op->) tombstone is expired. Exiting...\n";
			exit(1);
		}
	}

	Pointer<T>& operator=(const Pointer<T>& t) { // assignment
		ptr = t.ptr;

		if(ptr->expired) {
			cerr << "(op=) tombstone is expired. Exiting...\n";
			exit(1);
		}

		return *this;
	}

	friend void free(Pointer<T>& t) { // delete pointed-at object
		if (!t.ptr->expired) {
			delete t.ptr->val;
			t.ptr->expired = true;
		}
	}
	// This is essentially the inverse of the new inside the call to
	// the bootstrapping constructor. It should delete the pointed-to
	// object (which should in turn call its destructor).

	// equality comparisons:
	bool operator==(const Pointer<T>& t) const {
		if (!ptr->expired && !t.ptr->expired) {
			if (ptr->val == t.ptr->val)
				return true;
			else
				return false;
		}
		else {
			cerr << "(op==) tombstone is expired. Exiting...\n";
			exit(1);
		}
	}

	bool operator!=(const Pointer<T>& t) const {
		if (!ptr->expired && !t.ptr->expired) {
			if (ptr->val != t.ptr->val)
				return true;
			else
				return false;
		}
		else {
			cerr << "(op!=) tombstone is expired. Exiting...\n";
			exit(1);
		}
	}

	bool operator==(const int n) const {	// true iff Pointer is null and int is zero
		if (ptr->val == NULL && n == 0)
			return true;
		else
			return false;
	}
	

	bool operator!=(const int n) const {	// false iff Pointer is null and int is zero
		if (ptr->val == NULL && n == 0)
			return false;
		else
			return true;
	}

private:
	Tombstone<T>* ptr;
};


template <class T>
bool operator==(const int n, const Pointer<T>& t) { return t == n; }

template <class T>
bool operator!=(const int n, const Pointer<T>& t) { return t != n; }
