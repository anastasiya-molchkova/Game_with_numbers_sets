/* Используя пять вариантов наборов чисел:
   Набор №1: 6, 7, 8
   Набор №2: 7, 8, 9
   Набор №3: 6, 9, 10
   Набор №4: 6, 9, 8
   Набор №5: 7, 6, 10
Сыграйте с компьютером в игру. Введите с клавиатуры свой вариант и сравните с вариантом компьютера, 
который выбирается рандомно из 5 допустимых наборов. 
Если сумма цифр вашего варианта больше суммы цифр варианта компьютера, то вы выиграли и наоборот. */

#include <iostream>
#include <cstdlib>   // для функций выбора случайного числа srand() и rand()
#include <ctime>     // чтобы в randomize опираться на время запуска программы
#include <array>

// класс набора из трёх чисел
class Set
{
private:
	int n1_;
	int n2_;
	int n3_;
public:
	static const int min_possible_number_in_set = 0;
	static const int max_possible_number_in_set = 10;
	// конструктор класса,  проверка чисел осуществляется перед созданием набора
	Set(const int n1, const int n2, const int n3): n1_(n1), n2_(n2), n3_(n3)
	{}
	// сумма чисел набора
	const int get_summ()
	{
		return (n1_ + n2_ + n3_);
	}
	// перегрузка печати набора
	friend std::ostream& operator<<(std::ostream& out, const Set& set)
	{
		out << set.n1_ << " " << set.n2_ << " " << set.n3_ << std::endl;
		return out;
	}
	// перегрузка оператора сравнения двух наборов
	friend bool operator>(Set& set1, Set& set2)
	{
		return ((set1.get_summ() > set2.get_summ()) ? true : false);
	}
};

// возвращает число по ссылке и истину, если оно нормальное и между заданными значениями, или ложь - если нет
bool get_number_between(int& n, const int min, const int max)
{
	std::cin >> n;
	if (std::cin.fail() || (n < min) || (n > max))
		return false;
	return true;
}

// получает от пользователя набор из трёх чисел между заданными значениями
const Set get_users_set()
{
	const int min = Set::min_possible_number_in_set;
	const int max = Set::max_possible_number_in_set;
	std::cout << "Введите три числа от " << min << " до " << max << " через пробел: ";
	int n1{ 0 }, n2{ 0 }, n3{ 0 };
	bool numbers_are_correct = 
			get_number_between(n1, min, max) && get_number_between(n2, min, max) && get_number_between(n3, min, max);
	while (numbers_are_correct == false)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Произошла ошибка! Введите три числа от " << min << " до " << max << " заново: ";
		numbers_are_correct = 
			get_number_between(n1, min, max) && get_number_between(n2, min, max) && get_number_between(n3, min, max);
	}
	std::cin.ignore(10000, '\n'); // на случай, если ввёл лишние числа или что-то ещё
	Set set(n1, n2, n3);
	return set;
}

//функция выбора случайного числа между двумя заданными значениями
static unsigned short getRandomNumber(const unsigned short min, const unsigned short max)
{
	static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
	return static_cast<unsigned short>(rand() * fraction * (max - min + 1) + min);
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // для вывода сообщений на кириллице

	//аналог randomize с привязкой ко времени запуска:
	srand(static_cast<unsigned int>(time(0)));
	rand();

	// задаём массив из наборов чисел, которые может выбирать компьютер
	const unsigned short number_os_sets_by_default = 5;
	const std::array<Set, number_os_sets_by_default> Sets_by_default
					= { Set(6,7,8), Set(7,8,9), Set(6,9,10), Set(6,9,8), Set(7,6,10) };

	while (true) // пока не надоест
	{ 
		Set random_Set = Sets_by_default.at(getRandomNumber(0, number_os_sets_by_default - 1));
		Set users_Set = get_users_set();
		if (users_Set > random_Set) 
			std::cout << "Вы победили! ";
		else if (random_Set > users_Set)
				std::cout << "Вы проиграли! ";
			else 
				std::cout << "Ничья! ";
		std::cout << "Компьютер загадал: " << random_Set << std::endl;
	}
}