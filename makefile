main:
	python setup.py build_ext --inplace
clean:
	rm -rf Build *.so
