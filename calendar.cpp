#include <iostream>

#define ODD 31
#define EVEN 30
#define LEAP 29
#define NORMAL 28
#define MONTHS 12

#define B_RED "\033[91m"
#define DARK_GREY "\033[2m"
#define DEFAULT "\033[0m"
#define STRIKETHROUGH "\033[9m"

enum
{
	Jan,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};

/* initializes std::string mon[12] */
static void initialize_months(std::string (&mon)[12])
{
	mon[Jan] = "Jan";
	mon[Feb] = "Feb";
	mon[Mar] = "Mar";
	mon[Apr] = "Apr";
	mon[May] = "May";
	mon[Jun] = "Jun";
	mon[Jul] = "Jul";
	mon[Aug] = "Aug";
	mon[Sep] = "Sep";
	mon[Oct] = "Oct";
	mon[Nov] = "Nov";
	mon[Dec] = "Dec";
}

/* checks conditions and outputs day number */
static void output_conditions(unsigned int &i, unsigned int &current_month)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (i < (unsigned int)ltm->tm_mday && current_month == (unsigned int)ltm->tm_mon)
		std::cout << DARK_GREY << STRIKETHROUGH << i << " " << DEFAULT;
	else if (i == (unsigned int)ltm->tm_mday && current_month == (unsigned int)ltm->tm_mon)
		std::cout << B_RED << i << " " << DEFAULT;
	else
		std::cout << i << " ";
}

/* ouputs days */
static void output_days(unsigned int &current_month, unsigned int n)
{
	if (n == 29)
	{
		for (unsigned int i = 1; i <= LEAP; i++)
			output_conditions(i, current_month);
		std::cout << std::endl;
	}
	else if (n == 28)
	{
		for (unsigned int i = 1; i <= NORMAL; i++)
			output_conditions(i, current_month);
		std::cout << std::endl;
	}
	else if (n == 31)
	{
		for (unsigned int i = 1; i <= ODD; i++)
			output_conditions(i, current_month);
		std::cout << std::endl;
	}
	else if (n == 30)
	{
		for (unsigned int i = 1; i <= EVEN; i++)
			output_conditions(i, current_month);
		std::cout << std::endl;
	}
}

/* outputs months */
static void output_months(std::string (&mon)[12], unsigned int &current_month)
{
	std::cout << mon[current_month] << "\t";
}

int main(void)
{
	std::string mon[12];
	time_t now = time(0);
	tm *ltm = localtime(&now);
	unsigned int year = 1900 + ltm->tm_year;
	unsigned int current_month = 0;

	initialize_months(mon);
	std::cout << year << std::endl;
	while (current_month < MONTHS)
	{
		output_months(mon, current_month);
		if (current_month == Feb)
		{
			if (year % 4 == 0)
				output_days(current_month, LEAP);
			else  
				output_days(current_month, NORMAL);
		}
		else if (current_month == Aug)
			output_days(current_month, ODD);
		else if (current_month >= Sep && current_month % 2 == 0)
			output_days(current_month, EVEN);
		else if (current_month >= Sep && current_month % 2 != 0)
			output_days(current_month, ODD);
		else if (current_month % 2 == 0)
			output_days(current_month, ODD);
		else if (current_month % 2 != 0)
			output_days(current_month, EVEN);
		current_month++;
	}
	return (0);
}
