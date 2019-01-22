int	get_nbrlen(long int nbr)
{
	int	len = 0;

	do {
		nbr /= 10;
		len++;
	} while (nbr > 0);
	return (len);
}
