
#include <stdio.h>
#include <ctype.h>

char _I_Buffer[2110],_O_Buffer[2110],*_I_pos = _I_Buffer,*_O_pos = _O_Buffer;
inline int get()
{
	register int res = 0, k = 1;
	while (!isdigit(*_I_pos))
		if (*_I_pos++ == '-')k = 0;
	do res = (res << 3) + (res << 1), res += (*_I_pos++) & 15;while (isdigit(*_I_pos));
	return k ? res : -res;
}
inline void put(register int n)
{
	static char _buf[20];
	register char* _pos(_buf);
	if (n < 0) {*_O_pos++ = '-';n = -n;}
	do *_pos++ = 48 + n % 10;while (n /= 10);
	while (_pos != _buf)*_O_pos++ = *--_pos;
}
inline void put(register char ch){*_O_pos++ = ch;}
int main()
{
	register int n,a,b;
	fread(_I_Buffer, 1, 2110, stdin);
	n = get();
	while (n--) a = get(), b = get(), put(a + b), put('\n');
	fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout);
}
