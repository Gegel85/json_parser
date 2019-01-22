long	power(long nb, int p)
{
	if (p > 0)
		nb *= power(nb, p - 1);
	else
		return (1);
	return (nb);
}
