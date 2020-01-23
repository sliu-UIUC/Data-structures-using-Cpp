template<class T>
  class GeneralStack {
  public:
	virtual void push(T) = 0; // pure virtual function
	virtual T pop() = 0;     // pure virtual function
	virtual bool isempty() = 0;  // pure virtual fun.
	virtual bool isfull() = 0;   // pure virtual fun.
};
