Project of Paulo Zemek.   
From http://www.codeproject.com/Articles/746630/O-Object-Pool-in-Cplusplus  
## usage

To use the code we must initialize the pool giving the initial capacity and the maximum size for the other blocks. 
If we don't give any parameter, the defaults of 32 (for the initial capacity) and 1 million (for the maximum block size) are used.  

So, a line like the following will initialize our pool in the stack (or statically) using those defaults:

	ObjectPool<Test> pool;

Then, to allocate an object we do:

	Test *test = pool.New();

And to deallocate an object we do:


	pool.Delete(test);

If we don't want to use the default constructor, we can do:


	T *unitializedObject = pool.GetNextWithoutInitializing();
	// And then we can call an appropriate constructor:
	Test *test = new (uninitializedObject) Test(/*... parameters here...*/);

And if we don't want to allow the destructor to be called but we want to return the memory to the pool, we can use:


	pool.DeleteWithoutDestroying(test);

Obviously, we should use the appropriate class instead of Test and the appropriate variable names instead of test.