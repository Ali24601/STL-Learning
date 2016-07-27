#define ZERO 0
constexpr int get_size()
{
	return ZERO;
}
int main()
{
	int i = 5;
	int *ptr;
	const int *constptr;
	constexpr int constele = get_size();
	constptr = &i; 
	return 0;
}