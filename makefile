main:
	cd qlearn;python setup.py build_ext --inplace
clean:
	cd qlearn;rm -rf Build *.so
