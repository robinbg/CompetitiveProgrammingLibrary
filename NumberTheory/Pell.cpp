//求出p2 - D * q2 = 1的基解(最小正整数解),这个可能溢出,有必要的话,用java, 写成类比较)
//xk + yk * sqrt(D) = (x1 + y1 *sqrt(D))^k
bool PQA(LLI D, LLI &p, LLI &q) {//来自于PQA算法的一个特例
	LLI d = sqrt(D);
	if ((d + 1) * (d + 1) == D)	return false;
	if (d * d == D)					return false;
	if ((d - 1) * (d - 1) == D)	return false;//这里是判断佩尔方程有没有解
	LLI u = 0, v = 1, a = int(sqrt(D)), a0 = a, lastp = 1, lastq = 0;
	p = a, q = 1;
	do {
		u = a * v - u;
		v = (D - u * u) / v;
		a = (a0 + u) / v;
		LLI thisp = p, thisq = q;
		p = a * p + lastp;
		q = a * q + lastq;
		lastp = thisp;
		lastq = thisq;
	} while ((v != 1 && a <= a0));//这里一定要用do~while循环
	p = lastp;
	q = lastq;
	//这样求出后的(p,q)是p2 – D * q2 = (-1)k的解，也就是说p2 – D * q2可能等于1也可能等于-1,如果等于1,(p,q)就是解,如果等于-1还要通过(p2 + D * q2,2 * p * q)来求解，如下
	if (p * p - D * q * q == -1) {
		p = lastp * lastp + D * lastq * lastq;
		q = 2 * lastp * lastq;
	}
	return true;
}
