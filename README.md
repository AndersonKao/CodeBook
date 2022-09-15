# Codebook
My own Codebook for cp

## 1. How to Build
**Step 1:** Go to the project root and build by
~~~
$ cd Codebook
$ python GenCodebookList.py
$ xelatex Codebook.tex && xelatex Codebook.tex
~~~

### 1.1. Dependencies

* python (version >= 3.0)
* xelatex (latest version)

## 2. TODO list

1. 多餘的code
2. 重複的code
3. 3D rotation matrix
4. markdown input for Theories
5. Number Theories
	1. modpart
	2. [cp-algorithm Algebra](https://cp-algorithms.com/algebra/binary-exp.html)
	3. [x] rabin fingerprint(string hashing)
	4. [x] Vim Serach / Replace
	5. [ ] Modular Inverse
	6. [ ] More Binary Exponent
6. Graph
	1. [x] dijkstra
	2. [x] bellmanFord
	3. [x] dinic
  	4. [ ] Flow renew
7. Geometry
	1. [ ] 半平面交
	2. [ ] sweep line
		1. Line intersect
		2. Point Location
	4. [ ] Li-Chao Tree
	5. [ ] Nearest pair of points
	6. [ ] [halfplane-intersection](https://cp-algorithms.com/geometry/halfplane-intersection.html)
8. Miscelllaneous
	1. [Fast-Fourier Transform](https://cp-algorithms.com/algebra/fft.html#discrete-fourier-transform)
