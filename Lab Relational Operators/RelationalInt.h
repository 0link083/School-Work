bool gt(int i, int j) {
	return j < i;
}

bool eq(int i, int j) {
	return (!(i < j) && !(j < i));
}

bool ge(int i, int j) {
	if (eq(i,j)) return true;
	else return gt(i, j);
}

bool le(int i, int j) {
	if (eq(i,j)) return true;
	else return gt(j, i);
}

bool ne(int i, int j) {
	return !(eq(i,j));
}